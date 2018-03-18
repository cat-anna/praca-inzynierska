/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemPointer.cpp
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

MemPointer::MemPointer(MemObjectImpl* Owner, void* Memory):
	m_Owner(Owner),
	m_Memory(Memory) {
}

MemPointer::~MemPointer() {
	MemMgtImpl::GetThisProc()->NotifyPointerDestruction(m_Owner->GetID());
}

size_t MemPointer::GetSize() const { 
	return m_Owner->GetSize();
}

const InterprocessString& MemPointer::GetInternalName() const { 
	return m_Owner->GetName(); 
}

} //namespace Memory 
} //namespace Core 
