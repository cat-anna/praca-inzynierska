/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataSeries.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Project {

DataSeries::DataSeries(DataStore *Owner, const std::wstring& SeriesName, const Math::uvec3 &size):
		m_Owner(Owner),
		m_SeriesName(SeriesName),
		m_Status(eSeriesStatus::New),
		m_Size(size) {
}

DataSeries::DataSeries(DataStore *Owner):
		m_Owner(Owner),
		m_SeriesName(L"?"),
		m_Status(eSeriesStatus::New),
		m_Size() {
}

DataSeries::~DataSeries() {
}

//iResource implementation
Interface::iResource* DataSeries::GetOwnerResource() {
	return GetOwnerStore()->GetOwnerProject();
}

//iDataSeries implementation

Interface::iDataSeries::eSeriesStatus DataSeries::GetStatus() const {
	return m_Status;
}

const std::wstring& DataSeries::GetName() const {
	return m_SeriesName;
}

void DataSeries::SetName(const std::wstring &name) {
	m_SeriesName = name;
}

void DataSeries::GetSize(Math::uvec3 &size) const {
	size = m_Size;
}

index_t DataSeries::GetChannelCount() const {
	return m_DataChannels.size();
}

Interface::iDataChannel* DataSeries::GetChannel(index_t ChannelID) {
	return GetChannelInstance(ChannelID);
}

Interface::iDataChannel* DataSeries::GetChannel(const std::wstring &Name) {
	return GetChannelInstance(Name);
}

Interface::iDataChannel* DataSeries::AddChannel(const std::wstring& Name, const VisApp::Types::DataType &Type) {
	auto ch = new DataChannel(this, Name, Type);
	m_DataChannels.push_back(SharedDataChannel(ch));
	Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreNotification::ChannelChanged);
	AddLog(Hint, L"Added data channel " << Name << L" to series " << GetName())
	return ch;
}

void DataSeries::SetStatus(eSeriesStatus NewStatus) {
	ChangeStatus(NewStatus);
}

Interface::iProject* DataSeries::GetProject() const {
	return m_Owner->GetOwnerProject();
}

//public functions

void DataSeries::RemoveDataChannel(index_t index) {
	if(index >= m_DataChannels.size()) return;
	auto ch = m_DataChannels[index];
	m_DataChannels.erase(m_DataChannels.begin() + index);
	GetOwnerStore()->GetMemMgt().RelaseResourceMemory(ch.get());
}
	
void DataSeries::RemoveDataChannel(DataChannel *instance) {
	auto it = std::find_if(m_DataChannels.begin(), m_DataChannels.end(), [instance] (SharedDataChannel &i)  {
		return i.get() == instance;
	});

	if(it == m_DataChannels.end())
		return;
	GetOwnerStore()->GetMemMgt().RelaseResourceMemory(instance);
	m_DataChannels.erase(it);
};

DataChannel* DataSeries::GetChannelInstance(index_t index) {
	if(index >= m_DataChannels.size()) return 0;
	return m_DataChannels[index].get();
}

DataChannel* DataSeries::GetChannelInstance(const std::wstring &Name) {
	for(auto &it: m_DataChannels) 
		if(it->GetName() == Name)
			return it.get();
	return 0;
}

void DataSeries::ChangeStatus(eSeriesStatus NewStatus) {
	if(m_Status == NewStatus) return;
	Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreNotification::SeriesChanged);
	m_Status = NewStatus;
}

bool DataSeries::LoadMeta(xml_node MetaIn) {
	LoadInfo(MetaIn);
	m_SeriesName = MetaIn.child(L"Name").text().as_string(L"?");
	
	xml_node Size = MetaIn.child(L"Size");
	m_Size[0] = Size.attribute(L"X").as_uint();
	m_Size[1] = Size.attribute(L"Y").as_uint();
	m_Size[2] = Size.attribute(L"Z").as_uint();

	eSeriesStatus st = (eSeriesStatus)MetaIn.child(L"State").text().as_uint((unsigned)eSeriesStatus::Broken);

	xml_node Channels = MetaIn.child(L"Channels");
	for(auto it = Channels.child(L"Item"); it; it = it.next_sibling(L"Item")) {
		auto ch = new DataChannel(this);
		
		if(!ch->LoadMeta(it)) {
			const wchar_t *name = it.child(L"Name").text().as_string(L"?");
			AddLog(Hint, L"Unable to load data channel " << name << L" for series " << GetName())
			Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error)
					<< L"B³¹d wczytywania kana³u danych " << name << " dla serii danych " << GetName();
			delete ch;
			return false;
		}
		m_DataChannels.push_back(SharedDataChannel(ch));
		AddLog(Hint, L"Loaded data channel " << ch->GetName() << L" for series " << GetName())
	}

	if(st != eSeriesStatus::Ok) {
		AddLog(Warning, L"Loaded series is not in good shape!");
		Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error)
			<< L"Seria " << GetName() << L" jest uszkodzona!";
		SetStatus(eSeriesStatus::Broken);
	} else
		SetStatus(eSeriesStatus::Ok);

	return true;
}

bool DataSeries::SaveMeta(xml_node MetaOut) {
	SaveInfo(MetaOut);
	MetaOut.append_child(L"Name").text() = m_SeriesName.c_str();

	xml_node Size = MetaOut.append_child(L"Size");
	Size.append_attribute(L"X") = m_Size[0];
	Size.append_attribute(L"Y") = m_Size[1];
	Size.append_attribute(L"Z") = m_Size[2];

	MetaOut.append_child(L"State").text() = (unsigned)m_Status;
	
	xml_node Channels = MetaOut.append_child(L"Channels");
	for(auto &i: m_DataChannels) {
		xml_node Channel = Channels.append_child(L"Item");
		i->SaveMeta(Channel);
	}
	return true;
}

} //namespace Project
} //namesoace VisApp
