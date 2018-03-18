/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/D3PlanesSliceWindow.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#pragma managed

class D3PlanesSlice;

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace VisApp::Plugins;

	/// <summary>
	/// Summary for D3PlanesSliceWindow
	/// </summary>
	public ref class D3PlanesSliceWindow : public System::Windows::Forms::Form {
	public:
		D3PlanesSliceWindow(Form ^Owner, D3PlanesSlice *instance) {
			InitializeComponent();
			m_instance = instance;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~D3PlanesSliceWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// D3PlanesSliceWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"D3PlanesSliceWindow";
			this->Text = L"indows";
			this->ResumeLayout(false);

		}
#pragma endr	

	private:
		D3PlanesSlice *m_instance;
	};

	class D3PlanesSliceGuiHandler : public VisApp::Plugins::CLIGuiHandler {
	public:
		D3PlanesSliceGuiHandler(D3PlanesSlice *instance): CLIGuiHandler(), m_instance(instance) {
		}
 
		virtual GuiResult OpenGui(System::Windows::Forms::Form^ Owner) {
			auto form = gcnew D3PlanesSliceWindow(Owner, m_instance);
			form->ShowDialog();
			return GuiResult::Ok;
		}
	private:
		D3PlanesSlice *m_instance;
	};
}
