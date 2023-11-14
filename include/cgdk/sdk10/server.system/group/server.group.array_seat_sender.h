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

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
/**
 @class		array_seat_sender
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TPARAM = sMESSAGE, class _TMEMBER_DATA = int, class _TMEMBERBASE = _TMEMBER>
class group::array_seat_sender : 
	public						array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>,
	virtual public				net::io::Isender,
	virtual public				net::io::Isender_peer
{
public:
	using group_base_t = array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>;
	using member_t = _TMEMBER;
	using member_base_t = _TMEMBERBASE;
	using member_data_t = _TMEMBER_DATA;
	using param_t = _TPARAM;
	using container_t = typename group_base_t::container_t;
	using iterator_t = typename group_base_t::iterator_t;
	using const_iterator_t = typename group_base_t::const_iterator_t;

public:
			array_seat_sender(size_t _max_member = 256);
	virtual	~array_seat_sender() noexcept;

public:
	virtual	bool				send_to(int _index, const shared_buffer& _buffer, uint64_t _option = 0) override;
	virtual	bool				send_to(int _index, shared_buffer&& _buffer, uint64_t _option = 0) override;
	template<class T>
	typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
								send_to(int _index, const T& _data, uint64_t _option = 0);

			bool				send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	template<class T>
	typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
								send_except(member_t* _member_except, const T& _data, uint64_t _option = 0);

			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option = 0);
	template<class T>
	typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
								send_conditional(const T& _data, const std::function<bool (const member_t*)>& _pred, uint64_t _option = 0);

protected:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};


template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::array_seat_sender(size_t _max_member) :
	array_seat<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>(_max_member)
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::~array_seat_sender() noexcept
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_to(int _index, const shared_buffer& _buffer, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// declare)
	object_ptr<member_t> pmember;

	scoped_lock(this->m_lockable_group)
	{
		// check)
		RETURN_IF(_index < 0 || _index >= static_cast<int>(this->member_capacity()), false)

		// 1) get member
		pmember = this->member(_index);
	}

	// check)
	RETURN_IF(pmember.empty(), false);

	// 2) send to member
	pmember->process_send(shared_buffer(_buffer), 1, _option);

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_to(int _index, shared_buffer&& _buffer, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// declare)
	object_ptr<member_t> pmember;

	scoped_lock(this->m_lockable_group)
	{
		// check)
		RETURN_IF(_index < 0 || _index >= static_cast<int>(this->member_capacity()), false)

		// 1) get member
		pmember = this->member(_index);
	}

	// check)
	RETURN_IF(pmember.empty(), false);

	// 2) send to member
	pmember->process_send(std::move(_buffer), 1, _option);

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
template<class T>
typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_to(int _index, const T& _data, uint64_t _option)
{
	// declare)
	object_ptr<member_t> pmember;

	scoped_lock(this->m_lockable_group)
	{
		// check)
		RETURN_IF(_index < 0 || _index >= static_cast<int>(this->member_capacity()), false)

		// 1) get member
		pmember = this->member(_index);
	}

	// check)
	RETURN_IF(pmember.empty(), false);

	// 2) alloc shared_buffer
	shared_buffer buffer_temp = alloc_shared_buffer(get_size_of(_data));

	// 3) append data
	buffer_temp.template append<T>(_data);

	// 2) send to all member
	pmember->process_send(std::move(buffer_temp), 1, _option);

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	// check) _buffer가 empty면 리턴
	RETURN_IF(_buffer.empty(), false)

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - get member count
		auto count = this->member_count();

		// - reserve
		vector_send.reserve(count);

		for (auto iter = this->begin(); count > 0; ++iter)
		{
			// check) 
			CGASSERT_ERROR(iter != this->end());

			// check) continue if member is empty
			CONTINUE_IF((*iter).empty());

			// - dcrease member count
			--count;

			// check) except member == _member_except
			CONTINUE_IF((*iter).member() == _member_except);

			// - copy member
			vector_send.push_back((*iter).member());
		}
	}

	// 2) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
template<class T>
typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_except(member_t* _member_except, const T& _data, uint64_t _option)
{
	// 1) shared_buffer를 할당받는다.
	shared_buffer buffer_temp = alloc_shared_buffer(get_size_of(_data));

	// 2) append _data to buffer_temp
	buffer_temp.template append<T>(_data);

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 3) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - get member count
		auto count = this->member_count();

		// - reserve
		vector_send.reserve(count);

		for (auto iter = this->begin(); count > 0; ++iter)
		{
			// check) 
			CGASSERT_ERROR(iter != this->end());

			// check) continue if member is empty
			CONTINUE_IF((*iter).empty());

			// - dcrease member count
			--count;

			// check) except member == _member_except
			CONTINUE_IF((*iter).member() == _member_except);

			// - copy member
			vector_send.push_back((*iter).member());
		}
	}

	// 4) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(buffer_temp), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - get member count
		auto count = this->member_count();

		// - reserve
		vector_send.reserve(count);

		for (auto iter = this->begin(); count > 0; ++iter)
		{
			// check) 
			CGASSERT_ERROR(iter != this->end());

			// check) continue if member is empty
			CONTINUE_IF((*iter).empty());

			// - dcrease member count
			--count;

			// check) continue if result of '_pred' is false
			CONTINUE_IF(_pred((*iter).member()) == false);

			// - copy member
			vector_send.push_back((*iter).member());
		}
	}

	// 2) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
template<class T>
typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_conditional(const T& _data, const std::function<bool (const member_t*)>& _pred, uint64_t _option)
{
	// 1) alloc shared_buffer
	shared_buffer buffer_temp = alloc_shared_buffer(get_size_of(_data));

	// 2) append _data
	buffer_temp.template append<T>(_data);

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - get member count
		auto count = this->member_count();

		// - reserve
		vector_send.reserve(count);

		for (auto iter = this->begin(); count > 0; ++iter)
		{
			// check) 
			CGASSERT_ERROR(iter != this->end());

			// check) continue if member is empty
			CONTINUE_IF((*iter).empty());

			// - dcrease member count
			--count;

			// check) continue if result of '_pred' is false
			CONTINUE_IF(_pred((*iter).member()) == false);

			// - copy member
			vector_send.push_back((*iter).member());
		}
	}

	// 2) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(buffer_temp), 1, _option);
	}

	// return) 성공...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::array_seat_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - get member count
		auto count = this->member_count();

		// - reserve
		vector_send.reserve(count);

		for (auto iter = this->begin(); count > 0; ++iter)
		{
			// check) 
			CGASSERT_ERROR(iter != this->end());

			// check) continue if member is empty
			CONTINUE_IF((*iter).empty());

			// - dcrease member count
			--count;

			// - copy member
			vector_send.push_back((*iter).member());
		}
	}

	// 2) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), _count_message, _option);
	}

	// return)
	return true;
}


}