/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/SettingsWindow.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "CoreWaitForm.h"
#include "Helpers.h"

namespace VisApp {
	namespace gui {

		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Windows;
		using namespace System::Data;
		using namespace System::Drawing;


		enum class SettingsPage {
			Misc, Renderer,

			First = Misc,
		};

		public ref class SettingsWindow : public System::Windows::Forms::Form
		{
		public:
			static void ShowPage(SettingsPage page) {
				if(_Instance == nullptr)
					_Instance = gcnew SettingsWindow();
				//_Instance->Owner = MainForm::Instance();
				switch (page)
				{
				case SettingsPage::Misc:
					break;
				case SettingsPage::Renderer:
					_Instance->tabControl1->SelectedTab = _Instance->tabPageRendering;
					break;
				}
				_Instance->ShowDialog();
			}
			static void Show() {
				ShowPage(SettingsPage::First);
			}
			static void Hide() {
				_Instance->Visible = false;
				delete _Instance;
				_Instance = nullptr;
			}
		protected:
			static SettingsWindow ^_Instance = nullptr;
			SettingsWindow(void) {
				InitializeComponent();
				//	Owner = MainForm::Instance();
				Helpers::ProcessFormIcon(this);
			}
			~SettingsWindow() {
				if (components) {
					delete components;
				}
			}
		private: System::Windows::Forms::Panel^  panel1;
		protected: 
		private: System::Windows::Forms::TabControl^  tabControl1;
		private: System::Windows::Forms::TabPage^  tabPageRendering;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
		private: Microsoft::VisualBasic::PowerPacks::OvalShape^  ovalShapeBackColor;
		private: System::Windows::Forms::Button^  buttonOk;
		private: System::Windows::Forms::NumericUpDown^  numericUpDownDataInspectorDelay;
		private: System::Windows::Forms::CheckBox^  checkBoxUseDataInspector;

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
				this->panel1 = (gcnew System::Windows::Forms::Panel());
				this->buttonOk = (gcnew System::Windows::Forms::Button());
				this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				this->tabPageRendering = (gcnew System::Windows::Forms::TabPage());
				this->numericUpDownDataInspectorDelay = (gcnew System::Windows::Forms::NumericUpDown());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->checkBoxUseDataInspector = (gcnew System::Windows::Forms::CheckBox());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
				this->ovalShapeBackColor = (gcnew Microsoft::VisualBasic::PowerPacks::OvalShape());
				this->panel1->SuspendLayout();
				this->tabControl1->SuspendLayout();
				this->tabPageRendering->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDataInspectorDelay))->BeginInit();
				this->SuspendLayout();
				// 
				// panel1
				// 
				this->panel1->Controls->Add(this->buttonOk);
				this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
				this->panel1->Location = System::Drawing::Point(5, 308);
				this->panel1->Name = L"panel1";
				this->panel1->Size = System::Drawing::Size(435, 42);
				this->panel1->TabIndex = 0;
				// 
				// buttonOk
				// 
				this->buttonOk->Location = System::Drawing::Point(353, 10);
				this->buttonOk->Name = L"buttonOk";
				this->buttonOk->Size = System::Drawing::Size(75, 23);
				this->buttonOk->TabIndex = 0;
				this->buttonOk->Text = L"Zamknij";
				this->buttonOk->UseVisualStyleBackColor = true;
				this->buttonOk->Click += gcnew System::EventHandler(this, &SettingsWindow::buttonOk_Click);
				// 
				// tabControl1
				// 
				this->tabControl1->Controls->Add(this->tabPageRendering);
				this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tabControl1->Location = System::Drawing::Point(5, 5);
				this->tabControl1->Margin = System::Windows::Forms::Padding(7);
				this->tabControl1->Name = L"tabControl1";
				this->tabControl1->SelectedIndex = 0;
				this->tabControl1->Size = System::Drawing::Size(435, 303);
				this->tabControl1->TabIndex = 1;
				// 
				// tabPageRendering
				// 
				this->tabPageRendering->Controls->Add(this->numericUpDownDataInspectorDelay);
				this->tabPageRendering->Controls->Add(this->label2);
				this->tabPageRendering->Controls->Add(this->checkBoxUseDataInspector);
				this->tabPageRendering->Controls->Add(this->label1);
				this->tabPageRendering->Controls->Add(this->shapeContainer1);
				this->tabPageRendering->Location = System::Drawing::Point(4, 22);
				this->tabPageRendering->Name = L"tabPageRendering";
				this->tabPageRendering->Padding = System::Windows::Forms::Padding(3);
				this->tabPageRendering->Size = System::Drawing::Size(427, 277);
				this->tabPageRendering->TabIndex = 1;
				this->tabPageRendering->Text = L"Ustawienia";
				this->tabPageRendering->UseVisualStyleBackColor = true;
				// 
				// numericUpDownDataInspectorDelay
				// 
				this->numericUpDownDataInspectorDelay->Location = System::Drawing::Point(151, 99);
				this->numericUpDownDataInspectorDelay->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {-1486618625, 232830643, 
					0, 0});
				this->numericUpDownDataInspectorDelay->Name = L"numericUpDownDataInspectorDelay";
				this->numericUpDownDataInspectorDelay->Size = System::Drawing::Size(102, 20);
				this->numericUpDownDataInspectorDelay->TabIndex = 4;
				this->numericUpDownDataInspectorDelay->ValueChanged += gcnew System::EventHandler(this, &SettingsWindow::numericUpDownDataInspectorDelay_ValueChanged);
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(63, 101);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(82, 13);
				this->label2->TabIndex = 3;
				this->label2->Text = L"OpóŸnienie [ms]";
				// 
				// checkBoxUseDataInspector
				// 
				this->checkBoxUseDataInspector->AutoSize = true;
				this->checkBoxUseDataInspector->Location = System::Drawing::Point(27, 81);
				this->checkBoxUseDataInspector->Name = L"checkBoxUseDataInspector";
				this->checkBoxUseDataInspector->Size = System::Drawing::Size(137, 17);
				this->checkBoxUseDataInspector->TabIndex = 2;
				this->checkBoxUseDataInspector->Text = L"W³¹cz Data Inspektora";
				this->checkBoxUseDataInspector->UseVisualStyleBackColor = true;
				this->checkBoxUseDataInspector->CheckedChanged += gcnew System::EventHandler(this, &SettingsWindow::checkBoxUseDataInspector_CheckedChanged);
				this->checkBoxUseDataInspector->Click += gcnew System::EventHandler(this, &SettingsWindow::checkBoxUseDataInspector_Click);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(24, 20);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(47, 13);
				this->label1->TabIndex = 1;
				this->label1->Text = L"Kolor t³a";
				// 
				// shapeContainer1
				// 
				this->shapeContainer1->Location = System::Drawing::Point(3, 3);
				this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
				this->shapeContainer1->Name = L"shapeContainer1";
				this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) {this->ovalShapeBackColor});
				this->shapeContainer1->Size = System::Drawing::Size(421, 271);
				this->shapeContainer1->TabIndex = 0;
				this->shapeContainer1->TabStop = false;
				// 
				// ovalShapeBackColor
				// 
				this->ovalShapeBackColor->BorderColor = System::Drawing::Color::Transparent;
				this->ovalShapeBackColor->FillColor = System::Drawing::Color::Red;
				this->ovalShapeBackColor->FillGradientColor = System::Drawing::Color::Red;
				this->ovalShapeBackColor->FillStyle = Microsoft::VisualBasic::PowerPacks::FillStyle::Solid;
				this->ovalShapeBackColor->Location = System::Drawing::Point(101, 11);
				this->ovalShapeBackColor->Name = L"ovalShapeBackColor";
				this->ovalShapeBackColor->Size = System::Drawing::Size(121, 23);
				this->ovalShapeBackColor->Click += gcnew System::EventHandler(this, &SettingsWindow::ovalShapeBackColor_Click);
				// 
				// SettingsWindow
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(445, 355);
				this->Controls->Add(this->tabControl1);
				this->Controls->Add(this->panel1);
				this->Name = L"SettingsWindow";
				this->Padding = System::Windows::Forms::Padding(5);
				this->Text = L"Ustawienia";
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SettingsWindow::SettingsWindow_FormClosing);
				this->Load += gcnew System::EventHandler(this, &SettingsWindow::SettingsWindow_Load);
				this->panel1->ResumeLayout(false);
				this->tabControl1->ResumeLayout(false);
				this->tabPageRendering->ResumeLayout(false);
				this->tabPageRendering->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownDataInspectorDelay))->EndInit();
				this->ResumeLayout(false);

			}
