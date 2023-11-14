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
group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::no_manage():
	m_enable_enter(false)
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::~no_manage()
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
bool group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_is_enable_member_enter() const noexcept
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
bool group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_enable_member_enter(bool _enable)
{
	scoped_lock(this->m_lockable_enter)
	{
		// check) 
		RETURN_IF(this->m_enable_enter == _enable, false);

		// 1) 값을 설정
		this->m_enable_enter = _enable;

		// 2) OnOpen을 호출한다.
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
result_code group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember가 nullptr이면 안됀다.
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);

	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) 이미 Member인가?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) 입장 가능한 상태인가?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// 1) _process_member_entering() 함수를 호출한다.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) 입장 조건에 맞지 않는다!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 2) Add Reference한다.
		_pmember->add_ref();

		// 3) 이전 Group에서 떼낸다.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 4) _pmember의 Group을 설정함.
			this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);

			// 5) ProcessMemberEntered()함수를 호출한다.
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception)
			catch(std::exception& _e)
			{
				// log)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - ObejctGroup를 nullptr로 설정한다.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member를 Release한다.
				_pmember->release();

				// check) throwable::execute_exception_handler에서 처리되었다면 Reraise를 호출하지 않는다. 
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
			// exception)
			catch (...)
			{
				// log)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - ObejctGroup를 nullptr로 설정한다.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member를 Release한다.
				_pmember->release();

				// check) throwable::execute_exception_handler에서 처리되었다면 Reraise를 호출하지 않는다. 
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}
	
	// Result) 어쨌든 Success!!!
	return eRESULT::SUCCESS;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember가 nullptr이어서는 안됀다.
	CGASSERT_ERROR(_pmember != nullptr)
	
	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember는 Member인가?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) ProcessMemberLeaving함수를 호출한다.
			result = this->_process_member_leaving(_pmember, _param);

			// 2) _pmember의 Group을 해제함.
			this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);
		}

		// 3) _process_member_leaved()함수를 호출한다.
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

	// 4) Release한다.(Release는 반드시 Critical Section 밖에서 한다.)
	_pmember->release();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
result_code group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	return this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
uintptr_t group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// Declare0 
	uintptr_t result = 0;

	try
	{
		// 1) on_member_leaving함수를 호출한다.
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
void group::no_manage<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
{
	try
	{
		// 1) on_member_leaved함수를 호출한다.
		this->on_member_leaved(_pmember, _result);
	}
	catch (...)
	{
	}
}


}