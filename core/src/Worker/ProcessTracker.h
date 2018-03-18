/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessTracker.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef ProcessTracker_H
#define ProcessTracker_H

namespace Worker { 
namespace Mgt { 
#if 0
class ProcessTracker {
protected:
	std::wstring m_Excutable, m_Parameters;
	unsigned m_Flags;
	ProcessTracker(const std::wstring &ExcFile, const std::wstring &Parameters, unsigned RunFlags);
public:
	enum wRunFlags{
		rf_KillWhenFreed			= 0x0100,
		
		rf_PriorityBelowNormal		= 0x1000,

		rf_ExecuteNow				= 0x0001,
		
		rf_Default					= rf_KillWhenFreed | rf_PriorityBelowNormal,
		rf_DefaultExecuteNow		= rf_Default | rf_ExecuteNow,
	};

	virtual ~ProcessTracker();
	static ProcessTracker* CreateTracker(const std::wstring &ExcFile, const std::wstring &Parameters, unsigned RunFlags = rf_Default);
	
	virtual bool IsWorking() const = 0;
	virtual bool KillProcess() = 0;
	virtual bool ExecuteProcess() = 0;

	const std::wstring& GetExecFileName() const { return m_Excutable; }
	const std::wstring& GetExecParameters() const { return m_Parameters; }

	static unsigned long GetCurrentPID();
};
#endif
} //namespace Mgt
} //namespace Worker

#endif
