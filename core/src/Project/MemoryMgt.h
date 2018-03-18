/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/MemoryMgt.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef MemoryMgt_H
#define MemoryMgt_H

namespace VisApp {
namespace Project {

class Project;
class DataStore;
class MemoryPtrImpl;
using Interface::SharedMemoryPtr;

class MemoryMgt {
public:
 	MemoryMgt(DataStore *Owner);
 	~MemoryMgt();

	SharedMemoryPtr AllocateMemory(iResource *Owner, const std::wstring &Name, size_t ByteSize);
	SharedMemoryPtr OpenMemory(iResource *Owner, const std::wstring &Name);
	void RelaseResourceMemory(iResource *Owner);

	void LoadMeta(const xml_node in);
	void SaveMeta(xml_node out, bool DeepSave = true) const;

	DataStore* GetOwner() const { return m_Owner; }
	Project* GetOwnerProject() const;

	void DelayDestruction(MemoryPtrImpl *impl);
	void ReportUnusedMemory(MemoryPtrImpl *impl);

	void MemoryCreated(MemoryPtrImpl *impl) { _MemStats.MemObjects++; }
	void MemoryDestroyed(MemoryPtrImpl *impl) { _MemStats.MemObjects--; }
	void MemoryAcquired(MemoryPtrImpl *impl) { _MemStats.UsedMemory += impl->GetLength(); }
	void MemoryReleased(MemoryPtrImpl *impl) { _MemStats.UsedMemory -= impl->GetLength(); }

	static const Interface::MemoryStatistics* GetGlobalMemStats() { return &_MemStats; }
private:
	static Interface::MemoryStatistics _MemStats;

	DataStore *m_Owner;
	mutable std::recursive_mutex m_mutex;

	typedef std::unordered_map<std::wstring, SharedMemoryPtr> MemoryPtrMap;
	MemoryPtrMap m_LoadedData;

	void GetResourceName(std::wstring &output, iResource *res, const std::wstring &ObjectName);
	SharedMemoryPtr FindMemory(const std::wstring &Name);
};

} //namespace Project 
} //namespace VisApp 

#endif

