/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CoreMgt.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#ifdef _DEBUG
#define DEBUG_WINDOW_NAME this->Text += " [DEBUG]";
#else
#define DEBUG_WINDOW_NAME
#endif

class CoreMgt {
public:
	static bool Initialize(System::Windows::Forms::Form ^Owner);
	static bool Finalize(System::Windows::Forms::Form ^Owner);

	static VisApp::Interface::iManager *GetCore() { return _CoreInstance; }

	static void WaitForCore();
private:
	static VisApp::Interface::iManager *_CoreInstance;
};
