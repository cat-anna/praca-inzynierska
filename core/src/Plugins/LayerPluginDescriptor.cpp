/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Plugins/LayerPluginDescriptor.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Plugins {

LayerPluginDescriptor::LayerPluginDescriptor() : PluginDescriptor(PluginType::Layer), m_ClassName() {
}

LayerPluginDescriptor::~LayerPluginDescriptor() {
}

void LayerPluginDescriptor::Register(LayerConstructorFun fun, const std::wstring &LayerClassName) {
	if(!m_ClassName.empty())
		return;
	m_ClassName = LayerClassName;
	m_fun.swap(fun);
}

void LayerPluginDescriptor::RegisterDescriptor() {
	if(m_ClassName.empty())
		return;
	Renderer::LayerClassList::RegisterClassConstructor(m_ClassName, m_fun);
}

void LayerPluginDescriptor::UnregisterDescriptor() {
	Renderer::LayerClassList::DeregisterClassConstructor(m_ClassName);
}

}// namespace Plugins
}// namespace VisApp
