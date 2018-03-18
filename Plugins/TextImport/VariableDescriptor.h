/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/VariableDescriptor.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#pragma once
#ifndef VariableDescriptor_H
#define VariableDescriptor_H
#pragma unmanaged
class ImportTable;

using namespace VisApp::Interface;

struct VariableDescriptor {
	index_t FirstValueID;
	std::wstring Name;
	VisApp::Types::DataType Type;
	iDataChannel *DataChannel;

	bool DoImport;

	VariableDescriptor();
	~VariableDescriptor();

	ImportTable* CreateImportTable();
private:									
	VariableDescriptor(const VariableDescriptor&);
	VariableDescriptor& operator=(VariableDescriptor &);
};

#endif
