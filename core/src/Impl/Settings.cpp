/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Impl/Settings.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "..\Implementation.h"

namespace VisApp {
namespace Settings {
	const wchar_t *ColorXMLAttr[] = { L"R", L"G", L"B", };

	struct SettingsData {
		//renderer
		Math::fvec3 RendererBackColor;

		//private conf
		std::atomic<unsigned> RequestsInFly;
		std::wstring OutFileName;

		SettingsData():
				RendererBackColor(0.8f){
		}

		void NotifyAccess() {
			++RequestsInFly;
			Impl::CoreManager::InsertDelayedAction([this] { Save(false); }, 60 * 1000);
		}

		void Load() {
			xml_document doc;
			doc.load_file(OutFileName.c_str());
			xml_node root = doc.document_element();

			{
				xml_node R = root.child(L"Renderer");
				
				xml_node BG = R.child(L"BackColor");
				for(int i = 0; i < 3; ++i)
					RendererBackColor[i] = BG.attribute(ColorXMLAttr[i]).as_float(RendererBackColor[i]);
			}
		}

		void Save(bool force) {
			if(!force) {
				if(RequestsInFly.fetch_sub(1) > 1)
					return;
			}

			xml_document doc;
			xml_node root = doc.append_child(L"Settings");

			{
				xml_node R = root.append_child(L"Renderer");
				
				xml_node BG = R.append_child(L"BackColor");
				for(int i = 0; i < 3; ++i)
					BG.append_attribute(ColorXMLAttr[i]) = RendererBackColor[i];
			}
			doc.save_file(OutFileName.c_str());
		}

		void ConfigureSettings(const wchar_t *file) {
			OutFileName = file;
			RequestsInFly = 0;
			Load();
		}
	};
	SettingsData Data;

	void ConfigureSettings(const wchar_t *file) { Data.ConfigureSettings(file); };
	void FinalizeSettings() { Data.Save(true); Data.RequestsInFly = (int)1e6; }

	namespace Renderer {
		VISAPP_API const Math::fvec3& GetBackgroundColor() { return Data.RendererBackColor; }
		VISAPP_API void SetBackgroundColor(Math::fvec3& v) {
			Data.RendererBackColor = v;
			Data.NotifyAccess();
			//notify renderer;
			auto rend = VisApp::Renderer::Renderer::Instance();
			if(!rend) return;
			rend->GetRenderDevice()->ResetBackColor();
		}
	}
}
} //namespace VisApp 

