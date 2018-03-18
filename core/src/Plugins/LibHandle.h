/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/LibHandle.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef LibHandle_H
#define LibHandle_H

namespace VisApp {
namespace Plugins {
namespace OS {

class LibHandle {
public:
 	virtual ~LibHandle();

	virtual void* GetFunctionHandle(const std::string &fname) = 0;
	virtual bool HasFunction(const std::string &name) = 0;

	static bool IsSharedLib(const std::wstring &filename);
	static LibHandle* Open(const std::wstring &filename);

	virtual void ThrowAwayHandle() = 0;// use witch caution
protected:
 	LibHandle();
private: 
};

} //namespace OS 
} //namespace Plugins 
} //namespace VisApp 

#endif
