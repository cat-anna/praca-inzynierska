/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/AboutWindow.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "Helpers.h"

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AboutWindow
	/// </summary>
	public ref class AboutWindow : public System::Windows::Forms::Form
	{
	public:
		AboutWindow(System::Windows::Forms::Form ^aOwner) {
			this->Owner = aOwner;
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AboutWindow() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel2;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabControl^  tabControl2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  labelBuildInfo;

	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPage4;

	private: System::Windows::Forms::Label^  labelVersion;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;



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
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->labelVersion = (gcnew System::Windows::Forms::Label());
			this->labelBuildInfo = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panel2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 347);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(529, 39);
			this->panel2->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(445, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Zamknij";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->tabControl2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Padding = System::Windows::Forms::Padding(5);
			this->panel1->Size = System::Drawing::Size(529, 347);
			this->panel1->TabIndex = 2;
			// 
			// tabControl2
			// 
			this->tabControl2->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabControl2->Controls->Add(this->tabPage3);
			this->tabControl2->Controls->Add(this->tabPage4);
			this->tabControl2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl2->Location = System::Drawing::Point(5, 5);
			this->tabControl2->Name = L"tabControl2";
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(519, 337);
			this->tabControl2->TabIndex = 1;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->labelVersion);
			this->tabPage3->Controls->Add(this->labelBuildInfo);
			this->tabPage3->Controls->Add(this->linkLabel1);
			this->tabPage3->Controls->Add(this->label2);
			this->tabPage3->Controls->Add(this->label1);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(511, 308);
			this->tabPage3->TabIndex = 0;
			this->tabPage3->Text = L"VisApp";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// labelVersion
			// 
			this->labelVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->labelVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->labelVersion->Location = System::Drawing::Point(-1, 78);
			this->labelVersion->Name = L"labelVersion";
			this->labelVersion->Size = System::Drawing::Size(505, 16);
			this->labelVersion->TabIndex = 5;
			this->labelVersion->Text = L"v1.0";
			this->labelVersion->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// labelBuildInfo
			// 
			this->labelBuildInfo->AutoSize = true;
			this->labelBuildInfo->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->labelBuildInfo->Location = System::Drawing::Point(3, 292);
			this->labelBuildInfo->Name = L"labelBuildInfo";
			this->labelBuildInfo->Size = System::Drawing::Size(35, 13);
			this->labelBuildInfo->TabIndex = 4;
			this->labelBuildInfo->Text = L"label3";
			// 
			// linkLabel1
			// 
			this->linkLabel1->Location = System::Drawing::Point(6, 117);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(500, 23);
			this->linkLabel1->TabIndex = 3;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"mailto: pgrabas@gmail.com";
			this->linkLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutWindow::linkLabel1_LinkClicked);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(3, 94);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(505, 23);
			this->label2->TabIndex = 2;
			this->label2->Text = L"by Pawe³ Grabas";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(3, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(505, 36);
			this->label1->TabIndex = 1;
			this->label1->Text = L"VisApp";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->flowLayoutPanel1);
			this->tabPage4->Controls->Add(this->label5);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(511, 308);
			this->tabPage4->TabIndex = 1;
			this->tabPage4->Text = L"Biblioteki";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->label6);
			this->flowLayoutPanel1->Controls->Add(this->label3);
			this->flowLayoutPanel1->Controls->Add(this->label4);
			this->flowLayoutPanel1->Controls->Add(this->label7);
			this->flowLayoutPanel1->Controls->Add(this->label8);
			this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel1->Location = System::Drawing::Point(9, 85);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(496, 180);
			this->flowLayoutPanel1->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label6->Location = System::Drawing::Point(3, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(493, 15);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Boost C++";
			this->label6->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label6->Click += gcnew System::EventHandler(this, &AboutWindow::label6_Click);
			// 
			// label3
			// 
			this->label3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label3->Location = System::Drawing::Point(3, 15);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(490, 15);
			this->label3->TabIndex = 0;
			this->label3->Text = L"FreeImage ";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label3->Click += gcnew System::EventHandler(this, &AboutWindow::label3_Click);
			// 
			// label4
			// 
			this->label4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label4->Location = System::Drawing::Point(3, 30);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(493, 15);
			this->label4->TabIndex = 4;
			this->label4->Text = L"PugiXML";
			this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label7
			// 
			this->label7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label7->Location = System::Drawing::Point(3, 45);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(493, 15);
			this->label7->TabIndex = 5;
			this->label7->Text = L"OpenGL Mathematics";
			this->label7->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label8
			// 
			this->label8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label8->Location = System::Drawing::Point(3, 60);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(493, 15);
			this->label8->TabIndex = 6;
			this->label8->Text = L"The OpenGL Extension Wrangler Library";
			this->label8->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(238)));
			this->label5->Location = System::Drawing::Point(6, 51);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(499, 31);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Program wykorzystuje biblioteki:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label5->Click += gcnew System::EventHandler(this, &AboutWindow::label5_Click);
			// 
			// AboutWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(529, 386);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->panel2);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AboutWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"O programie";
			this->Load += gcnew System::EventHandler(this, &AboutWindow::AboutWindow_Load);
			this->panel2->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->tabControl2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void AboutWindow_Load(System::Object^  sender, System::EventArgs^  e) {
				 labelBuildInfo->Text = "Build " BUILD_ARCH " at "__TIMESTAMP__;
				 labelVersion->Text = "wersja " +  Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
			 }
private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
			 System::Diagnostics::Process::Start(L"mailto:pgrabas@gmail.com");
		 }
private: System::Void linkLabel2_LinkClicked(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start(L"http://www.boost.org/");
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start(L"http://pugixml.org/");
		 }
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start(L"http://glm.g-truc.net/0.9.5/index.html");
		 }
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start(L"http://glew.sourceforge.net/");
		 }
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start(L"http://freeimage.sourceforge.net");
			 System::Diagnostics::Process::Start(L"freeimage-license.txt");
		 }
};
}
