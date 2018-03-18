/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataSeries.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef DataSeries_H
#define DataSeries_H

namespace VisApp {
namespace Project {

class DataStore;

class DataSeries : public VisApp::Interface::iDataSeries {
public:
	DataSeries(DataStore *Owner, const std::wstring& SeriesName, const Math::uvec3 &size);
	DataSeries(DataStore *Owner);
	virtual ~DataSeries();
//iResource implementation
	virtual iResource* GetOwnerResource();
 	virtual const std::wstring& GetName() const;
//iDataSeries implementation
	virtual eSeriesStatus GetStatus() const;
	virtual void SetStatus(eSeriesStatus NewStatus);
	virtual void SetName(const std::wstring &name);
	virtual void GetSize(Math::uvec3 &size) const;
	virtual index_t GetChannelCount() const;
	virtual Interface::iDataChannel* GetChannel(index_t ChannelID);
	virtual Interface::iDataChannel* GetChannel(const std::wstring &Name);
	virtual Interface::iDataChannel* AddChannel(const std::wstring& Name, const VisApp::Types::DataType &Type);
	virtual Interface::iProject* GetProject() const;
//public functions
	DataChannel* GetChannelInstance(index_t ChannelID);
	DataChannel* GetChannelInstance(const std::wstring& ChannelName);

	bool CanBeModiffied() const {
		return m_Status == eSeriesStatus::New || m_Status == eSeriesStatus::Importing;
	}

	DataStore* GetOwnerStore() const { return m_Owner; }
	void ChangeStatus(eSeriesStatus NewStatus);
	bool SaveMeta(xml_node MetaOut);
	bool LoadMeta(xml_node MetaIn);

	void RemoveDataChannel(index_t index);
	void RemoveDataChannel(DataChannel *instance);

	const Math::uvec3& GetSize() const { return m_Size; }
private:
	std::wstring m_SeriesName;
	eSeriesStatus m_Status;
	Math::uvec3 m_Size;
	DataStore *m_Owner;
	//mapping is ignored!

	typedef std::shared_ptr<DataChannel> SharedDataChannel;
	typedef std::vector<SharedDataChannel> DataChannelVector;
	DataChannelVector m_DataChannels;
};

} //namespace Project
} //namespace VisApp

#endif
