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
 @class		list_sender
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TPARAM = sMESSAGE, class _TMEMBER_DATA = int, class _TMEMBERBASE = _TMEMBER>
class group::list_sender : 
// inherited classes)
	public						list<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>,
	virtual public				net::io::Isender
{
// definitnion)
public:
	using group_base_t = list<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>;
	using member_t = _TMEMBER;
	using member_base_t = _TMEMBERBASE;
	using member_data_t = _TMEMBER_DATA;
	using param_t = _TPARAM;
	using iterator_t = typename group_base_t::iterator_t;
	using const_iterator_t = typename group_base_t::const_iterator_t;

// constructor/destructor)
public:
			list_sender(size_t _max_member= SIZE_MAX) noexcept;
	virtual	~list_sender() noexcept {}

// public)
public:
			bool				send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	template<class T>
	typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
								send_except(member_t* _member_except, const T& _buffer, uint64_t _option = 0);
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option = 0);
	template<class T>
	typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
								send_conditional(const T& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option = 0);

			bool				process_request_send(const shared_buffer& _buffer, std::size_t _count_message);

// implementations)
protected:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::list_sender(size_t _max_member) noexcept :
	list<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>(_max_member)
{
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - reserve
		vector_send.reserve(this->m_container_member.size());

		// - copy list
		for (const auto& iter : this->m_container_member)
		{
			// check) 
			CONTINUE_IF(iter.member() == _member_except);

			// - push memer to list
			vector_send.push_back(iter.member());
		}
	}

	// 2) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1, _option);
	}

	// return) 성공...
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
template<class T>
typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_except(member_t* _member_except, const T& _data, uint64_t _option)
{
	// 1) shared_buffer를 할당받는다.
	auto buffer_temp = alloc_shared_buffer(get_size_of(_data));

	// 2) 붙인다.
	buffer_temp.template append<T>(_data);

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - reserve
		vector_send.reserve(this->m_container_member.size());

		// - copy member
		for (const auto& iter : this->m_container_member)
		{
			// check) except member == _memer_except
			CONTINUE_IF(iter.member() == _member_except);

			// - push_back
			vector_send.push_back(iter.member());
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
bool group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option)
{
	// check) _buffer.data()가 nullptr이 아닌가?
	RETURN_IF(_buffer.data() == nullptr, false)

	// check) _buffer.size()이 0이 아닌가?
	RETURN_IF(_buffer.size() == 0, false)

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	scoped_lock(this->m_lockable_group)
	{
		// - reserve
		vector_send.reserve(this->m_container_member.size());

		// - copy list
		for (const auto& iter : this->m_container_member)
		{
			// check) send only result of _pred is true
			CONTINUE_IF(_pred(iter.member()) == false);

			// - push_back
			vector_send.push_back(iter.member());
		}
	}

	// 2) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1,_option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
template<class T>
typename std::enable_if<!std::is_base_of<shared_buffer, T>::value, bool>::type
group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_conditional(const T& _data, const std::function<bool (const member_t*)>& _pred, uint64_t _option)
{
	// 1) buffer를 할당받는다.
	auto buffer_temp = alloc_shared_buffer(get_size_of(_data));

	// 2) 붙인다.
	buffer_temp.template append<T>(_data);

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	scoped_lock(this->m_lockable_group)
	{
		for(const auto& iter: this->m_container_member)
		{
			// check) _pred가 false면 전송하지 않는다.
			CONTINUE_IF(_pred(iter->member())==false);

			// - push_back
			vector_send.push_back(iter.member());
		}
	}

	// 4) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(buffer_temp), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::list_sender<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check) _buffer.data()가 nullptr이 아닌가?
	RETURN_IF(_buffer.data() == nullptr, false)

	// check) _buffer.size()이 0이 아닌가?
	RETURN_IF(_buffer.size() == 0, false)
	
	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	scoped_lock(this->m_lockable_group)
	{
		// - 모든 Member에게 전송한다.
		for(const auto& iter: this->m_container_member)
		{
			// - push_back
			vector_send.push_back(iter.member());
		}
	}

	// 4) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), _count_message, _option);
	}

	// return) 성공...
	return true;
}


}