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
 @class		list_dispatchable
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TPARAM = sMESSAGE, class _TMEMBER_DATA = int, class _TMEMBERBASE = _TMEMBER>
class group::list_dispatchable : 
	virtual public				list<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>,
	public						net::io::messageable::Nbase
{
public:
	using group_base_t = list<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>;
	using member_t = _TMEMBER;
	using member_base_t = _TMEMBERBASE;
	using member_data_t = _TMEMBER_DATA;
	using param_t = _TPARAM;
	using iterator_t = typename group_base_t::iterator_t;
	using const_iterator_t = typename group_base_t::const_iterator_t;

public:
			list_dispatchable(size_t _max_member= SIZE_MAX) : group_base_t(_max_member) {}
	virtual	~list_dispatchable() {}

private:
	virtual	void				_process_member_entered(member_t* _pmember, param_t& _param);
	virtual	uintptr_t			_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept;
};


template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
void group::list_dispatchable<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_entered(member_t* _pmember, param_t& _param)
{
	// 1) register message
	_pmember->register_messageable(this);

	try
	{
		// 2) on_member_entered
		this->on_member_entered(_pmember, _param);
	}
	catch(...)
	{
		// - Unreigster 
		_pmember->unregister_messageable(this);

		// reraise) 
		throw;
	}
}

template <class _TMEMBER, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
uintptr_t group::list_dispatchable<_TMEMBER, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::_process_member_leaving(member_t* _pmember, uintptr_t _param) noexcept
{
	// declare) 
	uintptr_t result = 0;

	try
	{
		// 1) on_member_leaving
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

	// 2) unregisterÇÑ´Ù.
	_pmember->unregister_messageable(this);

	// return)
	return	result;
}


}
