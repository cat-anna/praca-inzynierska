/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Commands.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

Command::CommandMap _CommandMap;

const wchar_t* CommandTable[Command::wc_MaxValue] = {};

Command::CommandMap::CommandMap() {
	CommandTable[wc_nop] = L"NOP";
//server
	CommandTable[wc_Suspend] = L"Suspend";
	CommandTable[wc_Resume] = L"Resume";
	CommandTable[wc_Abort] = L"Abort";
	CommandTable[wc_Command] = L"Command";
//client
	CommandTable[wc_DebugWait] = L"DebugWait";
	CommandTable[wc_Suspended] = L"Suspended";
	CommandTable[wc_Resumed] = L"Resumed";
	CommandTable[wc_Finished] = L"Finished";
	CommandTable[wc_Result] = L"Result";
	CommandTable[wc_Exited] = L"Exited";
//both
	CommandTable[wc_Message] = L"Message";
	CommandTable[wc_Status] = L"Status";
	CommandTable[wc_FatalError] = L"FatalError";
//non commands
	CommandTable[wc_ExecuteWorker] = L"ExecuteWorker";
	CommandTable[wc_DescribeWorker] = L"DescribeWorker";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";
//	CommandTable[wc_Status] = L"Status";

	for(unsigned i = wc_nop; i < wc_MaxValue; ++i)
		if(!CommandTable[i]) 
			continue;
		else 
			insert(std::make_pair(CommandTable[i], (CommandEnum)i));
}


const wchar_t* Command::CommandString(CommandEnum cmd) {
	if(cmd >= wc_MaxValue) return L"Unknown_Command";
	return CommandTable[cmd];
}

Command Command::FromString(const std::wstring &command){ 
	auto it = _CommandMap.find(command);
	if(it == _CommandMap.end()) return Command(Command::wc_UnknownCommand);
	return  Command(it->second);
}

} //namespace Mgt 
} //namespace Worker 
