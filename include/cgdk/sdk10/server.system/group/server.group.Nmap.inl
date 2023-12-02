//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Group Template Classes                           *
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
namespace CGDK
{

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::Nmap(size_t _max_member) noexcept :
	m_enable_enter(false)
{
	process_set_member_capacity(_max_member);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::~Nmap() noexcept
{
	leave_all();
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_set_member_capacity(size_t _max_count)
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group));

		// 1) set max member
		m_count_max_member = _max_count;
	
	#if defined(_MSC_VER)
		__if_exists(container_t::reserve)
		{
			this->m_container_member.reserve((_max_count>256) ? 256:_max_count);
		}
	#endif
	}
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
typename group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data_t& group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data(const member_t* _pmember)
{
	// return)
	return ((member_set_t*)_pmember->member_set())->m_member_data;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<_TMEMBERBASE> group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::find_member(const std::function<bool (_TMEMBERBASE*)>& _pred)
{
	scoped_lock(this->m_lockable_group)
	{
		for(auto& iter:this->m_container_member)
		{
			// 1) call '_pred'
			bool result = _pred(*(iter.second));

			// check) 
			RETURN_IF(result == true, *iter.second);
		}
	}

	// return) ã�� ���ߴ�..
	return	object_ptr<member_t>();
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<_TMEMBER> group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::find_member(const _TKEY& _key) const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group));

		// 1) key�� �ش��ϴ� Member�� ã�´�.
		auto iter_find = this->m_container_member.find(_key);

		// check) ���� ������ �׳� nullptr�� �����Ѵ�.
		RETURN_IF(iter_find == this->m_container_member.end(), object_ptr<member_t>());

		// 2) ã������ ã�� �ɸ���
		return iter_find->second.member();
	}
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<_TMEMBER> group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::find_member(_TKEY&& _key) const noexcept
{
	return this->find_member(_key);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::for_each_member(const std::function<bool (_TMEMBERBASE*)>& _function)
{
	scoped_lock(this->m_lockable_group)
	{
		for(auto& iter:this->m_container_member)
		{
			// 1) execute�Լ��� �����Ѵ�.
			bool result = _function(iter.second.member());

			// check) 
			RETURN_IF(result == false, false);
		}
	}

	// return) ����...
	return true;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_attach_member(member_t* _pmember, const _TKEY& _key)
{
	// check) ���⼭ ���� ���� �����ϸ� �ȉ´�.
	CGASSERT_ERROR(this->m_container_member.find(_key)== this->m_container_member.end());

	// 2) �߰��Ѵ�.
	auto result = this->m_container_member.insert(std::make_pair(_key, member_set_t(this)));

	// 3) ���� �����Ѵ�.
	result.first->second.member(_pmember);

#if defined(_MSC_VER)
	result.first->second.iter = result.first;
#else
	result.first->second.key = _key;
#endif

	// 4) Seat Info�� Push�ϳ�.
	_pmember->member_set(&result.first->second);

	// 5) Object�� ����!
	this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_detach_member(member_base_t* _pmember) noexcept
{
	// 1) pMemberData�� ����.
	member_set_t* pmember_set = (member_set_t*)_pmember->member_set();

	// 2) Object�� ������.
#if defined(_MSC_VER)
	this->m_container_member.erase(pmember_set->iter);
#else
	this->m_container_member.erase(pmember_set->key);
#endif

	// 3) Seat Info�� pop�Ѵ�.
	_pmember->reset_member_set();

	// 4) ObejctGroup�� nullptr�� �����Ѵ�.
	this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_is_enable_member_enter() const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_enter));

		// return) 
		return this->m_enable_enter;
	}
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enable_member_enter(bool _enable)
{
	scoped_lock(this->m_lockable_enter)
	{
		// check) 
		RETURN_IF(this->m_enable_enter == _enable, false);

		// 1) ���� ����
		this->m_enable_enter = _enable;

		// 2) OnOpen�� ȣ���Ѵ�.
		if(_enable)
		{
			this->on_enable_enter();
		}
		else
		{
			this->on_disable_enter();
		}
	}

	// return) 
	return true;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember�� nullptr�ΰ�?
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);

	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) �̹� Member�ΰ�?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) Enter������ �����ΰ�?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// check) �� á�°�?
		RETURN_IF(this->is_member_full(), eRESULT::MEMBER_FULL);

		// 1) _pmember�� ���� key���� ��´�.
		auto key = this->process_get_member_key(_pmember);

		// declare)
		object_ptr<_TMEMBER> pmember_old;

		// 2) �ߺ��˻縦 �����Ѵ�.
		scoped_lock(this->m_lockable_group)
		{
			// - �̹� �ش� key�� �ش��ϴ� Member�� �����ϴ��� �˻��Ѵ�.
			auto iter_find = this->m_container_member.find(key);

			// check) �̹� �����ϸ�...
			if(iter_find != this->m_container_member.end())
			{
				pmember_old = iter_find->second.member();
			}
		}

		// 3) �ߺ��� Member�� ������ ���...
		if(pmember_old.exist())
		{
			// - on_member_duplicated()�Լ��� ȣ���Ѵ�.
			auto result = this->on_member_duplicated(key, _pmember, pmember_old, _param);

			// check) ���� ���ǿ� ���� �ʴ´�!
			RETURN_IF(result != eRESULT::SUCCESS, result);
		}

		// 1) _process_member_entering()�Լ��� ȣ���Ѵ�.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, result);
		
		// 2) ���� Group���� ������.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 3) old Member�� �����Ѵ�.
			if(pmember_old.exist())
			{
				this->process_leave(pmember_old, 0);
			}

			// 4) attach�Ѵ�.
			this->_attach_member(_pmember, key);

			// 4) on_member_entered()�Լ��� ȣ���Ѵ�. 
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception) rollback�Ѵ�.
			catch(std::exception& _e)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - Member�� ������.
				this->_detach_member(_pmember);

				// check) throwable::execute_exception_handler�Լ����� ó���� ������ �����Ǿ��ٸ� reraise���� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
			// exception) rollback�Ѵ�.
			catch (...)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - Member�� ������.
				this->_detach_member(_pmember);

				// check) throwable::execute_exception_handler�Լ����� ó���� ������ �����Ǿ��ٸ� reraise���� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}
	
	// return) �����̴�!!!
	return	eRESULT::SUCCESS;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_all() noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group));

		// 1) leave all members
		for(auto& iter:this->m_container_member)
		{
			(iter.second)->leave_group();
		}
	}
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember�� nullptr�̾�� �ȉ´�.
	CGASSERT_ERROR(_pmember != nullptr);

	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember�� Group�� �Ȱ��� ������?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) ProcessMemberLeaving()�Լ��� ȣ���Ѵ�.
			result = this->_process_member_leaving(_pmember, _param);

			// 2) detach�Ѵ�.
			this->_detach_member(_pmember);
		}

		// 3) _process_member_leaved()�Լ��� ȣ���Ѵ�.
		try
		{
			this->_process_member_leaved(_pmember, result);
		}
		// exception) 
		catch(std::exception& _e)
		{
			// log) 
			LOG_FATAL << "(excp) occure exception in 'on_meber_leaved' function on group"sv;

			// - exceeption complete
			throwable::execute_exception_handler(this, _e, __FUNCTION__);
		}
		// exception) rollback�Ѵ�.
		catch (...)
		{
			// log) 
			LOG_FATAL << "(excp) occure exception in 'on_meber_leaved' function on group"sv;

			// - exceeption complete
			throwable::execute_exception_handler(this, __FUNCTION__);
		}
	}
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering�Լ��� ȣ���Ѵ�.
	return	this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entered�Լ��� ȣ���Ѵ�.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// declare)
	uintptr_t result = 0;

	try
	{
		// 1) on_member_leaving�Լ��� ȣ���Ѵ�.
		result = this->on_member_leaving(_pmember, _param);
	}
	catch(...)
	{
		result = static_cast<uintptr_t>(eRESULT::FAIL);
	}

	// return)
	return result;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
{
	try
	{
		// 1) on_member_leaved�Լ��� ȣ���Ѵ�.
		this->on_member_leaved(_pmember, _result);
	}
	catch (...)
	{
	}
}


}