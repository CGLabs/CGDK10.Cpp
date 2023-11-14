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
result_code group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember가 nullptr인가?
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);
	
	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) 이미 Member인가?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) Enter가 가능한 상태인가?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// check) 꽉 차 있는가?
		RETURN_IF(this->is_member_full(), eRESULT::MEMBER_FULL);

		// 1) _process_member_entering()함수를 호출한다.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) 입장 조건에 맞지 않는다!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 2) Add Reference한다.
		_pmember->add_ref();

		// 3) 이전 Group에서 떼낸다.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 4) Member count를 하나 줄인다.
			++this->m_count_member;

			// 5) _pmember의 Group을 설정함.
			this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);

			// 6) _process_member_entered()함수를 호출한다.
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

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - ObejctGroup를 nullptr로 설정한다.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member를 Release한다.
				_pmember->release();

				// check) throwable::execute_exception_handler에서 처리된 것이면 reraise하지 않는다.
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

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - ObejctGroup를 nullptr로 설정한다.
				this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// - Member를 Release한다.
				_pmember->release();

				// check) throwable::execute_exception_handler에서 처리된 것이면 reraise하지 않는다.
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
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember가 nullptr인가?
	CGASSERT_ERROR(_pmember != nullptr)

	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember가 현 Group의 Member인가?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) call on_member_leaving
			result = this->_process_member_leaving(_pmember, _param);

			// 2) _pmember의 Group을 Reset
			Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

			// 3) Member count수를 줄임.
			--this->m_count_member;
		}
		
		// 4) _process_member_leaved()함수를 호출한다.
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

	// 5) Release한다.(Release는 반드시 Critical Section 밖에서 한다.)
	_pmember->release();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
result_code group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	return	this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entered함수를 호출한다.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBERBASE>
uintptr_t group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// declare) 
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
void group::count<_TMEMBER, _TPARAM, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
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