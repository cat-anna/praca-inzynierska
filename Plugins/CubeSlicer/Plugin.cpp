/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/Plugin.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"

#include "CubeMapper.h"
#include "CubeLayer.h"

#pragma unmanaged

using namespace VisApp::Plugins;

class PluginIterfaceImpl : public PluginInterface {
public:
	PluginIterfaceImpl() {
		SetName(L"Cube microstructure viewer");
		SetDescription(L"Plugin allows to inspect cube sample miscrostructure");
		SetVersion(1, 0, 1);
		SetAuthorName(L"Pawe³ Grabas");
		SetLicense(L"");
		SetAboutText(L""); 

		RegisterDescriptor(new CubeMapperDescriptor());
		RegisterDescriptor(new CubeLayerDescriptor());
	}
};

DECLARE_PLUGIN_INTERFACE(PluginIterfaceImpl)
