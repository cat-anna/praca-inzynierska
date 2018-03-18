/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Log.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "Implementation.h"
#include <iomanip>

namespace VisApp {
namespace Logs {

std::ofstream  *_LogFile = 0;
std::recursive_mutex *_LogFileMutex = 0;

#define LOG_LOCK \
	if(!_LogFileMutex) _LogFileMutex= new std::recursive_mutex();\
	RECURSIVE_LOCK_EX(*_LogFileMutex);


void LogMgt::OpenLog() {
	//LOG_LOCK
	if(_LogFile) return;
	_LogFile = new std::ofstream("VisApp.log", std::ios::binary | std::ios::out | std::ios::app);
	if(_LogFile->tellp() < 1024) {
		_LogFile->seekp(0);
#pragma warning ( suppress: 4309 )
		const char bom[] = { 0xff, 0xfe };
		_LogFile->write(bom, sizeof(bom));
		_LogFile->flush();
	}
	std::wstringstream wss;
	wss	<< L"\n\n"
		<< L"-------====New session====-------\n"
		<< BUILD_CONFIGURATION << " " << BUILD_ARCH << " at " << __TIMESTAMP__
		<< "\n";
	PushRawLine(wss.str());
}

void LogMgt::CloseLog() {
	//LOG_LOCK
	if(!_LogFile) return;
	_LogFile->flush();
	_LogFile->close();
	delete _LogFile;
	_LogFile = 0;
}

void LogMgt::PushRawLine(const std::wstring &Line) {
//	LOG_LOCK
	if(!_LogFile) OpenLog();
	_LogFile->write((char*)Line.c_str(), sizeof(wchar_t) * Line.length());
	_LogFile->write((char*)L"\n", 2);
	_LogFile->flush();
	//(*_LogFile) << Line.c_str() << std::endl << std::flush;
}

LogMgt::LogMgt(void) { }

LogMgt::~LogMgt(void) { }

//-----------------------------------------------------------------------------

//using namespace boost::chrono;
using namespace boost::gregorian;
using namespace boost::posix_time;

const wchar_t *LogTypeNames[] = {
	L"NORM",
	L"CRIT",
	L"ERROR",
	L"WARN",
	L"HINT",
	L"DEBUG",
	L"?",
	L"?",
	L"?",
};

BasicLogLine& BasicLogLine::add(const std::wstring &t) {
	(*m_Line) << t;
	return *this;
}

BasicLogLine& BasicLogLine::add(const std::string &t) {
	(*m_Line) << t.c_str();
	return *this;
}

BasicLogLine::BasicLogLine(unsigned line, const char* file, const char* func) {
	//insert line header
	m_dothrow = false;
	m_Type = LogType::Normal;
	m_Stamp = new std::wstring();
	m_Line = new std::wstringstream();	
	(*m_Line)  << std::setprecision(2);
	std::wstringstream wss;

	{
		const char *f = strrchr(file, L'\\');
		if(f) file = f + 1;
	}
	wchar_t wbuffer[512];
	char cbuffer[256];

#ifdef _DEBUG
	std::wstring name = OS::CurrentProcExeName();
	const wchar_t *exeName = wcsrchr(name.c_str(), L'\\');
	if(!exeName) exeName = name.c_str();
	else ++exeName;

	swprintf_s(wbuffer, L"[%s:%d@%d]", exeName, OS::CurrentPID(), OS::CurrentTID());
	sprintf_s(cbuffer, "[%s:%d@%s]", file, line, func);
	std::string time = boost::posix_time::to_simple_string(microsec_clock::local_time());
#else
	swprintf_s(wbuffer, L"[%d]", OS::CurrentTID());
	sprintf_s(cbuffer, "[%s:%d]", file, line);
	std::string time = boost::posix_time::to_simple_string(second_clock::local_time());
#endif
	wss << "[" << time.c_str() << "]" << wbuffer << cbuffer;

	m_Stamp->swap(wss.str());
}

BasicLogLine::~BasicLogLine() {
	std::wstringstream wss;
	std::wstring str;
	m_Line->str().swap(str);
	wss << *m_Stamp << L"[" << LogTypeNames[static_cast<unsigned>(m_Type)] << L"] " << str;
	LogMgt::PushRawLine(wss.str());
	delete m_Line;
	delete m_Stamp;
	if(m_dothrow)
		throw str;
}

} // namespace Logs
} // namespace VisApp
