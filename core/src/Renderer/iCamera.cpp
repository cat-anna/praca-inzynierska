/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/iCamera.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Interface {
	
iCamera::iCamera() {
}

iCamera::~iCamera() {
}

using VisApp::Renderer::Renderer;

void iCamera::Center(VisApp::Renderer::LayerInterface *layer) {
	auto r = Renderer::Instance();
	if(!r) return;
	r->CenterView(layer);
}

void iCamera::SetPosition(const Math::fvec3 &Pos, bool DoAdd) {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([Pos, DoAdd, camera] {
		camera->SetPosition(Pos, DoAdd);
	});
}

void iCamera::SetLookAtPoint(const Math::fvec3 &Pos, bool DoAdd) {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([Pos, DoAdd, camera] {
		camera->SetLookAtPoint(Pos, DoAdd);
	});
}

void iCamera::MoveCamera(const Math::fvec3 &Pos) {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([Pos, camera] {
		camera->MoveCamera(Pos);
	});
}	

void iCamera::Orbit(const Math::fvec2 &Angles, bool DoAdd) {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([camera, Angles, DoAdd] {
		camera->Orbit(Angles, DoAdd);
	});
}

void iCamera::Magnify(float value) {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([camera, value] {
		camera->Magnify(value);
	});
}

void iCamera::SetOrthogonalMode() {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([camera] {
		camera->SetOrthogonalMode();
	});
}

void iCamera::SetPerspectiveMode() {
	auto dev = Renderer::Device();
	if(!dev) return;
	auto camera = dev->GetCurrentCamera();
	if(!camera) return;
	Renderer::PushAction([camera] {
		camera->SetPerspectiveMode();
	});
}

}
} //namespace Core 
