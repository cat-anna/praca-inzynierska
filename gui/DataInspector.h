/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/DataInspector.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

#include <Helpers.h>

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DataInspector
	/// </summary>
	public ref class DataInspector : public System::Windows::Forms::Form {
		bool m_Standalone;
	public:
		DataInspector(void) {
			InitializeComponent();
			m_Standalone = false;
			Helpers::ProcessFormIcon(this);
		}
		bool IsStandalone() { return m_Standalone ; } 
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DataInspector()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel;











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
		void InitializeComponent(void) {
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(2, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(168, 30);
			this->panel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->button1->Location = System::Drawing::Point(90, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Oderwij";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DataInspector::button1_Click);
			// 
			// panel3
			// 
			this->panel3->AutoSize = true;
			this->panel3->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel3->Controls->Add(this->panel4);
			this->panel3->Controls->Add(this->panel2);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(2, 32);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(168, 32);
			this->panel3->TabIndex = 2;
			// 
			// panel4
			// 
			this->panel4->AutoSize = true;
			this->panel4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel4->Controls->Add(this->flowLayoutPanel);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(168, 22);
			this->panel4->TabIndex = 1;
			// 
			// flowLayoutPanel
			// 
			this->flowLayoutPanel->AutoScroll = true;
			this->flowLayoutPanel->AutoSize = true;
			this->flowLayoutPanel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->flowLayoutPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel->Margin = System::Windows::Forms::Padding(0);
			this->flowLayoutPanel->Name = L"flowLayoutPanel";
			this->flowLayoutPanel->Size = System::Drawing::Size(168, 22);
			this->flowLayoutPanel->TabIndex = 0;
			this->flowLayoutPanel->WrapContents = false;
			// 
			// panel2
			// 
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 22);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(168, 10);
			this->panel2->TabIndex = 0;
			// 
			// DataInspector
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(172, 66);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(300, 400);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(150, 100);
			this->Name = L"DataInspector";
			this->Padding = System::Windows::Forms::Padding(2);
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Data inspektor";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &DataInspector::DataInspector_FormClosing);
			this->MouseEnter += gcnew System::EventHandler(this, &DataInspector::DataInspector_MouseEnter);
			this->MouseLeave += gcnew System::EventHandler(this, &DataInspector::DataInspector_MouseLeave);
			this->panel1->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DataInspector_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
				 // Hide();
			 }
	private: System::Void DataInspector_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 //				 int i = 0;
			 }
	private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->ControlBox = true;
				 m_Standalone = true;
				 button1->Enabled = false;
			 }
	private: System::Void DataInspector_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if(e->CloseReason != CloseReason::UserClosing) {
					 e->Cancel = false;
					 return;
				 }
				 if(m_Standalone)
					 e->Cancel = false;
				 else {
					 e->Cancel = true;
					 Hide();
				 }
			 }

	private: static Label^ PushLabel(String ^Text, TableLayoutPanel ^parent, int row, int column) {
				 Label ^l = gcnew Label();
				 l->Text = Text;
				 l->AutoSize = true;
				 l->Width = 1;
				 l->Height = 1;
				 parent->Controls->Add(l, column, row);
				 l->Dock = DockStyle::Fill;
				 if(column == 0)
					l->TextAlign = ContentAlignment::MiddleRight;
				 else
					l->TextAlign = ContentAlignment::MiddleLeft;
				 l->Parent = parent;
				 return l;
			 }

	public: void SetData(const VisApp::Interface::LocalDataQuerry &inp) {
				flowLayoutPanel->Controls->Clear();
				Width = 150;
				Height = 100;
				flowLayoutPanel->SuspendLayout();
				unsigned w = 0;
				for(auto &it: inp.table) {
					Panel ^panel = gcnew Panel();
					panel->Width = flowLayoutPanel->ClientSize.Width;
					flowLayoutPanel->Controls->Add(panel);
					panel->Visible = true;
				//	panel->Parent = flowLayoutPanel;
				//	panel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
				//	panel->AutoSize = true;
					//panel->BackColor = Color::Red;a

					TableLayoutPanel ^tlp = gcnew TableLayoutPanel();
					panel->Controls->Add(tlp);
					tlp->Height = 30;
					tlp->Width = 30;
					tlp->ColumnCount = 2;
					int row = 2;
					tlp->RowCount = row + it.DataSources.size();
					tlp->CellBorderStyle = TableLayoutPanelCellBorderStyle::Single;
					//tlp->Dock = DockStyle::Top;
					tlp->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
					tlp->AutoSize = true;
				
					PushLabel(L"Warstwa", tlp, 0, 0);
					PushLabel(Helpers::ToString(it.layer->GetName()), tlp, 0, 1);
					PushLabel(L"Wspó³rzêdne", tlp, 1, 0);
					PushLabel(Helpers::ToString(VisApp::Math::vec2ws(it.DataCoords)), tlp, 1, 1);

					for(auto &jt: it.DataSources) {
						auto series = jt->GetSeries();
						unsigned count = series->GetChannelCount();
						PushLabel(L"Seria\n" + Helpers::ToString(series->GetName()), tlp, row, 0);

						TableLayoutPanel ^stlp = gcnew TableLayoutPanel();
						tlp->Controls->Add(stlp, 1, row);
						stlp->Height = 30;
						stlp->Width = 30;
						stlp->ColumnCount = 2;
						stlp->RowCount = count;
						stlp->CellBorderStyle = TableLayoutPanelCellBorderStyle::Single;
						stlp->Dock = DockStyle::Top;
						stlp->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
						stlp->AutoSize = true;

						for(unsigned kt = 0; kt < count; ++kt) {
							auto channel = series->GetChannel(kt);
							Label ^lc = PushLabel(Helpers::ToString(channel->GetName()), stlp, kt, 0);
							
							auto fmt = VisApp::Types::ConstructFormatter(channel);
							auto val = fmt->Format(it.DataCoords);
							Label ^lv = PushLabel(Helpers::ToString(val), stlp, kt, 1);

						//	lv->hint

							for(auto &lt: it.DataSources)
								if(lt == channel) {
									lc->Font = gcnew Drawing::Font(lc->Font, FontStyle::Bold);
									lv->Font = gcnew Drawing::Font(lv->Font, FontStyle::Bold);
									break;
								}
						}
						++row;
					}
					
					panel->Height = tlp->Height;
					panel->Width = tlp->Width;
				//	panel->Width = flowLayoutPanel->ClientSize.Width;
				}
			//	flowLayoutPanel->ResumeLayout();
				w = 0;
				flowLayoutPanel->ResumeLayout();
				for each (Control ^c in flowLayoutPanel->Controls)
					w = VisApp::Math::max(w, (unsigned)c->Width);
				for each (Control ^c in flowLayoutPanel->Controls){
			//		c->Controls[0]->AutoSize = false;
					c->Width = w;//flowLayoutPanel->ClientSize.Width;
				}

			/*	flowLayoutPanel->ClientSize.Width  = w;
				flowLayoutPanel->ClientSize.Width = flowLayoutPanel->ClientSize.Width;*/
/*				int d = w - fp;
				d += 10;
				Width += d;*/
			}
	};
}
