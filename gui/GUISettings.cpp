/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/GUISettings.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "GUISettings.h"

namespace VisApp {
namespace gui {

//-----------------------------------------------------------

Settings *Settings::_Instance;

Settings& Settings::Instance() {
	if(!_Instance) {
		_Instance = new Settings();
	}
	return *_Instance;
}

Settings::Settings() {
	m_DataLoaded = false;
}

Settings::~Settings() {
//	if(GetSettingsAutoSave())
//		Save();
}

void Settings::DoSave() {
	Instance().Save();
}

void Settings::DoLoad() {
	Instance().Load();
}

void Settings::Load() {
	xml_document doc;
	doc.load_file(L"AppSettings.xml");

	xml_node root = doc.document_element();

	CurrentRegister::LoadSettings(root);

	m_DataLoaded = true;
}

void Settings::Save() {
	xml_document doc;

	xml_node root = doc.append_child(L"ApplicationSettings");
	CurrentRegister::StoreSettings(root);

	doc.save_file(L"AppSettings.xml");
}

} //namespace gui 
} //namespace VisApp 

