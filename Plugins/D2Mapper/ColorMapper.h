/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/ColorMapper.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#pragma unmanaged 

using namespace VisApp::Plugins;
using namespace VisApp::Interface;

typedef std::vector<Color::RGB> RGBvec;
typedef std::function<void(RGBvec &tex)> TexGenFunc;

class ColorMapper : public Processor {
public:
	ColorMapper();
	virtual ~ColorMapper();
protected:
	virtual void Run();
	virtual void StoreRuntimeConfig(xml_node out) const { }
	virtual void LoadRuntimeConfig(const xml_node in) { }

	TexGenFunc DispatchD1();
	TexGenFunc DispatchD2();
	TexGenFunc DispatchD3();
private:
};

class ColorMapperDescriptor : public RunnablePluginDescriptorWrapper<ProcessPluginDescriptor, ColorMapper> {
public:
	ColorMapperDescriptor(): BaseClass() {
		SetName(L"Generator map wartoœci");
		SetDescription(L"Wtyczka s³u¿y do generowania map 2d przedsatwiaj¹cych dany parametr za pomoc¹ koloru");
//		AddTypeFilter(VisApp::Types::DataType::D1Integer());
		AddDataSourceRequirement([] (const DataPointer *data) {
			Math::uvec3 size;
			data->Series->GetSize(size);
			return size.z == 1;
		});
	}
};
