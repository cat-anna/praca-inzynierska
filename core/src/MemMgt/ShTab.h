/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/ShTab.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace Core {
namespace Memory {

template <class T>
class ShTab : public ShMemoryBase<T> {
public:
	typedef ShTab<T> ThisClass;

	ShTab(): ShMemoryBase<T>(), m_Count() { }	
	ShTab(boost::shared_ptr<MemPointer> MemPtr, size_t count): ShMemoryBase<T>(MemPtr), m_Count(count) { }	
	ShTab(boost::shared_ptr<MemPointer> MemPtr): ShMemoryBase<T>(MemPtr), m_Count() {
		m_Count = size() / sizeof(T);//!!!!! owful workaround
	}	

	T& operator[] (size_t index) { 
		if(index >= m_Count)
			throw std::out_of_range("ShTab out of range!");
		return ((T*)m_Mem->GetMemory())[index];
	}

	const T& operator[] (size_t index) const { 
		if(index >= m_Count)
			throw std::out_of_range("ShTab out of range!");
		return ((const T*)m_Mem->GetMemory())[index];
	}

	T* unsafe_at(size_t index) {  return ((T*)m_Mem->GetMemory()) + index; }
	const T* unsafe_at(size_t index) const {  return ((T*)m_Mem->GetMemory()) + index; }

	ThisClass& write(const T* table, size_t Count) {
		memcpy(**this, table, Count * sizeof(T));
		return *this;
	}

	ThisClass& writeAll(const T* table) {
		write(table, m_Count);
		return *this;
	}

	size_t count() const { return m_Count; }
private:
	size_t m_Count;
};

} //namespace Memory 
} //namespace Core 
