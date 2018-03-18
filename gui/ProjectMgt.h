/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ProjectMgt.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "Helpers.h"
#include "CoreManip.h"

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

		using VisApp::Interface::SharedProject;

		enum class ProjectMgtPage {
			None, Layer, Data, Project,
		};

		delegate void StdStringActionHandler(String^);

		/// <summary>
		/// Summary for ProjectMgt
		/// </summary>
		public ref class ProjectMgt : public System::Windows::Forms::Form {
		public:
			static void DoShowFor(Form ^Owner,  SharedProject Project, ProjectMgtPage where, const std::wstring &ResName) {
				ProjectMgt ^w = gcnew ProjectMgt(Owner, Project);
				switch (where) {
				case ProjectMgtPage::Layer:
					//	Invoke(gcnew StdStringActionHandler(this, &ProjectMgt::ShowLayerProps), Helpers::ToString(ResName));
					break;
				case ProjectMgtPage::Data:
					break;
				case ProjectMgtPage::Project:
					break;
				}
				w->ShowDialog();
				delete w;
			}
			static void DoShow(Form ^Owner,  SharedProject Project) {
				ProjectMgt ^w = gcnew ProjectMgt(Owner, Project);
				w->ShowDialog();
				delete w;
			}
			static void Show();
		private: System::Windows::Forms::Panel^  panel2;
		public: 
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::Panel^  panel1;
		private: System::Windows::Forms::TabControl^  tabControl1;
		private: System::Windows::Forms::TabPage^  tabPage1;
		private: System::Windows::Forms::TabPage^  tabPage2;
		private: System::Windows::Forms::ListView^  listViewData;

		private: System::Windows::Forms::ListView^  listViewLayers;

		private: System::Windows::Forms::ColumnHeader^  columnHeader1;
		private: System::Windows::Forms::ColumnHeader^  columnHeader4;
		private: System::Windows::Forms::ColumnHeader^  columnHeader3;
		private: System::Windows::Forms::ColumnHeader^  columnHeader2;
		private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripLayer;
		private: System::Windows::Forms::ToolStripMenuItem^  zmieñNazwêToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  zmieñKolorToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ustawieniaWarstwyToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  usuñToolStripMenuItem;
		private: System::Windows::Forms::ColumnHeader^  columnHeader5;
		private: System::Windows::Forms::ColumnHeader^  columnHeader6;
		private: System::Windows::Forms::ColumnHeader^  columnHeader7;
		private: System::Windows::Forms::ColumnHeader^  columnHeader8;
		private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripData;
		private: System::Windows::Forms::ToolStripMenuItem^  zmieñNazwêToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^  usuñToolStripMenuItem1;

		protected:
			SharedProject *m_Project;
			SharedProject& Project() { return *m_Project; }

		public: bool AskForPermission() {
					return MessageBox::Show(this, L"Czy jesteœ pewien?", Application::ProductName, MessageBoxButtons::YesNo, MessageBoxIcon::Question) == Forms::DialogResult::Yes;
				}

				ProjectMgt(Form ^aOwner, SharedProject &Project): 
					m_Project(new SharedProject(Project)){
						Owner = aOwner;
						InitializeComponent();
						Helpers::ProcessFormIcon(this);
				}

				~ProjectMgt() {
					if (components) {
						delete components;
					}
					delete m_Project;
				}
		private: System::ComponentModel::IContainer^  components;
		public: 
		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>


#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void) {
				this->components = (gcnew System::ComponentModel::Container());
				this->panel2 = (gcnew System::Windows::Forms::Panel());
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->panel1 = (gcnew System::Windows::Forms::Panel());
				this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				this->listViewData = (gcnew System::Windows::Forms::ListView());
				this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
				this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				this->listViewLayers = (gcnew System::Windows::Forms::ListView());
				this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
				this->contextMenuStripLayer = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				this->zmieñNazwêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->zmieñKolorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ustawieniaWarstwyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->usuñToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->contextMenuStripData = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				this->zmieñNazwêToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->usuñToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->panel2->SuspendLayout();
				this->panel1->SuspendLayout();
				this->tabControl1->SuspendLayout();
				this->tabPage1->SuspendLayout();
				this->tabPage2->SuspendLayout();
				this->contextMenuStripLayer->SuspendLayout();
				this->contextMenuStripData->SuspendLayout();
				this->SuspendLayout();
				// 
				// panel2
				// 
				this->panel2->Controls->Add(this->button1);
				this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
				this->panel2->Location = System::Drawing::Point(0, 403);
				this->panel2->Name = L"panel2";
				this->panel2->Size = System::Drawing::Size(485, 46);
				this->panel2->TabIndex = 2;
				// 
				// button1
				// 
				this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->button1->Location = System::Drawing::Point(374, 11);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(99, 23);
				this->button1->TabIndex = 0;
				this->button1->Text = L"Ok";
				this->button1->UseVisualStyleBackColor = true;
				// 
				// panel1
				// 
				this->panel1->Controls->Add(this->tabControl1);
				this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->panel1->Location = System::Drawing::Point(0, 0);
				this->panel1->Margin = System::Windows::Forms::Padding(10);
				this->panel1->Name = L"panel1";
				this->panel1->Padding = System::Windows::Forms::Padding(5);
				this->panel1->Size = System::Drawing::Size(485, 403);
				this->panel1->TabIndex = 3;
				// 
				// tabControl1
				// 
				this->tabControl1->Controls->Add(this->tabPage1);
				this->tabControl1->Controls->Add(this->tabPage2);
				this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tabControl1->Location = System::Drawing::Point(5, 5);
				this->tabControl1->Margin = System::Windows::Forms::Padding(5);
				this->tabControl1->Name = L"tabControl1";
				this->tabControl1->SelectedIndex = 0;
				this->tabControl1->Size = System::Drawing::Size(475, 393);
				this->tabControl1->TabIndex = 0;
				// 
				// tabPage1
				// 
				this->tabPage1->Controls->Add(this->listViewData);
				this->tabPage1->Location = System::Drawing::Point(4, 22);
				this->tabPage1->Name = L"tabPage1";
				this->tabPage1->Padding = System::Windows::Forms::Padding(7);
				this->tabPage1->Size = System::Drawing::Size(467, 367);
				this->tabPage1->TabIndex = 0;
				this->tabPage1->Text = L"Serie danych";
				this->tabPage1->UseVisualStyleBackColor = true;
				// 
				// listViewData
				// 
				this->listViewData->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnHeader5, 
					this->columnHeader6, this->columnHeader7, this->columnHeader8});
				this->listViewData->ContextMenuStrip = this->contextMenuStripData;
				this->listViewData->Dock = System::Windows::Forms::DockStyle::Fill;
				this->listViewData->FullRowSelect = true;
				this->listViewData->GridLines = true;
				this->listViewData->Location = System::Drawing::Point(7, 7);
				this->listViewData->MultiSelect = false;
				this->listViewData->Name = L"listViewData";
				this->listViewData->Size = System::Drawing::Size(453, 353);
				this->listViewData->TabIndex = 0;
				this->listViewData->UseCompatibleStateImageBehavior = false;
				this->listViewData->View = System::Windows::Forms::View::Details;
				this->listViewData->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &ProjectMgt::listViewData_DrawItem);
				// 
				// columnHeader5
				// 
				this->columnHeader5->Text = L"Nazwa";
				this->columnHeader5->Width = 150;
				// 
				// columnHeader6
				// 
				this->columnHeader6->Text = L"Rozmiar";
				this->columnHeader6->Width = 100;
				// 
				// columnHeader7
				// 
				this->columnHeader7->Text = L"Typ";
				this->columnHeader7->Width = 90;
				// 
				// columnHeader8
				// 
				this->columnHeader8->Text = L"Status";
				this->columnHeader8->Width = 80;
				// 
				// tabPage2
				// 
				this->tabPage2->Controls->Add(this->listViewLayers);
				this->tabPage2->Location = System::Drawing::Point(4, 22);
				this->tabPage2->Name = L"tabPage2";
				this->tabPage2->Padding = System::Windows::Forms::Padding(7);
				this->tabPage2->Size = System::Drawing::Size(467, 367);
				this->tabPage2->TabIndex = 1;
				this->tabPage2->Text = L"Warstwy";
				this->tabPage2->UseVisualStyleBackColor = true;
				// 
				// listViewLayers
				// 
				this->listViewLayers->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnHeader1, 
					this->columnHeader4, this->columnHeader3, this->columnHeader2});
				this->listViewLayers->ContextMenuStrip = this->contextMenuStripLayer;
				this->listViewLayers->Dock = System::Windows::Forms::DockStyle::Fill;
				this->listViewLayers->FullRowSelect = true;
				this->listViewLayers->GridLines = true;
				this->listViewLayers->Location = System::Drawing::Point(7, 7);
				this->listViewLayers->MultiSelect = false;
				this->listViewLayers->Name = L"listViewLayers";
				this->listViewLayers->Size = System::Drawing::Size(453, 353);
				this->listViewLayers->Sorting = System::Windows::Forms::SortOrder::Ascending;
				this->listViewLayers->TabIndex = 0;
				this->listViewLayers->UseCompatibleStateImageBehavior = false;
				this->listViewLayers->View = System::Windows::Forms::View::Details;
				// 
				// columnHeader1
				// 
				this->columnHeader1->Text = L"Nazwa";
				this->columnHeader1->Width = 150;
				// 
				// columnHeader4
				// 
				this->columnHeader4->Text = L"ród³o danych";
				this->columnHeader4->Width = 150;
				// 
				// columnHeader3
				// 
				this->columnHeader3->Text = L"Typ";
				this->columnHeader3->Width = 40;
				// 
				// columnHeader2
				// 
				this->columnHeader2->Text = L"Klasa";
				this->columnHeader2->Width = 80;
				// 
				// contextMenuStripLayer
				// 
				this->contextMenuStripLayer->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->zmieñNazwêToolStripMenuItem, 
					this->zmieñKolorToolStripMenuItem, this->ustawieniaWarstwyToolStripMenuItem, this->toolStripMenuItem1, this->usuñToolStripMenuItem});
				this->contextMenuStripLayer->Name = L"contextMenuStripLayer";
				this->contextMenuStripLayer->Size = System::Drawing::Size(178, 98);
				// 
				// zmieñNazwêToolStripMenuItem
				// 
				this->zmieñNazwêToolStripMenuItem->Name = L"zmieñNazwêToolStripMenuItem";
				this->zmieñNazwêToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->zmieñNazwêToolStripMenuItem->Text = L"Zmieñ nazwê";
				this->zmieñNazwêToolStripMenuItem->Click += gcnew System::EventHandler(this, &ProjectMgt::zmieñNazwêToolStripMenuItem_Click);
				// 
				// zmieñKolorToolStripMenuItem
				// 
				this->zmieñKolorToolStripMenuItem->Name = L"zmieñKolorToolStripMenuItem";
				this->zmieñKolorToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->zmieñKolorToolStripMenuItem->Text = L"Zmieñ kolor";
				this->zmieñKolorToolStripMenuItem->Click += gcnew System::EventHandler(this, &ProjectMgt::zmieñKolorToolStripMenuItem_Click);
				// 
				// ustawieniaWarstwyToolStripMenuItem
				// 
				this->ustawieniaWarstwyToolStripMenuItem->Name = L"ustawieniaWarstwyToolStripMenuItem";
				this->ustawieniaWarstwyToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->ustawieniaWarstwyToolStripMenuItem->Text = L"Ustawienia warstwy";
				this->ustawieniaWarstwyToolStripMenuItem->Visible = false;
				this->ustawieniaWarstwyToolStripMenuItem->Click += gcnew System::EventHandler(this, &ProjectMgt::ustawieniaWarstwyToolStripMenuItem_Click);
				// 
				// toolStripMenuItem1
				// 
				this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
				this->toolStripMenuItem1->Size = System::Drawing::Size(174, 6);
				// 
				// usuñToolStripMenuItem
				// 
				this->usuñToolStripMenuItem->Name = L"usuñToolStripMenuItem";
				this->usuñToolStripMenuItem->Size = System::Drawing::Size(177, 22);
				this->usuñToolStripMenuItem->Text = L"Usuñ";
				this->usuñToolStripMenuItem->Click += gcnew System::EventHandler(this, &ProjectMgt::usuñToolStripMenuItem_Click);
				// 
				// contextMenuStripData
				// 
				this->contextMenuStripData->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->zmieñNazwêToolStripMenuItem1, 
					this->toolStripMenuItem2, this->usuñToolStripMenuItem1});
				this->contextMenuStripData->Name = L"contextMenuStripData";
				this->contextMenuStripData->Size = System::Drawing::Size(145, 54);
				// 
				// zmieñNazwêToolStripMenuItem1
				// 
				this->zmieñNazwêToolStripMenuItem1->Name = L"zmieñNazwêToolStripMenuItem1";
				this->zmieñNazwêToolStripMenuItem1->Size = System::Drawing::Size(144, 22);
				this->zmieñNazwêToolStripMenuItem1->Text = L"Zmieñ nazwê";
				this->zmieñNazwêToolStripMenuItem1->Click += gcnew System::EventHandler(this, &ProjectMgt::zmieñNazwêToolStripMenuItem1_Click);
				// 
				// toolStripMenuItem2
				// 
				this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
				this->toolStripMenuItem2->Size = System::Drawing::Size(141, 6);
				// 
				// usuñToolStripMenuItem1
				// 
				this->usuñToolStripMenuItem1->Name = L"usuñToolStripMenuItem1";
				this->usuñToolStripMenuItem1->Size = System::Drawing::Size(144, 22);
				this->usuñToolStripMenuItem1->Text = L"Usuñ";
				this->usuñToolStripMenuItem1->Click += gcnew System::EventHandler(this, &ProjectMgt::usuñToolStripMenuItem1_Click);
				// 
				// ProjectMgt
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(485, 449);
				this->Controls->Add(this->panel1);
				this->Controls->Add(this->panel2);
				this->Name = L"ProjectMgt";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				this->Text = L"Menad¿er projektu";
				this->Load += gcnew System::EventHandler(this, &ProjectMgt::ProjectMgt_Load);
				this->panel2->ResumeLayout(false);
				this->panel1->ResumeLayout(false);
				this->tabControl1->ResumeLayout(false);
				this->tabPage1->ResumeLayout(false);
				this->tabPage2->ResumeLayout(false);
				this->contextMenuStripLayer->ResumeLayout(false);
				this->contextMenuStripData->ResumeLayout(false);
				this->ResumeLayout(false);

			}
