/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Implementation.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#pragma warning ( disable: 4966 )

#include <VisApp\include\Tools\ActionQueue.h>

//global VisApp header
#include <VisApp\include\VisApp.h>

#include "Types\Types.h"

typedef std::lock_guard<std::mutex> scoped_lock;
#define LOCK_FUN std::lock_guard<std::mutex> Lock(m_mutex);
#define LOCK_FUN_EX(M) std::lock_guard<std::mutex> Lock(M);
#define RECURSIVE_LOCK_EX(M) std::lock_guard<std::recursive_mutex> Lock(M);
#define RECURSIVE_LOCK std::lock_guard<std::recursive_mutex> Lock(m_mutex); 

namespace Convert {

inline std::wstring s2ws(const std::string& str) {
     typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(str);
}

inline std::string ws2s(const std::wstring& wstr) {
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

}

#include "Config.h"

//#define DEBUG_VCAMERA

//Core headers

#include "Worker\Implementation.h"

#include "Project\Project.h"

#include "Project\Memory.h"
#include "Project\MemoryMgt.h"

#include "Project\DataChannel.h"
#include "Project\DataSeries.h"
#include "Project\DataStore.h"

#include "Renderer\nRenderer.h"

#include "Impl\CoreManager.h"
#include "Impl\Facedes.h"

#include "Plugins\nPlugins.h"
