/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/ColorMapper.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "Processor.h"
#include "ColorMapper.h"
#include "MapperLayer.h"
#pragma unmanaged
using namespace VisApp::Types;

ColorMapper::ColorMapper() {
	m_Config.Mode = OutMode::Map;
	m_Config.Normalization = NormalizeMode::DirectValue;
}

ColorMapper::~ColorMapper() {
}

typedef Accessor::Getter<float_t, index_t> Float1Getter;
typedef Accessor::Getter<fvec2, index_t> Float2Getter;
typedef Accessor::Getter<fvec3, index_t> Float3Getter;

typedef Accessor::Getter<int_t, index_t> Int1Getter;


template <class GETTER, class ColorTransform>
struct ColorGen {
	ConfigData *data;
	GETTER getter;
	ColorTransform func;

	std::vector<Color::RGB> *TextureMap;
	//GETTER::OutType_t>

	ColorGen() {
	}

	void work() {
		long long linear = data->OutputSize();
		TextureMap->resize(linear);

		for(long long i = 0; i < linear; ++i) {
			//auto v = getter(i);
			(*TextureMap)[i] = func(getter(i));

			if((i & 0xFF) == 0 && data->UpdateFun)
				data->UpdateFun((float)i, (float)linear);
		}
	}
};

TexGenFunc ColorMapper::DispatchD1() {
	switch (m_Config.SrcDataType.Type) {
	case VariableType::Integer:
		return [this] (RGBvec &tex) {
			ColorGen<Int1Getter, Color::RGB::ColorFunc> gen;
			gen.data = &m_Config;
			gen.getter.SetSource(m_Config);
			gen.func = &Color::RGB::RandomColor_v2;
			gen.TextureMap = &tex;
			gen.work();
		};
	case VariableType::Float:
		return [this] (RGBvec &tex) {
			ColorGen<Float1Getter, Color::RGB::ColorFuncf1> gen;
			gen.data = &m_Config;
			gen.getter.SetSource(m_Config);
			gen.func = &Color::RGB::GrayScaleColor_f1;
			gen.TextureMap = &tex;
			gen.work();
		};
	}
	return [] (RGBvec &tex) { AddLog(ThrowError, "fatal error!"); };
}

TexGenFunc ColorMapper::DispatchD2() {
	switch (m_Config.SrcDataType.Type) {
	case VariableType::Float:
		return [this] (RGBvec &tex) {
			ColorGen<Float2Getter, Color::RGB::ColorFuncf2> gen;
			gen.data = &m_Config;
			gen.getter.SetSource(m_Config);
			gen.func = &Color::RGB::DirectColor_f2v;
			gen.TextureMap = &tex;
			gen.work();
		};
	}
	return [] (RGBvec &tex) { AddLog(ThrowError, "fatal error!"); };
}

TexGenFunc ColorMapper::DispatchD3() {
	switch (m_Config.SrcDataType.Type) {
	case VariableType::Float:
		return [this] (RGBvec &tex) {
			ColorGen<Float3Getter, Color::RGB::ColorFuncf3> gen;
			gen.data = &m_Config;
			gen.getter.SetSource(m_Config);
			gen.func = &Color::RGB::DirectColor_f3v;
			gen.TextureMap = &tex;
			gen.work();
		};
	}
	return [] (RGBvec &tex) { AddLog(ThrowError, "fatal error!"); };
}

void ColorMapper::Run() {
	Processor::Run();
	std::vector<Color::RGB> tex;

	TexGenFunc fun;

	switch (m_Config.SrcDataType.Dimiension) {
	case DataDimiension::d1:
		fun = DispatchD1();
		break;
	case DataDimiension::d2:
		fun = DispatchD2();
		break;
	case DataDimiension::d3:
		fun = DispatchD3();
		break;
	}

	fun(tex);

	auto layerclass = m_Config.SrcDataPtr.Project->GetDataStore()->CreateLayer(this, GetOutputName(), MapperLayer::GetClassName());
	auto layer = dynamic_cast<MapperLayer*>(layerclass.get());
	layerclass->AddDataSoure(m_Config.SrcDataPtr.Channel);
	layer->SetSourceBits(tex, Math::uvec2(m_Config.InputDataSize), Math::uvec2(m_Config.OutputDataSize));
}
