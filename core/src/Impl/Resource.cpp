/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/Resource.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Interface {

class iResInternal {
	std::recursive_mutex iResourceMutex;
	std::unordered_map<std::wstring, iResource*> iResourceMap;
public:
	void Remove(iResource *res) {
		RECURSIVE_LOCK_EX(iResourceMutex);
		for(auto it = iResourceMap.begin(), jt = iResourceMap.end(); it != jt; ++it) 
			if(it->second == res) {
				iResourceMap.erase(it);
				break;
			}
	}

	void Insert(iResource *res) {
		RECURSIVE_LOCK_EX(iResourceMutex);
		iResourceMap.insert(std::make_pair(res->GetRawRUID(), res));
	}

	void Reset(iResource *res) {
		RECURSIVE_LOCK_EX(iResourceMutex);
		Remove(res);
		Insert(res);
	}

	iResource* Find(const std::wstring &RUID) {
		RECURSIVE_LOCK_EX(iResourceMutex);
		auto it = iResourceMap.find(RUID);
		if(it == iResourceMap.end())
			return 0;
		return it->second;
	}
};

static iResInternal ResInternal;

struct Randomizer {
	Randomizer() { srand(time(NULL)); }
	int operator()() { return rand(); }
};

iResource::~iResource() { 
	ResInternal.Remove(this);
}

iResource::iResource() { 
	static unsigned short counter = 0;
	static Randomizer r;

	const unsigned RUID_size = 4; // in bytes
	char buffer[2 * RUID_size + 4 + 4] = { };
	
	for(unsigned i = 0; i < RUID_size; ++i) {
		sprintf(buffer + 2 * i, "%02x", r() & 0xF);
	}

	sprintf(buffer + 2 * RUID_size, "%04x", counter);
	++counter;
	unsigned len = strlen(buffer);
	m_RUID = std::wstring(buffer, buffer + len);

	ResInternal.Insert(this);
}

iResource* iResource::FindResourceByRUID(const std::wstring &RUID) {
	return ResInternal.Find(RUID);
}

iResource* iResource::GetOwnerResource() { return NULL; }

const std::wstring& iResource::GetRawRUID() const {
	return m_RUID;
}

void iResource::LoadInfo(const xml_node src) {
	m_RUID = src.child(L"RUID").text().as_string(m_RUID.c_str());
	ResInternal.Reset(this);
}

void iResource::SaveInfo(xml_node dst) const {
	dst.append_child(L"RUID").text() = m_RUID.c_str();
}

}
}
