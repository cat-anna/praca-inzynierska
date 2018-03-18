/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ImportTextFileForm.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "ImportTextFileForm.h"

namespace gui {



 System::Void ImportTextFileForm::buttonFieldDown_Click(System::Object^  sender, System::EventArgs^  e) {
				if(listViewFields->SelectedItems->Count < 1) return;
				int idx = listViewFields->SelectedItems[0]->Index;
				if(idx + 1 >= listViewFields->Items->Count) return;
				ListViewItem^ lvi = listViewFields->SelectedItems[0];
				listViewFields->Items->Remove(lvi);
				listViewFields->Items->Insert(idx + 1, lvi);
				lvi->Selected = true;
			}

 System::Void ImportTextFileForm::buttonFieldUp_Click(System::Object^  sender, System::EventArgs^  e) {
				if(listViewFields->SelectedItems->Count < 1) return;
				int idx = listViewFields->SelectedItems[0]->Index;
				if(idx < 1) return;
				ListViewItem^ lvi = listViewFields->SelectedItems[0];
				listViewFields->Items->Remove(lvi);
				listViewFields->Items->Insert(idx - 1, lvi);
				lvi->Selected = true;
			}			

} //namesapce gui