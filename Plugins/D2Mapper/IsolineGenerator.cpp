/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/IsolineGenerator.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "Processor.h"
#include "IsolineGenerator.h"

#pragma unmanaged

namespace Math = VisApp::Math;
namespace Types = VisApp::Types;
namespace Renderer = VisApp::Renderer;

struct IsolinesPusher {
	std::map<index_t, index_t> IndexMapper;
	ConfigData *config;
	Renderer::LayerConstructor *output;

	IsolinesPusher() {
		NewCoords.reserve(5000);
		Line.reserve(5);
	}

	void operator() (std::vector<Math::uvec2> &LineVector) {
		NewCoords.clear();
		Line.clear();
		for(auto &coord: LineVector) {
			unsigned linear = config->OutputPos(coord);
			auto it = IndexMapper.find(linear);
			unsigned index;
			if(it == IndexMapper.end()) {
				Math::fvec3 vec(coord[0], coord[1], 0);
				vec -= config->PositionDelta;
				NewCoords.push_back(vec);
				index = IndexMapper.size();
				IndexMapper.insert(std::make_pair(linear, index));
			} else {
				index = it->second;
			}
			Line.push_back(index);
			if(Line.size() == 2) {
				output->PushMeshIndexes(Line, GL_LINES);
				Line.clear();
			}
		}
		if(!NewCoords.empty())
			output->PushVertexes(NewCoords);

		LineVector.clear();
	}

private:
	std::vector<Math::fvec3> NewCoords;
	std::vector<unsigned> Line;
};

template <class PUSHER, class GETTER>
struct TemplateIsolinesGenerator {
	ConfigData *config;

	typedef GETTER getter_t;
	typedef PUSHER pusher_t;

	getter_t getter;
	pusher_t PushLines;

	void generate() {
		std::vector<Math::uvec2> LineVector;

		bool InLine = false;
		uvec2 pos;

		unsigned global_max = config->OutputDataSize[0]-1 + config->OutputDataSize[1]-1;
		unsigned global_pos = 0;

		for(pos[0] = 0; pos[0] < config->OutputDataSize[0]-1; ++pos[0]) {
			InLine = false;
			uvec2 pos2 = pos;
			pos2[0] += 1;
			for(pos[1] = 0; pos[1] < config->OutputDataSize[1]; ++pos[1]) {
				pos2[1] = pos[1];
				bool NeedLine = false;// pos[1] == 0 || pos[1]+1 == config->OutputDataSize[1];
			//	if(!NeedLine) {
				int_t current[2] = { getter(pos), getter(pos2) };
				NeedLine = current[0] != current[1];
			//	}

				if(InLine == NeedLine) continue;
				LineVector.push_back(pos2);
				InLine = NeedLine;
			}
			if(InLine) {
				pos2[1] = config->OutputDataSize[1];
				LineVector.push_back(pos2);
			}
			PushLines(LineVector);
			++global_pos;
			if(!(global_pos & 0x7F))
				config->UpdateFun(global_pos, global_max);
		}

		for(pos[1] = 0; pos[1] < config->OutputDataSize[1]-1; ++pos[1]) {
			InLine = false;
			uvec2 pos2 = pos;
			pos2[1] += 1;
			for(pos[0] = 0; pos[0] < config->OutputDataSize[0]; ++pos[0]) {
				pos2[0] = pos[0];
				bool NeedLine = false;// pos[0] == 0 || pos[0]+1 == config->OutputDataSize[0];
			//	if(!NeedLine) {
				int_t current[2] = { getter(pos), getter(pos2) };
				NeedLine = current[0] != current[1];
			//	}

				if(InLine == NeedLine) continue;
				LineVector.push_back(pos2);
				InLine = NeedLine;
			}
			if(InLine) {
		//		if(pos2[0] > 10)
					pos2[0] = config->OutputDataSize[0]-1;
				LineVector.push_back(pos2);
			}
			PushLines(LineVector);
			++global_pos;
			if(!(global_pos & 0x7F))
				config->UpdateFun(global_pos, global_max);
		}
		auto hs = config->OutputDataSize;
		hs[0] -= 1; hs[1] -= 1;
		LineVector.clear();
		LineVector.push_back(uvec2(0, 0));
		LineVector.push_back(uvec2(0, hs[1]));

		LineVector.push_back(uvec2(0, 0));
		LineVector.push_back(uvec2(hs[0], 0));

		LineVector.push_back(uvec2(hs));
		LineVector.push_back(uvec2(hs[0], 0));

		LineVector.push_back(uvec2(hs));
		LineVector.push_back(uvec2(0, hs[1]));

		PushLines(LineVector);
	}
};

