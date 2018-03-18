/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/RenderDevice.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef RenderDevice_H
#define RenderDevice_H

namespace VisApp {
namespace Renderer { 
 
class RenderDevice : public GraphicDevice {
public:
	RenderDevice(Interface::iOGLContext *Context, unsigned Flags = 0);
	~RenderDevice();

	void ResizeDevice(unsigned Width, unsigned Height, float FOV) {
		m_Width = Width;
		m_Height = Height;
		m_Context->ContextResized(Width, Height, FOV);
		ResetCamera(m_CurrentCamera);
		BindCamera(m_CurrentCamera);
	}

	void ResetCamera(VirtualCamera *vc) {
		vc->SetView(m_Width, m_Height);
	}

	void Bind(Shader *shader);

	void BindShader(Shader *shader);
	void BindCamera(VirtualCamera *camera);
	void Bind(Shader *shader, VirtualCamera *camera);

	void BeginFrame() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, m_Width, m_Height);
	}

	void ResetBackColor();

	void EndFrame() {
		CheckError();
		m_Context->SwapBuffers();
	}

	VirtualCamera *GetCurrentCamera() const { return m_CurrentCamera; }
	Shader *GetCurrentShader() const { return m_CurrentShader; }

	void InitGL();
	void FinalizeGL() {
		m_Context->KillContext();
	}
private:
	VirtualCamera *m_CurrentCamera;

	Interface::iOGLContext *m_Context;
};

struct ErrorUnableToInitOGL : public std::runtime_error {
	ErrorUnableToInitOGL(const char* msg) : std::runtime_error(msg) {};
};

struct ErrorOGLWrongVersion : public std::runtime_error {
	ErrorOGLWrongVersion(const char* msg) : std::runtime_error(msg) {};
};

} //namespace Renderer
} //namespace VisApp

#endif
