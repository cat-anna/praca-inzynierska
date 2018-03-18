/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/MainForm.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include "CoreWaitForm.h"

#include "AddNewLayersWizard.h"
#include "ImportData.h"
#include "ManagementWindow.h"
#include "CreateProjectWizard.h"
#include "SettingsWindow.h"
#include "DataInspector.h"
#include "AboutWindow.h"

#include "ProjectMgt.h"

#include "GUISettings.h"

#include <msclr\marshal_cppstd.h>

#include "OGLContext.h"
#include "CoreMessages.h"

#include "CoreManip.h"

using namespace VisApp::gui;

namespace gui {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows;

	using System::Drawing::Point;
	using msclr::interop::marshal_as;

	using namespace VisApp::Interface;

	using VisApp::Renderer::LayerType;

	delegate void ActionHandler();
	enum MouseStatusFlags { MouseLeft = 0x1, MouseRight = 0x02, MouseMiddle = 0x4, };

	enum class StatusTipMessageClass {
		Normal, Warning, Error, Hint,
	};

	delegate void CoreMessageDispatcher(CoreMessageParameters^);

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		static MainForm ^Instance() {
			if(_Instance == nullptr) 
				_Instance = gcnew MainForm();
			return _Instance;
		}
	private: System::Windows::Forms::ToolStripMenuItem^  LayersManageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  LayersToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  MenuLayer;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem7;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton2;
	private: System::Windows::Forms::ToolStripMenuItem^  EnterD3MenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  EnterD2MenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  MoveUpTreeContexMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  MoveDownTreeContexMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  SaveProjectUpperMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem8;
	private: System::Windows::Forms::Timer^  RefreshStatusBarTimer;
	private: System::Windows::Forms::ToolStripMenuItem^  ShowManagementWindowMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem9;
	private: System::Windows::Forms::ToolStripMenuItem^  LayerSettingsLayerTreeViewContextMenu;
	private: System::Windows::Forms::Label^  ViewModeLabel;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripViewMode;
	private: System::Windows::Forms::ToolStripMenuItem^  OrthogonalViewMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  PerspectiveViewMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  renderingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  MakeScreenShotToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  SetLayerColorLayerTreeViewContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  SetLayerColorLayerMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ShowLayerInfoLayerTreeViewContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  ShowLayerInfoLayerMenuItem;
	private: System::Windows::Forms::Timer^  timerShowDataInspector;
	private: System::Windows::Forms::ToolStripMenuItem^  RenameLayerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem11;
	private: System::Windows::Forms::ToolStripMenuItem^  AboutToolStripMenuItem;
	private: System::Windows::Forms::Timer^  timerStatusBarNotifications;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripRenderer;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemResetLayerZoom;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem12;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItemRendererHideAll;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem10;
	private: System::Windows::Forms::ToolStripMenuItem^  RendererSettingsMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  zarzadzajProjektemToolStripMenuItem;

