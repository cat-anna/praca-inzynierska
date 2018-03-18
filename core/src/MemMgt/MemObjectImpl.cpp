/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemObjectImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\CoreShared.h"
#include "MemHdr.h"

namespace Core {
namespace Memory {

MemObjectImpl::MemObjectImpl(shmobjid id, size_t size, const InterprocessString &Name, MemObjectType Type, MemLifeTime LifeTime):
		m_BindCounter(0),
		m_ID(id),
		m_Name(Name.c_str(), MemMgtImpl::GetAllocator()),
		m_Size(size),
		m_Type(Type),
		m_LifeTime(LifeTime) {
}

MemObjectImpl::~MemObjectImpl() {
}

void MemObjectImpl::NotifyProcessBind(offset_ptr<MemProcessImpl> process) {
	m_BindCounter.Add(1);
}

void MemObjectImpl::NotifyProcessRelease(offset_ptr<MemProcessImpl> process) {
	m_BindCounter.Add(-1);
}

} //namespace Memory 
} //namespace Core 
