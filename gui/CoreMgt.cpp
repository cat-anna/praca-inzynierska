/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CoreMgt.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"

#include "CoreWaitForm.h"
#include <msclr\marshal_cppstd.h>
#include "MainForm.h"

#include "CoreMgt.h"

using namespace VisApp::gui;
using namespace gui;

VisApp::Interface::iManager* CoreMgt::_CoreInstance = 0;

class CoreObserver : public VisApp::Interface::iCoreObserver {
private:
	typedef VisApp::Interface::CoreNotification CoreNotification;

public:
	CoreObserver() { }
	virtual ~CoreObserver() { }

	virtual void OnNotification(CoreNotification cn) {
		MainForm::GetNotificationDispatcher()->OnMessage(cn);
	}

	virtual void OnCoreMessage(CoreMessageClass MessageClass, const std::wstring &Message) {
		MainForm::GetNotificationDispatcher()->OnMessage(MessageClass, Message);
	}

	virtual void NewLogLine(const std::wstring& FullLine, unsigned LineType) { }
};

bool CoreMgt::Initialize(System::Windows::Forms::Form ^Owner) {
	System::String ^dir = System::IO::Directory::GetCurrentDirectory();
	std::wstring stddir = msclr::interop::marshal_as<std::wstring>(dir);

	_CoreInstance = VisApp::Interface::CreateInstance(stddir);
	_CoreInstance->RegisterCoreObserver(new CoreObserver());
	//if(
		_CoreInstance->Initialize() ;
		//!= Core::Errdef::NoError)
		//return false;
	return true;
}

void CoreMgt::WaitForCore() {
	CoreWaitForm::WaitForLibStatus(gui::MainForm::Instance(), VisApp::Interface::iManager::ls_Ready);
}

bool CoreMgt::Finalize(System::Windows::Forms::Form ^Owner) {
	_CoreInstance->Finalize();
	delete _CoreInstance->RegisterCoreObserver(0);
	CoreWaitForm::WaitForLibStatus(Owner, VisApp::Interface::iManager::ls_Finalized);
	delete _CoreInstance;
	_CoreInstance = 0;
	return true;
}

