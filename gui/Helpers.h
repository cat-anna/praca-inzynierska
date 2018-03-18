/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/Helpers.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Windows::Forms; 

ref class Helpers {
	static System::Drawing::Icon ^_defIcon = nullptr;
public:
	static void ProcessFormIcon(System::Windows::Forms::Form ^f) {
		if(_defIcon == nullptr)
			_defIcon = f->Icon;
		else
			f->Icon = _defIcon;
	}
private:
	static array<String^>^ FileSizeArray = gcnew array<String^> {
		"B", "kB", "MB", "GB", "TB", "??", "??",
	};

public: static String^ FileSizeToString(__int64 len) {
			float flen = static_cast<float>(len);
			int i = 0;
			if(flen < 0) return gcnew String("?");
			while (flen >= 1000) {
				++i;
				flen /= 1024.0f;
			}
			return Convert::ToString((int)flen) + FileSizeArray[i];
		}

public:
	static String^ WorkerStatusToString(Worker::Mgt::WorkerStatus ws) {
		switch (ws) {
		case Worker::Mgt::WorkerStatus::Working: return "Pracuje";
		case Worker::Mgt::WorkerStatus::Paused: return "Pauza";
		case Worker::Mgt::WorkerStatus::Waiting: return "Oczekuje";

		case Worker::Mgt::WorkerStatus::Exited:
		case Worker::Mgt::WorkerStatus::Finished: return "Zakoñczony";

		case Worker::Mgt::WorkerStatus::Broken: return "B³¹d";
		case Worker::Mgt::WorkerStatus::DebugPause: return "Debug pause";

		case Worker::Mgt::WorkerStatus::NoInstance: 
		case Worker::Mgt::WorkerStatus::New: return "Nowy";
		default:
			return "Nieznany";
		}
	}

public: static String^ StringDataPointer2String(const VisApp::Interface::StringDataPointer &src) {
	return ToString(src.ToString());
}

public: static String^ ToString(const std::wstring& str) {
			return gcnew String(str.c_str());
		}
public: static String^ ToString(const char* str) {
			return gcnew String(str);
		}
public: static std::wstring ToString(String^ str) {
			return msclr::interop::marshal_as<std::wstring>(str);
		}
public: static std::wstring ToStdWStr(String^ str) {
			return msclr::interop::marshal_as<std::wstring>(str);
		}
public: static std::wstring ToStdWStr(const wchar_t* str) {
			return std::wstring(str);
		}
public: static std::wstring ToStdWStr(const std::wstring& str) {
			return std::wstring(str);
		}
public: static std::wstring ToStdWStr(const std::string& str) {
			return std::wstring(str.c_str(), str.c_str() + str.length());
		}
public: static std::wstring ToStdWStr(const char* str) {
			return std::wstring(str, str + strlen(str));
		}
public: static String^ ToString(const VisApp::Types::DataType &dt) {
			String ^r = "";
			using VisApp::Types::DataDimiension;
			using VisApp::Types::VariableType;
			switch (dt.Dimiension) {
			case DataDimiension::d1: r = "d1"; break;
			case DataDimiension::d2: r = "d2"; break;
			case DataDimiension::d3: r = "d3"; break;
			};
			r += " ";
			switch (dt.Type) {
			case VariableType::Integer: r += "integer"; break;
			case VariableType::Float: r += "float"; break;
			}
			return r;
		}
};

#include "InputBox.h"

struct LogCaster {
	template<class T>
	static std::wstring cast(T t) { return msclr::interop::marshal_as<std::wstring>(t); }

	static std::wstring cast(const wchar_t *t) { return t; };
	static std::wstring cast(const std::wstring &t) { return t; };
	static std::wstring cast(const char *t) { return std::wstring(t, t + strlen(t)); };
	static std::wstring cast(const std::string &t) { return std::wstring(t.c_str(), t.c_str() + t.length()); };
};

#define _AddLog(T, A)\
	VisApp::Logs::LogMgt::Begin(__LINE__, __FILE__, __FUNCTION__).SetType(VisApp::Logs::LogType::T).add(LogCaster::cast(A))


#define TRY_PROTECT(CODE, USER_MESG, ONERROR)\
try {\
	try { CODE }\
	catch(const wchar_t *msg) { throw LogCaster::cast(msg); }\
	catch(const char *msg) { throw LogCaster::cast(msg); }\
	catch(const std::wstring& msg) { throw LogCaster::cast(msg); }\
	catch(const std::string& msg) { throw LogCaster::cast(msg); }\
	catch(String^ msg) { throw LogCaster::cast(msg); }\
	catch(...) { throw 0; }\
}\
catch (const std::wstring& mesg) {\
	_AddLog(Error, mesg);\
	MessageBox::Show(this, USER_MESG, \
			Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);\
	ONERROR\
}\
catch(...) {\
	_AddLog(CriticalError, L"Critical error: Unknown exception type!");\
	MessageBox::Show(this, USER_MESG, \
			Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);\
	ONERROR\
}
