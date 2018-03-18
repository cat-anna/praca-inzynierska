/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessInstance.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef ProcessInstance_H
#define ProcessInstance_H

namespace Worker {
namespace Mgt {
	/*
class WORKER_API ProcessInstance : public Instance {
public:
	static int WorkerExecMain(int argc, wchar_t **argv);
	static int WorkerExecMain(wchar_t *argline);

 	virtual ~ProcessInstance();
protected:
	virtual int Execute();
	virtual int Initialize();
	std::vector<std::wstring>& GetParameters() { return m_Parameters; }
private: 
 	ProcessInstance();
 	ProcessInstance(const ProcessInstance&);//=delete;
	const ProcessInstance& operator=(const ProcessInstance&);//=delete;

	std::vector<std::wstring> m_Parameters;
	std::wstring m_ExecFile, m_FunName;
	unsigned long m_ParentPid;
	Communication::MessagePipe *m_InputPipe, *m_OutputPipe;
};
*/
} //namespace Mgt 
} //namespace Worker 

#endif

