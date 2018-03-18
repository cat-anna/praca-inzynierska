/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Implementation.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

//horrible, but working workaround
#include "..\Implementation.h"

#include "MessageQueue.h"
#include "InternalWorker.h"
#include "ManagerImpl.h"

#include <VisApp\include\VisAppOS.h>

#ifndef AddLOG
#define AddLOG(...) AddLog(Debug, __VA_ARGS__) 
#endif
