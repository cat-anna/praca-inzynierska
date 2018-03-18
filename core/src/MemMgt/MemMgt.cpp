/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemMgt.cpp
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

void MemMgt::AttachProcess() {
	MemMgtImpl::AttachProcess();
}

void MemMgt::DetachProcess() {
	MemMgtImpl::DetachProcess();
}

MemProcess MemMgt::GetThisProc() {
	return static_cast<MemProcess>(MemMgtImpl::GetThisProc());
}

void MemMgt::EnumerateProcesses(boost::function<void(MemProcess proc)> fun) {
	MemMgtImpl::Instance()->EnumerateProcesses([fun](MemProcessImpl* obj) { fun(static_cast<MemProcess>(obj)); });
}
	
void MemMgt::EnumerateMemoryObjects(boost::function<void(MemObject obj)> fun) {
	MemMgtImpl::Instance()->EnumerateMemoryObjects([fun](MemObjectImpl* obj) { fun(static_cast<MemObject>(obj)); });
}

boost::shared_ptr<MemPointer> MemMgt::CreatePointer(size_t size, const std::wstring &Name, MemObjectType Type, MemLifeTime LifeTime, unsigned Settings) {
	return MemMgtImpl::Instance()->CreatePointer(size, Name, Type, LifeTime, Settings);
}

boost::shared_ptr<MemPointer> MemMgt::OpenPointer(const std::wstring &Name, unsigned Settings) {
	return MemMgtImpl::Instance()->OpenPointer(Name, Settings);
}

} //namespace Memory 
} //namespace Core 
