/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataStore.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef DataStore_H
#define DataStore_H

namespace VisApp {
namespace Project {

class Project;
using Interface::SharedMemoryPtr;
class DataStore;
class MemoryPtrImpl;

class DataStore : public VisApp::Interface::iDataStore {
public:
	DataStore(Project *Owner);
	virtual ~DataStore();
//iDataStore implementation
	virtual index_t GetSetCount() const;
	virtual Interface::iDataSeries* GetDataSet(index_t index);
	virtual Interface::iDataSeries* GetDataSet(const std::wstring &Name);
	virtual Interface::iDataSeries* AddSeries(const std::wstring &Name, const Math::uvec3 &size);

	virtual index_t GetLayerCount() const;
	virtual Renderer::SharedLayerInterface GetLayer(index_t index);
	virtual Renderer::SharedLayerInterface GetLayer(const std::wstring &Name);
	virtual Renderer::SharedInternalLayer CreateInternalLayer(Plugins::ProcessPlugin* Owner, const std::wstring &Name);
	virtual Renderer::SharedLayerInterface CreateLayer(Plugins::ProcessPlugin* Owner, const std::wstring &Name, const std::wstring& LayerClassName);

	virtual SharedMemoryPtr AllocateMemory(iResource *Owner, const std::wstring &Name, size_t ByteSize);
	virtual SharedMemoryPtr OpenMemory(iResource *Owner, const std::wstring &Name);
	virtual Interface::iProject *GetOwnerProject();
	virtual void DeleteResource(iResource *res);
//public functions
	DataSeries* NewDataSeries(const std::wstring &Name, const Math::uvec3 &size);
	Project* GetOwnerProjectImpl() const { return m_Owner; }

	DataSeries* GetSeries(index_t index);
	DataSeries* GetSeries(const std::wstring &name);

	MemoryMgt& GetMemMgt() { return m_MemMgt; }
	const MemoryMgt& GetMemMgt() const { return m_MemMgt; }

	bool LoadMeta(xml_node MetaOut);
	bool SaveMeta(xml_node MetaIn, SaveMode Mode) const;

	Renderer::SharedLayerInterface AddLayer(Renderer::SharedLayerInterface NewLayer);
	Renderer::SharedLayerInterface AddLayer(Renderer::LayerInterface* NewLayer);

	void ResourceChangedState(iResource *res, ChangeReason Reason = ChangeReason::State);
private:
	Project *m_Owner;
	mutable std::recursive_mutex m_mutex;

	typedef std::shared_ptr<DataSeries> SharedDataSeries;
	typedef std::list<SharedDataSeries> SeriesList;
	SeriesList m_SeriesList;

	MemoryMgt m_MemMgt;

	typedef std::list<Renderer::SharedLayerInterface> SharedLayerInterfaceList;
	SharedLayerInterfaceList m_LayerList;
};

} //namespace Project
} //namespace VisApp

#endif
