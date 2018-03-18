/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Executable.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

Executable::Executable(): m_Progress(0) {
	m_ReqList.reset(new RequirementList());
}

Executable::~Executable() {
	//nothing here
}

void Executable::BeforeRun() {
	//nothing here
}

void Executable::AfterRun() {
	//nothing here
}

void Executable::Run() {
	//nothing here
}

void Executable::SetProgress(float value) {
	m_Progress = value;
}

float Executable::GetProgress() const {
	return m_Progress;
}

const std::wstring& Executable::GetName() const {
	return m_Name;
}

void Executable::SetName(const std::wstring &Name) {
	VisApp::OS::SetThreadName(Name);
	m_Name = Name;
}

WorkerStatus Executable::GetStatus() const {
	if(m_Instance.expired()) return WorkerStatus::NoInstance;
	return m_Instance.lock()->GetStatus();
}

void Executable::CheckInstance() {
	if(m_Instance.expired()) throw ExitProcessException();
	try {
		return m_Instance.lock()->CheckProcess();
	}
	catch (...) {
		throw ExitProcessException();
	}
}

void Executable::Execute(WeakInstance instance) {
	if(instance.expired()) {
		//TODO: make some error;
		return;
	}

	//TODO: test req

	m_Instance = instance;
	auto inst = m_Instance.lock();
	
	try {
		BeforeRun();
		Run();
		//TODO: measue execution time?
	}
#define _notify(HOW) { AddLog(Error, "Catched throwed message: '" << HOW << "'"); VisApp::Impl::CoreManager::Instance()->NotifyGUI(VisApp::CoreMessageClass::Error) << L"Process zakoñczy³ swoje dzia³aniez b³êdem: " << HOW; }
	catch(const std::wstring m) {
		_notify(m)
	}
	catch(const std::string m) {
		_notify(m.c_str())
	}
	catch(const char* m) {
		_notify(m)
	}
	catch(const wchar_t* m) {
		_notify(m)
	}
	catch(const std::exception &e) {
		_notify(e.what())
	}
	catch(...) {
		_notify("Catched unknown exception!")
	}

	try {
		AfterRun();
	}
	catch(const std::wstring m) {
		_notify(m)
	}
	catch(const std::string m) {
		_notify(m.c_str())
	}
	catch(const char* m) {
		_notify(m)
	}
	catch(const wchar_t* m) {
		_notify(m)
	}
	catch(const std::exception &e) {
		_notify(e.what())
	}
	catch(...) {
		_notify("Catched unknown exception!")
	}
#undef _notify
}

void Executable::AddRequirement(RequirementTestFun ReqFun) {
	m_ReqList->AddLambdaRequirement([this, ReqFun]() { return ReqFun(this); });
}

void Executable::AddStatelessRequirement(StatelessRequirementTestFun ReqFun) {
	m_ReqList->AddLambdaRequirement(ReqFun);
}

unsigned Executable::CheckRequirements() const {
	return m_ReqList->PerformTests();
}

} //namespace Mgt 
} //namespace Worker 

