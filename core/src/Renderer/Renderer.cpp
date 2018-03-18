/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/Renderer.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "nRenderer.h"

namespace VisApp {
namespace Renderer { 

typedef std::unique_lock<std::mutex> scoped_lock;

struct ExitException { };

class VisualizerFacade : public Interface::iVisualizer {
public:
	VisualizerFacade(Renderer *impl): m_impl(impl) { }
	Interface::iCamera* GetCamera() const { return impl()->GetCameraFacade(); }
	void RequestSingleRedraw() const { return impl()->RequestSingleRedraw(); }
	Error Initialize(Interface::iOGLContext *Context) { 
		return impl()->Initialize(Context); 
	}
	Error SetRenderSpace(unsigned w, unsigned h, float f) { return impl()->SetRenderSpace(w, h, f); }
	Error Finalize() { return impl()->Finalize(); }
	Error CaptureScreenShot(const std::wstring &OutFile, CaptureFileFormat format) { return impl()->CaptureScreenShot(OutFile, format); }

	Error PickLayersAt(Interface::LocalDataQuerry &output, const Math::uvec2 &MousePos) {
		return impl()->PickLayersAt(output, MousePos);
	}

private:
	Renderer* impl() { return m_impl; }
	Renderer* impl() const { return m_impl; }
	Renderer *m_impl;
};

RenderDevice *Renderer::_Device = 0;
std::shared_ptr<Renderer> Renderer::_Instance = 0;

Renderer::Renderer(): 
		Worker::Mgt::Executable(),
		m_Flags(0),
		m_Camera(0),
		m_Status(RendererStatus::Initializing) {
	SetProgress(-0.01f);
	SetName(L"Renderer");
	m_ActionQueue.reset(new Tools::ActionQueue());

	AddStatelessRequirement([this] {
		return _Device != 0;
	});
}

Renderer::~Renderer() {
}

bool Renderer::Execute() {
	if(_Instance || !Impl::CoreManager::Instance()) return false;
	_Instance.reset(new Renderer());
	Impl::CoreManager::InsertAction([] {
		Worker::Mgt::Manager::Instance()->CreateInternalInstance(_Instance).lock()->Execute();
	});
	return true;
}

Renderer* Renderer::Instance() { 
	return _Instance.get(); 
}

void Renderer::DeleteInstance() {
	static std::mutex func_mutex;
	scoped_lock lock(func_mutex);

	if(!_Instance || !_Device)
		return;

	std::mutex local_mutex;
	scoped_lock local_lock(local_mutex);
	std::condition_variable var;

	if(_Instance->m_ActiveLayers.size() > 0) {
		_Instance->AddAction([] {
			_Instance->FinalizeActiveLayers();
			AddLog(Debug, "FinalizeActiveLayers renderer instance")
		});
	}

	_Instance->AddAction([] {
		AddLog(Debug, "exiting renderer instance")
		throw ExitException();
	});

	_Instance->m_ExitCondition.wait(local_lock);
}

Interface::iVisualizer* Renderer::GetFacade() const { 
	return m_VisualizerFacade.GetInstance(this); 
};

void Renderer::OnMessage(unsigned command, xml_node data) {
//	static unsigned counter = 0;
//	switch(command) {
//	case Commands::ImportLyers: {
//		SetPhaseName(L"Wczytywanie warstwy");
//		xml_node layer = data.child(L"Layer");
	//	auto Project = Mgt::CoreManager::Instance()->GetProject(data.attribute(L"Project").as_string(L""));
	//	GetLayerLibrary()->LoadLayer(Project, layer);
	//	Mgt::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
	//	DumpDynamicXML("Layer", data);
	/*	if(GetLayerLibrary()->LayerCount() == 1) {
			//first layer was loaded
			auto layer = GetLayerLibrary()->GetLayer(0);
			SetRenderingMode(static_cast<RenderingMode>(layer->GetLayerType()));
			auto size = layer->GetSize();
			auto camera = m_RenderMode == RenderingMode::d2 ? m_D2Camera : m_D3Camera;
			camera->GetOrbitAngle()[2] = Math::max(size[0], size[1]) * 1.3f;
			camera->Magnify(0);
		}*/

	//	SetPhaseName(L"Renderowanie");
//		break;
//	}
//	default:
//		break;
//	};
}

void Renderer::DoRender() {
	if(!_Device) {
		//TODO: error!
		return;
	}

//	static Layers::EnvModel *env  = new Layers::EnvModel(5, Math::fvec3(), Math::fvec3());

//	if(m_RenderMode == RenderingMode::NotInitialized) {
		//Log error?
//		return;
//	}

	auto &dev = *GetRenderDevice();
	dev.BeginFrame();
	dev.BindShader(0);

/*	if(m_RenderMode == RenderingMode::d3) {
		Math::fvec2 angle(0.1f, 0.0f);
		m_Camera->Orbit(angle);
	}*/

//	dev.BindCamera(m_RenderMode == RenderingMode::d2 ? m_D2Camera : m_D3Camera);
	dev.BindCamera(m_Camera);

	for(auto &it: m_ActiveLayers) {
		auto l = it.first;
		auto impl = l->GetInternalImpl();
		if(!impl->shader) {
			AddLog(Error, L"Layer " << l->GetName() << L" does not have choosen shader. Unable to render.");
			RemoveLayer(l);
			continue;
		}
		auto shader = impl->shader;
		dev.BindShader(shader);
		shader->SetVec3Value(impl->BaseColor, Shader::eShaderParameters::spBaseColor);
		l->DoRender(dev);
	}

	dev.EndFrame();

//	for(auto &i: m_Layers) i->DoRender(*_Device);
//	for(auto &i: m_d2GUI) i->DoRender(*_Device);
//change camera to 2d rendedring
//	for(auto &i: m_2dGUI) i->DoRender(*_Device);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	m_CurrentScene->DoRender(*GetDevice());
//	m_Device->SetD3Mode(false);
//	m_CurrentScene->Do2DRender(*m_Device);
}

//---------------- Core::iVisualizer implementation ----------------

Interface::iCamera* Renderer::GetCameraFacade() {
	return m_CameraFacade.GetInstance();
}

void Renderer::RequestSingleRedraw() const {
	LOG_NOT_IMPLEMENTED
}

Renderer::Error Renderer::SetRenderSpace(unsigned ScreenWidth, unsigned ScreenHeight, float FOV) {
	if(!_Device) {
		//TODO: do error!
		return Error::NoError;// DeviceNotInitialized;
	}
	AddAction([=] {
		_Device->ResizeDevice(ScreenWidth, ScreenHeight, FOV);
	});
	return Error::NoError;
}

Renderer::Error Renderer::Initialize(Interface::iOGLContext *Context) {
	if(_Device) return Error::NoError;//DeviceIsWorking;

	if(!Context)
		return Error::NoError;//ContextMustBeProvided;

	_Device = new RenderDevice(Context);
	m_Camera = new VirtualCamera();
	_Device->BindCamera(m_Camera);

	return Error::NoError;
}

Renderer::Error Renderer::Finalize() {
	if(!_Device) return Error::NoError;
	
	DeleteInstance();
	return Error::NoError;
}

Renderer::Error Renderer::CaptureScreenShot(const std::wstring &OutFile, Interface::iVisualizer::CaptureFileFormat format) const {
	((Renderer*)this)->AddAction([OutFile, format] {
#ifdef BUILD_x86
		//now we are safe to use opengl functions
		unsigned w, h;
		GetRenderDevice()->GetSize(w, h);
		FIBITMAP *image = FreeImage_Allocate(w, h, 24);
		void *mem = FreeImage_GetBits(image);
		glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, mem);

		struct transform {
			static inline void RGBToBGR(FIBITMAP *dib){
				BYTE *bits = FreeImage_GetBits(dib);
				int width = FreeImage_GetWidth(dib);
				int height = FreeImage_GetHeight(dib);
				for(int i = 0, j = height * width; i < j; ++i){
					BYTE b = bits[0];
					bits[0] = bits[2];
					bits[2] = b;
					bits += 3;
				}
			}
			static inline void RGBAToBGRA(FIBITMAP *dib){
				BYTE *bits = FreeImage_GetBits(dib);
				int width = FreeImage_GetWidth(dib);
				int height = FreeImage_GetHeight(dib);

				for(int i = 0, j = height * width; i < j; ++i){
					BYTE b = bits[0];
					bits[0] = bits[2];
					bits[2] = b;
					bits += 4;
				}
			}
		};
		transform::RGBToBGR(image);
		
		std::string tempf = Convert::ws2s(OutFile);

		using VisApp::Interface::iVisualizer;
		switch (format) {
		case iVisualizer::CaptureFileFormat::PNG:
			FreeImage_Save(FIF_PNG, image, tempf.c_str(), 0);
			break;
		case iVisualizer::CaptureFileFormat::JPG:
			FreeImage_Save(FIF_JPEG, image, tempf.c_str(), 0);
			break;
		case iVisualizer::CaptureFileFormat::BMP:
		default:
			FreeImage_Save(FIF_BMP, image, tempf.c_str(), 0);
			break;
		}
		FreeImage_Unload(image);
#else
		AddLog(Error, "In 64bit mode FreeImage is not available!!");
		Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Notification)
			<< "64 bitowy build aplikacji nie obs³uguje przechwytywania ekranu silnika graficznego.";
#endif
	});
	return Error::NoError;
}

