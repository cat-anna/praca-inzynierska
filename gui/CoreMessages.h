/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/CoreMessages.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace gui {
	public ref class CoreMessageParameters {
	public:
		String ^Message;
		VisApp::Interface::CoreMessageClass Class;

		CoreMessageParameters(const std::wstring &Msg, VisApp::Interface::CoreMessageClass MClass) {
			Class = MClass;
			Message = Helpers::ToString(Msg);
		}
	};
}
