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

#include "cgdk/sdk10/server.system/group/server.group.base.h"

namespace CGDK
{
//-----------------------------------------------------------------------------
/**
 @class		map
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TKEY = group_member_id_t, class _TPARAM = sMESSAGE, class _TMEMBER_DATA = int, class _TMEMBERBASE = _TMEMBER>
class group::map :
	virtual public				Nmap<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>
{
public:
			map(size_t _max_member = SIZE_MAX) : m_serialMember(0) { Igroup_countable<_TMEMBERBASE, _TPARAM>::member_capacity(_max_member);}
	virtual	~map() {}

protected:
	[[nodiscard]] virtual _TKEY	process_get_member_key(_TMEMBER* _pmember) override;

private:
			std::atomic<_TKEY>	m_serialMember;
};

template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA, class _TMEMBERBASE>
_TKEY group::map<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA, _TMEMBERBASE>::process_get_member_key(_TMEMBER* /*_pmember*/)
{
	// 1) Generate New key
	auto key_new = ++this->m_serialMember;

	// 2) If generated key is zero, generate one more time
	if (key_new == 0)
	{
		key_new = ++this->m_serialMember;
	}

	// return) return generated key
	return key_new;
}


}