/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ImportData.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include <Helpers.h>

#if 0
//this debug mode short cut stopped to work
#ifdef _DEBUG
#pragma unmanaged
#if BUILD_BITS == 32
#pragma comment(lib, "TextImport32d.lib")
#else
#pragma comment(lib, "TextImport64d.lib")
#endif
#define TIMPORT_API __declspec(dllimport)

#include <Plugins\TextImport\TextImport.h>

#pragma managed
#endif

#endif

#include "ImportDataItem.h"

namespace VisApp {
	namespace gui {

		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Windows;
		using namespace System::Data;
		using namespace System::Drawing;

		using namespace VisApp::Plugins;

		struct ImportDataFlags {
			enum {
				CheckBox_Maxk				= 0x000F,
				CheckBox_ExecuteNow			= 0x0001,
				CheckBox_CreateProject		= 0x0002,
				CheckBox_AddLayers			= 0x0004,

				Action_Mask					= 0x0F00,
				Action_DisableCheckBox		= 0x0100,
				Action_EnableCheckBox		= 0x0200,
				Action_GetStatus			= 0x0300,
				Action_SetStatus			= 0x0400,

				Status_True					= 0x1000,

				//predef actions
				Get_ExecuteNow		= CheckBox_ExecuteNow | Action_GetStatus,
				Get_CreateProject	= CheckBox_CreateProject | Action_GetStatus,
				Get_AddLayers		= CheckBox_AddLayers | Action_GetStatus,
			};
		};