#pragma endregion

			//--------------------------------------------

		private: void LoadConfig() {
					 {
						 auto rc = VisApp::Settings::Renderer::GetBackgroundColor();
						 ovalShapeBackColor->FillColor = Color::FromArgb((int)(rc[0] * 255), (int)(rc[1] * 255), (int)(rc[2] * 255));
					 }
					 checkBoxUseDataInspector->Checked = VisApp::gui::Settings::root().DataInspector.Use;
					 unsigned val = VisApp::gui::Settings::root().DataInspector.ShowDelay;
					 numericUpDownDataInspectorDelay->Value = val;
				 }
		private: void SaveConfig() {
				 }

				 //-------------------------------------------


				 //-------------------------------------------

		private: System::Void SettingsWindow_Load(System::Object^  sender, System::EventArgs^  e) {
					 LoadConfig();
				 }
		private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {
					 DialogResult = Forms::DialogResult::OK;
				 }
		private: System::Void ovalShapeBackColor_Click(System::Object^  sender, System::EventArgs^  e) {
					 ColorDialog ^cd = gcnew ColorDialog();
					 cd->Color = ovalShapeBackColor->FillColor;

					 if(cd->ShowDialog() != Forms::DialogResult::OK)
						 return;
					 ovalShapeBackColor->FillColor = cd->Color;
					 VisApp::Math::fvec3 color;
					 auto in = cd->Color;
					 color[0] = in.R / 255.0f;
					 color[1] = in.G / 255.0f;
					 color[2] = in.B / 255.0f;
					 VisApp::Settings::Renderer::SetBackgroundColor(color);
				 }
		private: System::Void checkBoxUseDataInspector_Click(System::Object^  sender, System::EventArgs^  e) {

				 }
		private: System::Void numericUpDownDataInspectorDelay_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
					 unsigned val = System::Decimal::ToUInt32(numericUpDownDataInspectorDelay->Value);
					 VisApp::gui::Settings::root().DataInspector.ShowDelay = val;
				 }
		private: System::Void checkBoxUseDataInspector_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
					 numericUpDownDataInspectorDelay->Enabled = checkBoxUseDataInspector->Checked;
					 VisApp::gui::Settings::root().DataInspector.Use = checkBoxUseDataInspector->Checked;
				 }
		private: System::Void SettingsWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
					 Settings::DoSave();
				 }
};
	}
};