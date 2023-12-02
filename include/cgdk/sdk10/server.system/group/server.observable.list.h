//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Socket template Classes                           *
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
/**

 @class		list
 @brief		
 @todo		
 @ref		
 @details	\n
 일반적인 선형 Container를 가진 Observer 관리자.
 Array/Linked-List Container로 Observer를 관리한다.

*///-----------------------------------------------------------------------------
template <class _TOBSERVER, class _TOBSERVER_DATA=int64_t, class _observer_base_t=_TOBSERVER>
class observable::list :
	virtual public				Iobservable<_TOBSERVER>
{
public:
	using observer_t = _TOBSERVER;
	using observer_channel_t = typename _observer_base_t::observer_channel_t;
	using observer_base_t = _observer_base_t;
	using observer_data_t = _TOBSERVER_DATA;
	using observer_set_t = OBSERVER_SET_DATA<observer_t, observer_data_t>;
	using container_t = circular_list<observer_set_t>;
	using iterator_t = typename container_t::iterator;
	using const_iterator_t = typename container_t::const_iterator;

public:
			list(size_t _max_observer = SIZE_MAX) noexcept;
	virtual	~list() noexcept;

public:
			result_code			subscribe(observer_t* _pobserver, observer_channel_t _ocid = 0)	{ observer_data_t temp_observer_data{}; return subscribe(_pobserver, _ocid, temp_observer_data); }
	virtual	result_code			subscribe(observer_t* _pobserver, observer_channel_t _ocid, const observer_data_t& _observer_data);
	virtual	bool				unsubscribe(observer_t* _pobserver, observer_channel_t _ocid = 0) noexcept override;
	virtual	void				unsubscribe_all() noexcept override;

	[[nodiscard]] static observer_data_t& get_observer_data(observer_t* _pobserver) { return *(observer_set_t*)Iobservable<_observer_base_t>::_get_object_data(_pobserver); }
			bool				update_observer_data(observer_t* _pobserver, observer_data_t& _observer_data, observer_channel_t _ocid = 0);

	[[nodiscard]] size_t		observer_count() const noexcept { return count();}
	[[nodiscard]] size_t		count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_count(); }
	[[nodiscard]] size_t		capacity() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_capacity(); }
			void				capacity(size_t _max_count);
	[[nodiscard]] size_t		room_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_room_count(); }

	[[nodiscard]] bool			is_full() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_full(); }
	[[nodiscard]] bool			empty() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_empty(); }
	[[nodiscard]] bool			is_room() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_room(); }
	[[nodiscard]] bool			exist() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_exist(); }

	[[nodiscard]] iterator_t	begin() noexcept { return m_container_observer.begin();}
	[[nodiscard]] const_iterator_t begin() const noexcept { return m_container_observer.begin();}
	[[nodiscard]] iterator_t	end() noexcept { return m_container_observer.end();}
	[[nodiscard]] const_iterator_t end() const noexcept { return m_container_observer.end();}

	[[nodiscard]] object_ptr<observer_t> find_observer(const std::function<bool (observer_t*)>& _pred) const noexcept;

			bool				for_each(const std::function<bool (observer_t*)>& _function);

protected:
	virtual	result_code			on_observer_registering(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, observer_data_t& /*_observer_data*/) { return eRESULT::SUCCESS;}
	virtual	void				on_observer_registered(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, const observer_data_t& /*_observer_data*/) {}
	virtual	uintptr_t			on_observer_unregistering(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/) { return 0;}
	virtual	void				on_observer_unregistered(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, uintptr_t /*_result*/) {}
	virtual	uintptr_t			on_observer_data_updating(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, observer_data_t& /*_observer_data*/) { return 0;}
	virtual	void				on_observer_data_update(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, uintptr_t /*_result*/) {}

private:
	[[nodiscard]] size_t		_get_observer_count() const noexcept { return m_container_observer.size();}
	[[nodiscard]] size_t		_get_observer_room_count() const noexcept { return m_count_max_observer-m_container_observer.size();}
	[[nodiscard]] size_t		_get_observer_capacity() const noexcept { return m_count_max_observer;}
																			  
	[[nodiscard]] bool			_is_observer_full() const noexcept { return m_container_observer.size()>=m_count_max_observer;}
	[[nodiscard]] bool			_is_observer_empty() const noexcept { return m_container_observer.empty();}
	[[nodiscard]] bool			_is_observer_room() const noexcept { return m_container_observer.size()<m_count_max_observer;}
	[[nodiscard]] bool			_is_observer_exist() const noexcept { return !m_container_observer.empty();}

