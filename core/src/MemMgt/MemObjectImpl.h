/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemObjectImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemObjectImpl_H
#define MemObjectImpl_H

namespace Core {
namespace Memory {

//virtuality is forbidden!

class MemObjectImpl {
public:
	~MemObjectImpl();
	MemObjectImpl(shmobjid id, size_t size, const InterprocessString &Name, MemObjectType type, MemLifeTime LifeTime);

	const InterprocessString &GetName() const { return m_Name; }
	size_t GetSize() const { return m_Size; }
	shmobjid GetID() const { return m_ID; }
	unsigned GetAllocationCount() const { return static_cast<unsigned>(m_BindCounter); }
	MemLifeTime GetLifeTime() const { return m_LifeTime; }

	void NotifyProcessBind(offset_ptr<MemProcessImpl> process);
	void NotifyProcessRelease(offset_ptr<MemProcessImpl> process);
private:
	boost::interprocess::interprocess_mutex m_lock;
	Types::InterprocAtomic<unsigned> m_BindCounter;

	shmobjid m_ID;
	InterprocessString m_Name;
	size_t m_Size;
	MemObjectType m_Type;
	MemLifeTime m_LifeTime;
};

} //namespace Memory 
} //namespace Core 

#endif
