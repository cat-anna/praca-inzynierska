/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Types/SynchronizedQueue.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace VisApp {
namespace Impl {
namespace Types {
	/*
template <class T>
class SynchronizedQueue : protected std::list<T> {
public:
	typedef std::list<T> BASE;

	SynchronizedQueue() : BASE() { }

	bool IsEmpty() const { return size() == 0; }

	void push_back(T t) {
		boost::mutex::scoped_lock l(m_Lock);
		BASE::push_back(t);
	}

	using BASE::front;
	using BASE::back;

	template <class FUN>
	void remove_if(FUN fun) {
		boost::mutex::scoped_lock l(m_Lock);
		remove_if(fun);
	}

	bool contain(const T t) const {
		boost::mutex::scoped_lock l(m_Lock);
		for(auto &i : *this)
			if(i == t)
				return true;
		return false;
	}

	void pop_front() {
		boost::mutex::scoped_lock l(m_Lock);
		BASE::pop_front();
	}
private:
	mutable boost::mutex m_Lock;
};
*/
} //namespace Types
} //namespace Impl
} //namespace VisApp
