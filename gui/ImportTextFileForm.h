/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ImportTextFileForm.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "CoreMgt.h"
#include "Helpers.h"
#include <interface\CoreInterface.h>

#include <msclr\marshal_cppstd.h>

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Xml;

	using msclr::interop::marshal_as;

	/// <summary>
	/// Summary for ImportTextFileForm
	/// </summary>
	public ref class ImportTextFileForm : public System::Windows::Forms::Form
	{
	private:
		int m_CurrentPage;

	public:
		ImportTextFileForm(System::Windows::Forms::Form^ OwnerForm) {
			InitializeComponent();
			m_CurrentPage = 0;
			Owner = OwnerForm;
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
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Button^  buttonPrevious;
	private: System::Windows::Forms::Button^  buttonNext;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxSeriesName;
	private: System::Windows::Forms::Button^  buttonRemoveFile;
	private: System::Windows::Forms::Button^  buttonAddFile;
	private: System::Windows::Forms::ListView^  listViewFiles;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  buttonFieldDown;
	private: System::Windows::Forms::Button^  buttonFieldUp;
	private: System::Windows::Forms::Button^  buttonRemoveField;
	private: System::Windows::Forms::Button^  buttonAddField;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ListView^  listViewFields;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuFieldList;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  checkBoxCreateProject;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::TextBox^  textBoxOtherSerparator;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorOther;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorSemicolon;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorTab;
	private: System::Windows::Forms::RadioButton^  radioButtonSeparatorSpace;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialogSource;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItem1d;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItem2d;
	private: System::Windows::Forms::ToolStripMenuItem^  MenuItem3d;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  nowaDefinicjaZmiennejToolStripMenuItem;
	private: System::Windows::Forms::Button^  buttonChangeImportStatus;
	private: System::Windows::Forms::CheckBox^  checkBoxBeginImporting;
	private: System::Windows::Forms::CheckBox^  checkBoxAddLayers;
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
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {L"plik1.txt", 
				L"Seria1", L"20MB", L"100x100"}, -1));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {L"plik2.txt", 
				L"Seria2", L"22MB", L"100x100"}, -1));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxOtherSerparator = (gcnew System::Windows::Forms::TextBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->radioButtonSeparatorOther = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorSemicolon = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorTab = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSeparatorSpace = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxSeriesName = (gcnew System::Windows::Forms::TextBox());
			this->buttonRemoveFile = (gcnew System::Windows::Forms::Button());
			this->buttonAddFile = (gcnew System::Windows::Forms::Button());
			this->listViewFiles = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->buttonChangeImportStatus = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->buttonFieldDown = (gcnew System::Windows::Forms::Button());
			this->buttonFieldUp = (gcnew System::Windows::Forms::Button());
			this->buttonRemoveField = (gcnew System::Windows::Forms::Button());
			this->buttonAddField = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listViewFields = (gcnew System::Windows::Forms::ListView());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxBeginImporting = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxAddLayers = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCreateProject = (gcnew System::Windows::Forms::CheckBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonPrevious = (gcnew System::Windows::Forms::Button());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->contextMenuFieldList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->MenuItem1d = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem2d = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem3d = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->nowaDefinicjaZmiennejToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialogSource = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->panel2->SuspendLayout();
			this->contextMenuFieldList->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->tabControl1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(532, 479);
			this->panel1->TabIndex = 0;
			// 
			// tabControl1
			// 
			this->tabControl1->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(532, 479);
			this->tabControl1->TabIndex = 0;
			this->tabControl1->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &ImportTextFileForm::tabControl1_Selected);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox4);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->textBoxSeriesName);
			this->tabPage1->Controls->Add(this->buttonRemoveFile);
			this->tabPage1->Controls->Add(this->buttonAddFile);
			this->tabPage1->Controls->Add(this->listViewFiles);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(524, 450);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Krok 1: Wybierz pliki";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBoxOtherSerparator);
			this->groupBox4->Controls->Add(this->button9);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorOther);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorSemicolon);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorTab);
			this->groupBox4->Controls->Add(this->radioButtonSeparatorSpace);
			this->groupBox4->Location = System::Drawing::Point(32, 276);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(186, 115);
			this->groupBox4->TabIndex = 5;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Separator kolumn";
			// 
			// textBoxOtherSerparator
			// 
			this->textBoxOtherSerparator->Enabled = false;
			this->textBoxOtherSerparator->Location = System::Drawing::Point(102, 89);
			this->textBoxOtherSerparator->MaxLength = 1;
			this->textBoxOtherSerparator->Name = L"textBoxOtherSerparator";
			this->textBoxOtherSerparator->Size = System::Drawing::Size(50, 20);
			this->textBoxOtherSerparator->TabIndex = 5;
			// 
			// button9
			// 
			this->button9->Enabled = false;
			this->button9->Location = System::Drawing::Point(102, 16);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 4;
			this->button9->Text = L"Wykryj";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// radioButtonSeparatorOther
			// 
			this->radioButtonSeparatorOther->AutoSize = true;
			this->radioButtonSeparatorOther->Location = System::Drawing::Point(6, 89);
			this->radioButtonSeparatorOther->Name = L"radioButtonSeparatorOther";
			this->radioButtonSeparatorOther->Size = System::Drawing::Size(45, 17);
			this->radioButtonSeparatorOther->TabIndex = 3;
			this->radioButtonSeparatorOther->Text = L"Inny";
			this->radioButtonSeparatorOther->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorOther->Click += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorSemicolon
			// 
			this->radioButtonSeparatorSemicolon->AutoSize = true;
			this->radioButtonSeparatorSemicolon->Location = System::Drawing::Point(6, 66);
			this->radioButtonSeparatorSemicolon->Name = L"radioButtonSeparatorSemicolon";
			this->radioButtonSeparatorSemicolon->Size = System::Drawing::Size(61, 17);
			this->radioButtonSeparatorSemicolon->TabIndex = 2;
			this->radioButtonSeparatorSemicolon->Text = L"Œrednik";
			this->radioButtonSeparatorSemicolon->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorSemicolon->Click += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorTab
			// 
			this->radioButtonSeparatorTab->AutoSize = true;
			this->radioButtonSeparatorTab->Location = System::Drawing::Point(6, 43);
			this->radioButtonSeparatorTab->Name = L"radioButtonSeparatorTab";
			this->radioButtonSeparatorTab->Size = System::Drawing::Size(70, 17);
			this->radioButtonSeparatorTab->TabIndex = 1;
			this->radioButtonSeparatorTab->Text = L"Tabulator";
			this->radioButtonSeparatorTab->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorTab->Click += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// radioButtonSeparatorSpace
			// 
			this->radioButtonSeparatorSpace->AutoSize = true;
			this->radioButtonSeparatorSpace->Location = System::Drawing::Point(6, 20);
			this->radioButtonSeparatorSpace->Name = L"radioButtonSeparatorSpace";
			this->radioButtonSeparatorSpace->Size = System::Drawing::Size(58, 17);
			this->radioButtonSeparatorSpace->TabIndex = 0;
			this->radioButtonSeparatorSpace->Text = L"Spacja";
			this->radioButtonSeparatorSpace->UseVisualStyleBackColor = true;
			this->radioButtonSeparatorSpace->Click += gcnew System::EventHandler(this, &ImportTextFileForm::radioButtonSeparatorSpace_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(46, 234);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Edytuj nazwê serii";
			// 
			// textBoxSeriesName
			// 
			this->textBoxSeriesName->Location = System::Drawing::Point(32, 250);
			this->textBoxSeriesName->Name = L"textBoxSeriesName";
			this->textBoxSeriesName->Size = System::Drawing::Size(186, 20);
			this->textBoxSeriesName->TabIndex = 3;
			this->textBoxSeriesName->TextChanged += gcnew System::EventHandler(this, &ImportTextFileForm::textBoxSeriesName_TextChanged);
			// 
			// buttonRemoveFile
			// 
			this->buttonRemoveFile->Enabled = false;
			this->buttonRemoveFile->Location = System::Drawing::Point(414, 224);
			this->buttonRemoveFile->Name = L"buttonRemoveFile";
			this->buttonRemoveFile->Size = System::Drawing::Size(75, 23);
			this->buttonRemoveFile->TabIndex = 2;
			this->buttonRemoveFile->Text = L"Usuñ";
			this->buttonRemoveFile->UseVisualStyleBackColor = true;
			this->buttonRemoveFile->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonRemoveFile_Click);
			// 
			// buttonAddFile
			// 
			this->buttonAddFile->Location = System::Drawing::Point(333, 224);
			this->buttonAddFile->Name = L"buttonAddFile";
			this->buttonAddFile->Size = System::Drawing::Size(75, 23);
			this->buttonAddFile->TabIndex = 1;
			this->buttonAddFile->Text = L"Dodaj";
			this->buttonAddFile->UseVisualStyleBackColor = true;
			this->buttonAddFile->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonAddFile_Click);
			// 
			// listViewFiles
			// 
			this->listViewFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnHeader1, 
				this->columnHeader2, this->columnHeader3, this->columnHeader6});
			this->listViewFiles->FullRowSelect = true;
			this->listViewFiles->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) {listViewItem1, listViewItem2});
			this->listViewFiles->Location = System::Drawing::Point(32, 27);
			this->listViewFiles->Name = L"listViewFiles";
			this->listViewFiles->Size = System::Drawing::Size(457, 191);
			this->listViewFiles->TabIndex = 0;
			this->listViewFiles->UseCompatibleStateImageBehavior = false;
			this->listViewFiles->View = System::Windows::Forms::View::Details;
			this->listViewFiles->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ImportTextFileForm::listViewFiles_ItemSelectionChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Nazwa pliku";
			this->columnHeader1->Width = 137;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Nazwa serii";
			this->columnHeader2->Width = 92;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Rozmiar pliku";
			this->columnHeader3->Width = 100;
			// 
			// columnHeader6
			// 
			this->columnHeader6->Text = L"Rozmiar danych";
			this->columnHeader6->Width = 100;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->buttonChangeImportStatus);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->button8);
			this->tabPage2->Controls->Add(this->button7);
			this->tabPage2->Controls->Add(this->buttonFieldDown);
			this->tabPage2->Controls->Add(this->buttonFieldUp);
			this->tabPage2->Controls->Add(this->buttonRemoveField);
			this->tabPage2->Controls->Add(this->buttonAddField);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->listViewFields);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(524, 450);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Krok 2: Wybierz format plików";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// buttonChangeImportStatus
			// 
			this->buttonChangeImportStatus->Enabled = false;
			this->buttonChangeImportStatus->Location = System::Drawing::Point(295, 122);
			this->buttonChangeImportStatus->Name = L"buttonChangeImportStatus";
			this->buttonChangeImportStatus->Size = System::Drawing::Size(75, 23);
			this->buttonChangeImportStatus->TabIndex = 9;
			this->buttonChangeImportStatus->Text = L"Nie importuj";
			this->buttonChangeImportStatus->UseVisualStyleBackColor = true;
			this->buttonChangeImportStatus->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonChangeImportStatus_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(33, 332);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Iloœæ pól: 5";
			// 
			// button8
			// 
			this->button8->Enabled = false;
			this->button8->Location = System::Drawing::Point(295, 306);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(118, 23);
			this->button8->TabIndex = 7;
			this->button8->Text = L"Wczytaj wzorzec";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Location = System::Drawing::Point(295, 277);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(118, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Zapisz jako wzorzec";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// buttonFieldDown
			// 
			this->buttonFieldDown->Location = System::Drawing::Point(295, 203);
			this->buttonFieldDown->Name = L"buttonFieldDown";
			this->buttonFieldDown->Size = System::Drawing::Size(100, 23);
			this->buttonFieldDown->TabIndex = 5;
			this->buttonFieldDown->Text = L"Przesuñ w dó³";
			this->buttonFieldDown->UseVisualStyleBackColor = true;
			this->buttonFieldDown->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonFieldDown_Click);
			// 
			// buttonFieldUp
			// 
			this->buttonFieldUp->Location = System::Drawing::Point(295, 174);
			this->buttonFieldUp->Name = L"buttonFieldUp";
			this->buttonFieldUp->Size = System::Drawing::Size(100, 23);
			this->buttonFieldUp->TabIndex = 4;
			this->buttonFieldUp->Text = L"Przesuñ w górê";
			this->buttonFieldUp->UseVisualStyleBackColor = true;
			this->buttonFieldUp->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonFieldUp_Click);
			// 
			// buttonRemoveField
			// 
			this->buttonRemoveField->Enabled = false;
			this->buttonRemoveField->Location = System::Drawing::Point(295, 67);
			this->buttonRemoveField->Name = L"buttonRemoveField";
			this->buttonRemoveField->Size = System::Drawing::Size(75, 23);
			this->buttonRemoveField->TabIndex = 3;
			this->buttonRemoveField->Text = L"Usuñ";
			this->buttonRemoveField->UseVisualStyleBackColor = true;
			this->buttonRemoveField->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonRemoveField_Click);
			// 
			// buttonAddField
			// 
			this->buttonAddField->Location = System::Drawing::Point(295, 38);
			this->buttonAddField->Name = L"buttonAddField";
			this->buttonAddField->Size = System::Drawing::Size(75, 23);
			this->buttonAddField->TabIndex = 2;
			this->buttonAddField->Text = L"Dodaj";
			this->buttonAddField->UseVisualStyleBackColor = true;
			this->buttonAddField->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonAddField_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(33, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(99, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Pola w jednej linijce";
			// 
			// listViewFields
			// 
			this->listViewFields->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader4, 
				this->columnHeader5, this->columnHeader7});
			this->listViewFields->FullRowSelect = true;
			this->listViewFields->GridLines = true;
			this->listViewFields->Location = System::Drawing::Point(20, 35);
			this->listViewFields->Name = L"listViewFields";
			this->listViewFields->Size = System::Drawing::Size(269, 294);
			this->listViewFields->TabIndex = 0;
			this->listViewFields->UseCompatibleStateImageBehavior = false;
			this->listViewFields->View = System::Windows::Forms::View::Details;
			this->listViewFields->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ImportTextFileForm::listViewFields_ItemSelectionChanged);
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
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox3);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(524, 450);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Krok 3: Ustawienia importu";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBoxBeginImporting);
			this->groupBox3->Controls->Add(this->checkBoxAddLayers);
			this->groupBox3->Controls->Add(this->checkBoxCreateProject);
			this->groupBox3->Location = System::Drawing::Point(18, 18);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(220, 186);
			this->groupBox3->TabIndex = 5;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Ustawienia";
			// 
			// checkBoxBeginImporting
			// 
			this->checkBoxBeginImporting->AutoSize = true;
			this->checkBoxBeginImporting->Checked = true;
			this->checkBoxBeginImporting->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxBeginImporting->Enabled = false;
			this->checkBoxBeginImporting->Location = System::Drawing::Point(15, 132);
			this->checkBoxBeginImporting->Name = L"checkBoxBeginImporting";
			this->checkBoxBeginImporting->Size = System::Drawing::Size(168, 17);
			this->checkBoxBeginImporting->TabIndex = 2;
			this->checkBoxBeginImporting->Text = L"Rozpocznij import natychmiast";
			this->checkBoxBeginImporting->UseVisualStyleBackColor = true;
			// 
			// checkBoxAddLayers
			// 
			this->checkBoxAddLayers->AutoSize = true;
			this->checkBoxAddLayers->Checked = true;
			this->checkBoxAddLayers->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxAddLayers->Location = System::Drawing::Point(15, 39);
			this->checkBoxAddLayers->Name = L"checkBoxAddLayers";
			this->checkBoxAddLayers->Size = System::Drawing::Size(95, 17);
			this->checkBoxAddLayers->TabIndex = 1;
			this->checkBoxAddLayers->Text = L"Dodaj warstwy";
			this->checkBoxAddLayers->UseVisualStyleBackColor = true;
			// 
			// checkBoxCreateProject
			// 
			this->checkBoxCreateProject->AutoSize = true;
			this->checkBoxCreateProject->Enabled = false;
			this->checkBoxCreateProject->Location = System::Drawing::Point(15, 83);
			this->checkBoxCreateProject->Name = L"checkBoxCreateProject";
			this->checkBoxCreateProject->Size = System::Drawing::Size(94, 17);
			this->checkBoxCreateProject->TabIndex = 0;
			this->checkBoxCreateProject->Text = L"Utwórz projekt";
			this->checkBoxCreateProject->UseVisualStyleBackColor = true;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->buttonCancel);
			this->panel2->Controls->Add(this->buttonPrevious);
			this->panel2->Controls->Add(this->buttonNext);
			this->panel2->Controls->Add(this->shapeContainer1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 433);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(532, 46);
			this->panel2->TabIndex = 1;
			// 
			// buttonCancel
			// 
			this->buttonCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(275, 11);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 2;
			this->buttonCancel->Text = L"Anuluj";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonCancel_Click);
			// 
			// buttonPrevious
			// 
			this->buttonPrevious->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPrevious->Location = System::Drawing::Point(372, 11);
			this->buttonPrevious->Name = L"buttonPrevious";
			this->buttonPrevious->Size = System::Drawing::Size(75, 23);
			this->buttonPrevious->TabIndex = 1;
			this->buttonPrevious->Text = L"<< Wstecz";
			this->buttonPrevious->UseVisualStyleBackColor = true;
			this->buttonPrevious->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonPrevious_Click);
			// 
			// buttonNext
			// 
			this->buttonNext->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonNext->Location = System::Drawing::Point(453, 11);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(75, 23);
			this->buttonNext->TabIndex = 0;
			this->buttonNext->Text = L"Dalej >>";
			this->buttonNext->UseVisualStyleBackColor = true;
			this->buttonNext->Click += gcnew System::EventHandler(this, &ImportTextFileForm::buttonNext_Click);
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) {this->rectangleShape1});
			this->shapeContainer1->Size = System::Drawing::Size(532, 46);
			this->shapeContainer1->TabIndex = 3;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->rectangleShape1->BorderColor = System::Drawing::SystemColors::ControlDarkDark;
			this->rectangleShape1->FillColor = System::Drawing::Color::Chocolate;
			this->rectangleShape1->Location = System::Drawing::Point(13, 3);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(504, 0);
			// 
			// contextMenuFieldList
			// 
			this->contextMenuFieldList->AllowMerge = false;
			this->contextMenuFieldList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->MenuItem1d, 
				this->MenuItem2d, this->MenuItem3d, this->toolStripMenuItem1, this->nowaDefinicjaZmiennejToolStripMenuItem});
			this->contextMenuFieldList->Name = L"contextMenuStrip1";
			this->contextMenuFieldList->Size = System::Drawing::Size(205, 98);
			// 
			// MenuItem1d
			// 
			this->MenuItem1d->Name = L"MenuItem1d";
			this->MenuItem1d->Size = System::Drawing::Size(204, 22);
			this->MenuItem1d->Text = L"1d";
			// 
			// MenuItem2d
			// 
			this->MenuItem2d->Name = L"MenuItem2d";
			this->MenuItem2d->Size = System::Drawing::Size(204, 22);
			this->MenuItem2d->Text = L"2d";
			// 
			// MenuItem3d
			// 
			this->MenuItem3d->Name = L"MenuItem3d";
			this->MenuItem3d->Size = System::Drawing::Size(204, 22);
			this->MenuItem3d->Text = L"3d";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(201, 6);
			// 
			// nowaDefinicjaZmiennejToolStripMenuItem
			// 
			this->nowaDefinicjaZmiennejToolStripMenuItem->Name = L"nowaDefinicjaZmiennejToolStripMenuItem";
			this->nowaDefinicjaZmiennejToolStripMenuItem->Size = System::Drawing::Size(204, 22);
			this->nowaDefinicjaZmiennejToolStripMenuItem->Text = L"Nowa definicja zmiennej";
			// 
			// openFileDialogSource
			// 
			this->openFileDialogSource->Filter = L"Wszystkie pliki|*.*|Pliki tekstowe|*.txt";
			this->openFileDialogSource->Multiselect = true;
			// 
			// ImportTextFileForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 479);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ImportTextFileForm";
			this->Text = L"Importuj: Plik tekstowy";
			this->Load += gcnew System::EventHandler(this, &ImportTextFileForm::ImportTextFileForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->contextMenuFieldList->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		//----------------------------------CONTAINERS --------------------------------
	public:
		ref class SourceFileInfo {
		public:
			String^ FileName;
			String^ SeriesName;
			__int64 FileSize;
			int DataSizeX, DataSizeY, DataSizeZ;
		};

		ref class FieldDescription {
		public:
			Core::iDataChannel::eDataDimension Type;
			String^ TypeName;
			String^ Name;
			int ValuesPerVariable;

		};

		ref class FieldInfo {
		public:
			FieldDescription^ Description;
			bool DoImportFiled;
			bool CanDelete;
			String ^Name;
			bool IsCoords;
			FieldInfo(){
				DoImportFiled = true;
				CanDelete = true;
				IsCoords = false;
			}

			FieldInfo(bool Deleteable){
				DoImportFiled = true;
				CanDelete = Deleteable;
				IsCoords = false;
			}
		};
		//-------------------------------DATA -------------------------------
	private: array<FieldDescription^>^ m_FieldDescriptions;

			 //-------------------------------DATA GETTERS -------------------------------
	public: bool GetStartAddLayersWizard() { return checkBoxAddLayers->Checked; }
	public: bool GetCreateProject() { return checkBoxCreateProject->Checked; }
	public: bool GetBeginImportNoe() { return checkBoxBeginImporting->Checked; }
			//--------------------------------PUBLIC FUN's -------------------------------
	public: void SetImportProcess() {
				/*for(int i = 0, j = listViewFiles->Items->Count; i < j; ++i) {
					auto importer = CoreMgt::GetProject()->NewTextFileImporter();
					auto item = listViewFiles->Items[i];
					auto sfi = (ImportTextFileForm::SourceFileInfo^)item->Tag;
					String^ fn = sfi->FileName;
					std::wstring file = marshal_as<std::wstring>(fn);
					String^ sn = sfi->SeriesName;
					std::wstring series = marshal_as<std::wstring>(sn);

					importer->SetImportFile(file);
					importer->SetSeriesName(series);
					importer->SetCollumnSeparator(static_cast<char>(GetSeparatorChar()));

					for(int i2 = 0, j2 = listViewFields->Items->Count; i2 < j2; ++i2) {
						auto item = listViewFields->Items[i2];
						auto fi = (ImportTextFileForm::FieldInfo^)item->Tag;
						String^ cn = fi->Name;
						std::wstring ColName = msclr::interop::marshal_as<std::wstring>(cn);

						unsigned ImportSettings = 0;
						if(!fi->DoImportFiled)
							ImportSettings |= Core::Interface::iTextFileImporter::is_DoNotImportCollumn;
						if(fi->IsCoords)
							ImportSettings |= Core::Interface::iTextFileImporter::is_Coordinates;

						importer->AddCollumn(fi->Description->Type, ColName, ImportSettings);
					}
					importer->BeginImport();
				}*/
			}
			//--------------------------------SMALL F's -------------------------------
	public: void AddFile(const String ^file) {
				SourceFileInfo^ sfi = gcnew SourceFileInfo();
				sfi->FileName = (String^)file;
				String^ fn = Path::GetFileName(sfi->FileName);

				ListViewItem^ itm = listViewFiles->Items->Add(fn, -1);

				sfi->SeriesName = "Seria" + itm->Index;
				itm->SubItems->Add(sfi->SeriesName);

				FileInfo^ fi = gcnew FileInfo(sfi->FileName);
				sfi->FileSize = fi->Length;
				itm->SubItems->Add(Helpers::FileSizeToString((float)fi->Length));
				itm->Tag = sfi;
			}
	public: FieldInfo^ AddCollumn(FieldDescription^ descr, bool CanDelete) {
				FieldInfo ^fi = gcnew FieldInfo(CanDelete);
				fi->Description = descr;
				fi->Name = fi->Description->Name;
				fi->DoImportFiled = true;

				ListViewItem^ itm = listViewFields->Items->Add(fi->Name, -1);
				itm->Tag = fi;
				itm->SubItems->Add(fi->Description->TypeName);
				itm->SubItems->Add(Convert::ToString(fi->DoImportFiled));

				buttonNext->Enabled = true;
				return fi;
			}

	private: void ChangeStep(int index) {
				 if(index < 0) index = 0;
				 if(index >= tabControl1->TabCount) {
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
					 return;
				 }
				 m_CurrentPage = index;
				 tabControl1->SelectedIndex = m_CurrentPage;
				 if(m_CurrentPage == 1) {
					 buttonNext->Enabled = listViewFields->Items->Count > 1;
				 }
			 }

	private: void LoadVariableDefs(String^ file) {
				 MenuItem1d->DropDownItems->Clear();
				 MenuItem2d->DropDownItems->Clear();
				 MenuItem3d->DropDownItems->Clear();

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
			 }

	public: wchar_t GetSeparatorChar() {
				if(radioButtonSeparatorSpace->Checked) return L' ';
				if(radioButtonSeparatorTab->Checked) return L'\t';
				if(radioButtonSeparatorSemicolon->Checked) return L';';
				if(radioButtonSeparatorOther->Checked) 
					return textBoxOtherSerparator->Text[0];
				return L' ';
			}
			//----------------------------------EVENTS ---------------------------------
	private: System::Void ImportTextFileForm::buttonAddFile_Click(System::Object^  sender, System::EventArgs^  e) {
				if(openFileDialogSource->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
				for(int i = 0, j = openFileDialogSource->FileNames->Length; i < j; ++i) {
					AddFile((String^)openFileDialogSource->FileNames[i]);
				}
				buttonNext->Enabled = listViewFiles->Items->Count > 0;
			}
	private: System::Void buttonFieldDown_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void buttonFieldUp_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tabControl1_Selected(System::Object^ sender, System::Windows::Forms::TabControlEventArgs^  e) {
				 tabControl1->SelectedIndex = m_CurrentPage;
			 }
	private: System::Void buttonNext_Click(System::Object^  sender, System::EventArgs^  e) {
				 ChangeStep(m_CurrentPage + 1);
			 }
	private: System::Void buttonPrevious_Click(System::Object^  sender, System::EventArgs^  e) {
				 ChangeStep(m_CurrentPage - 1);
			 }
	private: System::Void ImportTextFileForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 listViewFiles->Items->Clear();
				 m_FieldDescriptions = gcnew array<FieldDescription^>(20);
				 LoadVariableDefs("VariableDef.xml");
				 buttonNext->Enabled = false;
				 radioButtonSeparatorSpace->Checked = true;

				 FieldDescription^ Description = gcnew FieldDescription();
				 Description->Name = "Wspolrzêdne";
				 Description->Type = Core::iDataChannel::dd_3dfloat;
				 Description->TypeName = "3d";
				 AddCollumn(Description, false)->IsCoords = true; 
#ifdef _DEBUG
			//	 AddFile("d:\\Dropbox\\Studia\\!inz\\Morfology after SRX 300x300.txt");
			//	 AddFile("d:\\Dropbox\\Studia\\!inz\\Morfology before SRX 300x300.txt");
				 AddFile("d:\\Dropbox\\Studia\\!inz\\Morfology_AfterGrainGrowth0.txt");
				 // AddFile("d:\\Dropbox\\Studia\\!inz\\Morfology 1000x1000 after SRX.txt");

				 AddCollumn(m_FieldDescriptions[0], true);
				 ChangeStep(2); 
				 buttonNext->Enabled = true;
#endif
			 }
	private: System::Void buttonRemoveField_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ lvi = listViewFields->SelectedItems[0];
				 FieldInfo ^fi = (FieldInfo^)lvi->Tag;
				 if(!fi->CanDelete) return;
				 lvi->Remove();
				 // listViewFields->Items->Remove(lvi);
				 buttonNext->Enabled = listViewFields->Items->Count > 1;
			 }
	private: System::Void buttonAddField_Click(System::Object^  sender, System::EventArgs^  e) {
				 contextMenuFieldList->Show(System::Windows::Forms::Control::MousePosition);
				 buttonNext->Enabled = listViewFields->Items->Count > 1;
			 }
	private: System::Void DynamicMenuItemAddField_Click(System::Object^ sender, System::EventArgs^  e) {
				 AddCollumn((FieldDescription^)((ToolStripMenuItem^)sender)->Tag, true);
			 }
	private: System::Void listViewFields_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
				 FieldInfo ^fi = (FieldInfo^)e->Item->Tag;
				 buttonChangeImportStatus->Enabled = e->IsSelected && fi != nullptr && fi->CanDelete;
				 buttonRemoveField->Enabled = e->IsSelected && (fi != nullptr && fi->CanDelete);
				 buttonFieldDown->Enabled = e->ItemIndex + 1 < listViewFields->Items->Count;
				 buttonFieldUp->Enabled = e->ItemIndex > 0;

				 if(e->Item->Tag != nullptr) {
					 if(((FieldInfo^)e->Item->Tag)->DoImportFiled)
						 buttonChangeImportStatus->Text = "Nie importuj";
					 else 
						 buttonChangeImportStatus->Text = "Importuj";
				 }
			 }
	private: System::Void buttonChangeImportStatus_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFields->SelectedItems->Count < 1) return;
				 ListViewItem^ itm = listViewFields->SelectedItems[0];
				 FieldInfo^ fi = (FieldInfo^)itm->Tag;
				 fi->DoImportFiled = !fi->DoImportFiled;
				 itm->SubItems[2]->Text = Convert::ToString(fi->DoImportFiled);
				 if(fi->DoImportFiled)
					 buttonChangeImportStatus->Text = "Nie importuj";
				 else 
					 buttonChangeImportStatus->Text = "Importuj";
			 }
	private: System::Void buttonRemoveFile_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFiles->SelectedItems->Count < 1) return;
				 listViewFiles->SelectedItems[0]->Remove();

				 buttonNext->Enabled = listViewFiles->Items->Count > 0;
			 }
	private: System::Void listViewFiles_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
				 buttonRemoveFile->Enabled = e->IsSelected;
				 textBoxSeriesName->Enabled = e->IsSelected;
				 textBoxSeriesName->Text = e->Item->SubItems[1]->Text;
			 }
	private: System::Void textBoxSeriesName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewFiles->SelectedItems->Count < 1) return;
				 ListViewItem ^lvi = listViewFiles->SelectedItems[0];
				 lvi->SubItems[1]->Text = textBoxSeriesName->Text;
				 auto sfi = (ImportTextFileForm::SourceFileInfo^)lvi->Tag;
				 sfi->SeriesName = textBoxSeriesName->Text;
			 }
	private: System::Void radioButtonSeparatorSpace_Click(System::Object^  sender, System::EventArgs^  e) {
				 textBoxOtherSerparator->Enabled = radioButtonSeparatorOther->Checked;
			 }
	private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}
