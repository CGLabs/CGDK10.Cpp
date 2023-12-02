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

 @class		map
 @brief		
 @todo		
 @ref		
 @details	\n
 �Ϲ����� ���� Container�� ���� Observer ������.
 Array/Linked-List Container�� Observer�� �����Ѵ�.

*///-----------------------------------------------------------------------------
template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA=int64_t, class _observer_base_t=_TOBSERVER>
class observable::map :
	virtual public				Iobservable<_observer_base_t>
{
public:
	using key_t = _TKEY;
	using observer_channel_t = typename _observer_base_t::observer_channel_t;
	using observer_t = _TOBSERVER;
	using observer_base_t = _observer_base_t;
	using observer_data_t = _TOBSERVER_DATA;
	using observer_set_t = OBSERVER_SET_DATA<observer_t, observer_data_t>;
	using container_t = std::map<key_t, observer_set_t>;
	using iterator_t = typename container_t::iterator;
	using const_iterator_t = typename container_t::const_iterator;

public:
			map(size_t _max_observer = SIZE_MAX) noexcept;
	virtual	~map() noexcept;

public:
			result_code			subscribe(const _TKEY& _key, observer_t* _pobserver, observer_channel_t _ocid = 0)	{ observer_data_t temp_observer_data{}; return subscribe(_key, _pobserver, _ocid, temp_observer_data); }
	virtual	result_code			subscribe(const _TKEY& _key, observer_t* _pobserver, observer_channel_t _ocid, const observer_data_t& _observer_data);
	virtual	bool				unsubscribe(observer_t* _pobserver, observer_channel_t _ocid = 0) noexcept override;
	virtual	bool				unsubscribe(const _TKEY& _key) noexcept;
	virtual	void				unsubscribe_all() noexcept override;

	[[nodiscard]] static observer_data_t& get_observer_data(observer_t* _pobserver) { return *(observer_set_t*)Iobservable<_observer_base_t>::_get_object_data(_pobserver); }
			bool				update_observer_data(observer_t* _pobserver, observer_data_t& _observer_data, observer_channel_t _ocid = 0);
			bool				update_observer_data(const _TKEY& _key, observer_data_t& _observer_data, observer_channel_t _ocid = 0);

	[[nodiscard]] size_t		count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_count(); }
	[[nodiscard]] size_t		capacity() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_capacity(); }
			void				capacity(size_t _max_count);
	[[nodiscard]] size_t		room_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _get_observer_room_count(); }

	[[nodiscard]] bool			empty() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_empty(); }
	[[nodiscard]] bool			exist() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_exist(); }
	[[nodiscard]] bool			is_full() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_full(); }
	[[nodiscard]] bool			is_room() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_observable)); return _is_observer_room(); }

	[[nodiscard]] iterator_t	begin() noexcept { return m_container_observer.begin();}
	[[nodiscard]] const_iterator_t begin() const noexcept { return m_container_observer.begin();}
	[[nodiscard]] iterator_t	end() noexcept { return m_container_observer.end();}
	[[nodiscard]] const_iterator_t end() const noexcept { return m_container_observer.end();}

	[[nodiscard]] object_ptr<observer_t> find_observer(const key_t& _key) const noexcept;
	[[nodiscard]] object_ptr<observer_t> find_observer(const std::function<bool (observer_t*)>& _pred) const noexcept;

			bool				for_each(const std::function<bool (observer_t*)>& _function);

