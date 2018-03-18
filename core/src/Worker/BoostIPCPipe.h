/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/BoostIPCPipe.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef BoostIPCPipe_H
#define BoostIPCPipe_H

namespace Worker { 
namespace Communication { 
#if 0
class BoostIPCPipe : public MessagePipe {
	std::wstring m_Name;
	boost::interprocess::message_queue *m_Queue;
public:
	BoostIPCPipe(const std::wstring &Name, bool Writable = true, bool Readable = true);
	BoostIPCPipe(const std::wstring &Name, unsigned QueueSize, unsigned MessagesCount, bool Writable = true, bool Readable = true);
	virtual ~BoostIPCPipe();

	virtual bool IsFull() const;
	virtual bool IsEmpty() const;
	virtual bool IsDataWaiting() const;

	virtual int WriteMessage(xml_node data);
	virtual int ReadMessage(xml_node data);

	virtual int WriteRawMessage(const std::wstring &in);
	virtual int ReadRawMessage(std::wstring &out);

	virtual const std::wstring& GetPipeID() const;
};
#endif 
} //namespace Communication
} //namespace Worker

#endif
