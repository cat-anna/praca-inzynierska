/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/CLIGuiHandler.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "CLIGuiHandler.h"
#include "TextImport.h"

#include "ImportTextFileForm.h"

#pragma managed 

GuiHandler::GuiHandler(TextImportPlugin *instance): CLIGuiHandler(), m_instance(instance) {
}

GuiHandler::GuiResult GuiHandler::OpenGui(System::Windows::Forms::Form^ Owner) {
	auto form = gcnew gui::ImportTextFileForm(Owner, m_instance);
	form->ShowDialog();
	return GuiResult::Ok;
}
