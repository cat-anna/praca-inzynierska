/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemObject.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemObject_H
#define MemObject_H

namespace Core {
namespace Memory {

class CORESHARED_API MemObject {
public:
 	MemObject(MemObjectImpl *Impl);
 	~MemObject();

	const InterprocessString &GetName() const;
	size_t GetSize() const;
	shmobjid GetID() const;
	unsigned GetAllocationCount() const;
private: 
	MemObjectImpl *m_Impl;
};

} //namespace Memory 
} //namespace Core 

#endif
