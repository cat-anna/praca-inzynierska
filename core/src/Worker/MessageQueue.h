/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/MessageQueue.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MessageQueue_H
#define MessageQueue_H

#include <queue>

namespace Worker {
namespace Communication {

class MessageQueue : public MessagePipe {
public:
 	MessageQueue();
 	virtual ~MessageQueue();

	virtual bool IsFull() const;
	virtual bool IsEmpty() const;

	virtual int WriteMessage(xml_node data);
	virtual int ReadMessage(xml_node data);

	virtual int WriteRawMessage(const std::wstring &in);
	virtual int ReadRawMessage(std::wstring &out);

	virtual const std::wstring& GetPipeID() const;
protected:
private: 
	std::queue<std::wstring> m_queue;
	std::wstring m_Name;
};

} //namespace Communication 
} //namespace Worker 

#endif

