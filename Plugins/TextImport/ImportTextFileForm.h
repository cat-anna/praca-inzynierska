/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/ImportTextFileForm.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "TextImport.h"

#pragma managed

#include <msclr\marshal_cppstd.h>

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Windows;
	using namespace System::Xml;

	using System::Windows::Forms::DialogResult;

	using msclr::interop::marshal_as;

	enum class TypeSelectionMode {
		NewCollumn, Coords,
	};

	/// <summary>
	/// Summary for ImportTextFileForm
	/// </summary>
	public ref class ImportTextFileForm : public System::Windows::Forms::Form
	{
	private:
		int m_CurrentPage;
		TextImportPlugin *m_instance;
		unsigned m_CollumnCount;
		TypeSelectionMode m_TypeSelectionMode;
		Generic::List<String^> ^PatternNames;
	private: System::Windows::Forms::CheckBox^  checkBoxFirstLineHasData;
	private: System::Windows::Forms::GroupBox^  groupBoxDataSize;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownSizeZ;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownSizeY;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownSizeX;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemFloatVariables;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItemIntegerVariables;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zmieñTypToolStripMenuItem;
	private: System::Windows::Forms::Button^  SavePatternButton;

	private: System::Windows::Forms::Button^  LoadPatternButton;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;

	private: System::Windows::Forms::ToolStripMenuItem^  zmieñNazwêToolStripMenuItem;

	public:
		ImportTextFileForm(System::Windows::Forms::Form^ OwnerForm, TextImportPlugin *instance) {
			InitializeComponent();
			m_CurrentPage = 0;
			Owner = OwnerForm;
			m_instance = instance;
			m_CollumnCount = 0;
			PatternNames = gcnew Generic::List<String^>();
			LoadCollumnPatterns();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImportTextFileForm() {
			if (components) {
				delete components;
			}
		}

		//---------------------------- DYNAMIC STUFF --------------------------------

	private: System::Windows::Forms::Panel^  panel2;

	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuFieldList;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::TextBox^  textBoxOtherSerparator;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorOther;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorSemicolon;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorTab;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorSpace;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  buttonChangeImportStatus;
	private: System::Windows::Forms::Label^  labelFieldCount;
	private: System::Windows::Forms::Button^  buttonFieldDown;
	private: System::Windows::Forms::Button^  buttonFieldUp;
	private: System::Windows::Forms::Button^  buttonRemoveField;
	private: System::Windows::Forms::Button^  buttonAddField;
	private: System::Windows::Forms::ListView^  listViewFields;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::CheckBox^  checkBoxIgnoreFollowingSeparators;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  ButtonAnalysis;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->contextMenuFieldList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->MenuItemFloatVariables = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItemIntegerVariables = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zmieñTypToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxIgnoreFollowingSeparators = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxOtherSerparator = (gcnew System::Windows::Forms::TextBox());
			this->radioButtonSeparatorOther = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorSemicolon = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorTab = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorSpace = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->SavePatternButton = (gcnew System::Windows::Forms::Button());
			this->LoadPatternButton = (gcnew System::Windows::Forms::Button());
			this->ButtonAnalysis = (gcnew System::Windows::Forms::Button());
			this->buttonChangeImportStatus = (gcnew System::Windows::Forms::Button());
			this->labelFieldCount = (gcnew System::Windows::Forms::Label());
			this->buttonFieldDown = (gcnew System::Windows::Forms::Button());
			this->buttonFieldUp = (gcnew System::Windows::Forms::Button());
			this->buttonRemoveField = (gcnew System::Windows::Forms::Button());
			this->buttonAddField = (gcnew System::Windows::Forms::Button());
			this->listViewFields = (gcnew System::Windows::Forms::ListView());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxFirstLineHasData = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxDataSize = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownSizeZ = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownSizeY = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownSizeX = (gcnew System::Windows::Forms::NumericUpDown());
			this->contextMenuStripItem = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->zmieñNazwêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->panel2->SuspendLayout();
			this->contextMenuFieldList->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBoxDataSize->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeZ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeX))->BeginInit();
			this->contextMenuStripItem->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->buttonOk);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 572);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(481, 46);
			this->panel2->TabIndex = 1;
			// 
			// buttonOk
			// 
			this->buttonOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonOk->Location = System::Drawing::Point(352, 11);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(111, 23);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"Ok";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonOk_Click);
			// 
			// contextMenuFieldList
			// 
			this->contextMenuFieldList->AllowMerge = false;
			this->contextMenuFieldList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->MenuItemFloatVariables, 
				this->MenuItemIntegerVariables});
			this->contextMenuFieldList->Name = L"contextMenuStrip1";
			this->contextMenuFieldList->OwnerItem = this->zmieñTypToolStripMenuItem;
			this->contextMenuFieldList->Size = System::Drawing::Size(189, 48);
			// 
			// MenuItemFloatVariables
			// 
			this->MenuItemFloatVariables->Name = L"MenuItemFloatVariables";
			this->MenuItemFloatVariables->Size = System::Drawing::Size(188, 22);
			this->MenuItemFloatVariables->Text = L"Zmiennoprzecinkowe";
			// 
			// MenuItemIntegerVariables
			// 
			this->MenuItemIntegerVariables->Name = L"MenuItemIntegerVariables";
			this->MenuItemIntegerVariables->Size = System::Drawing::Size(188, 22);
			this->MenuItemIntegerVariables->Text = L"Ca³kowite";
			// 
			// zmieñTypToolStripMenuItem
			// 
			this->zmieñTypToolStripMenuItem->DropDown = this->contextMenuFieldList;
			this->zmieñTypToolStripMenuItem->Name = L"zmieñTypToolStripMenuItem";
			this->zmieñTypToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->zmieñTypToolStripMenuItem->Text = L"Zmieñ typ";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->checkBoxIgnoreFollowingSeparators);
			this->groupBox4->Controls->Add(this->textBoxOtherSerparator);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorOther);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorSemicolon);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorTab);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorSpace);
			this->groupBox4->Location = System::Drawing::Point(18, 392);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(186, 174);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Separator kolumn";
			// 
			// checkBoxIgnoreFollowingSeparators
			// 
			this->checkBoxIgnoreFollowingSeparators->Location = System::Drawing::Point(6, 131);
			this->checkBoxIgnoreFollowingSeparators->Name = L"checkBoxIgnoreFollowingSeparators";
			this->checkBoxIgnoreFollowingSeparators->Size = System::Drawing::Size(152, 37);
			this->checkBoxIgnoreFollowingSeparators->TabIndex = 6;
			this->checkBoxIgnoreFollowingSeparators->Text = L"Traktuj kolejne ograniczniki jako jeden";
			this->checkBoxIgnoreFollowingSeparators->UseVisualStyleBackColor = true;
			// 
			// textBoxOtherSerparator
			// 
			this->textBoxOtherSerparator->Enabled = false;
			this->textBoxOtherSerparator->Location = System::Drawing::Point(53, 105);
			this->textBoxOtherSerparator->MaxLength = 1;
			this->textBoxOtherSerparator->Name = L"textBoxOtherSerparator";
			this->textBoxOtherSerparator->Size = System::Drawing::Size(50, 20);
			this->textBoxOtherSerparator->TabIndex = 5;
			// 
			// radioButtonSeparatorOther
			// 
			this->radioButtonSeparatorOther->AutoSize = true;
			this->radioButtonSeparatorOther->Location = System::Drawing::Point(6, 104);
			this->radioButtonSeparatorOther->Name = L"radioButtonSeparatorOther";
			this->radioButtonSeparatorOther->Size = System::Drawing::Size(48, 17);
			this->radioButtonSeparatorOther->TabIndex = 3;
			this->radioButtonSeparatorOther->Text = L"Inny:";
			this->radioButtonSeparatorOther->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorOther->CheckedChanged += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorSemicolon
			// 
			this->radioButtonSeparatorSemicolon->AutoSize = true;
			this->radioButtonSeparatorSemicolon->Location = System::Drawing::Point(6, 76);
			this->radioButtonSeparatorSemicolon->Name = L"radioButtonSeparatorSemicolon";
			this->radioButtonSeparatorSemicolon->Size = System::Drawing::Size(61, 17);
			this->radioButtonSeparatorSemicolon->TabIndex = 2;
			this->radioButtonSeparatorSemicolon->Text = L"Œrednik";
			this->radioButtonSeparatorSemicolon->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorSemicolon->CheckedChanged += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorTab
			// 
			this->radioButtonSeparatorTab->AutoSize = true;
			this->radioButtonSeparatorTab->Location = System::Drawing::Point(6, 48);
			this->radioButtonSeparatorTab->Name = L"radioButtonSeparatorTab";
			this->radioButtonSeparatorTab->Size = System::Drawing::Size(70, 17);
			this->radioButtonSeparatorTab->TabIndex = 1;
			this->radioButtonSeparatorTab->Text = L"Tabulator";
			this->radioButtonSeparatorTab->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorTab->CheckedChanged += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorSpace
			// 
			this->radioButtonSeparatorSpace->AutoSize = true;
			this->radioButtonSeparatorSpace->Checked = true;
			this->radioButtonSeparatorSpace->Location = System::Drawing::Point(6, 20);
			this->radioButtonSeparatorSpace->Name = L"radioButtonSeparatorSpace";
			this->radioButtonSeparatorSpace->Size = System::Drawing::Size(58, 17);
			this->radioButtonSeparatorSpace->TabIndex = 0;
			this->radioButtonSeparatorSpace->TabStop = true;
			this->radioButtonSeparatorSpace->Text = L"Spacja";
			this->radioButtonSeparatorSpace->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorSpace->CheckedChanged += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->SavePatternButton);
			this->groupBox1->Controls->Add(this->LoadPatternButton);
			this->groupBox1->Controls->Add(this->ButtonAnalysis);
			this->groupBox1->Controls->Add(this->buttonChangeImportStatus);
			this->groupBox1->Controls->Add(this->labelFieldCount);
			this->groupBox1->Controls->Add(this->buttonFieldDown);
			this->groupBox1->Controls->Add(this->buttonFieldUp);
			this->groupBox1->Controls->Add(this->buttonRemoveField);
			this->groupBox1->Controls->Add(this->buttonAddField);
			this->groupBox1->Controls->Add(this->listViewFields);
			this->groupBox1->Location = System::Drawing::Point(18, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(445, 374);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			// 
			// SavePatternButton
			// 
			this->SavePatternButton->Location = System::Drawing::Point(301, 283);
			this->SavePatternButton->Name = L"SavePatternButton";
			this->SavePatternButton->Size = System::Drawing::Size(100, 23);
			this->SavePatternButton->TabIndex = 32;
			this->SavePatternButton->Text = L"Zapisz wzorzec";
			this->SavePatternButton->UseVisualStyleBackColor = true;
			this->SavePatternButton->Click += gcnew System::EventHandler(this, &ImportTextFileForm::SavePatternButton_Click);
			// 
			// LoadPatternButton
			// 
			this->LoadPatternButton->Location = System::Drawing::Point(301, 256);
			this->LoadPatternButton->Name = L"LoadPatternButton";
			this->LoadPatternButton->Size = System::Drawing::Size(100, 23);
			this->LoadPatternButton->TabIndex = 31;
			this->LoadPatternButton->Text = L"Wczytaj wzorzec";
			this->LoadPatternButton->UseVisualStyleBackColor = true;
			this->LoadPatternButton->Click += gcnew System::EventHandler(this, &ImportTextFileForm::LoadPatternButton_Click);
			// 
			// ButtonAnalysis
			// 
			this->ButtonAnalysis->Location = System::Drawing::Point(26, 333);
			this->ButtonAnalysis->Name = L"ButtonAnalysis";
			this->ButtonAnalysis->Size = System::Drawing::Size(100, 23);
			this->ButtonAnalysis->TabIndex = 30;
			this->ButtonAnalysis->Text = L"Przeanalizuj plik";
			this->ButtonAnalysis->UseVisualStyleBackColor = true;
			this->ButtonAnalysis->Click += gcnew System::EventHandler(this, &ImportTextFileForm::ButtonAnalysis_Click);
			// 
			// buttonChangeImportStatus
			// 
			this->buttonChangeImportStatus->Enabled = false;
			this->buttonChangeImportStatus->Location = System::Drawing::Point(301, 123);
			this->buttonChangeImportStatus->Name = L"buttonChangeImportStatus";
			this->buttonChangeImportStatus->Size = System::Drawing::Size(75, 23);
			this->buttonChangeImportStatus->TabIndex = 29;
			this->buttonChangeImportStatus->Text = L"Nie importuj";
			this->buttonChangeImportStatus->UseVisualStyleBackColor = true;
			this->buttonChangeImportStatus->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonChangeImportStatus_Click);
			// 
			// labelFieldCount
			// 
			this->labelFieldCount->Location = System::Drawing::Point(26, 309);
			this->labelFieldCount->Name = L"labelFieldCount";
			this->labelFieldCount->Size = System::Drawing::Size(269, 13);
			this->labelFieldCount->TabIndex = 28;
			this->labelFieldCount->Text = L"Iloœæ pól: 5";
			// 
			// buttonFieldDown
			// 
			this->buttonFieldDown->Location = System::Drawing::Point(301, 213);
			this->buttonFieldDown->Name = L"buttonFieldDown";
			this->buttonFieldDown->Size = System::Drawing::Size(100, 23);
			this->buttonFieldDown->TabIndex = 25;
			this->buttonFieldDown->Text = L"Przesuñ w dó³";
			this->buttonFieldDown->UseVisualStyleBackColor = true;
			this->buttonFieldDown->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonFieldDown_Click);
			// 
			// buttonFieldUp
			// 
			this->buttonFieldUp->Location = System::Drawing::Point(301, 184);
			this->buttonFieldUp->Name = L"buttonFieldUp";
			this->buttonFieldUp->Size = System::Drawing::Size(100, 23);
			this->buttonFieldUp->TabIndex = 24;
			this->buttonFieldUp->Text = L"Przesuñ w górê";
			this->buttonFieldUp->UseVisualStyleBackColor = true;
			this->buttonFieldUp->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonFieldUp_Click);
			// 
			// buttonRemoveField
			// 
			this->buttonRemoveField->Enabled = false;
			this->buttonRemoveField->Location = System::Drawing::Point(301, 73);
			this->buttonRemoveField->Name = L"buttonRemoveField";
			this->buttonRemoveField->Size = System::Drawing::Size(75, 23);
			this->buttonRemoveField->TabIndex = 23;
			this->buttonRemoveField->Text = L"Usuñ";
			this->buttonRemoveField->UseVisualStyleBackColor = true;
			this->buttonRemoveField->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonRemoveField_Click_1);
			// 
			// buttonAddField
			// 
			this->buttonAddField->Location = System::Drawing::Point(301, 44);
			this->buttonAddField->Name = L"buttonAddField";
			this->buttonAddField->Size = System::Drawing::Size(75, 23);
			this->buttonAddField->TabIndex = 22;
			this->buttonAddField->Text = L"Dodaj";
			this->buttonAddField->UseVisualStyleBackColor = true;
			this->buttonAddField->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonAddField_Click);
			// 
			// listViewFields
			// 
			this->listViewFields->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader4, 
				this->columnHeader5, this->columnHeader7});
			this->listViewFields->FullRowSelect = true;
			this->listViewFields->GridLines = true;
			this->listViewFields->Location = System::Drawing::Point(26, 41);
			this->listViewFields->Name = L"listViewFields";
			this->listViewFields->Size = System::Drawing::Size(269, 265);
			this->listViewFields->TabIndex = 20;
			this->listViewFields->UseCompatibleStateImageBehavior = false;
			this->listViewFields->View = System::Windows::Forms::View::Details;
			this->listViewFields->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ImportTextFileForm::listViewFields_ItemSelectionChanged);
			this->listViewFields->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ImportTextFileForm::listViewFields_MouseUp);
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Nazwa";
			this->columnHeader4->Width = 100;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Text = L"Typ";
			// 
			// columnHeader7
			// 
			this->columnHeader7->Text = L"Importuj";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBoxFirstLineHasData);
			this->groupBox2->Location = System::Drawing::Point(210, 487);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(253, 79);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Opcje";
			// 
			// checkBoxFirstLineHasData
			// 
			this->checkBoxFirstLineHasData->AutoSize = true;
			this->checkBoxFirstLineHasData->Location = System::Drawing::Point(16, 21);
			this->checkBoxFirstLineHasData->Name = L"checkBoxFirstLineHasData";
			this->checkBoxFirstLineHasData->Size = System::Drawing::Size(202, 17);
			this->checkBoxFirstLineHasData->TabIndex = 0;
			this->checkBoxFirstLineHasData->Text = L"Pierwsza linia zawiara rozmiar danych";
			this->checkBoxFirstLineHasData->UseVisualStyleBackColor = true;
			this->checkBoxFirstLineHasData->CheckedChanged += gcnew System::EventHandler(this, &ImportTextFileForm::checkBoxFirstLineHasData_CheckedChanged);
			// 
			// groupBoxDataSize
			// 
			this->groupBoxDataSize->Controls->Add(this->label5);
			this->groupBoxDataSize->Controls->Add(this->label4);
			this->groupBoxDataSize->Controls->Add(this->label1);
			this->groupBoxDataSize->Controls->Add(this->numericUpDownSizeZ);
			this->groupBoxDataSize->Controls->Add(this->numericUpDownSizeY);
			this->groupBoxDataSize->Controls->Add(this->numericUpDownSizeX);
			this->groupBoxDataSize->Location = System::Drawing::Point(210, 392);
			this->groupBoxDataSize->Name = L"groupBoxDataSize";
			this->groupBoxDataSize->Size = System::Drawing::Size(253, 89);
			this->groupBoxDataSize->TabIndex = 11;
			this->groupBoxDataSize->TabStop = false;
			this->groupBoxDataSize->Text = L"Rozmiar danych";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(46, 63);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(12, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"z";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(46, 42);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(12, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"y";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(46, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(12, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"x";
			// 
			// numericUpDownSizeZ
			// 
			this->numericUpDownSizeZ->Location = System::Drawing::Point(64, 61);
			this->numericUpDownSizeZ->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->numericUpDownSizeZ->Name = L"numericUpDownSizeZ";
			this->numericUpDownSizeZ->Size = System::Drawing::Size(81, 20);
			this->numericUpDownSizeZ->TabIndex = 2;
			// 
			// numericUpDownSizeY
			// 
			this->numericUpDownSizeY->Location = System::Drawing::Point(64, 40);
			this->numericUpDownSizeY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->numericUpDownSizeY->Name = L"numericUpDownSizeY";
			this->numericUpDownSizeY->Size = System::Drawing::Size(81, 20);
			this->numericUpDownSizeY->TabIndex = 1;
			// 
			// numericUpDownSizeX
			// 
			this->numericUpDownSizeX->Location = System::Drawing::Point(64, 19);
			this->numericUpDownSizeX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->numericUpDownSizeX->Name = L"numericUpDownSizeX";
			this->numericUpDownSizeX->Size = System::Drawing::Size(81, 20);
			this->numericUpDownSizeX->TabIndex = 0;
			// 
			// contextMenuStripItem
			// 
			this->contextMenuStripItem->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->zmieñTypToolStripMenuItem, 
				this->zmieñNazwêToolStripMenuItem, this->toolStripMenuItem1});
			this->contextMenuStripItem->Name = L"contextMenuStripItem";
			this->contextMenuStripItem->Size = System::Drawing::Size(147, 54);
			this->contextMenuStripItem->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ImportTextFileForm::contextMenuStripItem_Opening);
			// 
			// zmieñNazwêToolStripMenuItem
			// 
			this->zmieñNazwêToolStripMenuItem->Name = L"zmieñNazwêToolStripMenuItem";
			this->zmieñNazwêToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->zmieñNazwêToolStripMenuItem->Text = L"Zmieñ Nazwê";
			this->zmieñNazwêToolStripMenuItem->Click += gcnew System::EventHandler(this, &ImportTextFileForm::zmieñNazwêToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(143, 6);
			// 
			// ImportTextFileForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(481, 618);
			this->Controls->Add(this->groupBoxDataSize);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->panel2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ImportTextFileForm";
			this->Text = L"Opcje importu";
			this->Load += gcnew System::EventHandler(this, &ImportTextFileForm::ImportTextFileForm_Load);
			this->panel2->ResumeLayout(false);
			this->contextMenuFieldList->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBoxDataSize->ResumeLayout(false);
			this->groupBoxDataSize->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeZ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSizeX))->EndInit();
			this->contextMenuStripItem->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: Forms::DialogResult InputBox(String ^title, String ^promptText, String^ %value)
			{
				Form ^form = gcnew Form();
				Label ^label = gcnew Label();
				TextBox ^textBox = gcnew TextBox();
				Button ^buttonOk = gcnew Button();
				Button ^buttonCancel = gcnew Button();

				form->Text = title;
				label->Text = promptText;
				textBox->Text = value;
				form->Owner = this;
				buttonOk->Text = "OK";
				buttonCancel->Text = "Cancel";
				buttonOk->DialogResult = Forms::DialogResult::OK;
				buttonCancel->DialogResult = Forms::DialogResult::Cancel;

				label->SetBounds(9, 20, 372, 13);
				textBox->SetBounds(12, 36, 372, 20);
				buttonOk->SetBounds(228, 72, 75, 23);
				buttonCancel->SetBounds(309, 72, 75, 23);

				label->AutoSize = true;
				textBox->Anchor = textBox->Anchor | AnchorStyles::Right;
				buttonOk->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;
				buttonCancel->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;

				form->ClientSize = Drawing::Size(396, 107);
				form->Controls->AddRange(gcnew cli::array< Control^ >(4) { label, textBox, buttonOk, buttonCancel });
				form->ClientSize = Drawing::Size(VisApp::Math::Max(300, label->Right + 10), form->ClientSize.Height);
				form->FormBorderStyle = Forms::FormBorderStyle::FixedDialog;
				form->StartPosition = FormStartPosition::CenterParent;
				form->MinimizeBox = false;
				form->MaximizeBox = false;
				form->AcceptButton = buttonOk;
				form->CancelButton = buttonCancel;

				Forms::DialogResult dialogResult = form->ShowDialog();
				value = textBox->Text;
				return dialogResult;
			}
	public: static String^ ToString(const std::wstring& str) {
				return gcnew String(str.c_str());
			}
	public: static std::wstring ToStdWStr(String^ str) {
				return msclr::interop::marshal_as<std::wstring>(str);
			}
	public: String^ ToString(const VisApp::Types::DataType &dt) {
				String ^r = "";
				using VisApp::Types::DataDimiension;
				using VisApp::Types::VariableType;
				switch (dt.Dimiension) {
				case DataDimiension::d1: r = "d1"; break;
				case DataDimiension::d2: r = "d2"; break;
				case DataDimiension::d3: r = "d3"; break;
				};
				r += " ";
				switch (dt.Type) {
				case VariableType::Integer: r += "integer"; break;
				case VariableType::Float: r += "float"; break;
				}
				return r;
			}

			//----------------------------------TextImport rw --------------------------------

	private: System::Void WriteSettings() {
				 m_instance->SetCollumnSeparator(GetCollumnSeparator());
				 m_instance->SetFlag(ImportFlags::IgonoreFollowingSeparator, checkBoxIgnoreFollowingSeparators->Checked);
				 m_instance->SetFlag(ImportFlags::FirstLineHaveSize, checkBoxFirstLineHasData->Checked);

				 uvec3 datasize;
				 datasize[0] = System::Decimal::ToUInt32(numericUpDownSizeX->Value);
				 datasize[1] = System::Decimal::ToUInt32(numericUpDownSizeY->Value);
				 datasize[2] = System::Decimal::ToUInt32(numericUpDownSizeZ->Value);
				 m_instance->SetDataSize(datasize);
			 }
	private: System::Void ReadSettings() {
				 SetCollumnSeparator(m_instance->GetCollumnSeparator());
				 checkBoxIgnoreFollowingSeparators->Checked = m_instance->CheckFlag(ImportFlags::IgonoreFollowingSeparator);
				 checkBoxFirstLineHasData->Checked = m_instance->CheckFlag(ImportFlags::FirstLineHaveSize);
				 auto datasize = m_instance->GetDataSize3();
				 numericUpDownSizeX->Value = datasize[0];
				 numericUpDownSizeY->Value = datasize[1];
				 numericUpDownSizeZ->Value = datasize[2];
				 LoadCollumns();
			 }
	private: System::Void DetectSettings() {
				 //TODO:!!!
				 WriteSettings();
				 m_instance->PreprocessFile();
				 ReadSettings();
			 }
	private: char GetCollumnSeparator() {
				 if(radioButtonSeparatorSpace->Checked) return ' ';
				 if(radioButtonSeparatorTab->Checked) return '\t';
				 if(radioButtonSeparatorSemicolon->Checked) return ';';
				 if(radioButtonSeparatorOther->Checked) 
					 return static_cast<char>(textBoxOtherSerparator->Text[0]);
				 return ';';
			 }
	private: System::Void SetCollumnSeparator(char value) {
				 textBoxOtherSerparator->Text = "";
				 switch(value) {
				 case ' ':
					 radioButtonSeparatorSpace->Checked = true;
					 break;
				 case '\t':
					 radioButtonSeparatorTab->Checked = true;
					 break;				
				 case ';':
					 radioButtonSeparatorSemicolon->Checked = true;
					 break;				 
				 default:
					 radioButtonSeparatorOther->Checked = true;
					 textBoxOtherSerparator->Text = "" + value;
					 break;
				 }
			 }
	private: System::Void RecalculateVariablesId() {
				 auto &vars = m_instance->GetVariables();
				 vars.clear();
				 unsigned index = 0;
				 for(int i = 0, j = listViewFields->Items->Count; i < j; ++i) {
					 ListViewItem ^itm = listViewFields->Items[i];
					 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
					 vars.push_back(*cd->item);
					 (*cd->item)->FirstValueID = index;
					 index += (*cd->item)->Type.ValuesCount();
				 }
				 m_CollumnCount = index;
				 labelFieldCount->Text = "Iloœæ pól: " + index;
			 }
	private: System::Void LoadCollumns() {
				 auto vars = m_instance->GetVariables();
				 listViewFields->Items->Clear();
				 for(auto &it: vars) {
					 ListViewItem ^Item = listViewFields->Items->Add("?", -1);
					 CollumnDescriptor ^cd = gcnew CollumnDescriptor();
					 Item->Tag = cd;
					 *cd->item = it;

					 if(*cd->item == m_instance->GetCoordDescriptor()) {
						 cd->AllowDeletion = false;
					 }
					 ResetCollumn(Item);
				 }

				 if(vars.empty()) {
					 CollumnDescriptor ^cd = AddCollumn(VisApp::Types::DataType::D3Integer());
					 (*cd->item)->DoImport = false;
					 cd->AllowDeletion = false;
					 cd->lvItem->SubItems[0]->Text = "Wspó³rzêdne";
					 (*cd->item)->Name = L"Wspó³rzêdne";
					 m_instance->SetCoordDescriptor(*cd->item);
					 ResetCollumn(cd->lvItem);
				 }

				 RecalculateVariablesId();
			 }

			 //-------------------------------------Private types -----------------------------------

	private: 
		ref class TypeDescriptor {
		public:
			VisApp::Types::DataType *Type;
			TypeDescriptor() {
				Type = new VisApp::Types::DataType();
			}
			~TypeDescriptor() {
				delete Type;
			}
		};

	private: 
		ref class CollumnDescriptor {
		public:
			SharedVariableDesciptor *item;
			ListViewItem ^lvItem;
			bool AllowDeletion;
			CollumnDescriptor() {
				item = new SharedVariableDesciptor();
				AllowDeletion = true;
			}
			~CollumnDescriptor() {
				delete item;
			}
		};


		//----------------------------------EVENTS --------------------------------

	private: System::Void ImportTextFileForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 using VisApp::Types::DataType;
				 AddVariableType(DataType::D1Float(), "d1");
				 AddVariableType(DataType::D2Float(), "d2");
				 AddVariableType(DataType::D3Float(), "d3");
				 AddVariableType(DataType::D1Integer(), "d1");
				 AddVariableType(DataType::D2Integer(), "d2");
				 AddVariableType(DataType::D3Integer(), "d3");
				 ReadSettings();
			 }
	private: System::Void radioButtonSeparatorSpace_Click(System::Object^  sender, System::EventArgs^  e) {
				 textBoxOtherSerparator->Enabled = radioButtonSeparatorOther->Checked;
			 }
	private: System::Void checkBoxFirstLineHasData_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 groupBoxDataSize->Enabled = !checkBoxFirstLineHasData->Checked;
			 }
	private: System::Void ButtonAnalysis_Click(System::Object^  sender, System::EventArgs^  e) {
				 DetectSettings();
			 }
	private: System::Void buttonAddField_Click(System::Object^  sender, System::EventArgs^  e) {
				 m_TypeSelectionMode = TypeSelectionMode::NewCollumn;
				 auto dummy = System::Windows::Forms::Control::MousePosition;
				 contextMenuFieldList->Show(System::Windows::Forms::Control::MousePosition);
			 }
	private: System::Void DynamicMenuItemAddField_Click(System::Object^ sender, System::EventArgs^  e) {
				 TypeDescriptor ^type = (TypeDescriptor^)((ToolStripMenuItem^)sender)->Tag;
				 switch (m_TypeSelectionMode) {
				 case gui::TypeSelectionMode::NewCollumn:
					 AddCollumn(*type->Type);
					 break;
				 case gui::TypeSelectionMode::Coords: {
					 ListViewItem^ itm = listViewFields->SelectedItems[0];
					 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
					 
					 if(!cd->AllowDeletion && type->Type->Type != VariableType::Integer) {
						 MessageBox::Show(this, "Wspó³rzêdne musz¹ byæ typu ca³kowitego!");
					 } else
						cd->item->get()->Type = *type->Type;
					 break;
					}
				 }
				 LoadCollumns();
			 }
	private: System::Void buttonChangeImportStatus_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
				 (*cd->item)->DoImport = !(*cd->item)->DoImport;
				 ResetCollumn(itm);
				 if((*cd->item)->DoImport)
					 buttonChangeImportStatus->Text = "Nie importuj";
				 else 
					 buttonChangeImportStatus->Text = "Importuj";
			 }
	private: System::Void listViewFields_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
				 CollumnDescriptor ^cd = (CollumnDescriptor^)e->Item->Tag;
				 SharedVariableDesciptor &vd = *cd->item;

				 buttonChangeImportStatus->Enabled = e->IsSelected && cd->AllowDeletion;
				 buttonRemoveField->Enabled = e->IsSelected && cd->AllowDeletion;
				 buttonFieldDown->Enabled = e->ItemIndex + 1 < listViewFields->Items->Count;
				 buttonFieldUp->Enabled = e->ItemIndex > 0;

				 if(e->Item->Tag != nullptr) {
					 if(vd->DoImport)
						 buttonChangeImportStatus->Text = "Nie importuj";
					 else 
						 buttonChangeImportStatus->Text = "Importuj";
				 }
			 }		
	private: System::Void buttonRemoveField_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ lvi = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)lvi->Tag;
				 if(!cd->AllowDeletion) return;
				 lvi->Remove();
				 RecalculateVariablesId();
			 }
	private: System::Void buttonFieldDown_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 int idx = listViewFields->SelectedItems[0]->Index;
				 if(idx + 1 >= listViewFields->Items->Count) return;
				 ListViewItem^ lvi = listViewFields->SelectedItems[0];
				 listViewFields->Items->Remove(lvi);
				 listViewFields->Items->Insert(idx + 1, lvi);
				 lvi->Selected = true;
			 }
	private: System::Void buttonFieldUp_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 int idx = listViewFields->SelectedItems[0]->Index;
				 if(idx < 1) return;
				 ListViewItem^ lvi = listViewFields->SelectedItems[0];
				 listViewFields->Items->Remove(lvi);
				 listViewFields->Items->Insert(idx - 1, lvi);
				 lvi->Selected = true;
			 }		
	private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {
				 WriteSettings();
				 DialogResult = Forms::DialogResult::OK;
			 }
	private: System::Void zmieñNazwêToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
				 if(!cd->AllowDeletion) return;

				 String ^value = itm->SubItems[0]->Text;
				 if(InputBox(Application::ProductName, "Zmieñ nazwê", value) != Forms::DialogResult::OK)
					 return;
				 (*cd->item)->Name = ToStdWStr(value);
				 ResetCollumn(itm);
			 }
	private: System::Void listViewFields_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(e->Button != Forms::MouseButtons::Right || listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
				 m_TypeSelectionMode = TypeSelectionMode::Coords;
				 contextMenuStripItem->Show(System::Windows::Forms::Control::MousePosition);
			 }
	private: System::Void contextMenuStripItem_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
				 zmieñNazwêToolStripMenuItem->Enabled = cd->AllowDeletion;
			 }	
	private: System::Void buttonRemoveField_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 CollumnDescriptor ^cd = (CollumnDescriptor^)itm->Tag;
				 if(!cd->AllowDeletion) return;
				
				 auto list = m_instance->GetVariables();
				 for(auto it = list.begin(), jt = list.end(); it != jt; ++it)
					 if(it->get() == cd->item->get()) {
						 list.erase(it);
						 break;
					 }

				 LoadCollumns();
			 }

	private: System::Void SavePatternButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 Forms::ContextMenuStrip ^Menu = gcnew Forms::ContextMenuStrip(this->components);
