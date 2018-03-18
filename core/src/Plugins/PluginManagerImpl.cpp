/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/PluginManagerImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

#include <boost/filesystem.hpp>

namespace filesystem = boost::filesystem;

namespace VisApp {
namespace Plugins {

struct InternalException { } ;
struct ExitException : public InternalException { } ;
struct PluginWrongVersionException : public InternalException { } ;

//-----------------------

PluginSettings::~PluginSettings() {
	PluginManagerImpl::GetInstance()->SavePluginConfigAction();
}

//-----------------------

PluginInfo::~PluginInfo() { }
PluginManagerActionHandler::~PluginManagerActionHandler() { }

class PluginInfoImpl : public PluginInfo {
public:
	PluginInfoImpl(OS::LibHandle *handle, const std::wstring &filename) {
		m_SysHandle = handle;
		m_FileName = filename;
	}

	~PluginInfoImpl() {
		m_Interface.reset();

		m_SysHandle->ThrowAwayHandle();
		delete m_SysHandle;
		m_SysHandle = 0;
	}

	void GetDescriptorList(WeakDescriptorList &list) {
		for(unsigned i = 0, j = m_Interface->GetPluginCount(); i < j; ++i)
			list.push_back(m_Interface->GetPlugin(i));
	}
	const std::wstring& GetFileName() const { return m_FileName; }
	const std::wstring& GetName() const { return m_Interface->GetName(); }
	const PluginVersion& GetVersion() const { return m_Interface->GetVersion(); }

