/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/InternalLayer.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

#include "InternalLayerFragmentShader.h"
#include "InternalLayerVertexShader.h"

namespace VisApp {
namespace Renderer {

struct Flags {
	enum {
		Have_Texture	 = 1 << 0,
		Have_Vertexes	 = 1 << 1,
		Have_Index		 = 1 << 2,
		Have_UVWs		 = 1 << 3,
	};
};

typedef VAO::MeshData MeshData;

InternalLayer::InternalLayer(const std::wstring& Name): LayerInterface(Name) { }
InternalLayer::~InternalLayer() { }


class InternalLayerConstructor;
class InternalLayerImpl;
InternalLayerConstructor *CreateInternalLayerConstructor(InternalLayerImpl *Owner);
void DeleteInternalLayerConstructor(InternalLayerConstructor *&ptr);

class PredefLayerNames {
public:
	std::wstring Texture, Vertex, Index, UVWs, MeshData;

	PredefLayerNames():
		Texture(L"TextureData"),
		Vertex(L"VertexTable"),
		Index(L"ElementIndex"),
		UVWs(L"TextureMappings"),
		MeshData(L"MeshData") { }
};

const PredefLayerNames InternalLayerNames;

class InternalLayerImpl : public InternalLayer {
friend class InternalLayerConstructor;
public:
	InternalLayerImpl(const std::wstring& Name): InternalLayer(Name) {
		m_Editable = true;
		m_Constructor = 0;
		m_Flags = 0;
	};

	~InternalLayerImpl() {
		DeleteInternalLayerConstructor(m_Constructor);
	}

	const wchar_t* GetLayerClassName() const {
		return L"InternalLayerClass";
	}

	void DoRender(GraphicDevice &dev) const {
		if(!m_EnableTexLocation)
			m_EnableTexLocation = GetShader()->CustomLocation("EnableTexturing");

		glUniform1i(m_EnableTexLocation, m_Flags & Flags::Have_Texture);
		m_Texture.Bind();
		m_VAO.Bind();
		for (auto &mesh : m_Meshes) {
			m_VAO.DrawElements(mesh.NumIndices, mesh.BaseIndex, mesh.BaseVertex, mesh.ElementMode);
		}
		m_VAO.UnBind();
	}

	bool CanBeEdited() const { return m_Editable; }

	LayerConstructor* GetLayerConstructor() { 
		if(m_Editable && !m_Constructor)
			m_Constructor = CreateInternalLayerConstructor(this);
		return (LayerConstructor*)m_Constructor; 
	}

	void DisableEditing() { 
		m_Editable = false; 
		SetReadyState();
	}
	 
	Error Initialize(GraphicDevice &dev) {
		Shader *shader;
		SetShader(shader = dev.GetShaderMgt().GetShader(L"InternalLayerDefaultShader", [&dev] (Shader* s) -> bool {
			const char* fs[] = { (const char*)InternalLayerFragmentShader_glsl, 0};
			const char* vs[] = { (const char*)InternalLayerVertexShader_glsl, 0};
			if(!s->LoadCode(GL_VERTEX_SHADER, vs, 1) ||
			   !s->LoadCode(GL_FRAGMENT_SHADER, fs, 1)) return false;
			s->SetVAOChannel("inVertexModelSpace", 0);
			s->SetVAOChannel("inVertexUVW", 1);
			return s->Compile();
		})); 
		if(!shader) return Error::Fatal;
		m_EnableTexLocation = 0;//GetShader()->CustomLocation("EnableTexturing");

		m_VAO.New();
		unsigned channel;
		{
			auto mem = GetOwner()->OpenMemory(this, InternalLayerNames.Vertex);
			if(mem) {
				m_VAO.AddDataChannel<3, float_t>((float_t*)mem->Get(), m_VertexCount, channel);
		//		shader->SetVAOChannel("inVertexModelSpace", channel);
			}
		}
		{
			auto mem = GetOwner()->OpenMemory(this, InternalLayerNames.UVWs);
			if(mem) {
				m_VAO.AddDataChannel<2, float_t>((float_t*)mem->Get(), m_UVWCount, channel);
		//		shader->SetVAOChannel("inVertexUVW", channel);
			}
		}
		{
			auto mem = GetOwner()->OpenMemory(this, InternalLayerNames.Index);
			if(mem) {
				m_VAO.WriteIndexes((unsigned*)mem->Get(), m_IndexCount);
			}
		}
		{
			auto mem = GetOwner()->OpenMemory(this, InternalLayerNames.Texture);
			if(mem) {
				m_Texture.LoadTexture(mem->Get(), m_TextureSize[0], m_TextureSize[1], m_TextureColorLayout, m_TextureElementType);
				m_Flags |= Flags::Have_Texture;
			}
			c2DTexture::ActivateChannel(0);
		}
		m_VAO.UnBind();
		{
			auto mem = GetOwner()->OpenMemory(this, InternalLayerNames.MeshData);
			if(mem) {
				m_Meshes.resize(m_MeshCount);
				memcpy(&m_Meshes[0], mem->Get(), sizeof(m_Meshes[0]) * m_MeshCount);
			}
		}
		return Error::NoError;
	}
	Error Finalize(GraphicDevice &dev) {
		m_Meshes.clear();
		m_Meshes.reserve(0);
		m_Texture.Free();
		m_VAO.Free();
		return Error::NoError;
	}

