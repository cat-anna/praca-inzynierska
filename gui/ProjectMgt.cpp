/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/ProjectMgt.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "ProjectMgt.h"
#include "MainForm.h"

namespace VisApp {
namespace gui {

	void ProjectMgt::Show() {
		DoShow(::gui::MainForm::Instance(), ::gui::MainForm::Instance()->Project());
	}

}
}