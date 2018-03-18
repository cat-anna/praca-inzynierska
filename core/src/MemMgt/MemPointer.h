/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemPointer.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemPointer_H
#define MemPointer_H

namespace Core {
namespace Memory {

class CORESHARED_API MemPointer {
public:
 	MemPointer(MemObjectImpl* Owner, void* Memory);
	~MemPointer();

	size_t GetSize() const;
	const InterprocessString& GetInternalName() const;

	void *GetMemory() const { return m_Memory; }
private: 
	MemObjectImpl *m_Owner;
	void* m_Memory;

	MemPointer(const MemPointer&);
	MemPointer& operator=(const MemPointer&);
};

} //namespace Memory 
} //namespace Core 

#endif
