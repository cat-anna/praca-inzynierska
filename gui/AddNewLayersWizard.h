/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/AddNewLayersWizard.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "Helpers.h"
#include "CoreMgt.h"

#include "SelectLayerTypesWindow.h"

#include <msclr\marshal_cppstd.h>

namespace VisApp {
namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using msclr::interop::marshal_as;
	using Collections::Generic::List;

	using VisApp::Plugins::SharedProcessPlugin;

	/// <summary>
	/// Summary for AddNewLayersWizard
	/// </summary>
	public ref class AddNewLayersWizard : public System::Windows::Forms::Form
	{
	public:
		AddNewLayersWizard(System::Windows::Forms::Form^ OwnerForm) {
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
			Owner = OwnerForm;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddNewLayersWizard() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::GroupBox^  groupBox1;

	private: System::Windows::Forms::Button^  LayerPropertiesButton;
	private: System::Windows::Forms::Button^  buttonRemoveLayer;
	private: System::Windows::Forms::Button^  buttonAddLayer;
	private: System::Windows::Forms::ListView^  listViewLayers;
	private: System::Windows::Forms::ColumnHeader^  columnLayerName;
	private: System::Windows::Forms::ColumnHeader^  columnLayerType;
	private: System::Windows::Forms::ColumnHeader^  columnLayerSource;
	private: System::Windows::Forms::ColumnHeader^  columnLayerPlugin;

	private: System::Windows::Forms::CheckBox^  checkBoxBeginNow;
	private: System::Windows::Forms::TextBox^  textBoxEditName;

	private: System::Windows::Forms::Label^  label1;
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
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"Warstwy 2d", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup2 = (gcnew System::Windows::Forms::ListViewGroup(L"Warstwy 3d", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"test"));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"test"));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxEditName = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->LayerPropertiesButton = (gcnew System::Windows::Forms::Button());
			this->buttonRemoveLayer = (gcnew System::Windows::Forms::Button());
			this->buttonAddLayer = (gcnew System::Windows::Forms::Button());
			this->listViewLayers = (gcnew System::Windows::Forms::ListView());
			this->columnLayerName = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnLayerPlugin = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnLayerType = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnLayerSource = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->checkBoxBeginNow = (gcnew System::Windows::Forms::CheckBox());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(532, 342);
			this->panel1->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBoxEditName);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->LayerPropertiesButton);
			this->groupBox1->Controls->Add(this->buttonRemoveLayer);
			this->groupBox1->Controls->Add(this->buttonAddLayer);
			this->groupBox1->Controls->Add(this->listViewLayers);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(532, 342);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Lista warstw";
			// 
			// textBoxEditName
			// 
			this->textBoxEditName->Location = System::Drawing::Point(6, 315);
			this->textBoxEditName->Name = L"textBoxEditName";
			this->textBoxEditName->Size = System::Drawing::Size(137, 20);
			this->textBoxEditName->TabIndex = 5;
			this->textBoxEditName->TextChanged += gcnew System::EventHandler(this, &AddNewLayersWizard::textBoxEditName_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 299);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(81, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Nazwa warstwy";
			// 
			// LayerPropertiesButton
			// 
			this->LayerPropertiesButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->LayerPropertiesButton->Enabled = false;
			this->LayerPropertiesButton->Location = System::Drawing::Point(210, 313);
			this->LayerPropertiesButton->Name = L"LayerPropertiesButton";
			this->LayerPropertiesButton->Size = System::Drawing::Size(103, 23);
			this->LayerPropertiesButton->TabIndex = 3;
			this->LayerPropertiesButton->Text = L"Opcje warstwy";
			this->LayerPropertiesButton->UseVisualStyleBackColor = true;
			this->LayerPropertiesButton->Click += gcnew System::EventHandler(this, &AddNewLayersWizard::LayerPropertiesButton_Click);
			// 
			// buttonRemoveLayer
			// 
			this->buttonRemoveLayer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonRemoveLayer->Enabled = false;
			this->buttonRemoveLayer->Location = System::Drawing::Point(370, 313);
			this->buttonRemoveLayer->Name = L"buttonRemoveLayer";
			this->buttonRemoveLayer->Size = System::Drawing::Size(75, 23);
			this->buttonRemoveLayer->TabIndex = 2;
			this->buttonRemoveLayer->Text = L"Usuñ";
			this->buttonRemoveLayer->UseVisualStyleBackColor = true;
			this->buttonRemoveLayer->Click += gcnew System::EventHandler(this, &AddNewLayersWizard::buttonRemoveLayer_Click);
			// 
			// buttonAddLayer
			// 
			this->buttonAddLayer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonAddLayer->Location = System::Drawing::Point(451, 313);
			this->buttonAddLayer->Name = L"buttonAddLayer";
			this->buttonAddLayer->Size = System::Drawing::Size(75, 23);
			this->buttonAddLayer->TabIndex = 1;
			this->buttonAddLayer->Text = L"Dodaj";
			this->buttonAddLayer->UseVisualStyleBackColor = true;
			this->buttonAddLayer->Click += gcnew System::EventHandler(this, &AddNewLayersWizard::buttonAddLayer_Click);
			// 
			// listViewLayers
			// 
			this->listViewLayers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->listViewLayers->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnLayerName, 
				this->columnLayerPlugin, this->columnLayerType, this->columnLayerSource});
			this->listViewLayers->FullRowSelect = true;
			listViewGroup1->Header = L"Warstwy 2d";
			listViewGroup1->Name = L"listViewGroup2dLayers";
			listViewGroup2->Header = L"Warstwy 3d";
			listViewGroup2->Name = L"listViewGroup3dLayers";
			this->listViewLayers->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(2) {listViewGroup1, listViewGroup2});
			this->listViewLayers->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) {listViewItem1, listViewItem2});
			this->listViewLayers->Location = System::Drawing::Point(6, 19);
			this->listViewLayers->Name = L"listViewLayers";
			this->listViewLayers->ShowGroups = false;
			this->listViewLayers->Size = System::Drawing::Size(520, 275);
			this->listViewLayers->TabIndex = 0;
			this->listViewLayers->UseCompatibleStateImageBehavior = false;
			this->listViewLayers->View = System::Windows::Forms::View::Details;
			this->listViewLayers->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &AddNewLayersWizard::listViewLayers_ItemSelectionChanged);
			// 
			// columnLayerName
			// 
			this->columnLayerName->Text = L"Nazwa";
			this->columnLayerName->Width = 120;
			// 
			// columnLayerPlugin
			// 
			this->columnLayerPlugin->Text = L"Wtyczka";
			this->columnLayerPlugin->Width = 80;
			// 
			// columnLayerType
			// 
			this->columnLayerType->Text = L"Typ";
			this->columnLayerType->Width = 89;
			// 
			// columnLayerSource
			// 
			this->columnLayerSource->Text = L"ród³o danych";
			this->columnLayerSource->Width = 195;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->checkBoxBeginNow);
			this->panel2->Controls->Add(this->buttonCancel);
			this->panel2->Controls->Add(this->buttonOk);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 348);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(532, 45);
			this->panel2->TabIndex = 1;
			// 
			// checkBoxBeginNow
			// 
			this->checkBoxBeginNow->AutoSize = true;
			this->checkBoxBeginNow->Checked = true;
			this->checkBoxBeginNow->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxBeginNow->Location = System::Drawing::Point(6, 14);
			this->checkBoxBeginNow->Name = L"checkBoxBeginNow";
			this->checkBoxBeginNow->Size = System::Drawing::Size(137, 17);
			this->checkBoxBeginNow->TabIndex = 2;
			this->checkBoxBeginNow->Text = L"Rozpocznij natychmiast";
			this->checkBoxBeginNow->UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this->buttonCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(365, 14);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 1;
			this->buttonCancel->Text = L"Anuluj";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// buttonOk
			// 
			this->buttonOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOk->Location = System::Drawing::Point(446, 14);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"Ok";
			this->buttonOk->UseVisualStyleBackColor = true;
			// 
			// AddNewLayersWizard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(532, 393);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"AddNewLayersWizard";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Dodaj warstwy";
			this->Load += gcnew System::EventHandler(this, &AddNewLayersWizard::AddNewLayersWizard_Load);
			this->panel1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		// -------------- OwnTypes --------------
		//	public: typedef SelectLayerTypesWindow::ViewDataPointer ViewDataPointer;
		//	public: typedef SelectLayerTypesWindow::LayerDescriptor LayerDescriptor;
		//	public: typedef SelectLayerTypesWindow::DataChannelPointer DataChannelPointer;
	public: ref struct ProcessDescriptor {
				//				LayerDescriptor ^Layer;
				//				List<DataChannelPointer^> Data;

				String ^Project, ^Series, ^Channel;
				String ^Name;

				VisApp::Plugins::SharedProcessDescriptor& Descriptor() { return *m_Descriptor; }
				VisApp::Plugins::SharedProcessPlugin& PluginInstance() { return *m_PluginInstance; }

				std::wstring GetProject() { return Helpers::ToStdWStr(Project); }
				std::wstring GetSeries() { return Helpers::ToStdWStr(Series); }
				std::wstring GetChannel() { return Helpers::ToStdWStr(Channel); }

				ProcessDescriptor(ListView ^lv) : m_lv(lv), m_lvItem(nullptr) { 
					m_Descriptor = new VisApp::Plugins::SharedProcessDescriptor(); 
					m_PluginInstance = new VisApp::Plugins::SharedProcessPlugin(); 
					Name = "Brak nazwy";
				}
				~ProcessDescriptor() { 
					delete m_Descriptor; 
					delete m_PluginInstance; 
				}

				void UpdateItem() {
					m_lv->Invoke(gcnew Action(this, &ProcessDescriptor::DoUpdateItem));
				}


	private:
		void DoUpdateItem() {
			if(m_lvItem == nullptr) {
				m_lvItem = m_lv->Items->Add("");
				m_lvItem->Tag = this;
				for(int i =0; i < 5; ++i)
					m_lvItem->SubItems->Add("?");

				m_lvItem->SubItems[1]->Text = Helpers::ToString(PluginInstance()->GetName());
			}

			auto & datasrc = PluginInstance()->GetDataSource();
			auto data = datasrc.Translate();
			if(data.IsOk()) {
				m_lvItem->SubItems[2]->Text = Helpers::ToString(data.Channel->GetType());
			} else {
				m_lvItem->SubItems[2]->Text = "?";
			}
			
			m_lvItem->SubItems[0]->Text = Name;
			m_lvItem->SubItems[3]->Text = Helpers::StringDataPointer2String(PluginInstance()->GetDataSource());
		}

		ListViewItem ^m_lvItem;
		ListView ^m_lv;
		VisApp::Plugins::SharedProcessDescriptor *m_Descriptor;
		VisApp::Plugins::SharedProcessPlugin *m_PluginInstance;
			};

			//-------------- PRIV FUN -------------

	private: List<SelectLayerTypesWindow::ProcessDataPointer^>^ ShowLayerSelector() {
				 SelectLayerTypesWindow ^sltw = gcnew SelectLayerTypesWindow(this);
				 sltw->Reset();
				 if(sltw->ShowDialog(this) != System::Windows::Forms::DialogResult::OK)
					 return nullptr;
				 return sltw->GetSelectedLayers();
			 }
	private: void AddSelectedLayers() {
				 auto selection = ShowLayerSelector();
				 if(selection == nullptr) return;

				 for each(SelectLayerTypesWindow::ProcessDataPointer ^it in selection) {
					 auto plugin = it->Descriptor()->CreateInstance();
					 auto &instance = *((SharedProcessPlugin*)&plugin);
					 // auto instance = std::dynamic_pointer_cast<VisApp::Plugins::ProcessPlugin>();
					 if(!instance) {
						 //TODO: make some error!
						 MessageBox::Show("B³¹d tworzenia instancji pluginu " + Helpers::ToString(it->Descriptor()->GetName()));
						 continue;
					 }

					 ProcessDescriptor ^pd = gcnew ProcessDescriptor(listViewLayers);
					 pd->Descriptor() = it->Descriptor();
					 pd->Project = it->Project;
					 pd->Series = it->Series;
					 pd->Channel = it->Channel;
					 pd->PluginInstance() = instance;

					 instance->SetDataSource(
						 Helpers::ToString(pd->Project),
						 Helpers::ToString(pd->Series),
						 Helpers::ToString(pd->Channel)
						 );
					 pd->UpdateItem();
				 }
			 }

			 //------------ PUBLIC FUN -------------

	public: void BeginProcesses() {
				for(int i = 0, j = listViewLayers->Items->Count; i < j; ++i) {
					ListViewItem ^lvi = listViewLayers->Items[i];
					auto pd = (ProcessDescriptor^)lvi->Tag;

					auto plugin = pd->PluginInstance();
					plugin->SetOutputName(Helpers::ToString(pd->Name));
					auto worker = plugin->Execute().lock();
					if(checkBoxBeginNow->Checked) 
						worker->Execute();
					//TODO: handle failure!!
				}
			}

			//-------------- EVENTS --------------

	private: System::Void AddNewLayersWizard_Load(System::Object^  sender, System::EventArgs^  e) {
				 listViewLayers->Items->Clear();
#ifndef _DEBUG
				 checkBoxBeginNow->Visible = false;
#endif
			 }
	private: System::Void buttonAddLayer_Click(System::Object^  sender, System::EventArgs^  e) {
				 AddSelectedLayers();
			 }
	private: System::Void listViewLayers_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e) {
				 bool single = listViewLayers->SelectedItems->Count == 1;
				 LayerPropertiesButton->Enabled = single;
				 buttonRemoveLayer->Enabled = single;
				 textBoxEditName->Enabled = single;		
				 if(listViewLayers->SelectedItems->Count == 1) {
					 ListViewItem ^sel = listViewLayers->SelectedItems[0];
					 auto pd = (ProcessDescriptor^)sel->Tag;
					 textBoxEditName->Text = pd->Name;
				 }
				 else textBoxEditName->Text = "";
			 }
	private: System::Void buttonRemoveLayer_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewLayers->SelectedItems->Count != 1) return;
				 ListViewItem ^sel = listViewLayers->SelectedItems[0];
				 auto pd = (ProcessDescriptor^)sel->Tag;
				 sel->Tag = nullptr; 
				 delete pd; 
				 listViewLayers->Items->Remove(sel);
			 }
	private: System::Void LayerPropertiesButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewLayers->SelectedItems->Count != 1) return;
				 ListViewItem ^sel = listViewLayers->SelectedItems[0];
				 auto pd = (ProcessDescriptor^)sel->Tag;
				 auto &instance = pd->PluginInstance();
				 auto gui = instance->GetCLIGuiHandler();
				 if(!gui) {
					 MessageBox::Show(this, "Wtyczka nie posiada okna konfiguracji", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Information);
					 return;
				 }

				 TRY_PROTECT({ gui->OpenGui(this); },
					 L"Wyst¹pi³ b³¹d w interfejsie plugina.\nZaleca siê ponowne uruchomienie aplikacji.",
					{ sel->Tag = nullptr; delete pd; listViewLayers->Items->Remove(sel); return; })
				 pd->UpdateItem();
			 }

	private: System::Void textBoxEditName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(listViewLayers->SelectedItems->Count != 1) return;
				 ListViewItem ^sel = listViewLayers->SelectedItems[0];
				 auto pd = (ProcessDescriptor^)sel->Tag;
				 pd->Name = textBoxEditName->Text;
				 pd->UpdateItem();
			 }
};
}
}
