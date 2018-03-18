/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginDescriptor.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

PluginDescriptor::PluginDescriptor(PluginType type): m_type(type) {
	//nothing here
}

PluginDescriptor::~PluginDescriptor() {
	//nothing here
}

const std::wstring& PluginDescriptor::GetName() const {
	return m_Name;
}

const std::wstring& PluginDescriptor::GetDescription() const {
	return m_Description;
}

PluginType PluginDescriptor::GetPluginType() const {
	return m_type;
}

void PluginDescriptor::SetName(const std::wstring& value) {
	m_Name = value;
}

void PluginDescriptor::SetDescription(const std::wstring& value) {
	m_Description = value;
}

PluginInterface* PluginDescriptor::GetOwnerInterface() {
	return m_Owner;
}

void PluginDescriptor::RegisterDescriptor() {
}

void PluginDescriptor::UnregisterDescriptor() {
}

}// namespace Plugins
}// namespace VisApp
