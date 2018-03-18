/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemProcess.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\CoreShared.h"
#include "MemHdr.h"

namespace Core {
namespace Memory {

MemProcess::MemProcess(MemProcessImpl *Impl): m_Impl(Impl) {
}

MemProcess::~MemProcess() {
}

Shared::OS::PID_t MemProcess::GetSysPid() {
	return m_Impl->GetSysPid();
}

shmpid MemProcess::GetPid() const {
	return m_Impl->GetPid();
}

const MemortStatusInfo &MemProcess::GetStatusinfo() const {
	return m_Impl->GetStatusinfo();
}

void MemProcess::EnumerateAllocatedObjects(boost::function<void(MemObject)> fun) {
	m_Impl->EnumerateAllocatedObjects([fun](MemObjectImpl* obj) { fun(static_cast<MemObject>(obj)); });
}  

bool MemProcess::IsWorking() const {
	return m_Impl->IsWorking();
}


} //namespace Memory 
} //namespace Core 

