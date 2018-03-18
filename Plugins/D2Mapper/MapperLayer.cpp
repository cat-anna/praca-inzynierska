/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/MapperLayer.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "Stdafx.h"
#include "MapperLayer.h"
//#include "ConfigForm.h"

#pragma unmanaged

#include "FragmentShader.h"
#include "VertexShader.h"

#define MapperLayer_RES_NAME L"PlaneTexture"

MapperLayer::MapperLayer(const std::wstring& Name): Renderer::LayerInterface(Name) {
	SetLayerType(Renderer::LayerType::d2);
	m_InvertColor = false;
	m_InputMode = InputColorMode::RGB;
	m_OutputMode = OutputColorMode::RGB;
}

MapperLayer::~MapperLayer() {
}

//-------------

void MapperLayer::DoRender(Renderer::GraphicDevice &dev) const {
	m_Texture.Bind();

	//TODO: set texturing mode

	m_PlaneVAO.RenderMesh(m_PlaneMesh);

/*	glUniform3uiv(m_CubeSizeLocation, 1, &m_CubeSize[0]);

	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	if(m_RenderInternalEdges || m_RenderCubeEdges) { 
		float black[3] = { }; 
		glUniform3fv(m_BaseColorLocation, 1, black);
		m_EdgesVAO.RenderMesh(m_EdgesMesh);
	} */
} 

MapperLayer::Error MapperLayer::Initialize(Renderer::GraphicDevice &dev) {
	auto shader = 
		dev.GetShaderMgt().GetShader(L"MapperLayerBasicShader", 
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
//	shader->SetVAOChannel("", 0);
//	shader->SetVAOChannel("", 1);
//	m_CubeSizeLocation = shader->CustomLocation("CubeSize");
//	m_BaseColorLocation = shader->CustomLocation("BaseColor"); 
	   
	auto mem = GetOwner()->OpenMemory(this, MapperLayer_RES_NAME);
	if(mem) {
		Renderer::Texture::ActivateChannel(0);
		switch (m_InputMode) {
		case InputColorMode::RGB:
			m_Texture.SetTextureBits(mem->Get(), m_TexSize, GL_RGB, GL_UNSIGNED_BYTE);
			break;

/*		case InputColorMode::Norm1:
			break;*/
		/*case InputColorMode::Norm2:
			break;*/
	/*	case InputColorMode::Norm3:
			break;*/
		default:
			break;
		}
		m_Texture.SetClampToEdges();
		m_Texture.SetNearestFiltering();
	} 
	RegenMesh();
	return Error::NoError; 
}
 
MapperLayer::Error MapperLayer::Finalize(Renderer::GraphicDevice &dev) {
	m_Texture.Free();
	m_PlaneVAO.Free();
	return Error::NoError;
}

Renderer::LayerCLIGUIHandler* MapperLayer::QuerryCLIGuiHandler() const {
/*	if(!m_GuiHandler) {
		if(_GuiHandlerInstance.expired()) {
			m_GuiHandler.reset(new CubeSlicer::CubeLayerGuiHandler((CubeLayer*)this));
			_GuiHandlerInstance = m_GuiHandler;
		} else {
			m_GuiHandler = _GuiHandlerInstance.lock();
		}
	}
	return m_GuiHandler.get();*/
	return 0;
}

MapperLayer::Error MapperLayer::Load(const xml_node src) {
	LayerInterface::Load(src);

	auto SizeNode = src.child(L"PlaneSize");
	m_PlaneSize[0] = SizeNode.child(L"PlaneWidth").text().as_uint();
	m_PlaneSize[1] = SizeNode.child(L"PlaneHeight").text().as_uint();
	m_TexSize[0] = SizeNode.child(L"TexWidth").text().as_uint();
	m_TexSize[1] = SizeNode.child(L"TexHeight").text().as_uint();

	auto SettingsNode = src.child(L"Config");
	m_InvertColor = SettingsNode.child(L"InvertColor").text().as_bool(false);
	m_InputMode = (InputColorMode)SettingsNode.child(L"InputMode").text().as_uint(0);
	m_OutputMode = (OutputColorMode)SettingsNode.child(L"OutputMode").text().as_uint(0);

	return Error::NoError;
}

MapperLayer::Error MapperLayer::Save(xml_node dst) const {
	LayerInterface::Save(dst);

	auto SizeNode = dst.append_child(L"PlaneSize");
	SizeNode.append_child(L"PlaneWidth").text() = m_PlaneSize[0];
	SizeNode.append_child(L"PlaneHeight").text() = m_PlaneSize[1];
	SizeNode.append_child(L"TexWidth").text() = m_TexSize[0];
	SizeNode.append_child(L"TexHeight").text() = m_TexSize[1];

	auto SettingsNode = dst.append_child(L"Config");
	SettingsNode.append_child(L"OutputMode").text() = (unsigned)m_OutputMode;
	SettingsNode.append_child(L"InputMode").text() = (unsigned)m_InputMode;
	SettingsNode.append_child(L"InvertColor").text() = m_InvertColor;

	return Error::NoError;
}
 
//--------------

void MapperLayer::RegenMesh() {
	m_PlaneVAO.New();
	unsigned ch;

	float_t hX = m_PlaneSize[0] / 2.0f;
	float_t hY = m_PlaneSize[1] / 2.0f;

	const Math::fvec3 Coords[] = {
		Math::fvec3(-hX, -hY, 0),
		Math::fvec3( hX, -hY, 0),
		Math::fvec3( hX,  hY, 0),
		Math::fvec3(-hX,  hY, 0),
	};
	m_PlaneVAO.AddDataChannel<3, float>(&Coords[0][0], 4, ch);

	const Math::fvec2 UVWs[] = {
		Math::fvec2(0, 0),
		Math::fvec2(1, 0),
		Math::fvec2(1, 1),
		Math::fvec2(0, 1),
	};
	m_PlaneVAO.AddDataChannel<2, float>(&UVWs[0][0], 4, ch);
	
	const unsigned Index[] = {
		0, 1, 2, 3,
	};
	m_PlaneVAO.WriteIndexes(Index, 4);
	m_PlaneVAO.UnBind();
	m_PlaneMesh.clear();
	m_PlaneMesh.push_back_mesh(0, 0, 4, GL_QUADS);
}

void MapperLayer::SetSourceBits(const std::vector<Color::RGB> &input, const Math::uvec2 &size, const Math::uvec2 &InputSize) {
	m_PlaneSize = size;
	m_TexSize = InputSize;
	m_InputMode = InputColorMode::RGB;
	m_OutputMode = OutputColorMode::RGB;
	SetSize(Math::fvec3(m_PlaneSize, 0));

	unsigned byteSize = sizeof(input[0]) * input.size();
	auto mem = GetOwner()->AllocateMemory(this, MapperLayer_RES_NAME, byteSize);
	mem->PushData(&input[0], byteSize, 0);
}