	Error Load(const xml_node src) {
		m_Editable = false; 
		xml_node TexNode = src.child(L"Texture");
		m_TextureColorLayout = TexNode.child(L"ColorLayout").attribute(L"IntVal").as_uint();
		m_TextureElementType = TexNode.child(L"ElementType").attribute(L"IntVal").as_uint();
		xml_node Size = TexNode.child(L"Size");
		m_TextureSize[0] = Size.attribute(L"W").as_uint();
		m_TextureSize[1] = Size.attribute(L"H").as_uint();

		xml_node BufferNode = src.child(L"Buffers");
		m_VertexCount = BufferNode.child(InternalLayerNames.Vertex.c_str()).attribute(L"Count").as_uint();
		m_UVWCount	  = BufferNode.child(InternalLayerNames.UVWs.c_str()).attribute(L"Count").as_uint();  
		m_IndexCount  = BufferNode.child(InternalLayerNames.Index.c_str()).attribute(L"Count").as_uint(); 
		m_MeshCount   = BufferNode.child(InternalLayerNames.MeshData.c_str()).attribute(L"Count").as_uint(); 

		auto r =  LayerInterface::Load(src);
		SetReadyState();
		return r;
	}
	Error Save(xml_node dst) const {
		xml_node TexNode = dst.append_child(L"Texture");
		TexNode.append_child(L"ColorLayout").append_attribute(L"IntVal") = m_TextureColorLayout;
		TexNode.append_child(L"ElementType").append_attribute(L"IntVal") = m_TextureElementType;
		xml_node Size = TexNode.append_child(L"Size");
		Size.append_attribute(L"W") = m_TextureSize[0];
		Size.append_attribute(L"H") = m_TextureSize[1];

		xml_node BufferNode = dst.append_child(L"Buffers");
		BufferNode.append_child(InternalLayerNames.Vertex.c_str()).append_attribute(L"Count") = m_VertexCount;
		BufferNode.append_child(InternalLayerNames.UVWs.c_str()).append_attribute(L"Count") = m_UVWCount;
		BufferNode.append_child(InternalLayerNames.Index.c_str()).append_attribute(L"Count") = m_IndexCount;
		BufferNode.append_child(InternalLayerNames.MeshData.c_str()).append_attribute(L"Count") = m_MeshCount;

		return LayerInterface::Save(dst);
	}
protected:
	InternalLayerConstructor *m_Constructor;
	bool m_Editable;

	VAO m_VAO;
	std::vector<MeshData> m_Meshes;
	unsigned m_Flags;

	GLuint m_TextureColorLayout, m_TextureElementType;
	c2DTexture m_Texture;
	Math::uvec2 m_TextureSize;
	unsigned m_VertexCount, m_UVWCount, m_IndexCount, m_MeshCount;
	mutable GLuint m_EnableTexLocation;

	void NoMoreConstructible() {
		if(!m_Constructor) return;
		DeleteInternalLayerConstructor(m_Constructor);
		m_Editable = false;
	}
};

//-------------------------------------------------------------------------------------------

LayerConstructor::~LayerConstructor() { }
LayerConstructor::LayerConstructor() { }

class InternalLayerConstructor : public LayerConstructor {
public:

	~InternalLayerConstructor() {
	}
	InternalLayerConstructor(InternalLayerImpl *Owner): m_Owner(Owner) {
		m_Flags = 0;
		for(int i = 0; i < 3; ++i) 
			m_MinSize[i] = 1e10, m_MaxSize[i] = -1e10;

	}

	void SetTextureData(void* Texture, unsigned DataSize, const Math::uvec2 &Size, unsigned GLPixelMode, unsigned GLValueSize, unsigned Config) {
		if(!m_Owner->CanBeEdited()) return;
		if(!Texture || !DataSize) return;

		m_Owner->m_TextureSize = Size;
		m_Owner->m_TextureColorLayout = GLPixelMode;
		m_Owner->m_TextureElementType = GLValueSize;
		
		auto mem = m_Owner->GetOwner()->AllocateMemory(m_Owner, InternalLayerNames.Texture, DataSize);
		mem->PushData(Texture, DataSize, 0);

		m_Flags |= Flags::Have_Texture;
	}

