/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/Memory.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\Implementation.h"
#include "FileHeaders.h"

namespace VisApp {
namespace Interface {

using Project::DataStore;
	
MemoryPtr::MemoryPtr(iDataStore* MemoryOwner, Project::MemoryPtrImpl *impl): 
		m_Owner(MemoryOwner),
		m_Impl(impl) { }

MemoryPtr::~MemoryPtr() {
	m_Impl->GetOwner()->DelayDestruction(m_Impl);
}

void MemoryPtr::AddUser(iResource *who) { m_Impl->AddUser(who); }
void* MemoryPtr::Get() { return m_Impl->GetMemory(); }
const void* MemoryPtr::Get() const { return m_Impl->GetMemory(); }
unsigned long long MemoryPtr::ByteSize() const { return m_Impl->GetLength(); }
const std::wstring &MemoryPtr::GetName() const { return m_Impl->GetName(); }

unsigned MemoryPtr::PushData(const void *src, unsigned length, unsigned offset) {
	return m_Impl->PushData(src, length, offset);
}

}//namespace Interface
//---------------------------------------------------------------------------------
namespace Project {

MemoryPtrImpl::MemoryPtrImpl(MemoryMgt *Owner): m_Flags(0) {
	m_Owner = Owner;
	m_Memory = 0;
	SetFlags(Flags::Dirty);
	m_Owner->MemoryCreated(this);
}

MemoryPtrImpl::~MemoryPtrImpl() {
	if(m_Memory)
		ReleaseMemHandle();
	m_Owner->MemoryDestroyed(this);
}

std::wstring MemoryPtrImpl::GetFileName() const {
	const std::wstring &Folder = m_Owner->GetOwnerProject()->GetLocation();
	std::wstringstream wss;
	wss << Folder << L"\\" << Name << VISAPP_DATAFILE_EXTENSION;
	return wss.str();
}

bool MemoryPtrImpl::WriteToFile() const {
	BinFiles::Headers::RawFileHeader rfh;
	rfh.DataSize = m_len;
	std::ofstream out(GetFileName(), std::ios::out | std::ios::binary);
	out.write((char*)&rfh, sizeof(rfh));
	out.write(m_Memory, m_len);

	return true;
}

bool MemoryPtrImpl::LoadFromFile() {
	BinFiles::Headers::RawFileHeader rfh;

	std::ifstream in(GetFileName(), std::ios::in | std::ios::binary);

	in.read((char*)&rfh, sizeof(rfh));
	bool FileOk = true;
	size_t NewLen;
	if(!rfh.IsValid()) {
		AddLog(Error, "Unable to load memory " << Name << " from file " << GetFileName() << ". File is corrupted");
		Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::CriticalError)
			<< "B³¹d wczytywania zasobu " << Name << ". Plik uszkodzony.";

		FileOk = false;
	} else {
		NewLen = (size_t)rfh.DataSize;
	}

	Recreate(NewLen);

	if(FileOk) {
		in.read(m_Memory, NewLen);
	} 

	return FileOk;
}

unsigned MemoryPtrImpl::PushData(const void *src, unsigned length, unsigned offset) {
	unsigned long long cpy = Math::Min((unsigned long long)length, m_len - offset);
	memcpy(GetMem() + offset, src, static_cast<size_t>(cpy));
	SetFlags(FlagSet::UserModiffied);
	return (unsigned)cpy;
}

char* MemoryPtrImpl::GetMem() {
	Needed();
	SetFlags(Flags::Accessed);
	return m_Memory;
}

void MemoryPtrImpl::ReleaseMemHandle() {
	if(!m_Memory) return;
	delete m_Memory;
	m_Memory = 0;
	SetFlags(Flags::Virtual);
	ClearFlags(FlagSet::UserModiffied);
	m_Owner->MemoryReleased(this);
}

void MemoryPtrImpl::Recreate(size_t NewLen) {
	ReleaseMemHandle();
	m_Memory = new char[(unsigned)NewLen];
	memset(m_Memory, 0, (size_t)NewLen);
	m_len = NewLen;
	SetFlags(Flags::Dirty);
	m_Owner->MemoryAcquired(this);
}

void MemoryPtrImpl::Save() const {
	WriteToFile();
	ClearFlags(Flags::Dirty);
}

void MemoryPtrImpl::DumpAndDestroy() {
	WriteToFile();
	ReleaseMemHandle();
	SetFlags(Flags::Virtual);
	ClearFlags(FlagSet::UserModiffied);
}

void MemoryPtrImpl::Needed() {
	if(TestFlags(Flags::Virtual)) {
		LoadFromFile();
		ClearFlags(FlagSet::Existing);
	}
}

void MemoryPtrImpl::Delete() {
	ReleaseMemHandle();
	auto f = GetFileName();
	boost::filesystem::remove(f);
	ClearFlags(FlagSet::Existing);
}

void MemoryPtrImpl::AddUser(iResource *user) {
	auto &ruid = user->GetRawRUID();
	auto it = std::find_if(m_Users.begin(), m_Users.end(), [&ruid] (const std::wstring& ws) {
		return ruid.compare(ws) == 0;
	});
	if(it == m_Users.end())
		m_Users.push_back(user->GetRawRUID());
	else
		AddLog(Warning, "Attempt to existing RUID to memory user list! ruid:" << ruid  << "  memory: " << GetName());
}

void MemoryPtrImpl::RemoveUser(iResource *user) {
	auto &ruid = user->GetRawRUID();
	auto it = std::find_if(m_Users.begin(), m_Users.end(), [&ruid] (const std::wstring& ws) {
		return ruid.compare(ws) == 0;
	});
	if(it == m_Users.end())
		return;
	m_Users.erase(it);
	if(m_Users.empty()) {
		AddLog(Debug, "Memory '" << Name << "' is now userless");
		GetOwner()->ReportUnusedMemory(this);
	}
}

bool MemoryPtrImpl::LoadMeta(const xml_node in) {
	Name = in.child(L"Name").text().as_string();
	m_len = in.attribute(L"Size").as_ullong();
	SetFlags(Flags::Virtual);
	ClearFlags(FlagSet::UserModiffied);

	auto users = in.child(L"Users");
	for(users = users.child(L"RUID"); users; users = users.next_sibling(L"RUID"))
		m_Users.push_back(users.text().as_string(L""));

	return !m_Users.empty();
}

void MemoryPtrImpl::SaveMeta(xml_node out, bool DeepSave) const {
	out.append_attribute(L"Size") = m_len;
	out.append_child(L"Name").text() = Name.c_str();

	auto users = out.append_child(L"Users");
	for(auto &it: m_Users)
		users.append_child(L"RUID").text() = it.c_str();

	//check if memory is loaded
	if(!m_Memory) return;

	//save changed memory
	if(TestFlags(Flags::Dirty) || DeepSave) {
		Save();
	}
}

} //namespace Project 
} //namespace VisApp 

