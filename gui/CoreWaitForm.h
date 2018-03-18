/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CoreWaitForm.h
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
	/// Summary for CoreWaitForm
	/// </summary>
	public ref class CoreWaitForm : public System::Windows::Forms::Form
	{
	public:
//-----------------------------------------------------------------
		static ref class CoreWaitFormSettings {
		public:
			CoreWaitFormSettings() { }
			virtual ~CoreWaitFormSettings() { }

			virtual bool CheckFinish() { return false; }
		};

		CoreWaitForm(Form ^NewOwner, CoreWaitFormSettings^ Settings) {
			InitializeComponent();
			Helpers::ProcessFormIcon(this);
			m_Settings = Settings;
			Owner = NewOwner;
			timer1->Enabled = true;
		}
//-----------------------------------------------------------------
	protected: static ref class LibStatusChecker : public CoreWaitFormSettings {
			VisApp::Interface::iManager::eLibStatus m_DesiredStatus;
		public:
			LibStatusChecker(VisApp::Interface::iManager::eLibStatus DesiredStatus) {
				m_DesiredStatus = DesiredStatus;
			}
			virtual bool CheckFinish() override {
				return CoreMgt::GetCore()->GetStatus() == m_DesiredStatus;
			}
		};
	
	public: static void WaitForLibStatus(Form^ Owner, VisApp::Interface::iManager::eLibStatus DesiredStatus) {
			(gcnew CoreWaitForm(Owner, gcnew LibStatusChecker(DesiredStatus)))->ShowDialog(Owner);
		}

//-----------------------------------------------------------------
	private:
		CoreWaitFormSettings^ m_Settings;
//-----------------------------------------------------------------
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^ e) {
				 if(!CoreMgt::GetCore()) return;

				 if(m_Settings->CheckFinish()) 
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
			 }
//-----------------------------------------------------------------

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CoreWaitForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Timer^  timer1;
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
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 59);
			this->progressBar1->MarqueeAnimationSpeed = 1;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(259, 23);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(0, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(320, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Proszê czekaæ...";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &CoreWaitForm::timer1_Tick);
			// 
			// CoreWaitForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(321, 128);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"CoreWaitForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Proszê czekaæ";
			this->Load += gcnew System::EventHandler(this, &CoreWaitForm::CoreWaitForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void CoreWaitForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 Text = Application::ProductName;
				 progressBar1->Left = (ClientRectangle.Width - progressBar1->Width) / 2;
				 label1->Left = 0;
				 label1->Width = ClientRectangle.Width;
			 }
};

} // namespace gui
} // namespace VisApp
