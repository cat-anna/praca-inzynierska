/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/CubeMapper.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "CubeMapper.h"
#include "CubeLayer.h"

#pragma unmanaged

#define Math VisApp::Math

using Color::RGB;

CubeMapper::CubeMapper() {
}

CubeMapper::~CubeMapper() {
}

void CubeMapper::BeforeRun() {
	ProcessPlugin::BeforeRun();
}

void CubeMapper::AfterRun() {
	ProcessPlugin::AfterRun();
}

void CubeMapper::StoreRuntimeConfig(xml_node out) const {
	ProcessPlugin::StoreRuntimeConfig(out);
}

void CubeMapper::LoadRuntimeConfig(const xml_node in) {
	ProcessPlugin::LoadRuntimeConfig(in);
}

CLIGuiHandler* CubeMapper::GetCLIGuiHandler() {
	/*if(!m_GuiHandler.get())
		m_GuiHandler.reset(new gui::D3PlanesSliceGuiHandler(this));
	return m_GuiHandler.get();*/
	return 0;
}

using namespace Planes;

void CubeMapper::Run() {
	ProcessPlugin::Run();

	auto DataSrc = GetDataSource().Translate();
	if(!DataSrc.IsReady()) {
		MakeError("ród³o danych nie jest gotowe!");
		//TODO: make some 
		return;
	}

	Math::uvec3 size;
	DataSrc.Channel->GetSize(size);
	unsigned LinearSize = size[0] * size[1] * size[2];

	typedef std::vector<RGB> RGBVector;
	typedef std::map<int_t, RGB> RGBIntMap;
	typedef std::vector<Math::fvec2> Vec2Vector;
	typedef std::vector<Math::fvec3> Vec3Vector;

	auto Data = DataSrc.Channel->GetMemory<Types::VariableType::Integer, Types::DataDimiension::d1>();

	RGBIntMap ColorMap;

	auto ColorFunc = &RGB::RandomColor_v2;

	std::vector<Color::RGB> TexVector;
	TexVector.resize(LinearSize);

	Math::uvec3 Pos;
	for(index_t x = 0; x < size[0]; ++x) {
		Pos[0] = x;
		for(index_t y = 0; y < size[1]; ++y) {
			Pos[1] = y;
			for(index_t z = 0; z < size[2]; ++z) {
				Pos[2] = z;

				unsigned l = Pos[0] + (Pos[1] + Pos[2] * size[1]) * size[0];
				auto elem = Data.at(Pos)[0];
				TexVector[l] = Color::RGB::RandomColor_v2(static_cast<__int16>(elem));
			}
		}
	}

	auto layerclass = DataSrc.Project->GetDataStore()->CreateLayer(this, GetOutputName(), CubeLayer::GetClassName());
	auto layer = dynamic_cast<CubeLayer*>(layerclass.get());
	layer->AddDataSoure(DataSrc.Channel);
	layer->SetSourceCube(TexVector, size);
}

void CubeMapper::OnExecute() {
	ProcessPlugin::OnExecute();
}

#if 0
	ProcessPlugin::Run();

	auto DataSrc = GetDataSource().Translate();
	if(!DataSrc.IsReady()) {
		MakeError("ród³o danych nie jest gotowe!");
		//TODO: make some 
		return;
	}

	Math::uvec3 size;
	DataSrc.Channel->GetSize(size);

	unsigned LinearSize = size[0] * size[1];

	typedef std::vector<RGB> RGBVector;
	typedef std::map<int_t, RGB> RGBIntMap;
	typedef std::vector<Math::fvec2> Vec2Vector;
	typedef std::vector<Math::fvec3> Vec3Vector;

	RGB::ColorFunc ColorFunc = &RGB::RandomColor_v2;

	auto Data = DataSrc.Channel->GetMemory<Types::VariableType::Integer, Types::DataDimiension::d1>();
	auto layer = DataSrc.Project->GetDataStore()->CreateInternalLayer(this, GetOutputName());
	auto constructor = layer->GetLayerConstructor();
	if(!constructor) {
		//sth bad has happen
		throw false;
	}

	//create coords and uvs
	{
		Vec3Vector Coords;
		Vec2Vector UVs;
		Coords.reserve(4);
		UVs.reserve(4);
		float_t hX = size[0] / 2.0f;
		float_t hY = size[1] / 2.0f;

		Coords.push_back(Math::fvec3(-hX, -hY, 0)); UVs.push_back(Math::fvec2(0, 0));
		Coords.push_back(Math::fvec3( hX, -hY, 0)); UVs.push_back(Math::fvec2(1, 0));
		Coords.push_back(Math::fvec3( hX,  hY, 0)); UVs.push_back(Math::fvec2(1, 1));
		Coords.push_back(Math::fvec3(-hX,  hY, 0)); UVs.push_back(Math::fvec2(0, 1));

		constructor->PushUVMapping(UVs);
		constructor->PushVertexes(Coords);
	}

	RGBIntMap ColorMap;
	RGBVector LayerTexture;

	LayerTexture.resize(LinearSize);

	for(index_t i = 0; i < LinearSize; ++i) {
		auto elem = Data.at(i)[0];

		RGBIntMap::iterator ColIt;
		if((ColIt = ColorMap.find(elem)) == ColorMap.end()) {
			RGB c = ColorFunc(ColorMap.size());
			ColorMap.insert(std::make_pair(elem, c));
			LayerTexture[i] = c;
		} else {
			LayerTexture[i] = ColIt->second;
		}

		if(!(i & 0xF))
			GetExec()->SetProgress(i, LinearSize);
	}

	constructor->SetTextureData(&LayerTexture[0], sizeof(RGB) * LinearSize, Math::uvec2(size), GL_RGB, GL_UNSIGNED_BYTE, 0);
	constructor->SetLayerType(VisApp::Renderer::LayerType::d2);

	//create index
	{
		std::vector<unsigned __int32> Indexes;
		for(int i = 0; i < 4; ++i)
			Indexes.push_back(i);
		constructor->PushMeshIndexes(Indexes, GL_QUADS);
	}

	constructor->Done();
#endif