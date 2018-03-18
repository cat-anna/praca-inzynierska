/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataChannel.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Project {

#define DataChannelMemoryName L"Data"

struct RangeValues {
	virtual ~RangeValues() { }
	virtual void Save(xml_node node) const = 0;
	virtual void Load(const xml_node node) = 0;
	virtual bool TestType(const Types::DataType &dt)const = 0;
	virtual void Set(const void* mem, unsigned memsize) = 0;
	virtual void Get(void* mem, unsigned memsize) const = 0;
};

template <Types::VariableType VT, Types::DataDimiension VD>
struct RangeValuesImpl : public RangeValues {
	typedef typename Types::DataType::ElementType<VT, VD> BaseElementProps;
	typedef typename Interface::ChannelMemory<VT, VD> ChannelMemory_t;
	typedef typename BaseElementProps::Element_t Element_t;
	typedef typename BaseElementProps::type_t type_t;
	enum { Element_Size = BaseElementProps::Size, };

	typename ChannelMemory_t::RangeValues values;

	RangeValuesImpl(int) { };
/*
	struct MinMaxIndent {
		Element_t value;
		Math::uvec3 location;
	};
	MinMaxIndent Min, Max;
	Element_t VectorMin, VectorMax;
*/

	virtual void Set(const void* mem, unsigned memsize) {
		if(memsize != sizeof(values))
			throw L"Attempt to set range values of different size!";
		memcpy(&values, mem, sizeof(values));
	}

	virtual void Get(void* mem, unsigned memsize) const {
		if(memsize != sizeof(values))
			throw L"Attempt to get range values of different size!";
		memcpy(mem, &values, sizeof(values));
	}

	bool TestType(const Types::DataType &dt) const {
		return dt.Type == VT && dt.Dimiension == VD;
	}

	virtual void Save(xml_node node) const {
		WriteGLMVector(node, L"MinLocation", values.Min.location);
		WriteGLMVector(node, L"MinValues", values.Min.value);
		WriteGLMVector(node, L"MaxLocation", values.Max.location);
		WriteGLMVector(node, L"MaxValues", values.Max.value);
		WriteGLMVector(node, L"VectorMin", values.VectorMin);
		WriteGLMVector(node, L"VectorMax", values.VectorMax);
	}

	virtual void Load(const xml_node node) {
		ReadGLMVector(node, L"MinLocation", values.Min.location);
		ReadGLMVector(node, L"MinValues", values.Min.value);
		ReadGLMVector(node, L"MaxLocation", values.Max.location);
		ReadGLMVector(node, L"MaxValues", values.Max.value);
		ReadGLMVector(node, L"VectorMin", values.VectorMin);
		ReadGLMVector(node, L"VectorMax", values.VectorMax);
	}
};

//-------------------------------------

DataChannel::DataChannel(DataSeries *Owner, const std::wstring &ChannelName, const VisApp::Types::DataType& Type):
		m_Owner(Owner),
		m_ChannelName(ChannelName), 
		m_DataType(Type),
		m_MemPtr(0) {
	m_RangeValues.reset(Types::DataType::DispatchTypeTemplate<RangeValuesImpl, RangeValues, int>(Type, 0));
}

DataChannel::DataChannel(DataSeries *Owner):
		m_Owner(Owner),
		m_ChannelName(L"?"), 
		m_DataType(),
		m_MemPtr(0) {
}

DataChannel::~DataChannel() {
}

//iResource implementation

Interface::iResource* DataChannel::GetOwnerResource() {
	return GetOwnerSeries();
}

//iDataChannel implementation

const std::wstring& DataChannel::GetName() const {
	return m_ChannelName;
}

void DataChannel::SetName(const std::wstring &name) {
	m_ChannelName = name;
}

const VisApp::Types::DataType& DataChannel::GetType() const {
	return m_DataType;
}

void DataChannel::GetSize(Math::uvec3 &size) const {
	GetOwnerSeries()->GetSize(size);
}

SharedMemoryPtr DataChannel::GetMemoryImpl(Types::VariableType RequestedType, Types::DataDimiension size) {
	auto series = GetOwnerSeries();
	auto store = series->GetOwnerStore();

	auto status = series->GetStatus();

	if(status == Interface::iDataSeries::eSeriesStatus::New) {
		m_MemPtr = GetOwnerSeries()->GetOwnerStore()->AllocateMemory(this, DataChannelMemoryName, GetByteSize());
	} else
		m_MemPtr = GetOwnerSeries()->GetOwnerStore()->OpenMemory(this, DataChannelMemoryName);

	return m_MemPtr;
}

Interface::iDataSeries* DataChannel::GetSeries() const {
	return m_Owner;
}

void DataChannel::SetRangeValues(const Types::DataType &dt, const void* mem, unsigned memsize) {
	if(!m_RangeValues.get()) return;
	if(!m_RangeValues->TestType(dt)) {
		AddLog(Warning, L"Attempt to overwrite DataChannel range values with wrong input data type!");
		return;
	}
	if(!m_Owner->CanBeModiffied()) {
		AddLog(Warning, L"Attempt to overwrite DataChannel range values!");
		return;
	}
	m_RangeValues->Set(mem, memsize);
}

void DataChannel::GetRangeValues(const Types::DataType &dt, void* mem, unsigned memsize) const {
	if(!m_RangeValues.get())
		return;
	if(!m_RangeValues->TestType(dt)) {
		AddLog(Warning, L"Attempt to read DataChannel range values with wrong output data type!");
		return;
	}
	m_RangeValues->Get(mem, memsize);
}

//public functions

size_t DataChannel::ElementCount() const {
	Math::uvec3 size;
	GetOwnerSeries()->GetSize(size);
	return size[0] * size[1] * (size[2] > 0 ? size[2] : 1);
}

size_t DataChannel::GetByteSize() const {
	return m_DataType.BytesPerElement() * ElementCount();
}

bool DataChannel::LoadMeta(xml_node MetaIn) {
	LoadInfo(MetaIn);
	m_ChannelName = MetaIn.child(L"ChannelName").text().as_string();
	m_DataType.Load(MetaIn.child(L"Type"));
	m_RangeValues.reset(Types::DataType::DispatchTypeTemplate<RangeValuesImpl, RangeValues, int>(m_DataType, 0));
	m_RangeValues->Load(MetaIn.child(L"RangeValues"));
	return true;
}

bool DataChannel::SaveMeta(xml_node MetaOut) {
	SaveInfo(MetaOut);
	MetaOut.append_child(L"ChannelName").text() = m_ChannelName.c_str();
	m_DataType.Save(MetaOut.append_child(L"Type"));
	if(m_RangeValues.get())
		m_RangeValues->Save(MetaOut.append_child(L"RangeValues"));
	return true;
}

} //namespace Project
} //namespace VisApp
