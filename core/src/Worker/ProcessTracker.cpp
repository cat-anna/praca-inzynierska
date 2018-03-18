/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessTracker.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Shellapi.h>

namespace Worker{ 
namespace Mgt { 
#if 0
unsigned long ProcessTracker::GetCurrentPID() {
	return GetCurrentProcessId();
}

class WindowsProcessTracker : public ProcessTracker {
protected:
	HANDLE m_hProcess;
public:
	WindowsProcessTracker(const std::wstring &ExcFile, const std::wstring &Parameters, unsigned RunFlags):
			ProcessTracker(ExcFile, Parameters, RunFlags),
			m_hProcess(0) {
		if(m_Flags & rf_ExecuteNow)
			ExecuteProcess();
	}
	~WindowsProcessTracker() {
		if(m_Flags & rf_KillWhenFreed)
			KillProcess();
		else
			CloseHandle(m_hProcess);
	}

	bool IsWorking() const {
		return m_hProcess != 0;
	}
	bool KillProcess() {
		if(!IsWorking()) return true;	

		TerminateProcess(m_hProcess, 0);
		CloseHandle(m_hProcess);
		m_hProcess = 0;
		return true;
	}
	bool ExecuteProcess() {
		if(IsWorking()) return false;

		PROCESS_INFORMATION pi;
		memset(&pi, 0, sizeof(pi));
		STARTUPINFOW si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		unsigned procflags = 0;
#ifdef BUILD_Debug 
//		procflags |= DEBUG_PROCESS;
#endif
		//if((m_Flags & rf_PriorityBelowNormal) > 0)
		//	procflags |= BELOW_NORMAL_PRIORITY_CLASS;
		bool r = CreateProcessW(
				m_Excutable.c_str(),//lpApplicationName 
				(wchar_t*)m_Parameters.c_str(),//lpCommandLine 
				0,//lpProcessAttributes 
				0,//lpThreadAttributes 
				FALSE,//bInheritHandles 
				procflags,//dwCreationFlags
				0,//lpEnvironment 
				0,//lpCurrentDirectory 
				&si,//lpStartupInfo 
				&pi//lpProcessInformation 
			) > 0;
		if(!r) {
			AddLOG(L"Unable to create process: '" << m_Excutable << "'  Code: " << GetLastError());
			return false;
		}
		m_hProcess = OpenProcess(PROCESS_TERMINATE, false, pi.dwProcessId);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return true;

	/*	SHELLEXECUTEINFOA sei;
		memset(&sei, sizeof(sei), 0);
		sei.cbSize = sizeof(sei);
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;
		sei.lpVerb = "open";
		sei.lpFile = m_Excutable.c_str();
		sei.lpParameters = m_Parameters.c_str();
		sei.lpDirectory = 0;
		sei.nShow = SW_NORMAL;
		bool r = ShellExecuteExA(&sei);
		if(!r) return false;
		m_hProcess = sei.hProcess;*/
		return true;
	}
};

//--------------------------Interface --------------------------

// static constructor

ProcessTracker* ProcessTracker::CreateTracker(const std::wstring &ExcFile, const std::wstring &Parameters, unsigned RunFlags) {
	return new WindowsProcessTracker(ExcFile, Parameters, RunFlags);
}

// abstract interface functions
 
ProcessTracker::ProcessTracker(const std::wstring &ExcFile, const std::wstring &Parameters, unsigned RunFlags):
		m_Excutable(ExcFile),
		m_Parameters(Parameters),
		m_Flags(RunFlags) {
}

ProcessTracker::~ProcessTracker() {
}
#endif
} //namespace Mgt
} //namespace Worker
