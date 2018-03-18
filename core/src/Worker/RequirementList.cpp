/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Worker/RequirementList.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include <stdafx.h>
#include "Implementation.h"

namespace Worker {
namespace Mgt {


class LambdaRequirement : public Requirement {
public:
	LambdaRequirement(RequirementList* Owner, RequirementList::LambdaTextFun fun): Requirement(Owner), m_TestFun(fun) {}
protected:
	virtual bool DoTest() const {
		return m_TestFun();
	}
private:
	RequirementList::LambdaTextFun m_TestFun;
};



RequirementList::RequirementList():
	m_State(State::NotTested) {
}

RequirementList::~RequirementList() {
}

bool RequirementList::AreFullfiled() const {
	return m_State == State::Passed;
}

unsigned RequirementList::PerformTests() const {
	m_State = State::NotPassed;
	unsigned notpassed = 0;
	for(auto &i: m_List){
		bool r = i->PerformTest();
		if(!r)
			++notpassed;
	}
	if(notpassed == 0)
		m_State = State::Passed;
	return notpassed;
}

void RequirementList::AddRequirement(Requirement *R) {
	m_List.push_back(std::shared_ptr<Requirement>(R));
}
	
void RequirementList::AddLambdaRequirement(LambdaTextFun fun) {
	AddRequirement(new LambdaRequirement(this, fun));
}

} //namespace Mgt 
} //namespace Worker 
