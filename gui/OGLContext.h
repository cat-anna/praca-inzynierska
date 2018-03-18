/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/OGLContext.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace VisApp {
namespace gui {

class OGLContext : public VisApp::Interface::iOGLContext {
public:
	static bool InitInstance(System::Windows::Forms::Form ^owner, HWND handle);

	static void FinInstance();
	static bool SetView(int w, int h);

	virtual ~OGLContext();

	virtual VisApp::Interface::iVisualizer::Error CreateOGLContext();
	virtual void KillContext();
	virtual void ContextResized(unsigned, unsigned, float);

	virtual void ContextError(VisApp::Interface::iVisualizer::Error ContextError);

	virtual void SwapBuffers();
protected:
	OGLContext(HWND handle);
private:
	HGLRC m_hRC;
	HWND m_h;
	static OGLContext *_instance;

	void InitWGL();
	void InitPixelFormat();	
};

} //namespace gui
} //namespace VisApp
