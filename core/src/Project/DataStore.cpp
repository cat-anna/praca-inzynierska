/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/DataStore.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Project {

DataStore::DataStore(Project *Owner): m_Owner(Owner), m_MemMgt(this) {
}	

DataStore::~DataStore() {
}

//iDataStore implementation

Interface::iProject *DataStore::GetOwnerProject() {
	return GetOwnerProjectImpl();
}

index_t DataStore::GetSetCount() const {
	return m_SeriesList.size();
}

Interface::iDataSeries* DataStore::GetDataSet(index_t index) {
	return GetSeries(index);
}

Interface::iDataSeries* DataStore::GetDataSet(const std::wstring &Name) {
	return GetSeries(Name);
}

Interface::iDataSeries* DataStore::AddSeries(const std::wstring &Name, const Math::uvec3 &size) {
	return NewDataSeries(Name, size);
}

index_t DataStore::GetLayerCount() const {
	return m_LayerList.size();
}

Renderer::SharedLayerInterface DataStore::GetLayer(index_t index) {
	RECURSIVE_LOCK
	for(auto &it: m_LayerList)
		if(index == 0)
			return it;
		else
			--index;
	return Renderer::SharedLayerInterface();
}

Renderer::SharedLayerInterface DataStore::GetLayer(const std::wstring &Name) {
	RECURSIVE_LOCK
	for(auto &it: m_LayerList)
		if(it->GetName() == Name)
			return it;
	AddLog(Error, L"Unable to find layer " << Name)
	return Renderer::SharedLayerInterface();
}

Renderer::SharedInternalLayer DataStore::CreateInternalLayer(Plugins::ProcessPlugin* Owner, const std::wstring &Name) {
	return std::dynamic_pointer_cast<Renderer::SharedInternalLayer::element_type>(CreateLayer(Owner, Name, L"InternalLayerClass"));
}

Renderer::SharedLayerInterface DataStore::CreateLayer(Plugins::ProcessPlugin* Owner, const std::wstring &Name, const std::wstring& LayerClassName) {
	Renderer::SharedLayerInterface layer;
	{
		RECURSIVE_LOCK
		std::wstring lname = Name;
		int index = 0;
		for(auto it = m_LayerList.begin(), jt = m_LayerList.end(); it != jt; ) {
			if((*it)->GetName() == lname) {
				wchar_t buf[16] = { };
				_itow_s(index, buf, 10);
				lname = Name + buf;
				++index;
				it = m_LayerList.begin();
			} 
			else ++it;
		}
		
		layer = Renderer::LayerClassList::ConstructLayer(LayerClassName, lname, 0);
	}
	return AddLayer(layer);
}

SharedMemoryPtr DataStore::AllocateMemory(iResource *Owner, const std::wstring &Name, size_t ByteSize) {
	return m_MemMgt.AllocateMemory(Owner, Name, ByteSize);
}
SharedMemoryPtr DataStore::OpenMemory(iResource *Owner, const std::wstring &Name) {
	return m_MemMgt.OpenMemory(Owner, Name);

}

//public functions

Renderer::SharedLayerInterface DataStore::AddLayer(Renderer::SharedLayerInterface NewLayer) {
	if(!NewLayer) return NewLayer;
	RECURSIVE_LOCK
	m_LayerList.push_back(NewLayer);
	NewLayer->SetOwner(this);
	Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreNotification::LayersChanged);
	AddLog(Hint, L"Created layer " << NewLayer->GetName() << L" of class " << NewLayer->GetLayerClassName())
	return NewLayer;
}

Renderer::SharedLayerInterface DataStore::AddLayer(Renderer::LayerInterface* NewLayer) {
	Renderer::SharedLayerInterface layer(NewLayer);
	return AddLayer(layer);
}