typedef TemplateIsolinesGenerator<IsolinesPusher, Accessor::Getter<int_t, Math::uvec2>> IsolineGeneratorObject;

//------------------------------------------------------------------------

IsolineGenerator::IsolineGenerator() {
	m_Config.Subdivs = 1;
	m_Config.Mode = OutMode::Isolines;
	m_Config.Normalization = NormalizeMode::DirectValue;
}

IsolineGenerator::~IsolineGenerator() {
}


typedef std::vector<Math::fvec2> Vec2Vector;
typedef std::vector<Math::fvec3> Vec3Vector;
/*
bool operator < (const Math::uvec2 &p1, const Math::uvec2 &p2) {
	return p1[0] < p2[0] && p1[1] < p2[1];
}

struct uvec2_less {	
	bool operator()(const Math::uvec2 &p1, const Math::uvec2 &p2) const
	{	
		return p1[0] < p2[0] && p1[1] < p2[1];
	}
};
*/
/*
void GenerateSimpleIsolines(const fvec3 &PositionDelta, const Math::uvec3 &MeshSize, Renderer::LayerConstructor* output,  int* Src, unsigned flags) {
	unsigned LinearMeshSize = MeshSize[0] * MeshSize[1];

	std::map<unsigned, unsigned> IndexMapper;
	std::vector<Math::uvec2> LineVector;

	auto PushLines = [&IndexMapper, &LineVector, output, &MeshSize, &PositionDelta] () {
		Vec3Vector NewCoords;
		std::vector<unsigned __int32> Line;
		Line.reserve(2);

		for(auto &coord: LineVector) {
			unsigned linear = coord[0] + coord[1] * MeshSize[0];
			auto it = IndexMapper.find(linear);
			unsigned index;
			if(it == IndexMapper.end()) {
				Math::fvec3 vec(coord[0], coord[1], 0);
				vec -= PositionDelta;
				NewCoords.push_back(vec);
				index = IndexMapper.size();
				IndexMapper.insert(std::make_pair(linear, index));
			} else {
				index = it->second;
			}
			Line.push_back(index);
			if(Line.size() == 2) {
				output->PushMeshIndexes(Line, GL_LINES);
				Line.clear();
			}
		}
		if(!NewCoords.empty())
			output->PushVertexes(NewCoords);
		LineVector.clear();
	};

	auto get = [Src, &MeshSize] (index_t x, index_t y) {
		return Src[x + y * MeshSize[0]];
	};

	auto push = [&LineVector] (index_t x, index_t y) {
		LineVector.push_back(Math::uvec2(x, y));
	};
	
	bool InLine = false;

	for(index_t x = 0; x < MeshSize[0]-1; ++x) {
		InLine = false;
		for(index_t y = 0; y < MeshSize[1]; ++y) {
			int current[2] = { get(x, y), get(x+1, y) };
			bool NeedLine = current[0] != current[1];

			if(InLine == NeedLine) continue;
			push(x+1, y);
			InLine = NeedLine;
		}
		PushLines();
	}

	for(index_t y = 0; y < MeshSize[1]-1; ++y) {
		InLine = false;
		for(index_t x = 0; x < MeshSize[0]; ++x) {
			int current[2] = { get(x, y), get(x, y+1) };
			bool NeedLine = current[0] != current[1];

			if(InLine == NeedLine) continue;
			push(x, y+1);
			InLine = NeedLine;
		}
		PushLines();
	}
}
*/
void IsolineGenerator::Run() {
	Processor::Run();

	if(m_Config.Subdivs == 1) {
	} else {
		MakeError("Subdivs > 1 is not supported!");
		return;
	}

	auto layer = m_Config.SrcDataPtr.Project->GetDataStore()->CreateInternalLayer(this, GetOutputName());
	auto constructor = layer->GetLayerConstructor();
	if(!constructor) {
		//sth bad has happen
		throw false;
	}
	layer->AddDataSoure(m_Config.SrcDataPtr.Channel);

	IsolineGeneratorObject gen;
	gen.config = &m_Config;
	gen.PushLines.config = &m_Config;
	gen.PushLines.output = constructor;
	gen.getter.SetSource(m_Config);

	gen.generate();

	//GenerateSimpleIsolines(m_Config.PositionDelta, MeshSize, constructor, SourceData, 0);

	constructor->SetLayerType(VisApp::Renderer::LayerType::d2);
	constructor->Done();
}