	private:
		static MainForm^ _Instance = nullptr;
		MainForm(void) {
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
			m_Project = new VisApp::Interface::SharedProject();
			SetMenuDispatchers();
			m_CurrentViewType = VisApp::Renderer::LayerType::Unknown;
			m_UsePerspective = true;
			m_WhenToShowDataInspector = 0;
			m_DataInspector = nullptr;
			m_CanRender = -1;
			StatusBarNotifications = gcnew Generic::Queue<StatusBarNotificationItem^>();
		}	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm() {
			delete m_Project;
			if (components) {
				delete components;
			}
		}
#if 1
		//---------------------------- DYNAMIC STUFF --------------------------------
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripLayerTreeNode;
	private: System::Windows::Forms::ToolStripMenuItem^  ToggleLayerVisibilityTreeViewMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem4;
	private: System::Windows::Forms::Panel^  panelRender;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelTips;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelMiddle;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelOperation;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabelPercentage;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::Panel^  panelMain;
	private: System::Windows::Forms::Panel^  panelBody;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::Panel^  panelLeft;
	private: System::Windows::Forms::Panel^  panelTop;
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  daneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  wczytajToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  importujToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  wyjscieToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TreeView^  treeViewLayers;
	private: System::Windows::Forms::ToolStripMenuItem^  nowaWarstwaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  RemoveLayerMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ToggleLayerVisiblityMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  MoveUpLayerMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  MoveDownLayerMenu;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  LayerSettingsLayerMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  ustawieniaToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;
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
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 System::Windows::Forms::TreeNode^  treeNode7 = (gcnew System::Windows::Forms::TreeNode(L"èrÛd≥o: Seria1"));
				 System::Windows::Forms::TreeNode^  treeNode8 = (gcnew System::Windows::Forms::TreeNode(L"Typ: izolinie"));
				 System::Windows::Forms::TreeNode^  treeNode9 = (gcnew System::Windows::Forms::TreeNode(L"Granica ziaren", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {treeNode7, 
					 treeNode8}));
				 System::Windows::Forms::TreeNode^  treeNode10 = (gcnew System::Windows::Forms::TreeNode(L"èrÛd≥o: Seria1"));
				 System::Windows::Forms::TreeNode^  treeNode11 = (gcnew System::Windows::Forms::TreeNode(L"Typ: ciπg≥y kolor"));
				 System::Windows::Forms::TreeNode^  treeNode12 = (gcnew System::Windows::Forms::TreeNode(L"ZawartoúÊ wÍgla", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {treeNode10, 
					 treeNode11}));
				 this->contextMenuStripLayerTreeNode = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->ToggleLayerVisibilityTreeViewMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->MoveUpTreeContexMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->MoveDownTreeContexMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->SetLayerColorLayerTreeViewContextMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->LayerSettingsLayerTreeViewContextMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ShowLayerInfoLayerTreeViewContextMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->MoveUpLayerMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->MoveDownLayerMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripStatusLabelTips = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabelMiddle = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabelOperation = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
				 this->toolStripStatusLabelPercentage = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->panelMain = (gcnew System::Windows::Forms::Panel());
				 this->panelBody = (gcnew System::Windows::Forms::Panel());
				 this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
				 this->panelLeft = (gcnew System::Windows::Forms::Panel());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->panel2 = (gcnew System::Windows::Forms::Panel());
				 this->treeViewLayers = (gcnew System::Windows::Forms::TreeView());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
				 this->MenuLayer = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->nowaWarstwaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->RemoveLayerMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->ToggleLayerVisiblityMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->SetLayerColorLayerMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->RenameLayerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->LayerSettingsLayerMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ShowLayerInfoLayerMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripDropDownButton2 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
				 this->EnterD3MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->EnterD2MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->panelRender = (gcnew System::Windows::Forms::Panel());
				 this->contextMenuStripRenderer = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->toolStripMenuItemResetLayerZoom = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripMenuItemRendererHideAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ViewModeLabel = (gcnew System::Windows::Forms::Label());
				 this->panelTop = (gcnew System::Windows::Forms::Panel());
				 this->LayersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
				 this->daneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->wczytajToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->SaveProjectUpperMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->importujToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->wyjscieToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->renderingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->MakeScreenShotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ustawieniaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ShowManagementWindowMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->zarzadzajProjektemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->RendererSettingsMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->AboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->LayersManageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->RefreshStatusBarTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->contextMenuStripViewMode = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->OrthogonalViewMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->PerspectiveViewMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->timerShowDataInspector = (gcnew System::Windows::Forms::Timer(this->components));
				 this->timerStatusBarNotifications = (gcnew System::Windows::Forms::Timer(this->components));
				 this->contextMenuStripLayerTreeNode->SuspendLayout();
				 this->statusStrip1->SuspendLayout();
				 this->panelMain->SuspendLayout();
				 this->panelBody->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
				 this->splitContainer1->Panel1->SuspendLayout();
				 this->splitContainer1->Panel2->SuspendLayout();
				 this->splitContainer1->SuspendLayout();
				 this->panelLeft->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 this->panel2->SuspendLayout();
				 this->panel1->SuspendLayout();
				 this->toolStrip1->SuspendLayout();
				 this->MenuLayer->SuspendLayout();
				 this->panelRender->SuspendLayout();
				 this->contextMenuStripRenderer->SuspendLayout();
				 this->menuStrip->SuspendLayout();
				 this->contextMenuStripViewMode->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // contextMenuStripLayerTreeNode
				 // 
				 this->contextMenuStripLayerTreeNode->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->ToggleLayerVisibilityTreeViewMenuItem, 
					 this->toolStripMenuItem4, this->MoveUpTreeContexMenu, this->MoveDownTreeContexMenu, this->toolStripMenuItem9, this->SetLayerColorLayerTreeViewContextMenu, 
					 this->LayerSettingsLayerTreeViewContextMenu, this->ShowLayerInfoLayerTreeViewContextMenu});
				 this->contextMenuStripLayerTreeNode->Name = L"contextMenuStrip1";
				 this->contextMenuStripLayerTreeNode->Size = System::Drawing::Size(191, 148);
				 this->contextMenuStripLayerTreeNode->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::TestLayerSelction_MenuOpening);
				 // 
				 // ToggleLayerVisibilityTreeViewMenuItem
				 // 
				 this->ToggleLayerVisibilityTreeViewMenuItem->Name = L"ToggleLayerVisibilityTreeViewMenuItem";
				 this->ToggleLayerVisibilityTreeViewMenuItem->Size = System::Drawing::Size(190, 22);
				 this->ToggleLayerVisibilityTreeViewMenuItem->Text = L"Renderuj";
				 this->ToggleLayerVisibilityTreeViewMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem4
				 // 
				 this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
				 this->toolStripMenuItem4->Size = System::Drawing::Size(187, 6);
				 // 
				 // MoveUpTreeContexMenu
				 // 
				 this->MoveUpTreeContexMenu->Name = L"MoveUpTreeContexMenu";
				 this->MoveUpTreeContexMenu->Size = System::Drawing::Size(190, 22);
				 this->MoveUpTreeContexMenu->Text = L"PrzesuÒ w gÛrÍ";
				 this->MoveUpTreeContexMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // MoveDownTreeContexMenu
				 // 
				 this->MoveDownTreeContexMenu->Name = L"MoveDownTreeContexMenu";
				 this->MoveDownTreeContexMenu->Size = System::Drawing::Size(190, 22);
				 this->MoveDownTreeContexMenu->Text = L"PrzesuÒ w dÛ≥";
				 this->MoveDownTreeContexMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem9
				 // 
				 this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
				 this->toolStripMenuItem9->Size = System::Drawing::Size(187, 6);
				 // 
				 // SetLayerColorLayerTreeViewContextMenu
				 // 
				 this->SetLayerColorLayerTreeViewContextMenu->Name = L"SetLayerColorLayerTreeViewContextMenu";
				 this->SetLayerColorLayerTreeViewContextMenu->Size = System::Drawing::Size(190, 22);
				 this->SetLayerColorLayerTreeViewContextMenu->Text = L"ZmieÒ kolor";
				 this->SetLayerColorLayerTreeViewContextMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // LayerSettingsLayerTreeViewContextMenu
				 // 
				 this->LayerSettingsLayerTreeViewContextMenu->Name = L"LayerSettingsLayerTreeViewContextMenu";
				 this->LayerSettingsLayerTreeViewContextMenu->Size = System::Drawing::Size(190, 22);
				 this->LayerSettingsLayerTreeViewContextMenu->Text = L"Ustawienia warstwy";
				 this->LayerSettingsLayerTreeViewContextMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // ShowLayerInfoLayerTreeViewContextMenu
				 // 
				 this->ShowLayerInfoLayerTreeViewContextMenu->Name = L"ShowLayerInfoLayerTreeViewContextMenu";
				 this->ShowLayerInfoLayerTreeViewContextMenu->Size = System::Drawing::Size(190, 22);
				 this->ShowLayerInfoLayerTreeViewContextMenu->Text = L"Informacje o warstwie";
				 this->ShowLayerInfoLayerTreeViewContextMenu->Visible = false;
				 // 
				 // MoveUpLayerMenu
				 // 
				 this->MoveUpLayerMenu->Name = L"MoveUpLayerMenu";
				 this->MoveUpLayerMenu->Size = System::Drawing::Size(190, 22);
				 this->MoveUpLayerMenu->Text = L"PrzesuÒ w gÛrÍ";
				 this->MoveUpLayerMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // MoveDownLayerMenu
				 // 
				 this->MoveDownLayerMenu->Name = L"MoveDownLayerMenu";
				 this->MoveDownLayerMenu->Size = System::Drawing::Size(190, 22);
				 this->MoveDownLayerMenu->Text = L"PrzesuÒ w dÛ≥";
				 this->MoveDownLayerMenu->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripStatusLabelTips
				 // 
				 this->toolStripStatusLabelTips->Name = L"toolStripStatusLabelTips";
				 this->toolStripStatusLabelTips->Size = System::Drawing::Size(420, 17);
				 this->toolStripStatusLabelTips->Spring = true;
				 this->toolStripStatusLabelTips->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // toolStripStatusLabelMiddle
				 // 
				 this->toolStripStatusLabelMiddle->AutoSize = false;
				 this->toolStripStatusLabelMiddle->Name = L"toolStripStatusLabelMiddle";
				 this->toolStripStatusLabelMiddle->Size = System::Drawing::Size(150, 17);
				 // 
				 // toolStripStatusLabelOperation
				 // 
				 this->toolStripStatusLabelOperation->AutoSize = false;
				 this->toolStripStatusLabelOperation->Name = L"toolStripStatusLabelOperation";
				 this->toolStripStatusLabelOperation->Size = System::Drawing::Size(150, 17);
				 this->toolStripStatusLabelOperation->Text = L"Nazwa operacji";
				 this->toolStripStatusLabelOperation->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // toolStripProgressBar
				 // 
				 this->toolStripProgressBar->AutoSize = false;
				 this->toolStripProgressBar->Name = L"toolStripProgressBar";
				 this->toolStripProgressBar->Size = System::Drawing::Size(148, 16);
				 this->toolStripProgressBar->Step = 1;
				 this->toolStripProgressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
				 this->toolStripProgressBar->Value = 100;
				 this->toolStripProgressBar->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 this->toolStripProgressBar->DoubleClick += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripStatusLabelPercentage
				 // 
				 this->toolStripStatusLabelPercentage->Name = L"toolStripStatusLabelPercentage";
				 this->toolStripStatusLabelPercentage->Size = System::Drawing::Size(35, 17);
				 this->toolStripStatusLabelPercentage->Text = L"100%";
				 this->toolStripStatusLabelPercentage->Visible = false;
				 // 
				 // toolStripSplitButton1
				 // 
				 this->toolStripSplitButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->toolStripSplitButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripSplitButton1.Image")));
				 this->toolStripSplitButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
				 this->toolStripSplitButton1->Size = System::Drawing::Size(32, 20);
				 this->toolStripSplitButton1->Text = L"toolStripSplitButton1";
				 this->toolStripSplitButton1->Visible = false;
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->toolStripStatusLabelTips, 
					 this->toolStripStatusLabelMiddle, this->toolStripStatusLabelOperation, this->toolStripProgressBar, this->toolStripStatusLabelPercentage, 
					 this->toolStripSplitButton1});
				 this->statusStrip1->Location = System::Drawing::Point(0, 462);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(885, 22);
				 this->statusStrip1->TabIndex = 3;
				 this->statusStrip1->Text = L"statusStrip";
				 // 
				 // panelMain
				 // 
				 this->panelMain->Controls->Add(this->panelBody);
				 this->panelMain->Controls->Add(this->panelTop);
				 this->panelMain->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panelMain->Location = System::Drawing::Point(0, 24);
				 this->panelMain->Name = L"panelMain";
				 this->panelMain->Size = System::Drawing::Size(885, 438);
				 this->panelMain->TabIndex = 4;
				 // 
				 // panelBody
				 // 
				 this->panelBody->Controls->Add(this->splitContainer1);
				 this->panelBody->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panelBody->Location = System::Drawing::Point(0, 10);
				 this->panelBody->Name = L"panelBody";
				 this->panelBody->Size = System::Drawing::Size(885, 428);
				 this->panelBody->TabIndex = 5;
				 // 
				 // splitContainer1
				 // 
				 this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->splitContainer1->Location = System::Drawing::Point(0, 0);
				 this->splitContainer1->Name = L"splitContainer1";
				 // 
				 // splitContainer1.Panel1
				 // 
				 this->splitContainer1->Panel1->Controls->Add(this->panelLeft);
				 // 
				 // splitContainer1.Panel2
				 // 
				 this->splitContainer1->Panel2->Controls->Add(this->panelRender);
				 this->splitContainer1->Size = System::Drawing::Size(885, 428);
				 this->splitContainer1->SplitterDistance = 142;
				 this->splitContainer1->TabIndex = 0;
				 // 
				 // panelLeft
				 // 
				 this->panelLeft->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->panelLeft->Controls->Add(this->groupBox1);
				 this->panelLeft->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panelLeft->Location = System::Drawing::Point(0, 0);
				 this->panelLeft->Name = L"panelLeft";
				 this->panelLeft->Size = System::Drawing::Size(142, 428);
				 this->panelLeft->TabIndex = 0;
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->panel2);
				 this->groupBox1->Controls->Add(this->panel1);
				 this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
				 this->groupBox1->Location = System::Drawing::Point(0, 0);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(140, 423);
				 this->groupBox1->TabIndex = 0;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"DostÍpne warstwy";
				 // 
				 // panel2
				 // 
				 this->panel2->Controls->Add(this->treeViewLayers);
				 this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panel2->Location = System::Drawing::Point(3, 37);
				 this->panel2->Name = L"panel2";
				 this->panel2->Size = System::Drawing::Size(134, 383);
				 this->panel2->TabIndex = 1;
				 // 
				 // treeViewLayers
				 // 
				 this->treeViewLayers->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->treeViewLayers->DrawMode = System::Windows::Forms::TreeViewDrawMode::OwnerDrawText;
				 this->treeViewLayers->Location = System::Drawing::Point(0, 0);
				 this->treeViewLayers->Name = L"treeViewLayers";
				 treeNode7->Name = L"Node2";
				 treeNode7->Text = L"èrÛd≥o: Seria1";
				 treeNode8->Name = L"Node0";
				 treeNode8->Text = L"Typ: izolinie";
				 treeNode9->ContextMenuStrip = this->contextMenuStripLayerTreeNode;
				 treeNode9->Name = L"Node0";
				 treeNode9->Text = L"Granica ziaren";
				 treeNode10->Name = L"Node1";
				 treeNode10->Text = L"èrÛd≥o: Seria1";
				 treeNode11->Name = L"Node2";
				 treeNode11->Text = L"Typ: ciπg≥y kolor";
				 treeNode12->ContextMenuStrip = this->contextMenuStripLayerTreeNode;
				 treeNode12->Name = L"Node1";
				 treeNode12->Text = L"ZawartoúÊ wÍgla";
				 this->treeViewLayers->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {treeNode9, treeNode12});
				 this->treeViewLayers->Size = System::Drawing::Size(134, 383);
				 this->treeViewLayers->TabIndex = 0;
				 this->treeViewLayers->DrawNode += gcnew System::Windows::Forms::DrawTreeNodeEventHandler(this, &MainForm::treeView1_DrawNode_1);
				 this->treeViewLayers->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::treeViewLayers_MouseDoubleClick);
				 this->treeViewLayers->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::treeView1_MouseDown);
				 // 
				 // panel1
				 // 
				 this->panel1->Controls->Add(this->toolStrip1);
				 this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
				 this->panel1->Location = System::Drawing::Point(3, 16);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(134, 21);
				 this->panel1->TabIndex = 0;
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->AutoSize = false;
				 this->toolStrip1->GripMargin = System::Windows::Forms::Padding(0);
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripDropDownButton1, 
					 this->toolStripSeparator2, this->toolStripDropDownButton2});
				 this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::Flow;
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Padding = System::Windows::Forms::Padding(0);
				 this->toolStrip1->Size = System::Drawing::Size(134, 25);
				 this->toolStrip1->TabIndex = 0;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // toolStripDropDownButton1
				 // 
				 this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->toolStripDropDownButton1->DropDown = this->MenuLayer;
				 this->toolStripDropDownButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripDropDownButton1.Image")));
				 this->toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
				 this->toolStripDropDownButton1->Size = System::Drawing::Size(29, 20);
				 this->toolStripDropDownButton1->Text = L"toolStripDropDownButton1";
				 this->toolStripDropDownButton1->DropDownOpening += gcnew System::EventHandler(this, &MainForm::toolStripDropDownButton1_DropDownOpening);
				 // 
				 // MenuLayer
				 // 
				 this->MenuLayer->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {this->nowaWarstwaToolStripMenuItem, 
					 this->RemoveLayerMenuItem, this->toolStripSeparator1, this->ToggleLayerVisiblityMenuItem, this->toolStripMenuItem2, this->MoveUpLayerMenu, 
					 this->MoveDownLayerMenu, this->toolStripMenuItem3, this->SetLayerColorLayerMenuItem, this->RenameLayerToolStripMenuItem, this->toolStripMenuItem11, 
					 this->LayerSettingsLayerMenuItem, this->ShowLayerInfoLayerMenuItem});
				 this->MenuLayer->Name = L"contextMenuStrip1";
				 this->MenuLayer->OwnerItem = this->LayersToolStripMenuItem;
				 this->MenuLayer->Size = System::Drawing::Size(191, 226);
				 this->MenuLayer->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::TestLayerSelction_MenuOpening);
				 // 
				 // nowaWarstwaToolStripMenuItem
				 // 
				 this->nowaWarstwaToolStripMenuItem->Name = L"nowaWarstwaToolStripMenuItem";
				 this->nowaWarstwaToolStripMenuItem->Size = System::Drawing::Size(190, 22);
				 this->nowaWarstwaToolStripMenuItem->Text = L"Nowa warstwa...";
				 this->nowaWarstwaToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // RemoveLayerMenuItem
				 // 
				 this->RemoveLayerMenuItem->Name = L"RemoveLayerMenuItem";
				 this->RemoveLayerMenuItem->Size = System::Drawing::Size(190, 22);
				 this->RemoveLayerMenuItem->Text = L"UsuÒ warstwÍ";
				 this->RemoveLayerMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(187, 6);
				 // 
				 // ToggleLayerVisiblityMenuItem
				 // 
				 this->ToggleLayerVisiblityMenuItem->Name = L"ToggleLayerVisiblityMenuItem";
				 this->ToggleLayerVisiblityMenuItem->Size = System::Drawing::Size(190, 22);
				 this->ToggleLayerVisiblityMenuItem->Text = L"Renderuj warstwÍ";
				 this->ToggleLayerVisiblityMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem2
				 // 
				 this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
				 this->toolStripMenuItem2->Size = System::Drawing::Size(187, 6);
				 // 
				 // toolStripMenuItem3
				 // 
				 this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
				 this->toolStripMenuItem3->Size = System::Drawing::Size(187, 6);
				 // 
				 // SetLayerColorLayerMenuItem
				 // 
				 this->SetLayerColorLayerMenuItem->Name = L"SetLayerColorLayerMenuItem";
				 this->SetLayerColorLayerMenuItem->Size = System::Drawing::Size(190, 22);
				 this->SetLayerColorLayerMenuItem->Text = L"ZmieÒ kolor";
				 this->SetLayerColorLayerMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // RenameLayerToolStripMenuItem
				 // 
				 this->RenameLayerToolStripMenuItem->Name = L"RenameLayerToolStripMenuItem";
				 this->RenameLayerToolStripMenuItem->Size = System::Drawing::Size(190, 22);
				 this->RenameLayerToolStripMenuItem->Text = L"ZmieÒ NazwÍ";
				 this->RenameLayerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem11
				 // 
				 this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
				 this->toolStripMenuItem11->Size = System::Drawing::Size(187, 6);
				 // 
				 // LayerSettingsLayerMenuItem
				 // 
				 this->LayerSettingsLayerMenuItem->Name = L"LayerSettingsLayerMenuItem";
				 this->LayerSettingsLayerMenuItem->Size = System::Drawing::Size(190, 22);
				 this->LayerSettingsLayerMenuItem->Text = L"Ustawiena warstwy";
				 this->LayerSettingsLayerMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // ShowLayerInfoLayerMenuItem
				 // 
				 this->ShowLayerInfoLayerMenuItem->Name = L"ShowLayerInfoLayerMenuItem";
				 this->ShowLayerInfoLayerMenuItem->Size = System::Drawing::Size(190, 22);
				 this->ShowLayerInfoLayerMenuItem->Text = L"Informacje o warstwie";
				 this->ShowLayerInfoLayerMenuItem->Visible = false;
				 // 
				 // toolStripSeparator2
				 // 
				 this->toolStripSeparator2->Name = L"toolStripSeparator2";
				 this->toolStripSeparator2->Size = System::Drawing::Size(6, 23);
				 // 
				 // toolStripDropDownButton2
				 // 
				 this->toolStripDropDownButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				 this->toolStripDropDownButton2->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->EnterD3MenuItem, 
					 this->EnterD2MenuItem});
				 this->toolStripDropDownButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripDropDownButton2.Image")));
				 this->toolStripDropDownButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripDropDownButton2->Name = L"toolStripDropDownButton2";
				 this->toolStripDropDownButton2->Size = System::Drawing::Size(29, 20);
				 this->toolStripDropDownButton2->Text = L"toolStripDropDownButton2";
				 // 
				 // EnterD3MenuItem
				 // 
				 this->EnterD3MenuItem->Name = L"EnterD3MenuItem";
				 this->EnterD3MenuItem->Size = System::Drawing::Size(88, 22);
				 this->EnterD3MenuItem->Text = L"3D";
				 this->EnterD3MenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // EnterD2MenuItem
				 // 
				 this->EnterD2MenuItem->Checked = true;
				 this->EnterD2MenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->EnterD2MenuItem->Name = L"EnterD2MenuItem";
				 this->EnterD2MenuItem->Size = System::Drawing::Size(88, 22);
				 this->EnterD2MenuItem->Text = L"2D";
				 this->EnterD2MenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // panelRender
				 // 
				 this->panelRender->ContextMenuStrip = this->contextMenuStripRenderer;
				 this->panelRender->Controls->Add(this->ViewModeLabel);
				 this->panelRender->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panelRender->Location = System::Drawing::Point(0, 0);
				 this->panelRender->Name = L"panelRender";
				 this->panelRender->Size = System::Drawing::Size(739, 428);
				 this->panelRender->TabIndex = 0;
				 this->panelRender->SizeChanged += gcnew System::EventHandler(this, &MainForm::panelRender_SizeChanged);
				 this->panelRender->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelRender_MouseDown);
				 this->panelRender->MouseEnter += gcnew System::EventHandler(this, &MainForm::panelRender_MouseEnter);
				 this->panelRender->MouseLeave += gcnew System::EventHandler(this, &MainForm::panelRender_MouseLeave);
				 this->panelRender->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelRender_MouseMove);
				 this->panelRender->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelRender_MouseUp);
				 this->panelRender->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelRender_MouseWheel);
				 // 
				 // contextMenuStripRenderer
				 // 
				 this->contextMenuStripRenderer->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItemResetLayerZoom, 
					 this->toolStripMenuItem12, this->toolStripMenuItemRendererHideAll});
				 this->contextMenuStripRenderer->Name = L"contextMenuStripRenderer";
				 this->contextMenuStripRenderer->Size = System::Drawing::Size(154, 54);
				 this->contextMenuStripRenderer->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::contextMenuStripRenderer_Opening);
				 // 
				 // toolStripMenuItemResetLayerZoom
				 // 
				 this->toolStripMenuItemResetLayerZoom->Name = L"toolStripMenuItemResetLayerZoom";
				 this->toolStripMenuItemResetLayerZoom->Size = System::Drawing::Size(153, 22);
				 this->toolStripMenuItemResetLayerZoom->Text = L"Resetuj";
				 this->toolStripMenuItemResetLayerZoom->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem12
				 // 
				 this->toolStripMenuItem12->Name = L"toolStripMenuItem12";
				 this->toolStripMenuItem12->Size = System::Drawing::Size(150, 6);
				 // 
				 // toolStripMenuItemRendererHideAll
				 // 
				 this->toolStripMenuItemRendererHideAll->Name = L"toolStripMenuItemRendererHideAll";
				 this->toolStripMenuItemRendererHideAll->Size = System::Drawing::Size(153, 22);
				 this->toolStripMenuItemRendererHideAll->Text = L"Ukryj wszystkie";
				 this->toolStripMenuItemRendererHideAll->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // ViewModeLabel
				 // 
				 this->ViewModeLabel->AutoSize = true;
				 this->ViewModeLabel->BackColor = System::Drawing::SystemColors::Control;
				 this->ViewModeLabel->Location = System::Drawing::Point(0, 0);
				 this->ViewModeLabel->Name = L"ViewModeLabel";
				 this->ViewModeLabel->Size = System::Drawing::Size(69, 17);
				 this->ViewModeLabel->TabIndex = 2;
				 this->ViewModeLabel->Text = L"Perspektywa";
				 this->ViewModeLabel->TextAlign = System::Drawing::ContentAlignment::BottomRight;
				 this->ViewModeLabel->UseCompatibleTextRendering = true;
				 this->ViewModeLabel->Click += gcnew System::EventHandler(this, &MainForm::ViewModeLabel_Click);
				 // 
				 // panelTop
				 // 
				 this->panelTop->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->panelTop->Dock = System::Windows::Forms::DockStyle::Top;
				 this->panelTop->Location = System::Drawing::Point(0, 0);
				 this->panelTop->Name = L"panelTop";
				 this->panelTop->Size = System::Drawing::Size(885, 10);
				 this->panelTop->TabIndex = 4;
				 // 
				 // LayersToolStripMenuItem
				 // 
				 this->LayersToolStripMenuItem->DropDown = this->MenuLayer;
				 this->LayersToolStripMenuItem->Name = L"LayersToolStripMenuItem";
				 this->LayersToolStripMenuItem->Size = System::Drawing::Size(64, 20);
				 this->LayersToolStripMenuItem->Text = L"Warstwy";
				 // 
				 // menuStrip
				 // 
				 this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->daneToolStripMenuItem, 
					 this->LayersToolStripMenuItem, this->renderingToolStripMenuItem, this->ustawieniaToolStripMenuItem, this->AboutToolStripMenuItem});
				 this->menuStrip->Location = System::Drawing::Point(0, 0);
				 this->menuStrip->Name = L"menuStrip";
				 this->menuStrip->Size = System::Drawing::Size(885, 24);
				 this->menuStrip->TabIndex = 5;
				 this->menuStrip->Text = L"menuStrip1";
				 this->menuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainForm::menuStrip_ItemClicked);
				 // 
				 // daneToolStripMenuItem
				 // 
				 this->daneToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->wczytajToolStripMenuItem, 
					 this->SaveProjectUpperMenuItem, this->toolStripMenuItem8, this->importujToolStripMenuItem, this->toolStripMenuItem1, this->wyjscieToolStripMenuItem});
				 this->daneToolStripMenuItem->Name = L"daneToolStripMenuItem";
				 this->daneToolStripMenuItem->Size = System::Drawing::Size(46, 20);
				 this->daneToolStripMenuItem->Text = L"Dane";
				 // 
				 // wczytajToolStripMenuItem
				 // 
				 this->wczytajToolStripMenuItem->Name = L"wczytajToolStripMenuItem";
				 this->wczytajToolStripMenuItem->Size = System::Drawing::Size(166, 22);
				 this->wczytajToolStripMenuItem->Text = L"Wczytaj...";
				 this->wczytajToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // SaveProjectUpperMenuItem
				 // 
				 this->SaveProjectUpperMenuItem->Name = L"SaveProjectUpperMenuItem";
				 this->SaveProjectUpperMenuItem->Size = System::Drawing::Size(166, 22);
				 this->SaveProjectUpperMenuItem->Text = L"Zapisz";
				 this->SaveProjectUpperMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem8
				 // 
				 this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
				 this->toolStripMenuItem8->Size = System::Drawing::Size(163, 6);
				 // 
				 // importujToolStripMenuItem
				 // 
				 this->importujToolStripMenuItem->Name = L"importujToolStripMenuItem";
				 this->importujToolStripMenuItem->ShortcutKeyDisplayString = L"";
				 this->importujToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::I));
				 this->importujToolStripMenuItem->Size = System::Drawing::Size(166, 22);
				 this->importujToolStripMenuItem->Tag = L"1";
				 this->importujToolStripMenuItem->Text = L"Importuj...";
				 this->importujToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem1
				 // 
				 this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
				 this->toolStripMenuItem1->Size = System::Drawing::Size(163, 6);
				 // 
				 // wyjscieToolStripMenuItem
				 // 
				 this->wyjscieToolStripMenuItem->Name = L"wyjscieToolStripMenuItem";
				 this->wyjscieToolStripMenuItem->Size = System::Drawing::Size(166, 22);
				 this->wyjscieToolStripMenuItem->Text = L"Wyjscie";
				 // 
				 // renderingToolStripMenuItem
				 // 
				 this->renderingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->MakeScreenShotToolStripMenuItem});
				 this->renderingToolStripMenuItem->Name = L"renderingToolStripMenuItem";
				 this->renderingToolStripMenuItem->Size = System::Drawing::Size(73, 20);
				 this->renderingToolStripMenuItem->Text = L"Rendering";
				 // 
				 // MakeScreenShotToolStripMenuItem
				 // 
				 this->MakeScreenShotToolStripMenuItem->Name = L"MakeScreenShotToolStripMenuItem";
				 this->MakeScreenShotToolStripMenuItem->Size = System::Drawing::Size(164, 22);
				 this->MakeScreenShotToolStripMenuItem->Text = L"PrzechwyÊ klatkÍ";
				 this->MakeScreenShotToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // ustawieniaToolStripMenuItem
				 // 
				 this->ustawieniaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->ShowManagementWindowMenuItem, 
					 this->zarzadzajProjektemToolStripMenuItem, this->toolStripMenuItem10, this->RendererSettingsMenuItem1});
				 this->ustawieniaToolStripMenuItem->Name = L"ustawieniaToolStripMenuItem";
				 this->ustawieniaToolStripMenuItem->Size = System::Drawing::Size(76, 20);
				 this->ustawieniaToolStripMenuItem->Text = L"Ustawienia";
				 this->ustawieniaToolStripMenuItem->DropDownOpened += gcnew System::EventHandler(this, &MainForm::ustawieniaToolStripMenuItem_DropDownOpened);
				 // 
				 // ShowManagementWindowMenuItem
				 // 
				 this->ShowManagementWindowMenuItem->Name = L"ShowManagementWindowMenuItem";
				 this->ShowManagementWindowMenuItem->Size = System::Drawing::Size(197, 22);
				 this->ShowManagementWindowMenuItem->Text = L"Pokaø okno statusu";
				 this->ShowManagementWindowMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // zarzadzajProjektemToolStripMenuItem
				 // 
				 this->zarzadzajProjektemToolStripMenuItem->Enabled = false;
				 this->zarzadzajProjektemToolStripMenuItem->Name = L"zarzadzajProjektemToolStripMenuItem";
				 this->zarzadzajProjektemToolStripMenuItem->Size = System::Drawing::Size(197, 22);
				 this->zarzadzajProjektemToolStripMenuItem->Text = L"Zarzπdzaj projektem";
				 this->zarzadzajProjektemToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // toolStripMenuItem10
				 // 
				 this->toolStripMenuItem10->Name = L"toolStripMenuItem10";
				 this->toolStripMenuItem10->Size = System::Drawing::Size(194, 6);
				 // 
				 // RendererSettingsMenuItem1
				 // 
				 this->RendererSettingsMenuItem1->Name = L"RendererSettingsMenuItem1";
				 this->RendererSettingsMenuItem1->Size = System::Drawing::Size(197, 22);
				 this->RendererSettingsMenuItem1->Text = L"Konfiguracja programu";
				 this->RendererSettingsMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::MainFormUpperMenuDispatcher);
				 // 
				 // AboutToolStripMenuItem
				 // 
				 this->AboutToolStripMenuItem->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				 this->AboutToolStripMenuItem->Name = L"AboutToolStripMenuItem";
				 this->AboutToolStripMenuItem->Size = System::Drawing::Size(86, 20);
				 this->AboutToolStripMenuItem->Text = L"O programie";
				 this->AboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::AboutToolStripMenuItem_Click);
				 // 
				 // LayersManageToolStripMenuItem
				 // 
				 this->LayersManageToolStripMenuItem->Enabled = false;
				 this->LayersManageToolStripMenuItem->Name = L"LayersManageToolStripMenuItem";
				 this->LayersManageToolStripMenuItem->Size = System::Drawing::Size(132, 22);
				 this->LayersManageToolStripMenuItem->Text = L"Zarzπdzaj...";
				 // 
				 // toolStripMenuItem5
				 // 
				 this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
				 this->toolStripMenuItem5->Size = System::Drawing::Size(154, 22);
				 this->toolStripMenuItem5->Text = L"Renderuj";
				 // 
				 // toolStripSeparator3
				 // 
				 this->toolStripSeparator3->Name = L"toolStripSeparator3";
				 this->toolStripSeparator3->Size = System::Drawing::Size(151, 6);
				 // 
				 // toolStripMenuItem6
				 // 
				 this->toolStripMenuItem6->Enabled = false;
				 this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
				 this->toolStripMenuItem6->Size = System::Drawing::Size(154, 22);
				 this->toolStripMenuItem6->Text = L"PrzesuÒ w gÛrÍ";
				 // 
				 // toolStripMenuItem7
				 // 
				 this->toolStripMenuItem7->Enabled = false;
				 this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
				 this->toolStripMenuItem7->Size = System::Drawing::Size(154, 22);
				 this->toolStripMenuItem7->Text = L"PrzesuÒ w dÛ≥";
				 // 
				 // RefreshStatusBarTimer
				 // 
				 this->RefreshStatusBarTimer->Interval = 500;
				 this->RefreshStatusBarTimer->Tick += gcnew System::EventHandler(this, &MainForm::RefreshStatusBarTimer_Tick);
				 // 
				 // contextMenuStripViewMode
				 // 
				 this->contextMenuStripViewMode->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->OrthogonalViewMenuItem, 
					 this->PerspectiveViewMenuItem});
				 this->contextMenuStripViewMode->Name = L"contextMenuStripViewMode";
				 this->contextMenuStripViewMode->Size = System::Drawing::Size(164, 48);
				 // 
				 // OrthogonalViewMenuItem
				 // 
				 this->OrthogonalViewMenuItem->Name = L"OrthogonalViewMenuItem";
				 this->OrthogonalViewMenuItem->Size = System::Drawing::Size(163, 22);
				 this->OrthogonalViewMenuItem->Tag = L"0";
				 this->OrthogonalViewMenuItem->Text = L"Rzut prostokπtny";
				 this->OrthogonalViewMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SetPerspectiveMode);
				 // 
				 // PerspectiveViewMenuItem
				 // 
				 this->PerspectiveViewMenuItem->Name = L"PerspectiveViewMenuItem";
				 this->PerspectiveViewMenuItem->Size = System::Drawing::Size(163, 22);
				 this->PerspectiveViewMenuItem->Tag = L"1";
				 this->PerspectiveViewMenuItem->Text = L"Perspektywa";
				 this->PerspectiveViewMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SetPerspectiveMode);
				 // 
				 // timerShowDataInspector
				 // 
				 this->timerShowDataInspector->Tick += gcnew System::EventHandler(this, &MainForm::timerShowDataInspector_Tick);
				 // 
				 // timerStatusBarNotifications
				 // 
				 this->timerStatusBarNotifications->Interval = 10000;
				 this->timerStatusBarNotifications->Tick += gcnew System::EventHandler(this, &MainForm::timerStatusBarNotifications_Tick);
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(885, 484);
				 this->Controls->Add(this->panelMain);
				 this->Controls->Add(this->statusStrip1);
				 this->Controls->Add(this->menuStrip);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->Location = System::Drawing::Point(150, 200);
				 this->MainMenuStrip = this->menuStrip;
				 this->Name = L"MainForm";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
				 this->Text = L"VisApp";
				 this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
				 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
				 this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
				 this->contextMenuStripLayerTreeNode->ResumeLayout(false);
				 this->statusStrip1->ResumeLayout(false);
				 this->statusStrip1->PerformLayout();
				 this->panelMain->ResumeLayout(false);
				 this->panelBody->ResumeLayout(false);
				 this->splitContainer1->Panel1->ResumeLayout(false);
				 this->splitContainer1->Panel2->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
				 this->splitContainer1->ResumeLayout(false);
				 this->panelLeft->ResumeLayout(false);
				 this->groupBox1->ResumeLayout(false);
				 this->panel2->ResumeLayout(false);
				 this->panel1->ResumeLayout(false);
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->MenuLayer->ResumeLayout(false);
				 this->panelRender->ResumeLayout(false);
				 this->panelRender->PerformLayout();
				 this->contextMenuStripRenderer->ResumeLayout(false);
				 this->menuStrip->ResumeLayout(false);
				 this->menuStrip->PerformLayout();
				 this->contextMenuStripViewMode->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
