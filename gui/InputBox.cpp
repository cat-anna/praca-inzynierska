/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/InputBox.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "InputBox.h"
#include "Helpers.h"

namespace VisApp {
namespace gui {
	Windows::Forms::DialogResult InputBox(Form ^Owner, String ^promptText, String^ %value)
			{
				Form ^form = gcnew Form();
				Label ^label = gcnew Label();
				TextBox ^textBox = gcnew TextBox();
				Button ^buttonOk = gcnew Button();
				Button ^buttonCancel = gcnew Button();

				form->Text = Application::ProductName;
				label->Text = promptText;
				textBox->Text = value;
				form->Owner = Owner;
				buttonOk->Text = "OK";
				buttonCancel->Text = "Cancel";
				buttonOk->DialogResult = Windows::Forms::DialogResult::OK;
				buttonCancel->DialogResult = Windows::Forms::DialogResult::Cancel;

				label->SetBounds(9, 20, 372, 13);
				textBox->SetBounds(12, 36, 372, 20);
				buttonOk->SetBounds(228, 72, 75, 23);
				buttonCancel->SetBounds(309, 72, 75, 23);

				label->AutoSize = true;
				textBox->Anchor = textBox->Anchor | AnchorStyles::Right;
				buttonOk->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;
				buttonCancel->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;

				form->ClientSize = Drawing::Size(396, 107);
				form->Controls->AddRange(gcnew cli::array< Control^ >(4) { label, textBox, buttonOk, buttonCancel });
				form->ClientSize = Drawing::Size(Math::Max(300, label->Right + 10), form->ClientSize.Height);
				form->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedDialog;
				form->StartPosition = FormStartPosition::CenterParent;
				form->MinimizeBox = false;
				form->MaximizeBox = false;
				form->AcceptButton = buttonOk;
				form->CancelButton = buttonCancel;
				Helpers::ProcessFormIcon(form);
				Windows::Forms::DialogResult dialogResult = form->ShowDialog();
				value = textBox->Text;
				return dialogResult;
			}

}
}