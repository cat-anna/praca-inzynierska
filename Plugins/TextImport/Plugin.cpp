/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/Plugin.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "TextImport.h"

#pragma unmanaged

using namespace VisApp::Plugins;

class TextImportDescriptor : public RunnablePluginDescriptorWrapper<ImportPluginDescriptor, TextImportPlugin> {
public:
	TextImportDescriptor(): BaseClass() {
		SetName(L"Text file importer");
		SetDescription(L"Allows to import data files stored in regular text files");
		AddExtFilter(L"*.txt");
	}
};

class PluginIterfaceImpl : public PluginInterface {
public:
	PluginIterfaceImpl() {
		SetName(L"TextImport");
		SetDescription(L"Plugin contains regular text file importer");
		SetVersion(0, 1, 0);
	
		RegisterDescriptor(new TextImportDescriptor());
	}
};

DECLARE_PLUGIN_INTERFACE(PluginIterfaceImpl)
