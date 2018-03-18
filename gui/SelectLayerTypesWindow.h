/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/SelectLayerTypesWindow.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include <msclr\marshal_cppstd.h>

namespace VisApp {
namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::Collections;

	using Collections::Generic::Dictionary;
	using Collections::Generic::List;
	using Collections::Generic::KeyValuePair;
	using msclr::interop::marshal_as;

	/// <summary>
	/// Summary for SelectLayerTypesWindow
	/// </summary>
	public ref class SelectLayerTypesWindow : public System::Windows::Forms::Form
	{
	public:
		SelectLayerTypesWindow(System::Windows::Forms::Form^ OwnerWindow) {
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
			Owner = OwnerWindow;
//			m_DataChannels = gcnew Dictionary<unsigned, DataChannelList^>();
			m_DisablePropagation = false;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectLayerTypesWindow() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TreeView^  treeViewLayers;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
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
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->treeViewLayers = (gcnew System::Windows::Forms::TreeView());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Location = System::Drawing::Point(0, 305);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(311, 35);
			this->panel1->TabIndex = 9;
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(143, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Anuluj";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(224, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->Controls->Add(this->groupBox2);
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(311, 299);
			this->panel2->TabIndex = 10;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->treeViewLayers);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(0, 0);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(311, 299);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			// 
			// treeViewLayers
			// 
			this->treeViewLayers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeViewLayers->CheckBoxes = true;
			this->treeViewLayers->Location = System::Drawing::Point(8, 20);
			this->treeViewLayers->Name = L"treeViewLayers";
			this->treeViewLayers->Size = System::Drawing::Size(295, 271);
			this->treeViewLayers->TabIndex = 0;
			this->treeViewLayers->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &SelectLayerTypesWindow::treeViewD2LayerTypes_AfterCheck);
			// 
			// SelectLayerTypesWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(311, 341);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"SelectLayerTypesWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Wybierz warstwy";
			this->Load += gcnew System::EventHandler(this, &SelectLayerTypesWindow::SelectLayerTypesWindow_Load);
			this->Shown += gcnew System::EventHandler(this, &SelectLayerTypesWindow::SelectLayerTypesWindow_Shown);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
		// -------------- OwnTypes --------------
	public: ref struct ProcessDataPointer {
				String ^Project, ^Series, ^Channel;

				VisApp::Plugins::SharedProcessDescriptor& Descriptor() { return *m_Descriptor; }

				std::wstring GetProject() { return Helpers::ToStdWStr(Project); }
				std::wstring GetSeries() { return Helpers::ToStdWStr(Series); }
				std::wstring GetChannel() { return Helpers::ToStdWStr(Channel); }

				ProcessDataPointer() { m_Descriptor = new VisApp::Plugins::SharedProcessDescriptor(); }
				~ProcessDataPointer() { delete m_Descriptor; }

	private:
		VisApp::Plugins::SharedProcessDescriptor *m_Descriptor;
			};
			// -------------- MEMBERS --------------
	private:
		// -------------- PRIVATE FUN --------------	
#if 0
	private: void ProcessLayerModeXML(XmlNode^ ModeNode, TreeNodeCollection^ Outtv, LayerDescriptor::LayerMode ViewMode) {
				 /*	XmlNodeList ^varlist = ModeNode->SelectNodes("Variable");
				 String^ ModeName = ModeNode->Attributes["Value"]->Value;
				 String^ ModeCaption = ModeNode->Attributes["Caption"]->Value;
				 auto ModeTreeNode = Outtv->Add(ModeCaption);

				 for(int vari = 0, varj = varlist->Count; vari < varj; ++vari) {
				 XmlNode ^VarNode = varlist[vari];

				 LayerDescriptor^ ld = gcnew LayerDescriptor();
				 ld->Mode = ViewMode;
				 ld->ModeName = ModeName;
				 ld->ModeCaption = ModeCaption;

				 String^ TypeName = VarNode->Attributes["Type"]->Value;
				 ld->ProcessorName = VarNode->Attributes["Processor"]->Value;
				 std::wstring wsTypeNode = marshal_as<std::wstring>(TypeName);
				 ld->VariableType = Core::Shared::Conv::ColumnTypes::FromString(wsTypeNode.c_str()); 

				 DataChannelList^ chl;
				 if(!m_DataChannels->TryGetValue(ld->VariableType, chl)) continue;

				 for each (DataChannelList::ListValuePair^ sit in chl->ChannelList) {
				 auto SeriesNode = ModeTreeNode->Nodes->Add(sit->Key);
				 SeriesNode->Tag = ld;
				 for each (DataChannelPointer^ % chit in sit->Value) {
				 auto ChannelNode = SeriesNode->Nodes->Add(chit->SeriesName);
				 LayerTypesTreeNodeDescriptor^ lnd = gcnew LayerTypesTreeNodeDescriptor();
				 lnd->Data = chit;
				 lnd->Layer = ld;
				 ChannelNode->Tag = lnd;
				 }
				 }
				 }*/
			 }
	private: void ProcessLayerTypes(XmlNode^ node, TreeView^ Outtv, LayerDescriptor::LayerMode ViewMode) {
				 Outtv->Nodes->Clear();

				 XmlNodeList ^GroupNodes = node->SelectNodes("Group");
				 for(int i = 0, j = GroupNodes->Count; i < j; ++i) {
					 auto Node = Outtv->Nodes->Add(GroupNodes[i]->Attributes["Caption"]->Value);
					 XmlNodeList ^xnl = GroupNodes[i]->SelectNodes("Mode");

					 for(int modei = 0, modej = xnl->Count; modei < modej; ++modei) {
						 ProcessLayerModeXML(xnl[modei], Node->Nodes, ViewMode);
					 }
				 }

				 XmlNodeList ^xnl = node->SelectNodes("Mode");
				 for(int modei = 0, modej = xnl->Count; modei < modej; ++modei) {
					 ProcessLayerModeXML(xnl[modei], Outtv->Nodes, ViewMode);
				 }
			 }
#endif
	private: bool m_DisablePropagation;
	private: void PropagateDownNodeCheck(TreeNode^ node, bool checked) {
				 if(!node) return;
				 for each (TreeNode ^i in node->Nodes) {
					 i->Checked = checked;
					 PropagateDownNodeCheck(i, checked);
				 }
			 }
	private: void PropagateUpNodeCheck(TreeNode^ node, bool checked) {
				 if(!node) return;
				 node = node->Parent;
				 if(!node) return;
				 for each (TreeNode ^i in node->Nodes) {
					 if(i->Checked != checked) return;
				 }
				 node->Checked = checked;
				 PropagateUpNodeCheck(node, checked);
			 }
	private: void GetTaggedTreeViewNodes(TreeNodeCollection^ Nodes, List<TreeNode^> ^out) {
				 for each(TreeNode ^i in Nodes) {
					 if(i->Tag != nullptr)
						 out->Add(i);
					 if(i->Nodes->Count > 0)
						 GetTaggedTreeViewNodes(i->Nodes, out);
				 }
			 }
	private: void SetProjectToPluginView() {
				 auto projMgt = VisApp::Interface::iProjectMgt::GetInstance();

				 VisApp::Interface::WeakProjectList projList;
				 projMgt->GetOpenedProjects(projList);

				 VisApp::Plugins::WeakProcessDescriptorList pluginWeakList;
				 VisApp::Plugins::PluginManager::Instance()->GetProcessPlugins(pluginWeakList);

				 std::list<VisApp::Plugins::SharedProcessDescriptor> pluginList;
				 for(auto &weakPlugin: pluginWeakList)
					 pluginList.push_back(weakPlugin.lock());

				 auto Items = treeViewLayers->Nodes;
				 this->treeViewLayers->BeginUpdate();
				 this->treeViewLayers->Nodes->Clear();
				 for(auto &weakProject: projList) {
					 auto project = weakProject.lock();
					 String ^projName = Helpers::ToString(project->GetName());

					 TreeNode ^projNode = nullptr;
					 TreeNodeCollection ^projNodeCollection = nullptr;
					 if(projList.size() == 1) {
						 projNodeCollection = Items;
					 } else {
						 projNode = Items->Add("[Projekt] " + projName);
						 projNodeCollection = projNode->Nodes;
					 }

					 auto datastore = project->GetDataStore();
					 //interate through data series
					 for(index_t seriesNo = 0, seriesMax = datastore->GetSetCount(); seriesNo < seriesMax; ++seriesNo) {
						 auto series = datastore->GetDataSet(seriesNo);
						 String ^seriesName = Helpers::ToString(series->GetName());
						 TreeNode ^seriesNode = projNodeCollection->Add("[Seria danych] " + seriesName);

						 //iterate trough series data channels
						 for(index_t channelNo = 0, channelMax = series->GetChannelCount(); channelNo < channelMax; ++channelNo) {
							 auto channel = series->GetChannel(channelNo);
							 String ^channelName = Helpers::ToString(channel->GetName());
							 TreeNode ^channelNode = seriesNode->Nodes->Add("[Dane] " + channelName);

							 for(auto &plugin: pluginList) {
								 VisApp::Interface::DataPointer datap;

								 datap.Project = project.get();
								 datap.Series = series;
								 datap.Channel = channel;

								 if(!plugin->TestDataSource(&datap)) continue;
								 
								 auto ptrData = gcnew ProcessDataPointer();
								 ptrData->Channel = channelName;
								 ptrData->Series = seriesName;
								 ptrData->Project = projName;
								 ptrData->Descriptor() = plugin;

								 TreeNode ^pluginNode = channelNode->Nodes->Add(Helpers::ToString(plugin->GetName()));
								 pluginNode->Tag = ptrData;
							 }
						 }
					 }
				 }
				 this->treeViewLayers->EndUpdate();
			 }
			 // -------------- PUBLIC FUN ---------------
	public: void Reset()  {
				SetProjectToPluginView();
			}
	public: List<ProcessDataPointer^>^ GetSelectedLayers() {
				List<TreeNode^> ^lst = gcnew List<TreeNode^>();
				GetTaggedTreeViewNodes(treeViewLayers->Nodes, lst);
				List<ProcessDataPointer^> ^output = gcnew List<ProcessDataPointer^>();
				for each (TreeNode ^i in lst) {
					if(i->Tag == nullptr || !i->Checked) continue;
					ProcessDataPointer ^pdp = dynamic_cast<ProcessDataPointer^>(i->Tag);
					if(pdp == nullptr) continue;

					output->Add(pdp);
				}
				return output;
			}
			// ---------------- EVENTS ----------------
	private: System::Void treeViewD2LayerTypes_AfterCheck(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
				 if(m_DisablePropagation) return;
				 m_DisablePropagation = true;
				 PropagateDownNodeCheck(e->Node, e->Node->Checked);
				 PropagateUpNodeCheck(e->Node, e->Node->Checked);
				 m_DisablePropagation = false;
			 }
	private: System::Void SelectLayerTypesWindow_Load(System::Object^  sender, System::EventArgs^  e) {
				// treeViewLayers->Nodes->Clear();
			 }
	private: System::Void SelectLayerTypesWindow_Shown(System::Object^  sender, System::EventArgs^  e) {
				 for each (TreeNode^ tn in treeViewLayers->Nodes) {
					 PropagateDownNodeCheck(tn, false);
				 }
			 }
			 // ---------------- SHITTY STUFF ----------------
	};
}
}
