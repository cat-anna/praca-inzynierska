/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemProcessImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\CoreShared.h"
#include "MemHdr.h"

namespace Core {
namespace Memory {

using namespace boost::interprocess;

MemProcessImpl::MemProcessImpl(shmpid pid): 
		m_pid(pid), 
		m_SysPid(Shared::OS::Process::CurrentPID()),
		m_StatusInfo(),
		m_AllocatedObjects(std::less<shmobjid>(), MemMgtImpl::GetAllocator()),
		m_ActionList(MemMgtImpl::GetAllocator()),
		m_IsWorking(false) {
	scoped_lock l(m_lock);
	LOG << "Create process: " << pid;

	QuerryProcMemInfoStatus();

	m_timestap = microsec_clock::local_time();
	boost::thread(&MemProcessImpl::ThreadMain, this).detach();
	boost::this_thread::yield();
}

MemProcessImpl::~MemProcessImpl() {
	if(m_IsWorking) CancellProcess();
	LOG << "Delete process: " << m_pid;
}

boost::shared_ptr<MemPointer> MemProcessImpl::BindMemObject(offset_ptr<MemObjectImpl> object) {
	scoped_lock l(m_lock);
	if(MemMgtImpl::GetThisProc()->GetPid() == m_pid) {
		return InternalMemBind(object);
	} else {
		//queue action
		LOG << LogType::Fatal << "Enqueue action is not implemented";
		return boost::shared_ptr<MemPointer> (0);
	}
}

void MemProcessImpl::ReleaseMemObject(offset_ptr<MemObjectImpl> object) {
	scoped_lock l(m_lock);
	if(MemMgtImpl::GetThisProc()->GetPid() == m_pid) {
		InternalMemRelease(object);
	} else {
		//queue action
		LOG << LogType::Fatal << "Enqueue action is not implemented";
	}
}

void MemProcessImpl::CancellProcess() {
	{
		scoped_lock l(m_lock);
		Action act;
		act.Type = Action::Types::AbortMemProcessImpl;
		m_ActionList.push_front(act);
	}
	while(m_IsWorking) 
		boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
}

boost::shared_ptr<MemPointer> MemProcessImpl::InternalMemBind(offset_ptr<MemObjectImpl> object) {
	MemSegment &ms = m_AllocatedObjects[object->GetID()];
	if(ms.Manager) {
		return boost::shared_ptr<MemPointer>(ms.Pointer); //allready bind. exit.
	}
	
	try {
		ms.Manager = new SharedMemoryManager(open_only, object->GetName().c_str());
		ms.MemObjPointer = object;
		ms.MemObjPointer->NotifyProcessBind(static_cast<offset_ptr<MemProcessImpl>>(this));
		void *Mem = ms.Manager->find_or_construct<char>("Mem")[object->GetSize()]();
		boost::shared_ptr<MemPointer> ptr = boost::shared_ptr<MemPointer>(new MemPointer(ms.MemObjPointer.get(), Mem));
		ms.Pointer = boost::weak_ptr<MemPointer>(ptr);
#ifdef MGMMGT_DEBUG_LOG_SEGM_FLOW
		LOG << "Memory object attached: " << object->GetName().c_str();
#endif
		return ptr;
	} catch(...) {
		delete ms.Manager;
		m_AllocatedObjects.erase(object->GetID());
		LOG << LogType::Fatal << "Unable to bind to object: " << object->GetName();
		return boost::shared_ptr<MemPointer> (0);
	}
}

void MemProcessImpl::InternalMemRelease(offset_ptr<MemObjectImpl> object, bool Force) { 
	auto memseg = m_AllocatedObjects.find(object->GetID());
	if(memseg == m_AllocatedObjects.end()) {
		LOG << LogType::Fatal << "An attempt to release object which haven't been bind!";
		return;
	}

	delete memseg->second.Manager;
	memseg->second.Manager = 0;
	memseg->second.MemObjPointer->NotifyProcessRelease(static_cast<offset_ptr<MemProcessImpl>>(this));
	m_AllocatedObjects.erase(memseg);	
#ifdef MGMMGT_DEBUG_LOG_SEGM_FLOW
	LOG << "Memory object detached: " << object->GetName().c_str();
#endif
	MemMgtImpl::Instance()->NotifyObjectRelease(memseg->second.MemObjPointer);
}

void MemProcessImpl::NotifyPointerDestruction(shmobjid id) {
	scoped_lock l(m_lock);
	auto obj = m_AllocatedObjects.find(id);
	if(obj == m_AllocatedObjects.end()) {
		LOG << LogType::Warning << "Notification about not bound memory object!";
		return;
	}

	InternalMemRelease(obj->second.MemObjPointer);
}

bool MemProcessImpl::IsBroken() const {
	auto diff = microsec_clock::local_time() - m_timestap;
	return diff.total_milliseconds() > 500 || !Shared::OS::Process::IsProcessRunning(m_SysPid);
}

void MemProcessImpl::ThreadMain() {
	LOG << "Entering process memory mgr thread";

	unsigned NOPCounter = 0;
	m_IsWorking = true;
	while(m_IsWorking) {
		try {
			boost::this_thread::interruption_point();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
			m_timestap = microsec_clock::local_time();

			if(m_ActionList.empty()){
				if(MemMgtImpl::GetOwnerPid() != m_pid) continue;
				++NOPCounter;
				MemMgtImpl::OwnerThreadNotification(NOPCounter);
				continue;
			}
		}
		catch(...) {

		}

		m_lock.lock();
		auto action = m_ActionList.front();
		m_ActionList.pop_front();
		m_lock.unlock();

		switch(action.Type) {
		case Action::Types::AbortMemProcessImpl: {
			scoped_lock l(m_lock);
			while(!m_AllocatedObjects.empty())
				InternalMemRelease(m_AllocatedObjects.begin()->second.MemObjPointer, true);
		/*	for(auto &i: m_AllocatedObjects) {
				InternalMemRelease(i.second.MemObjPointer, true);
			}*/
			m_AllocatedObjects.clear();
			m_IsWorking = false;
			continue;
		}

		case Action::Types::BindObject:
			LOG << "not implemented action: BindObject";
			continue;
										  
		case Action::Types::ReleaseObject:
			LOG << "not implemented action: ReleaseObject";
			continue;
		}
	}

	LOG << "Leaving process memory mgr thread";
}

void MemProcessImpl::EnumerateAllocatedObjects(boost::function<void(MemObjectImpl*)> fun) {
	scoped_lock l(m_lock);
	for(auto &i: m_AllocatedObjects) {
		fun(i.second.MemObjPointer.get());
	}}

void MemProcessImpl::UpdateStatus() {
	LOG_NOT_IMPLEMENTED
}

void MemProcessImpl::QuerryProcMemInfoStatus() {
	LOG_NOT_IMPLEMENTED
}

} //namespace Memory 
} //namespace Core 
