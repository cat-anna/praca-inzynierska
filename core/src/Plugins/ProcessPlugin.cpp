/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/ProcessPlugin.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

void ProcessPlugin::SetOutputName(const std::wstring &Name) {
	m_OutputName = Name;
}

const std::wstring& ProcessPlugin::GetOutputName() const {
	return m_OutputName;
}

PluginType ProcessPlugin::GetPluginClassType() {
	return PluginType::Process;
}

ProcessPlugin::ProcessPlugin():
		PluginBase(GetPluginClassType()) {
}

ProcessPlugin::~ProcessPlugin() {
}

void ProcessPlugin::SetDataSource(const std::wstring &ProjectName, const std::wstring &SeriesName, const std::wstring &ChannelName) {
	m_BasicDataSource.Set(ProjectName, SeriesName, ChannelName);
}

Interface::StringDataPointer& ProcessPlugin::AccessDataSource() {
	return m_BasicDataSource;
}

const Interface::StringDataPointer& ProcessPlugin::GetDataSource() const {
	return m_BasicDataSource;
}

void ProcessPlugin::OnExecute() {
	PluginBase::OnExecute();
	 
	GetExec()->AddStatelessRequirement([this] () -> bool {
		try {
			auto ptr = m_BasicDataSource.Translate();
			if(!ptr.IsReady()) return false;
			return true;
		} catch (...) { }
		return false;	
	});
}

} //namespace Plugins 
} //namespace VisApp 
