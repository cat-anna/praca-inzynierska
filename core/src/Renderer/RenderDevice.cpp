/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/RenderDevice.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "nRenderer.h"

namespace VisApp {
namespace Renderer { 

using Interface::iVisualizer;
using Interface::iOGLContext;

RenderDevice::RenderDevice(Interface::iOGLContext *Context, unsigned Flags) : 
		m_CurrentCamera(0),
		m_Context(Context) {
	m_CurrentShader = 0;
}

RenderDevice::~RenderDevice() {
}

void RenderDevice::Bind(Shader *shader) {
	BindShader(shader);
}

void RenderDevice::BindShader(Shader *shader) {
	m_CurrentShader = shader;
	if(m_CurrentShader) {
		m_CurrentShader->BindShader();
		if(m_CurrentCamera)
			m_CurrentShader->BindCamera(m_CurrentCamera);
	}
}

void RenderDevice::BindCamera(VirtualCamera *camera) {
	m_CurrentCamera = camera;
	if(m_CurrentShader && m_CurrentCamera) {
		m_CurrentShader->BindCamera(m_CurrentCamera);
	}
}

void RenderDevice::Bind(Shader *shader, VirtualCamera *camera) {
	m_CurrentShader = shader;
	m_CurrentCamera = camera;

	if(m_CurrentShader && m_CurrentCamera) {
		m_CurrentShader->BindShader();
		m_CurrentShader->BindCamera(m_CurrentCamera);
	}
}

void RenderDevice::ResetBackColor() {
	Renderer::PushAction([] {
		auto color = Settings::Renderer::GetBackgroundColor();
		glClearColor(color[0], color[1], color[2], 0.0f);
	});
}

void RenderDevice::InitGL() {
	if(m_Context->CreateOGLContext() != iVisualizer::Error::NoError)
		throw ErrorUnableToInitOGL("Context Creation failed!");

	GLenum glewCode;
#ifdef GLEW_MX
	glewCode = glewContextInit(&_GLContext); //glewInit();
#else
	glewCode = glewInit();
#endif
	
	if(glewCode != GLEW_OK)
		throw ErrorUnableToInitOGL("GLEW initialization error!");

#define LogOGLText(VALUE, LOGNAME) \
	{\
		const char *text = (char*)glGetString(VALUE);\
		if(!text) { AddLog(Warning, "Unable to get OpenGL string " #VALUE); }\
		else { AddLog(Hint, "OpenGL " << LOGNAME << " is " << text); }\
	}

	LogOGLText(GL_VERSION, "version");
	LogOGLText(GL_SHADING_LANGUAGE_VERSION, "GLSL version");
	LogOGLText(GL_RENDERER, "renderer");

	try {
		AddLog(Hint, "Testing OpenGL functions avability");
		Shader::TestOpenGLFunctions();
		AddLog(Hint, "All tests passed");
	}
	catch(const OpenGLFunctionAssertException& e) {
		AddLog(Error, "OpenGL function test ended eror! Function " << e.name << " is not available!");
		m_Context->ContextError(iVisualizer::Error::OpenGLUnsupportedVersion);
		throw ErrorOGLWrongVersion("Unsupported OpenGL version!");
	}
	catch(...) { 
		AddLog(CriticalError, "OpenGL function test ended with unexpected error!");
		m_Context->ContextError(iVisualizer::Error::OpenGLUnsupportedVersion);
		throw ErrorOGLWrongVersion("Unsupported OpenGL version!");
	}

	if(!(GLEW_VERSION_3_0)) {
		//wrong version
		//m_Context->ContextError(iVisualizer::Error::OpenGLUnsupportedVersion);
		Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Notification)
			<< L"Program wykry³, ¿e wersja OpenGL jest starsza ni¿ 3.0.\nProgram mo¿e nie dzia³aæ stabilnie!";
		AddLog(Warning, "OpenGL version is below 3.0. Application may be unstable!");
		//throw ErrorOGLWrongVersion("Unsupported OpenGL version. Program cannot run on opengl below 3.0!");
	}

//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClearColor(135.0f/255.0f, 168.0f/255.0f, 205.0f/255.0f, 0.0f/255.0f);
//	glClearColor(200.0f/255.0f, 200.0f/255.0f, 200.0f/255.0f, 0.0f/255.0f);

	ResetBackColor();

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);   
	glDepthFunc(GL_LEQUAL);

//	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);

/*
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.4f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
*/
}

} //namespace Renderer
} //namespace VisApp
