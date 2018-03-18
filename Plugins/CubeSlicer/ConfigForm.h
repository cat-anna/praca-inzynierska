/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/CubeSlicer/ConfigForm.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#pragma managed

namespace CubeSlicer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ConfigForm
	/// </summary>
	public ref class ConfigForm : public System::Windows::Forms::Form
	{
	public:
		ConfigForm(System::Windows::Forms::Form^ aOwner, CubeLayer *Instance, VisApp::gui::CLIGuiOperations *GuiOp)
		{
			InitializeComponent();
			Owner = aOwner;
			m_Op = GuiOp;
			m_Layer = Instance;
			m_Disable = false;
		}

	protected:
		VisApp::gui::CLIGuiOperations* m_Op;
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TabPage^  tabPage3Planes;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  checkBoxXZHide;
	private: System::Windows::Forms::CheckBox^  checkBoxZYHide;
	private: System::Windows::Forms::Label^  labelYZInfo;
	private: System::Windows::Forms::Label^  labelXZInfo;
	private: System::Windows::Forms::Label^  labelXYInfo;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  checkBoxXYHide;
	private: System::Windows::Forms::TrackBar^  trackBarYZPlane;
	private: System::Windows::Forms::TrackBar^  trackBarXZPlane;
	private: System::Windows::Forms::TrackBar^  trackBarXYPlane;

	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::RadioButton^  radioButtonOuterView;
	private: System::Windows::Forms::RadioButton^  radioButton3Planes;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::CheckBox^  checkBoxOuterEdges;
	private: System::Windows::Forms::CheckBox^  checkBoxShowInternalEdges;

	protected: 
		CubeLayer *m_Layer;
		~ConfigForm()
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->checkBoxOuterEdges = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->radioButtonOuterView = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3Planes = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->tabPage3Planes = (gcnew System::Windows::Forms::TabPage());
			this->checkBoxShowInternalEdges = (gcnew System::Windows::Forms::CheckBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->checkBoxXZHide = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxZYHide = (gcnew System::Windows::Forms::CheckBox());
			this->labelYZInfo = (gcnew System::Windows::Forms::Label());
			this->labelXZInfo = (gcnew System::Windows::Forms::Label());
			this->labelXYInfo = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBoxXYHide = (gcnew System::Windows::Forms::CheckBox());
			this->trackBarYZPlane = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarXZPlane = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarXYPlane = (gcnew System::Windows::Forms::TrackBar());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tabPage3Planes->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarYZPlane))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarXZPlane))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarXYPlane))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->checkBoxOuterEdges);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 453);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(438, 43);
			this->panel1->TabIndex = 6;
			// 
			// checkBoxOuterEdges
			// 
			this->checkBoxOuterEdges->AutoSize = true;
			this->checkBoxOuterEdges->Location = System::Drawing::Point(5, 13);
			this->checkBoxOuterEdges->Name = L"checkBoxOuterEdges";
			this->checkBoxOuterEdges->Size = System::Drawing::Size(164, 17);
			this->checkBoxOuterEdges->TabIndex = 1;
			this->checkBoxOuterEdges->Text = L"Poka¿ zewnêtrzne krawêdzie";
			this->checkBoxOuterEdges->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(337, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 28);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Zamknij";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ConfigForm::button1_Click);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->tabControl1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Padding = System::Windows::Forms::Padding(5);
			this->panel2->Size = System::Drawing::Size(438, 453);
			this->panel2->TabIndex = 7;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage3Planes);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(5, 5);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(428, 443);
			this->tabControl1->TabIndex = 5;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->label1);
			this->tabPage3->Controls->Add(this->tableLayoutPanel1);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(420, 417);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Ustawienia";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Aktywny widok";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->Controls->Add(this->radioButtonOuterView, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->radioButton3Planes, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->radioButton3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->radioButton4, 0, 3);
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 37);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->Padding = System::Windows::Forms::Padding(5);
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(420, 109);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// radioButtonOuterView
			// 
			this->radioButtonOuterView->AutoSize = true;
			this->radioButtonOuterView->Location = System::Drawing::Point(8, 8);
			this->radioButtonOuterView->Name = L"radioButtonOuterView";
			this->radioButtonOuterView->Size = System::Drawing::Size(75, 17);
			this->radioButtonOuterView->TabIndex = 0;
			this->radioButtonOuterView->Tag = L"1";
			this->radioButtonOuterView->Text = L"z zewn¹trz";
			this->radioButtonOuterView->UseVisualStyleBackColor = true;
			this->radioButtonOuterView->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::ModeChange);
			// 
			// radioButton3Planes
			// 
			this->radioButton3Planes->AutoSize = true;
			this->radioButton3Planes->Checked = true;
			this->radioButton3Planes->Location = System::Drawing::Point(8, 32);
			this->radioButton3Planes->Name = L"radioButton3Planes";
			this->radioButton3Planes->Size = System::Drawing::Size(92, 17);
			this->radioButton3Planes->TabIndex = 2;
			this->radioButton3Planes->TabStop = true;
			this->radioButton3Planes->Tag = L"2";
			this->radioButton3Planes->Text = L"3 p³aszczyzny";
			this->radioButton3Planes->UseVisualStyleBackColor = true;
			this->radioButton3Planes->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::ModeChange);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(8, 56);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(85, 17);
			this->radioButton3->TabIndex = 3;
			this->radioButton3->Tag = L"3";
			this->radioButton3->Text = L"radioButton3";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->Visible = false;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(8, 80);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(85, 17);
			this->radioButton4->TabIndex = 4;
			this->radioButton4->Tag = L"4";
			this->radioButton4->Text = L"radioButton4";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->Visible = false;
			// 
			// tabPage3Planes
			// 
			this->tabPage3Planes->Controls->Add(this->checkBoxShowInternalEdges);
			this->tabPage3Planes->Controls->Add(this->label8);
			this->tabPage3Planes->Controls->Add(this->label7);
			this->tabPage3Planes->Controls->Add(this->checkBoxXZHide);
			this->tabPage3Planes->Controls->Add(this->checkBoxZYHide);
			this->tabPage3Planes->Controls->Add(this->labelYZInfo);
			this->tabPage3Planes->Controls->Add(this->labelXZInfo);
			this->tabPage3Planes->Controls->Add(this->labelXYInfo);
			this->tabPage3Planes->Controls->Add(this->label2);
			this->tabPage3Planes->Controls->Add(this->checkBoxXYHide);
			this->tabPage3Planes->Controls->Add(this->trackBarYZPlane);
			this->tabPage3Planes->Controls->Add(this->trackBarXZPlane);
			this->tabPage3Planes->Controls->Add(this->trackBarXYPlane);
			this->tabPage3Planes->Location = System::Drawing::Point(4, 22);
			this->tabPage3Planes->Name = L"tabPage3Planes";
			this->tabPage3Planes->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3Planes->Size = System::Drawing::Size(420, 417);
			this->tabPage3Planes->TabIndex = 0;
			this->tabPage3Planes->Text = L"3 p³aszczyzny";
			this->tabPage3Planes->UseVisualStyleBackColor = true;
			// 
			// checkBoxShowInternalEdges
			// 
			this->checkBoxShowInternalEdges->AutoSize = true;
			this->checkBoxShowInternalEdges->Location = System::Drawing::Point(9, 385);
			this->checkBoxShowInternalEdges->Name = L"checkBoxShowInternalEdges";
			this->checkBoxShowInternalEdges->Size = System::Drawing::Size(167, 17);
			this->checkBoxShowInternalEdges->TabIndex = 24;
			this->checkBoxShowInternalEdges->Text = L"Poka¿ wewnêtrzne krawêdzie";
			this->checkBoxShowInternalEdges->UseVisualStyleBackColor = true;
			this->checkBoxShowInternalEdges->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 286);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(84, 13);
			this->label8->TabIndex = 23;
			this->label8->Text = L"P³aszczyzna YZ";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 147);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(84, 13);
			this->label7->TabIndex = 22;
			this->label7->Text = L"P³aszczyzna XZ";
			// 
			// checkBoxXZHide
			// 
			this->checkBoxXZHide->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxXZHide->AutoSize = true;
			this->checkBoxXZHide->Location = System::Drawing::Point(361, 146);
			this->checkBoxXZHide->Name = L"checkBoxXZHide";
			this->checkBoxXZHide->Size = System::Drawing::Size(50, 17);
			this->checkBoxXZHide->TabIndex = 21;
			this->checkBoxXZHide->Text = L"Ukryj";
			this->checkBoxXZHide->UseVisualStyleBackColor = true;
			this->checkBoxXZHide->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// checkBoxZYHide
			// 
			this->checkBoxZYHide->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxZYHide->AutoSize = true;
			this->checkBoxZYHide->Location = System::Drawing::Point(361, 285);
			this->checkBoxZYHide->Name = L"checkBoxZYHide";
			this->checkBoxZYHide->Size = System::Drawing::Size(50, 17);
			this->checkBoxZYHide->TabIndex = 20;
			this->checkBoxZYHide->Text = L"Ukryj";
			this->checkBoxZYHide->UseVisualStyleBackColor = true;
			this->checkBoxZYHide->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// labelYZInfo
			// 
			this->labelYZInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->labelYZInfo->Location = System::Drawing::Point(96, 283);
			this->labelYZInfo->Name = L"labelYZInfo";
			this->labelYZInfo->Size = System::Drawing::Size(258, 13);
			this->labelYZInfo->TabIndex = 18;
			this->labelYZInfo->Text = L"label5";
			this->labelYZInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelXZInfo
			// 
			this->labelXZInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->labelXZInfo->Location = System::Drawing::Point(99, 147);
			this->labelXZInfo->Name = L"labelXZInfo";
			this->labelXZInfo->Size = System::Drawing::Size(255, 13);
			this->labelXZInfo->TabIndex = 17;
			this->labelXZInfo->Text = L"label4";
			this->labelXZInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelXYInfo
			// 
			this->labelXYInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->labelXYInfo->Location = System::Drawing::Point(96, 32);
			this->labelXYInfo->Name = L"labelXYInfo";
			this->labelXYInfo->Size = System::Drawing::Size(258, 13);
			this->labelXYInfo->TabIndex = 16;
			this->labelXYInfo->Text = L"label3";
			this->labelXYInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 32);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"P³aszczyzna XY";
			// 
			// checkBoxXYHide
			// 
			this->checkBoxXYHide->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxXYHide->AutoSize = true;
			this->checkBoxXYHide->Location = System::Drawing::Point(361, 31);
			this->checkBoxXYHide->Name = L"checkBoxXYHide";
			this->checkBoxXYHide->Size = System::Drawing::Size(50, 17);
			this->checkBoxXYHide->TabIndex = 13;
			this->checkBoxXYHide->Text = L"Ukryj";
			this->checkBoxXYHide->UseVisualStyleBackColor = true;
			this->checkBoxXYHide->CheckedChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// trackBarYZPlane
			// 
			this->trackBarYZPlane->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->trackBarYZPlane->Location = System::Drawing::Point(24, 308);
			this->trackBarYZPlane->Name = L"trackBarYZPlane";
			this->trackBarYZPlane->Size = System::Drawing::Size(374, 45);
			this->trackBarYZPlane->TabIndex = 7;
			this->trackBarYZPlane->ValueChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// trackBarXZPlane
			// 
			this->trackBarXZPlane->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->trackBarXZPlane->Location = System::Drawing::Point(24, 163);
			this->trackBarXZPlane->Name = L"trackBarXZPlane";
			this->trackBarXZPlane->Size = System::Drawing::Size(374, 45);
			this->trackBarXZPlane->TabIndex = 6;
			this->trackBarXZPlane->ValueChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// trackBarXYPlane
			// 
			this->trackBarXYPlane->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->trackBarXYPlane->Location = System::Drawing::Point(24, 48);
			this->trackBarXYPlane->Name = L"trackBarXYPlane";
			this->trackBarXYPlane->Size = System::Drawing::Size(374, 45);
			this->trackBarXYPlane->TabIndex = 5;
			this->trackBarXYPlane->ValueChanged += gcnew System::EventHandler(this, &ConfigForm::TrackBarDispatcher);
			// 
			// ConfigForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(438, 496);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"ConfigForm";
			this->Text = L"Konfiguracja warstwy";
			this->Shown += gcnew System::EventHandler(this, &ConfigForm::ConfigForm_Shown);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tabPage3Planes->ResumeLayout(false);
			this->tabPage3Planes->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarYZPlane))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarXZPlane))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarXYPlane))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
		bool m_Disable;

		delegate void ActionHandler();

	private:void ActionDispatcher(System::Object^  sender) {
				Object^ tag = ((Control^)sender)->Tag;
				if(tag == nullptr){
					((Control^)sender)->Enabled = false;
					return;
				}
				((ActionHandler^)tag)();
			}
	private: System::Void TrackBarDispatcher(System::Object^  sender, System::EventArgs^  e) {
				 ActionDispatcher(sender);
			 }

	private: System::Void ModeChange(System::Object^  sender, System::EventArgs^  e) {
				 tabPage3Planes->Enabled = radioButton3Planes->Checked;

				 if(radioButton3Planes->Checked) {
					 m_Layer->SetMode(CubeLayerMode::Planes3);
					 Read3PlanesConfig();
					 Update3PlanesConfig();
					 return;
				 }
				 if(radioButtonOuterView->Checked) {
					 m_Layer->SetMode(CubeLayerMode::OuterCube);
					 return;
				 }
			 }

	private: void Read3PlanesConfig() {
				 m_Disable = true;
				 auto &s = m_Layer->CubeSize();
				 trackBarXYPlane->Maximum = s[0];
				 trackBarXZPlane->Maximum = s[1];
				 trackBarYZPlane->Maximum = s[2];
				 auto &v = m_Layer->Slices();
				 trackBarXYPlane->Value = v[0].CenterPoint[2];
				 trackBarXZPlane->Value = v[1].CenterPoint[0];
				 trackBarYZPlane->Value = v[2].CenterPoint[1];
				 checkBoxXYHide->Checked = v[0].Hide;
				 checkBoxXZHide->Checked = v[1].Hide;
				 checkBoxZYHide->Checked = v[2].Hide;
				 checkBoxShowInternalEdges->Checked = m_Layer->IsInnerEdgesVisible();
				 m_Disable = false;
			 }
	private: void Update3PlanesConfig() {
				 if(m_Disable) return;
				 auto &v = m_Layer->Slices();
				 auto &s = m_Layer->CubeSize();
				 labelXYInfo->Text = String::Format("{0}/{1}", v[0].CenterPoint[2], s[0]);
				 labelXZInfo->Text = String::Format("{0}/{1}", v[1].CenterPoint[0], s[1]);
				 labelYZInfo->Text = String::Format("{0}/{1}", v[2].CenterPoint[1], s[2]);
				 v[0].Hide = checkBoxXYHide->Checked;
				 v[1].Hide = checkBoxXZHide->Checked;
				 v[2].Hide = checkBoxZYHide->Checked;
				 v[0].CenterPoint[2] = trackBarXYPlane->Value;
				 v[1].CenterPoint[0] = trackBarXZPlane->Value;
				 v[2].CenterPoint[1] = trackBarYZPlane->Value;
				 m_Layer->ShowInnerEdges(checkBoxShowInternalEdges->Checked);
				 m_Layer->InvalidateSlicesVAO();
			 }

	private: System::Void ConfigForm_Shown(System::Object^  sender, System::EventArgs^  e) {
				 ActionHandler 
					 ^p3_update = gcnew ActionHandler(this, &ConfigForm::Update3PlanesConfig),
					 ^edges_update = gcnew ActionHandler(this, &ConfigForm::UpdateOuterEdgesSetting)
					 ;

				 checkBoxOuterEdges->Checked = m_Layer->IsOuterEdgesVisible();

				 trackBarXYPlane->Tag = p3_update;
				 trackBarXZPlane->Tag = p3_update;
				 trackBarYZPlane->Tag = p3_update;
				 checkBoxXYHide->Tag = p3_update;
				 checkBoxXZHide->Tag = p3_update;
				 checkBoxZYHide->Tag = p3_update;
				 checkBoxShowInternalEdges->Tag = p3_update;

				 checkBoxOuterEdges->Tag = edges_update;

				 switch (m_Layer->GetMode()) {
				 case CubeLayerMode::Planes3: 
					 radioButton3Planes->Checked = true;
					 break;
				 case CubeLayerMode::OuterCube: 
					 radioButtonOuterView->Checked = true;
					 break;
				 case CubeLayerMode::User:
					 break;
				 default:
					 break;
				 }
				 ModeChange(nullptr, nullptr);
				 checkBoxOuterEdges->Enabled = true;
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 Hide();
			 }

	private: void UpdateOuterEdgesSetting() {
				 m_Layer->ShowOuterEdges(checkBoxOuterEdges->Checked);
			 }
};

	//----------------------------------------------------------------------------------------

	class CubeLayerGuiHandler : public VisApp::Renderer::LayerCLIGUIHandler {
	public:
		CubeLayerGuiHandler(CubeLayer *Owner): VisApp::Renderer::LayerCLIGUIHandler(), m_Owner(Owner) {
		}

		virtual void OpenConfiguration(System::Windows::Forms::Form^ Owner) {
			auto form = gcnew ConfigForm(Owner, m_Owner, Operations());
			form->Show();
		}
	private:
		CubeLayer *m_Owner;
	};
}