DataSeries* DataStore::GetSeries(index_t index) {
	RECURSIVE_LOCK
	if(index >= m_SeriesList.size()) return 0;
	auto it = m_SeriesList.begin();
	for(unsigned long i = 0; i < index; ++i, ++it);
	return it->get();
}

DataSeries* DataStore::GetSeries(const std::wstring &name) {
	RECURSIVE_LOCK
	for(auto &i: m_SeriesList)
		if(i->GetName() == name)
			return i.get();
	AddLog(Error, L"Unable to find series: " << name)
	return 0;
}

DataSeries* DataStore::NewDataSeries(const std::wstring &Name, const Math::uvec3 &size) {
	RECURSIVE_LOCK

	std::wstring dname = Name;
	int index = 0;
	for(auto it = m_SeriesList.begin(), jt = m_SeriesList.end(); it != jt; ) {
		if((*it)->GetName() == dname) {
			wchar_t buf[16] = { };
			_itow_s(index, buf, 10);
			dname = Name + buf;
			++index;
			it = m_SeriesList.begin();
		} 
		else ++it;
	}

	auto ds = new DataSeries(this, dname, size); 
	m_SeriesList.push_back(SharedDataSeries(ds));
	Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreNotification::SeriesChanged);
	AddLog(Hint, L"Added new data series " << dname << L" with size " << size)
	return ds;
}

bool DataStore::SaveMeta(xml_node MetaOut, SaveMode Mode) const {
	bool DeepSave = Mode == SaveMode::Deep;
	RECURSIVE_LOCK
	{
		xml_node SeriesNode = UniqeChild(MetaOut, L"Series");

		for(xml_node it; it = SeriesNode.find_child([](xml_node n){
			return n.attribute(L"Error").as_bool(false) == false;
		}); ) {
			SeriesNode.remove_child(it);
		}

		for(auto &it: m_SeriesList) {
			xml_node ItemNode = FindNodeWithChildText(SeriesNode, L"Name", it->GetName().c_str());
			if(ItemNode)
				SeriesNode.remove_child(ItemNode);
			
			ItemNode = SeriesNode.append_child(L"Item");
			it->SaveMeta(ItemNode);
		}
	}
	{
		xml_node LayersNode = UniqeChild(MetaOut, L"Layers");

		for(xml_node it; it = LayersNode.find_child([](xml_node n){
			return n.attribute(L"Error").as_bool(false) == false;
		}); ) {
			LayersNode.remove_child(it);
		}

		for(auto &it: m_LayerList) {
			xml_node ItemNode = FindNodeWithChildText(LayersNode, L"Name", it->GetName().c_str());
			if(ItemNode)
				LayersNode.remove_child(ItemNode);

			ItemNode = LayersNode.append_child(L"Item");
			it->Save(ItemNode);
		}
	}
	
	m_MemMgt.SaveMeta(UniqeChild(MetaOut, L"Data"), DeepSave);
	
	return true;
}

