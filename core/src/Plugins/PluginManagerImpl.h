/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginManagerImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace VisApp {
namespace Plugins {

class PluginManagerImpl : public PluginManager {
public:
	typedef Tools::ActionQueue::ActionFunc ActionFunc; 

	PluginManagerImpl(PluginManagerActionHandler *handler);
	virtual ~PluginManagerImpl();
	virtual void DiscoverPlugins(const std::wstring& BaseDir, OnDiscoverEndFunc OnEnd);
	virtual void GetImportPlugins(WeakImportDescriptorList &ImportList);
	virtual void GetProcessPlugins(WeakProcessDescriptorList &ImportList);
	virtual void GetPlugins(PluginType type, WeakDescriptorList &ImportList);
	virtual PluginManagerState GetState() const;
	virtual SharedPluginList& GetPluginList();
	virtual const SharedPluginList& GetPluginList() const;
	virtual unsigned PluginCount() const;

	ExecuteResult ExecutePlugin(SharedPluginBase plugin, SharedPluginExec Exec);
	static std::unique_ptr<PluginManagerImpl>& GetInstance() { return _PluginMgtInstance; }

	PluginSettings QuerryPluginSettings(PluginBase *plugin);
	void SavePluginConfigAction();
protected:
	void AddAction(ActionFunc action);
	bool LoadPlugin(const std::wstring &FileName);
	void UnloadPlugin(SharedPlugin plugin);

	template<class PLUGIN_CLASS>
	void FilterDescriptors(PluginType type, std::list<std::weak_ptr<PLUGIN_CLASS>> &ImportList) {
		for(auto it = m_DescriptorList.begin(), jt = m_DescriptorList.end(); it != jt; ++it)
			if(!(*it).expired()) { 
				std::shared_ptr<PluginDescriptor> plugin = (*it).lock();
				if(plugin->GetPluginType() != type) continue;
				if(dynamic_cast<PLUGIN_CLASS*>(plugin.get()) == NULL) continue;
				std::shared_ptr<PLUGIN_CLASS> casted = std::dynamic_pointer_cast<PLUGIN_CLASS>(plugin);
				if(!casted) continue;
				ImportList.push_back(casted);
			}
	}

	void AbortThread();
	void SetState(PluginManagerState state);

private:
	Tools::ActionQueue m_ActionQueue;
	std::auto_ptr<std::thread> m_thread;
	std::mutex m_mutex;
	PluginManagerState m_State;
	SharedPluginList m_PluginList;
	WeakDescriptorList m_DescriptorList;
	PluginManagerActionHandler *m_ActionHandler;
	xml_document m_PluginData;

	void ThreadMain();

	static std::unique_ptr<PluginManagerImpl> _PluginMgtInstance;
};

} //namespace Plugins 
} //namespace VisApp 