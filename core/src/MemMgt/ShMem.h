/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/ShMem.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace Core {
namespace Memory {

template <class T>
class ShMem : public ShMemoryBase<T> {
public:
	ShMem(): ShMemoryBase<T>(){}
	ShMem(boost::shared_ptr<MemPointer> MemPtr): ShMemoryBase<T>(MemPtr) { }	

	ShMem<T>& write(const T* data, size_t bytesize) {
		//TODO: add checks
		memcpy(m_Mem->GetMemory(), data, bytesize);
		return *this;
	}

	ShMem<T>& copy(T* data, size_t bytesize) const {
		//TODO: add checks
		memcpy(data, m_Mem->GetMemory(), bytesize);
		return *this;
	}
private:
};

} //namespace Memory 
} //namespace Core 
