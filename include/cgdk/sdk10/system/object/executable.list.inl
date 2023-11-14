//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// executable::list
//
// 1. executable::list의 특징!
//    1) 여러개의 Executable을 list형태로 가지고 있으며 실행될 때 자신이 가진
//       Executable의 process_execute()를 호출해준다.
//
//-----------------------------------------------------------------------------
template <class TEXECUTABLE>
class executable::list<TEXECUTABLE>::ITERATOR
{
public:
	ITERATOR(lock_object& cs, const typename CONTAINER::iterator& _iter_begin, const typename CONTAINER::iterator& _iter_end) noexcept : m_lockable_lock(cs,std::adopt_lock), m_iter(_iter_begin), m_iter_end(_iter_end)	{}

public:
			bool				is_continue() const noexcept	{ return m_iter!=m_iter_end;}
			bool				is_ended() const noexcept		{ return m_iter==m_iter_end;}
			bool				move_next() noexcept			{ if(m_iter==m_iter_end) return false; ++m_iter; return true;}
																  
			void				operator++() noexcept			{ ++m_iter;}
			TEXECUTABLE*		operator->() const noexcept		{ return *m_iter;}
			TEXECUTABLE*		operator*() const noexcept		{ return *m_iter;}

public:
			std::unique_lock<lock_object>	m_lockable_lock;
	typename CONTAINER::iterator	m_iter;
	typename CONTAINER::iterator	m_iter_end;
};

template <class TEXECUTABLE>
executable::list<TEXECUTABLE>::list()
{
	this->set_object_type(eOBJECT_TYPE::EXECUTABLE_LIST);
}

template <class TEXECUTABLE>
executable::list<TEXECUTABLE>::~list() noexcept
{
	// 1) remove all
	scoped_lock(m_list_executable)
	{
		m_list_executable.clear();
	}
}

template <class TEXECUTABLE>
bool executable::list<TEXECUTABLE>::register_executable(TEXECUTABLE* _pexecutable)
{
	scoped_lock(m_list_executable)
	{
		// 1) find _pexecutable
		auto iter_end = m_list_executable.end();
		auto iter = std::find(m_list_executable.begin(), iter_end, _pexecutable);

		// check)
		RETURN_IF(iter!=iter_end, false);

		// 2) add
		m_list_executable.emplace_back(_pexecutable);
	}

	// return)
	return true;
}

template <class TEXECUTABLE>
bool executable::list<TEXECUTABLE>::unregister_executable(TEXECUTABLE* _pexecutable) noexcept
{
	scoped_lock(m_list_executable)
	{
		// 1) find object
		auto iter = std::find(m_list_executable.begin(), m_list_executable.end(), _pexecutable);

		// check)
		RETURN_IF(iter==m_list_executable.end(), false);

		// 2) erase 
		m_list_executable.erase(iter);
	}

	// return)
	return true;
}

template <class TEXECUTABLE>
void executable::list<TEXECUTABLE>::unregister_executable_all() noexcept
{
	// declare) 
	CONTAINER list_executable;

	// 1) swap
	scoped_lock(m_list_executable)
	{
		list_executable.swap(m_list_executable);
	}

	// 2) remove all
	list_executable.clear();
}

template <class TEXECUTABLE>
typename executable::list<TEXECUTABLE>::ITERATOR executable::list<TEXECUTABLE>::get_iterator() noexcept
{
	scoped_lock(m_list_executable)
	{
		return	ITERATOR(m_list_executable, m_list_executable.begin(), m_list_executable.end());
	}
}

template <class TEXECUTABLE>
size_t executable::list<TEXECUTABLE>::executable_count() const noexcept
{
	scoped_lock(m_list_executable)
	{
		return	m_list_executable.size();
	}
}

template <class TEXECUTABLE>
bool executable::list<TEXECUTABLE>::empty() const noexcept
{
	scoped_lock(m_list_executable)
	{
		return executable_count()==0;
	}
}

template <class TEXECUTABLE>
bool executable::list<TEXECUTABLE>::exist() const noexcept
{
	scoped_lock(m_list_executable)
	{
		return executable_count()!=0;
	}
}

template <class TEXECUTABLE>
intptr_t executable::list<TEXECUTABLE>::process_execute(intptr_t _return, size_t _param)
{
	// declare) 
	std::vector<object_ptr<TEXECUTABLE>>	vector_executable;

	// 1) copy 
	scoped_lock(m_list_executable)
	{
		vector_executable.reserve(m_list_executable.size());

		for (auto& iter: m_list_executable)
		{
			vector_executable.emplace_back(iter);
		}
	}

	// 2) 순회하며 실행한다.
	for(auto& iter: vector_executable)
	{
		(*iter)->process_execute(_return, _param);
	}

	// return) Success
	return	intptr_t(0);
}

template <class TEXECUTABLE>
void executable::list<TEXECUTABLE>::on_final_release() noexcept
{
	unregister_executable_all();
}


}
