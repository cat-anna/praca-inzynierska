/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginExec.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

PluginExec::PluginExec(SharedPluginBase Owner): Worker::Mgt::Executable(), m_Plugin(Owner) {
	SetName(Owner->GetName());
}

PluginExec::~PluginExec() {
}

void PluginExec::AfterRun() {
	m_Plugin->AfterRun();		
}

void PluginExec::BeforeRun() {
	m_Plugin->BeforeRun();		
}

void PluginExec::Run() {
	m_Plugin->Run();		
}

} //namespace Plugins
} //namespace VisApp 
