/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Worker.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {

std::wstring Worker::GenUID() {
	char rawrandname[32];
#pragma warning ( suppress: 4996 )
	sprintf(rawrandname, "%04x%04x%04x%04x", rand() & 0xFFFF, rand() & 0xFFFF, rand() & 0xFFFF, rand() & 0xFFFF);
	return std::wstring(rawrandname, rawrandname+16);
}

Worker::Worker(Manager *Owner) :
		m_InputPipe(),
		m_OutputPipe(),
		m_Owner(Owner) {
}

Worker::~Worker() {
}

Worker::Error Worker::Resume() {
	return Error::NotSupported;
}

Worker::Error Worker::Pause() {
	return Error::NotSupported;
}

Worker::Error Worker::Execute() {
	auto st = GetStatus();
	if(st == WorkerStatus::New)  {
		SetStatus(WorkerStatus::Waiting);
		ManagerImpl::Instance()->QueueWorker(this);
		return Error::Queued;
	} else
	if(st == WorkerStatus::Waiting) {
		return Error::NoError;
	}
	return Error::InvalidStatus;
}

Worker::Error Worker::Cancel() {
	return Error::NotSupported;
}

void Worker::ProcessInstance() {
	while(!m_InputPipe->IsEmpty()) {
		xml_document doc;
		xml_node root = doc.append_child(L"root");
		m_InputPipe->ReadMessage(root);
		xml_node command = root.first_child();
		Command wc = Command::FromString(command.name());

		switch (wc.as_enum()) {
	//	case Command::wc_Suspended:
	//		SetStatus(WorkerStatus::Suspended);
		//	break;
		case Command::wc_Resumed:
			SetStatus(WorkerStatus::Working);
			break;
		case Command::wc_Finished:
			WriteMessage(Command::wc_Status);
			SetStatus(WorkerStatus::Finished);
			break;		
		case Command::wc_Exited:
			SetStatus(WorkerStatus::Exited);
			break;

		case Command::wc_Message:
//			if(m_OnMessageHandler) m_OnMessageHandler(command);
			break;		
		case Command::wc_Result:
		//	if(m_OnResultHandler) m_OnResultHandler(command);
			break;	

		case Command::wc_DebugWait:
			SetStatus(WorkerStatus::DebugPause);
			break;

		case Command::wc_Status: {
	//		SetProgress(command.child(L"Progress").text().as_float(0));
			//SetWorkerName(command.child(L"Name").text().as_string(L"Unknown"));
			break;
		}
		default:
			//TODO: spawn error!
			break;
		}
	}		
}

int Worker::WriteExecutionData(xml_node data) {
	/*xml_document doc;
	xml_node exec = m_Owner->GenerateExecutionXML(doc, Command::wc_ExecuteWorker);
	for(auto it = data.first_child(); it; it = it.next_sibling())
		exec.append_copy(it);
	return WriteMessage(Command::wc_RawData, doc.document_element());*/
	return 0;
}

int Worker::WriteMessage(Command Cmd, xml_node data) {
	if(!Cmd.IsCommand())
		return m_OutputPipe->WriteMessage(data);

	std::wstringstream ss;

	if(!data)
		ss << L"<" << Cmd.ToString() << " />";
	else {
		ss << L"<" << Cmd.ToString() << ">";
		data.print(ss, L"", pugi::format_raw);
		ss << L"</" << Cmd.ToString() << ">";
	}

	return m_OutputPipe->WriteRawMessage(ss.str());
}

int Worker::WriteMessage(Command Cmd, const std::wstring &data) {
	if(!Cmd.IsCommand())
		return m_OutputPipe->WriteRawMessage(data);

	std::wstringstream ss;
	const wchar_t *cmd = Cmd.ToString();
	if(data.empty())
		ss << L"<" << cmd << " />";
	else {
		ss << L"<" << cmd << ">" 
		   << data
		   << L"</" << cmd << ">";
	}

	return m_OutputPipe->WriteRawMessage(ss.str());
}

int Worker::WriteUserCommand(unsigned Command, xml_node data) {
	std::wstringstream ss;

	const wchar_t *cmd = Command::CommandString(Command::wc_Command);
	ss << L"<" << cmd << L" " << L"UintValue=\"" << Command << "\"";
	if(!data)
		ss << " />";
	else {
		ss << ">";
		data.print(ss, L"", pugi::format_raw);
		ss << L"</" << cmd << ">";
	}

	return m_OutputPipe->WriteRawMessage(ss.str());
}

int Worker::ReadMessage(xml_node &data) {
	return m_OutputPipe->ReadMessage(data);
}	

} //namespace Mgt 
} //namespace Worker 

