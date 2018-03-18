/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/LayerInterfaceImpl.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Renderer { 
 
LayerInterfaceImpl::LayerInterfaceImpl():
		Name(L"?"),
		LayerType(LayerType::Unknown),
		visible(false),
		BaseColor(1, 1, 1),
		Size() {
	RenderIndex = -1;
	Owner = 0;
};

} //namespace Renderer
} //namespace VisApp
