/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemMgtImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\CoreShared.h"
#include "MemHdr.h"

#include <boost/crc.hpp>



namespace Core {
namespace Memory {

struct KillMemoryManagerException {};

const char SharedMemoryGlobalObjectName[] = "SharedMemoryManager_" BUILD_ARCH;
const char ManagerName[] = "MemoryManagerInstance";

const char CoreMemoryLogFileName[] = "CoreMemory.log";

using namespace boost::interprocess;

MemMgtImpl *MemMgtImpl::_Instance = 0;
MemProcessImpl *MemMgtImpl::_ThisProc = 0;
SharedMemoryManager *MemMgtImpl::_Memory = 0;
VoidAllocator *MemMgtImpl::_MemAllocator = 0;

std::ofstream _MemoryLog;

template <unsigned LEN, class T>
void GenShMemUID(T &out) {
	char rawrandname[LEN * 2 + 1];
	char *ptr = rawrandname;
	for(unsigned i = 0; i < LEN; ++i) {
#pragma warning ( suppress: 4996 )
		sprintf(ptr, "%02x", rand() & 0xFF);
		ptr += 2;
	}
	out = rawrandname;
}

void MemMgtImpl::LogShMemSegmentActivity(const SharedCharType* action, const SharedCharType* name, size_t size, MemType type) {
	SharedCharType buffer[1024];
	sprintf_s(buffer, "<%s Name=\"%s\" Size=\"%d\" Type=\"%d\" />\n", action, name, size, static_cast<unsigned>(type));
	_MemoryLog << buffer << std::flush;
}

template <class TIN, class TOUT>
void DoHash(const TIN *in, TOUT &out) {
	for(const TIN *i = in; *i; ++i) {
		const TOUT high_mask = 0xF0000000;//TODO unsigned may have not be 32 bit integer
		TOUT high = (out & high_mask) >> 28;
		out ^= *i;
		out <<= 2;
		out ^= high;
	}
}

void MemMgtImpl::GenInternalName(const std::wstring &data, InterprocessString & out) {
	boost::crc_32_type result;
    result.process_bytes(data.data(), data.length());
	char buffer[1024];
    std::hash<std::wstring> hash_fn;
  //  std::size_t str_hash = hash_fn(str);
	unsigned chk = hash_fn(data);//result.checksum();
	//DoHash<>(data.c_str(), chk);
	sprintf_s(buffer, "ShMem_" BUILD_ARCH "_%s_%08x", m_Identiffier.c_str(), chk);
    out = buffer;
}

using namespace boost::posix_time;

MemMgtImpl::MemMgtImpl(): 
		m_Processes(std::less<shmpid>(), GetAllocator()), 
		m_Objects(std::less<InterprocessString>(), GetAllocator()), 
		m_Identiffier("", GetAllocator()) {
#pragma warning ( suppress: 4244 )
	srand(time(0));
	m_LastIntegrityCheck = second_clock::local_time();
	GenShMemUID<4>(m_Identiffier);
}

MemMgtImpl::~MemMgtImpl() {
}

void MemMgtImpl::LogStatus() {
//	scoped_lock l(_Instance->m_lock, boost::interprocess::try_to_lock);	
//	if(!l.owns()) return;

	float segmremain = _Memory->get_free_memory() / static_cast<float>(Core::Config::StdDef::KiloByte);
	float alloc = 0;

	for(auto &i: _Instance->m_Objects)
		alloc += i.second->GetSize();
	alloc /= static_cast<float>(Core::Config::StdDef::MegaByte);

	LOG << LogType::Hint << std::setprecision(1) << std::fixed
		<< "Status:"
		<< " Ownwer:" << _Instance->m_OwnerPid
		<< " Objects:" << _Instance->m_Objects.size() 
		<< " Processes:" << _Instance->m_Processes.size() 
		<< " FreeSpace:"  << segmremain << "Kb"
		<< " Allocated:"  << alloc << "Mb";
}

void MemMgtImpl::OwnerThreadNotification(unsigned &tick) {
	if((tick % 50) == 0) {
		_Instance->m_LastIntegrityCheck = second_clock::local_time();				
	}

	if(tick > 100){
		LogStatus();
		tick = 0;
	}
}

void MemMgtImpl::ValidateInstance() {
	enum {
		Mutex_Locked			= 0x0001,
		Mutex_IsOwner			= 0x0002,
		Mutex_FATAL				= Mutex_Locked,


		Process_NoOwner			= 0x0010,
		Process_OwnerNotExist	= 0x0020,
		Process_FATAL			= Process_OwnerNotExist,

	//if instance got one of these flags means that is broken
		Issues_FATAL			= Mutex_FATAL | Process_FATAL,
	};
/*
	auto currtime = second_clock::local_time();
	auto diff = currtime - m_LastIntegrityCheck;
	if(diff.seconds() < 10)
		return;//lasty ingerity check was earlier than 10 secs.

	m_LastIntegrityCheck = currtime;
*/
	unsigned Issues = 0;
	auto CheckIssuesSanity = [&Issues] () {
	//Check if instance failed one of integrity checks
		if(Issues & Issues_FATAL) throw false;
	};
	static const char Failure[] = "ShMem integrity failure: ";
	static const char Warning[] = "ShMem integrity warning: ";
	static const char Repair[]  = "Doing ShMem integrity repair: ";

	try {
//Firstly test mutex. If ownership cannot be obtained its owner process may be broken
		{//Mutex checks
			try {
				if(m_lock.timed_lock(boost::get_system_time() +  boost::posix_time::milliseconds(500)))
					throw false;

				Issues |= Mutex_Locked;//TODO: excange to try_lock!!!
				LOG << LogType::Fatal << Failure << "Mutex is locked!";
			} catch(...) {
				m_lock.unlock();
			}
		}
		CheckIssuesSanity();
//if we are here that means mutex is not locked by broken process
//and it can be used to isolate integrity tests
		recursive_scoped_lock l(m_lock);
		{//Processes checks
			auto proc = m_Processes.find(GetOwnerPid());
			if(proc == m_Processes.end()) {
				Issues |= Process_OwnerNotExist;
				LOG << LogType::Fatal << Failure << "Owner not exists!";
			}
			auto syspid = proc->second->GetSysPid();
			if(!Shared::OS::Process::IsProcessRunning(syspid)) {
				Issues |= Process_NoOwner;
				LOG << LogType::Warning << Warning << "Owner process not exists!";
			}
		}
		CheckIssuesSanity();
//All checks are perforemed
//Process results
		if(Issues == 0) return;

		if(Issues & Process_NoOwner) {
			LOG << LogType::Warning << Repair << "Changing owner to next created process";
			m_OwnerPid = m_shPidCounter;//TODO: decide whether this is a good solution or not
			Issues &= ~Process_NoOwner;
		}
	}
	catch(...) {
		//integrity check failed
		//instance had to be removed
		//TODO: chech if it is nessesary co execute CoreMemFree
		throw false;
	}
//Instance passed integrity checks
}

boost::shared_ptr<MemPointer> MemMgtImpl::CreatePointer(size_t size, const std::wstring &Name, MemObjectType Type, MemLifeTime LifeTime, unsigned Settings) {
	auto obj = AllocateMemory(size, Name, Type, LifeTime, Settings);
	return _ThisProc->BindMemObject(obj);	
}

boost::shared_ptr<MemPointer> MemMgtImpl::OpenPointer(const std::wstring &Name, unsigned Settings) {
	InterprocessString HashName(GetAllocator());
	GenInternalName(Name, HashName);

	auto obj = m_Objects.find(HashName);

	if(obj == m_Objects.end()) throw MemoryObjectDoesNotExists();

	return _ThisProc->BindMemObject(obj->second);
}

offset_ptr<MemObjectImpl> MemMgtImpl::AllocateMemory(size_t size, const std::wstring &Name, MemObjectType type, MemLifeTime LifeTime, unsigned Settings) {
	MemObjectImpl *objptr = 0;

	//eneter protected area
	{
		recursive_scoped_lock l(m_lock);
		size_t segsize = size + static_cast<Config::MemConf_t>(Config::Memory::SharedMemorySegmentDelta);

		InterprocessString HashName(GetAllocator());
		GenInternalName(Name, HashName);
		shmobjid objid;
		
		try {
			SharedMemoryManager mem(create_only, HashName.c_str(), segsize);
			LogShMemSegmentActivity("Create", HashName.c_str(), segsize, MemType::Segment);
			objid = m_shObjCounter.next();
			objptr = new (Allocate<MemObjectImpl>()) MemObjectImpl(objid, size, HashName, type, LifeTime);
			m_Objects.insert(std::make_pair(HashName, static_cast<offset_ptr<MemObjectImpl>>(objptr)));
#ifdef MGMMGT_DEBUG_LOG_SEGM_CREATION
			LOG << "Created memory object: " << HashName.c_str() << "  from name: " << Name;
#endif
		}
		catch (...) {
			LOG << "Attempt to recreate existing memory object: " << HashName.c_str() << "  from name: " << Name;
			auto it = m_Objects.find(HashName);
			if(it == m_Objects.end()) {
				LOG << LogType::Critical << "Attempt to recreate nonexisting memory object. cannot continue.";
				exit(1);
			};
			if(DeallocateMemory(it->second)) {
				LOG << "Existing object was succesfully removed: " << HashName.c_str() << "  from name: " << Name;
				l.unlock();
				return AllocateMemory(size, Name, type, LifeTime, Settings);					
			}
			LOG << "Unable to remove existing object. Connecting to it";
			objptr = it->second.get();
		}
	}
	//leace protected area
	if(!objptr) {
		LOG << LogType::Critical << "Unable to get MemObject pointer!!!";
		exit(1);
	}

	//_ThisProc->BindMemObject(objptr);

	return static_cast<offset_ptr<MemObjectImpl>>(objptr);
}

bool MemMgtImpl::DeallocateMemory(offset_ptr<MemObjectImpl> obj) {
	if(!obj) return true;
	if(obj->GetAllocationCount() > 0) {
		LOG << LogType::Warning << "Cannot deallocate not completyl released mem object: " << obj->GetName().c_str();
		return false;//TODO throw error
	}

	auto it = m_Objects.find(obj->GetName());

	if(it == m_Objects.end()) {
		LOG << LogType::Critical << "Attempt to release existing, but unknown object: " << obj->GetName().c_str();
		return false;
	}

	LogShMemSegmentActivity("Destroy", obj->GetName().c_str(), 0, MemType::Segment);
	if(shared_memory_object::remove(obj->GetName().c_str())) {
#ifdef MGMMGT_DEBUG_LOG_SEGM_FLOW
		LOG << "Object: " << obj->GetName().c_str() << " were removed from system";
#endif
	} else
		LOG << "Unable to remove object: " << obj->GetName().c_str() << " from system";
		
	m_Objects.erase(it);
	Deallocate(obj.get());
	return true;
}

void MemMgtImpl::AttachProcess() {
	if(_Instance) return;
	_MemoryLog.open(CoreMemoryLogFileName, std::ios::app);
	LOG << "Attaching process";
	
	try {
		_Memory = new SharedMemoryManager(open_only, SharedMemoryGlobalObjectName);
		//object exists, conntect to it
		_Instance = _Memory->find<MemMgtImpl>(ManagerName).first;
		if(!_Instance) {
			LOG << LogType::Critical << "Memory manager segment exists, but contains no instance!! Cannot recover!";
			exit(0);
		}
		//TODO: handle this case properly		
		//TODO: check instance integrity
		//runnging corememfree should be enough

		_Instance->ValidateInstance();

		InitalizeAllocator();
		_Instance->InitLocalInstance(false);
		LOG << "MemMgt: attached instance";
	}
	catch(...) {
		//object has to be constructed
		try {
			_Memory = new SharedMemoryManager(create_only, SharedMemoryGlobalObjectName, (Config::MemConf_t)Config::Memory::ManagerMemorySegmentSize);
		
		//TODO: handle failure properly
			LogShMemSegmentActivity("Create", SharedMemoryGlobalObjectName, (unsigned)Config::Memory::ManagerMemorySegmentSize, MemType::Manager);
			InitalizeAllocator();
			_Instance = _Memory->construct<MemMgtImpl>(ManagerName)();
			Logs::LogMgt::PushRawLine(L"---===Constructed new Memory Manager===---");
			_Instance->InitLocalInstance(true);
			LOG << "Created new memory manager instance";	
		}
		catch (...) {
			LOG << "CRITICAL ERROR: UNABLE TO CREATE MANAGER MEMORY SEGMENT!!!";
			exit(1);
		}
	}
}

void MemMgtImpl::DetachProcess() {
	if(!_Instance) return;

	try {
		_Instance->FinLocalInstance();
	}
	catch (KillMemoryManagerException) {
		if(shared_memory_object::remove(SharedMemoryGlobalObjectName)) {
			LogShMemSegmentActivity("Destroy", SharedMemoryGlobalObjectName, 0, MemType::Manager);
			LOG << "Memory manager segment succesfully removed";
		} 
		else
			LOG << "Unable to remove memory manager segment!";
	}

	delete _MemAllocator;
	_MemAllocator = 0;

	delete _Memory;
	_Memory = 0;	

	_Instance = 0;

	_MemoryLog.close();
	LOG << "Detaching process";
}

void MemMgtImpl::InitLocalInstance(bool WasConstructed)  {
	recursive_scoped_lock l(m_lock);
	
	//TODO: What if there is no memory left in segment?
	shmpid pid = m_shPidCounter.fetch_add(1);

	MemProcessImpl *proc = static_cast<MemProcessImpl*>(_Memory->allocate(sizeof(MemProcessImpl)));
	proc = new (proc) MemProcessImpl(pid);

	m_Processes.insert(std::make_pair(pid, offset_ptr<MemProcessImpl>(proc)));
	auto it = m_Processes.find(pid);
	_ThisProc = proc;

	if(WasConstructed) {
		m_OwnerPid = pid;
	}
}

void MemMgtImpl::FinLocalInstance() {
	try {
		{
			recursive_scoped_lock l(m_lock);
			bool exitMmgt = true;
			if(m_Processes.size() > 1 && _ThisProc->GetPid() == m_OwnerPid) {
				//detaching owner of memory manager transfer ownership to another process
				LOG << "Looking for process to transfer ownership";
				MemProcessImpl *proc = 0;
				for(auto &i: m_Processes){
					//do not try to move ownership to itself
					if(i.second->GetPid() == m_OwnerPid) continue;
					//test if proc is broken
					if(i.second->IsBroken()) continue;
					proc = i.second.get();
					break;
				}

				if(!proc) {
					LOG << "FATAL ERROR: CANNOT FIND PROCESS TO TRANSFER OWNERSHIP! Killing memory manager!";
				} else {
					m_OwnerPid = proc->GetPid();
					LOG << "Ownership succesfully transfered";
					m_Processes.erase(_ThisProc->GetPid());
					exitMmgt = false;
				}
			} 

			if(exitMmgt){
				//killing memory manager
				//this a bit complicated situation
				//not every thing can be handled here
				Deallocate(_ThisProc); //kill last process
				//we are in no process currently
				while(m_Objects.size() > 0)
					DeallocateMemory(m_Objects.begin()->second);
				throw KillMemoryManagerException();
			}
		}
		_ThisProc->CancellProcess();
		{
			recursive_scoped_lock l(m_lock);
			Deallocate(_ThisProc);
		}
		_ThisProc = 0;
	} 
	catch(KillMemoryManagerException &e) {
		throw e;//not handled here
	}
	catch(...) {
		LOG << "FATAL ERROR: SOMETHING WENT TERRIBLY WRONG, UNKNOWN ERROR!";
	}
}

void MemMgtImpl::InitalizeAllocator() {
	_MemAllocator = new VoidAllocator(_Memory->get_segment_manager());
}

MemMgtImpl* MemMgtImpl::Instance() {
	if(!_Instance) AttachProcess();
	return _Instance;
}

void MemMgtImpl::EnumerateProcesses(boost::function<void(MemProcessImpl *proc)> fun) {
	recursive_scoped_lock l(m_lock);
	for(auto &i: m_Processes) {
		fun(i.second.get());
	}
}

void MemMgtImpl::EnumerateMemoryObjects(boost::function<void(MemObjectImpl *obj)> fun) {
	recursive_scoped_lock l(m_lock);
	for(auto &i: m_Objects) {
		fun(i.second.get());
	}
}

void MemMgtImpl::NotifyObjectRelease(offset_ptr<MemObjectImpl> obj) {
	if(obj->GetAllocationCount() > 0) return;

	recursive_scoped_lock l(m_lock);

	if(obj->GetLifeTime() == MemLifeTime::Pointer) 
		DeallocateMemory(obj);
}

offset_ptr<MemObjectImpl> MemMgtImpl::GetMemObject(shmobjid id) {
	recursive_scoped_lock l(m_lock);
	for(auto &i: m_Objects) 
		if(i.second->GetID() == id)
			return i.second;
	throw MemoryObjectDoesNotExists();
}

} //namespace Memory 
} //namespace Core 