		/// <summary>
		/// Summary for ImportData
		/// </summary>
		public ref class ImportData : public System::Windows::Forms::Form {
		public:
			ImportData(System::Windows::Forms::Form^ OwnerForm) {
				InitializeComponent();
				Helpers::ProcessFormIcon(this);
				Owner = OwnerForm;

				m_ImportPluginList = new VisApp::Plugins::WeakImportDescriptorList;
				m_PluginFilters = new std::vector<WeakImportDescriptor>();
			}
		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~ImportData() {
				delete m_ImportPluginList;
				delete m_PluginFilters;
				if (components) {
					delete components;
				}
			}
		private:
			VisApp::Plugins::WeakImportDescriptorList *m_ImportPluginList;
			std::vector<WeakImportDescriptor> *m_PluginFilters;

#if 1
		private: System::Windows::Forms::GroupBox^  groupBox3;
		private: System::Windows::Forms::CheckBox^  checkBoxBeginImporting;
		private: System::Windows::Forms::CheckBox^  checkBoxAddLayers;
		private: System::Windows::Forms::CheckBox^  checkBoxCreateProject;
		private: System::Windows::Forms::OpenFileDialog^  openFileDialogSource;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::TextBox^  textBoxSeriesName;
		private: System::Windows::Forms::Button^  buttonRemoveFile;
		private: System::Windows::Forms::Button^  buttonAddFile;
		private: System::Windows::Forms::ListView^  listViewFiles;
		private: System::Windows::Forms::ColumnHeader^  columnHeader1;
		private: System::Windows::Forms::ColumnHeader^  columnHeader2;
		private: System::Windows::Forms::ColumnHeader^  columnHeader3;
		private: System::Windows::Forms::ColumnHeader^  columnHeader4;
		private: System::Windows::Forms::ColumnHeader^  columnHeader5;
		private: System::Windows::Forms::Button^  ButtonPluginSettings;
		private: System::Windows::Forms::ColumnHeader^  columnHeader6;
		private: System::Windows::Forms::Button^  buttonOk;
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
				System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {L"plik1.txt", 
					L"Seria1", L"20MB", L"100x100"}, -1));
				System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(4) {L"plik2.txt", 
					L"Seria2", L"22MB", L"100x100"}, -1));
				this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				this->checkBoxBeginImporting = (gcnew System::Windows::Forms::CheckBox());
				this->checkBoxAddLayers = (gcnew System::Windows::Forms::CheckBox());
				this->checkBoxCreateProject = (gcnew System::Windows::Forms::CheckBox());
				this->openFileDialogSource = (gcnew System::Windows::Forms::OpenFileDialog());
				this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				this->ButtonPluginSettings = (gcnew System::Windows::Forms::Button());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->textBoxSeriesName = (gcnew System::Windows::Forms::TextBox());
				this->buttonRemoveFile = (gcnew System::Windows::Forms::Button());
				this->buttonAddFile = (gcnew System::Windows::Forms::Button());
				this->listViewFiles = (gcnew System::Windows::Forms::ListView());
				this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
				this->buttonOk = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->groupBox3->SuspendLayout();
				this->groupBox1->SuspendLayout();
				this->SuspendLayout();
				// 
				// groupBox3
				// 
				this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->groupBox3->Controls->Add(this->checkBoxBeginImporting);
				this->groupBox3->Controls->Add(this->checkBoxAddLayers);
				this->groupBox3->Controls->Add(this->checkBoxCreateProject);
				this->groupBox3->Location = System::Drawing::Point(12, 342);
				this->groupBox3->Name = L"groupBox3";
				this->groupBox3->Size = System::Drawing::Size(406, 94);
				this->groupBox3->TabIndex = 8;
				this->groupBox3->TabStop = false;
				this->groupBox3->Text = L"Ustawienia";
				// 
				// checkBoxBeginImporting
				// 
				this->checkBoxBeginImporting->AutoSize = true;
				this->checkBoxBeginImporting->Checked = true;
				this->checkBoxBeginImporting->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBoxBeginImporting->Location = System::Drawing::Point(12, 65);
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
				this->checkBoxAddLayers->Location = System::Drawing::Point(12, 19);
				this->checkBoxAddLayers->Name = L"checkBoxAddLayers";
				this->checkBoxAddLayers->Size = System::Drawing::Size(95, 17);
				this->checkBoxAddLayers->TabIndex = 1;
				this->checkBoxAddLayers->Text = L"Dodaj warstwy";
				this->checkBoxAddLayers->UseVisualStyleBackColor = true;
				// 
				// checkBoxCreateProject
				// 
				this->checkBoxCreateProject->AutoSize = true;
				this->checkBoxCreateProject->Location = System::Drawing::Point(12, 42);
				this->checkBoxCreateProject->Name = L"checkBoxCreateProject";
				this->checkBoxCreateProject->Size = System::Drawing::Size(94, 17);
				this->checkBoxCreateProject->TabIndex = 0;
				this->checkBoxCreateProject->Text = L"Utwórz projekt";
				this->checkBoxCreateProject->UseVisualStyleBackColor = true;
				// 
				// openFileDialogSource
				// 
				this->openFileDialogSource->Filter = L"Wszystkie pliki|*.*|Pliki tekstowe|*.txt";
				this->openFileDialogSource->Multiselect = true;
				// 
				// groupBox1
				// 
				this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->groupBox1->Controls->Add(this->ButtonPluginSettings);
				this->groupBox1->Controls->Add(this->label1);
				this->groupBox1->Controls->Add(this->textBoxSeriesName);
				this->groupBox1->Controls->Add(this->buttonRemoveFile);
				this->groupBox1->Controls->Add(this->buttonAddFile);
				this->groupBox1->Controls->Add(this->listViewFiles);
				this->groupBox1->Location = System::Drawing::Point(12, 12);
				this->groupBox1->Margin = System::Windows::Forms::Padding(5);
				this->groupBox1->Name = L"groupBox1";
				this->groupBox1->Padding = System::Windows::Forms::Padding(5);
				this->groupBox1->Size = System::Drawing::Size(594, 322);
				this->groupBox1->TabIndex = 10;
				this->groupBox1->TabStop = false;
				this->groupBox1->Text = L"Pliki Ÿród³owe";
				// 
				// ButtonPluginSettings
				// 
				this->ButtonPluginSettings->Enabled = false;
				this->ButtonPluginSettings->Location = System::Drawing::Point(19, 227);
				this->ButtonPluginSettings->Name = L"ButtonPluginSettings";
				this->ButtonPluginSettings->Size = System::Drawing::Size(194, 23);
				this->ButtonPluginSettings->TabIndex = 11;
				this->ButtonPluginSettings->Text = L"Opcje wtyczki";
				this->ButtonPluginSettings->UseVisualStyleBackColor = true;
				this->ButtonPluginSettings->Click += gcnew System::EventHandler(this, &ImportData::ButtonPluginSettings_Click);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(29, 269);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(99, 13);
				this->label1->TabIndex = 10;
				this->label1->Text = L"Nazwa serii danych";
				// 
				// textBoxSeriesName
				// 
				this->textBoxSeriesName->Location = System::Drawing::Point(19, 285);
				this->textBoxSeriesName->Name = L"textBoxSeriesName";
				this->textBoxSeriesName->Size = System::Drawing::Size(186, 20);
				this->textBoxSeriesName->TabIndex = 9;
				this->textBoxSeriesName->TextChanged += gcnew System::EventHandler(this, &ImportData::textBoxSeriesName_TextChanged);
				// 
				// buttonRemoveFile
				// 
				this->buttonRemoveFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->buttonRemoveFile->Enabled = false;
				this->buttonRemoveFile->Location = System::Drawing::Point(475, 227);
				this->buttonRemoveFile->Name = L"buttonRemoveFile";
				this->buttonRemoveFile->Size = System::Drawing::Size(96, 23);
				this->buttonRemoveFile->TabIndex = 8;
				this->buttonRemoveFile->Text = L"Usuñ";
				this->buttonRemoveFile->UseVisualStyleBackColor = true;
				this->buttonRemoveFile->Click += gcnew System::EventHandler(this, &ImportData::buttonRemoveFile_Click);
				// 
				// buttonAddFile
				// 
				this->buttonAddFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->buttonAddFile->Location = System::Drawing::Point(377, 227);
				this->buttonAddFile->Name = L"buttonAddFile";
				this->buttonAddFile->Size = System::Drawing::Size(96, 23);
				this->buttonAddFile->TabIndex = 7;
				this->buttonAddFile->Text = L"Dodaj";
				this->buttonAddFile->UseVisualStyleBackColor = true;
				this->buttonAddFile->Click += gcnew System::EventHandler(this, &ImportData::buttonAddFile_Click);
				// 
				// listViewFiles
				// 
				this->listViewFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->listViewFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->columnHeader1, 
					this->columnHeader2, this->columnHeader3, this->columnHeader4, this->columnHeader5, this->columnHeader6});
				this->listViewFiles->FullRowSelect = true;
				this->listViewFiles->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) {listViewItem1, listViewItem2});
				this->listViewFiles->Location = System::Drawing::Point(19, 30);
				this->listViewFiles->Name = L"listViewFiles";
				this->listViewFiles->Size = System::Drawing::Size(552, 191);
				this->listViewFiles->TabIndex = 6;
				this->listViewFiles->UseCompatibleStateImageBehavior = false;
				this->listViewFiles->View = System::Windows::Forms::View::Details;
				this->listViewFiles->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ImportData::listViewFiles_ItemSelectionChanged);
				// 
				// columnHeader1
				// 
				this->columnHeader1->Text = L"Nazwa pliku";
				this->columnHeader1->Width = 139;
				// 
				// columnHeader2
				// 
				this->columnHeader2->Text = L"Nazwa serii";
				this->columnHeader2->Width = 66;
				// 
				// columnHeader3
				// 
				this->columnHeader3->Text = L"Rozmiar pliku";
				this->columnHeader3->Width = 76;
				// 
				// columnHeader4
				// 
				this->columnHeader4->Text = L"Rozmiar danych";
				this->columnHeader4->Width = 92;
				// 
				// columnHeader5
				// 
				this->columnHeader5->Text = L"Wtyczka";
				this->columnHeader5->Width = 100;
				// 
				// columnHeader6
				// 
				this->columnHeader6->Text = L"Status";
				// 
				// buttonOk
				// 
				this->buttonOk->Location = System::Drawing::Point(424, 342);
				this->buttonOk->Name = L"buttonOk";
				this->buttonOk->Size = System::Drawing::Size(75, 23);
				this->buttonOk->TabIndex = 11;
				this->buttonOk->Text = L"Ok";
				this->buttonOk->UseVisualStyleBackColor = true;
				this->buttonOk->Click += gcnew System::EventHandler(this, &ImportData::buttonOk_Click);
				// 
				// button2
				// 
				this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->button2->Location = System::Drawing::Point(531, 342);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(75, 23);
				this->button2->TabIndex = 12;
				this->button2->Text = L"Anuluj";
				this->button2->UseVisualStyleBackColor = true;
				// 
				// ImportData
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(623, 448);
				this->Controls->Add(this->button2);
				this->Controls->Add(this->buttonOk);
				this->Controls->Add(this->groupBox1);
				this->Controls->Add(this->groupBox3);
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				this->Name = L"ImportData";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				this->Text = L"Importuj dane";
				this->Load += gcnew System::EventHandler(this, &ImportData::ImportData_Load);
				this->Shown += gcnew System::EventHandler(this, &ImportData::ImportData_Shown);
				this->groupBox3->ResumeLayout(false);
				this->groupBox3->PerformLayout();
				this->groupBox1->ResumeLayout(false);
				this->groupBox1->PerformLayout();
				this->ResumeLayout(false);

			}
