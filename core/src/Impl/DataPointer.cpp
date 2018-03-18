/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/DataPointer.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Interface {



StringDataPointer::StringDataPointer(const iDataChannel *channel) {
	auto series = channel->GetSeries();
	m_ProjectRUID = series->GetProject()->GetRawRUID();
	m_SeriesRUID = series->GetRawRUID();
	m_ChannelRUID = channel->GetRawRUID();
}

StringDataPointer::StringDataPointer() {
	m_ProjectRUID = L"";
	m_SeriesRUID = L"";
	m_ChannelRUID = L"";
}

StringDataPointer::~StringDataPointer() {
}

std::wstring StringDataPointer::ToString() const{
	try {
		std::wstringstream ss;
		DataPointer dp = Translate();
		ss << L"(";
#ifdef CONFIG_MULTIPROJECT
		ss << dp.Project->GetName() << ";";
#endif
		ss << dp.Series->GetName() << ";";
		ss << dp.Channel->GetName();
		ss << L")";
		return ss.str();
	}
	catch(...) {
		return L"(?)";
	}
}
/*
const std::wstring& StringDataPointer::GetProjectName() const {
	auto *ptr = iResource::GetResource<iDataChannel>(m_ProjectRUID);
	if(!ptr) throw NoSuchDataSourceException();
	return ptr->GetName();
}

const std::wstring& StringDataPointer::GetSeriesName() const {
	auto *ptr = iResource::GetResource<iDataSeries>(m_SeriesRUID);
	if(!ptr) throw NoSuchDataSourceException();
	return ptr->GetName();
}

const std::wstring& StringDataPointer::GetChannelName() const {
	auto *ptr = iResource::GetResource<iProject>(m_ProjectRUID);
	if(!ptr) throw NoSuchDataSourceException();
	return ptr->GetName();
}*/

bool StringDataPointer::LoadFromXML(const xml_node node) {
	m_ProjectRUID = node.attribute(L"Project").as_string(L"");
	m_SeriesRUID = node.attribute(L"Series").as_string(L"");
	m_ChannelRUID = node.attribute(L"Channel").as_string(L"");
	return !m_ProjectRUID.empty() && !m_SeriesRUID.empty() && !m_ChannelRUID.empty();
}

bool StringDataPointer::SaveToXML(xml_node node) const {
	node.append_attribute(L"Project") = m_ProjectRUID.c_str();
	node.append_attribute(L"Series") = m_SeriesRUID.c_str();
	node.append_attribute(L"Channel") = m_ChannelRUID.c_str();
	return true;
}

void StringDataPointer::Set(const std::wstring &Project, const std::wstring& Series, const std::wstring &Channel) {
	auto proj = VisApp::Interface::iProjectMgt::GetInstance()->GetProject(Project);
	if(!proj) return;
	auto store = proj->GetDataStore();
	auto s = store->GetDataSet(Series);
	if(!s) throw NoSuchDataSourceException();
	auto ch = s->GetChannel(Channel);
	if(!ch) throw NoSuchDataSourceException();
	m_ProjectRUID = proj->GetRawRUID();
	m_SeriesRUID = s->GetRawRUID();
	m_ChannelRUID = ch->GetRawRUID();
}

DataPointer StringDataPointer::Translate() const {
	DataPointer result;

	iDataChannel *channel = iResource::GetResource<iDataChannel>(m_ChannelRUID);
	if(!channel)
		throw NoSuchDataSourceException();

	result.Channel = channel;
	result.Series = channel->GetSeries();
	result.Project = result.Series->GetProject();

	return result;
}

bool DataPointer::IsReady() const {
	return IsOk() && Series->GetStatus() == VisApp::Interface::iDataSeries::eSeriesStatus::Ok;
}

bool DataPointer::IsOk() const {
	return Project && Series && Channel;
}

}
}