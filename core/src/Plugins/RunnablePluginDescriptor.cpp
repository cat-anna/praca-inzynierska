/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/RunnablePluginDescriptor.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

RunnablePluginDescriptor::RunnablePluginDescriptor(PluginType type): PluginDescriptor(type) {
	//nothing here
}

SharedPluginBase RunnablePluginDescriptor::InitPlugin(PluginBase* p) const {
	p->m_Descriptor = GetWeakSelf();
	p->m_Name = GetName();
	SharedPluginBase sp(p);
	p->m_WeakThis = WeakPluginBase(sp);
	return sp;
}

//---------------------------------------------------------------------------------

ImportPluginDescriptor::ImportPluginDescriptor(PluginType type) : RunnablePluginDescriptor(PluginType::Import) {
	if(type != PluginType::Import)
		throw "Wrong plugin import class type!";
}

ImportPluginDescriptor::~ImportPluginDescriptor() {
}

const std::vector<std::wstring>& ImportPluginDescriptor::GetExtFilter() const {
	return m_ExtFilter;
}

void ImportPluginDescriptor::AddExtFilter(const wchar_t *Filter) {
	m_ExtFilter.push_back(Filter);
}

//---------------------------------------------------------------------------------

ProcessPluginDescriptor::ProcessPluginDescriptor(PluginType type) : RunnablePluginDescriptor(PluginType::Process) {
	if(type != PluginType::Process)
		throw "Wrong plugin process class type!";
}

ProcessPluginDescriptor::~ProcessPluginDescriptor() {
}

bool ProcessPluginDescriptor::TestDataSource(Interface::DataPointer* src) const {
	if(!src || !src->IsOk()) return false;
	if(!m_TypeFilter.Test(src->Channel->GetType())) return false;
	for(auto &it: m_RequirementList)
		if(!it || !it(src))
			return false;
	return true;
}

void ProcessPluginDescriptor::AddDataSourceRequirement(SourceCondition c) {
	m_RequirementList.push_back(c);
}

void ProcessPluginDescriptor::AddTypeFilter(const VisApp::Types::DataType &type) {
	m_TypeFilter.AddFilter(type);
}

void ProcessPluginDescriptor::SetLayerClass(const std::wstring& Name) {
	LOG_NOT_IMPLEMENTED
}


}// namespace Plugins
}// namespace VisApp
