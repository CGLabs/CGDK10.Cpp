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
 �Ϲ����� ���� Container�� ���� Object ������.
 Array/Linked-List Container�� object�� �����Ѵ�.

*///-----------------------------------------------------------------------------
template <class _TOBJECT, class _TOBJECT_DATA = int, class _TOBJECTBASE = _TOBJECT>
class container::list :
	virtual public				Iserver_container<_TOBJECT>
{
public:
	using object_t = _TOBJECT;
	using object_base_t = _TOBJECTBASE;
	using object_data_t = _TOBJECT_DATA;
	using object_set_t = OBJECT_SET_DATA<object_t, object_data_t>;
	using container_t = circular_list<object_set_t>;
	using iterator_t = typename container_t::iterator;
	using const_iterator_t = typename container_t::const_iterator;

public:
			result_code			register_object(object_t* _pobject) { object_data_t observer_data; return register_object(_pobject, observer_data);}
	virtual	result_code			register_object(object_t* _pobject, const object_data_t& _object_data);
	virtual	bool				unregister_object(object_t* _pobject) noexcept override;
	virtual	void				unregister_object_all() noexcept override;

	[[nodiscard]] size_t		count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _get_object_count(); }
	[[nodiscard]] size_t		capacity() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _get_max_object_count(); }
			void				capacity(size_t _max_count);
	[[nodiscard]] size_t		room_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _get_object_room_count();}

	[[nodiscard]] bool			empty() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _is_object_empty(); }
	[[nodiscard]] bool			exist() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _is_object_exist(); }
	[[nodiscard]] bool			is_full() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _is_object_full(); }
	[[nodiscard]] bool			is_room() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_container)); return _is_object_room(); }

	[[nodiscard]] iterator_t	begin() noexcept { return m_container_object.begin();}
	[[nodiscard]] const_iterator_t begin() const noexcept { return m_container_object.begin();}
	[[nodiscard]] iterator_t	end() noexcept { return m_container_object.end();}
	[[nodiscard]] const_iterator_t end() const noexcept { return m_container_object.end();}

	[[nodiscard]] object_ptr<object_t> find_object(const std::function<bool (object_t*)>& _pred) const noexcept;

			bool				for_each(const std::function<bool (object_t*)>& _function);

protected:
	virtual	result_code			on_object_registering (object_t* /*_pobject*/, const object_data_t& /*_object_data*/){ return eRESULT::SUCCESS;}
	virtual	void				on_object_registered (object_t* /*_pobject*/, const object_data_t& /*_object_data*/) {}
	virtual	uintptr_t			on_object_unregistering (object_t* /*_pobject*/) { return 0;}
	virtual	void				on_object_unregistered (object_t* /*_pobject*/, uintptr_t /*_result*/){}

private:
	[[nodiscard]] size_t		_get_object_count() const noexcept { return m_container_object.size();}
	[[nodiscard]] size_t		_get_object_room_count() const noexcept { return m_capacity- m_container_object.size();}
	[[nodiscard]] size_t		_get_max_object_count() const noexcept { return m_capacity;}
			
	[[nodiscard]] bool			_is_object_full() const noexcept { return m_container_object.size()>=m_capacity;}
	[[nodiscard]] bool			_is_object_empty() const noexcept { return m_container_object.empty();}
	[[nodiscard]] bool			_is_object_room() const noexcept { return m_container_object.size()<m_capacity;}
	[[nodiscard]] bool			_is_object_exist() const noexcept { return !m_container_object.empty();}

