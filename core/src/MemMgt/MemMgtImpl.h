/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemMgtImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemMgtImpl_H
#define MemMgtImpl_H

namespace Core {
namespace Memory {

//wywaliæ do nowej dll'ki
	
//For shared objects virtuality is forbidden!
class MemMgtImpl {
	friend class MemMgt;
public:	
	~MemMgtImpl();
	MemMgtImpl();
	static void AttachProcess();
	static void DetachProcess();

	static VoidAllocator &GetAllocator() { return *_MemAllocator; }
	static MemMgtImpl* Instance();
	static MemProcessImpl* GetThisProc() { return _ThisProc; }
	static shmpid GetOwnerPid() { return _Instance->m_OwnerPid; }

	static void LogStatus();
	static void OwnerThreadNotification(unsigned &tick);

	static void LogShMemSegmentActivity(const SharedCharType * action, const SharedCharType* name, size_t size, MemType type);

	offset_ptr<MemObjectImpl> GetMemObject(shmobjid id);//throws MemoryObjectDoesNotExists;

	void EnumerateProcesses(boost::function<void(MemProcessImpl *proc)> fun);
	void EnumerateMemoryObjects(boost::function<void(MemObjectImpl *obj)> fun);

	void NotifyObjectRelease(offset_ptr<MemObjectImpl> obj); //allways arrives from current proc

	void ValidateInstance();//throws error if instance had to be destroyed
private: 
	boost::shared_ptr<MemPointer> CreatePointer(size_t size, const std::wstring &Name, MemObjectType Type, MemLifeTime LifeTime, unsigned Settings);
	boost::shared_ptr<MemPointer> OpenPointer(const std::wstring &Name, unsigned Settings);

	offset_ptr<MemObjectImpl> AllocateMemory(size_t size, const std::wstring &Name, MemObjectType type, MemLifeTime LifeTime, unsigned Settings);
	bool DeallocateMemory(offset_ptr<MemObjectImpl> obj);

	Types::InterprocAtomic<shmpid> m_shPidCounter;
	Types::InterprocAtomic<shmobjid> m_shObjCounter;

	SharedMemProcessImplMap m_Processes;
	MemoryObjectMap m_Objects;
	shmpid m_OwnerPid;
	InterprocessString m_Identiffier;
	boost::posix_time::ptime m_LastIntegrityCheck;

	recursive_mutex_type m_lock;

	void InitLocalInstance(bool WasConstructed);
	void FinLocalInstance();
	void GenInternalName(const std::wstring &data, InterprocessString & out);

	template <class T> T *Allocate() { return static_cast<T*>(_Memory->allocate(sizeof(T))); }
	template <class T> void Deallocate(T* ptr) { if(!ptr) return; ptr->~T(); _Memory->deallocate(ptr); }

	static MemMgtImpl *_Instance;
	static MemProcessImpl *_ThisProc;
	static SharedMemoryManager *_Memory;	
	static VoidAllocator *_MemAllocator;

	static void InitalizeAllocator();
};

} //namespace Memory 
} //namespace Core 

#endif
