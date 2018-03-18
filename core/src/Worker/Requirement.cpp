/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/Requirement.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {
	
Requirement::Requirement(RequirementList *Owner):
		m_Owner(Owner), 
		m_State(State::NotTested) {
}

Requirement::~Requirement() {
}

bool Requirement::IsFullfiled() const {
	return m_State == State::Passed;
}

bool Requirement::PerformTest() const {
	m_State = State::NotPassed;
	bool r = DoTest();
	if(!r) return false;
	m_State = State::Passed;
	return true;
}

} //namespace Mgt 
} //namespace Worker 
