/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CreateProjectWizard.h
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

	/// <summary>
	/// Summary for CreateProjectWizard
	/// </summary>
	public ref class CreateProjectWizard : public System::Windows::Forms::Form {
	public:
		CreateProjectWizard(System::Windows::Forms::Form ^Owner) {
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
			this->Owner = Owner;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateProjectWizard() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxLocation;
	private: System::Windows::Forms::TextBox^  textBoxProjectName;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxLocation = (gcnew System::Windows::Forms::TextBox());
			this->textBoxProjectName = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBoxLocation);
			this->groupBox1->Controls->Add(this->textBoxProjectName);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(288, 142);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ustawienia projektu";
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button3->Location = System::Drawing::Point(248, 100);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(25, 20);
			this->button3->TabIndex = 4;
			this->button3->Text = L"...";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &CreateProjectWizard::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 85);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(45, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Lokacja";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Nazwa";
			// 
			// textBoxLocation
			// 
			this->textBoxLocation->Location = System::Drawing::Point(29, 101);
			this->textBoxLocation->Name = L"textBoxLocation";
			this->textBoxLocation->Size = System::Drawing::Size(213, 20);
			this->textBoxLocation->TabIndex = 1;
			// 
			// textBoxProjectName
			// 
			this->textBoxProjectName->Location = System::Drawing::Point(29, 41);
			this->textBoxProjectName->Name = L"textBoxProjectName";
			this->textBoxProjectName->Size = System::Drawing::Size(213, 20);
			this->textBoxProjectName->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(142, 157);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Anuluj";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(223, 157);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Ok";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &CreateProjectWizard::button2_Click);
			// 
			// CreateProjectWizard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(310, 192);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"CreateProjectWizard";
			this->Text = L"Nowy projekt";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	public: String^ GetProjectName() { return textBoxProjectName->Text; }
	public: String^ GetLocation() { return textBoxLocation->Text + "\\" + textBoxProjectName->Text; }
	public: String^ GetProjectFile() { return GetLocation() + "\\" + GetProjectName() + ".vap"; } 

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::FolderBrowserDialog ^brw = gcnew System::Windows::Forms::FolderBrowserDialog();
				 brw->SelectedPath = textBoxLocation->Text;
				 if(brw->ShowDialog() == Windows::Forms::DialogResult::OK) {
					 textBoxLocation->Text = brw->SelectedPath;
				 }
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(System::IO::File::Exists(GetProjectFile())) {
					 if(MessageBox::Show(this, 
						 "W podanej lokalizacji istnieje ju¿ projetk. Nadpisaæ?", 
						 Application::ProductName, 
						 Windows::Forms::MessageBoxButtons::YesNo) != Windows::Forms::DialogResult::Yes)
						 return;
				 }
				 DialogResult = Windows::Forms::DialogResult::OK;
			 }
	};
}
}
