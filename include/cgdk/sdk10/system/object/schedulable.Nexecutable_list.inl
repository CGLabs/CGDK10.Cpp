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
// schedulable::Nexecutable_list
//
//
//-----------------------------------------------------------------------------
template <class TEXECUTABLE>
class schedulable::Nexecutable_list<TEXECUTABLE>::ITERATOR
{
public:
			ITERATOR(std::shared_mutex& _cs, typename schedulable::Nexecutable_list<TEXECUTABLE>::CONTAINER& _container) noexcept : m_lockable_lock(_cs, std::adopt_lock), m_iter(_container.begin()), m_iter_end(_container.end()) {}

public:
			bool				is_continue() const noexcept { return this->m_iter != this->m_iter_end;}
			bool				is_ended() const noexcept { return this->m_iter == this->m_iter_end;}
			bool				move_next() noexcept { if(this->m_iter == this->m_iter_end) return false; ++this->m_iter; return true;}

			void				operator++() noexcept { ++this->m_iter;}
			TEXECUTABLE*		operator->() const noexcept { return *this->m_iter;}
			TEXECUTABLE*		operator*() const noexcept { return *this->m_iter;}

public:
	std::unique_lock<std::shared_mutex> m_lockable_lock;
	typename CONTAINER::iterator m_iter;
	typename CONTAINER::iterator m_iter_end;
};

template <class TEXECUTABLE>
schedulable::Nexecutable_list<TEXECUTABLE>::Nexecutable_list()
{
	scoped_lock(this->m_lockable_list_executable)
	{
		this->m_iter_now = this->m_list_executable.end();
	}
}

template <class TEXECUTABLE>
schedulable::Nexecutable_list<TEXECUTABLE>::~Nexecutable_list() noexcept
{
	// 1) free all executable
	scoped_lock(this->m_lockable_list_executable)
	{
		this->m_list_executable.clear();
	}
}

template <class TEXECUTABLE>
bool schedulable::Nexecutable_list<TEXECUTABLE>::register_executable(TEXECUTABLE* _pexecutable)
{
	scoped_lock(this->m_lockable_list_executable)
	{
		// 1) find executable object
		auto iter_end = this->m_list_executable.end();
		auto iter = std::find(this->m_list_executable.begin(), iter_end, _pexecutable);

		// check)
		RETURN_IF(iter != iter_end, false);

		// 2) add
		this->m_list_executable.emplace_back(_pexecutable);

		// 3) ...
		if(this->m_iter_now == iter_end)
		{
			this->m_iter_now = this->m_list_executable.end();
		}
	}

	// return)
	return true;
}

template <class TEXECUTABLE>
bool schedulable::Nexecutable_list<TEXECUTABLE>::unregister_executable(TEXECUTABLE* _pexecutable) noexcept
{
	scoped_lock(this->m_lockable_list_executable)
	{
		// 1) find executable object
		auto iter = std::find(this->m_list_executable.begin(), this->m_list_executable.end(), _pexecutable);

		// check) 
		RETURN_IF(iter == this->m_list_executable.end(), false);

		// 2) except on process
		if(this->m_iter_now == iter)
		{
			++this->m_iter_now;
		}

		// 3) Áö¿î´Ù.
		this->m_list_executable.erase(iter);
	}

	// return)
	return true;
}

template <class TEXECUTABLE>
void schedulable::Nexecutable_list<TEXECUTABLE>::unregister_executable_all() noexcept
{
	// declare) 
	CONTAINER list_executable;

	// 1) swap
	scoped_lock(this->m_lockable_list_executable)
	{
		list_executable.swap(this->m_list_executable);
	}

	// 2) remove all
	list_executable.clear();
}

template <class TEXECUTABLE>
typename schedulable::Nexecutable_list<TEXECUTABLE>::ITERATOR schedulable::Nexecutable_list<TEXECUTABLE>::get_iterator() const
{
	return ITERATOR(m_lockable_list_executable, this->m_list_executable);
}

template <class TEXECUTABLE>
size_t schedulable::Nexecutable_list<TEXECUTABLE>::executable_count() const noexcept
{
	scoped_lock(this->m_lockable_list_executable)
	{
		return this->m_list_executable.size();
	}
}

template <class TEXECUTABLE>
bool schedulable::Nexecutable_list<TEXECUTABLE>::empty() const noexcept
{
	scoped_lock(this->m_lockable_list_executable)
	{
		return this->executable_count() == 0;
	}
}

template <class TEXECUTABLE>
bool schedulable::Nexecutable_list<TEXECUTABLE>::exist() const noexcept
{
	return !this->empty();
}

template <class TEXECUTABLE>
intptr_t schedulable::Nexecutable_list<TEXECUTABLE>::process_execute(intptr_t _return, size_t _param)
{
	// declare) 
	std::vector<object_ptr<Iexecutable>> vector_executable;

	// 1) copy temporary executable
	scoped_lock(this->m_lockable_list_executable)
	{
		vector_executable.reserve(this->m_list_executable.size());

		for (auto& iter : this->m_list_executable)
		{
			vector_executable.push_back(iter);
		}
	}

	// 2) execute copyed executable
	for (auto& iter : vector_executable)
	{
		iter->process_execute(_return, _param);;
	}

	// return) 
	return intptr_t(0);
}


}