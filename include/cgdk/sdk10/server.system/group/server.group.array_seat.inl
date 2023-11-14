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

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::array_seat(size_t _max_member) :
	m_seat(_max_member),
	m_enable_enter(false),
	m_count_member(0)
{
	this->process_set_member_capacity(_max_member);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::~array_seat() noexcept
{
	this->leave_all();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_set_member_capacity(size_t _max_count)
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(this->m_lockable_group);

		// 1) 최대 Member수를 설정한다.
		this->m_count_max_member = _max_count;

		// 2) 새로 할당한다.
		this->m_container_member.assign(_max_count, member_set_t(this));

		// 3) Member Seat번호는 GMD에 미리 써놓는다.
		for (size_t i = 0; i < _max_count; ++i)
		{
			this->m_container_member.at(i).member_serial(i);
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
typename group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data_t& group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data(const member_t* _pmember)
{
	// return) 현재 Member Data를 즉시 Return한다.		
	return ((member_set_t*)_pmember->member_set())->m_member_data;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<_TMEMBERBASE> group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::find_member(const std::function<bool (_TMEMBERBASE*)>& _pred)
{
	scoped_lock(this->m_lockable_group)
	{
		auto count = this->member_count();

		for(auto iter = this->m_container_member.begin(); count > 0; ++iter)
		{
			// check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).empty());

			// 1) execute함수를 실행한다.
			auto result = _pred(iter->member());

			// check) 
			RETURN_IF(result == true, iter->member());

			--count;
		}
	}

	// return) 성공...
	return object_ptr<_TMEMBERBASE>();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::for_each_member(const std::function<bool (_TMEMBERBASE*)>& _function)
{
	scoped_lock(this->m_lockable_group)
	{
		auto count = this->member_count();

		for(auto iter = this->m_container_member.begin(); count > 0; ++iter)
		{
			// check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).empty());

			// 1) execute함수를 실행한다.
			auto result = _function(iter->member());

			// check) 
			RETURN_IF(result == false, false);

			--count;
		}
	}

	// return) 성공...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_attach_member(member_t* _pmember)
{
	// 1) 숫자를 하나 늘린다.(이걸 제일 먼저 한다.)
	++this->m_count_member;

	// 2) Seat를 얻는다.
	auto seat_index = this->m_seat.alloc_seat();

	// check) seat_index가 0보다 작을 수는 없다.
	CGASSERT_ERROR(seat_index >= 0);

	// check)
	THROW_IF(seat_index < 0, throwable::failure(eRESULT::OUT_OF_RANGE));

	// 3) 값을 읽어온다.
	auto& rSeat = this->m_container_member.at(static_cast<size_t>(seat_index));

	// 4) Seat의 Node를 nullptr을 한다.
	rSeat.member(_pmember);

	// 6) Seat Info를 Push한다.
	_pmember->member_set(&rSeat);

	// 7) _pmember의 Group을 설정함.(이것을 제일 마지막에 한다.)
	this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_detach_member(member_base_t* _pmember) noexcept
{
	// 1) Seat Serial을 잠시 저장해 놓는다.
	auto seat_index = this->member_serial(_pmember);

	// check) seat_index값이 0보다는 커야한다.
	CGASSERT_ERROR(seat_index >= 0);

	// check)
	RETURN_IF(seat_index < 0);

	// 2) 값을 읽어온다.
	auto& rSeat = this->m_container_member.at(static_cast<size_t>(seat_index));

	// check) _pmember와 Seat에 있는 Object가 같은 것이어야 한다.
	CGASSERT_ERROR(rSeat == _pmember);

	// 3) Seat Info를 pop한다.
	_pmember->reset_member_set();

	// 4) _pmember의 Group을 해제함.(이걸 제일 먼저 한다.)
	this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

	// 5) Seat의 Node를 nullptr을 한다.
	rSeat.reset_member();

	// 6) Seat번호를 돌려준다.
	this->m_seat.free_seat(seat_index);

	// 7) Socket 숫자를 하나 줄인다.(이걸 제일 마지막에 한다.)
	--this->m_count_member;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_is_enable_member_enter() const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_enter));

		// return) 
		return this->m_enable_enter;
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enable_member_enter(bool _enable)
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

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember가 nullptr인가?
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);

	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) _pmember가 이미 Member인가?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) _Enter할 수 있는 상태인가?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// check) 이미 꽉 찼는가?
		RETURN_IF(this->is_member_full(), eRESULT::MEMBER_FULL);

		// 1) _process_member_entering함수를 호출한다.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) 입장 조건에 맞지 않는다!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 2) 이전 Group에서 떼낸다.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 3) attach한다.
			_attach_member(_pmember);

			// 4) ProcessMemberEntered함수를 호출한다.
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception) rollback한다.
			catch(std::exception& _e)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - Seat Info를 pop한다.
				this->_detach_member(_pmember);

				// - execute_exception_handler에서 처리되었으면 Reraise시키지 않는다.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
			// exception) rollback한다.
			catch(...)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - Seat Info를 pop한다.
				this->_detach_member(_pmember);

				// - execute_exception_handler에서 처리되었으면 Reraise시키지 않는다.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}
	
	// return) 성공이닷!!!
	return eRESULT::SUCCESS;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_all() noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(this->m_lockable_group);

		auto count = this->member_count();

		for(auto iter = this->m_container_member.begin(); count > 0;)
		{
			// check) nullptr이면 다음...
			CONTINUE_IF((*iter).empty());

			// 1) Member를 Leave한다.
			(*(iter++))->leave_group();

			// 2) 증가...
			--count;
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember가 nullptr인가?
	CGASSERT_ERROR(_pmember != nullptr);

	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember가 이 Group에 Member인가?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) ProcessMemberLeaving()함수를 호출한다.
			result = this->_process_member_leaving(_pmember, _param);

			// 2) detach한다.
			this->_detach_member(_pmember);
		}

		// 3) _process_member_leaved 함수를 호출한다.
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
}