protected:
			container_t			m_container_object;
			size_t				m_capacity;
};

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
result_code container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::register_object(object_t* _pobject,const object_data_t& _object_data)
{
	// check) _pobject�� nullptr�̸� �ȉ´�.
	RETURN_IF(_pobject == nullptr, eRESULT::INVALID_ARGUMENT);
	
	scoped_lock(this->m_lockable_container_enter)
	{
		// check) �� á�°�?
		RETURN_IF(is_full(), eRESULT::MEMBER_FULL);

		// declare) 
		object_set_t temp_object_set(_pobject, _object_data);

		// 1) �̹� �����ϴ��� Ȯ���Ѵ�.
		scoped_lock(this->m_lockable_container)
		{
			for (auto& iter : m_container_object)
			{
				// check) �̹� �����ϸ� ������.
				RETURN_IF(iter == temp_object_set, eRESULT::ALEADY_EXIST);
			}
		}

		// 2) on_object_registering()�Լ��� ȣ���Ѵ�.
		auto result = on_object_registering(_pobject, _object_data);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		scoped_lock(this->m_lockable_container)
		{
			// 3) �߰��Ѵ�.
			m_container_object.push_back(temp_object_set);

			// 4) on_object_registered()�Լ��� ȣ���Ѵ�.
			try
			{
				on_object_registered(_pobject, _object_data);
			}
			// exception) rollback�Ѵ�.
			catch(std::exception& e)
			{
				// log)
				LOG_FATAL << "(excp) exception completeion[on_object_registered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, e, __FUNCTION__);

				// - object�� �����Ѵ�.
				m_container_object.pop_back();

				// check) 
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}

	// return) �����̴�!!!
	return	eRESULT::SUCCESS;
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::unregister_object(object_t* _pobject) noexcept
{
	// check) _pobject�� nullptr�̿����� �ȉ´�.
	CGASSERT_ERROR(_pobject != nullptr);
	
	scoped_lock(this->m_lockable_container)
	{
		// declare) 
		uintptr_t result = 0;

		// 1) ���� �̹� ��ϵǾ� �ִ��� ã�´�.
		auto iter_find = std::find(m_container_object.begin(), m_container_object.end(), object_set_t(_pobject));

		// check) ã�� �������� ������.
		RETURN_IF(iter_find== m_container_object.end(), false);

		// 2) on_object_unregistering()�Լ��� ȣ���Ѵ�.
		try
		{
			result = on_object_unregistering(_pobject);
		}
		// exception) 
		catch(std::exception& /*_8e*/)
		{
			LOG_FATAL << "(prgr) occure exception in 'on_object_unregistering' function on object"sv;
		}

		// 3) �����Ѵ�.
		m_container_object.erase(iter_find);

		// 4) on_object_unregistered()�Լ��� ȣ���Ѵ�.
		try
		{
			on_object_unregistered(_pobject, result);
		}
		// exception) 
		catch(std::exception& /*_e*/)
		{
			LOG_FATAL << "(prgr) occure exception in 'on_object_unregistered' function on object"sv;
		}
	}

	// return) 
	return true;
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
void container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::unregister_object_all() noexcept
{
	// declare) 
	container_t vector_object;

	// 1) �����Ѵ�.
	scoped_lock(this->m_lockable_container)
	{
		vector_object = m_container_object;
	}

	// 2) ��� unregister�Ѵ�.
	for(auto& iter: vector_object)
	{
		unregister_object(iter.pobject);
	}
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
void container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::capacity(size_t _max_count)
{
	scoped_lock(this->m_lockable_container)
	{
		// 1) �ִ� Object���� �����Ѵ�.
		m_capacity = _max_count;
	
		// 2) Reserve�Ѵ�.(Reserver�Լ��� ���� ��쿡��...)
	#if defined(_MSC_VER)
		__if_exists(container_t::reserve)
		{
			m_container_object.reserve((_max_count>256) ? 256:_max_count);
		}
	#endif
	}
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
object_ptr<_TOBJECT> container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::find_object(const std::function<bool (object_t*)>& _pred) const noexcept
{
	scoped_lock(this->m_lockable_container)
	{
		for(auto& iter: m_container_object)
		{
			// 1) execute�Լ��� �����Ѵ�.
			bool result = _pred(iter);

			// check) 
			RETURN_IF(result == true, iter);
		}
	}

	// return) ã�� ���ߴ�..
	return	object_ptr<object_t>();
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::for_each(const std::function<bool (object_t*)>& _function)
{
	scoped_lock(this->m_lockable_container)
	{
		for(auto& iter: m_container_object)
		{
			// 1) execute�Լ��� �����Ѵ�.
			bool result = _function(*iter);

			// check) 
			RETURN_IF(result == false, false);
		}
	}

	// return) ����...
	return true;
}


}