/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/Interface.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Interface {

iProject::~iProject() { }
//-------------------------------------------------------------------------
iDataStore::~iDataStore() { }
//-------------------------------------------------------------------------
iDataSeries::~iDataSeries() { }
//-------------------------------------------------------------------------
iDataChannel::~iDataChannel() { }
//-------------------------------------------------------------------------
iManager::~iManager() { }
//-------------------------------------------------------------------------
iCoreObserver::~iCoreObserver() { }
//-------------------------------------------------------------------------
iOGLContext::~iOGLContext() { }
//-------------------------------------------------------------------------
iVisualizer::~iVisualizer() { }
//-------------------------------------------------------------------------

//------------------------------------------------------------------------
ChannelMemoryBase::ChannelMemoryBase(std::shared_ptr<Interface::MemoryPtr> pointer, iDataChannel *Channel): m_Memory(pointer), m_Channel(Channel) {
	m_Channel->GetSize(m_Size);
	GetMemory();
}
ChannelMemoryBase::~ChannelMemoryBase() { }
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

}
}
