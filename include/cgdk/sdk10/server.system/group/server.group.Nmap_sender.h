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
 @class		Nmap_sender
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TKEY = uint64_t, class _TPARAM = sMESSAGE, class _TMEMBER_DATA = int, class _TMEMBERBASE = _TMEMBER>
class group::Nmap_sender :
	public						Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>,
	virtual public				net::io::Isender
{
public:
	using group_base_t = Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>;
	using key_t = _TKEY;
	using member_t = _TMEMBER;
	using member_base_t = _TMEMBERBASE;
	using member_data_t = _TMEMBER_DATA;
	using param_t = _TPARAM;
	using iterator_t = typename group_base_t::iterator_t;
	using const_iterator_t = typename group_base_t::const_iterator_t;

public:
			Nmap_sender() noexcept : Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>() {}
			Nmap_sender(size_t _max_member) noexcept;
	virtual	~Nmap_sender() noexcept {}

public:
			bool				send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option = 0);

protected:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
group::Nmap_sender<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::Nmap_sender(size_t _max_member) noexcept :
	Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>(_max_member)
{
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap_sender<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_except(member_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	// check) 
	RETURN_IF(_buffer.empty(), false)

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
			// check) 
			CONTINUE_IF(iter->member() == _member_except);

			// - push back
			vector_send.push_back(iter.second.member());
		}
	}

	// 2) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap_sender<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const member_t*)>& _pred, uint64_t _option)
{
	// check) _buffer가 empty면 리턴
	RETURN_IF(_buffer.empty(), false)

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
			// check) _pred가 false면 전송하지 않는다.
			CONTINUE_IF(_pred(iter.second.member()) == false);

			// - push back
			vector_send.push_back(iter.second.member());
		}
	}

	// 2) send
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), 1, _option);
	}

	// return)
	return true;
}

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
bool group::Nmap_sender<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// declare)
	std::vector<object_ptr<_TMEMBER>> vector_send;

	// 1) make member list
	scoped_lock(this->m_lockable_group)
	{
		// - reserve
		vector_send.reserve(this->m_container_member.size());

		// - copy member
		for(const auto& iter: this->m_container_member)
		{
			vector_send.push_back(iter.second.member());
		}
	}

	// 2) send to all
	for (auto& iter : vector_send)
	{
		iter->process_send(shared_buffer(_buffer), _count_message, _option);
	}

	// return) 성공...
	return true;
}


}