bool DataStore::LoadMeta(xml_node MetaIn)  {
	RECURSIVE_LOCK
	{
		xml_node SeriesNode = MetaIn.child(L"Series");
		for(auto it = SeriesNode.child(L"Item"); it; it = it.next_sibling(L"Item")) {
			it.remove_attribute(L"Error");
			auto ds = new DataSeries(this); 
			try {
				if(!ds->LoadMeta(it)) throw false;
			}
			catch(...) {
				const wchar_t *name = it.child(L"Name").text().as_string(L"?");
				AddLog(Hint, L"Unable to load data series " << name)
				Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error)
					<< L"B³¹d wczytywania serii danych " << name;
				delete ds;
				UniqeAttrib(it, L"Error") = true;
				continue;
			}
			m_SeriesList.push_back(SharedDataSeries(ds));
			AddLog(Hint, L"Loaded data series " << ds->GetName() << L" with size " << ds->GetSize())
		}
	}
	{
		xml_node LayersNode = MetaIn.child(L"Layers");
		for(auto it = LayersNode.child(L"Item"); it; it = it.next_sibling(L"Item")) {
			it.remove_attribute(L"Error");
			std::wstring Class = it.attribute(L"LayerClass").as_string();

			auto layer = Renderer::LayerClassList::ConstructLayer(Class, L"?", 0);
			if(!layer) {
				AddLog(Error, "Unknown layer class " << Class);
				Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error)
					<< L"Nieznana klasa warstwy " << Class;
				UniqeAttrib(it, L"Error") = true;
				continue;
			}
			layer->SetOwner(this);
			try {
				if(layer->Load(it) != Renderer::LayerInterface::Error::NoError) throw false;
			}
			catch(...) {
				AddLog(Error, "Unable to load layer of class " << Class);
				Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error)
					<< L"B³¹d wczytywania warstwy o klasie " << Class;
				UniqeAttrib(it, L"Error") = true;
				continue;
			}
			m_LayerList.push_back(layer);
			AddLog(Hint, L"Loaded layer " << layer->GetName() << L" of class " << Class)
		}
	}
	
	m_MemMgt.LoadMeta(MetaIn.child(L"Data"));
	
	return true;
}

void DataStore::ResourceChangedState(iResource *res, ChangeReason Reason) {
	if(!res) return;
	Renderer::LayerInterface *layer;

	if((layer = dynamic_cast<Renderer::LayerInterface*>(res))) {
		Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreNotification::LayersChanged);
		//queue to save?

		return;
	}

	AddLog(Error, "Resource " << res->GetName() << " changed state, but it has unknown type!");
}

void DataStore::DeleteResource(iResource *res) {
	if(!res) return;
	RECURSIVE_LOCK
	for(Renderer::LayerInterface *layer = dynamic_cast<Renderer::LayerInterface*>(res); layer; ) {
		Renderer::Renderer::Instance()->RemoveLayer(layer, true);
		Renderer::Renderer::PushAction([this, layer] {
			RECURSIVE_LOCK
			auto it = std::find_if(m_LayerList.begin(), m_LayerList.end(), [layer] (Renderer::SharedLayerInterface &i) {
				return layer == i.get();
			});
			if(it == m_LayerList.end()) {
				Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::CriticalError)
					<< "Nie mo¿na odnaleŸæ warstwy o nazwie: " << layer->GetName();
				return;
			}
			m_MemMgt.RelaseResourceMemory(layer);
			m_LayerList.erase(it);
			Impl::CoreManager::PushGUINotification(CoreNotification::LayersChanged);
		});
		return;
	}

	if(auto series = dynamic_cast<DataSeries*>(res)) {
		Impl::CoreManager::PushAction([this, series] {
			RECURSIVE_LOCK
			auto it = std::find_if(m_SeriesList.begin(), m_SeriesList.end(), [series] (SharedDataSeries &i) {
				return series == i.get();
			});
			if(it == m_SeriesList.end()) {
				Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::CriticalError)
					<< "Nie mo¿na odnaleŸæ serii danych o nazwie: " << series->GetName();
				return;
			}
			m_MemMgt.RelaseResourceMemory(series);

			while(series->GetChannelCount() > 0)
				series->RemoveDataChannel(series->GetChannelCount() - 1);

			m_SeriesList.erase(it);
			Impl::CoreManager::PushGUINotification(CoreNotification::SeriesChanged);
		});
		return;
	}

	if(auto channel = dynamic_cast<DataChannel*>(res)) {
		Impl::CoreManager::PushAction([this, channel] {
			RECURSIVE_LOCK
			channel->GetOwnerSeries()->RemoveDataChannel(channel);
			Impl::CoreManager::PushGUINotification(CoreNotification::ChannelChanged);
		});
		return;
	}

	AddLog(Error, "Resource " << res->GetName() << " requested to be deleted, but it has unknown type!");
}

//------------------------------------------------------------------

} //namespace Project
} //namespace VisApp