Renderer::Error Renderer::PickLayersAt(Interface::LocalDataQuerry &output, const Math::uvec2 &MousePos) const {
	if(m_ActiveLayers.empty()) {
		return Error::FatalError;
	}
	Error result = Error::FatalError;

	((Renderer*)this)->AddAction([this, &output, &MousePos, &result] {
		//m_Camera
		auto cpos = m_Camera->GetPosition();
		Math::ivec2 ds = _Device->GetSize();
		Math::fvec2 hds = ds / 2;
		Math::fvec2 worldMousPos(MousePos);
		worldMousPos = -hds + worldMousPos;
		worldMousPos /= m_Camera->GetOrbitAngle()[2];
		worldMousPos -= Math::fvec2(m_Camera->GetPosition());

		for(auto &it: m_ActiveLayers) {

			auto layer = it.first;
			auto size = layer->GetSize();

			switch (layer->GetLayerType()) {
			case LayerType::d2:
				break;
			default: 
				continue;
			}
			using Interface::LocalDataQuerry;
			LocalDataQuerry::QuerryDataPointer qdp;

			auto lsize = layer->GetSize();
			auto hlsize = lsize / 2.0f;
			Math::fvec3 lpos = Math::fvec3(worldMousPos, 0) + hlsize;

	//	AddLog(Debug, "layer " << layer->GetName() << "  l:" << lpos << "     M:" << worldMousPos << "   s:" << lsize);

			if(lpos[0] < 0 || lpos[1] < 0) continue;
			if(lpos[0] > lsize[0] || lpos[1] >lsize[1]) continue;
	
			qdp.layer = layer;
			qdp.DataCoords = Math::uvec3(lpos);
			qdp.DataSources.reserve(layer->GetDataSources().size());
			for(auto &it: layer->GetDataSources()) {
				try {
					auto ptr = it.Translate();
					qdp.DataSources.push_back(ptr.Channel);
				}
				catch(...) { }
			}
			output.table.push_back(qdp);
			result = Error::NoError;
		}
	})->WaitForDispatch();
	return result;
}