#pragma endregion
#endif
			//------------------------------public shit ------------------------------

		public: bool ExecuteAction(unsigned data) {
					switch (data & ImportDataFlags::Action_Mask) {
					case ImportDataFlags::Action_DisableCheckBox: 
						if(data & ImportDataFlags::CheckBox_AddLayers) checkBoxAddLayers->Enabled = false;
						if(data & ImportDataFlags::CheckBox_CreateProject) checkBoxCreateProject->Enabled = false;
						if(data & ImportDataFlags::CheckBox_ExecuteNow) checkBoxBeginImporting->Enabled = false;
						return true;
					case ImportDataFlags::Action_EnableCheckBox: 
						if(data & ImportDataFlags::CheckBox_AddLayers) checkBoxAddLayers->Enabled = true;
						if(data & ImportDataFlags::CheckBox_CreateProject) checkBoxCreateProject->Enabled = true;
						if(data & ImportDataFlags::CheckBox_ExecuteNow) checkBoxBeginImporting->Enabled = true;
						return true;
					case ImportDataFlags::Action_GetStatus: 
						if(data & ImportDataFlags::CheckBox_AddLayers && !checkBoxAddLayers->Checked) return false;
						if(data & ImportDataFlags::CheckBox_CreateProject && !checkBoxCreateProject->Checked) return false;
						if(data & ImportDataFlags::CheckBox_ExecuteNow && !checkBoxBeginImporting->Checked) return false;
						return true;
					case ImportDataFlags::Action_SetStatus: 
						if(data & ImportDataFlags::CheckBox_AddLayers) checkBoxAddLayers->Checked = (data & ImportDataFlags::Status_True) > 0;
						if(data & ImportDataFlags::CheckBox_CreateProject) checkBoxCreateProject->Checked = (data & ImportDataFlags::Status_True) > 0;
						if(data & ImportDataFlags::CheckBox_ExecuteNow) checkBoxBeginImporting->Checked = (data & ImportDataFlags::Status_True) > 0;
						return true;
					};
					return false;
				};
		public: void SetImportProcess(const std::wstring &DestProj) {
					for(int i = 0, j = listViewFiles->Items->Count; i < j; ++i) {
						ListViewItem ^lvi = listViewFiles->Items[i];

						lvi->SubItems[1]->Text = textBoxSeriesName->Text;
						auto ii = (ImportInfo^)lvi->Tag;

						int c = ii->GetInstance().use_count();

						auto plugin = ii->GetInstance();
						plugin->SetProjectName(DestProj, Helpers::ToStdWStr(ii->SeriesName));
						auto worker = plugin->Execute().lock();
						if(ExecuteAction(ImportDataFlags::Get_ExecuteNow)) 
							worker->Execute();

						delete ii;
						lvi->Tag = nullptr;
						//TODO: handle failure!!
					}
					listViewFiles->Items->Clear();
				}

				//------------------------------FORM EVENTS------------------------------

		private: System::Void ImportData_Load(System::Object^  sender, System::EventArgs^  e) {
					 listViewFiles->Items->Clear();
#ifndef _DEBUG
					 checkBoxBeginImporting->Visible = false;
#endif
				 }
		private: System::Void ImportData_Shown(System::Object^  sender, System::EventArgs^  e) {
					 auto mgt = VisApp::Plugins::PluginManager::Instance();
					 mgt->GetImportPlugins(*m_ImportPluginList);
					 if(m_ImportPluginList->empty()) {
						 MessageBox::Show("Nie ma za³adownych wtyczek importu.\nAkcja nie mo¿liwa.", Application::ProductName,
							 MessageBoxButtons::OK,MessageBoxIcon::Error);
						 this->DialogResult = System::Windows::Forms::DialogResult::Abort;
						 return;
					 }

					 RefreshFilter();
#if 0
//def _DEBUG
					 using VisApp::Types::DataType;
					 const char* D1IntFiles[] = {
						 "d:\\Dropbox\\Studia\\!inz\\Morfology after SRX 300x300.txt", 
						 "d:\\Dropbox\\Studia\\!inz\\Morfology before SRX 300x300.txt", 
						 //	 "d:\\Dropbox\\Studia\\!inz\\Morfology 1000x1000 after SRX.txt",
						 //	 "d:\\Dropbox\\Studia\\!inz\\Morfology 1000x1000 before SRX.txt",
						 "d:\\Dropbox\\Studia\\!inz\\Morfology_AfterGrainGrowth0.txt",
						 0
					 };

					 if(m_PluginFilters->size() > 0)
						 for(const char** it = D1IntFiles; *it; ++it) {
							 ImportInfo^ ii = AddFile(gcnew String(*it), m_PluginFilters->at(0));
							 ii->AddVariable(L"Id ziarna", DataType::D1Integer());
						 }

						 cli::array<System::String^> ^D1FloatFiles = gcnew cli::array<System::String^>(1) {
							 "d:\\Dropbox\\Studia\\!inz\\Morfology_id+orientacja krystalograficzna.txt"
						 };
						 {
							 String ^test = "d:\\Dropbox\\Studia\\!inz\\test_1000x1000x1.txt";
							 ImportInfo^ ii = AddFile(test, m_PluginFilters->at(0));
							 ii->AddVariable(L"sinsin", DataType::D1Float())
								 ->AddVariable(L"sincos", DataType::D1Float())
								 ->AddVariable(L"coscos", DataType::D1Float())
								 ->AddVariable(L"center", DataType::D1Float())
								 ->AddVariable(L"d3", DataType::D3Float());
						 }
						 {
							 String ^test = "d:\\Dropbox\\Studia\\!inz\\Morfology_id+orientacja krystalograficzna.txt";
							 ImportInfo^ ii = AddFile(test, m_PluginFilters->at(0));
							 ii->AddVariable(L"Id ziarna", DataType::D1Integer())
								 ->AddVariable(L"orientacja", DataType::D1Float())
								 ->castPlugin()->GetCoordDescriptor()->Type = DataType::D2Integer();
						 }
#endif
				 }

				 //------------------------------------Events --------------------------------------

		private: System::Void buttonAddFile_Click(System::Object^  sender, System::EventArgs^  e) {
					 if(openFileDialogSource->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
					 int filter = openFileDialogSource->FilterIndex - 1;
					 for(int i = 0, j = openFileDialogSource->FileNames->Length; i < j; ++i) {
						 AddFile((String^)openFileDialogSource->FileNames[i], m_PluginFilters->at(filter));
					 }
				 }
		private: System::Void listViewFiles_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
					 buttonRemoveFile->Enabled = e->IsSelected;
					 textBoxSeriesName->Enabled = e->IsSelected;
					 ButtonPluginSettings->Enabled = e->IsSelected;
					 textBoxSeriesName->Text = e->Item->SubItems[1]->Text;
				 }
		private: System::Void textBoxSeriesName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
					 if(listViewFiles->SelectedItems->Count < 1) return;
					 ListViewItem ^lvi = listViewFiles->SelectedItems[0];
					 lvi->SubItems[1]->Text = textBoxSeriesName->Text;
					 auto ii = (ImportInfo^)lvi->Tag;
					 ii->SeriesName = textBoxSeriesName->Text;
				 }
		private: System::Void ButtonPluginSettings_Click(System::Object^  sender, System::EventArgs^  e) {
					 ListViewItem ^lvi = listViewFiles->SelectedItems[0];
					 auto ii = (ImportInfo^)lvi->Tag;
					 ii->GetInstance()->GetCLIGuiHandler()->OpenGui(this);
					 ii->UpdateItem();
				 }
		private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e) {
					 //validate
					 DialogResult = Forms::DialogResult::OK;
				 }
		private: System::Void buttonRemoveFile_Click(System::Object^  sender, System::EventArgs^  e) {
					 if(listViewFiles->SelectedItems->Count < 1) return;
					 ListViewItem ^lvi = listViewFiles->SelectedItems[0];
					 lvi->SubItems[1]->Text = textBoxSeriesName->Text;
					 auto ii = (ImportInfo^)lvi->Tag;
					 delete ii;
					 lvi->Tag = nullptr;
					 lvi->Remove();
				 }

				 //--------------------------------Files Mgt ------------------------------

		private: ImportInfo^ AddFile(String^ FileName, WeakImportDescriptor plugin) {
					 auto descriptor = plugin.lock();
					 auto instance = descriptor->CreateInstance();
					 auto &import = *((SharedImportPlugin*)&instance);
					 // auto &import = std::dynamic_pointer_cast<VisApp::Plugins::ImportPlugin>(descriptor->CreateInstance());
					 if(!import) {
						 return nullptr;
						 //TODO: not ignore the case
					 }

					 import->SetSourceFile(Helpers::ToStdWStr(FileName));
					 import->PreprocessFile();

					 ImportInfo ^ii = gcnew ImportInfo(listViewFiles);
					 ii->GetInstance() = import;
					 ii->FileName = FileName;
					 *ii->PluginDescriptor = plugin;
					 ii->PluginName = Helpers::ToString(import->GetName());

					 ii->SeriesName = "Seria " + ii->GetListItem()->Index;
					 ii->UpdateItem();
					 ii->PerformCheck();
					 return ii;
				 }

				 //----------------------------Functions --------------------------------------

		private: System::Void RefreshFilter() {
					 String ^Filter = gcnew String("");
					 m_PluginFilters->clear();
					 for(auto it = m_ImportPluginList->begin(), jt = m_ImportPluginList->end(); it != jt; ++it) {
						 if(it->expired()) continue;
						 auto descr = it->lock();
						 auto exts = descr->GetExtFilter();
						 String ^Pname = Helpers::ToString(descr->GetName());
						 for(auto iu = exts.begin(), ju = exts.end(); iu != ju; ++iu) {
							 String ^ext = Helpers::ToString(*iu);
							 String ^line;
							 line = String::Format("{0} ({1})|{1}", Pname, ext);
							 if(Filter->Length > 0)
								 Filter += "|";
							 Filter += line;
							 m_PluginFilters->push_back(*it);
						 }
					 }

					 openFileDialogSource->Filter = Filter;
					 openFileDialogSource->FilterIndex = 0;
				 }

				 //------------------------------OTHER-------------------------------------

		};
	}
}
