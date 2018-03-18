/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/nMemMgt.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace Core {
namespace Memory {
	class MemObject;
	class MemObjectImpl;
	class MemProcess;
	class MemProcessImpl;

	using boost::interprocess::offset_ptr;
	using boost::interprocess::allocator;

	typedef boost::interprocess::managed_shared_memory SharedMemoryManager;

	typedef allocator<void, SharedMemoryManager::segment_manager> VoidAllocator;

	typedef allocator<char, SharedMemoryManager::segment_manager> CharAllocator;
	typedef allocator<wchar_t, SharedMemoryManager::segment_manager> WCharAllocator;
	typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> InterprocessString;
	typedef boost::interprocess::basic_string<wchar_t, std::char_traits<wchar_t>, WCharAllocator> InterprocessWString;

	typedef unsigned shmpid;
	typedef unsigned shmobjid;

	struct MemortStatusInfo {
		size_t AllocatedSize;
		size_t AllocatedSegmentsCount;
		size_t RemainVirtualMemorySize;
		size_t VirtualMemorySize;
	};

	enum class MemLifeTime {
		Application,
		Pointer,
		Permanent,
	};

	enum class MemObjectType : unsigned {
		Unknown, Table, Raw,
	};

	enum class MemType : unsigned {
		Unknown, Manager, Segment, IPCQueue,
	};

	struct MemoryObjectDoesNotExists {};
}
}

#include "MemPointer.h"
#include "ShMemoryBase.h"
#include "ShMem.h"
#include "ShTab.h"

#include "MemMgt.h"
#include "MemProcess.h"
#include "MemObject.h"