protected:
	virtual	result_code			on_observer_registering(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, observer_data_t& /*_observer_data*/){ return eRESULT::SUCCESS;}
	virtual	void				on_observer_registered(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, const observer_data_t& /*_observer_data*/) {}
	virtual	uintptr_t			on_observer_unregistering(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/) { return 0;}
	virtual	void				on_observer_unregistered(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, uintptr_t /*_result*/){}
	virtual	uintptr_t			on_observer_data_updating(observer_t* /*_pobserver*/, observer_channel_t /*_ocid*/, observer_data_t& /*_observer_data*/) { return 0; }
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

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::map(size_t _max_observer) noexcept :
	m_count_max_observer(_max_observer)
{
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::~map() noexcept
{
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
result_code observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::subscribe(const _TKEY& _key, _TOBSERVER* _pobserver, observer_channel_t _ocid, const observer_data_t& _observer_data)
{
	// check) _pobserver�� nullptr�̸� �ȉ´�.
	RETURN_IF(_pobserver == nullptr, eRESULT::INVALID_ARGUMENT);
	
	scoped_lock(_pobserver->m_vector_observable)
	scoped_lock(this->m_lockable_observable_enter)
	{
		// check) �� á�°�?
		RETURN_IF(is_full(), eRESULT::MEMBER_FULL);

		// declare) 
		observer_set_t temp_observer_set(_pobserver, _ocid, _observer_data);

		scoped_lock(this->m_lockable_observable)
		{
			// 1) �̹� ���� Observer�� �����ϴ��� Ȯ���Ѵ�.
			auto iter_find = m_container_observer.find(_key);

			// check) �̹� �پ� �ִٸ� ������.
			RETURN_IF(iter_find != m_container_observer.end(), eRESULT::NOT_EXIST);
		}

		// 2) on_observer_registering()�Լ��� ȣ���Ѵ�.
		auto result = this->on_observer_registering(_pobserver, _ocid, temp_observer_set.observer_data);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 3) ���� ocid�� ��ϵ� Observable�� ã�´�.
		_pobserver->_unsubscribe(_ocid);

		scoped_lock(this->m_lockable_observable)
		{
			// 4) �߰��Ѵ�.
			auto result_insert = m_container_observer.insert(std::make_pair(_key, temp_observer_set));

			// 5) pobserver�� �߰��Ѵ�.
			_pobserver->_add_observable(this, _ocid);

			// 6) observer_data ����
			this->_set_observer_data(_pobserver, &result_insert.first->second.observer_data);

			// 7) on_observer_registered()�Լ��� ȣ���Ѵ�.
			try
			{
				this->on_observer_registered(_pobserver, _ocid, temp_observer_set.observer_data);
			}
			// exception) rollback�Ѵ�.
			catch(std::exception& e)
			{
				// log)
				LOG_FATAL << "(excp) exception completeion[on_observer_registered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, e, __FUNCTION__);

				// - ����
				_pobserver->_popback_observable();

				// - Observer�� �����Ѵ�.
				m_container_observer.erase(_key);

				// 4) observer_data ����
				this->_reset_observer_data(_pobserver);

				// check) 
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}

	// return) �����̴�!!!
	return eRESULT::SUCCESS;
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::unsubscribe(_TOBSERVER* _pobserver, observer_channel_t _ocid) noexcept
{
	// check) _pobserver�� nullptr�̿����� �ȉ´�.
	CGASSERT_ERROR(_pobserver != nullptr);

	// check) _pobserver�� nullptr�̿����� �ȉ´�.
	RETURN_IF(_pobserver == nullptr, false);

	scoped_lock(_pobserver->m_vector_observable)
	scoped_lock(this->m_lockable_observable)
	{
		// declare) 
		uintptr_t result = 0;

		// declare) 
		typename container_t::iterator iter_find;

		// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
		for(auto iter_end= m_container_observer.end(); iter_find !=iter_end; ++iter_find)
		{
			BREAK_IF(iter_find->second.pobserver==_pobserver && iter_find->second.ocid==_ocid);
		}

		// check) ã�� �������� ������.
		RETURN_IF(iter_find==m_container_observer.end(), false);

		// 2) on_observer_unregistering()�Լ��� ȣ���Ѵ�.
		try
		{
			result = this->on_observer_unregistering(_pobserver, _ocid);
		}
		// exception) 
		catch(std::exception& /*_e*/)
		{
			LOG_FATAL << "(excp) occure exception in 'on_observer_unregistering' function on observer"sv;
		}

		// 2) �����Ѵ�.
		m_container_observer.erase(iter_find);

		// 3) �����Ѵ�.
		_pobserver->_erase_observable(_ocid);

		// 4) observer_data ����
		this->_reset_observer_data(_pobserver);

		// 5) on_observer_unregistered()�Լ��� ȣ���Ѵ�.
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

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::unsubscribe(const _TKEY& _key) noexcept
{
	// declare) 
	auto	pobserver = find_observer(_key);

	scoped_lock(pobserver->m_vector_observable)
	scoped_lock(this->m_lockable_observable)
	{
		// declare) 
		uintptr_t result = 0;

		// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
		auto iter_find = m_container_observer.find(_key);

		// check) ã�� �������� ������.
		RETURN_IF(iter_find==m_container_observer.end(), false);

		// declare)
		auto second = iter_find->second;

		// 2) on_observer_unregistering()�Լ��� ȣ���Ѵ�.
		try
		{
			result = this->on_observer_unregistering(second.pobserver, second.ocid);
		}
		// exception) 
		catch(std::exception& /*_e*/)
		{
			LOG_FATAL << "(excp) occure exception in 'on_observer_unregistering' function on observer"sv;
		}

		// 3) �����Ѵ�.
		m_container_observer.erase(iter_find);

		// 4) �����Ѵ�.
		second.pobserver->_erase_observable(second.ocid);

		// 5) observer_data ����
		this->_reset_observer_data(second.pobserver);

		// 6) on_observer_unregistered()�Լ��� ȣ���Ѵ�.
		try
		{
			this->on_observer_unregistered(second.pobserver, second.ocid, result);
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

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
void observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::unsubscribe_all() noexcept
{
	// declare) 
	container_t	vectorObserver;

	// 1) �����Ѵ�.
	scoped_lock(this->m_lockable_observable)
	{
		vectorObserver = m_container_observer;
	}

	// 2) ��� unregister�Ѵ�.
	for(auto& iter: vectorObserver)
	{
		unsubscribe(iter.ocid);
	}
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::update_observer_data(observer_t* _pobserver, observer_data_t& _observer_data, observer_channel_t _ocid)
{
	// check) _pobserver�� nullptr�̿����� �ȉ´�.
	CGASSERT_ERROR(_pobserver != nullptr);

	// declare) 
	uintptr_t	tempResult;

	scoped_lock(_pobserver->m_vector_observable)
	{
		scoped_lock(this->m_lockable_observable)
		{
			// declare) 
			typename container_t::iterator	iter_find;

			// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
			for (auto iter_end = m_container_observer.end(); iter_find != iter_end; ++iter_find)
			{
				BREAK_IF(iter_find->second.pobserver == _pobserver && iter_find->second.ocid == _ocid);
			}

			// check) ã�� �������� ������.
			RETURN_IF(iter_find == m_container_observer.end(), false);

			// 2) on_observer_unregistering()�Լ��� ȣ���Ѵ�.
			tempResult = this->on_observer_data_updating(_pobserver, _ocid, _observer_data);

			// 3) observer_data�� Update�Ѵ�.
			iter_find->set_observer_data(_observer_data);
		}

		// 3) Update...
		this->on_observer_data_update(_pobserver, _ocid, tempResult);
	}

	// return)
	return true;
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::update_observer_data(const _TKEY& _key, observer_data_t& _observer_data, observer_channel_t _ocid)
{
	// declare) 
	auto	pobserver	 = find_observer(_key);

	// declare) 
	uintptr_t	tempResult;

	scoped_lock(pobserver->m_vector_observable)
	{
		scoped_lock(this->m_lockable_observable)
		{
			// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
			auto	iter_find = m_container_observer.find(_key);

			// check) ã�� �������� ������.
			RETURN_IF(iter_find == m_container_observer.end(), false);

			// 2) on_observer_unregistering()�Լ��� ȣ���Ѵ�.
			tempResult = this->on_observer_data_updating(pobserver, _ocid, _observer_data);

			// 3) observer_data�� Update�Ѵ�.
			iter_find->set_observer_data(_observer_data);
		}

		// 3) Update...
		this->on_observer_data_update(pobserver, _ocid, tempResult);
	}

	// return)
	return true;
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
void observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::capacity(size_t _max_count)
{
	scoped_lock(this->m_lockable_observable)
	{
		// 1) �ִ� Observer���� �����Ѵ�.
		m_count_max_observer	 = _max_count;
	
		// 2) Reserve�Ѵ�.(Reserver�Լ��� ���� ��쿡��...)
	#if defined(_MSC_VER)
		__if_exists(container_t::reserve)
		{
			m_container_observer.reserve((_max_count>256) ? 256:_max_count);
		}
	#endif
	}
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
object_ptr<_TOBSERVER> observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::find_observer(const key_t& _key) const noexcept
{
	scoped_lock(this->m_lockable_observable)
	{
		// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
		auto		iter_find = m_container_observer.find(_key);

		// check) ã�� �������� ������.
		RETURN_IF(iter_find == m_container_observer.end(), object_ptr<_TOBSERVER>());

		// 2) ã�� Observer�� �����Ѵ�.
		return	iter_find->second.pobserver;
	}
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
object_ptr<_TOBSERVER> observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::find_observer(const std::function<bool (_TOBSERVER*)>& _pred) const noexcept
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter:m_container_observer)
		{
			// 1) execute�Լ��� �����Ѵ�.
			bool	result	 = _pred(iter);

			// check) 
			RETURN_IF(result==true, iter);
		}
	}

	// return) ã�� ���ߴ�..
	return	object_ptr<_TOBSERVER>();
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::for_each(const std::function<bool (_TOBSERVER*)>& _function)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter:m_container_observer)
		{
			// 1) execute�Լ��� �����Ѵ�.
			bool	result	 = _function(*iter);

			// check) 
			RETURN_IF(result==false, false);
		}
	}

	// return) ����...
	return true;
}


}