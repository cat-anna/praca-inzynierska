/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ManagerImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

class ManagerImpl: public Manager {
public:
	ManagerImpl();
	~ManagerImpl();

	size_t GetWorkerCount();
	void GetWorkerList(WeakWorkerList &list) const;

	Error CancellAll();
	WorkerPtr CreateInternalInstance(SharedExecutable exec);

	void QueueWorker(SharedWorker SW);
	void QueueWorker(Worker *W);

	SharedWorker GetSharedPointer(Worker *W);

	static ManagerImpl* Instance();

	void ProcessFinished(Worker *W);
private:
	void AddAction(std::function<void()> action);
	void AddDelayedAction(std::function<void()> action, unsigned ms);
	void ThreadMain();

	void ProcessQueueAction();
	void RemoveFinishedAction();

	std::thread m_thread;
	std::mutex m_mutex;

	std::auto_ptr<VisApp::Tools::ActionQueue> m_Actions;

	std::list<SharedWorker> m_WorkerList;
	std::list<SharedWorker> m_WorkerQueue;
};

} //namespace Mgt 
} //namespace Worker 