protected:
			container_t			m_container_observer;
			size_t				m_count_max_observer;
};

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::list(size_t _max_observer) noexcept :
	m_count_max_observer(_max_observer)
{
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::~list() noexcept
{
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
result_code observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::subscribe(observer_t* _pobserver, observer_channel_t _ocid, const observer_data_t& _observer_data)
{
	// check) _pobserver가 nullptr이면 안됀다.
	RETURN_IF(_pobserver == nullptr, eRESULT::INVALID_ARGUMENT);
	
	scoped_lock(_pobserver->m_vector_observable)
	scoped_lock(this->m_lockable_observable_enter)
	{
		// check) 꽉 찼는가?
		RETURN_IF(is_full(), eRESULT::MEMBER_FULL);

		// declare) 
		observer_set_t observer_set(_pobserver, _ocid, _observer_data);

		// 1) 이미 존재하는지 확인한다.
		scoped_lock(this->m_lockable_observable)
		{
			for (auto& iter : m_container_observer)
			{
				// check) 이미 존재하면 끝낸다.
				RETURN_IF(iter == observer_set, eRESULT::ALEADY_EXIST);
			}
		}

		// 2) on_observer_registering()함수를 호출한다.
		auto result = this->on_observer_registering(_pobserver, _ocid, observer_set.observer_data);

		// check) 입장 조건에 맞지 않는다!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 3) 이전 ocid로 등록된 Observable을 찾는다.
		_pobserver->_unsubscribe(_ocid);

		scoped_lock(this->m_lockable_observable)
		{
			// 4) 추가한다.
			m_container_observer.push_back(observer_set);

			// 5) pobserver에 추가한다.
			_pobserver->_add_observable(this, _ocid);

			// 6) observer_data 설정
			this->_set_observer_data(_pobserver, &m_container_observer.back().observer_data);

			// 7) on_observer_registered()함수를 호출한다.
			try
			{
				this->on_observer_registered(_pobserver, _ocid, observer_set.observer_data);
			}
			// exception) rollback한다.
			catch(std::exception& e)
			{
				// log)
				LOG_FATAL << "(excp) exception completeion[on_observer_registered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, e, __FUNCTION__);

				// - observer_data 리셋
				this->_reset_observer_data(_pobserver);

				// - pobserver에 추가한다.
				_pobserver->_erase_observable(_ocid);

				// - Observer를 제거한다.
				m_container_observer.pop_back();

				// check) 
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}

	// return) 성공이닷!!!
	return	eRESULT::SUCCESS;
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::unsubscribe(observer_t* _pobserver, observer_channel_t _ocid) noexcept
{
	// check) _pobserver가 nullptr이여서는 안됀다.
	CGASSERT_ERROR(_pobserver != nullptr);
	
	scoped_lock(_pobserver->m_vector_observable)
	scoped_lock(this->m_lockable_observable)
	{
		// declare) 
		uintptr_t result = 0;

		// 1) find info
		auto iter_find = std::find(m_container_observer.begin(), m_container_observer.end(), observer_set_t(_pobserver, _ocid));

		// check) return if not found
		RETURN_IF(iter_find == m_container_observer.end(), false);

		// 2) remove from oberser
		_pobserver->_erase_observable(_ocid);

		// 3) call 'on_observer_unregistering()'
		try
		{
			result = this->on_observer_unregistering(_pobserver, _ocid);
		}
		// exception) 
		catch(std::exception& /*_8e*/)
		{
			LOG_FATAL << "(excp) occure exception in 'on_observer_unregistering' function on observer"sv;
		}

		// 4) 제거한다.
		m_container_observer.erase(iter_find);

		// 5) reset observer_data
		this->_reset_observer_data(_pobserver);

		// 6) call 'on_observer_unregistered()'
		try
		{
			this->on_observer_unregistered(_pobserver, _ocid, result);
		}
		// exception) 
		catch(std::exception& /*_e*/)
		{
			LOG_FATAL << "(excp) occure exception in 'on_observer_unregistered' function on observer"sv;
		}
	}

	// return) 
	return true;
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
void observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::unsubscribe_all() noexcept
{
	// declare) 
	container_t	vectorObserver;

	// 1) copy temporary
	scoped_lock(this->m_lockable_observable)
	{
		vectorObserver = m_container_observer;
	}

	// 2) unregister all
	for(auto& iter: vectorObserver)
	{
		unsubscribe(iter.pobserver);
	}
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::update_observer_data(observer_t* _pobserver, observer_data_t& _observer_data, observer_channel_t _ocid)
{
	// check) 
	CGASSERT_ERROR(_pobserver != nullptr);
	
	// declare) 
	uintptr_t result;

	scoped_lock(_pobserver->m_vector_observable)
	{
		scoped_lock(this->m_lockable_observable)
		{
			// 1) find registred observer
			auto iter_find = std::find(m_container_observer.begin(), m_container_observer.end(), observer_set_t(_pobserver, _ocid));

			// check) return if not info
			RETURN_IF(iter_find==m_container_observer.end(), false);

			// 2) call 'on_observer_unregistering()'
			result = this->on_observer_data_updating(_pobserver, _ocid, _observer_data);

			// 3) set observer_data
			iter_find->set_observer_data(_observer_data);
		}

		// 4) update...
		this->on_observer_data_update(_pobserver, _ocid, result);
	}

	// return)
	return true;
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
void observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::capacity(size_t _max_count)
{
	scoped_lock(this->m_lockable_observable)
	{
		// 1) set max observer
		m_count_max_observer = _max_count;
	
		// 2) reverve container
	#if defined(_MSC_VER)
		__if_exists(container_t::reserve)
		{
			m_container_observer.reserve((_max_count>256) ? 256:_max_count);
		}
	#endif
	}
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
object_ptr<_TOBSERVER> observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::find_observer(const std::function<bool (observer_t*)>& _pred) const noexcept
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter:m_container_observer)
		{
			// 1) call '_pred'
			bool result = _pred(iter);

			// check) 
			RETURN_IF(result == true, iter);
		}
	}

	// return)
	return object_ptr<observer_t>();
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::for_each(const std::function<bool (observer_t*)>& _function)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter:m_container_observer)
		{
			// 1) call '_function'
			bool result = _function(*iter);

			// check) 
			RETURN_IF(result == false, false);
		}
	}

	// return) 
	return true;
}


}