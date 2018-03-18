/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/GraphicDevice.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "../Implementation.h"

namespace VisApp {
namespace Renderer {

GraphicDevice::GraphicDevice() {
	m_ShaderMgt = ShaderManager::ConstructInstance();
}

GraphicDevice::~GraphicDevice() {
	delete m_ShaderMgt;
}

void GraphicDevice::CheckError() const {
	GLenum err = glGetError();
	if(err == GL_NO_ERROR) return;

	const char *errstr = (char*)gluErrorString(err);
	AddLog(Warning, L"GLError: " << errstr);
}

} //namespace Renderer 
} //namespace VisApp 

