/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginInterface.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

typedef std::vector<std::shared_ptr<PluginDescriptor>> DescriptorList;

struct PluginInterfaceImpl {
	DescriptorList DescriptorList;
	std::wstring Name, Description, License, AuthorName, InfoText;
	PluginVersion Version;

	PluginInterfaceImpl(): 
			Name(L"?"), 
			Description(L"?"),
			License(L""), 
			AuthorName(L""), 
			InfoText(L"") {
	}
};

PluginInterface::PluginInterface(): m_Impl(new PluginInterfaceImpl()) {
	SetVersion();
	AddLog(Debug, "Created plugin interface " << this);
}

PluginInterface::~PluginInterface() {
	AddLog(Debug, "Deleted plugin interface " << this);
}

const std::wstring& PluginInterface::GetName() const {
	return m_Impl->Name;
}

const PluginVersion& PluginInterface::GetVersion() const {
	return m_Impl->Version;
}

unsigned PluginInterface::GetPluginCount() const {
	return m_Impl->DescriptorList.size();
}

const std::weak_ptr<PluginDescriptor> PluginInterface::GetPlugin(unsigned index) const {
	if(index >= m_Impl->DescriptorList.size()) return std::weak_ptr<PluginDescriptor>();
	return m_Impl->DescriptorList.at(index);
}

void PluginInterface::OnLoad() {
	for(auto &desc: m_Impl->DescriptorList)
		desc->RegisterDescriptor();
}

void PluginInterface::OnRelease() {
	for(auto &desc: m_Impl->DescriptorList)
		desc->UnregisterDescriptor();
}

void PluginInterface::RegisterDescriptor(std::shared_ptr<PluginDescriptor> desc) {
	m_Impl->DescriptorList.push_back(desc);
	desc->m_WeakThis = desc;
	desc->m_Owner = this;
}

void PluginInterface::RegisterDescriptor(PluginDescriptor *desc) {
	RegisterDescriptor(std::shared_ptr<PluginDescriptor>(desc));
}

void PluginInterface::SetName(const std::wstring &value) {
	m_Impl->Name = value;
}

void PluginInterface::SetDescription(const std::wstring &value) {
	m_Impl->Description = value;
}

void PluginInterface::SetLicense(const std::wstring &license) {
	m_Impl->License = license;
}

void PluginInterface::SetAuthorName(const std::wstring &name) {
	m_Impl->AuthorName = name;
}

void PluginInterface::SetAboutText(const std::wstring &text) {
	m_Impl->InfoText = text;
}

const std::wstring& PluginInterface::GetLicense() const {
	return m_Impl->License;
}

const std::wstring& PluginInterface::GetAuthorName() const {
	return m_Impl->AuthorName;
}

const std::wstring& PluginInterface::GetAboutText() const {
	return m_Impl->InfoText;
}

void PluginInterface::SetVersion(__int8 Major, __int8 Minor, __int16 Release, bool IsDebug, const char *BuildDate) {
	auto &ver = m_Impl->Version;
	ver.Major = Major;
	ver.Minor = Minor;
	ver.IsDebugBuild = IsDebug;
	ver.Release = Release;
	ver.BuildDate = ((BuildDate)?(BuildDate):("?"));
}

}// namespace Plugins
}// namespace VisApp
