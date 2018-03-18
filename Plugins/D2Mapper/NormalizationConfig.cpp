/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/NormalizationConfig.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "Processor.h"

namespace NormConfig {

NormConf::NormConf(OutMode algo, NormalizeMode Norm, const NormInfo &inf) :
		Alogrithm(algo), Normalization(Norm), Info(inf) {
}

//--------------------------------------------------------

struct NormConfTableImpl;
NormConfTableImpl *NormTable = 0;
NormConfTable::NormConfVector NormConfTable::_table;

using namespace VisApp::Types;

struct NormalizationDescription {
	void Add(NormalizeMode Mode, VisApp::Types::DataType &tout, bool s, const wchar_t *n, const wchar_t *d) {
		NormInfo i;
		i.Name = n;
		i.Description = d;
		i.Sections = s;
		m_InfoTable.insert(std::make_pair(Mode, i));
	}

	NormalizationDescription() {
#define _add(A, T, ...) Add(NormalizeMode::A, DataType::T, __VA_ARGS__)
		_add(DirectValue,				UnknownUnknown(),	false,	L"Brak",															L"");
		_add(Length,					D1Float(),			false,	L"D³ugoœæ wektora",													L"");
		_add(LengthSections,			UnknownUnknown(),	true,	L"D³ugoœæ wektora z podzia³em na sekcje",							L"");
		_add(VectorNormalize,			UnknownFloat(),		false,	L"Normalizacja wektora",											L"");
//		_add(VectorNormalizeSections,	UnknownUnknown(),	true,	L"Normalizacja wektora z podzia³em na sekcje",						L"");
		_add(LengthMinMax,				D1Float(),			false,	L"D³ugoœæ wektora w zakresie min/max",								L"");
		_add(LengthMinMaxSections,		D1Integer(),		true,	L"D³ugoœæ wektora w zakresie min/max z podzia³em na sekcje",		L"");
		_add(ValuesMinMax,				UnknownFloat(),		false,	L"Wartoœci wektora w ich zakresach min/max",						L"");
		_add(ValuesMinMaxSections,		UnknownInteger(),	true,	L"Wartoœci wektora w ich zakresach min/max z podzia³em na sekcje",	L"");
#undef _add
	}

	const NormInfo& operator[](NormalizeMode Mode) {
		return m_InfoTable[Mode];
	}
private:
	std::map<NormalizeMode, NormInfo> m_InfoTable;
};

struct NormConfTableImpl : public NormConfTable {
	NormalizationDescription NormDesc;

	struct Mod {
		NormConf &handle;
		Mod(NormConf &h): handle(h) { };
		Mod& AddType(VisApp::Types::DataType &tin) {
			handle.AllowedTypes.AddFilter(tin);
			return *this;
		}
	};

	Mod Add(OutMode algo, NormalizeMode Norm) {
		auto &info = NormDesc[Norm];
		_table.push_back(NormConf(algo, Norm, info));
		return Mod(_table.back());
	}

	NormConfTableImpl(){
#define _add(O, N) Add(OutMode::O, NormalizeMode::N)
		_add(Isolines, DirectValue).AddType(DataType::D1Unknown());
		_add(Isolines, Length).AddType(DataType::UnknownUnknown());
	//	_add(Isolines, LengthSections).AddType(DataType::UnknownUnknown());
	//	_add(Isolines, VectorNormalize).AddType(DataType::D1Unknown());
	//	_add(Isolines, VectorNormalizeSections).AddType(DataType::UnknownUnknown());
	//	_add(Isolines, LengthMinMax).AddType(DataType::D1Unknown());
		_add(Isolines, LengthMinMaxSections).AddType(DataType::UnknownUnknown());
	//	_add(Isolines, ValuesMinMax).AddType(DataType::D1Unknown());
	//	_add(Isolines, ValuesMinMaxSections).AddType(DataType::D1Unknown());

		_add(Map, DirectValue).AddType(DataType::D1Integer()).AddType(DataType::UnknownFloat());
		_add(Map, Length).AddType(DataType::UnknownUnknown());
		_add(Map, LengthSections).AddType(DataType::UnknownUnknown());
		_add(Map, VectorNormalize).AddType(DataType::UnknownUnknown());
//		_add(Map, VectorNormalizeSections).AddType(DataType::UnknownUnknown());
		_add(Map, LengthMinMax).AddType(DataType::UnknownUnknown());
	//	_add(Map, LengthMinMaxSections).AddType(DataType::UnknownUnknown());
		_add(Map, ValuesMinMax).AddType(DataType::UnknownUnknown());
	//	_add(Map, ValuesMinMaxSections).AddType(DataType::D1Unknown());
#undef _add
	}
};

const NormConfTable::NormConfVector& NormConfTable::Get() {
	if(!NormTable)
		NormTable = new NormConfTableImpl();
	return _table;
}

}