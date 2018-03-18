/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/CubeMapper.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#pragma unmanaged 

using namespace VisApp::Plugins;
using namespace VisApp::Interface;

#include <VisApp\include\Tools\Planes.h>
#include <VisApp\include\Tools\Color.h>

using namespace VisApp::Tools;

class CubeMapper : public ProcessPlugin {
public:
	CubeMapper();
	virtual ~CubeMapper();

	CLIGuiHandler* GetCLIGuiHandler();
protected:
	virtual void BeforeRun();
	virtual void AfterRun();
	virtual void Run();
	virtual void OnExecute();
	virtual void StoreRuntimeConfig(xml_node out) const;
	virtual void LoadRuntimeConfig(const xml_node in);
private:
	std::auto_ptr<CLIGuiHandler> m_GuiHandler;
};

class CubeMapperDescriptor : public RunnablePluginDescriptorWrapper<ProcessPluginDescriptor, CubeMapper> {
public:
	CubeMapperDescriptor(): BaseClass() {
		SetName(L"Cube inspector data generator");
		SetDescription(L"Generates data for inspector layer");
		AddTypeFilter(VisApp::Types::DataType::D1Integer());
		AddDataSourceRequirement([] (const DataPointer *data) {
			Math::uvec3 size;
			data->Series->GetSize(size);
			return size.z > 1;
		});
		AddDataSourceRequirement([] (const DataPointer *data) {
			Math::uvec3 size;
			length_t s = size[0] * size[1] * size[2];
			return s < 300 * 1024 * 1024;//<300MB
		});
	}
};
