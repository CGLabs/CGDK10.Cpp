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
group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::array(size_t _max_member) :
	m_count_member(0),
	m_enable_enter(false)
{
	this->process_set_member_capacity(_max_member);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::~array() noexcept
{
	this->leave_all();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_set_member_capacity(size_t _max_count)
{
	// 1) 최대 Member수를 설정한다.
	this->m_count_max_member = _max_count; 
	
	// 2) 새로 할당한다.
	this->m_container_member.assign(_max_count, member_set_t(this));

	// 3) Member Seat번호는 GMD에 미리 써놓는다.
	for(size_t i=0; i<_max_count; ++i)
	{
		this->m_container_member.at(i).member_serial(i);
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<_TMEMBERBASE> group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::find_member(const std::function<bool (_TMEMBERBASE*)>& _pred)
{
	scoped_lock(this->m_lockable_group)
	{
		auto iter_count = this->member_count();

		for(auto iter = this->m_container_member.begin(); iter_count > 0; ++iter)
		{
			// check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).empty());

			// 1) execute함수를 실행한다.
			bool result = _pred(iter->member());

			// check) 
			RETURN_IF(result == true, iter->member());

			--iter_count;
		}
	}

	// return) 찾지 못했다..
	return object_ptr<_TMEMBERBASE>();
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::for_each_member(const std::function<bool (_TMEMBERBASE*)>& _function)
{
	scoped_lock(this->m_lockable_group)
	{
		auto iter_count = this->member_count();

		for(auto iter = this->m_container_member.begin(); iter_count > 0; ++iter)
		{
			// check) Member가 비어 있으면 넘어간다.
			CONTINUE_IF((*iter).empty());

			// 1) execute함수를 실행한다.
			bool result = _function(iter->member());

			// check) 
			RETURN_IF(result == false, false);

			--iter_count;
		}
	}

	// return) 성공...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data_t& group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data(const member_t* _pmember)
{
	// return) 현재 Member Data를 즉시 Return한다.		
	return ((member_set_t*)_pmember->member_set())->m_member_data;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enter(member_t* /*_pmember*/, param_t& /*_param*/)
{
	throw throwable::failure(eRESULT::ACCESS_DENIED);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_is_enable_member_enter() const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(this->m_lockable_enter);

		// return) 
		return m_enable_enter;
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enable_member_enter(bool _enable)
{
	scoped_lock(m_lockable_enter)
	{
		// check) 
		RETURN_IF(m_enable_enter == _enable, false);

		// 1) 값을 설정
		m_enable_enter = _enable;

		// 2) OnOpen을 호출한다.
		if(_enable)
		{
			on_enable_enter();
		}
		else
		{
			on_disable_enter();
		}
	}

	// return) 
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member(member_t* _pmember, group_member_id_t _seat, param_t& _param)
{
	// declare) 
	object_ptr<member_t> pmember_old;

	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(m_lockable_enter)
	{
		// check) 이미 현 Group의 멤버이면서 Seat까지 같은가?
		RETURN_IF(_pmember->_is_member_of(this) == true && (member_serial(_pmember) == _seat), object_ptr<member_t>());

		// check) Enter가능한 상태인가?
		RETURN_IF(m_enable_enter == false, object_ptr<member_t>());

		// check) 방이 꽉 찼는가?
		RETURN_IF(this->is_member_full(), object_ptr<member_t>());

		// 1) _process_member_entering()함수를 호출한다.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) 입장 조건에 맞지 않는다!
		RETURN_IF(result != eRESULT::SUCCESS, object_ptr<member_t>());

		// 2) 현재 Seat에 붙어 있는 object를 떼낸다.
		pmember_old = this->leave_by_seat(_seat);

		// 3) 부모 Group에서 떼낸다.(이거 잘못하면 Dead Lock이 걸릴 수 있으므로 주의해야 함.)
		if(_pmember != nullptr)
		{
			_pmember->leave_group();
		}

		scoped_lock(this->m_lockable_group)
		{
			// 4) 값을 읽어온다.
			auto& rSeat = this->m_container_member.at(_seat);

			// 5) Node에 _pmember을 설정한다.
			rSeat = _pmember;

			// check) _pmember가 nullptr이면 if안에 내용은 실행하지 않는다.
			RETURN_IF(_pmember == nullptr, pmember_old)

			// 6) 숫자를 하나 늘린다.
			++this->m_count_member;

			// 7) Seat Info를 Push한다..
			_pmember->member_set(&rSeat);

			// 8) _pmember의 Group을 설정함.
			this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);
			
			// 9) ProcessMemberEntered를 호출한다.
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception) rollback한다.
			catch(std::exception& _e)
			{
				// trace)
				LOG_FATAL << "(excp) group: exception complete[on_member_entered]"sv;

				// - exceeption complete
				bool is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - Node를 reset한다.
				rSeat.reset_member();

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - Seat Info를 pop한다.
				_pmember->reset_member_set();

				// - ObejctGroup를 nullptr로 설정한다.
				Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// check) 
				RETURN_IF(is_executed, object_ptr<member_t>());

				// reraise) 
				throw;
			}
			// exception) rollback한다.
			catch (...)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				bool is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - Node를 reset한다.
				rSeat.reset_member();

				// - 숫자를 줄인다.
				--this->m_count_member;

				// - Seat Info를 pop한다.
				_pmember->reset_member_set();

				// - ObejctGroup를 nullptr로 설정한다.
				Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// check) 
				RETURN_IF(is_executed, object_ptr<member_t>());

				// reraise) 
				throw;
			}
		}
	}

	// Result) 어쨌든 Success!!!
	return pmember_old;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_all(uintptr_t _param) noexcept
{
	scoped_lock(this->m_lockable_group)
	{
		size_t i = 0;

		for(auto iter = this->m_container_member.begin(); i < this->member_count();)
		{
			// check) nullptr이면 다음...
			CONTINUE_IF((*iter).empty());

			// 1) Member를 Leave한다.
			(*(iter++))->leave_group(_param);

			// 2) 증가...
			++i;
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember이 nullptr인가?
	CGASSERT_ERROR(_pmember != nullptr)

	//1) Leave한다.
	object_ptr<member_t> pobject = this->leave_by_seat(member_serial(_pmember), _param);

	// check) pobject와 _pmember는 반드시 같아야 한다.
	CGASSERT_ERROR(pobject == _pmember);
}


template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_by_seat(group_member_id_t _seat, uintptr_t _param) noexcept
{
	// check) _seat의 범위가 제대로 되었는가?
	RETURN_IF(_seat<0 || _seat >= static_cast<group_member_id_t>(this->member_capacity()), object_ptr<member_t>());
	
	// declare) 
	object_ptr<member_t> pmember;

	// 1) _seat위치의 pmember를 먼저 얻어온다.
	scoped_lock(this->m_lockable_group)
	{
		pmember = this->m_container_member.at(_seat).member();
	}

	// check) 
	RETURN_IF(pmember.empty(), object_ptr<member_t>());

	scoped_lock(this->member_group_lock(pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) pmember는 반드시 _seat의 값과 동일해야 한다.
			RETURN_IF(pmember != this->m_container_member.at(_seat).member(), object_ptr<member_t>());
			
			// 2) on_member_leaving()함수를 호출한다.
			result = this->_process_member_leaving(pmember, _param);

			// 3) Seat값을 얻어온다.
			auto& rSeat = this->m_container_member.at(_seat);

			// 4) Seat의 Node를 nullptr을 한다.
			rSeat.reset_member();

			// 5) Seat Info를 pop한다.
			pmember->reset_member_set();

			// 6) pmember의 Group을 해제함.
			Igroup<_TMEMBERBASE>::reset_member_group(pmember);

			// 7) Socket 숫자를 하나 줄인다.
			--this->m_count_member;
		}
		
		// 8) _process_member_leaved()함수를 호출한다.
		try
		{
			this->_process_member_leaved(pmember, result);
		}
		// exception) 
		catch(std::exception& _e)
		{
			// - Log
			LOG_FATAL << "(excp) occure exception in 'on_meber_leaved' function on group"sv;

			// - exceeption complete
			throwable::execute_exception_handler(this, _e, __FUNCTION__);
		}
		catch (...)
		{
			// - Log
			LOG_FATAL << "(excp) occure exception in 'on_meber_leaved' function on group"sv;

			// - exceeption complete
			throwable::execute_exception_handler(this, __FUNCTION__);
		}
	}

	// Result) Success!!!
	return pmember;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member(group_member_id_t _seat)
{
	scoped_lock(this->m_lockable_group)
	{
		// check) 만약에 _seat가 0보다 작거나 Size()보다 크면 그냥 nullptr을 Return한다.
		RETURN_IF(_seat<0 || _seat>=static_cast<group_member_id_t>(this->m_container_member.size()), object_ptr<member_t>());

		// return) pmember를 Return한다.
		return this->m_container_member.at(_seat).member();
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	return this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering함수를 호출한다.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
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
	return result;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
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