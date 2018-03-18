/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/CubeLayer.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "Stdafx.h"
#include "CubeLayer.h"
#include "ConfigForm.h"

#pragma unmanaged

#include "FragmentShader.h"
#include "VertexShader.h"

#define D3TEX_RES_NAME L"CubeMap"


CubeLayer::CubeLayer(const std::wstring& Name): Renderer::LayerInterface(Name) {
	SetLayerType(Renderer::LayerType::d3);
	m_RenderCubeEdges = true;
	m_RegenerateSlicesVAO = true;
	m_RenderInternalEdges = true;
	m_Mode = CubeLayerMode::Planes3;
}

CubeLayer::~CubeLayer() {

}

//-------------

void CubeLayer::SetMode(CubeLayerMode mode) {
	m_Mode = mode;

	switch (mode) {
	case CubeLayerMode::Planes3: {
			m_Slices.clear();
			Math::uvec3 center = m_CubeSize;
			for(int i = 0; i < 3; ++i)
				center[i] /= 2;
			m_Slices.push_back(CubeSlice(Planes::Plane::XY, center));
			m_Slices.push_back(CubeSlice(Planes::Plane::XZ, center));
			m_Slices.push_back(CubeSlice(Planes::Plane::YZ, center));
			InvalidateSlicesVAO();
			m_RegenerateEdgesMesh = true;
		}
		break;
	case CubeLayerMode::OuterCube: {
			m_Slices.clear();
			m_Slices.push_back(CubeSlice(Planes::Plane::XY, Math::uvec3(0)));
			m_Slices.push_back(CubeSlice(Planes::Plane::XZ, Math::uvec3(0)));
			m_Slices.push_back(CubeSlice(Planes::Plane::YZ, Math::uvec3(0)));

			m_Slices.push_back(CubeSlice(Planes::Plane::XY, m_CubeSize));
			m_Slices.push_back(CubeSlice(Planes::Plane::XZ, m_CubeSize));
			m_Slices.push_back(CubeSlice(Planes::Plane::YZ, m_CubeSize));
			InvalidateSlicesVAO();
			m_RegenerateEdgesMesh = true;
		}
		break;
	case CubeLayerMode::User:
		break;
	default:
		break;
	}
}

void CubeLayer::DoRender(Renderer::GraphicDevice &dev) const {
	glUniform3uiv(m_CubeSizeLocation, 1, &m_CubeSize[0]);

#if 0
	if(m_dbgAnim) {
		auto xthis = (CubeLayer*)this;
		xthis->m_RegenerateSlicesVAO = true;
		for(auto &slice: xthis->m_Slices) {
			Math::fvec3 Coords[4];
			auto &p = Planes::PlanesCoords(slice.Plane);
			slice.CenterPoint[p[2]]++;
			slice.CenterPoint[p[2]] %= m_CubeSize[p[2]];
		}
	}
#endif    
	if(m_RegenerateSlicesVAO) {
		auto xthis = (CubeLayer*)this;
		xthis->RecreateSlicesVAO();
		xthis->m_RegenerateSlicesVAO = false;
	}
	 
	if(m_RegenerateEdgesMesh) {
		auto xthis = (CubeLayer*)this;
		xthis->RecreateEdgesMesh();
		xthis->m_RegenerateEdgesMesh = false;
	}  
	   
	auto t = dev.CurrentShader()->CustomLocation("mode"); 
	glUniform1i(t, 0);
	m_CubeTexture.Bind();
	m_SlicesVAO.RenderMesh(m_SlicesMesh);

	glUniform1i(t, 1);
	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	if(m_RenderInternalEdges || m_RenderCubeEdges) { 
		float black[3] = { }; 
		glUniform3fv(m_BaseColorLocation, 1, black);
		m_EdgesVAO.RenderMesh(m_EdgesMesh);
	} 
} 

