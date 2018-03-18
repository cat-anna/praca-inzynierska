/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginBase.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

PluginBase::PluginBase(PluginType pt): 
		m_Type(pt), 
		m_Executed(false) {
	AddLog(Debug, "Constructing PluginBase " << this);
}

PluginBase::~PluginBase() {
	AddLog(Debug, "Destroying PluginBase " << this);
}

void PluginBase::SetObserver(ObserverPtr observer) {
	m_Observer = observer;
}

ExecuteResult PluginBase::Execute() {
	if(m_Executed) return ExecuteResult();
	auto res = PluginManagerImpl::GetInstance()->ExecutePlugin(m_WeakThis.lock(), GetExec());
	if(!res.expired()) {
		m_Executed = true;
		this->OnExecute();
	}
	return res;
}

void PluginBase::BeforeRun() { }
void PluginBase::AfterRun() { }
void PluginBase::Run() { }
void PluginBase::OnExecute() { }
void PluginBase::StoreRuntimeConfig(xml_node out) const { }
void PluginBase::LoadRuntimeConfig(const xml_node out) { }

bool PluginBase::IsExecuted() const {
	return m_Executed;
}

void PluginBase::CheckInstance() {
	m_ExecPtr->CheckInstance();
}

SharedPluginExec PluginBase::GetExec() {
	if(m_Exec.expired()) {
		SharedPluginExec exc(new PluginExec(m_WeakThis.lock()));
		m_ExecPtr = exc.get();
		m_Exec = WeakPluginExec(exc);
		return exc;
	}
	return m_Exec.lock();
}

CLIGuiHandler* PluginBase::GetCLIGuiHandler() {
	return 0;
}

const std::wstring& PluginBase::GetName() const {
	return m_Descriptor.lock()->GetName();
}

PluginObserver& PluginBase::GetObserver() {
	return *m_Observer.get();
}

PluginType PluginBase::GetType() const {
	return m_Type;
}

void PluginBase::MakeError(const char* Message) {
	AddLog(Error, Message);
	
	throw Message;
}

PluginSettings PluginBase::GetGlobalSettings() {
	return PluginManagerImpl::GetInstance()->QuerryPluginSettings(this);
}

const PluginSettings PluginBase::GetGlobalSettings() const {
	return PluginManagerImpl::GetInstance()->QuerryPluginSettings(const_cast<PluginBase*>(this));
}

WeakPluginBase PluginBase::GetWeakSelfPointer() {
	return m_WeakThis;
}

WeakPluginDescriptor PluginBase::GetDescriptor() {
	return m_Descriptor;
}

}// namespace Plugins
}// namespace VisApp
