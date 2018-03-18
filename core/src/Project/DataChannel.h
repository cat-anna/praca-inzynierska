/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataChannel.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef DataChannel_H
#define DataChannel_H

namespace VisApp {
namespace Project {

class DataSeries;
class DataChannel;
struct RangeValues;

class DataChannel : public VisApp::Interface::iDataChannel {
public:
	DataChannel(DataSeries *Owner, const std::wstring &ChannelName, const VisApp::Types::DataType& Type);
	DataChannel(DataSeries *Owner);
	virtual ~DataChannel();
//iResource implementation
	virtual iResource* GetOwnerResource();
	virtual const std::wstring& GetName() const;
//iDataChannel implementation
	virtual void SetName(const std::wstring &name);
	virtual const VisApp::Types::DataType& GetType() const;
	virtual void GetSize(Math::uvec3 &size) const;
	virtual Interface::iDataSeries* GetSeries() const;
protected:
	virtual Interface::SharedMemoryPtr GetMemoryImpl(Types::VariableType RequestedType, Types::DataDimiension size);
	virtual void SetRangeValues(const Types::DataType &dt, const void* mem, unsigned memsize);
	virtual void GetRangeValues(const Types::DataType &dt, void* mem, unsigned memsize) const;
public:
//public functions
	DataSeries* GetOwnerSeries() const { return m_Owner; }
	bool SaveMeta(xml_node MetaOut);
	bool LoadMeta(xml_node MetaIn);

	size_t GetByteSize() const;
	size_t ElementCount() const;
private:
	DataSeries *m_Owner;
	std::wstring m_ChannelName;
	VisApp::Types::DataType m_DataType;
	std::auto_ptr<RangeValues> m_RangeValues;

	Interface::SharedMemoryPtr m_MemPtr;
};

} //namespace Project
} //namespace VisApp

#endif
