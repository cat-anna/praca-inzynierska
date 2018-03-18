/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/CoreManager.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\Implementation.h"

namespace VisApp {
namespace Settings {
	void ConfigureSettings(const wchar_t *file);
	void FinalizeSettings();
}
namespace Renderer {
	void RegisterInternalLayer();
}
namespace Interface {

VISAPP_API Interface::iManager* CreateInstance(const std::wstring &LibDirectory) {
	if(!Impl::CoreManager::Instance()) 
		new Impl::CoreManager(LibDirectory);
	return Impl::CoreManager::Instance();
}

}

namespace Impl {

struct InternalException { } ;
struct ExitException : public InternalException { } ;

class PluginMgtActionHandler : public VisApp::Plugins::PluginManagerActionHandler {
public:
	PluginMgtActionHandler() { }
	~PluginMgtActionHandler() { }
	Worker::Mgt::WorkerPtr ExecutePlugin(Plugins::SharedPluginBase plugin, Plugins::SharedPluginExec Exec) {
		return Worker::Mgt::Manager::Instance()->CreateInternalInstance(Exec);
	}
};

PluginMgtActionHandler _PluginActionHandler;

//-----------------------------------------

CoreManager *CoreManager::_Instance = 0;

CoreManager::CoreManager(const std::wstring &LibDirectory) : 
		m_Status(iManager::ls_NotReady),
		m_Observer(0),
		m_MainThread() {
	_Instance = this;
	m_RootDir = LibDirectory;
	m_ActionQueue.reset(new Tools::ActionQueue());
//new Mgt::ProcessManager();
}

CoreManager::~CoreManager() {
	if(m_MainThread) {
		m_MainThread->join();
		delete m_MainThread;
	}
}

//------------ iManager implementation ------------

const Interface::MemoryStatistics* CoreManager::GetMemoryStatistics() const {
	return Project::MemoryMgt::GetGlobalMemStats();
};

Interface::iCoreObserver* CoreManager::RegisterCoreObserver(Interface::iCoreObserver *Observer) {
	Interface::iCoreObserver *prv = m_Observer;
	m_Observer = Observer;
	if(m_Observer) {
		NotifyGUI(Interface::CoreNotification::LayersChanged);
	//	NotifyGUI(Interface::CoreNotification::ProcessesChanged);
	};
	return prv;
}

CoreManager::Error CoreManager::Initialize() {
	if(m_Status != iManager::ls_NotReady) return Error::InvalidStatus;

	m_Status = iManager::ls_Initializing;
	m_MainThread = new std::thread([this]() { 
		try {
			this->MainThread(); 
		} 
		catch(...) {
		}
		m_Status = iManager::ls_Finalized;
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return Error::NoError;
}

CoreManager::Error CoreManager::Finalize() {
	if(m_Status != iManager::ls_Ready) return Error::InvalidStatus;
	AddAction([this] {
		m_Status = iManager::ls_Finalizing;
	});
	return Error::NoError;
}

Interface::iManager::eLibStatus CoreManager::GetStatus() const {
	return m_Status;
}

Interface::iVisualizer* CoreManager::GetVisualizer() const {
	if(!Renderer::Renderer::Instance()) {
		static bool ExecutedOnce = false;
		if(ExecutedOnce) return 0;
		ExecutedOnce = true;
		if(!Renderer::Renderer::Execute())
			return 0;
		else 
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return Renderer::Renderer::Instance()->GetFacade();
}

//------------ Own functions ------------

void CoreManager::OneMinuteAction() {
	AddLog(Debug, "Executing one minute action");
	Interface::WeakProjectList projlist;
	Interface::iProjectMgt::GetInstance()->GetOpenedProjects(projlist);

	for(auto &it: projlist) {
		if(!it.expired())
			std::dynamic_pointer_cast<Project::Project>(it.lock())->DoSaveProject(Project::SaveMode::Shallow);
	}
	auto &meminfo = *Project::MemoryMgt::GetGlobalMemStats();
	AddLog(Hint, "Memory usage " << meminfo.UsedMemory << "[" << (meminfo.UsedMemory / (1024.0f*1024.0f))  << " MiB], " << meminfo.MemObjects << " objects are loaded.")
	throw Tools::ActionQueue::DelayAction(60 * 1000);
}

void CoreManager::MainThread() {
	VisApp::OS::SetThreadName("VisApp Mgt Thread");
	AddLog(Debug, L"Entering Core Manager thread");

	std::atomic<unsigned> InitStatus = 0;

	try {
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		switch (m_Status) {
		case Interface::iManager::ls_NotReady:
			break;

		case Interface::iManager::ls_Initializing:
			Settings::ConfigureSettings(L"CoreSettings.xml");

			Worker::Mgt::Manager::ConstructInstance();
			VisApp::Plugins::PluginManager::ConstructInstance(&_PluginActionHandler);
 
			m_Status = iManager::ls_Waiting;
			VisApp::Plugins::PluginManager::Instance()->DiscoverPlugins(m_RootDir, 
					[this, &InitStatus](const std::wstring&, unsigned){ 
						InitStatus.fetch_or(0x01);
						AddDelayedAction([this] { OneMinuteAction(); }, 60 * 1000);
					});
			AddAction([] { Renderer::RegisterInternalLayer(); });
			continue;

		case Interface::iManager::ls_Waiting:
			if(Renderer::Renderer::Status() != Renderer::RendererStatus::Initializing)
					InitStatus.fetch_or(0x02);

			if(InitStatus == 0x3)
				m_Status = iManager::ls_Ready;

		case Interface::iManager::ls_Ready:
			m_ActionQueue->DispatchPendingActions();
			continue;

		case Interface::iManager::ls_Finalizing:
			m_ActionQueue->DispatchPendingActions();
			//cleaning process may generate actions which has to be immediately executed

			Renderer::Renderer::DeleteInstance();
			m_ActionQueue->DispatchPendingActions();
			
			Worker::Mgt::Manager::Instance()->CancellAll();
			Worker::Mgt::Manager::DestroyInstance();

			Interface::iProjectMgt::GetInstance()->CloseAllProjects();
			m_ActionQueue->DispatchPendingActions();

			Plugins::PluginManager::DeleteInstance();

			Renderer::LayerClassList::Reset();

			m_Status = iManager::ls_Finalized;
			continue;

		case Interface::iManager::ls_Finalized:
			Settings::FinalizeSettings();
			throw 0; //exit
		default:
			throw 0;
		}
	}
	} catch(...) {
	}
	AddLog(Debug, L"Leaving Core Manager thread");
}

void CoreManager::NotifyGUI(Interface::CoreNotification notf) {
	if(!m_Observer) return;
	AddAction([this, notf] {
		AddLog(Debug, "Pushing notification to gui: " << static_cast<int>(notf))
		m_Observer->OnNotification(notf);
	});
}

CoreManagerGUIMessageBuilder CoreManager::NotifyGUI(CoreMessageClass Class) {
	return CoreManagerGUIMessageBuilder(this, Class);
}

void CoreManager::NotifyGUI(CoreMessageClass Class, const std::wstring& Message) {
	if(!m_Observer) return;
	AddAction([this, Class, Message] {
		AddLog(Debug, "Passing notification to gui. Message: '" << Message << "', class: " << static_cast<int>(Class));
		m_Observer->OnCoreMessage(Class, Message);
	});
}

//----------------------------------------------

CoreManagerGUIMessageBuilder::CoreManagerGUIMessageBuilder(CoreManager *Owner, CoreMessageClass Class) {
	m_Owner = Owner;
	m_Class = Class;
}

CoreManagerGUIMessageBuilder::~CoreManagerGUIMessageBuilder() {
	m_Owner->NotifyGUI(m_Class, m_Line.str());
}

} //namespace Impl 
} //namespace VisApp 
