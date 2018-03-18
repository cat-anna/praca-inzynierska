/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CoreManip.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "Helpers.h"

namespace VisApp {
namespace gui {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows;

	public ref class Manip {
	public:
		ref class Layer {
		public:
			typedef VisApp::Renderer::LayerInterface LayerInterface;
			static bool EditColor(Forms::Form^ form, LayerInterface *layer) {
				 VisApp::Math::fvec3 color = layer->GetBaseColor();
				 ColorDialog ^cd = gcnew ColorDialog();

				 cd->Color = Color::FromArgb(255, (int)(255 * color[0]), (int)(255 * color[1]), (int)(255 * color[2]));
				 if(cd->ShowDialog(form) != Forms::DialogResult::OK)
					 return false;
				 color[0] = cd->Color.R / 255.0f;
				 color[1] = cd->Color.G / 255.0f;
				 color[2] = cd->Color.B / 255.0f;
				 layer->SetBaseColor(color);
				 return true;
			}
			static bool EditName(Forms::Form^ form, LayerInterface *layer) {
				 String ^inp = Helpers::ToString(layer->GetName());
				 if(InputBox(form, L"Podaj now¹ nazwê", inp) != Forms::DialogResult::OK)
					 return false;
				 layer->SetName(Helpers::ToString(inp));
				 return true;
			}
		};

		ref class Series {
		public:
			typedef VisApp::Interface::iDataSeries iDataSeries;
			static bool EditName(Forms::Form^ form, iDataSeries *series) {
				 String ^inp = Helpers::ToString(series->GetName());
				 if(InputBox(form, L"Podaj now¹ nazwê", inp) != Forms::DialogResult::OK)
					 return false;
				 series->SetName(Helpers::ToString(inp));
				 return true;
			}
		};

		ref class Channel {
		public:
			typedef VisApp::Interface::iDataChannel iDataChannel;
			static bool EditName(Forms::Form^ form, iDataChannel *channel) {
				 String ^inp = Helpers::ToString(channel->GetName());
				 if(InputBox(form, L"Podaj now¹ nazwê", inp) != Forms::DialogResult::OK)
					 return false;
				 channel->SetName(Helpers::ToString(inp));
				 return true;
			}
		};
	};

}
}