#endif
			 //---------------------------------Form Events -------------------------------

	private: void SetMenuDispatchers() {
				 ActionHandler
					 //layer actions
					 ^ToggleLayerVisbilityAction = gcnew ActionHandler(this, &MainForm::ToggleSelectedLayerVisibility),
					 ^MoveUpAction = gcnew ActionHandler(this, &MainForm::MoveLayerUp),
					 ^MoveDownAction = gcnew ActionHandler(this, &MainForm::MoveLayerDown),
					 ^Enter3DAction = gcnew ActionHandler(this, &MainForm::EnterD3),
					 ^Enter2DAction = gcnew ActionHandler(this, &MainForm::EnterD2),
					 ^ShowLayerSettings = gcnew ActionHandler(this, &MainForm::ShowSelectedLayerSettings),
					 ^SetLayerColor = gcnew ActionHandler(this, &MainForm::ChangeLayerBaseColor),
					 ^ShowLayerInfo = gcnew ActionHandler(this, &MainForm::ShowLayerInfoWindow),
					 ^DeleteLayer = gcnew ActionHandler(this, &MainForm::DeleteLayer),
					 ^RenameLayer = gcnew ActionHandler(this, &MainForm::ChangeLayerName),
					 //project action
					 ^SaveAction = gcnew ActionHandler(this, &MainForm::ActionSaveProject),
					 ^LoadAction = gcnew ActionHandler(this, &MainForm::ActionLoadProject),
					 //external windows
					 ^ManagementWindow = gcnew ActionHandler(&VisApp::gui::ManagementWindow::Show),
					 ^SettingsWindow = gcnew ActionHandler(&VisApp::gui::SettingsWindow::Show),
					 ^ProjectMgt = gcnew ActionHandler(&VisApp::gui::ProjectMgt::Show),
					 //Wizards
					 ^ImportWizard = gcnew ActionHandler(this, &MainForm::ActionPerformImportWizard),
					 ^LayerWizard = gcnew ActionHandler(this, &MainForm::ActionPerfromAddLayersWizard),
					 //Renderer
					 ^MakeRendererScreenShot = gcnew ActionHandler(this, &MainForm::MakeScreenShot),
					 ^ResetZoom = gcnew ActionHandler(this, &MainForm::ResetZoom),
					 ^HideAll = gcnew ActionHandler(this, &MainForm::HideAllLayers),
					 //null action
					 ^NullAction = nullptr
					 ;

				 ShowManagementWindowMenuItem->Tag = ManagementWindow;
				 toolStripProgressBar->Tag = ManagementWindow;
				 RendererSettingsMenuItem1->Tag = SettingsWindow;
				 zarzadzajProjektemToolStripMenuItem->Tag = ProjectMgt;

				 importujToolStripMenuItem->Tag		= ImportWizard;
				 nowaWarstwaToolStripMenuItem->Tag	= LayerWizard;

				 wczytajToolStripMenuItem->Tag = LoadAction;
				 SaveProjectUpperMenuItem->Tag = SaveAction;

				 ShowLayerInfoLayerTreeViewContextMenu->Tag = ShowLayerInfo;
				 ShowLayerInfoLayerMenuItem->Tag			= ShowLayerInfo;
				 SetLayerColorLayerMenuItem->Tag			= SetLayerColor;
				 SetLayerColorLayerTreeViewContextMenu->Tag = SetLayerColor;
				 LayerSettingsLayerMenuItem->Tag			= ShowLayerSettings;
				 LayerSettingsLayerTreeViewContextMenu->Tag	= ShowLayerSettings;
				 ToggleLayerVisiblityMenuItem->Tag			= ToggleLayerVisbilityAction;
				 ToggleLayerVisibilityTreeViewMenuItem->Tag = ToggleLayerVisbilityAction;
				 MoveUpLayerMenu->Tag						= MoveUpAction;
				 MoveUpTreeContexMenu->Tag					= MoveUpAction;
				 MoveDownLayerMenu->Tag						= MoveDownAction;
				 MoveDownTreeContexMenu->Tag				= MoveDownAction;
				 EnterD2MenuItem->Tag						= Enter2DAction;
				 EnterD3MenuItem->Tag						= Enter3DAction;
				 RemoveLayerMenuItem->Tag					= DeleteLayer;
				 RenameLayerToolStripMenuItem->Tag			= RenameLayer;

				 MakeScreenShotToolStripMenuItem->Tag		= MakeRendererScreenShot;
				 toolStripMenuItemRendererHideAll->Tag		= HideAll;
				 toolStripMenuItemResetLayerZoom->Tag		= ResetZoom;
			 }

			 //---------------------------------Project -------------------------------

	private: 
		VisApp::Interface::SharedProject *m_Project;
	public: VisApp::Interface::SharedProject& Project() { return *m_Project; }

			//---------------------------------Form Events -------------------------------

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 //	 ViewModeLabel->Visible = false;
				 UpdateWindowName();
				 treeViewLayers->Nodes->Clear();
				 RefreshStatusBarTimer->Enabled = true;
