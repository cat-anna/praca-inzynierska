/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/OGLContext.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "stdafx.h"
#include "CoreMgt.h"
#include "MainForm.h"
#include "OGLContext.h"

using namespace gui;

namespace VisApp {
namespace gui {

OGLContext *OGLContext::_instance = 0;

bool OGLContext::InitInstance(System::Windows::Forms::Form ^owner, HWND handle) {
	if(_instance) return false;
	auto vis = CoreMgt::GetCore()->GetVisualizer();
	if(!vis) {
		MessageBox::Show(owner, "B³¹d inicjalizacji grafiki. Wizualizacje s¹ niedostêpne.");
		return false;
	} 
	_instance = new OGLContext(handle);
	vis->Initialize(_instance);
	return true;
}

void OGLContext::FinInstance() {
	if(!_instance) return;
	auto vis = CoreMgt::GetCore()->GetVisualizer();
	if(vis) {
		vis->Finalize();
	}
	delete _instance;
	_instance = 0;
}

bool OGLContext::SetView(int w, int h) {
	if(!_instance) return false;
	auto vis = CoreMgt::GetCore()->GetVisualizer();
	if(!vis) {
		//TODO: do some error!
		return false;
	}
	vis->SetRenderSpace(w, h, 45.0f);
	return true;
}

OGLContext::~OGLContext() {
	KillContext();
};

OGLContext::OGLContext(HWND handle) { 
	GetDC(m_h = handle); 
}

VisApp::Interface::iVisualizer::Error OGLContext::CreateOGLContext() {
	InitPixelFormat();
	InitWGL();
	return VisApp::Interface::iVisualizer::Error::NoError;
};

void OGLContext::KillContext() {
	wglMakeCurrent(GetDC(m_h),NULL);		//deselect rendering context
	wglDeleteContext(m_hRC);		//delete rendering context
};

void OGLContext::ContextResized(unsigned, unsigned, float){
	if (!wglMakeCurrent(GetDC(m_h), m_hRC))  { 
	// DeactivateOpenGLRendering(WindowHandle); 
	//	 ErrorMessage = "The GL Rendering Context Can't be Activated!"; 
		return; 
	} 
}

ref class ContextErrorDispatcher {
public:
	ContextErrorDispatcher(VisApp::Interface::iVisualizer::Error v) {
		error = v;
	}

	VisApp::Interface::iVisualizer::Error error;

	void dispatch() {
			switch (error)
	{
	case VisApp::Interface::iVisualizer::Error::NoError:
		break;
	case VisApp::Interface::iVisualizer::Error::OpenGLUnsupportedVersion:
		System::Windows::Forms::MessageBox::Show("B³¹d inicjalizacji OpenGL. Program wymaga OpenGL wersji 3.0 lub nowszej.");
		break;
	default:
		break;//::gui::MainForm::Instance(), 
	}
	}
};

delegate void ContextErrorDispatcherDelegate();

void OGLContext::ContextError(VisApp::Interface::iVisualizer::Error ContextError) {
	auto fun = gcnew ContextErrorDispatcherDelegate(gcnew ContextErrorDispatcher(ContextError), &ContextErrorDispatcher::dispatch);
	MainForm::Instance()->Invoke(fun);
}

void OGLContext::SwapBuffers() {
	::SwapBuffers(GetDC(m_h));
};

void OGLContext::InitWGL() {
	// we need to create the rendering context for the actual UserControl 
	if (!(m_hRC = wglCreateContext(GetDC(m_h))))  { 
	//	 DeactivateOpenGLRendering(WindowHandle); 
	//	 ErrorMessage = "The GL Rendering Context was not created!"; 
		return; 
	} 

	// we need to make the Device and also the RenderingContext 
	// current for the actual thread 
	// this action is done just once, because each OpenGL component 
	// has its own rendering thread 
	if (!wglMakeCurrent(GetDC(m_h), m_hRC))  { 
	// DeactivateOpenGLRendering(WindowHandle); 
	//	 ErrorMessage = "The GL Rendering Context Can't be Activated!"; 
		return; 
	} 
}

void OGLContext::InitPixelFormat() {
	static  PIXELFORMATDESCRIPTOR pfd = { // pfd Tells Windows How We Want Things To Be
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int  iPixelFormat;
	// get the device context's best, available pixel format match 
	if((iPixelFormat = ChoosePixelFormat(GetDC(m_h), &pfd)) == 0) {
	//	MessageBox::Show("ChoosePixelFormat Failed");
		return;
	}
	if(SetPixelFormat(GetDC(m_h), iPixelFormat, &pfd) == FALSE) {
	//	MessageBox::Show("SetPixelFormat Failed");
		return;
	}		
};

} //namespace gui
} //namespace VisApp
