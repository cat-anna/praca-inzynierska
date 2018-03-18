/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/LayerInterface.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "..\Implementation.h"

namespace VisApp {
namespace Renderer { 

LayerInterface::LayerInterface(const std::wstring& Name) :
		m_Impl(new LayerInterfaceImpl()) {
	m_Impl->Name = Name;
}

LayerInterface::~LayerInterface() {
	if(m_Impl->visible)
		Renderer::Instance()->RemoveLayer(this, false);
	delete m_Impl;
}

// iResource implementation

Interface::iResource* LayerInterface::GetOwnerResource() {
	return GetOwner()->GetOwnerProject();
}

//LayerInterface implementation

LayerInterface::Error LayerInterface::Load(const xml_node src) {
	LoadInfo(src);
	m_Impl->Name = src.child(L"Name").text().as_string(m_Impl->Name.c_str());

	Math::ReadGLMVector(src, L"Size", m_Impl->Size, Math::Captions::XYZ);
	Math::ReadGLMVector(src, L"BaseColor", m_Impl->BaseColor, Math::Captions::RGBA);

	auto SrcNode = src.child(L"Sources").child(L"Source");
	if(SrcNode)
		for(auto it = SrcNode; it; it = it.next_sibling(L"Source")) {
			m_Impl->DataSources.push_back(Interface::StringDataPointer());
			auto &ptr = m_Impl->DataSources.back();
			ptr.LoadFromXML(it);
		}

	m_Impl->LayerType = static_cast<decltype(m_Impl->LayerType)>(src.child(L"Type").attribute(L"IntVal").as_uint());
	return Error::NoError;
}

LayerInterface::Error LayerInterface::Save(xml_node dst) const {
	SaveInfo(dst);
	dst.append_attribute(L"LayerClass") = GetLayerClassName();
	dst.append_child(L"Name").text() = m_Impl->Name.c_str();

	Math::WriteGLMVector(dst, L"Size", m_Impl->Size, Math::Captions::XYZ);
	Math::WriteGLMVector(dst, L"BaseColor", m_Impl->BaseColor, Math::Captions::RGBA);

	auto SrcNode = dst.append_child(L"Sources");
	for(auto &it: m_Impl->DataSources) {
		auto item = SrcNode.append_child(L"Source");
		it.SaveToXML(item);;
	}

	dst.append_child(L"Type").append_attribute(L"IntVal") = static_cast<unsigned>(m_Impl->LayerType);
	return Error::NoError;
}

void LayerInterface::AddDataSoure(const Interface::iDataChannel *source) {
	m_Impl->DataSources.push_back(Interface::StringDataPointer(source));
}

void LayerInterface::AddDataSoure(const Interface::StringDataPointer &source) {
	m_Impl->DataSources.push_back(source);
}

const LayerInterface::DataPointerVector& LayerInterface::GetDataSources() const {
	return m_Impl->DataSources;
}

void LayerInterface::SetOwner(Interface::iDataStore* Owner) {
	if(!m_Impl->Owner && Owner) {
		m_Impl->Owner = (Project::DataStore*)Owner;
	//	m_Owner->RegisterLayer(this);
		//return true;
	}
	//return false;
}

LayerType LayerInterface::GetLayerType() const {
	return m_Impl->LayerType;
}

Interface::iDataStore* LayerInterface::GetOwner() const {
	return m_Impl->Owner;
}

bool LayerInterface::SetLayerType(LayerType value) {
	if(m_Impl->LayerType == LayerType::Unknown) {
		m_Impl->LayerType = value;
		return true;
	}
	return false;
}

void LayerInterface::SetSize(const Math::fvec3 &Value) {
	m_Impl->Size = Value;
}

void LayerInterface::SetName(const std::wstring &Value) {
	m_Impl->Name = Value;
	Impl::CoreManager::Instance()->NotifyGUI(CoreNotification::LayersChanged);
}

void LayerInterface::SetBaseColor(const Math::fvec3 &Color) {
	m_Impl->BaseColor = Color;
	if(m_Impl->visible) {
		//TODO: request single redraw, if applicable
	}
}

const Math::fvec3& LayerInterface::GetBaseColor() const {
	return m_Impl->BaseColor;
}

int LayerInterface::GetRenderIndex() const {
	return m_Impl->RenderIndex;
}

const std::wstring &LayerInterface::GetName() const {
	return m_Impl->Name;
}

const Math::fvec3 &LayerInterface::GetSize() const {
	return m_Impl->Size;
}

bool LayerInterface::IsVisible() const {
	return m_Impl->visible;
}

void LayerInterface::SetShader(Shader *shader) {
	m_Impl->shader = shader;
}

Shader* LayerInterface::GetShader() const {
	return m_Impl->shader;
}

void LayerInterface::SetReadyState() {
	m_Impl->Ready = true;
	m_Impl->Owner->ResourceChangedState(this);
}

bool LayerInterface::IsReady() const {
	return m_Impl->Ready;
}

LayerInterface::Error LayerInterface::SetVisibility(bool value) {
	if(!Renderer::Instance())
		return Error::Fatal;
	if(value == m_Impl->visible) return Error::NoError;
	if(m_Impl->visible) {
		Renderer::Instance()->RemoveLayer(this);
	} else {
		Renderer::Instance()->AddLayer(this, m_Impl);
	}
	return Error::NoError;
}

void LayerInterface::Move(int offset) {
	Renderer::Instance()->MoveLayer(this, offset);
}

LayerCLIGUIHandler* LayerInterface::QuerryCLIGuiHandler() const {
	return 0;
}

void LayerInterface::OGLAssertFunction(bool test, const char *name) {
	if(test)
		throw OpenGLFunctionAssertException(name);
}

} //namespace Renderer
} //namespace VisApp
