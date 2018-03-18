/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/Renderer.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef Renderer_H
#define Renderer_H

namespace VisApp {
namespace Renderer { 

class VisualizerFacade;

enum class RendererStatus {
	None, 
	Initializing,
	Paused,
	Rendering,
	Broken,
};

struct OpenGLFunctionAssertException {
	const char *name;
	OpenGLFunctionAssertException(const char* n): name(n) { };
};
 
class Renderer : public Worker::Mgt::Executable {
public:
	typedef Interface::iVisualizer::Error Error;
//public type imports
	typedef Interface::iVisualizer iVisualizer;
//primary constructor and destructors
	virtual ~Renderer();
//Core::iVisualizer implementation
	void RequestSingleRedraw() const;
	Error Initialize(Interface::iOGLContext *Context);
	Error Finalize();
	Error SetRenderSpace(unsigned ScreenWidth, unsigned ScreenHeight, float FOV);
	Interface::iCamera* GetCameraFacade();
	Error CaptureScreenShot(const std::wstring &OutFile, Interface::iVisualizer::CaptureFileFormat format) const;
	Error PickLayersAt(Interface::LocalDataQuerry &output, const Math::uvec2 &MousePos) const;
//Public functions
	Interface::iVisualizer* GetFacade() const;

	static bool Execute();
	static void DeleteInstance();
	static RenderDevice *GetRenderDevice() { return _Device; }
	static RenderDevice *Device() { return _Device; }
	static Renderer* Instance();

	bool AddLayer(LayerInterface *layer, LayerInterfaceImpl *liImpl);
	bool RemoveLayer(LayerInterface *layer, bool Async = true);
	void MoveLayer(LayerInterface *layer, int value);
	void CenterView(LayerInterface *layer);

	Tools::ActionQueue::ActionRef AddAction(std::function<void()> action) {
		return m_ActionQueue->AddAction(action);
	}
	static void PushAction(std::function<void()> action, unsigned delay = 0) {
		if(_Instance)
			_Instance->m_ActionQueue->AddDelayedAction(action, delay);
	}

	RendererStatus GetStatus() const { return m_Status; }
	static RendererStatus Status() { 
		if(_Instance)
			return _Instance->GetStatus(); 
		return RendererStatus::Broken;
	}
protected:
	void DoRender();
	virtual void BeforeRun();
	virtual void AfterRun();
	virtual void Run();
	virtual void OnMessage(unsigned commandm, xml_node data);

	void FinalizeActiveLayers();
private:
	Renderer();

	Impl::Types::FacadeHolder<VisualizerFacade> m_VisualizerFacade;
	Impl::Types::FacadeHolder<VisApp::Interface::iCamera> m_CameraFacade;

	VirtualCamera *m_Camera;
	unsigned m_Flags;
	RendererStatus m_Status;

	typedef std::pair<LayerInterface*, LayerInterfaceImpl*> LayerData;
	typedef std::list<LayerData> LayerList;
	LayerList m_ActiveLayers;
	std::mutex m_mutex;
	std::condition_variable m_ExitCondition;

	std::auto_ptr<Tools::ActionQueue> m_ActionQueue;

//	ModelVector m_d3GUI;	// guis added by layer
//	ModelVector m_d2GUI;	// ↑↑↑
//	ModelVector m_StaticGUI;//global gui elements

	static RenderDevice *_Device;
	static std::shared_ptr<Renderer> _Instance;
	
	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);
};

} //namespace Renderer
} //namespace VisApp

#endif