#pragma endregion

		private: System::Void ProjectMgt_Load(System::Object^  sender, System::EventArgs^  e) {
					 UpdateLayerList();
					 UpdateDataList();
				 }

	// Layers
		private: typedef VisApp::Renderer::LayerInterface LayerInterface;
		private: ref class LayerItem {
		public:
			typedef VisApp::Renderer::SharedLayerInterface SharedLayerInterface;
			SharedLayerInterface &Instance() { return *m_shlayer; }
			ListViewItem^ Item;
			LayerItem(ListView ^l, SharedLayerInterface &layer) {
				m_shlayer = new SharedLayerInterface(layer);
				Item = l->Items->Add(Helpers::ToString(layer->GetName()));
				Item->Tag = this;
				for(int i = 0; i < 5; ++i) Item->SubItems->Add("?");
				UpdateItem();
			}
			~LayerItem() { delete m_shlayer; }
			void UpdateItem() {
				Item->SubItems[0]->Text = Helpers::ToString(Instance()->GetName());
				String ^srcs = nullptr;
				for(auto &it: Instance()->GetDataSources()) {
					if(srcs) srcs +="; ";
					else srcs = "";
					srcs += Helpers::StringDataPointer2String(it);
				}
				Item->SubItems[1]->Text = srcs;
				String ^type = "?";
				switch (Instance()->GetLayerType()) {
					case VisApp::Renderer::LayerType::d2:
						type = "2d";
						break;
					case VisApp::Renderer::LayerType::d3:
						type = "3d";
						break;
				}
				Item->SubItems[2]->Text = type;
				Item->SubItems[3]->Text = Helpers::ToString(Instance()->GetLayerClassName());
			}
			void Remove() {
				Item->Tag = nullptr;
				Item->Remove();
				Item = nullptr;
			}
		private:
			SharedLayerInterface *m_shlayer;
		};
		private: LayerItem^ SelectedLayer() { 
					 if(listViewLayers->SelectedItems->Count < 1) return nullptr;
					 LayerItem ^li = dynamic_cast<LayerItem^>(listViewLayers->SelectedItems[0]->Tag);
					 if(!li) return nullptr;
					 return li;
				 }
		private: void UpdateLayerList() {
						listViewLayers->BeginUpdate();
						listViewLayers->Items->Clear();
						auto store = Project()->GetDataStore();
						for(unsigned i = 0, j = store->GetLayerCount(); i < j; ++i) {
							auto layer = store->GetLayer(i);
							if(!layer) break;
							LayerItem ^li = gcnew LayerItem(listViewLayers, layer);
						}
	//	 treeViewLayers->TreeViewNodeSorter = gcnew LayerTreeNodeSorter();
	//	 treeViewLayers->Sort();
						listViewLayers->EndUpdate();
					}
		private: System::Void zmieñNazwêToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 LayerItem ^li = SelectedLayer();
					 if(!li) return;
					 VisApp::gui::Manip::Layer::EditName(this, li->Instance().get());
					 li->UpdateItem();
				 }
		private: System::Void zmieñKolorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 LayerItem ^li = SelectedLayer();
					 if(!li) return;
					 VisApp::gui::Manip::Layer::EditColor(this, li->Instance().get());
				 }
		private: System::Void ustawieniaWarstwyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 LayerItem ^li = SelectedLayer();
					 if(!li) return;

				 }
		private: System::Void usuñToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 LayerItem ^li = SelectedLayer();
					 if(!li) return;
					 if(!AskForPermission()) return;
					 auto store = Project()->GetDataStore();
					 store->DeleteResource(li->Instance().get());
					 li->Remove();
					 delete li;
				 }

 // data

		private: ref class DataItem {
			ListView ^OwnerView;
		public:
			typedef VisApp::Interface::iDataChannel iDataChannel;
			typedef VisApp::Interface::iDataSeries iDataSeries;
			ListViewItem ^Item, ^DummyItem;
			iDataChannel *channel;
			iDataSeries *series;
			DataItem ^Owner;
			Generic::LinkedList<DataItem^> Channels;

			DataItem(DataItem ^owner, ListView ^l, iDataChannel *ch) {
				DummyItem = nullptr;
				Owner = owner;
				OwnerView = l;
				series = 0;
				channel = ch;
				Item = OwnerView->Items->Add(Helpers::ToString(ch->GetName()));
				for(int i = 0; i < 5; ++i) Item->SubItems->Add(" ");
				Item->Tag = this;
				
				UpdateItem();
			}

			DataItem(ListView ^l, iDataSeries *s) {
				Owner = nullptr;
				OwnerView = l;
				series = s;
				channel = 0;
				Item = OwnerView->Items->Add(Helpers::ToString(s->GetName()));
				for(int i = 0; i < 5; ++i) Item->SubItems->Add(" ");
				Item->Tag = this;

				for(int i = 0, j = s->GetChannelCount(); i < j; ++i) {
					auto ch = s->GetChannel(i);
					Channels.AddLast(gcnew DataItem(this, l, ch));
				}
				DummyItem = OwnerView->Items->Add("");
				Item->Font = gcnew System::Drawing::Font(Item->Font, System::Drawing::FontStyle::Bold);
				UpdateItem();
			}

			void Remove() {
				if(DummyItem) {
					DummyItem->Remove();
					DummyItem = nullptr;
				}
				for each(DataItem ^i in Channels) {
					i->Remove();
					delete i;
				}
				Item->Tag = nullptr;
				Item->Remove();
				Item = nullptr;

				if(series) {
					auto store = series->GetProject()->GetDataStore();
					store->DeleteResource(series);
				} else
				if(channel) {
					auto store = channel->GetSeries()->GetProject()->GetDataStore();
					store->DeleteResource(channel);
				} 
			}

			void UpdateItem() {
				if(Owner) Owner->UpdateItem();
				else UpdateSeriesItem();
			}

			void ChangeName(Form ^form) {
				if(series) {
					VisApp::gui::Manip::Series::EditName(form, series);
					UpdateSeriesItem();
				} else
				if(channel) {
					VisApp::gui::Manip::Channel::EditName(form, channel);
					UpdateChannelItem();
				}
			}
		private:
			void UpdateSeriesItem() {
				String ^hdr;
				switch (series->GetStatus()) {
				case VisApp::Interface::iDataSeries::eSeriesStatus::Broken:
					hdr = L"B³êdny";
					break;
				case VisApp::Interface::iDataSeries::eSeriesStatus::Importing:
					hdr = L"Importujê...";
					break;
				case VisApp::Interface::iDataSeries::eSeriesStatus::New:
					hdr = L"Nowy";
					break;
				case VisApp::Interface::iDataSeries::eSeriesStatus::Ok:
				case VisApp::Interface::iDataSeries::eSeriesStatus::Locked:
				default:
					hdr = L"Gotowy";
				}
				Item->SubItems[0]->Text = Helpers::ToString(series->GetName());
				VisApp::Math::uvec3 ds;
				series->GetSize(ds);
				if(ds[0] == 0 || ds[1] == 0 || ds[2] == 0) Item->SubItems[1]->Text = "?";
				else Item->SubItems[1]->Text = String::Format("{0}x{1}x{2}", ds[0], ds[1], ds[2]);
				Item->SubItems[3]->Text = hdr;

				for each(DataItem ^i in Channels) {
					i->UpdateChannelItem();
				}
			}
			void UpdateChannelItem() {
				Item->SubItems[0]->Text = Helpers::ToString(channel->GetName());
				Item->SubItems[2]->Text = Helpers::ToString(channel->GetType().ToString());
			}
		};

		private: DataItem^ SelectedData() { 
					 if(listViewData->SelectedItems->Count < 1) return nullptr;
					 DataItem ^di = dynamic_cast<DataItem^>(listViewData->SelectedItems[0]->Tag);
					 if(!di) return nullptr;
					 return di;
				 }

		private: System::Void listViewData_DrawItem(System::Object^  sender, System::Windows::Forms::DrawListViewItemEventArgs^  e) {
					 ListViewItem ^item = e->Item;
					 DataItem ^di = (DataItem^)item->Tag;
					 e->DrawDefault = true;
					 if(di->series) {
					 }
				 }
		private: System::Void zmieñNazwêToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
					 DataItem ^di = SelectedData();
					 if(!di) return;
					 di->ChangeName(this);
				 }
		private: System::Void usuñToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
					 DataItem ^di = SelectedData();
					 if(!di) return;
					 if(!AskForPermission()) return;
					 di->Remove();
				 }
		private: void UpdateDataList() {
						listViewData->BeginUpdate();
						listViewData->Items->Clear();
						listViewData->Groups->Clear();
						auto store = Project()->GetDataStore();
						for(unsigned i = 0, j = store->GetSetCount(); i < j; ++i) {
							auto data = store->GetDataSet(i);
							if(!data) break;
							DataItem ^di = gcnew DataItem(listViewData, data);
						}
						listViewData->EndUpdate();
				 }

		// Miszung

};

	}
}