//-------------------

bool Renderer::AddLayer(LayerInterface *layer, LayerInterfaceImpl *liImpl) {
	AddAction([this, layer, liImpl] {
		try {
			if(layer->Initialize(*GetRenderDevice()) != LayerInterface::Error::NoError) throw false;
			AddLog(Hint, L"Succesfully initialized layer: " << layer->GetName());
			scoped_lock lock(m_mutex);
			if(m_ActiveLayers.empty())
				CenterView(layer);
			liImpl->visible = true;
			Impl::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
			m_ActiveLayers.push_back(std::make_pair(layer, liImpl));
			liImpl->RenderIndex = m_ActiveLayers.size() - 1;
			return;
		}
		catch(const OpenGLFunctionAssertException &e) {
			Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreMessageClass::Error)
				<< L"Wyst¹pi³ b³¹d podczas inicjalizacji warstwy '" << layer->GetName() << L"'\nPrzyczyn¹ jest brak funkcji " << e.name << L" w implementacji OpenGL'a";
				AddLog(Error, L"Unable to initialize layer '" << layer->GetName() << "'. Required function '" << e.name << "' is not available");
		}
		catch(...) {
			Impl::CoreManager::Instance()->NotifyGUI(Interface::CoreMessageClass::Error)
				<< L"Wyst¹pi³ b³¹d podczas inicjalizacji warstwy '" << layer->GetName() << "'";
			AddLog(Error, L"Unable to initialize layer: " << layer->GetName());
		}
		liImpl->visible = false;
		Impl::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
	});
	return true;
}

