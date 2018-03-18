/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/CoreManager.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace VisApp {

using Interface::CoreMessageClass;
using Interface::CoreNotification;

namespace Impl {

class CoreManager;

class CoreManagerGUIMessageBuilder  {
	std::wstringstream m_Line;
	CoreMessageClass m_Class;
	CoreManager *m_Owner;
public:
	CoreManagerGUIMessageBuilder(CoreManager *Owner, CoreMessageClass Class);
	~CoreManagerGUIMessageBuilder();

	template <class T>
	CoreManagerGUIMessageBuilder& operator << (const T &t) {
		(m_Line) << t;
		return *this;
	}

	template <class T, glm::precision P>
	CoreManagerGUIMessageBuilder& operator << (const glm::detail::tvec3<T, P> &t) {
		(m_Line) << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")";
		return *this;
	}

	template <class T, glm::precision P>
	CoreManagerGUIMessageBuilder& operator << (const glm::detail::tvec2<T, P> &t) {
		(m_Line) << "(" << t[0] << ", " << t[1] << ")";
		return *this;
	}

};

class CoreManager : public VisApp::Interface::iManager {
public:
	CoreManager(const std::wstring &LibDirectory);
	virtual ~CoreManager();

//iManager implementation
	virtual Interface::iCoreObserver* RegisterCoreObserver(Interface::iCoreObserver *Observer);
	virtual Interface::iVisualizer* GetVisualizer() const;
	virtual Error Initialize();
	virtual Error Finalize();
	virtual eLibStatus GetStatus() const;
	virtual const Interface::MemoryStatistics* GetMemoryStatistics() const;

//	virtual Interface::iProcessManager* GetProcessManager() const;
	//virtual Interface::iPluginManager* GetPluginManafer()  const;

//Own functions
	void NotifyGUI(Interface::CoreNotification notf);
	void NotifyGUI(CoreMessageClass Class, const std::wstring& Message);
	CoreManagerGUIMessageBuilder NotifyGUI(CoreMessageClass Class);

	static CoreManager *Instance() { return _Instance; }
	const std::wstring& GetRootDir() const { return m_RootDir; }

	bool IsReady() const { return m_Status == Interface::iManager::ls_Waiting || m_Status == Interface::iManager::ls_Ready; }

	void AddAction(std::function<void()> action) {
		m_ActionQueue->AddAction(action);
	}

	void AddDelayedAction(std::function<void()> action, unsigned ms) {
		m_ActionQueue->AddDelayedAction(action, ms);
	}

	static void InsertDelayedAction(std::function<void()> action, unsigned ms) {
		if(_Instance)
			Instance()->AddDelayedAction(action, ms);
	}
	static void InsertAction(std::function<void()> action) {
		if(_Instance)
			Instance()->AddAction(action);
	}
	static void PushGUINotification(Interface::CoreNotification notf) {
		if(_Instance)
			Instance()->NotifyGUI(notf);
	}
	static void PushAction(std::function<void()> action, unsigned delay = 0) {
		if(_Instance)
			_Instance->m_ActionQueue->AddDelayedAction(action, delay);
	}
protected:
	void MainThread();
private:
	volatile eLibStatus m_Status;
	std::thread *m_MainThread;
	std::mutex m_mutex;
	std::wstring m_RootDir;
	std::auto_ptr<Tools::ActionQueue> m_ActionQueue;

	Interface::iCoreObserver *m_Observer;

	void OneMinuteAction();

	static CoreManager *_Instance;
};

} //namespace Impl 
} //namespace VisApp 
