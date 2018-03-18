/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/MemoryMgt.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\Implementation.h"

namespace VisApp {
namespace Project {

Interface::MemoryStatistics MemoryMgt::_MemStats;

MemoryMgt::MemoryMgt(DataStore *Owner): m_Owner(Owner) {
}

MemoryMgt::~MemoryMgt() {
}

void MemoryMgt::DelayDestruction(MemoryPtrImpl *impl) {
	delete impl; //nope
	//TODO: remove nope
}

void MemoryMgt::ReportUnusedMemory(MemoryPtrImpl *impl) {
	if(!impl) return;
	Impl::CoreManager::PushAction([this, impl] {
		RECURSIVE_LOCK
		AddLog(Debug, "Deleting unused memory: " << impl->GetName());

		auto it = std::find_if(m_LoadedData.begin(), m_LoadedData.end(), [impl] (MemoryPtrMap::value_type it) {
			return it.second->GetInternalImpl() == impl;
		});

		if(it == m_LoadedData.end()) {
			AddLog(Error, "Report about unused memory was obtained, but memory does not exists!");
			return;
		}
		auto sh = it->second;
		m_LoadedData.erase(it);
		impl->Delete();
	}, 1 * 1000);
}

Project* MemoryMgt::GetOwnerProject() const { return GetOwner()->GetOwnerProjectImpl(); }

void MemoryMgt::LoadMeta(const xml_node in) {
	RECURSIVE_LOCK
	memset(&_MemStats, 0, sizeof(_MemStats));
	for(auto it = in.child(L"Memory"); it; it = it.next_sibling(L"Memory")) {
		MemoryPtrImpl *mi = new MemoryPtrImpl(this);
		if(!mi->LoadMeta(it)) {
			AddLog(Error, "Found unused memory object. Object deleted. ('" << mi->GetName() << "')");
			delete mi;
			continue;
		}
		Interface::MemoryPtr *ptr = new Interface::MemoryPtr(m_Owner, mi);
		m_LoadedData.insert(std::make_pair(mi->Name, SharedMemoryPtr(ptr)));
		AddLog(Hint, L"Loaded data '" << mi->GetName() << L"' of size " << mi->GetLength())
	}
}

void MemoryMgt::SaveMeta(xml_node out, bool DeepSave) const {
	RECURSIVE_LOCK
	for(xml_node it; it = out.first_child(); )
		out.remove_child(it);

	for(auto &it: m_LoadedData) {
		auto *ptr = it.second.get();
		MemoryPtrImpl *impl = ptr->GetInternalImpl();

		xml_node MemNode = FindNodeWithChildText(out, L"Name", impl->Name.c_str());
		if(MemNode)
			out.remove_child(MemNode);
		MemNode = out.append_child(L"Memory");
		impl->SaveMeta(MemNode, DeepSave);
	}
}

void MemoryMgt::GetResourceName(std::wstring &output, iResource *res, const std::wstring &ObjectName) {
	std::wstringstream wss;
	wss << res->GetRawRUID() << L"_" << ObjectName;
	output = wss.str();
}

SharedMemoryPtr MemoryMgt::FindMemory(const std::wstring &Name) {
	RECURSIVE_LOCK
	auto it = m_LoadedData.find(Name);
	if(it == m_LoadedData.end()) {
		return SharedMemoryPtr();
	}
	return it->second;
}

SharedMemoryPtr MemoryMgt::AllocateMemory(iResource *Owner, const std::wstring &Name, size_t ByteSize) {
	std::wstring resId;
	GetResourceName(resId, Owner, Name);
	RECURSIVE_LOCK
	MemoryPtrImpl *mi;
	auto result = FindMemory(resId);
	if(result) {
		mi = result->GetInternalImpl();
		mi->ReleaseMemHandle();
		AddLog(Warning, L"Recreate memory " << resId << L" with size " << ByteSize << " bytes")
	} else {
		mi = new MemoryPtrImpl(this);
		result = SharedMemoryPtr(new Interface::MemoryPtr(m_Owner, mi));
		mi->Name = resId;
		m_LoadedData.insert(std::make_pair(resId, result));
		AddLog(Debug, L"Create memory " << resId << L" with size " << ByteSize << " bytes")
	}
	mi->AddUser(Owner);
	mi->Recreate(ByteSize);
	memset(mi->GetMemory(), 0, ByteSize);
	return result;
}

SharedMemoryPtr MemoryMgt::OpenMemory(iResource *Owner, const std::wstring &Name) {
	std::wstring resId;
	GetResourceName(resId, Owner, Name);	
	AddLog(Debug, L"Opening memory: " << resId)
	RECURSIVE_LOCK
	auto R = FindMemory(resId);
	if(!R){
		AddLog(Warning, L"Unable to find memory: " << Name)
		return SharedMemoryPtr();
	}
	return R;
}

void MemoryMgt::RelaseResourceMemory(iResource *Owner) {
	RECURSIVE_LOCK
	for(auto &it: m_LoadedData)
		it.second->GetInternalImpl()->RemoveUser(Owner);
}

} //namespace Project 
} //namespace VisApp 
