/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/InternalWorker.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef InternalWorker_H
#define InternalWorker_H

namespace Worker {
namespace Mgt {

class InternalInstance;

class InternalWorker : public Worker {
friend class InternalInstance;
public:

	InternalWorker(Manager *Owner, SharedExecutable Exec);
 	virtual ~InternalWorker();

	virtual float GetProgress() const;
	virtual const std::wstring& GetName() const;
	virtual WorkerStatus GetStatus() const;

	virtual Error Execute();
	virtual Error Cancel();
protected:
	SharedExecutable& GetExec();
	SharedExecutable& GetExec() const;
	virtual void SetStatus(WorkerStatus NewStatus);
private:
	std::shared_ptr<InternalInstance> m_Instance;
};

} //namespace Mgt 
} //namespace Worker 

#endif

