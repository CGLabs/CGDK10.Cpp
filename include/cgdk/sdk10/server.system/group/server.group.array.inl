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
	// 1) �ִ� Member���� �����Ѵ�.
	this->m_count_max_member = _max_count; 
	
	// 2) ���� �Ҵ��Ѵ�.
	this->m_container_member.assign(_max_count, member_set_t(this));

	// 3) Member Seat��ȣ�� GMD�� �̸� ����´�.
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
			// check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).empty());

			// 1) execute�Լ��� �����Ѵ�.
			bool result = _pred(iter->member());

			// check) 
			RETURN_IF(result == true, iter->member());

			--iter_count;
		}
	}

	// return) ã�� ���ߴ�..
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
			// check) Member�� ��� ������ �Ѿ��.
			CONTINUE_IF((*iter).empty());

			// 1) execute�Լ��� �����Ѵ�.
			bool result = _function(iter->member());

			// check) 
			RETURN_IF(result == false, false);

			--iter_count;
		}
	}

	// return) ����...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data_t& group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_data(const member_t* _pmember)
{
	// return) ���� Member Data�� ��� Return�Ѵ�.		
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

		// 1) ���� ����
		m_enable_enter = _enable;

		// 2) OnOpen�� ȣ���Ѵ�.
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
		// check) �̹� �� Group�� ����̸鼭 Seat���� ������?
		RETURN_IF(_pmember->_is_member_of(this) == true && (member_serial(_pmember) == _seat), object_ptr<member_t>());

		// check) Enter������ �����ΰ�?
		RETURN_IF(m_enable_enter == false, object_ptr<member_t>());

		// check) ���� �� á�°�?
		RETURN_IF(this->is_member_full(), object_ptr<member_t>());

		// 1) _process_member_entering()�Լ��� ȣ���Ѵ�.
		auto result = this->_process_member_entering(_pmember, _param);

		// check) ���� ���ǿ� ���� �ʴ´�!
		RETURN_IF(result != eRESULT::SUCCESS, object_ptr<member_t>());

		// 2) ���� Seat�� �پ� �ִ� object�� ������.
		pmember_old = this->leave_by_seat(_seat);

		// 3) �θ� Group���� ������.(�̰� �߸��ϸ� Dead Lock�� �ɸ� �� �����Ƿ� �����ؾ� ��.)
		if(_pmember != nullptr)
		{
			_pmember->leave_group();
		}

		scoped_lock(this->m_lockable_group)
		{
			// 4) ���� �о�´�.
			auto& rSeat = this->m_container_member.at(_seat);

			// 5) Node�� _pmember�� �����Ѵ�.
			rSeat = _pmember;

			// check) _pmember�� nullptr�̸� if�ȿ� ������ �������� �ʴ´�.
			RETURN_IF(_pmember == nullptr, pmember_old)

			// 6) ���ڸ� �ϳ� �ø���.
			++this->m_count_member;

			// 7) Seat Info�� Push�Ѵ�..
			_pmember->member_set(&rSeat);

			// 8) _pmember�� Group�� ������.
			this->member_group_as((typename _TMEMBER::group_base_t*)this, _pmember);
			
			// 9) ProcessMemberEntered�� ȣ���Ѵ�.
			try
			{
				this->_process_member_entered(_pmember, _param);
			}
			// exception) rollback�Ѵ�.
			catch(std::exception& _e)
			{
				// trace)
				LOG_FATAL << "(excp) group: exception complete[on_member_entered]"sv;

				// - exceeption complete
				bool is_executed = throwable::execute_exception_handler(this, _e, __FUNCTION__);

				// - Node�� reset�Ѵ�.
				rSeat.reset_member();

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - Seat Info�� pop�Ѵ�.
				_pmember->reset_member_set();

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// check) 
				RETURN_IF(is_executed, object_ptr<member_t>());

				// reraise) 
				throw;
			}
			// exception) rollback�Ѵ�.
			catch (...)
			{
				// trace)
				LOG_FATAL << "(excp) exception complete[on_member_entered]"sv;

				// - exceeption complete
				bool is_executed = throwable::execute_exception_handler(this, __FUNCTION__);

				// - Node�� reset�Ѵ�.
				rSeat.reset_member();

				// - ���ڸ� ���δ�.
				--this->m_count_member;

				// - Seat Info�� pop�Ѵ�.
				_pmember->reset_member_set();

				// - ObejctGroup�� nullptr�� �����Ѵ�.
				Igroup<_TMEMBERBASE>::reset_member_group(_pmember);

				// check) 
				RETURN_IF(is_executed, object_ptr<member_t>());

				// reraise) 
				throw;
			}
		}
	}

	// Result) ��·�� Success!!!
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
			// check) nullptr�̸� ����...
			CONTINUE_IF((*iter).empty());

			// 1) Member�� Leave�Ѵ�.
			(*(iter++))->leave_group(_param);

			// 2) ����...
			++i;
		}
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_leave(member_base_t* _pmember, uintptr_t _param) noexcept
{
	// check) _pmember�� nullptr�ΰ�?
	CGASSERT_ERROR(_pmember != nullptr)

	//1) Leave�Ѵ�.
	object_ptr<member_t> pobject = this->leave_by_seat(member_serial(_pmember), _param);

	// check) pobject�� _pmember�� �ݵ�� ���ƾ� �Ѵ�.
	CGASSERT_ERROR(pobject == _pmember);
}


template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
object_ptr<typename group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::member_t> group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::leave_by_seat(group_member_id_t _seat, uintptr_t _param) noexcept
{
	// check) _seat�� ������ ����� �Ǿ��°�?
	RETURN_IF(_seat<0 || _seat >= static_cast<group_member_id_t>(this->member_capacity()), object_ptr<member_t>());
	
	// declare) 
	object_ptr<member_t> pmember;

	// 1) _seat��ġ�� pmember�� ���� ���´�.
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
			// check) pmember�� �ݵ�� _seat�� ���� �����ؾ� �Ѵ�.
			RETURN_IF(pmember != this->m_container_member.at(_seat).member(), object_ptr<member_t>());
			
			// 2) on_member_leaving()�Լ��� ȣ���Ѵ�.
			result = this->_process_member_leaving(pmember, _param);

			// 3) Seat���� ���´�.
			auto& rSeat = this->m_container_member.at(_seat);

			// 4) Seat�� Node�� nullptr�� �Ѵ�.
			rSeat.reset_member();

			// 5) Seat Info�� pop�Ѵ�.
			pmember->reset_member_set();

			// 6) pmember�� Group�� ������.
			Igroup<_TMEMBERBASE>::reset_member_group(pmember);

			// 7) Socket ���ڸ� �ϳ� ���δ�.
			--this->m_count_member;
		}
		
		// 8) _process_member_leaved()�Լ��� ȣ���Ѵ�.
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
		// check) ���࿡ _seat�� 0���� �۰ų� Size()���� ũ�� �׳� nullptr�� Return�Ѵ�.
		RETURN_IF(_seat<0 || _seat>=static_cast<group_member_id_t>(this->m_container_member.size()), object_ptr<member_t>());

		// return) pmember�� Return�Ѵ�.
		return this->m_container_member.at(_seat).member();
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
result_code group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entering(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering�Լ��� ȣ���Ѵ�.
	return this->on_member_entering(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) on_member_entering�Լ��� ȣ���Ѵ�.
	this->on_member_entered(_pmember, _param);
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
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
	return result;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::array<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaved(member_t* _pmember, uintptr_t _result) noexcept
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