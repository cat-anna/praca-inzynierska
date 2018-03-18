/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/ShMemoryBase.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace Core {
namespace Memory {

template <class T>
class ShMemoryBase {
public:
	typedef T type_t;

	size_t size() const { return m_Mem->GetSize(); }
	const char* GetInternalName() const { return m_Mem->GetName().c_str(); }
	boost::weak_ptr<MemPointer> GetPointer() { return static_cast<weak_ptr<MemPointer>>(m_Mem); }

	void Release() { m_Mem = boost::shared_ptr<MemPointer>(0); }

	operator bool () const { return static_cast<bool>(m_Mem); }
	bool operator ! () const { return !static_cast<bool>(m_Mem); }
	bool operator == (const ShMemoryBase<T> & oth) const { return m_Mem == oth.m_Mem; }

	T* operator*() { return (T*)m_Mem->GetMemory(); }
	operator T*() { return (T*)m_Mem->GetMemory(); }

	const T* operator*() const { return (const T*)m_Mem->GetMemory(); }
	operator const T*() { return (const T*)m_Mem->GetMemory(); }
protected:
	ShMemoryBase(): m_Mem() { }	
	ShMemoryBase(boost::shared_ptr<MemPointer> MemPtr): m_Mem(MemPtr) { }	
	ShMemoryBase(const ShMemoryBase<T> &other): m_Mem(other.m_Mem) { }	

	boost::shared_ptr<MemPointer> m_Mem;
};

} //namespace Memory 
} //namespace Core 
