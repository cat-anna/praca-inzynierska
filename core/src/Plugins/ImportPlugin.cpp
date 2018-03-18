/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/ImportPlugin.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

#include <fstream>

namespace VisApp {
namespace Plugins {

PluginType ImportPlugin::GetPluginClassType() {
	return PluginType::Import;
}

ImportPlugin::ImportPlugin(): 
		PluginBase(GetPluginClassType()), 
		m_LastPreprocessResult(PreprocessResult::FunctionNotSupported),
		m_FileSize(-1),
		m_DataSize(0) {
}

ImportPlugin::~ImportPlugin() {
	//nothing here
}

void ImportPlugin::SetSourceFile(const std::wstring &file) {
	m_SrcFile = file;
	if(GetLastPreporcessResult() != PreprocessResult::FunctionNotSupported)
		SetPreporcessResult(PreprocessResult::FileNotPreprocessed);
}

const std::wstring& ImportPlugin::GetSrcFile() const {
	return m_SrcFile;
}

bool ImportPlugin::CheckFile() {
	m_FileSize = 0;
	std::wifstream file;
	file.open(m_SrcFile, std::ios::in | std::ios::binary);
	if(!file) return false;
	file.seekg(0, std::ios::end);
	m_FileSize = static_cast<decltype(m_FileSize)>(file.tellg());
	return true;
}

PreprocessResult ImportPlugin::PreprocessFile() {
	return SetPreporcessResult(PreprocessResult::FunctionNotSupported);
}

PreprocessResult ImportPlugin::GetLastPreporcessResult() const {
	return m_LastPreprocessResult;
}

PreprocessResult ImportPlugin::SetPreporcessResult(PreprocessResult value) {
	return m_LastPreprocessResult = value;
}

void ImportPlugin::SetDataSize(const glm::uvec3& size3) {
	m_DataSize = size3;
}

__int64 ImportPlugin::GetFileSize() const {
	return m_FileSize;
}

const glm::uvec3&  ImportPlugin::GetDataSize3() const {
	return m_DataSize;
}

glm::uvec2 ImportPlugin::GetDataSize2() const {
	return glm::uvec2(m_DataSize[0], m_DataSize[1]);
}

const std::wstring& ImportPlugin::GetSeriesName() const {
	return m_SeriesName;
}

const std::wstring& ImportPlugin::GetProjectName() const {
	return m_ProjectName;
}

void ImportPlugin::SetProjectName(const std::wstring &ProjName, const std::wstring &SeriesName) {
	m_ProjectName = ProjName;
	m_SeriesName = SeriesName;
}

/*

enum class PreprocessResult {
	Ok, FileNotFound, WrongFileType, SyntaxError, UnknownError, FunctionNotSupported, FileNotPreprocessed,
};

class PLUGIN_API ImportPlugin : public PluginBase {
public:
protected:

private:
	ImportPlugin(const ImportPlugin&);//=delete;
	ImportPlugin& operator=(const ImportPlugin&);//=delete;

	std::wstring m_SrcFile;
	size_t m_FileSize;
	glm::uvec4 m_DataSize;
	PreprocessResult m_LastPreprocessResult;
};

*/

}// namespace Plugins
}// namespace VisApp
