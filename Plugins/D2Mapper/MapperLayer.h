/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/MapperLayer.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#pragma once
#ifndef CubeLayer_H
#define CubeLayer_H

#pragma unmanaged

#include <VisApp\include\Tools\Planes.h>
#include <VisApp\include\Tools\Color.h>

using namespace VisApp;
using namespace VisApp::Tools;

#define Math VisApp::Math

enum class InputColorMode {
	RGB, Norm1, Norm2, Norm3,
	//Norm3==RGB?
};

enum class OutputColorMode {
	RGB, R, G, B, GrayScale, RG, GB, BR,
};

class MapperLayer : public Renderer::LayerInterface {
public:
	MapperLayer(const std::wstring& Name);
 	virtual ~MapperLayer();

	static const wchar_t *GetClassName() { return L"D2TexturedDynamicPlane"; }

	void SetSourceBits(const std::vector<Color::RGB> &input, const Math::uvec2 &PlaneSize, const Math::uvec2 &InputSize);

//LayerInterface impl
	void DoRender(Renderer::GraphicDevice &dev) const;
	virtual Error Initialize(Renderer::GraphicDevice &dev);
	virtual Error Finalize(Renderer::GraphicDevice &dev);
	virtual Error Load(const xml_node src);
	virtual Error Save(xml_node dst) const;
	virtual const wchar_t* GetLayerClassName() const { return GetClassName(); }
	virtual Renderer::LayerCLIGUIHandler* QuerryCLIGuiHandler() const;
protected:
private: 
	Math::uvec2 m_PlaneSize, m_TexSize;
	InputColorMode m_InputMode;
	OutputColorMode m_OutputMode;
	bool m_InvertColor;

	Renderer::Texture m_Texture;
	Renderer::VAO m_PlaneVAO;
	Renderer::VAO::MeshVector m_PlaneMesh;

	/*static */ mutable std::weak_ptr<Renderer::LayerCLIGUIHandler> _GuiHandlerInstance;
	mutable std::shared_ptr<Renderer::LayerCLIGUIHandler> m_GuiHandler;

	void RegenMesh();
};

class MapperLayerDescriptor : public VisApp::Plugins::LayerPluginDescriptor {
public:
	MapperLayerDescriptor() {
		SetName(L"Warstwa mappera d2");
		SetDescription(L"Dynamiczna warstwa mappera koloru");
		Register([] (const std::wstring &Name) -> Renderer::LayerInterface* {
			return new MapperLayer(Name);
		}, MapperLayer::GetClassName());
	}
};

#endif