	void Initialize() {
		QuerryPluginInterfaceFun qfun;
		qfun = (QuerryPluginInterfaceFun)m_SysHandle->GetFunctionHandle(PLUGIN_INTERFACE_QUERRY_FUN_NAME);
		if(!qfun) throw false;
		m_Interface.reset(qfun());
		
		auto ver = m_Interface->GetVersion();
		if(ver.IsDebugBuild != PLUGIN_IS_DEBUG)
			throw PluginWrongVersionException();

		m_Interface->OnLoad();
	}

private:
	OS::LibHandle *m_SysHandle;
	//std::shared_ptr<PluginDescriptor> m_Plugin;
	std::wstring m_FileName;
	std::auto_ptr<PluginInterface> m_Interface;
};

typedef std::shared_ptr<PluginInfoImpl> SharedPluginImpl;

PluginManagerImpl::PluginManagerImpl(PluginManagerActionHandler *handler): 
	m_State(PluginManagerState::Initialization),
	m_ActionHandler(handler) {
	m_thread.reset(new std::thread(&PluginManagerImpl::ThreadMain, this));
}

PluginManagerImpl::~PluginManagerImpl() {
	AbortThread();
	m_thread->join();
}

ExecuteResult PluginManagerImpl::ExecutePlugin(SharedPluginBase plugin, SharedPluginExec Exec) {
	if(!m_ActionHandler) return ExecuteResult();
	return m_ActionHandler->ExecutePlugin(plugin, Exec);
}

void PluginManagerImpl::DiscoverPlugins(const std::wstring& BaseDir, OnDiscoverEndFunc OnEnd) {
	AddLog(Hint, L"Looking for plugins in folder " << BaseDir);
	AddAction([this, BaseDir, OnEnd](){
		SetState(PluginManagerState::Discovery);
		unsigned PluginsFound = 0;
		filesystem::path path(BaseDir);
		if(filesystem::is_directory(path)) {
			for(auto it = filesystem::directory_iterator(path), jt = filesystem::directory_iterator();
				it != jt; ++it) {
					filesystem::path filepath = it->path();
					std::wstring filename = filepath.generic_wstring();
					if(!OS::LibHandle::IsSharedLib(filename))
						continue;
					if(LoadPlugin(filename))
						++PluginsFound;
			}
		}
		//TODO
		if(OnEnd)
			OnEnd(BaseDir, PluginsFound);
	});
}

void PluginManagerImpl::GetImportPlugins(WeakImportDescriptorList &ImportList) {
	FilterDescriptors(PluginType::Import, ImportList);
}

void PluginManagerImpl::GetProcessPlugins(WeakProcessDescriptorList &ImportList) {
	FilterDescriptors(PluginType::Process, ImportList);
}

void PluginManagerImpl::GetPlugins(PluginType type, WeakDescriptorList &ImportList) {
	FilterDescriptors(type, ImportList);
}

PluginManagerState PluginManagerImpl::GetState() const { return m_State; }
SharedPluginList& PluginManagerImpl::GetPluginList() { return m_PluginList; }
const SharedPluginList& PluginManagerImpl::GetPluginList() const { return m_PluginList; }
unsigned PluginManagerImpl::PluginCount() const { return m_PluginList.size(); }

void PluginManagerImpl::AddAction(ActionFunc action) {
	m_ActionQueue.AddAction(action);
}

void PluginManagerImpl::SavePluginConfigAction() {
	AddAction([this] {
		if(m_PluginData.document_element())
			m_PluginData.save_file(L"PluginConfig.xml");
	});
}

bool PluginManagerImpl::LoadPlugin(const std::wstring &FileName)  {
	try {
		OS::LibHandle *h = OS::LibHandle::Open(FileName);
		if(!h) {
			return false;
		}
		if(!h->HasFunction(PLUGIN_INTERFACE_VERSION_FUN_NAME)) {
			delete h;
			return false;
		}

		QuerryPluginInterfaceVersionFun verfun = (QuerryPluginInterfaceVersionFun)h->GetFunctionHandle(PLUGIN_INTERFACE_VERSION_FUN_NAME);
		if(!verfun) {
			delete h;
			return false;
		}
		auto vern = verfun();
		if(((PLUGIN_DEBUG_BUILD_FLAG & vern) > 0) != PLUGIN_IS_DEBUG) {
			//debug/release build mismatch
			delete h;
			throw PluginWrongVersionException();
		}
		if((PLUGIN_INTERFACE_VERSION_MASK & vern) != PLUGIN_INTERFACE_VERSION_Current) {
			//interface version mismatch
			delete h;
			throw PluginWrongVersionException();
		}

		if(!h->HasFunction(PLUGIN_INTERFACE_QUERRY_FUN_NAME)) {
			delete h;
			return false;
		}
		SharedPluginImpl impl = SharedPluginImpl(new PluginInfoImpl(h, FileName));
		impl->Initialize();
		m_PluginList.push_back(impl);
		impl->GetDescriptorList(m_DescriptorList);
		AddLog(Hint, "Succesfully loaded plugin: " << FileName);
		return true;
	}
	catch(PluginWrongVersionException&) {
		AddLog(Error, "Plugin " << FileName << " have wrong interface or build version!");
	}
	catch (...) {
	}
	AddLog(Error, "Unable to load plugin: " << FileName);
	return false;
}

void PluginManagerImpl::UnloadPlugin(SharedPlugin plugin) {
	AddLog(Hint, "Unloading plugin: " << plugin->GetFileName());

	for(auto it = m_PluginList.begin(), jt = m_PluginList.end(); it != jt; ++it) {
		if(it->get() != plugin.get()) continue;
		m_PluginList.erase(it);
		break;
	}
		
	PluginInfoImpl *impl = (PluginInfoImpl*)plugin.get();
	
	//TODO: handle case properly
	//delete impl;//done by shared pointer;
}

void PluginManagerImpl::AbortThread() { AddAction([this]() { throw ExitException(); }); }
void PluginManagerImpl::SetState(PluginManagerState state) { m_State = state; }
void PluginManagerImpl::ThreadMain() {
	VisApp::OS::SetThreadName("Plugin Mgt thread");
	AddLog(Debug, L"Entering Plugin Manager thread");

	try {
		while(1) 
			try {
				m_ActionQueue.WaitForAction();
				m_ActionQueue.DispatchSingleAction();
			}
			catch (ExitException &) {
				if(m_PluginList.empty()) {
					//if(m_PluginData.document_element())
					//	m_PluginData.save_file(L"PluginConfig.xml");
					throw;
				}
				for(auto &it: m_PluginList) {
					AddAction([this, it] {
						UnloadPlugin(it);
					});
					SavePluginConfigAction();
				}
				m_PluginList.clear();
				AbortThread();
				continue;
			}
			catch (const InternalException&) {
				throw;
			}
			catch (...) {
				//TODO: log error
			}
	}
	catch(...) {
	}
	AddLog(Debug, L"Exiting Plugin Manager thread");
}

PluginSettings PluginManagerImpl::QuerryPluginSettings(PluginBase *plugin) {
	if(!m_PluginData.document_element()) {
		//do load
		m_PluginData.load_file(L"PluginConfig.xml");

		if(!m_PluginData.document_element()) {
			m_PluginData.append_child(L"PluginConfig");
		}
	}

	auto conf = m_PluginData.child(L"PluginConfig");

	auto descr = plugin->GetDescriptor().lock();
	auto iface = descr->GetOwnerInterface();

	auto iface_node = conf.find_child_by_attribute(L"Interface", L"Name", iface->GetName().c_str());
	if(!iface_node) {
		iface_node = conf.append_child(L"Interface");
		iface_node.append_attribute(L"Name") = iface->GetName().c_str();
	}

	auto plugin_node = iface_node.find_child_by_attribute(L"Plugin", L"Name", plugin->GetName().c_str());
	if(!plugin_node) {
		plugin_node = iface_node.append_child(L"Plugin");
		plugin_node.append_attribute(L"Name") = plugin->GetName().c_str();
	}

	return PluginSettings(plugin_node);
}

//-----------------------------------------------------------------------------

std::unique_ptr<PluginManagerImpl> PluginManagerImpl::_PluginMgtInstance;

PluginManager::PluginManager() {
}

PluginManager::~PluginManager() {
}

PluginManager* PluginManager::Instance() {
	return PluginManagerImpl::GetInstance().get();
}

bool PluginManager::ConstructInstance(PluginManagerActionHandler *handler) {
	if(PluginManagerImpl::GetInstance()) return false;
	PluginManagerImpl::GetInstance().reset(new PluginManagerImpl(handler));
	return true;
}

bool PluginManager::DeleteInstance() {
	if(!PluginManagerImpl::GetInstance()) return false;
	PluginManagerImpl::GetInstance().reset(NULL);
	return true;
}


} //namespace Plugins 
} //namespace VisApp 
