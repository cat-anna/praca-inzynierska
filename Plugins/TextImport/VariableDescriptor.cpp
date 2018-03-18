/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/VariableDescriptor.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#include "stdafx.h"
#include "TextImport.h"
#pragma unmanaged

VariableDescriptor::VariableDescriptor() {
	FirstValueID = 0;
	DataChannel = 0;
}

VariableDescriptor::~VariableDescriptor() {
}

using namespace VisApp::Types;

ImportTable* VariableDescriptor::CreateImportTable() {
	return VisApp::Types::DataType::DispatchTypeTemplate<TypedImportTable, ImportTable, VariableDescriptor*>(Type, this);
}

/*
template <DataDimiension VD>
ImportTable* CreateTypedImportTable(VariableType vt, VariableDescriptor *vd) {
	switch (vt) {
	case VariableType::Integer: return new TypedImportTable<VariableType::Integer, VD>(vd);
	case VariableType::Float: return new TypedImportTable<VariableType::Float, VD>(vd);
	default:
		return 0;
	}
}

ImportTable* VariableDescriptor::CreateImportTable() {
	switch (Type.Dimiension) {
	case DataDimiension::d1: return CreateTypedImportTable<DataDimiension::d1>(Type.Type, this);
	case DataDimiension::d2: return CreateTypedImportTable<DataDimiension::d2>(Type.Type, this);
	case DataDimiension::d3: return CreateTypedImportTable<DataDimiension::d3>(Type.Type, this);
	default:
		return 0;
	}
}
*/