CubeLayer::Error CubeLayer::Initialize(Renderer::GraphicDevice &dev) {
//	OpenGLAssertFunction(GLEW_VERSION_1_2);
	//OpenGLAssertFunction(glUniform1i);
	////OpenGLAssertFunction(glUniform3fv);
	//OpenGLAssertFunction(glUniform3uiv);

	auto shader = 
		dev.GetShaderMgt().GetShader(L"CubeSliceLayerBasicShader", 
			[&dev] (Renderer::Shader* s) -> bool {
				const char* fs[] = { (const char*)FragmentShader_glsl, 0};
				const char* vs[] = { (const char*)VertexShader_glsl, 0};
				if(!s->LoadCode(GL_VERTEX_SHADER, vs, 1) ||
				   !s->LoadCode(GL_FRAGMENT_SHADER, fs, 1)) return false;
				s->SetVAOChannel("inVertexModelSpace", 0);
				s->SetVAOChannel("inVertexUVW", 1);
				return s->Compile();
			});  
	if(!shader)
		return Error::Fatal;
	SetShader(shader);
	dev.Bind(shader); 
	m_CubeSizeLocation = shader->CustomLocation("CubeSize");
	m_BaseColorLocation = shader->CustomLocation("BaseColor"); 
	   
	auto mem = GetOwner()->OpenMemory(this, D3TEX_RES_NAME);
	if(mem) {
		Renderer::Texture::ActivateChannel(0);
		m_CubeTexture.New();
		glTexImage3D(GL_TEXTURE_3D, 0/*MipmapLevel*/, 
			GL_RGB, 
			m_CubeSize[0], m_CubeSize[1], m_CubeSize[2],
			0, 
			GL_RGB, GL_UNSIGNED_BYTE, mem->Get());
		  
		auto mode = GL_TEXTURE_3D;
		glTexParameteri(mode, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(mode, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(mode, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glTexParameteri(mode, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(mode, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	} 
	  
	RecreateEdgesMesh();
	RecreateSlicesVAO(); 
	  
	return Error::NoError; 
}
 
CubeLayer::Error CubeLayer::Finalize(Renderer::GraphicDevice &dev) {
	m_CubeTexture.Free();
	m_SlicesVAO.Free();
	m_EdgesVAO.Free();
	return Error::NoError;
}

Renderer::LayerCLIGUIHandler* CubeLayer::QuerryCLIGuiHandler() const {
	if(!m_GuiHandler) {
		if(_GuiHandlerInstance.expired()) {
			m_GuiHandler.reset(new CubeSlicer::CubeLayerGuiHandler((CubeLayer*)this));
			_GuiHandlerInstance = m_GuiHandler;
		} else {
			m_GuiHandler = _GuiHandlerInstance.lock();
		}
	}
	return m_GuiHandler.get();
}

CubeLayer::Error CubeLayer::Load(const xml_node src) {
	LayerInterface::Load(src);

	auto CubeSizeNode = src.child(L"CubeSize");
	m_CubeSize[0] = CubeSizeNode.attribute(L"X").as_uint();
	m_CubeSize[1] = CubeSizeNode.attribute(L"Y").as_uint();
	m_CubeSize[2] = CubeSizeNode.attribute(L"Z").as_uint();

	auto SettingsNode = src.child(L"Config");
	m_RenderCubeEdges = SettingsNode.child(L"RenderCubeEdges").text().as_bool(true);
	m_RenderInternalEdges = SettingsNode.child(L"RenderInternalEdges").text().as_bool(true);
	m_Mode = (CubeLayerMode)SettingsNode.child(L"Mode").text().as_uint(0);
	SetMode(m_Mode);

	if(m_Mode == CubeLayerMode::User) {
		//TODO read
	}

	return Error::NoError;
}

CubeLayer::Error CubeLayer::Save(xml_node dst) const {
	LayerInterface::Save(dst);

	auto CubeSizeNode = dst.append_child(L"CubeSize");
	CubeSizeNode.append_attribute(L"X") = m_CubeSize[0];
	CubeSizeNode.append_attribute(L"Y") = m_CubeSize[1];
	CubeSizeNode.append_attribute(L"Z") = m_CubeSize[2];

	auto SettingsNode = dst.append_child(L"Config");
	SettingsNode.append_child(L"RenderCubeEdges").text() = m_RenderCubeEdges;
	SettingsNode.append_child(L"RenderInternalEdges").text() = m_RenderInternalEdges;
	SettingsNode.append_child(L"Mode").text() = (unsigned)m_Mode;
	
	if(m_Mode == CubeLayerMode::User) {
		//TODO write
	}

	return Error::NoError;
}
 
//--------------
 
void CubeLayer::RecreateSlicesVAO() {
	m_SlicesVAO.New();
	m_SlicesMesh.clear();
	  
	typedef std::vector<Math::fvec3> Vec3Vector;
	 
	unsigned ch;
	Math::fvec3 hs;
	for(int i = 0; i < 3; ++i)
		hs[i] = m_CubeSize[i] / 2.0f;

	Vec3Vector Vertexes;
	Vec3Vector UVWs;

	bool Added = false;

	for(auto &slice: m_Slices) {
		if(slice.Hide) continue;
		auto &p = Planes::PlanesCoords(slice.Plane);

		Math::fvec3 Coords[4] = { hs, hs, hs, hs, };
		 
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 2; ++k) {
				Coords[j][p[k]] *= Planes::VertexOrder(j)[k];
				//if(Coords[j][p[k]] > 0)
				//	Coords[j][p[k]] -= 1;
			}

			Coords[j][p[2]] = hs[p[2]] - slice.CenterPoint[p[2]];
		}
		   
		Math::fvec3 Tex[4];
		float t = 1.0f / m_CubeSize[p[0]];
		     
		for(int i = 0; i < 4; ++i) {
			auto &base = Planes::TexCoordOrder(i);
			Tex[i][p[0]] = (float)base[0];
			Tex[i][p[1]] = (float)base[1];
			if(slice.CenterPoint[p[2]] == ((float)m_CubeSize[p[2]] - 1))
				Tex[i][p[2]] = 1;
			else
				Tex[i][p[2]] = slice.CenterPoint[p[2]] / ((float)m_CubeSize[p[2]] - 1);

			Tex[i][p[2]] = 1 - Tex[i][p[2]];
		} 

		for(int i = 0; i < 4; ++i) Vertexes.push_back(Coords[i]);
		for(int i = 0; i < 4; ++i) UVWs.push_back(Tex[i]);
		Added = true;
	}

	if(Added) {
		m_SlicesVAO.AddDataChannel<3, float>(&Vertexes[0][0], Vertexes.size(), ch);
		m_SlicesVAO.AddDataChannel<3, float>(&UVWs[0][0], UVWs.size(), ch);
		std::vector<unsigned __int32> Indexes;
		for(unsigned i = 0; i < Vertexes.size(); ++i)
			Indexes.push_back(i);
		m_SlicesVAO.WriteIndexes(&Indexes[0], Indexes.size());
		m_SlicesMesh.push_back_mesh(0, 0, Indexes.size(), GL_QUADS);
	}
	m_SlicesVAO.UnBind();
}

void CubeLayer::CreateEdgesSliceMesh(std::vector<Math::fvec3> &VertexVec, std::vector<unsigned> &IndexVector) {
	Math::fvec3 hs = Math::fvec3(m_CubeSize) / 2.0f;
	for(unsigned i = 0, j = m_Slices.size(); i < j; ++i) {
		auto &srcSlice = m_Slices[i];
		if(srcSlice.Hide) continue;

		{
			auto &psrc = Planes::PlanesCoords(srcSlice.Plane);
			Math::fvec3 Coords[4] = { hs, hs, hs, hs, };
		 
			for(unsigned j = 0; j < 4; ++j) {
				for(unsigned k = 0; k < 2; ++k) {
					Coords[j][psrc[k]] *= Planes::VertexOrder(j)[k];
				}
				Coords[j][psrc[2]] = hs[psrc[2]] - srcSlice.CenterPoint[psrc[2]];
			}

			m_EdgesMesh.push_back_mesh(VertexVec.size(), IndexVector.size(), 8, GL_LINE_STRIP);
			for(unsigned i = 0; i < 4; ++i) {
				IndexVector.push_back(i);
				VertexVec.push_back(Coords[i]);
			}
			IndexVector.push_back(0);
		}

		if(m_Slices.size() > 1)
		for(unsigned k = i+1; k < j; ++k) {
			auto &dstSlice = m_Slices[k];
			if(dstSlice.Hide) continue;

			if(srcSlice.Plane == dstSlice.Plane)
				continue;//we are gracaful for parallel slices

			Math::fvec3 Vertexes[2] = {
				hs, -hs,
			}; 

			auto &psrc = Planes::PlanesCoords(srcSlice.Plane);
			auto &pdst = Planes::PlanesCoords(dstSlice.Plane);

			for(unsigned v = 0; v < 2; ++v)  {
				Vertexes[v][pdst[2]] = (hs[pdst[2]] - (float)dstSlice.CenterPoint[pdst[2]]);
				Vertexes[v][psrc[2]] = (hs[psrc[2]] - (float)srcSlice.CenterPoint[psrc[2]]);
			}

			m_EdgesMesh.push_back_mesh(VertexVec.size(), IndexVector.size(), 2, GL_LINES);

			for(unsigned i = 0; i < 2; ++i) {
				IndexVector.push_back(i);
				VertexVec.push_back(Vertexes[i]);
			}
		}
	}
}

void CubeLayer::RecreateEdgesMesh() {
	std::vector<Math::fvec3> VertexVec;
	std::vector<unsigned> IndexVector;

	m_EdgesVAO.New();
	m_EdgesMesh.clear();

	Math::fvec3 hs = Math::fvec3(m_CubeSize) / 2.0f;
	float &hx = hs[0];
	float &hy = hs[1];
	float &hz = hs[2];
	if(m_RenderCubeEdges) {
		float phx = hx;
		float phy = hy;
		float phz = hz;

		const Math::fvec3 Vertexes[8] = {
			Math::fvec3( -hx,  -hy,  -hz),
			Math::fvec3( phx,  -hy,  -hz),
			Math::fvec3( phx,  phy,  -hz),
			Math::fvec3( -hx,  phy,  -hz),

			Math::fvec3( -hx,  -hy,  phz),
			Math::fvec3( phx,  -hy,  phz),
			Math::fvec3( phx,  phy,  phz),
			Math::fvec3( -hx,  phy,  phz),
		};
		for(int i = 0; i < 8; ++i)
			VertexVec.push_back(Vertexes[i]);

		unsigned Indexes[] = {
			0, 1, 
			1, 2,
			2, 3,
			3, 0,

			4, 5,
			5, 6,
			6, 7,
			7, 4,
		
			0, 4,
			1, 5,
			2, 6,
			3, 7,
		};
		unsigned count = sizeof(Indexes) / sizeof(__int32);
		for(unsigned i = 0; i < count; ++i)
			IndexVector.push_back(Indexes[i]);
	}
	m_EdgesMesh.push_back_mesh(0, 0, IndexVector.size(), GL_LINES);

	if(m_RenderInternalEdges && m_Mode == CubeLayerMode::Planes3) {
		CreateEdgesSliceMesh(VertexVec, IndexVector);
	}

	unsigned ch;
	m_EdgesVAO.AddDataChannel<3, float>(&VertexVec[0][0], VertexVec.size(), ch);
	m_EdgesVAO.WriteIndexes(&IndexVector[0], IndexVector.size());
	
	m_EdgesVAO.UnBind();
}

void CubeLayer::SetSourceCube(const std::vector<Color::RGB> &input, const Math::uvec3 &size) {
	m_CubeSize = size;

	unsigned byteSize = sizeof(input[0]) * input.size();

	auto mem = GetOwner()->AllocateMemory(this, D3TEX_RES_NAME, byteSize);
	mem->PushData(&input[0], byteSize, 0);

	SetMode(CubeLayerMode::Planes3);
}
