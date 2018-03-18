/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ImportDataItem.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#pragma once
#ifndef ImportDataItem_H
#define ImportDataItem_H

#include <Helpers.h>

namespace VisApp {
namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace VisApp::Plugins;

	using VisApp::Plugins::WeakImportDescriptor;

	ref class ImportInfo {
	public:
		WeakImportDescriptor *PluginDescriptor;

		String ^PluginName;
		String ^FileName;
		String ^SeriesName;

		enum class State {
			Ok, NotChecked, Checking, WrongPlugin, FatalError, FileError,
		};
		State state;

		std::shared_ptr<VisApp::Plugins::ImportPlugin>& GetInstance() { return *m_PluginInstance; }
		bool IsOk() { return state == State::Ok; }
		ListViewItem^ GetListItem() { return m_ListItem; }

		ImportInfo(ListView ^itemOwner) : state(State::NotChecked) {
			PluginDescriptor = new WeakImportDescriptor();
			m_PluginInstance = new std::shared_ptr<VisApp::Plugins::ImportPlugin>();
			m_StateText = "Plik nie jest sprawdzony";

			m_ItemListView = itemOwner;
			m_ListItem = m_ItemListView->Items->Add("?", -1);
			m_ListItem->Tag = this;
			for(int i = 0; i < 5; ++i) m_ListItem->SubItems->Add("?");
		}
		~ImportInfo() {
			delete PluginDescriptor;
			delete m_PluginInstance;
		}

		void PerformCheck() { System::Threading::Tasks::Task::Run(gcnew Action(this, &ImportInfo::PerformCheckFunc)); }
		void UpdateItem() { m_ItemListView->Invoke(gcnew Action(this, &ImportInfo::UpdateListItem)); } 

#if 0
		//def _DEBUG && 0
			std::shared_ptr<TextImportPlugin> castPlugin() {
				return std::dynamic_pointer_cast<TextImportPlugin>(GetInstance());
			}
			ImportInfo^ AddVariable(const wchar_t *vname, VisApp::Types::DataType type) {
				auto plugin = castPlugin();
				plugin->AddVariable(vname, type);
				return this;
			}
#endif
	private:
		VisApp::Plugins::SharedImportPlugin *m_PluginInstance;
		String ^m_StateText;
		ListViewItem ^m_ListItem;
		ListView ^m_ItemListView;

		void PerformCheckFunc() {
			m_StateText = "Analizowanie...";
			UpdateItem();
			using VisApp::Plugins::PreprocessResult;
			switch (GetInstance()->PreprocessFile()) {
			case PreprocessResult::Ok: 
				m_StateText = "Ok";
				state = State::Ok;
				break;
			case PreprocessResult::FileNotFound:
				m_StateText = "Plik nie istniejes";
				state = State::FatalError;
				break;
			case PreprocessResult::SyntaxError:
				m_StateText = "Plik posiada b³¹d sk³adni";
				state = State::FileError;
				break;
			case PreprocessResult::UnknownError:
				m_StateText = "Nieznany b³¹d";
				state = State::FatalError;
				break;
			case PreprocessResult::FunctionNotSupported:
				m_StateText = "Wtyczka nie obs³uguje wstêpnej analizy pliku";
				state = State::Ok;
				break;
			case PreprocessResult::FileNotPreprocessed:
				m_StateText = "Nieznany b³¹d";
				state = State::FatalError;
				break;
			}
			UpdateItem();
		}

		System::Void UpdateListItem() {
			String^ fn = Path::GetFileName(FileName);
			m_ListItem->SubItems[0]->Text = fn;
			m_ListItem->SubItems[1]->Text = SeriesName;
			m_ListItem->SubItems[2]->Text = Helpers::FileSizeToString(GetInstance()->GetFileSize());
			auto &ds = GetInstance()->GetDataSize3();
			if(ds[0] == 0 && ds[1] == 0 && ds[2] == 0)
				m_ListItem->SubItems[3]->Text = "?";
			else
				m_ListItem->SubItems[3]->Text = String::Format("{0}x{1}x{2}", ds[0], ds[1], ds[2]);
			m_ListItem->SubItems[4]->Text = PluginName;
			m_ListItem->SubItems[5]->Text = m_StateText;
		}
		};

	} //namespace gui 
}

#endif
