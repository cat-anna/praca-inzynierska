/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/LibHandle.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

namespace VisApp {
namespace Plugins {
namespace OS {

class WinDll : public LibHandle {
public:
	void* GetFunctionHandle(const std::string &fname) {
		return GetProcAddress(m_h, fname.c_str());
	}
	WinDll() : m_h(NULL), m_DoDel(true) { };
	~WinDll() {
		if(m_h && m_DoDel)
			FreeLibrary(m_h);
	};

	bool HasFunction(const std::string &name) {
		return GetProcAddress(m_h, name.c_str()) != NULL;
	}

	void Open(const std::wstring &filename) {
		m_h = LoadLibraryW(filename.c_str());
		DWORD err = GetLastError();
		if(m_h == NULL) throw false;
	}

	void ThrowAwayHandle() {
		m_DoDel = false;
	}
private:
	HMODULE m_h;
	bool m_DoDel;
};

bool LibHandle::IsSharedLib(const std::wstring &filename) {
	std::wstring fn = filename;
	static const std::wstring ext = L".dll";
	std::transform(fn.begin(), fn.end(), fn.begin(), ::tolower);
	std::wstring::size_type pos = fn.rfind(ext);
	if(pos == std::wstring::npos) return false;
	std::wstring::size_type delta = fn.length() - pos;
	if(delta > ext.length()) return false;
	return true;
}

LibHandle* LibHandle::Open(const std::wstring &filename) {
	WinDll *h = new WinDll();
	try {
		h->Open(filename);
		return h;
	} 
	catch(...) {
		delete h;
		return 0;
	}
}

//-----------------------------------------

LibHandle::LibHandle() {
}

LibHandle::~LibHandle() {
}

} //namespace OS 
} //namespace Plugins 
} //namespace VisApp 

