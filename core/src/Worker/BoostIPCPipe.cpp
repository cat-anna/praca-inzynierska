/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/BoostIPCPipe.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
//because of boost annoying warnings
#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4503 )

#include <stdafx.h>
#include "Implementation.h"

namespace Worker { 
namespace Communication { 
#if 0
using namespace boost::interprocess;

enum {
	BoostIPCPipe_IsOwner		= 0x100000,
};
 
BoostIPCPipe::BoostIPCPipe(const std::wstring &Name, bool Writable, bool Readable) : 
		MessagePipe(),
		m_Name(Name),
		m_Queue(0) {
	try {//TODO
		const std::string charname(Name.begin(), Name.end() );
		m_Queue = new message_queue(open_only_t(), charname.c_str());
   }
   catch(interprocess_exception &) {
   }
	m_Flags |= pf_Good;
	if(Writable) m_Flags |= pf_Writable;
	if(Readable) m_Flags |= pf_Readable;
}

BoostIPCPipe::BoostIPCPipe(const std::wstring &Name, unsigned QueueSize, unsigned MessagesCount, bool Writable, bool Readable) : 
		MessagePipe(),
		m_Name(Name),
		m_Queue(0) {
	try {//TODO
		const std::string charname( Name.begin(), Name.end() );
		m_Queue = new message_queue(create_only, charname.c_str(), MessagesCount, QueueSize);
#ifdef _DEBUG
		boost::mutex lock;
		lock.lock();
		std::ofstream dbg(BUILDING_PROJECT "_boost_open_pipes.dbg", std::ios::out | std::ios::app);
		dbg << "open "<< charname << " " << (MessagesCount * QueueSize) << std::endl << std::flush;
		dbg.close();
		lock.unlock();
#endif
   }
   catch(interprocess_exception &ex) {
	   m_Name += L"_create_err";
	   std::wofstream(m_Name.c_str()) << ex.what() << std::flush;
   }

	m_Flags |= pf_Good | BoostIPCPipe_IsOwner;
	if(Writable) m_Flags |= pf_Writable;
	if(Readable) m_Flags |= pf_Readable;
}

BoostIPCPipe::~BoostIPCPipe() {
	if(m_Flags & BoostIPCPipe_IsOwner) {
		const std::string charname( m_Name.begin(), m_Name.end() );
	//	while(!
			bool succ = message_queue::remove(charname.c_str());
#ifdef _DEBUG
		boost::mutex lock;
		lock.lock();
		std::ofstream dbg(BUILDING_PROJECT "_boost_open_pipes.dbg", std::ios::out | std::ios::app);
		dbg << std::boolalpha << "close "<< charname << " " << succ << std::endl << std::flush;
		dbg.close();
		lock.unlock();
#endif

		//	)
		//	boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	}
	delete m_Queue;
}

bool BoostIPCPipe::IsFull() const {
	return false;//return m_Queue->get_num_msg() == m_Queue->get_max_msg();
}

bool BoostIPCPipe::IsEmpty() const {
	return m_Queue->get_num_msg() == 0;
}

int BoostIPCPipe::WriteMessage(xml_node data){
	if(!IsWritable()) return -1;
	std::wstringstream ss;
	data.print(ss, L"", pugi::format_raw);
	return WriteRawMessage(ss.str());
}

int BoostIPCPipe::ReadMessage(xml_node data){
	if(!IsReadable()) return -1;
	std::wstring str;
	ReadRawMessage(str);
	data.append_buffer(str.c_str(), str.size() * 2);
	return 0;
}

int BoostIPCPipe::WriteRawMessage(const std::wstring &out){
	if(!IsWritable()) return -1;
	try {//TODO
		size_t s = (out.size() + 1) * 2;
		m_Queue->send(out.c_str(), s, 0);	
		//m_Queue->send(L"tst", 4*2, 0);
	}
   catch(interprocess_exception &ex) {
	   std::wofstream(L"send") << ex.what() << std::flush;
   }

	return 0;
}

int BoostIPCPipe::ReadRawMessage(std::wstring &out){
	if(!IsReadable()) return -1;
	out.resize(m_Queue->get_max_msg_size() / 2);
	unsigned __int32 priority;
	size_t recvd_size;
	m_Queue->receive((wchar_t*)out.c_str(), (out.size() + 1) * 2, recvd_size, priority);
	return 0;
}

const std::wstring& BoostIPCPipe::GetPipeID() const{
	return m_Name;
}
#endif
} //namespace Communication
} //namespace Worker
