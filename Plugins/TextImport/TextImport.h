/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/TextImport.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#pragma unmanaged 

using namespace VisApp::Plugins;
using namespace VisApp::Interface;

#ifndef TIMPORT_API
#define TIMPORT_API
//#define TIMPORT_API __declspec(dllexport)
#endif

#include "ImportTable.h"
#include "VariableDescriptor.h"
#include "ReadBucket.h"
class FileReader;

typedef std::shared_ptr<VariableDescriptor> SharedVariableDesciptor;
typedef std::vector<SharedVariableDesciptor> SharedVariableDesciptorVector;

enum class ImportFlags {
	FirstLineHaveSize = 1,
	IgonoreFollowingSeparator,
};

struct ImportData;
typedef std::vector<ImportTable*> ImportStructure;

class TIMPORT_API TextImportPlugin : public ImportPlugin {
public:
	TextImportPlugin();
	virtual ~TextImportPlugin();

	virtual void SetSourceFile(const std::wstring &file);
	virtual PreprocessResult PreprocessFile();

	CLIGuiHandler* GetCLIGuiHandler();

	SharedVariableDesciptorVector& GetVariables() { return m_Variables; }
	void SetCoordDescriptor(SharedVariableDesciptor &svd) { m_CoordVars = svd; }
	SharedVariableDesciptor& GetCoordDescriptor() { return m_CoordVars; }

	char GetCollumnSeparator() { return m_CollumnSeparator; }
	void SetCollumnSeparator(char val) { m_CollumnSeparator = val; }
	using ImportPlugin::SetDataSize;

	unsigned ResetVariableIds();
	unsigned GetVariableCount() const;

	bool CheckFlag(ImportFlags flag) const;
	void SetFlag(ImportFlags flag, bool status);

	void SaveCollumSettings(xml_node out) const;
	void LoadCollumnSettings(const xml_node in);

	void AddVariable(const wchar_t *name, VisApp::Types::DataType type);
protected:
	virtual void BeforeRun();
	virtual void AfterRun();
	virtual void Run();
	virtual void OnExecute();

	virtual void StoreRuntimeConfig(xml_node out) const { }
	virtual void LoadRuntimeConfig(const xml_node in) { }

	char m_CollumnSeparator;
//	char m_DecimalSeparator;//LineSeparator?
	unsigned m_ImportFlags;
	//unsigned m_CollumnsPerLine;//TODO

	SharedVariableDesciptor m_CoordVars;
	SharedVariableDesciptorVector m_Variables;

	char m_XYZMap[3];
	enum class Mapping { X, Y, Z, };
	char GetMapping(Mapping map) const { return m_XYZMap[static_cast<char>(map)]; }

	void ReadDataSize(FileReader &reader, ReadBucket::LineVector* out);
private:
	std::auto_ptr<CLIGuiHandler> m_GuiHandler;
	SharedProject m_Project;
	iDataSeries *m_OutSeries;

//import
	ImportData *m_Import;
};