#ifndef _DEBUG
				 ViewModeLabel->Visible = false;
#endif
			 }
	private: System::Void MainForm_Shown(System::Object^  sender, System::EventArgs^  e) {
				 if(!InitializeCore()) {
					 MessageBox::Show(this, L"B≥πd inicjalizacji!", L"B≥πd", MessageBoxButtons::OK, MessageBoxIcon::Error);
					 Application::Exit();
				 }
#ifdef _DEBUG
				 //	 VisApp::gui::ManagementWindow::Show();
#endif
			 }
	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 // Core::gui::ProcessListWindow::Hide();
				 RefreshStatusBarTimer->Enabled = false;
				 FinalizeCore();
			 }
	private: System::Void AboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 gui::AboutWindow ^aw = gcnew AboutWindow(this);
				 aw->ShowDialog();
				 delete aw;
			 }

	private: System::Void RefreshStatusBarTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 UpdateStatusBar();
			 }

			 //-------------------------------- Events -------------------------------

	private: System::Void MainFormUpperMenuDispatcher(System::Object^  sender, System::EventArgs^  e) {
				 Object^ tag = ((ToolStripItem^)sender)->Tag;
				 if(tag == nullptr){
					 ((ToolStripItem^)sender)->Enabled = false;
					 MessageBox::Show("Funkcja jest niedostÍpna");
					 return;
				 }
				 try {
					 ((ActionHandler^)tag)();
				 }
				 catch(const wchar_t *msg) {
					 _AddLog(Warning, msg);
					 MessageBox::Show(this, gcnew String(msg), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				 }
				 catch(const char *msg) {
					 _AddLog(Warning, msg);
					 MessageBox::Show(this, gcnew String(msg), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				 }
				 catch(const std::wstring& msg) {
					 _AddLog(Warning, msg);
				 }
				 catch(String^ msg) {
					 _AddLog(Warning, msg);
				 }
				 catch(...) {
					 ((ToolStripItem^)sender)->Enabled = false;
					 _AddLog(CriticalError, "CRITICAL ERROR IN USER INTERFACE ACTION DISPATCHER. CATCHED UNKNOWN EXCEPTION.");
					 MessageBox::Show(this, L"Wystπpi≥ b≥πd w interfejsie aplikacji.\nZaleca siÍ ponowne uruchomnienie programu.\n", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }

			 //---------------------------------OWN TYPES -------------------------------
	public: 
		ref class NotificationDispatcher {
		public:
			NotificationDispatcher() {
			}
			void OnMessage(CoreMessageClass MessageClass, const std::wstring &Message) {
				MainForm::Instance()->Invoke(gcnew CoreMessageDispatcher(MainForm::Instance(), &MainForm::CoreMessage),
					gcnew CoreMessageParameters(Message, MessageClass));
			}
			void OnMessage(VisApp::Interface::CoreNotification notf) {
				using VisApp::Interface::CoreNotification;
				switch (notf) {
				case VisApp::Interface::CoreNotification::Unknown:
					break;
				case VisApp::Interface::CoreNotification::LayersChanged: {
					MainForm::Instance()->Invoke(gcnew ActionHandler(MainForm::Instance(), &MainForm::UpdateLayerList));
					break;
																		 }
				case VisApp::Interface::CoreNotification::ProcessesChanged:
					break;
				case CoreNotification::ProjectChanged:
					MainForm::Instance()->Invoke(gcnew ActionHandler(MainForm::Instance(), &MainForm::UpdateWindowName));
					break;				
				default:
					break;
				}
			}
		};
	private: 
		ref class LayerTreeNode {
		public:
			VisApp::Renderer::LayerInterface *Instance; //TODO: this is unsafe!!
			TreeNode^ OwnerNode;
		};
	private:
		ref class LayerTreeNodeSorter : public System::Collections::IComparer {
		public:
			virtual int Compare(Object^ x, Object^ y) {
				TreeNode^ tx = (TreeNode^)x;
				TreeNode^ ty = (TreeNode^)y;
				LayerTreeNode ^nx = (LayerTreeNode^) tx->Tag;
				LayerTreeNode ^ny = (LayerTreeNode^) ty->Tag;
				if(!nx || !ny) return 0;
				int posx = nx->Instance->GetRenderIndex();
				int posy = ny->Instance->GetRenderIndex();
				if(posx == posy) return String::Compare(tx->Text, ty->Text);
				if(posx == -1) return 1;
				if(posy == -1) return -1;
				return posx - posy;
			}
		};
	private: 
		typedef Generic::List<LayerTreeNode^> LayerTreeNodeList;
	private: 
		ref class StatusBarNotificationItem {
		public:
			String ^Message;
			StatusTipMessageClass Class;
			StatusBarNotificationItem(String ^m, StatusTipMessageClass c) {
				Message = m;
				Class = c;
			}
		};

		//------------------------------------DATA ---------------------------------

	private:
		static NotificationDispatcher ^_NotificationDispatcher = nullptr;
		Point m_LastMousePoint;
		unsigned m_MouseStatus;
		LayerType m_CurrentViewType;
		bool m_UsePerspective;
		int m_CanRender;
		unsigned __int64 m_WhenToShowDataInspector;
		System::Drawing::Point m_DataInspectorShowPoint;
		DataInspector ^m_DataInspector;
		Generic::Queue<StatusBarNotificationItem^> ^StatusBarNotifications;

		//-------------------------------PUBLIC GETTERS ----------------------------	

	public:
		static NotificationDispatcher^ GetNotificationDispatcher() {
			if(_NotificationDispatcher == nullptr)
				_NotificationDispatcher = gcnew NotificationDispatcher();
			return _NotificationDispatcher;
		}

		DataInspector^ GetDataInspector() {
			if(m_DataInspector == nullptr) {
				m_DataInspector = gcnew DataInspector();
				//	m_DataInspector->Owner = this;
			}
			auto mp = System::Windows::Forms::Cursor::Position;
			m_DataInspector->SetDesktopLocation(mp.X-2, mp.Y-2);
			return m_DataInspector;
		}
		void HideDataInspector() {
			if(m_DataInspector == nullptr) return;
			if(m_DataInspector->IsStandalone()) {
				m_DataInspector = nullptr;
			} else
				m_DataInspector->Hide();
		}

		//---------------------------------user handlers -------------------------------

	public: bool AskForPermission() {
				return MessageBox::Show(this, L"Czy jesteú pewien?", Application::ProductName, MessageBoxButtons::YesNo, MessageBoxIcon::Question) == Forms::DialogResult::Yes;
			}

	public: void PushStatusNotification(String ^s, StatusTipMessageClass c) {
				StatusBarNotifications->Enqueue(gcnew StatusBarNotificationItem(s, c));
				if(!timerStatusBarNotifications->Enabled) {
					timerStatusBarNotifications->Enabled = true;
					timerStatusBarNotifications_Tick(nullptr, nullptr);
				}
			}
	private: System::Void timerStatusBarNotifications_Tick(System::Object^  sender, System::EventArgs^  e) {
				 if(StatusBarNotifications->Count == 0) {
					 toolStripStatusLabelTips->Text = "";
					 timerStatusBarNotifications->Enabled = false;
				 } else {
					 StatusBarNotificationItem ^itm = StatusBarNotifications->Dequeue();
					 switch (itm->Class) {
					 case StatusTipMessageClass::Error: 
						 toolStripStatusLabelTips->ForeColor = Color::Maroon;
						 break;
					 case StatusTipMessageClass::Hint: 
						 toolStripStatusLabelTips->ForeColor = Color::Blue;
						 break;
					 case StatusTipMessageClass::Warning: 
						 toolStripStatusLabelTips->ForeColor = Color::Olive;
						 break;
					 default:
						 toolStripStatusLabelTips->ForeColor = this->ForeColor;
					 }
					 toolStripStatusLabelTips->Text = itm->Message;
				 }
			 }

			 //---------------------------------core handlers -------------------------------

	private: bool InitializeCore() {
				 CoreMgt::Initialize(this);
				 VisApp::gui::OGLContext::InitInstance(this, (HWND)panelRender->Handle.ToPointer());
				 CoreMgt::WaitForCore();
				 panelRender_SizeChanged(panelRender, nullptr);
				 EnterD2();
				 return true;
			 }
	private: System::Void FinalizeCore() {
				 VisApp::gui::OGLContext::FinInstance();
				 CoreMgt::Finalize(this);
			 }
	private: void UpdateWindowName() {
				 String ^t = Application::ProductName;
				 if(Project() && !Project()->IsVirtual())
					 t += String::Format(" [{0}]", Helpers::ToString(Project()->GetName()));
				 this->Text = t;
				 DEBUG_WINDOW_NAME
			 }
	private: bool CanRender() {
				 if(m_CanRender < 0) {
					 m_CanRender = CoreMgt::GetCore()->GetVisualizer() != 0;
				 }
				 return m_CanRender == 1;
			 }
	private: bool FailIfNoRendering() {
				 if(CanRender()) return false;
				 MessageBox::Show(this, "Ta funkcja wymaga uruchomionego silnika graficznego!", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 return true;
			 }
	private: void RendererChanged() {
				 if(!CanRender()) return;
				 //ignore; for future use
				 //request frame
			 }
	private: VisApp::Interface::iVisualizer* GetRenderer() {
				 auto r = CoreMgt::GetCore()->GetVisualizer();
				 if(!r) throw "Silnik graficzny nie jest uruchomiony.\nAkcja niemoøliwa.";
				 return r;
			 }
	private: void CoreMessage(CoreMessageParameters ^params) {
				 MessageBoxIcon ic;
				 switch (params->Class) {
				 case CoreMessageClass::Error:
					 ic = MessageBoxIcon::Error;
					 break;				 
				 case CoreMessageClass::Notification:
					 ic = MessageBoxIcon::Information;
					 break;
				 default:
					 ic = MessageBoxIcon::None;
				 }
				 MessageBox::Show(this, params->Message, Application::ProductName, MessageBoxButtons::OK, ic);
			 }

	public: VisApp::gui::CLIGuiOperations* GetGuiOperations() {
				return 0;
			}

			//----------------------------------camera manipulation ---------------------------------

	private: System::Void panelRender_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 switch (e->Button) {
				 case Windows::Forms::MouseButtons::Left:
					 m_LastMousePoint = e->Location;
					 m_MouseStatus |= MouseLeft;
					 break;
				 case Windows::Forms::MouseButtons::Middle:
					 break;
				 }
			 }
	private: System::Void panelRender_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 switch (e->Button) {
				 case Windows::Forms::MouseButtons::Left:
					 m_MouseStatus &= ~MouseLeft;
					 break;
				 case Windows::Forms::MouseButtons::Middle:
					 break;
				 }
			 }
	private: System::Void panelRender_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(!CanRender()) return;

				 if(Settings::root().DataInspector.Use) {
					 m_WhenToShowDataInspector = GetTickCount64() + Settings::root().DataInspector.ShowDelay;
					 m_DataInspectorShowPoint = e->Location;
				 }

				 HideDataInspector();
				 Point Delta(-e->X, -e->Y);
				 Delta.Offset(m_LastMousePoint);
				 m_LastMousePoint = e->Location;
				 if(m_MouseStatus & MouseLeft) {
					 auto vis = CoreMgt::GetCore()->GetVisualizer();
					 auto camera = vis->GetCamera();
					 VisApp::Math::fvec2 o;
					 o[0] = (float)-Delta.X;
					 o[1] = (float)-Delta.Y;
					 if(m_CurrentViewType == LayerType::d3) {
						 o /= 100.0f;
						 camera->Orbit(o, true);
					 } else {
						 o /= 2.0f;
						 camera->MoveCamera(VisApp::Math::fvec3(o[0], o[1], 0));
					 }
				 }	
			 }
	private: System::Void panelRender_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
				 if(!CanRender()) return;
				 auto vis = CoreMgt::GetCore()->GetVisualizer();
				 auto camera = vis->GetCamera();
				 if(m_UsePerspective)
					 camera->Magnify(e->Delta / 5.0f);
				 else
					 camera->Magnify(e->Delta / 500.0f);
			 }
	private: System::Void panelRender_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
				 VisApp::gui::OGLContext::SetView(panelRender->Width, panelRender->Height);
				 if(CanRender())
					 GetRenderer()->GetCamera()->Center(NULL);
			 }
	private: System::Void ViewModeLabel_Click(System::Object^  sender, System::EventArgs^  e) {
				 contextMenuStripViewMode->Show(System::Windows::Forms::Control::MousePosition);
			 }
	private: void SetPerspectiveMode(System::Object^ sender, System::EventArgs^ e) {
				 auto vis = CoreMgt::GetCore()->GetVisualizer();
				 if(!vis) return;
				 String^ tag = (String^)((ToolStripItem^)sender)->Tag;
				 ViewModeLabel->Text = ((ToolStripItem^)sender)->Text;
				 switch(Convert::ToInt32(tag)) {
				 case 0: 
					 //orthogonal
					 vis->GetCamera()->SetOrthogonalMode();
					 m_UsePerspective = false;
					 PushStatusNotification(L"W≥πczono tryb rzutu prostokπtnego", StatusTipMessageClass::Normal);
					 break;
				 case 1: 
					 //perspective
					 vis->GetCamera()->SetPerspectiveMode();
					 m_UsePerspective = true;
					 PushStatusNotification(L"W≥πczono tryb perspektywy", StatusTipMessageClass::Normal);
					 break;
				 }
			 }

			 //basic Actions

	private: void ActionPerformImportWizard() {
				 VisApp::gui::ImportData ^id = gcnew VisApp::gui::ImportData(this);
				 if(id->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) {
					 delete id;
					 return;
				 }

				 if(id->ExecuteAction(ImportDataFlags::Get_CreateProject)) 
					 ActionPerformCreateProjectWizard(1);
				 else {
					 if(!Project())
						 CreateDummyProject();
				 }

				 id->SetImportProcess(Project()->GetName());//TODO:!!!!

				 if(id->ExecuteAction(ImportDataFlags::Get_AddLayers)) 
					 ActionPerfromAddLayersWizard();
				 delete id;
			 }
	private: void ActionPerfromAddLayersWizard() {
				 AddNewLayersWizard^ anlw = gcnew AddNewLayersWizard(this);
				 if(anlw->ShowDialog(this) != Forms::DialogResult::OK) {
					 delete anlw;
					 return;
				 }
				 anlw->BeginProcesses();
				 delete anlw;
			 }
	private: bool ActionPerformCreateProjectWizard(unsigned CreateDummyOnFail) { //TODO
				 auto pmgt = VisApp::Interface::iProjectMgt::GetInstance();
				 if(pmgt->ProjectCount() > 0) {
					 //app allows only one active project

					 if(MessageBox::Show(this, "Akcja wymaga zamkniÍcia obecnie otwartego projektu.\nKontynuowaÊ?", 
						 Application::ProductName, MessageBoxButtons::YesNo) != Forms::DialogResult::Yes)
						 return false;

					 pmgt->CloseAllProjects();
				 }

				 CreateProjectWizard ^cpw = gcnew CreateProjectWizard(this);
				 if(cpw->ShowDialog() != Windows::Forms::DialogResult::OK) {
					 if(CreateDummyOnFail) {
						 CreateDummyProject();
						 return true;
					 }
					 return false;
				 }

				 Directory::CreateDirectory(cpw->GetLocation());
				 std::wstring stdproj = marshal_as<std::wstring>(cpw->GetProjectName());
				 std::wstring stddir = marshal_as<std::wstring>(cpw->GetLocation());

				 Project() = VisApp::Interface::iProjectMgt::GetInstance()->CreateProject(stdproj, stddir);
				 UpdateWindowName();
				 return true;
			 }
	private: void CreateDummyProject() {
				 std::wstring dir;
				 std::wstring projn = L"UnnamedProject";
#ifdef _DEBUG
				 dir = Helpers::ToStdWStr(Directory::GetCurrentDirectory());
				 dir += L"\\";
				 dir += projn;
#endif
				 Project() = VisApp::Interface::iProjectMgt::GetInstance()->CreateProject(projn, dir);
				 UpdateWindowName();
			 }
	private: void ActionLoadProject() {
				 auto pmgt = VisApp::Interface::iProjectMgt::GetInstance();
				 if(Project()) {
					 //app allows only one active project
					 if(MessageBox::Show(this, "Akcja wymaga zamkniÍcia obecnie otwartego projektu.\nKontynuowaÊ?", 
						 Application::ProductName, MessageBoxButtons::YesNo) != Forms::DialogResult::Yes)
						 return;

					 pmgt->CloseAllProjects();
				 }

				 OpenFileDialog ^ofd = gcnew OpenFileDialog();
				 ofd->Filter = "VisApp project file (*.vap)|*.vap";
				 ofd->FilterIndex = 1;
				 ofd->CheckFileExists = true;
				 if(ofd->ShowDialog() != Forms::DialogResult::OK) return;

				 String ^fn = ofd->FileName;
				 std::wstring stdfn = Helpers::ToString(fn);
				 Project() = pmgt->LoadProject(stdfn);
			 }
	private: void ActionSaveProject() {
				 if(!Project()) return;
				 auto &proj = Project();
				 if(proj->IsVirtual()) {
					 CreateProjectWizard ^cpw = gcnew CreateProjectWizard(this);
					 if(cpw->ShowDialog() != Windows::Forms::DialogResult::OK)
						 return;
					 std::wstring stdproj = marshal_as<std::wstring>(cpw->GetProjectName());
					 std::wstring stddir = marshal_as<std::wstring>(cpw->GetLocation());
					 proj->SetLocation(stddir);
					 proj->SetName(stdproj);
					 UpdateWindowName();
				 } 
				 proj->SaveProject();
			 }
	private: void UpdateStatusBar() {
				 auto instance = Worker::Mgt::Manager::Instance();
				 if(!instance) return; //silently ignore if worker instance isn't created.

				 Worker::Mgt::WeakWorkerList list;
				 instance->GetWorkerList(list);

				 int real_count = 0;
				 float progress = 0;

				 for(auto &it: list) {
					 if(it.expired()) continue;
					 auto worker = it.lock();

					 switch(worker->GetStatus()){
					 case Worker::Mgt::WorkerStatus::Working:
					 case Worker::Mgt::WorkerStatus::Waiting:
						 float p = worker->GetProgress();
						 if(p < 0) continue;
						 ++real_count;
						 progress += p;
						 break;
					 }
				 }

				 static int max_count = 1;
				 max_count = max(max_count, real_count);

				 int delta = max_count - real_count;
				 // if(delta < 0) delta = 0;
				 if(real_count == 0) {
					 if(max_count != 0) {
						 progress = 0;
						 toolStripStatusLabelOperation->Text = "bezczynny";
						 PushStatusNotification(L"UkoÒczono wszystkie aktywne zadania", StatusTipMessageClass::Normal);
						 max_count = 0;
						 toolStripProgressBar->ProgressBar->Value = 0;
					 }
				 } else {
					 progress += delta;
					 progress *= 100;
					 progress /= (max_count);				 
					 toolStripStatusLabelOperation->Text = real_count + " aktywnych zadaÒ";
					 toolStripProgressBar->ProgressBar->Value = (int)progress;
				 }

				 auto *im = CoreMgt::GetCore();
				 if(!im) return;
				 auto *ms = im->GetMemoryStatistics();
				 if(ms->UsedMemory > 0) {
					 String ^memused = Helpers::FileSizeToString(ms->UsedMemory);
#ifdef _DEBUG
					 toolStripStatusLabelMiddle->Text = String::Format("ZajÍto {0}, exist {1} memobjs", memused, ms->MemObjects);
#else
					 toolStripStatusLabelMiddle->Text = String::Format("ZajÍto {0}", memused);
#endif
				 } else {
					 toolStripStatusLabelMiddle->Text = "";
				 }
			 }

			 //Layer list manipulation

	private: System::Void treeViewLayers_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 ToggleSelectedLayerVisibility();
			 }
	private: System::Void toolStripDropDownButton1_DropDownOpening(System::Object^  sender, System::EventArgs^  e) {
				 TestLayerSelction();
			 }
	private: System::Void TestLayerSelction_MenuOpening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 TestLayerSelction();
			 }
	private: System::Void treeView1_DrawNode_1(System::Object^  sender, System::Windows::Forms::DrawTreeNodeEventArgs^  e) {
				 bool grayed = true;
				 e->DrawDefault = true;

				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(e->Node->Tag);
				 if(ltn)
					 grayed = !ltn->Instance->IsVisible();

				 if(grayed)
					 e->Node->ForeColor = Color::Gray;
				 else
					 e->Node->ForeColor = Color::Black;
			 }
	private: System::Void treeView1_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
				 if(e->Node->Level != 1) return;
				 e->Node->Checked = !e->Node->Checked;
			 }
	private: System::Void treeView1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(e->Button == System::Windows::Forms::MouseButtons::Right) {
					 TreeNode ^n = treeViewLayers->GetNodeAt(e->X, e->Y);
					 if(n != nullptr) {
						 treeViewLayers->SelectedNode = n;
					 }
					 TestLayerSelction();
				 }
			 }
	private: void MoveLayerUp() { MoveLayer(-1); }
	private: void MoveLayerDown() { MoveLayer(1); }
	private: void MoveLayer(int index) {
				 if(!CanRender()) return;
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = (LayerTreeNode^)treeViewLayers->SelectedNode->Tag;
				 if(!ltn->Instance->IsVisible())
					 return;
				 ltn->Instance->Move(index);
			 }
	private: void ToggleSelectedLayerVisibility() {
				 if(FailIfNoRendering()) return;
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;
				 bool value;
				 treeViewLayers->SelectedNode->Checked = value = !ltn->Instance->IsVisible();
				 ltn->Instance->SetVisibility(value);
			 }
	private: void UpdateLayerList() {
				 LayerTreeNodeList ^Nodes = gcnew LayerTreeNodeList();
				 for each (TreeNode ^i in treeViewLayers->Nodes) {
					 Nodes->Add((LayerTreeNode^)i->Tag);
				 }

				 auto proj = VisApp::Interface::iProjectMgt::GetInstance()->GetProject(0);
				 if(!proj) return;

				 treeViewLayers->BeginUpdate();

				 auto store = proj->GetDataStore();
				 //TODO: this in not thread safe!!!
				 for(unsigned i = 0; i < store->GetLayerCount(); ++i) {
					 auto layer = store->GetLayer(i);
					 if(!layer) break;

					 if(layer->GetLayerType() != m_CurrentViewType) {
						 if(layer->IsVisible())
							 layer->SetVisibility(false);
						 continue;
					 }

					 LayerTreeNode ^node = nullptr;
					 for each (LayerTreeNode ^j in Nodes)
						 if(j->Instance == layer.get()) {
							 node = j;
							 Nodes->Remove(j);
							 break;
						 }

						 if(node == nullptr) {
							 node = gcnew LayerTreeNode();
							 node->Instance = layer.get();
							 node->OwnerNode = treeViewLayers->Nodes->Add(Helpers::ToString(layer->GetName()));
							 node->OwnerNode->ContextMenuStrip = contextMenuStripLayerTreeNode;
							 node->OwnerNode->Tag = node;
						 }
						 node->OwnerNode->Checked = node->Instance->IsVisible();
						 node->OwnerNode->Text = Helpers::ToString(layer->GetName());

						 //	TreeNode ^tn = node->OwnerNode;
						 //	tn->Nodes->Clear();
						 //TODO: recreate info subnodes
				 }
				 for each (LayerTreeNode ^i in Nodes) {
					 i->OwnerNode->Remove();
					 delete i;
				 }
				 delete Nodes;
				 treeViewLayers->TreeViewNodeSorter = gcnew LayerTreeNodeSorter();
				 treeViewLayers->Sort();
				 treeViewLayers->EndUpdate();
			 }
	private: void ShowSelectedLayerSettings() {
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;

				 if(!ltn->Instance->IsVisible()) {
					 MessageBox::Show(this, "Nie moøna otworzyÊ konfiguracji niewidocznej warstwy!.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 return;
				 }

				 auto lgui = ltn->Instance->QuerryCLIGuiHandler();
				 if(!lgui) {
					 MessageBox::Show(this, "Wtyczka nie udostÍpnia okna konfiguracji.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Information);
					 return;
				 }

				 lgui->SetGuiOperations(GetGuiOperations());
				 lgui->OpenConfiguration(this);
			 }
	private: void ChangeLayerBaseColor() {
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;
				 VisApp::gui::Manip::Layer::EditColor(this, ltn->Instance);
				 RendererChanged();
			 }
	private: void ShowLayerInfoWindow() {
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;
				 ProjectMgt::DoShowFor(this, Project(), ProjectMgtPage::Layer, ltn->Instance->GetName());
			 }
	private: void TestLayerSelction() {
				 bool enabled = false, checked = false;
				 if(treeViewLayers->SelectedNode) {
					 enabled = treeViewLayers->SelectedNode->Level == 0;
					 checked = treeViewLayers->SelectedNode->Checked && enabled;
				 }
				 ToggleLayerVisibilityTreeViewMenuItem->Checked = checked;
				 ToggleLayerVisibilityTreeViewMenuItem->Enabled = enabled;
				 ToggleLayerVisiblityMenuItem->Checked = checked;
				 ToggleLayerVisiblityMenuItem->Enabled = enabled;
				 RemoveLayerMenuItem->Enabled = enabled;
				 MoveUpLayerMenu->Enabled = enabled;
				 MoveDownLayerMenu->Enabled = enabled;
				 MoveUpTreeContexMenu->Enabled = enabled;
				 MoveDownTreeContexMenu->Enabled = enabled;
				 LayerSettingsLayerTreeViewContextMenu->Enabled = enabled;
				 LayerSettingsLayerMenuItem->Enabled = enabled;
				 RenameLayerToolStripMenuItem->Enabled = enabled;
				 SetLayerColorLayerMenuItem->Enabled = enabled;
				 SetLayerColorLayerTreeViewContextMenu->Enabled = enabled;
			 }
	private: void EnterD3() {
				 if(m_CurrentViewType == LayerType::d3) return;
				 m_CurrentViewType = LayerType::d3;
				 SetPerspectiveMode(PerspectiveViewMenuItem, nullptr);
				 treeViewLayers->Nodes->Clear();
				 UpdateLayerList();
				 TestViewType();
			 }
	private: void EnterD2() {
				 if(m_CurrentViewType == LayerType::d2) return;
				 m_CurrentViewType = LayerType::d2;
				 SetPerspectiveMode(OrthogonalViewMenuItem, nullptr);
				 treeViewLayers->Nodes->Clear();
				 UpdateLayerList();
				 TestViewType();
			 }
	private: void TestViewType() {
				 EnterD2MenuItem->Checked = m_CurrentViewType == LayerType::d2;
				 EnterD3MenuItem->Checked = m_CurrentViewType == LayerType::d3;
			 }
	private: void DeleteLayer() {
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;
				 auto proj = VisApp::Interface::iProjectMgt::GetInstance()->GetProject(0);
				 if(!proj) return;
				 if(!AskForPermission())
					 return;
				 treeViewLayers->SelectedNode->Tag = nullptr;
				 treeViewLayers->SelectedNode->Remove();
				 auto store = proj->GetDataStore();
				 store->DeleteResource(ltn->Instance);
				 delete ltn;
			 }
	private: void ChangeLayerName() {
				 if(treeViewLayers->SelectedNode == nullptr) return;
				 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(treeViewLayers->SelectedNode->Tag);
				 if(!ltn) return;
				 VisApp::gui::Manip::Layer::EditName(this, ltn->Instance);
			 }

			 //Renderer

	private: void MakeScreenShot() {
				 if(FailIfNoRendering()) return;
				 auto vis = CoreMgt::GetCore()->GetVisualizer();
				 SaveFileDialog ^sfd = gcnew SaveFileDialog();
				 sfd->Filter = "PNG|*.png|BMP|*.bmp";
				 sfd->FilterIndex = 1;
				 sfd->AddExtension = true;
				 //PNG, JPG, BMP,
				 if(sfd->ShowDialog() != Forms::DialogResult::OK) return;
				 auto file = Helpers::ToString(sfd->FileName);
				 auto fmt = static_cast<VisApp::Interface::iVisualizer::CaptureFileFormat>(sfd->FilterIndex - 1);
				 vis->CaptureScreenShot(file, fmt);
			 }
	private: System::Void timerShowDataInspector_Tick(System::Object^  sender, System::EventArgs^  e) {
				 auto ticks = GetTickCount64();
				 if(m_WhenToShowDataInspector > ticks || m_WhenToShowDataInspector == 0)
					 return;

				 m_WhenToShowDataInspector = 0;

				 if(m_UsePerspective) {
					 PushStatusNotification(L"Podglπd danych pracuje jedynie w trybie 2D!", StatusTipMessageClass::Hint);
					 return;
				 }

				 VisApp::Math::uvec2 mp(m_DataInspectorShowPoint.X, m_DataInspectorShowPoint.Y);

				 auto vis = CoreMgt::GetCore()->GetVisualizer();
				 if(!vis) return;

				 VisApp::Interface::LocalDataQuerry ldq;
				 if(vis->PickLayersAt(ldq, mp) != VisApp::Interface::iVisualizer::Error::NoError)
					 return;

				 if(ldq.table.empty()) return;
				 auto insp = GetDataInspector();
				 insp->SetData(ldq);
				 insp->Show();
			 }
	private: System::Void panelRender_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
				 timerShowDataInspector->Enabled = false;
				 m_WhenToShowDataInspector = 0;
			 }
	private: System::Void panelRender_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 panelRender->Focus();
				 if(Settings::root().DataInspector.Use)
					 timerShowDataInspector->Enabled = true;
			 }
	private: System::Void contextMenuStripRenderer_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				 e->Cancel = !CanRender();
			 }
	private: void ResetZoom() { 
				 if(FailIfNoRendering())
					 return;
				 GetRenderer()->GetCamera()->Center(NULL);
			 } 
	private: void HideAllLayers() {
				 if(FailIfNoRendering())
					 return;
				 for each(TreeNode ^node in treeViewLayers->Nodes) {
					 LayerTreeNode ^ltn = dynamic_cast<LayerTreeNode^>(node->Tag);
					 if(!ltn) continue;
					 ltn->Instance->SetVisibility(false);
				 }
			 } 

			 //miszung

	private: System::Void menuStrip_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
			 }
	private: System::Void ustawieniaToolStripMenuItem_DropDownOpened(System::Object^  sender, System::EventArgs^  e) {
				 zarzadzajProjektemToolStripMenuItem->Enabled = m_Project->get() != NULL;
			 }
};
}