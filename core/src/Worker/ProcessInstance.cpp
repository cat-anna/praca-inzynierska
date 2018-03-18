/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/ProcessInstance.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

//using namespace boost::program_options;
//using namespace boost::chrono;

namespace Worker {
namespace Mgt {
	/*
int ProcessInstance::WorkerExecMain(int argc, wchar_t **argv) {
	ProcessInstance *ptr = new ProcessInstance();
	for(int i = 1; i < argc; ++i) ptr->GetParameters().push_back(argv[i]);
	int r = ptr->Main();
	delete ptr;
	return r;
}

int ProcessInstance::WorkerExecMain(wchar_t *argline) {
	ProcessInstance *ptr = new ProcessInstance();
	ptr->GetParameters() = split_winmain(argline);
	int r = ptr->Main();
	delete ptr;
	return r;
}

int ProcessInstance::Execute() {
	return 0;
}

int ProcessInstance::Initialize() {
	Instance::Initialize();
	std::wstring input, output;
	options_description desc("Settings");
	desc.add_options()
	//	("help", "produce help message")
		("input", wvalue<std::wstring>(&input), "Input pipe")
		("output", wvalue<std::wstring>(&output), "Output pipe")
		("file", wvalue<std::wstring>(&m_ExecFile), "Executable")
		("func", wvalue<std::wstring>(&m_FunName), "Function name")
		("ParentPID", value<unsigned long>(&m_ParentPid), "Parent process id")
	;

	variables_map vm;
	store(wcommand_line_parser(m_Parameters).options(desc).run(), vm);
	notify(vm);    

	GetOutputPipe() = new Communication::BoostIPCPipe(output, true, false);
	GetInputPipe() = new Communication::BoostIPCPipe(input, false, true);

	return 0;
}

ProcessInstance::ProcessInstance() {
}

ProcessInstance::~ProcessInstance() {
}
*/
} //namespace Mgt 
} //namespace Worker 

