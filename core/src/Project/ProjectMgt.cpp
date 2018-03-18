/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/ProjectMgt.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "../Implementation.h"

namespace VisApp {
namespace Project {

using Interface::SharedProject;
using Interface::SharedProjectList;
using Interface::WeakProject;
using Interface::WeakProjectList;

class ProjectMgt : public Interface::iProjectMgt {
public:
	ProjectMgt() { }
 	~ProjectMgt() { }

	index_t ProjectCount() const { return m_Projects.size(); }

	SharedProject LoadProject(const std::wstring &FileName) {
		Project *prj = new Project(FileName);
		SharedProject sp(prj);
		m_Projects.push_back(sp);
		return sp;
	}

	SharedProject GetProject(const std::wstring &ProjectName) {
		for(auto &it: m_Projects)
			if(it->GetName() == ProjectName)
				return it;
		return SharedProject();
	}

	SharedProject GetProject(index_t index) {
		for(auto &it: m_Projects)
			if(index == 0)
				return it;
			else
				--index;
		return SharedProject();
	}

	SharedProject CreateProject(const std::wstring &ProjectName, const std::wstring &Location) {
		SharedProject sp(new Project(Location, ProjectName));
		m_Projects.push_back(sp);
		return sp;
	}

	void GetOpenedProjects(WeakProjectList& list) {
		list.clear();
		for(auto &it: m_Projects)
			list.push_back(WeakProject(it));
	}

	static std::auto_ptr<ProjectMgt>& GetInstance() {
		if(!_Instance.get()) _Instance.reset(new ProjectMgt());
		return _Instance;
	}

	virtual void CloseAllProjects() {
		for(auto &it: m_Projects) {
			Impl::CoreManager::InsertDelayedAction([it] {
				auto prj = std::dynamic_pointer_cast<Project>(it);
				prj->DoSaveProject(SaveMode::Deep);
				//TODO: do sth more?
			}, 0);
		}
		m_Projects.clear();
	}
protected:
	SharedProjectList m_Projects;
private:
	static std::auto_ptr<ProjectMgt> _Instance;
};

std::auto_ptr<ProjectMgt> ProjectMgt::_Instance(0);

//--------------------------------------------------------


} //namespace Project 

namespace Interface {

iProjectMgt* iProjectMgt::GetInstance() {
	return Project::ProjectMgt::GetInstance().get();
}

iProjectMgt::iProjectMgt() { }
iProjectMgt::~iProjectMgt() { }

} //namespace Interface 

} //namespace VisApp 