bool Renderer::RemoveLayer(LayerInterface *layer, bool Async) {
	std::mutex local_mutex;
	scoped_lock local_lock(local_mutex);
	std::condition_variable var;

	AddAction([this, layer, &var, Async] {
		scoped_lock lock(m_mutex);
		for(auto it = m_ActiveLayers.begin(), jt = m_ActiveLayers.end(); it != jt; ++it)
			if(it->first == layer) {
				it->first->Finalize(*GetRenderDevice());
				it->second->RenderIndex = -1;
				it->second->visible = false;
				Impl::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
				m_ActiveLayers.erase(it);
				if(m_Camera && m_ActiveLayers.empty()) {
					m_Camera->Reset();
				}

				if(!Async)
					var.notify_all();
				return;
			}
	});

	if(!Async)
		var.wait(local_lock);
	return true;
}

void Renderer::MoveLayer(LayerInterface *layer, int value) {
	AddAction([this, layer, value] {
		scoped_lock lock(m_mutex);
		unsigned index = 0;
		LayerData item;
		bool found = false;
		for(auto it = m_ActiveLayers.begin(), jt = m_ActiveLayers.end(); it != jt; ++it)
			if(it->first == layer) {
				item = *it;
				m_ActiveLayers.erase(it);
				found = true;
				break;
			} else index++;
		if(!found)
			return;
		if((int)index < value) index = 0;
		index += value;
		if(index >= m_ActiveLayers.size()) index = m_ActiveLayers.size();
		auto it = m_ActiveLayers.begin();
		std::advance(it, index);
		m_ActiveLayers.insert(it, item);
		index = 0;
		for(auto it = m_ActiveLayers.begin(), jt = m_ActiveLayers.end(); it != jt; ++it, index++) 
			it->second->RenderIndex = index;
		Impl::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
	});
}

void Renderer::CenterView(LayerInterface *layer) {
	AddAction([this, layer] {
		Math::fvec3 size;
		auto alayer = layer;
		auto camera = GetRenderDevice()->GetCurrentCamera();
		camera->Reset();
		if(m_ActiveLayers.size() > 0)
			alayer = m_ActiveLayers.front().first;
		if(camera->UsePerspective()) {
			if(alayer)
				size = alayer->GetSize();
			camera->Magnify(Math::Max(size[0], size[1]));
		} else {
			camera->Magnify(1);
		}
	});
}

void Renderer::BeforeRun() {
	//nothing here
}

void Renderer::Run() {
	GetRenderDevice()->InitGL();
	//GetRenderDevice()->Bind(_ShaderMgr->GetDefaultShader(), m_Camera);
	m_Status = RendererStatus::Rendering;
	try {
		while(1) {
			CheckInstance();
			m_ActionQueue->DispatchPendingActions();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000/10));	
			scoped_lock lock(m_mutex);
			DoRender();
		}
	}
	catch(ExitException &) {
	}
}

void Renderer::AfterRun() {
	m_Status = RendererStatus::Broken;
	FinalizeActiveLayers();
	if(_Device) {
		GetRenderDevice()->FinalizeGL();
		delete m_Camera;
		delete _Device;
		_Device = 0;
	}

	Impl::CoreManager::Instance()->AddAction([] {
		_Instance = std::shared_ptr<Renderer>();
		AddLog(Debug, "deleting renderer instance")
	});

	m_ExitCondition.notify_all();
}

void Renderer::FinalizeActiveLayers() {
	for(auto &it: m_ActiveLayers) {
		it.first->Finalize(*_Device);
		it.second->RenderIndex = -1;
		it.second->visible = false;
	}
	m_ActiveLayers.clear();
}

} //namespace Renderer
} //namespace VisApp
