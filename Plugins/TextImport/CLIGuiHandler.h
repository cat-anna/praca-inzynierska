/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/CLIGuiHandler.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef CLIGuiHandler_H
#define CLIGuiHandler_H

class TextImportPlugin;

#pragma managed

class GuiHandler : public VisApp::Plugins::CLIGuiHandler {
public:
	GuiHandler(TextImportPlugin *instance); 
	virtual GuiResult OpenGui(System::Windows::Forms::Form^ Owner);
private:
	TextImportPlugin *m_instance;
};

#pragma unmanaged

#endif
