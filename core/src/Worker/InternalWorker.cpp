/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/InternalWorker.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

class DummyExecutable : public Executable {
public:
	DummyExecutable(SharedExecutable src) {
		SetName(src->GetName());
		SetProgress(src->GetProgress());
	}
};

class InternalInstance : public Instance {
friend class InternalWorker;
public:
	InternalInstance(InternalWorker *worker, SharedExecutable Exec): 
			Instance(), 
			m_Worker(worker),
			m_Exec(Exec),
			m_Status(WorkerStatus::New) {
	}

	~InternalInstance() {
		SetStatus(WorkerStatus::Finished);
		m_thread.join();
	}

	virtual int Execute() {
		if(!m_Exec) return 1;
		m_Exec->Execute(m_WeakThis);
		return 0;
	}

	void SetProgress(float progress) { 
		m_Exec->SetProgress(progress); 
	}
	void SetName(const std::wstring &Name) { 
		m_Exec->SetName(Name); 
	}

	WorkerStatus GetStatus() const { 
		return m_Status; 
	}
	const std::wstring& GetName() { 
		return m_Exec->GetName(); 
	}
	float GetProgress() const { 
		return m_Exec->GetProgress(); 
	}

	void SetStatus(WorkerStatus status) { m_Status = status; }

	void SetSelfPointer(std::weak_ptr<InternalInstance> instance) { m_WeakThis = instance; }
	void SetPipes(std::shared_ptr<Communication::MessagePipe> in, std::shared_ptr<Communication::MessagePipe> out) {
		m_InputPipe = in;
		m_OutputPipe = out;
	}
	void Run() {
		m_thread = std::thread([this] { ThreadExec(); } );
	}
	
	void ThreadExec() {
		InstanceMain(); 
		DummyExecutable *de = new DummyExecutable(m_Exec);
		m_Exec = SharedExecutable(de);
		ManagerImpl::Instance()->ProcessFinished(m_Worker);
	}

	InternalWorker::Error Cancel() {
		SetStatus(WorkerStatus::Finished);
		return InternalWorker::Error::NoError;
	}
private:
	InternalWorker *m_Worker;
	SharedExecutable m_Exec;
	std::weak_ptr<InternalInstance> m_WeakThis;
	WorkerStatus m_Status;

	std::thread m_thread;
};

//---------------------------------------------------------------------------------- 

InternalWorker::InternalWorker(Manager *Owner, SharedExecutable Exec): Worker(Owner) {
	m_InputPipe.reset(new Communication::MessageQueue());
	m_OutputPipe.reset(new Communication::MessageQueue());
	
	m_Instance.reset(new InternalInstance(this, Exec));
	m_Instance->SetSelfPointer(std::weak_ptr<InternalInstance>(m_Instance));
	m_Instance->SetPipes(m_InputPipe, m_OutputPipe);
}

InternalWorker::~InternalWorker() {
}

InternalWorker::Error InternalWorker::Execute() {
	auto st = Worker::Execute();
	if(st == Error::NoError) {
		if(m_Instance->m_Exec->CheckRequirements() == 0)
			m_Instance->Run();
		else {
			return Error::RequirementsNotFullfiled;
		}
	}
	return Error::NoError;
}

SharedExecutable& InternalWorker::GetExec() {
	return m_Instance->m_Exec;
}

SharedExecutable& InternalWorker::GetExec() const {
	return m_Instance->m_Exec;
}

InternalWorker::Error InternalWorker::Cancel() {
	return m_Instance->Cancel();
}

float InternalWorker::GetProgress() const {
	return GetExec()->GetProgress();
}

const std::wstring& InternalWorker::GetName() const {
	return GetExec()->GetName();
}

WorkerStatus InternalWorker::GetStatus() const {
	return m_Instance->GetStatus();
}

void InternalWorker::SetStatus(WorkerStatus NewStatus) {
	m_Instance->SetStatus(NewStatus);
}

} //namespace Mgt 
} //namespace Worker 
