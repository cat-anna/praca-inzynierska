/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/Project.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "../Implementation.h"

#include <boost\filesystem.hpp>

namespace VisApp {
namespace Project {

typedef Interface::iProject::Error Error;

Project::Project(const std::wstring &Location, const std::wstring &Name): 
		m_Name(Name),
		m_Location(Location),
		m_DataStore() {
	m_DataStore.reset(new DataStore(this));
}

Project::Project(const std::wstring &File): 
		m_Name(L"?"),
		m_Location(L""),
		m_DataStore() {
	m_DataStore.reset(new DataStore(this));

	boost::filesystem::path f(File);
	m_Location = f.parent_path().generic_wstring();

	Impl::CoreManager::Instance()->AddAction([this, File] {
		DoLoadProject(File);
	});
}

Project::~Project() {
}

bool Project::CanBeSaved() const {
	return !m_Location.empty();
}

//iProject implementation

bool Project::IsVirtual() const {
	return !CanBeSaved();
}

Project::Error Project::SetLocation(const std::wstring &folder) {
	m_Location = folder;
	SaveProject();
	return Error::NoError;
}

Project::Error Project::SetName(const std::wstring &name) {
	m_Name = name;
	SaveProject();
	return Error::NoError;
}

const std::wstring& Project::GetLocation() const {
	return m_Location;
}

const std::wstring &Project::GetName() const {
	return m_Name;
}

Interface::iDataStore* Project::GetDataStore() const {
	return m_DataStore.get();
}

void Project::SaveProject() {
	if(!CanBeSaved()) return;
	AddLog(Hint, "Saving project " << GetName())
	Impl::CoreManager::Instance()->AddAction([this] {
		DoSaveProject(SaveMode::Deep);
	});
}

void Project::DoSaveProject(SaveMode Mode) {
	if(!CanBeSaved()) return;
	AddLog(Debug, "Saving project " << GetName())

	if(!m_ProjDoc) {
		m_ProjDoc.reset(new xml_document());
	} 
	xml_document &doc = *m_ProjDoc.get();
	
	xml_node ProjNode =  UniqeChild(doc, L"Project");

	xml_node Settings = UniqeChild(ProjNode, L"Settings");
	UniqeChild(Settings, L"Name").text() = m_Name.c_str();

	xml_node DataStore = UniqeChild(ProjNode, L"DataStore");
	if(!m_DataStore->SaveMeta(DataStore, Mode)) {
		return ;//Error::FatalError;
	}

	std::wstringstream wss;
	wss << m_Location << L"\\" << GetName() << L".vap";

	boost::filesystem::create_directories(m_Location);
	m_ProjFile = wss.str();
	if(!doc.save_file(m_ProjFile.c_str())) {
		return ;//Error::FatalError;
	}
}

void Project::DoLoadProject(const std::wstring &File) {
	AddLog(Hint, "Loading project from file " << File);


	m_ProjDoc = std::shared_ptr<xml_document>(new xml_document());
	xml_document &doc = *m_ProjDoc.get();
	doc.load_file(File.c_str());
	m_ProjFile = File;

	try {
		xml_node ProjNode = doc.child(L"Project");

		xml_node Settings = ProjNode.child(L"Settings");
		m_Name = Settings.child(L"Name").text().as_string(0);

		xml_node DataStore = ProjNode.child(L"DataStore");
		if(!m_DataStore->LoadMeta(DataStore)) {
			throw false;
		}

		auto cmgr = Impl::CoreManager::Instance();
		cmgr->NotifyGUI(CoreNotification::ProjectChanged);
		cmgr->NotifyGUI(CoreNotification::SeriesChanged);
		cmgr->NotifyGUI(CoreNotification::LayersChanged);
	}
	catch(...) {
	}
}

} //namespace Project
} //namespace VisApp
