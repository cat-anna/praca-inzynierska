/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/ProcessorConfigForm.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#include "Processor.h"
#pragma managed

namespace D2Mapper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace VisApp::Types;

	enum class SectionState {
		Enabled, Disabled, Forced,
	};

	/// <summary>
	/// Summary for ProcessorConfigForm
	/// </summary>
	public ref class ProcessorConfigForm : public System::Windows::Forms::Form {
	public:
		ProcessorConfigForm(System::Windows::Forms::Form^ OwnerForm, Processor *instance) 	{
			Owner = OwnerForm;
			InitializeComponent();
			m_NormInfos = new std::vector<const NormConfig::NormConf*>();
			m_instance = instance;
			m_config = &instance->GetConfig();
		}
	protected:
		~ProcessorConfigForm() {
			if (components) {
				delete components;
			}
			delete m_NormInfos;
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  labelSourceInfo;
	private: System::Windows::Forms::Label^  labelNormalizationInfo;
	private: System::Windows::Forms::ComboBox^  comboBoxNormalizationSelect;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownSectionCount;
	private: System::Windows::Forms::Label^  labelSectionsText;
	private: System::Windows::Forms::ComboBox^  comboBoxColorAlgo;
	private: System::Windows::Forms::Label^  labelColorAlgo;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBoxColorAlgo = (gcnew System::Windows::Forms::ComboBox());
			this->labelColorAlgo = (gcnew System::Windows::Forms::Label());
			this->labelNormalizationInfo = (gcnew System::Windows::Forms::Label());
			this->comboBoxNormalizationSelect = (gcnew System::Windows::Forms::ComboBox());
			this->numericUpDownSectionCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelSectionsText = (gcnew System::Windows::Forms::Label());
			this->labelSourceInfo = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSectionCount))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(162, 278);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Zamknij";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ProcessorConfigForm::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->comboBoxColorAlgo);
			this->groupBox1->Controls->Add(this->labelColorAlgo);
			this->groupBox1->Controls->Add(this->labelNormalizationInfo);
			this->groupBox1->Controls->Add(this->comboBoxNormalizationSelect);
			this->groupBox1->Controls->Add(this->numericUpDownSectionCount);
			this->groupBox1->Controls->Add(this->labelSectionsText);
			this->groupBox1->Location = System::Drawing::Point(12, 57);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(227, 215);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Metoda normalizacji wejœciowych danych";
			// 
			// comboBoxColorAlgo
			// 
			this->comboBoxColorAlgo->DisplayMember = L"2";
			this->comboBoxColorAlgo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxColorAlgo->FormattingEnabled = true;
			this->comboBoxColorAlgo->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Ci¹g³y", L"Losowy"});
			this->comboBoxColorAlgo->Location = System::Drawing::Point(6, 145);
			this->comboBoxColorAlgo->Name = L"comboBoxColorAlgo";
			this->comboBoxColorAlgo->Size = System::Drawing::Size(215, 21);
			this->comboBoxColorAlgo->TabIndex = 26;
			this->comboBoxColorAlgo->ValueMember = L"0";
			// 
			// labelColorAlgo
			// 
			this->labelColorAlgo->AutoSize = true;
			this->labelColorAlgo->Location = System::Drawing::Point(16, 129);
			this->labelColorAlgo->Name = L"labelColorAlgo";
			this->labelColorAlgo->Size = System::Drawing::Size(112, 13);
			this->labelColorAlgo->TabIndex = 25;
			this->labelColorAlgo->Text = L"Sposób wyboru koloru";
			// 
			// labelNormalizationInfo
			// 
			this->labelNormalizationInfo->Location = System::Drawing::Point(6, 69);
			this->labelNormalizationInfo->Name = L"labelNormalizationInfo";
			this->labelNormalizationInfo->Size = System::Drawing::Size(215, 51);
			this->labelNormalizationInfo->TabIndex = 24;
			this->labelNormalizationInfo->Text = L"Jeœli widzisz ten tekst to znaczy, ¿e autor wtyczki jest idiot¹ i nie przewidza³ " 
				L"jakiegoœ przypadku :)";
			// 
			// comboBoxNormalizationSelect
			// 
			this->comboBoxNormalizationSelect->DisplayMember = L"dupa";
			this->comboBoxNormalizationSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxNormalizationSelect->DropDownWidth = 300;
			this->comboBoxNormalizationSelect->FormattingEnabled = true;
			this->comboBoxNormalizationSelect->Location = System::Drawing::Point(6, 33);
			this->comboBoxNormalizationSelect->Name = L"comboBoxNormalizationSelect";
			this->comboBoxNormalizationSelect->Size = System::Drawing::Size(215, 21);
			this->comboBoxNormalizationSelect->TabIndex = 23;
			this->comboBoxNormalizationSelect->SelectedIndexChanged += gcnew System::EventHandler(this, &ProcessorConfigForm::comboBoxNormalizationSelect_SelectedIndexChanged);
			// 
			// numericUpDownSectionCount
			// 
			this->numericUpDownSectionCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->numericUpDownSectionCount->Location = System::Drawing::Point(121, 189);
			this->numericUpDownSectionCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000000, 0, 0, 0});
			this->numericUpDownSectionCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownSectionCount->Name = L"numericUpDownSectionCount";
			this->numericUpDownSectionCount->Size = System::Drawing::Size(76, 20);
			this->numericUpDownSectionCount->TabIndex = 22;
			this->numericUpDownSectionCount->ThousandsSeparator = true;
			this->numericUpDownSectionCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// labelSectionsText
			// 
			this->labelSectionsText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->labelSectionsText->AutoSize = true;
			this->labelSectionsText->Location = System::Drawing::Point(26, 191);
			this->labelSectionsText->Name = L"labelSectionsText";
			this->labelSectionsText->Size = System::Drawing::Size(89, 13);
			this->labelSectionsText->TabIndex = 21;
			this->labelSectionsText->Text = L"Iloœæ przedzia³ów";
			// 
			// labelSourceInfo
			// 
			this->labelSourceInfo->AutoSize = true;
			this->labelSourceInfo->Location = System::Drawing::Point(13, 24);
			this->labelSourceInfo->Name = L"labelSourceInfo";
			this->labelSourceInfo->Size = System::Drawing::Size(103, 13);
			this->labelSourceInfo->TabIndex = 6;
			this->labelSourceInfo->Text = L"Info o Ÿródle danych";
			// 
			// ProcessorConfigForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(249, 306);
			this->Controls->Add(this->labelSourceInfo);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ProcessorConfigForm";
			this->Text = L"Konfiguracja preprocesora warstwy";
			this->Shown += gcnew System::EventHandler(this, &ProcessorConfigForm::ProcessorConfigForm_Shown);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownSectionCount))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	protected:
		volatile bool m_SaveDisabled;
		Processor *m_instance;
		ConfigData *m_config;
		std::vector<const NormConfig::NormConf*> *m_NormInfos;

	private: void SetColorAlgoSelection(bool enable) {
				 comboBoxColorAlgo->Visible = enable;
				 labelColorAlgo->Visible = enable;
			 }

	private: System::Void ProcessorConfigForm_Shown(System::Object^  sender, System::EventArgs^  e) {
				 ReadConfig();
				 SetColorAlgoSelection(false);
			 }

	private: void SetSectionsState(SectionState st) {
				 switch (st)  {
				 case D2Mapper::SectionState::Forced:
					 //				 checkBoxEnableSections->Enabled = false;
					 //					 checkBoxEnableSections->Checked = true;
					 labelSectionsText->Enabled = true;
					 numericUpDownSectionCount->Enabled = true;
					 break;
				 case D2Mapper::SectionState::Enabled:
					 //					 checkBoxEnableSections->Enabled = true;
					 labelSectionsText->Enabled = true;
					 numericUpDownSectionCount->Enabled = true;
					 labelSectionsText->Enabled = true;
					 break;
				 case D2Mapper::SectionState::Disabled:
					 //				 checkBoxEnableSections->Enabled = false;
					 labelSectionsText->Enabled = false;
					 numericUpDownSectionCount->Enabled = false;
					 labelSectionsText->Enabled = false;
					 break;
				 }
			 }

	private: void ReadConfig() {
				 m_SaveDisabled = true;
				 m_instance->UpdateConfig();

				 numericUpDownSectionCount->Value = (unsigned)m_config->SectionCount;
				 m_NormInfos->clear();
				 int normindex = 0;
				 auto &norms = NormConfig::NormConfTable::Get();
				 auto Outmode = m_config->Mode;
				 auto currNorMode = m_config->Normalization;

				 auto srcType = m_config->SrcDataPtr.Channel->GetType();

				 for(auto &it: norms) {
					 if(it.Alogrithm != Outmode)
						 continue;

					 if(!it.AllowedTypes.Test(srcType))
						 continue;

					 m_NormInfos->push_back(&it);

					 if(currNorMode == it.Normalization) {
						 normindex = m_NormInfos->size() - 1;
					 }
				 }

				 switch (m_config->Mode) {
				 case OutMode::Isolines:
					// SetColorAlgoSelection(false);
					 break;
				 case OutMode::Map:
					// SetColorAlgoSelection(true);
					 comboBoxColorAlgo->SelectedIndex = static_cast<int>(m_config->ColorMode) + 1;
					 break;
				 }

				 comboBoxNormalizationSelect->BeginUpdate();
				 comboBoxNormalizationSelect->Items->Clear();
				 for(auto *it: *m_NormInfos) {
					 comboBoxNormalizationSelect->Items->Add(gcnew String(it->Info.Name));
				 }
				 comboBoxNormalizationSelect->EndUpdate();

				 comboBoxNormalizationSelect->SelectedIndex = normindex;

				 labelSourceInfo->Text = "Typ danych wejœciowych: " + gcnew String(srcType.ToString().c_str());
				 m_SaveDisabled = false;
				 comboBoxNormalizationSelect_SelectedIndexChanged(nullptr, nullptr);
			 }

	private: void WriteConfig() {
				 if(m_SaveDisabled) return;
				 m_config->SectionCount = Decimal::ToUInt32(numericUpDownSectionCount->Value);
				 int index = comboBoxNormalizationSelect->SelectedIndex;
				 if(index < 0) {
					 //There should be some fail!
					 return;
				 }
				 auto *mode = m_NormInfos->at(index);
				 m_config->Normalization = mode->Normalization;
				 if(m_config->Mode == OutMode::Map)
					 m_config->ColorMode = static_cast<ColorSelectionMode>(comboBoxColorAlgo->SelectedIndex - 1);
				 labelNormalizationInfo->Text = gcnew String(mode->Info.Description);
				 SetSectionsState(mode->Info.Sections ? SectionState::Enabled : SectionState::Disabled);
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 WriteConfig();
			 }
	private: System::Void comboBoxNormalizationSelect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 WriteConfig();
			 }
			 // miszung

	};

	class GuiHandler : public VisApp::Plugins::CLIGuiHandler {
	public:
		GuiHandler(Processor *instance) {
			m_instance = instance;
		}
		virtual GuiResult OpenGui(System::Windows::Forms::Form^ Owner) {
			auto form = gcnew D2Mapper::ProcessorConfigForm(Owner, m_instance);
			form->ShowDialog();
			return GuiResult::Ok;
		}
	private:
		Processor *m_instance;
	};

}
