/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemMgt.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemMgt_H
#define MemMgt_H

namespace Core {
namespace Memory {

class CORESHARED_API MemMgt {
public:
	template <class T>
	static ShMem<T> CreateMemory(size_t size, const std::wstring &Name, MemLifeTime LifeTime = MemLifeTime::Application) {
		return ShMem<T>(CreatePointer(size, Name, MemObjectType::Raw, LifeTime, 0));
	}

	template <class T>
	static ShTab<T> CreateTable(size_t Count, const std::wstring &Name, MemLifeTime LifeTime = MemLifeTime::Application) {
		return ShTab<T>(CreatePointer(Count * sizeof(T), Name, MemObjectType::Table, LifeTime, 0), Count);
	}

	template <class T>
	static ShMem<T> OpenMemory(const std::wstring &Name) {
		return ShMem<T>(OpenPointer(Name, 0));
	}

	template <class T>
	static ShTab<T> OpenTable(const std::wstring &Name) {
		return ShTab<T>(OpenPointer(Name, 0));
	}

	static void AttachProcess();
	static void DetachProcess();

	static MemProcess GetThisProc();

	static void EnumerateMemoryObjects(boost::function<void(MemObject obj)> fun);
	static void EnumerateProcesses(boost::function<void(MemProcess proc)> fun);
private: 
	static boost::shared_ptr<MemPointer> CreatePointer(size_t size, const std::wstring &Name, MemObjectType Type, MemLifeTime LifeTime, unsigned Settings);
	static boost::shared_ptr<MemPointer> OpenPointer(const std::wstring &Name, unsigned Settings);

	MemMgt();
 	~MemMgt();
	MemMgt(const MemMgt&);
	MemMgt& operator=(const MemMgt&);
};

} //namespace Memory 
} //namespace Core 

#endif

