/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ManagerImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

typedef std::lock_guard<std::mutex> scoped_lock;

struct InternalException { } ;
struct ExitException : public InternalException { } ;

ManagerImpl::ManagerImpl() {
	m_Actions.reset(new VisApp::Tools::ActionQueue());
	m_thread = std::thread(&ManagerImpl::ThreadMain, this);
}
ManagerImpl::~ManagerImpl() {
	m_WorkerList.clear();
	AddAction([this]() { throw ExitException(); });
	m_thread.join();
}

size_t ManagerImpl::GetWorkerCount(){
	return m_WorkerList.size();
}

void ManagerImpl::GetWorkerList(WeakWorkerList &list) const {
	list.clear();
	for(auto &it: m_WorkerList)
		list.push_back(it);
}

Manager::Error ManagerImpl::CancellAll() {
	for(auto &it: m_WorkerList)
		it->Cancel();
	return Error::NoError;
}

WorkerPtr ManagerImpl::CreateInternalInstance(SharedExecutable exec) {
	SharedWorkerPtr ptr(new InternalWorker(this, exec));
	m_WorkerList.push_back(ptr);
	return WorkerPtr(ptr);
}

void ManagerImpl::AddAction(std::function<void()> action) {
	m_Actions->AddAction(action);
}

void ManagerImpl::AddDelayedAction(std::function<void()> action, unsigned ms) {
	m_Actions->AddDelayedAction(action, ms);
}

SharedWorker ManagerImpl::GetSharedPointer(Worker *W) {
	scoped_lock lock(m_mutex);
	for(auto &it: m_WorkerList) 
		if(it.get() == W) 
			return it;
	return SharedWorker(0);
}

void ManagerImpl::QueueWorker(Worker *W) {
	QueueWorker(GetSharedPointer(W));
}

void ManagerImpl::QueueWorker(SharedWorker SW) {
	//accept workers in waiting status only
	if(SW->GetStatus() != WorkerStatus::Waiting)
		return;
	scoped_lock lock(m_mutex);
	m_WorkerQueue.push_back(SW);
}

void ManagerImpl::ProcessQueueAction() {
	scoped_lock lock(m_mutex);
	for(auto it = m_WorkerQueue.begin(), jt = m_WorkerQueue.end(); it != jt; ++it) {
		auto &w = *it;
		if(w->GetStatus() != WorkerStatus::Waiting) {
			//somehow into queue gets not waiting worker or got waken up earlier
			//ignore
			m_WorkerQueue.erase(it);
			break;
		}

		if(w->Execute() != Worker::Error::NoError) 
			continue;

		m_WorkerQueue.erase(it);
		break;
	};

	throw VisApp::Tools::ActionQueue::DelayAction(100);
}

void ManagerImpl::ProcessFinished(Worker *W) {
	/*AddDelayedAction([this, W] {
		auto ptr = GetSharedPointer(W);
		if(!ptr) return;

		std::remove_if(m_WorkerList.begin(), m_WorkerList.end(), [W] (SharedWorker &w) -> bool {
			return w.get() == W;
		});
		std::remove_if(m_WorkerQueue.begin(), m_WorkerQueue.end(), [W] (SharedWorker &w) -> bool {
			return w.get() == W;
		});
	}, 10 * 1000);*/
}

void ManagerImpl::RemoveFinishedAction() {
	scoped_lock lock(m_mutex);

	for(auto it = m_WorkerList.begin(), jt = m_WorkerList.end(); it != jt; ++it) {
		switch ((*it)->GetStatus()) {
		case WorkerStatus::Exited:
		case WorkerStatus::Finished:
			break;
		default:
			continue;
		}
		m_WorkerList.erase(it);
		throw VisApp::Tools::ActionQueue::DelayAction(1 * 1000);
	}

	throw VisApp::Tools::ActionQueue::DelayAction(60 * 1000);
}

void ManagerImpl::ThreadMain() {
	VisApp::OS::SetThreadName("Worker Mgt thread");

	try {
		AddAction([this] { ProcessQueueAction(); });
		AddAction([this] { RemoveFinishedAction(); });
		while(1) 
		try {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			m_Actions->WaitForAction();
			m_Actions->DispatchSingleAction();
		}
		catch (const InternalException&) {
			throw;
		}
		catch (...) {
			//TODO: log error
		}
	}
	catch(...) {
	}
//	boost::this_thread::yield();
//	while (!m_thread.interruption_requested()) {
//		boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
//		boost::mutex::scoped_lock l(m_mutex);
	//	for(auto *i : m_Clients)
	//		i->ProcessInstance();
	//}
}	

//---------------------------------------------------------------------

Manager::Manager() { }
Manager::~Manager() { }

/*
Worker Manager::CreateInstance(const std::wstring &LibFile, const std::wstring &FunName, WorkerExecMode mode) {
	switch (mode) {
	case WorkerExecMode::Process: {
		boost::mutex::scoped_lock l(m_mutex);
		Worker *client = new Worker(LibFile, FunName, this);
		m_WorkerList.push_back(client);
		return client;
	}
	case WorkerExecMode::Thread:
		AddLOG("Fatal error! - thread mode is not supported yet");
		return 0;
		break;
	}
	AddLOG("Fatal error!");
	return 0;
*/
/*
xml_node Manager::GenerateExecutionXML(xml_document &document, Command ExecMode) {
	document.reset();

	xml_node root = document.append_child(L"Worker");
	root.append_child(L"ExecMode").text() = ExecMode.ToString();
	xml_node Config = root.append_child(L"Configuration");

	return root.append_child(Command::CommandString(Command::wc_ExecuteWorker));
}*/

//------------------------------------------------------------------------------

std::unique_ptr<ManagerImpl> _Instance;

ManagerImpl* ManagerImpl::Instance() {
	return _Instance.get();
}

Manager* Manager::Instance() {
	return _Instance.get();
}

bool Manager::ConstructInstance() {
	if(_Instance) return false;
	_Instance.reset(new ManagerImpl());
	return true;
}

Manager::Error Manager::DestroyInstance() {
	if(!_Instance) return Manager::Error::NoError;
	_Instance->CancellAll();
	_Instance.reset();
	return Error::NoError;
}

} //namespace Mgt 
} //namespace Worker 