	void SetLayerType(LayerType lt) {
		m_Owner->SetLayerType(lt);
	}

	void PushMeshIndexes(const IndexVector& index, unsigned ElementMode) {
		if(!m_Owner->CanBeEdited()) return;

		MeshData md;
		md.BaseIndex = (unsigned __int32)m_Index.size();
		md.NumIndices = (unsigned __int32)index.size();
		md.BaseVertex = 0;
		md.ElementMode = (unsigned __int32)ElementMode;
	//copy indexes
		m_Index.reserve(index.size() + 1);
		for(auto &it: index)
			m_Index.push_back(it);
		m_Flags |= Flags::Have_UVWs;

		m_Meshes.push_back(md);
		m_Flags |= Flags::Have_Index;
	}
	void PushUVMapping(const UVMapVector& uvs) {
		if(!m_Owner->CanBeEdited()) return;
		m_UVs.reserve(uvs.size() + 1);
		for(auto &it: uvs)
			m_UVs.push_back(it);
		m_Flags |= Flags::Have_UVWs;
	}

	void PushVertexes(const VertexVector& vertexes) {
		if(!m_Owner->CanBeEdited()) return;
		m_Vertexes.reserve(vertexes.size() + 1);
		for(auto &it: vertexes) {
			m_Vertexes.push_back(it);
			
			for(int i = 0; i < 3; ++i)
				m_MinSize[i] = Math::Min(m_MinSize[i], it[i]),
				m_MaxSize[i] = Math::Max(m_MaxSize[i], it[i]);
		}
		m_Flags |= Flags::Have_Vertexes;
		m_Owner->SetSize(m_MaxSize - m_MinSize);
	}

	index_t GetIndexesCount() const { return m_Index.size(); }
	index_t GetUVsCount() const { return m_UVs.size(); }
	index_t GetMeshCount() const { return m_Meshes.size(); }
	index_t GetVertexCount() const { return m_Vertexes.size(); }

	void Done() { 
		m_Owner->m_VertexCount = m_Vertexes.size();
		m_Owner->m_IndexCount = m_Index.size();
		m_Owner->m_UVWCount = m_UVs.size();
		m_Owner->m_MeshCount = m_Meshes.size();

		if(m_Index.size() > 0) {
			length_t len = m_Index.size() * sizeof(m_Index[0]);
			auto mem = m_Owner->GetOwner()->AllocateMemory(m_Owner, InternalLayerNames.Index, len);
			mem->PushData(&m_Index[0], len, 0);
		}

		if(m_UVs.size() > 0) {
			length_t len = m_UVs.size() * sizeof(m_UVs[0]);
			auto mem = m_Owner->GetOwner()->AllocateMemory(m_Owner, InternalLayerNames.UVWs, len);
			mem->PushData(&m_UVs[0], len, 0);
		}

		if(m_Vertexes.size() > 0) {
			length_t len = m_Vertexes.size() * sizeof(m_Vertexes[0]);
			auto mem = m_Owner->GetOwner()->AllocateMemory(m_Owner, InternalLayerNames.Vertex, len);
			mem->PushData(&m_Vertexes[0], len, 0);
		}

		if(m_Meshes.size() > 0) {
			length_t len = m_Meshes.size() * sizeof(m_Meshes[0]);
			auto mem = m_Owner->GetOwner()->AllocateMemory(m_Owner, InternalLayerNames.MeshData, len);
			mem->PushData(&m_Meshes[0], len, 0);
		}
		m_Owner->DisableEditing(); 
	}
protected:
	IndexVector m_Index;
	UVMapVector m_UVs;
	VertexVector m_Vertexes;
	std::vector<MeshData> m_Meshes;
	Math::fvec3 m_MinSize, m_MaxSize;

	unsigned m_Flags;

	InternalLayerImpl *m_Owner;
};

InternalLayerConstructor *CreateInternalLayerConstructor(InternalLayerImpl *Owner) {
	return new InternalLayerConstructor(Owner);
}

void DeleteInternalLayerConstructor(InternalLayerConstructor *&ptr) {
	delete ptr;
	ptr = 0;
}

//-------------------------------------------------------------------------------------------

void RegisterInternalLayer() {
	LayerClassList::AutoClassRegister 
		InternalLayerReg(
			L"InternalLayerClass", [] (const std::wstring& Name) 
					{ return new InternalLayerImpl(Name); } );
}
} //namespace Renderer 
} //namespace VisApp 
