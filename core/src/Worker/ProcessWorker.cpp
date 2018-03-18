/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessWorker.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

#if 0

ProcessWorker::ProcessWorker(const std::wstring &ExecFile, const std::wstring &FunName): 
		m_Process() {
		std::wstring inp, outp;
	inp = outp = GenUID();
	inp += L"_i";
	outp += L"_o";

	m_OutputPipe = new Communication::BoostIPCPipe(outp, 64*1024, 8, true, false);
	m_InputPipe = new Communication::BoostIPCPipe(inp, 64*1024, 8, false, true);

	std::wostringstream Params;
	Params << L" --input="		<< outp;
	Params << L" --output="		<< inp;
	Params << L" --ParentPID="  << ProcessTracker::GetCurrentPID();
	Params << L" --function="	<< FunName;
	Params << L" ";

	m_Process = ProcessTracker::CreateTracker(ExecFile, Params.str());
}

ProcessWorker::~ProcessWorker() {
	delete m_Process;

}


ProcessTracker* Worker::GetProcess() const {
	return m_Process;
}

#endif

} //namespace Mgt 
} //namespace Worker 

