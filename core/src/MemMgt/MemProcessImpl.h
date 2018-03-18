/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemProcessImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemProcessImpl_H
#define MemProcessImpl_H

namespace Core {
namespace Memory {

//For shared objects virtuality is forbidden!
class MemProcessImpl {
public:
 	MemProcessImpl(shmpid pid);
 	~MemProcessImpl();

	Shared::OS::PID_t GetSysPid() const { return m_SysPid; }
	shmpid GetPid() const { return m_pid; }
	const MemortStatusInfo &GetStatusinfo() const {  return m_StatusInfo; }

	void EnumerateAllocatedObjects(boost::function<void(MemObjectImpl*)> fun);
	boost::shared_ptr<MemPointer> BindMemObject(offset_ptr<MemObjectImpl> object);
	void ReleaseMemObject(offset_ptr<MemObjectImpl> object);
	void CancellProcess();
	bool IsWorking() const { return m_IsWorking; };

	void NotifyPointerDestruction(shmobjid id);

	bool IsBroken() const;
private: 
	const shmpid m_pid;
	const Shared::OS::PID_t m_SysPid;
	bool volatile m_IsWorking;
	MemortStatusInfo m_StatusInfo;
	boost::posix_time::ptime m_timestap;
	
	mutex_type m_lock;
	
	//these functions assume, that mutex is allready locked!!!
	void InternalMemRelease(offset_ptr<MemObjectImpl> object, bool Force = false);
	boost::shared_ptr<MemPointer> InternalMemBind(offset_ptr<MemObjectImpl> object);

	struct Action {
		enum class Types {
			BindObject,
			ReleaseObject,
			AbortMemProcessImpl,
		};

		Types Type;
		shmobjid ObjId;
	};

	struct MemSegment {
		offset_ptr<MemObjectImpl> MemObjPointer;
		Types::InterprocAtomic<unsigned> Flags;
	//!!!Internal use only. Valid only from owner process!
		SharedMemoryManager *Manager; 
		boost::weak_ptr<MemPointer> Pointer;
		MemSegment(): Manager(0) {};
	};

	typedef std::pair<const shmobjid, MemSegment> SharedObjectListPair;
	typedef allocator<SharedObjectListPair, SharedMemoryManager::segment_manager> SharedObjectListAllocator;
	typedef boost::interprocess::map<shmobjid, MemSegment, std::less<shmobjid>, SharedObjectListAllocator> SharedObjectList;
	
	typedef allocator<Action, SharedMemoryManager::segment_manager> ActionListAllocator;
	typedef boost::interprocess::list<Action, ActionListAllocator> ActionList;
	
	SharedObjectList m_AllocatedObjects;
	ActionList m_ActionList;

	void ThreadMain();

	void UpdateStatus();
	void QuerryProcMemInfoStatus();

	MemProcessImpl &operator=(const MemProcessImpl &);
//	MemProcessImpl(const MemProcessImpl &);
};

} //namespace Memory 
} //namespace Core 

#endif
