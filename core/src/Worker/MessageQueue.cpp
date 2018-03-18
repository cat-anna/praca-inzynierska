/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/MessageQueue.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Communication {

MessageQueue::MessageQueue()  {
	char buf[32] = { };
	sprintf_s(buf, "%02x%02x%x", rand()&0xFF, rand()&0xFF, (unsigned)this);
	m_Name = std::wstring(buf, buf + strlen(buf));
	m_Flags |= pf_Good | pf_Writable | pf_Readable;
}

MessageQueue::~MessageQueue() {

}

bool MessageQueue::IsFull() const {
	return false;
}

bool MessageQueue::IsEmpty() const {
	return m_queue.empty();
}

int MessageQueue::WriteMessage(xml_node data){
	if(!IsWritable()) return -1;
	std::wstringstream ss;
	data.print(ss, L"", pugi::format_raw);
	m_queue.push(std::wstring());
	m_queue.back().swap(ss.str());
	return 0;
}

int MessageQueue::ReadMessage(xml_node data){
	if(!IsReadable()) return -1;
	std::wstring str;
	ReadRawMessage(str);
	data.append_buffer(str.c_str(), str.size() * 2);
	return 0;
}

int MessageQueue::WriteRawMessage(const std::wstring &out){
	if(!IsWritable()) return -1;
	m_queue.push(out);
	return 0;
}

int MessageQueue::ReadRawMessage(std::wstring &out){
	if(!IsReadable()) return -1;
	out.swap(m_queue.front());
	m_queue.pop();
	return 0;
}

const std::wstring& MessageQueue::GetPipeID() const {
	return m_Name;
}

} //namespace Communication 
} //namespace Worker 
