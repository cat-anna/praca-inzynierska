/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemHdr.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

//Secret memory manager header

#include "..\Types\SynchronizedList.h"
#include "..\Types\InterprocessAtomic.h"

/*
	debug levels:
		0 - disabled
		1 - yelds object creation
		2 - enables Segment flow logs
		3 - yelds each mutex lock and unlock
*/
#define MEMMGT_DEBUG_LEVEL 1

//---

#if MEMMGT_DEBUG_LEVEL >= 1
#define MGMMGT_DEBUG_LOG_SEGM_CREATION
#endif

#if MEMMGT_DEBUG_LEVEL >= 2
#define MGMMGT_DEBUG_LOG_SEGM_FLOW
#endif

#if MEMMGT_DEBUG_LEVEL >= 3
#define MGMMGT_DEBUG_LOG_SEGM_FLOW
#define MEMMGT_DEBUG_LOG_EACH_MUTEX_LOCK
#endif


namespace Core {
namespace Memory {
	class MemMgt;
	class MemPointer;

	typedef char SharedCharType;

	typedef Types::SynchronizedList<shmpid> ProcessPidList;

	typedef std::pair<const shmpid, offset_ptr<MemProcessImpl>> SharedMemProcessImplMapPair;
	typedef allocator<SharedMemProcessImplMapPair, SharedMemoryManager::segment_manager> SharedMemProcessImplMapAllocator;
	typedef boost::interprocess::map<shmpid, offset_ptr<MemProcessImpl>, std::less<shmpid>, SharedMemProcessImplMapAllocator> SharedMemProcessImplMap;

	typedef std::pair<const InterprocessString, offset_ptr<MemObjectImpl>> MemoryObjectMapPair;
	typedef allocator<MemoryObjectMapPair, SharedMemoryManager::segment_manager> MemoryObjectMapAllocator;
	typedef boost::interprocess::map<InterprocessString, offset_ptr<MemObjectImpl>, std::less<InterprocessString>, MemoryObjectMapAllocator> MemoryObjectMap;

	typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> scoped_lock_type;
	typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_recursive_mutex> recursive_scoped_lock_type;

#ifdef MEMMGT_DEBUG_LOG_EACH_MUTEX_LOCK

	template <class MUTEX>
	class LinedMutex : public MUTEX {
	public:
		unsigned Line;
	};

	template <unsigned LINE, class MUTEX, class LOCK>
	class scoped_lined_lock : public LOCK {
	public:
		typedef MUTEX mutex_type;
		scoped_lined_lock(mutex_type &mutex): LOCK(mutex) {
			mutex.Line = LINE;
			LOG << LogType::Hint << "Locing mutex at line " << LINE;
		}

		~scoped_lined_lock() {
			LOG << LogType::Hint << "Unlocking mutex at line " << LINE;
		}
	};
	
	typedef LinedMutex<scoped_lock_type::mutex_type> mutex_type;
	typedef LinedMutex<recursive_scoped_lock_type::mutex_type> recursive_mutex_type;
#else
	typedef scoped_lock_type::mutex_type mutex_type;
	typedef recursive_scoped_lock_type::mutex_type recursive_mutex_type;
#endif

#ifdef MEMMGT_DEBUG_LOG_EACH_MUTEX_LOCK
#define scoped_lock scoped_lined_lock<__LINE__, mutex_type, scoped_lock_type>
#define recursive_scoped_lock scoped_lined_lock<__LINE__, recursive_mutex_type, recursive_scoped_lock_type>
#else
	typedef scoped_lock_type scoped_lock;
	typedef recursive_scoped_lock_type recursive_scoped_lock;
#endif
}
}

#include "MemProcessImpl.h"
#include "MemObjectImpl.h"
#include "MemMgtImpl.h"
