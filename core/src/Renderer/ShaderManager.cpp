/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/ShaderManager.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "nRenderer.h"

//#pragma comment(lib, "glfx-0.75\\x64\\glfx.lib")
//#pragma comment(lib, "glfx-0.75\\x86\\glfx.lib")

namespace VisApp {
namespace Renderer { 

ShaderManager::ShaderManager() {

}

ShaderManager::~ShaderManager() {
} 

ShaderManager* ShaderManager::ConstructInstance() {
	return new ShaderManager();
}

Shader* ShaderManager::GetShader(const std::wstring &Name, std::function<bool(Shader*)> ShaderInitFun) {
	auto it = m_ShaderList.find(Name);
	if(it != m_ShaderList.end())
		return it->second;

	Shader *s = new Shader(Name);
	if(!ShaderInitFun(s)) {
		AddLog(Error, "Unable to initialize shader " << Name);
		delete s;
		return 0;
	}
	m_ShaderList.insert(std::make_pair(Name, s));
	s->BindShader();
	return s;
}

} //namespace Renderer
} //namespace VisApp
