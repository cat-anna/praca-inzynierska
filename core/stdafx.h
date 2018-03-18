/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/stdafx.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#include <cstdio>
#include <iomanip>
#include <stdexcept>
#include <queue>
#include <type_traits>

#include <boost\ptr_container\ptr_container.hpp>
#include <boost\atomic.hpp>
#include <boost\date_time.hpp>

#include <locale>
#include <codecvt>

#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

//#define GLEW_MX
#include <gl\glew.h>
#define GLM_FORCE_RADIANS
#include <glm\glm\glm.hpp>

#include <unordered_map>

#include <boost\filesystem.hpp>

#include <boost\interprocess\managed_shared_memory.hpp>
#include <boost\ptr_container\ptr_container.hpp>
#include <boost\container\flat_map.hpp>
#include <boost\algorithm\string\replace.hpp>
