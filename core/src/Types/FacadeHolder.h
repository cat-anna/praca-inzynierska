/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Types/FacadeHolder.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace VisApp {
namespace Impl {
namespace Types {

template <class T>
class FacadeInstance : public T {
public:
	template <class OWNER>
	FacadeInstance(const OWNER* owner) : T(const_cast<OWNER*>(owner)) {}
	FacadeInstance() : T() {}
	virtual ~FacadeInstance() {} 
};

template <class T>
class FacadeHolder {
public:
	FacadeHolder(): m_Inst(0) { }
	~FacadeHolder() { delete m_Inst; }

	template <class OWNER>
	T* GetInstance(OWNER *owner) const {
		if(!m_Inst)
			m_Inst = new FacadeInstance<T>(owner);
		return m_Inst;
	}

	T* GetInstance() const {
		if(!m_Inst)
			m_Inst = new FacadeInstance<T>();
		return m_Inst;
	}
private:
	mutable FacadeInstance<T> *m_Inst;
};

} //namespace Types
} //namespace Impl
} //namespace VisApp