template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_by_seat(group_member_id_t _seat, uintptr_t _param) noexcept
{
	// check) _seat의 범위가 제대로 되었는가?
	RETURN_IF(_seat<0 || _seat >= static_cast<group_member_id_t>(this->member_capacity()), object_ptr<member_t>());

	// declare) 
	object_ptr<member_t> pmember;

	// 1) _seat 자리의 Member를 먼저 얻는다.
	scoped_lock(this->m_lockable_group)
	{
		pmember = this->m_container_member.at(_seat).member();
	}

	// check) pmember가 empty면 그냥 끝낸다.
	RETURN_IF(pmember.empty(), object_ptr<member_t>());

	scoped_lock(this->member_group_lock(pmember))
	{
		// declare) 
		uintptr_t result = 0;
	
		scoped_lock(this->m_lockable_group)
		{
			// check) 
			RETURN_IF(pmember != this->m_container_member.at(_seat).member(), object_ptr<member_t>());

			// 1) on_member_leaving()함수를 호출한다.
			try
			{
				result = this->on_member_leaving(pmember, _param);
			}
			// exception) 
			catch(std::exception& _e)
			{
				// log) 
				LOG_FATAL << "(excp) occure exception in 'on_meber_leaving' function on group"sv;

				// - exceeption complete
				throwable::execute_exception_handler(this, _e, __FUNCTION__);
			}
			// exception) 
			catch (...)
			{
				// log) 
				LOG_FATAL << "(excp) occure exception in 'on_meber_leaving' function on group"sv;

				// - exceeption complete
				throwable::execute_exception_handler(this, __FUNCTION__);
			}

			// 2) pmember를 떼낸다.
			this->_detach_member(pmember);

			// 3) Member count를 하나 줄인다.
			--this->m_count_member;
		}

		// 4) _process_member_leaved()함수를 호출한다.
		try
		{
			this->_process_member_leaved(pmember, result);
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

	// return)
	return	pmember;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member(group_member_id_t _seat) noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(this->m_lockable_group);

		// check) 만약에 _seat가 0보다 작거나 Size()보다 크면 그냥 nullptr을 Return한다.
		RETURN_IF(_seat < 0 || _seat>=static_cast<group_member_id_t>(this->m_container_member.size()), object_ptr<member_t>());

		// return) pmember를 Return한다.
		return this->m_container_member.at(static_cast<size_t>(_seat)).member();
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	return this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entered함수를 호출한다.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// declare)
	uintptr_t result = 0;

	try
	{
		// 1) on_member_leaving함수를 호출한다.
		result = this->on_member_leaving(_pmember, _param);
	}
	catch (throwable::failure& _e)
	{
		result = _e.reason<uintptr_t>();
	}
	catch(...)
	{
		result = static_cast<uintptr_t>(eRESULT::FAIL);
	}

	// return) 
	return	result;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
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