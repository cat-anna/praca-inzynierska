/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/LayerClassList.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Renderer {

typedef std::map<std::wstring, LayerConstructorFunction> LayerConstructorClassMap;
 
LayerConstructorClassMap *_StaticClassRegister = 0;
 
LayerConstructorClassMap& GetStaticClassRegister() {
	if(!_StaticClassRegister)
		_StaticClassRegister = new LayerConstructorClassMap();
	return *_StaticClassRegister;
}

void LayerClassList::Reset() {
	AddLog(Debug, "Reseting layer class list");
	GetStaticClassRegister().clear();
	delete _StaticClassRegister;
	_StaticClassRegister = 0;
}

void LayerClassList::RegisterClassConstructor(const std::wstring &ClassName, LayerConstructorFunction ConstructorFun) {
	GetStaticClassRegister().insert(std::make_pair(ClassName, ConstructorFun));
	AddLog(Hint, "Registered layer class: " << ClassName);
}

void LayerClassList::DeregisterClassConstructor(const std::wstring &ClassName) {
	AddLog(Hint, "Removing layer class: " << ClassName);
	if(!_StaticClassRegister)
		return;//nothing todo
	auto list = GetStaticClassRegister();
	auto it = list.find(ClassName);
	if(it == list.end()) {
		AddLog(Error, "Attempt to deregister not registered layer class: " << ClassName);
		return;
	} 
	list.erase(it);
}

SharedLayerInterface LayerClassList::ConstructLayer(const std::wstring& ClassName, const std::wstring& Name, Library *Owner) {
	auto &list = GetStaticClassRegister();
	auto id = list.find(ClassName);
	if(id == list.end()) throw NoSuchClassNameException();
	try {
		auto res = SharedLayerInterface(id->second(Name));
		if(!res) throw false;
		return res;
	}
	catch(...) {
		Impl::CoreManager::Instance()->NotifyGUI(CoreMessageClass::Error) << L"B³¹t tworzenia instancji warstwy o klasie '" << ClassName << "'";
		return SharedLayerInterface();
	}
}

} //namespace Renderer 
} //namespace VisApp 

