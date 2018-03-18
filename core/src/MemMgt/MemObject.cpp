/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemObject.cpp
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


MemObject::MemObject(MemObjectImpl *Impl): m_Impl(Impl) {
}

MemObject::~MemObject() {
}

const InterprocessString &MemObject::GetName() const {
	return m_Impl->GetName();
}

size_t MemObject::GetSize() const {
	return m_Impl->GetSize();
}

shmobjid MemObject::GetID() const {
	return m_Impl->GetID();
}

unsigned MemObject::GetAllocationCount() const {
	return m_Impl->GetAllocationCount();
}

} //namespace Memory 
} //namespace Core 

