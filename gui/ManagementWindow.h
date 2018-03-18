/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ManagementWindow.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "CoreMgt.h"
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
	/// Summary for ManagementWindow
	/// </summary>
	public ref class ManagementWindow : public System::Windows::Forms::Form
	{
	public:
		static void Show() {
			if(_Instance == nullptr)
				gcnew ManagementWindow();
			_Instance->Visible = true;
			_Instance->BringToFront();
		}
		static void Hide() {
			_Instance->Visible = false;
			delete _Instance;
		}
	protected:
		static ManagementWindow^ _Instance = nullptr;
		ManagementWindow(void) 	{
			_Instance = this;
	//		Owner = MainForm::Instance();
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
		}
		~ManagementWindow() {
			_Instance = nullptr;
			if (components) {
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  ProcessesTabPage;
	private: System::Windows::Forms::TabPage^  PluginsTabPage;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::ListView^  listViewProcess;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::ColumnHeader^  columnHeader8;
	private: System::ComponentModel::IContainer^  components;
	protected: 

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
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"Aktywne", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup2 = (gcnew System::Windows::Forms::ListViewGroup(L"Nieaktywne", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup3 = (gcnew System::Windows::Forms::ListViewGroup(L"Zakoñczone", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup4 = (gcnew System::Windows::Forms::ListViewGroup(L"W tle", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup5 = (gcnew System::Windows::Forms::ListViewGroup(L"plugin1.dll", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup6 = (gcnew System::Windows::Forms::ListViewGroup(L"Plugin2.dll", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(3) {L"Test import", 
				L"1.0", L"opis"}, -1));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->ProcessesTabPage = (gcnew System::Windows::Forms::TabPage());
			this->listViewProcess = (gcnew System::Windows::Forms::ListView());
			this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
			this->PluginsTabPage = (gcnew System::Windows::Forms::TabPage());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabControl1->SuspendLayout();
			this->ProcessesTabPage->SuspendLayout();
			this->PluginsTabPage->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &ManagementWindow::timer1_Tick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->ProcessesTabPage);
			this->tabControl1->Controls->Add(this->PluginsTabPage);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(7, 7);
			this->tabControl1->Margin = System::Windows::Forms::Padding(5);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(533, 459);
			this->tabControl1->TabIndex = 2;
			// 
			// ProcessesTabPage
			// 
			this->ProcessesTabPage->Controls->Add(this->listViewProcess);
			this->ProcessesTabPage->Location = System::Drawing::Point(4, 22);
			this->ProcessesTabPage->Name = L"ProcessesTabPage";
			this->ProcessesTabPage->Padding = System::Windows::Forms::Padding(7);
			this->ProcessesTabPage->Size = System::Drawing::Size(525, 433);
			this->ProcessesTabPage->TabIndex = 1;
			this->ProcessesTabPage->Text = L"Procesy";
			this->ProcessesTabPage->UseVisualStyleBackColor = true;
			// 
			// listViewProcess
			// 
			this->listViewProcess->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->columnHeader6, 
				this->columnHeader3, this->columnHeader5, this->columnHeader7, this->columnHeader8});
			this->listViewProcess->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewProcess->FullRowSelect = true;
			this->listViewProcess->GridLines = true;
			listViewGroup1->Header = L"Aktywne";
			listViewGroup1->Name = L"listViewGroupProcessActive";
			listViewGroup2->Header = L"Nieaktywne";
			listViewGroup2->Name = L"listViewGroupProcessInactive";
			listViewGroup3->Header = L"Zakoñczone";
			listViewGroup3->Name = L"listViewGroupProcessFinished";
			listViewGroup4->Header = L"W tle";
			listViewGroup4->Name = L"listViewGroupProcessBackground";
			this->listViewProcess->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(4) {listViewGroup1, listViewGroup2, 
				listViewGroup3, listViewGroup4});
			this->listViewProcess->Location = System::Drawing::Point(7, 7);
			this->listViewProcess->Name = L"listViewProcess";
			this->listViewProcess->Size = System::Drawing::Size(511, 419);
			this->listViewProcess->TabIndex = 1;
			this->listViewProcess->UseCompatibleStateImageBehavior = false;
			this->listViewProcess->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader6
			// 
			this->columnHeader6->Text = L"ipid";
			this->columnHeader6->Width = 0;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Nazwa";
			this->columnHeader3->Width = 200;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Text = L"Status";
			this->columnHeader5->Width = 68;
			// 
			// columnHeader7
			// 
			this->columnHeader7->Text = L"Postêp";
			this->columnHeader7->Width = 47;
			// 
			// columnHeader8
			// 
			this->columnHeader8->Text = L"Zadanie";
			this->columnHeader8->Width = 150;
			// 
			// PluginsTabPage
			// 
			this->PluginsTabPage->Controls->Add(this->listView1);
			this->PluginsTabPage->Location = System::Drawing::Point(4, 22);
			this->PluginsTabPage->Name = L"PluginsTabPage";
			this->PluginsTabPage->Padding = System::Windows::Forms::Padding(7);
			this->PluginsTabPage->Size = System::Drawing::Size(525, 433);
			this->PluginsTabPage->TabIndex = 0;
			this->PluginsTabPage->Text = L"Wtyczki";
			this->PluginsTabPage->UseVisualStyleBackColor = true;
			// 
			// listView1
			// 
			this->listView1->AutoArrange = false;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader1, this->columnHeader2, 
				this->columnHeader4});
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->FullRowSelect = true;
			listViewGroup5->Header = L"plugin1.dll";
			listViewGroup5->Name = L"listViewGroup1";
			listViewGroup6->Header = L"Plugin2.dll";
			listViewGroup6->Name = L"listViewGroup2";
			this->listView1->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(2) {listViewGroup5, listViewGroup6});
			this->listView1->HideSelection = false;
			listViewItem1->Group = listViewGroup5;
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) {listViewItem1});
			this->listView1->Location = System::Drawing::Point(7, 7);
			this->listView1->Margin = System::Windows::Forms::Padding(10);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(511, 419);
			this->listView1->Sorting = System::Windows::Forms::SortOrder::Descending;
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Nazwa";
			this->columnHeader1->Width = 200;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Typ";
			this->columnHeader2->Width = 80;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Opis";
			this->columnHeader4->Width = 157;
			// 
			// ManagementWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(547, 473);
			this->Controls->Add(this->tabControl1);
			this->Name = L"ManagementWindow";
			this->Padding = System::Windows::Forms::Padding(7);
			this->Text = L"Status aplikacji";
			this->Load += gcnew System::EventHandler(this, &ManagementWindow::ManagementWindow_Load);
			this->Shown += gcnew System::EventHandler(this, &ManagementWindow::ManagementWindow_Shown);
			this->tabControl1->ResumeLayout(false);
			this->ProcessesTabPage->ResumeLayout(false);
			this->PluginsTabPage->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		//----------------------------------

	public: static String^ PluginTypeToString(VisApp::Plugins::PluginType Type) {
				switch (Type)
				{
				case VisApp::Plugins::PluginType::Import: return "Import";
				case VisApp::Plugins::PluginType::Process: return "Przetwarzanie";
				case VisApp::Plugins::PluginType::Layer: return "Warstwa";
				default: return "Nizenany";
				}
			};
	
	private: void RefreshProcesses() {
				 listViewProcess->Items->Clear();

				 auto instance = Worker::Mgt::Manager::Instance();
				 if(!instance) return; //silently ignore if worker instance isn't created.


				 Worker::Mgt::WeakWorkerList list;
				 instance->GetWorkerList(list);

				 for(auto &it: list) {
					 if(it.expired()) continue;
					 auto worker = it.lock();

					 auto progress = worker->GetProgress();

					 if(progress < 0) 
						 continue;

					 auto item = listViewProcess->Items->Add(" "); //ipid
					 const std::wstring &Name = worker->GetName();
					 item->SubItems->Add(Helpers::ToString(Name));
					 item->SubItems->Add(Helpers::WorkerStatusToString(worker->GetStatus()));
					
					 //auto progress = worker->GetProgress();
					 if(progress < 0) {
						 item->SubItems->Add("-");
						 item->Group = listViewProcess->Groups[3];
					 } else {
						 item->SubItems->Add(Convert::ToString(progress * 100.0f) + "%");

						 switch (worker->GetStatus()) {
						 case Worker::Mgt::WorkerStatus::Working:
							 item->Group = listViewProcess->Groups[0];
							 break;
						 case Worker::Mgt::WorkerStatus::Finished:
							 item->Group = listViewProcess->Groups[2];
							 break;
						 default:
							 item->Group = listViewProcess->Groups[1];
						 }
					 }
					 //	item->SubItems->Add(Convert::ToString(proc->GetPhase()) + "/" + Convert::ToString(proc->GetMaxPhase()));
					 //	item->SubItems->Add(::gui::Helpers::ToString(proc->GetPhaseName()));
				 }
			 }
	private: void RefreshPluginList() {
				ListView ^list = listView1;

				list->BeginUpdate();
				list->Groups->Clear();
				list->Items->Clear();

				auto pmgt = VisApp::Plugins::PluginManager::Instance();

				auto plugins = pmgt->GetPluginList();

				for(auto &plugin: plugins) {
					String ^Name = Helpers::ToString(plugin->GetName());
					String ^File = Path::GetFileName(Helpers::ToString(plugin->GetFileName()));
					auto version = plugin->GetVersion();
#if 0
					String ^Ver = String::Format("{0}.{1}.{2}  {4}build at {3} ", 
						version.Major, version.Minor, version.Release, Helpers::ToString(version.BuildDate),
						Helpers::ToString((version.IsDebugBuild ? "debug " : "")));
#else
					String ^Ver = Helpers::ToString(std::wstring((version.IsDebugBuild ? L"  DEBUG BUILD" : L"")));
#endif
					String ^GroupName = Name + " (" + File + ") " + Ver;
					ListViewGroup ^group = list->Groups->Add("key", GroupName);

					VisApp::Plugins::WeakDescriptorList descrList;
					plugin->GetDescriptorList(descrList);
					for(auto &weak_descr: descrList) {
						//TODO: handle expiored pointer
						auto descr = weak_descr.lock();

						ListViewItem ^itm = list->Items->Add(Helpers::ToString(descr->GetName()));
						itm->Group = group;
						itm->SubItems->Add(PluginTypeToString(descr->GetPluginType()));
						itm->SubItems->Add(Helpers::ToString(descr->GetDescription()));
					}
					if(descrList.empty()) {
						ListViewItem ^itm = list->Items->Add("Wtyczka nie udostêpnia ¿adnych funkcjonalnoœci");
						itm->Group = group;
					}
				}
				list->EndUpdate();
			}
			
		//---------------------------------

	private: System::Void ManagementWindow_Load(System::Object^  sender, System::EventArgs^  e) {
				 DEBUG_WINDOW_NAME
				 RefreshPluginList();
			 }
	private: System::Void ManagementWindow_Shown(System::Object^  sender, System::EventArgs^  e) {
				 timer1->Enabled = true;
				 RefreshPluginList();
				 RefreshProcesses();
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 int ti = tabControl1->SelectedIndex;
				 switch(ti) {
				 case 0:
					 RefreshProcesses();
					 return;
				 case 1: 
					 return;
				 }
			 }

		 //---------------------------------

	};
}
}
