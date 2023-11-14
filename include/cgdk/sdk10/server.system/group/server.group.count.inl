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

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::count(size_t _max_member) :
	m_enable_enter(false),
	m_count_member(0)
{
	this->process_set_member_capacity(_max_member);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::~count() noexcept
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
bool group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_is_enable_member_enter() const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_enter));

		// return) 
		return this->m_enable_enter;
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
bool group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_enable_member_enter(bool _enable)
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

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
result_code group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember�� nullptr�ΰ�?
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);
	
	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) �̹� Member�ΰ�?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) Enter�� ������ �����ΰ�?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// check) �� �� �ִ°�?
		RETURN_IF(this->is_member_full(), eRESULT::MEMBER_FULL);

		// 1) _process_member_entering()�Լ��� ȣ���Ѵ�.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 2) Add Reference�Ѵ�.
		_pmember->add_ref();

		// 3) ���� Group���� ������.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 4) Member count�� �ϳ� ���δ�.
			++this->m_count_member;

			// 5) _pmember�� Group�� ������.
			this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);

			// 6) _process_member_entered()�Լ��� ȣ���Ѵ�.
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception) Rollback
			catch(std::exception& _e)
			{
				// log)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member�� Release�Ѵ�.
				_pmember->release();

				// check) throwable::execute_exception_handler���� ó���� ���̸� reraise���� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
			// exception) Rollback
			catch (...)
			{
				// log)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member�� Release�Ѵ�.
				_pmember->release();

				// check) throwable::execute_exception_handler���� ó���� ���̸� reraise���� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}

	// Result) ��·�� Success!!!
	return eRESULT::SUCCESS;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember�� nullptr�ΰ�?
	CGASSERT_ERROR(_pmember != nullptr)

	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember�� �� Group�� Member�ΰ�?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) call on_member_leaving
			result = this->_process_member_leaving(_pmember, _param);

			// 2) _pmember�� Group�� Reset
			Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

			// 3) Member count���� ����.
			--this->m_count_member;
		}
		
		// 4) _process_member_leaved()�Լ��� ȣ���Ѵ�.
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
		// exception) 
		catch (...)
		{
			// log) 
			LOG_FATAL << "(excp) occure exception in 'on_meber_leaved' function on group"sv;

			// - exceeption complete
			throwable::execute_exception_handler(this, __FUNCTION__);
		}
	}

	// 5) Release�Ѵ�.(Release�� �ݵ�� Critical Section �ۿ��� �Ѵ�.)
	_pmember->release();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
result_code group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering�Լ��� ȣ���Ѵ�.
	return	this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entered�Լ��� ȣ���Ѵ�.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
uintptr_t group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
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
	return	result;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
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