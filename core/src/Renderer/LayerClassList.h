/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/LayerClassList.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef LayerClassList_H
#define LayerClassList_H

namespace VisApp {
namespace Renderer {

class LayerInterface;
typedef std::shared_ptr<LayerInterface> SharedLayerInterface;

typedef std::function<LayerInterface*(const std::wstring &LayerName )> LayerConstructorFunction;

class LayerClassList {
public:
	struct NoSuchClassNameException { };

	//TODO: because i don't know why i put Owner parameter it is unused, user shall pass null pointer
	static SharedLayerInterface ConstructLayer(const std::wstring& ClassName, const std::wstring& Name, Library *Owner);

	static void RegisterClassConstructor(const std::wstring &ClassName, LayerConstructorFunction ConstructorFun);
	static void DeregisterClassConstructor(const std::wstring &ClassName);//not implemented

	static void Reset();
	
	struct AutoClassRegister {
		AutoClassRegister(const std::wstring &ClassName, LayerConstructorFunction fun) {
			RegisterClassConstructor(ClassName, fun);
		}
	};
private: 
 	LayerClassList();
 	~LayerClassList();
};

} //namespace Renderer 
} //namespace VisApp 

#endif
