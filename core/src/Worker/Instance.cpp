/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Instance.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"
#include <boost\chrono.hpp>
//using namespace boost::program_options;
using namespace boost::chrono;

namespace Worker {
namespace Mgt {

struct eWorkerClientException { };
struct eInitializationException : public eWorkerClientException { };
struct eUnknownStatus : public eWorkerClientException { };
struct eBrokenStatus : public eWorkerClientException { };
struct eCancelledStatus : public eWorkerClientException { };
struct eFinishedStatus : public eWorkerClientException { };

//-----------------

Instance::Instance() {
}

Instance::~Instance() {
}

int Instance::Initialize() {
//	m_InputPipe->ReadMessage(m_ExecutionData);
//	xml_node root = m_ExecutionData.document_element();
//	m_ExecutionData.save_file("tstdoc");
//	return WorkerCommands::StringToCommand(root.child(L"ExecMode").text().as_string(L""));
	
//TODO: check root element name
//		xml_node Config = root.child(L"Configuration");
	return 0;
}

int Instance::Finalize() {
	SendStatus();
	MessageToSever(Command::wc_Finished);
	return 0;
}

int Instance::InstanceMain() {

	steady_clock::time_point start = steady_clock::now();
	try {
		
		Initialize();
#ifdef  _DEBUG
		//SetStatus(WorkerStatus::DebugPause);
		CheckStatus();
#endif
		SetStatus(WorkerStatus::Working);
		AddLog(Hint, "Worker '" << GetName() << "' is starting");
		std::thread workthread;
		volatile bool isWorking = true;

		workthread = std::thread([this, &isWorking] {
			try {
				CheckStatus();
				Execute(); 
				SetProgress(1);
				MessageToSever(Command::wc_Finished);
				SetStatus(WorkerStatus::Finished);
			}
			catch(const std::exception &e) {
				AddLog(CriticalError, L"Catched critical error with message: " << e.what());
			}
			catch(...) {
				AddLog(CriticalError, L"Catched critical and unknown exception!");
			}		
			isWorking = false;
		});

		try {
			while(isWorking) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				CheckStatus();
			}
			workthread.join();
		}
		catch(...) {
			workthread.join();
			throw;
		}
	}
	catch(const eFinishedStatus &) {
		//no error
	}
	catch(const eInitializationException &) {
	//	AddLOG();
		return 1;
	}
	catch(const eWorkerClientException& e) {
		(void)e;//kill warning;
		AddLog(Error, "Error! Catched error class: " << typeid(e).name());
	}
	catch(...) {
		AddLog(Error, "Unknown fatal error!");
	}
	Finalize();
	duration<double> sec = steady_clock::now() - start;
	long long secs = static_cast<long long>(sec.count());
	AddLog(Hint, L"Worker '" << GetName() << L"' finished in " << secs << L" seconds [" << std::setprecision(2) << (secs / 60.0f) << L" min]");
	return 0;
}

void Instance::SendStatus() {
	xml_document doc;
	xml_node root = doc.append_child(L"root");
//	root.append_child(L"Progress").text() = m_Progress;
	xml_node phase = root.append_child(L"Phase");
//	root.append_child(L"Name").text() = m_Name.c_str();
	//MessageToSever(WorkerCommands::wc_Status, root);
}

void Instance::CheckProcess() {
	bool messageSent = false;

	while(1)
	switch (GetStatus()) {
	case WorkerStatus::Working:
		return;

//long wait
	case WorkerStatus::New:
		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		continue;

//short wait
	case WorkerStatus::DebugPause: 
	case WorkerStatus::Paused:
		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		continue;

	case WorkerStatus::Broken:
		throw eBrokenStatus(); //TODO

	case WorkerStatus::Finished:
		throw eFinishedStatus();

	default:
		throw eUnknownStatus();
	}
}


void Instance::CheckStatus() {
	bool messageSent = false;

	while(1)
	switch (GetStatus()) {
		
	case WorkerStatus::New:
		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		continue;

	case WorkerStatus::Working:
		return;

	case WorkerStatus::Paused:
		if(!messageSent) {
			MessageToSever(Command::wc_Suspended);
			messageSent = true;
		}
		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		if(GetStatus() == WorkerStatus::Working)
			MessageToSever(Command::wc_Resumed);

		continue;

	//case WorkerStatus::Broken:
	//	throw eBrokenStatus(); //TODO

	//case WorkerStatus::Finished:
	//	throw eFinishedStatus();

	case WorkerStatus::DebugPause: {
		MessageToSever(Command::wc_DebugWait);
		float prv_progress = GetProgress();
		for(int i = 0; i < 10; ++i){
			SetProgress((i+1) / 10.0f);
			SendStatus();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		SetProgress(prv_progress);
		return;
	}

	default:
		return;
		//throw eUnknownStatus();
	}
}

int Instance::MessageToSever(Command cmd, xml_node MessageData) {
	if(!cmd.IsCommand())
		return m_OutputPipe->WriteMessage(MessageData);
	std::wstringstream ss;

	if(!MessageData)
		ss << L"<" << cmd.ToString() << " />";
	else {
		ss << L"<" << cmd.ToString() << ">";
		for(auto it = MessageData.first_child(); it; it = it.next_sibling())
			it.print(ss, L"", pugi::format_raw);
		ss << L"</" << cmd.ToString() << ">";
	}
	
	return m_OutputPipe->WriteRawMessage(ss.str());
}

} //namespace Mgt 
} //namespace Worker 
