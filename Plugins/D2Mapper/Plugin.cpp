/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/Plugin.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"

#include "Processor.h"
#include "IsolineGenerator.h"
#include "ColorMapper.h"
#include "MapperLayer.h"

#pragma unmanaged

using namespace VisApp::Plugins;

class PluginIterfaceImpl : public PluginInterface {
public:
	PluginIterfaceImpl() {
		SetName(L"D2Mapper");
		SetDescription(L"Wtyczka zawiera podstawowe procesory 2d");
		SetVersion(1, 0, 1);
		SetAuthorName(L"Pawe³ Grabas");
		SetLicense(L"");
		SetAboutText(L"");
	
		RegisterDescriptor(new IsolineGeneratorDescriptor());
		RegisterDescriptor(new ColorMapperDescriptor());
		RegisterDescriptor(new MapperLayerDescriptor());
	}
};

DECLARE_PLUGIN_INTERFACE(PluginIterfaceImpl)
