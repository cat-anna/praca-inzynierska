/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/MemMgt/MemProcess.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemProcess_H
#define MemProcess_H

namespace Core {
namespace Memory {

class CORESHARED_API MemProcess {
public:
 	MemProcess(MemProcessImpl *Impl);
 	~MemProcess();

	Shared::OS::PID_t GetSysPid();
	shmpid GetPid() const;
	const MemortStatusInfo &GetStatusinfo() const;

	void EnumerateAllocatedObjects(boost::function<void(MemObject)> fun);
	bool IsWorking() const;
private: 
	MemProcessImpl *m_Impl;
};

} //namespace Memory 
} //namespace Core 

#endif
