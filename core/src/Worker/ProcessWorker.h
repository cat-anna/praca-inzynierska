/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessWorker.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef ProcessWorker_H
#define ProcessWorker_H

namespace Worker {
namespace Mgt {

class ProcessTracker;

class ProcessWorker : public Worker {
public:
 	ProcessWorker(const std::wstring &ExecFile, const std::wstring &FunName);
 	virtual ~ProcessWorker();

	ProcessTracker* GetProcess() const;
protected:
private: 
	WorkerStatus m_Status;
	ProcessTracker *m_Process;

	float m_Progress;
	std::wstring m_WorkerName;
};

} //namespace Mgt 
} //namespace Worker 

#endif

