/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/ImportTable.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#ifndef ImportTable_H
#define ImportTable_H
#pragma unmanaged
//using Core::Memory::ShTab;
typedef unsigned __int32  uint32;

struct VariableDescriptor;

using VisApp::Interface::ChannelMemory;
using VisApp::Interface::ChannelMemoryBase;

class ImportTable {
public:
	ImportTable(const VariableDescriptor* vd):
			m_Variable(vd) { }
	virtual ~ImportTable() { }

	virtual void PutValue(const VisApp::Math::uvec3 &pos, const float_t *value, index_t Size) = 0;
	virtual ChannelMemoryBase& GetMemory() = 0;
	virtual unsigned GetValuesCount() const = 0;

	const std::wstring &GetLayerName() const { return m_LayerName; }
	const VariableDescriptor* GetDescriptor() const { return m_Variable; }
protected:
	VisApp::Math::uvec2 m_LayerSize;
	std::wstring m_LayerName;
	const VariableDescriptor *m_Variable;
};

using VisApp::Types::VariableType;
using VisApp::Types::DataDimiension;

template <VariableType VT, DataDimiension VD>
class TypedImportTable : public ImportTable {
public:
	typedef typename ChannelMemory<VT, VD> Mem_t;

	TypedImportTable(VariableDescriptor* vd):
			ImportTable(vd), 
			m_Memory(vd->DataChannel->GetMemory<VT, VD>()) {
	}

	~TypedImportTable() { 
		m_Variable->DataChannel->SetRangeValues<VT, VD>(m_RangeValues);
	}

	enum {
		LENGTH = Mem_t::Element_Size,
	};

	virtual void PutValue(const VisApp::Math::uvec3 &pos, const float_t *value, index_t Size) {
		Size = VisApp::Math::min(Size, (index_t)LENGTH);
		auto &itm = m_Memory.at(pos);
		for(unsigned i = 0; i < Size; ++i)
			itm[i] = static_cast<Mem_t::type_t>(value[i]);
		m_RangeValues.Push(itm, pos);
	}
	 
	virtual unsigned GetValuesCount() const { return LENGTH; }
	virtual ChannelMemoryBase& GetMemory() { return m_Memory; }
protected:
	typename Mem_t::RangeValues m_RangeValues;
	Mem_t m_Memory;
};

#endif
