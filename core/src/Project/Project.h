/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/Project.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#ifndef Project_H
#define Project_H

namespace VisApp {
namespace Project {

class DataStore;

enum class SaveMode { Shallow, Deep, };
enum class ChangeReason { State, Data, };

class Project : public VisApp::Interface::iProject {
public:
	Project(const std::wstring &Location, const std::wstring &Name);//create
	Project(const std::wstring &File);//load
	virtual ~Project();
//iResource implementation
	//virtual iResource* GetOwnerResource();//default implemementation
//iProject implementation
	virtual const std::wstring &GetName() const;
	virtual Interface::iDataStore* GetDataStore() const;
	virtual void SaveProject();
	virtual Error SetName(const std::wstring &name);
	virtual bool IsVirtual() const;
	virtual Error SetLocation(const std::wstring &folder);
	virtual const std::wstring& GetLocation() const;
//public functions
	DataStore* GetDataStoreInstance() const { return m_DataStore.get(); }

	bool CanBeSaved() const;

	void DoSaveProject(SaveMode mode = SaveMode::Deep);
protected:
	std::wstring m_Name;
	std::wstring m_Location;
	std::wstring m_ProjFile;
	std::shared_ptr<xml_document> m_ProjDoc;

	std::auto_ptr<DataStore> m_DataStore;

	typedef std::function<Error()> SaveEvent;
	struct SaveAction {
		iResource *Requester;
		SaveEvent Action;
		SaveAction(iResource *ir, SaveEvent a): Requester(ir), Action(a) { }
	};
	typedef std::list<SaveAction> SaveActionList;

	SaveActionList m_SaveActions;

	void DoLoadProject(const std::wstring &File);
};

} //namespace Project
} //namespace VisApp

#endif
