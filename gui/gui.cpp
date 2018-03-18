/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/gui.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
// gui.cpp : main project file.

#include "stdafx.h"
#include "MainForm.h"

#include "CoreMgt.h"

using namespace VisApp::gui;
using namespace gui;
 
[STAThreadAttribute]
int main(array<System::String ^> ^args) {
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Settings::DoLoad();
	
	// Create the main window and run it
	Application::Run(MainForm::Instance());

	Settings::DoSave();

	return 0;
}
