/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/Memory.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef Memory_H
#define Memory_H

namespace VisApp {
namespace Project {

class MemoryMgt;

class MemoryPtrImpl {
public:
	std::wstring Name;

	MemoryPtrImpl(MemoryMgt *Owner);
	~MemoryPtrImpl();

	bool LoadMeta(const xml_node in);
	void SaveMeta(xml_node out, bool DeepSave = true) const;

	void AddUser(iResource *user);
	void RemoveUser(iResource *user);
	void IsUser(iResource *user);

	void Delete();

	char* GetMemory() const { return ((MemoryPtrImpl*)this)->GetMem(); }
	unsigned long long GetLength() const { return m_len; }
	std::wstring GetFileName() const;
	const std::wstring& GetName() const { return Name; }
	MemoryMgt* GetOwner() const { return m_Owner; }
	bool IsLoaded() const { return !TestFlags(Flags::Virtual); }

	unsigned PushData(const void *src, unsigned length, unsigned offset);//returns amount copied

	void Needed();
	void Recreate(size_t NewLen);
	void ReleaseMemHandle();
	void Save() const;
	void DumpAndDestroy();
private:
	char* GetMem();

	bool WriteToFile() const;
	bool LoadFromFile();

	bool TestFlags(unsigned what) const { return (m_Flags & what) == what; }
	void SetFlags(unsigned what) const { m_Flags |= what; };
	void ClearFlags(unsigned what) const { m_Flags &= ~what; }
	
	struct Flags {
		enum {
			Virtual		= 0x01,
			Dirty		= 0x02,
			Accessed	= 0x04,
		};
	};

	struct FlagSet : protected Flags {
		enum {

			UserModiffied		= Dirty | Accessed,

			Existing			= Virtual | Dirty | Accessed,
		};
	};

	char* m_Memory;
	unsigned long long m_len;

	std::vector<std::wstring> m_Users;
	mutable unsigned m_Flags;

	MemoryMgt *m_Owner;
};

} //namespace Project 
} //namespace VisApp 

#endif
