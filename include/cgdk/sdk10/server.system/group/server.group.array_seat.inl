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

		// 1) �ִ� Member���� �����Ѵ�.
		this->m_count_max_member = _max_count;

		// 2) ���� �Ҵ��Ѵ�.
		this->m_container_member.assign(_max_count, member_set_t(this));

		// 3) Member Seat��ȣ�� GMD�� �̸� ����´�.
		for (size_t i = 0; i < _max_count; ++i)
		{
			this->m_container_member.at(i).member_serial(i);
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
typename group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data_t& group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data(const member_t* _pmember)
{
	// return) ���� Member Data�� ��� Return�Ѵ�.		
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
			// check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).empty());

			// 1) execute�Լ��� �����Ѵ�.
			auto result = _pred(iter->member());

			// check) 
			RETURN_IF(result == true, iter->member());

			--count;
		}
	}

	// return) ����...
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
			// check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).empty());

			// 1) execute�Լ��� �����Ѵ�.
			auto result = _function(iter->member());

			// check) 
			RETURN_IF(result == false, false);

			--count;
		}
	}

	// return) ����...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_attach_member(member_t* _pmember)
{
	// 1) ���ڸ� �ϳ� �ø���.(�̰� ���� ���� �Ѵ�.)
	++this->m_count_member;

	// 2) Seat�� ��´�.
	auto seat_index = this->m_seat.alloc_seat();

	// check) seat_index�� 0���� ���� ���� ����.
	CGASSERT_ERROR(seat_index >= 0);

	// check)
	THROW_IF(seat_index < 0, throwable::failure(eRESULT::OUT_OF_RANGE));

	// 3) ���� �о�´�.
	auto& rSeat = this->m_container_member.at(static_cast<size_t>(seat_index));

	// 4) Seat�� Node�� nullptr�� �Ѵ�.
	rSeat.member(_pmember);

	// 6) Seat Info�� Push�Ѵ�.
	_pmember->member_set(&rSeat);

	// 7) _pmember�� Group�� ������.(�̰��� ���� �������� �Ѵ�.)
	this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_detach_member(member_base_t* _pmember) noexcept
{
	// 1) Seat Serial�� ��� ������ ���´�.
	auto seat_index = this->member_serial(_pmember);

	// check) seat_index���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT_ERROR(seat_index >= 0);

	// check)
	RETURN_IF(seat_index < 0);

	// 2) ���� �о�´�.
	auto& rSeat = this->m_container_member.at(static_cast<size_t>(seat_index));

	// check) _pmember�� Seat�� �ִ� Object�� ���� ���̾�� �Ѵ�.
	CGASSERT_ERROR(rSeat == _pmember);

	// 3) Seat Info�� pop�Ѵ�.
	_pmember->reset_member_set();

	// 4) _pmember�� Group�� ������.(�̰� ���� ���� �Ѵ�.)
	this->Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

	// 5) Seat�� Node�� nullptr�� �Ѵ�.
	rSeat.reset_member();

	// 6) Seat��ȣ�� �����ش�.
	this->m_seat.free_seat(seat_index);

	// 7) Socket ���ڸ� �ϳ� ���δ�.(�̰� ���� �������� �Ѵ�.)
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

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_enter(member_base_t* _pmember, param_t& _param)
{
	// check) _pmember�� nullptr�ΰ�?
	RETURN_IF(_pmember == nullptr, eRESULT::INVALID_ARGUMENT);

	scoped_lock(this->member_group_lock(_pmember))
	scoped_lock(this->m_lockable_enter)
	{
		// check) _pmember�� �̹� Member�ΰ�?
		RETURN_IF(_pmember->_is_member_of(this) == true, eRESULT::ALEADY_EXIST);

		// check) _Enter�� �� �ִ� �����ΰ�?
		RETURN_IF(this->m_enable_enter == false, eRESULT::FAIL_DISABLED);

		// check) �̹� �� á�°�?
		RETURN_IF(this->is_member_full(), eRESULT::MEMBER_FULL);

		// 1) _process_member_entering�Լ��� ȣ���Ѵ�.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, result);

		// 2) ���� Group���� ������.
		_pmember->leave_group();

		scoped_lock(this->m_lockable_group)
		{
			// 3) attach�Ѵ�.
			_attach_member(_pmember);

			// 4) ProcessMemberEntered�Լ��� ȣ���Ѵ�.
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

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - Seat Info�� pop�Ѵ�.
				this->_detach_member(_pmember);

				// - execute_exception_handler���� ó���Ǿ����� Reraise��Ű�� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
			// exception) rollback�Ѵ�.
			catch(...)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				auto is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - Seat Info�� pop�Ѵ�.
				this->_detach_member(_pmember);

				// - execute_exception_handler���� ó���Ǿ����� Reraise��Ű�� �ʴ´�.
				RETURN_IF(is_executed, eRESULT::EXCEPTION);

				// reraise) 
				throw;
			}
		}
	}
	
	// return) �����̴�!!!
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
			// check) nullptr�̸� ����...
			CONTINUE_IF((*iter).empty());

			// 1) Member�� Leave�Ѵ�.
			(*(iter++))->leave_group();

			// 2) ����...
			--count;
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember�� nullptr�ΰ�?
	CGASSERT_ERROR(_pmember != nullptr);

	scoped_lock(this->member_group_lock(_pmember))
	{
		// declare) 
		uintptr_t result = 0;

		scoped_lock(this->m_lockable_group)
		{
			// check) _pmember�� �� Group�� Member�ΰ�?
			RETURN_IF(_pmember->_is_member_of(this) == false);

			// 1) ProcessMemberLeaving()�Լ��� ȣ���Ѵ�.
			result = this->_process_member_leaving(_pmember, _param);

			// 2) detach�Ѵ�.
			this->_detach_member(_pmember);
		}

		// 3) _process_member_leaved �Լ��� ȣ���Ѵ�.
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
	// check) _seat�� ������ ����� �Ǿ��°�?
	RETURN_IF(_seat<0 || _seat >= static_cast<group_member_id_t>(this->member_capacity()), object_ptr<member_t>());

	// declare) 
	object_ptr<member_t> pmember;

	// 1) _seat �ڸ��� Member�� ���� ��´�.
	scoped_lock(this->m_lockable_group)
	{
		pmember = this->m_container_member.at(_seat).member();
	}

	// check) pmember�� empty�� �׳� ������.
	RETURN_IF(pmember.empty(), object_ptr<member_t>());

	scoped_lock(this->member_group_lock(pmember))
	{
		// declare) 
		uintptr_t result = 0;
	
		scoped_lock(this->m_lockable_group)
		{
			// check) 
			RETURN_IF(pmember != this->m_container_member.at(_seat).member(), object_ptr<member_t>());

			// 1) on_member_leaving()�Լ��� ȣ���Ѵ�.
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

			// 2) pmember�� ������.
			this->_detach_member(pmember);

			// 3) Member count�� �ϳ� ���δ�.
			--this->m_count_member;
		}

		// 4) _process_member_leaved()�Լ��� ȣ���Ѵ�.
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

		// check) ���࿡ _seat�� 0���� �۰ų� Size()���� ũ�� �׳� nullptr�� Return�Ѵ�.
		RETURN_IF(_seat < 0 || _seat>=static_cast<group_member_id_t>(this->m_container_member.size()), object_ptr<member_t>());

		// return) pmember�� Return�Ѵ�.
		return this->m_container_member.at(static_cast<size_t>(_seat)).member();
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering�Լ��� ȣ���Ѵ�.
	return this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entered�Լ��� ȣ���Ѵ�.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// declare)
	uintptr_t result = 0;

	try
	{
		// 1) on_member_leaving�Լ��� ȣ���Ѵ�.
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
		// 1) on_member_leaved�Լ��� ȣ���Ѵ�.
		this->on_member_leaved(_pmember, _result);
	}
	catch (...)
	{
	}
}


}