//				 ToolStripMenuItem ^itm;

				 Menu->Items->Add(gcnew ToolStripMenuItem("Nowy...", nullptr, gcnew EventHandler(this, &ImportTextFileForm::SaveAsNewPattern)));
				 Menu->Items->Add("-");

				 for each(String ^it in PatternNames) 
					 Menu->Items->Add(gcnew ToolStripMenuItem(it, nullptr, gcnew EventHandler(this, &ImportTextFileForm::SaveAsPattern)));

				 Menu->Show(System::Windows::Forms::Control::MousePosition);
			 }
	private: System::Void LoadPatternButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 Forms::ContextMenuStrip ^Menu = gcnew Forms::ContextMenuStrip(this->components);

				 for each(String ^it in PatternNames) 
					 Menu->Items->Add(gcnew ToolStripMenuItem(it, nullptr, gcnew EventHandler(this, &ImportTextFileForm::LoadPattern)));

				 if(PatternNames->Count == 0) {
					 ToolStripMenuItem ^itm;
					 Menu->Items->Add(itm = gcnew ToolStripMenuItem("Brak wzorców", nullptr, gcnew EventHandler(this, &ImportTextFileForm::LoadPattern)));
					 itm->Enabled = false;
				 }


				 Menu->Show(System::Windows::Forms::Control::MousePosition);
			 }			 
			 //----------------------------------------Var types --------------------------------

	private: System::Void AddVariableType(const VisApp::Types::DataType &type, String ^Caption) {
				 using namespace VisApp::Types;

				 ToolStripMenuItem ^parent;
				 switch(type.Type) {
				 case VariableType::Float: 
					 parent = MenuItemFloatVariables;
					 break;
				 case VariableType::Integer:
					 parent = MenuItemIntegerVariables;
					 break;
				 default:
					 return;
				 }
				 ToolStripMenuItem ^item = gcnew System::Windows::Forms::ToolStripMenuItem();
				 TypeDescriptor ^descriptor = gcnew TypeDescriptor();
				 item->Text = Caption;
				 item->Tag = descriptor;
				 (*descriptor->Type) = type;
				 parent->DropDownItems->Add(item);
				 item->Click += gcnew System::EventHandler(this, &ImportTextFileForm::DynamicMenuItemAddField_Click);
			 }
	private: System::Void ResetCollumn(ListViewItem ^Item) {
				 CollumnDescriptor ^cd = (CollumnDescriptor^)Item->Tag;
				 SharedVariableDesciptor &vt = *cd->item;
				 for(int i = Item->SubItems->Count; i < 5; ++i) Item->SubItems->Add("?");

				 Item->SubItems[0]->Text = ToString(vt->Name);
				 Item->SubItems[1]->Text = ToString(vt->Type);
				 Item->SubItems[2]->Text = vt->DoImport ? "Tak" : "Nie";
			 }
	private: CollumnDescriptor^ AddCollumn(const VisApp::Types::DataType &type) {
				 auto vars = m_instance->GetVariables();
				 VariableDescriptor *vt = new VariableDescriptor();
				 vt->Type = type; 
				 vt->FirstValueID = 0;
				 vt->Name = L"Zmienna";
				 vars.push_back(SharedVariableDesciptor(vt));

				 ListViewItem ^Item = listViewFields->Items->Add("?", -1);
				 CollumnDescriptor ^cd = gcnew CollumnDescriptor();
				 Item->Tag = cd;
				 cd->lvItem = Item;
				 *cd->item = vars.back();
				 ResetCollumn(Item);
				 RecalculateVariablesId();
				 return cd;
			 }

	private: void SaveAsNewPattern(System::Object^  sender, System::EventArgs^  e) {
				 String ^value = "Brak nazwy";
				 if(InputBox(Application::ProductName, "Zapisz jako wzorzec", value) != Forms::DialogResult::OK)
					 return;	

				 auto sett = m_instance->GetGlobalSettings();
				 auto patterns = sett.GetNode().child(L"Patterns");
				 if(!patterns) 
					 patterns = sett.GetNode().append_child(L"Patterns");

				 auto patt = patterns.find_child_by_attribute(L"Item", L"Name", ToStdWStr(value).c_str());
				 patterns.remove_child(patt);
				 patt = patterns.append_child(L"Item");
				 patt.append_attribute(L"Name") = ToStdWStr(value).c_str();
				 m_instance->SaveCollumSettings(patt);
				 if(PatternNames->IndexOf(value) < 0) 
					 PatternNames->Add(value);
				 PatternNames->Sort();
			 }	
	private: void SaveAsPattern(System::Object^  sender, System::EventArgs^ e) {
				 std::wstring value = ToStdWStr(((ToolStripMenuItem^)sender)->Text);

				 auto sett = m_instance->GetGlobalSettings();
				 auto patterns = sett.GetNode().child(L"Patterns");
				 if(!patterns) 
					 patterns = sett.GetNode().append_child(L"Patterns");

				 auto patt = patterns.find_child_by_attribute(L"Item", L"Name", value.c_str());
				 patterns.remove_child(patt);
				 patt = patterns.append_child(L"Item");
				 patt.append_attribute(L"Name") = value.c_str();
				 m_instance->SaveCollumSettings(patt);
				 if(PatternNames->IndexOf(ToString(value)) < 0) 
					 PatternNames->Add(ToString(value));
				 PatternNames->Sort();
			 }	
	private: void LoadPattern(System::Object^  sender, System::EventArgs^  e) {
				 std::wstring value = ToStdWStr(((ToolStripMenuItem^)sender)->Text);
				 auto sett = m_instance->GetGlobalSettings();
				 auto patterns = sett.GetNode().child(L"Patterns");
				 if(!patterns) 
					 return;

				 auto patt = patterns.find_child_by_attribute(L"Item", L"Name", value.c_str());
				 if(!patt)
					 return;
				 m_instance->LoadCollumnSettings(patt);
				 ReadSettings();
			 }
	private: void LoadCollumnPatterns() {
				 PatternNames->Clear();

				 auto sett = m_instance->GetGlobalSettings();
				 auto patterns = sett.GetNode().child(L"Patterns");
				 if(!patterns) return;

				 for(auto it = patterns.child(L"Item"); it; it = it.next_sibling(L"Item")) {
					 PatternNames->Add(ToString(it.attribute(L"Name").as_string()));
				 }
				 PatternNames->Sort();
			 }

			 //----------------------------------CONTAINERS --------------------------------
			 //--------------------------------PUBLIC FUN's -------------------------------

	private: void LoadVariableDefs(String^ file) {
#if 0
				 System::Xml::XmlDocument xmlDoc;
				 xmlDoc.Load(file);
				 XmlNode ^node = xmlDoc.SelectSingleNode("//VariableDef");

				 XmlNodeList ^xnl = node->SelectNodes("Variable");
				 for(int i = 0, j = xnl->Count; i < j; ++i) {
					 XmlNode ^vardef = xnl[i];
					 XmlNode ^type = vardef->SelectSingleNode("Type");
					 FieldDescription ^fd = gcnew FieldDescription();
					 fd->Name = vardef->Attributes["Name"]->Value;
					 fd->TypeName = type->InnerText;
					 fd->Type = Helpers::StringToDataDimension(fd->TypeName);
					 m_FieldDescriptions[i] = fd;

					 ToolStripMenuItem ^item = gcnew System::Windows::Forms::ToolStripMenuItem();
					 item->Text = fd->Name;
					 item->Tag = fd;
					 item->Name = fd->Name;

					 item->Click += gcnew System::EventHandler(this, &ImportTextFileForm::DynamicMenuItemAddField_Click);

					 switch (fd->Type)
					 {
					 case Core::iDataChannel::dd_Integer:
					 case Core::iDataChannel::eDataDimension::dd_Scalar:

						 MenuItem1d->DropDownItems->Add(item);
						 break;
					 case Core::iDataChannel::eDataDimension::dd_2dfloat:
						 MenuItem2d->DropDownItems->Add(item);
						 break;
					 case Core::iDataChannel::eDataDimension::dd_3dfloat:
						 MenuItem3d->DropDownItems->Add(item);
						 break;	
					 }
				 }
#endif
			 }


};
}
