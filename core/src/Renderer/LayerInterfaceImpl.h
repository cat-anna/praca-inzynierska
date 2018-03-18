/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/LayerInterfaceImpl.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef LayerInterfaceImpl_H
#define LayerInterfaceImpl_H

namespace VisApp {
namespace Renderer { 
 
class LayerInterfaceImpl {
	friend class LayerInterface;
public:
	typedef LayerInterface::Error Error;

	std::wstring Name;
	Math::fvec3 Size, BaseColor;
	LayerType LayerType;
	bool visible;
	Shader *shader;
	int RenderIndex;
	bool Ready;
	Project::DataStore *Owner;

	LayerInterface::DataPointerVector DataSources;

	LayerInterfaceImpl();
protected:
};

} //namespace Renderer
} //namespace VisApp

#endif
