/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/IsolineGenerator.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef IsolineGenerator_H
#define IsolineGenerator_H

#pragma unmanaged 

using namespace VisApp::Plugins;
using namespace VisApp::Interface;

class IsolineGenerator : public Processor {
public:
 	IsolineGenerator();
 	virtual ~IsolineGenerator();
protected:
	virtual void Run();
	virtual void StoreRuntimeConfig(xml_node out) const { }
	virtual void LoadRuntimeConfig(const xml_node in) { }
private: 
};

class IsolineGeneratorDescriptor : public RunnablePluginDescriptorWrapper<ProcessPluginDescriptor, IsolineGenerator> {
public:
	IsolineGeneratorDescriptor(): BaseClass() {
		SetName(L"Generator izolini");
		SetDescription(L"Wtyczka s³u¿y do generowania izolini 2d");
	//	AddTypeFilter(VisApp::Types::DataType::D1Integer());
		AddDataSourceRequirement([] (const DataPointer *data) {
			VisApp::Math::uvec3 size;
			data->Series->GetSize(size);
			return size.z == 1;
		});
	}
};

#endif
