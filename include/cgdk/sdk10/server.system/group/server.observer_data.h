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

 @class		array
 @brief		멤버별 데이터를 저장할 데이터
 @todo		
 @ref		
 @details	\n
 멤버별 데이터를 임시 저장하는 용도로 사용되는 것이다.
       
*///-----------------------------------------------------------------------------
template <class _TOBSERVER>
struct observable::OBSERVER_SET
{
public:
			object_ptr<_TOBSERVER> pobserver;
			typename _TOBSERVER::observer_channel_t	ocid;

public:
	[[nodiscard]] bool			operator==(const _TOBSERVER* _rhs) const noexcept { return pobserver == _rhs;}
	[[nodiscard]] bool			operator!=(const _TOBSERVER* _rhs) const noexcept { return pobserver != _rhs;}
	[[nodiscard]] bool			operator>=(const _TOBSERVER* _rhs) const noexcept { return pobserver >= _rhs;}
	[[nodiscard]] bool			operator> (const _TOBSERVER* _rhs) const noexcept { return pobserver >  _rhs;}
	[[nodiscard]] bool			operator<=(const _TOBSERVER* _rhs) const noexcept { return pobserver <= _rhs;}
	[[nodiscard]] bool			operator< (const _TOBSERVER* _rhs) const noexcept { return pobserver <  _rhs;}

	[[nodiscard]] bool			operator==(const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return pobserver == _rhs.pobserver && ocid==_rhs.ocid;}
	[[nodiscard]] bool			operator!=(const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return pobserver != _rhs.pobserver || ocid!=_rhs.ocid;}
	[[nodiscard]] bool			operator>=(const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return (pobserver > _rhs.pobserver) ? true : (pobserver<_rhs.pobserver) ? false : (ocid>=_rhs.ocid);}
	[[nodiscard]] bool			operator> (const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return (pobserver > _rhs.pobserver) ? true : (pobserver<_rhs.pobserver) ? false : (ocid> _rhs.ocid);}
	[[nodiscard]] bool			operator<=(const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return (pobserver < _rhs.pobserver) ? true : (pobserver>_rhs.pobserver) ? false : (ocid<=_rhs.ocid);}
	[[nodiscard]] bool			operator< (const OBSERVER_SET<_TOBSERVER>& _rhs) const noexcept { return (pobserver < _rhs.pobserver) ? true : (pobserver>_rhs.pobserver) ? false : (ocid< _rhs.ocid);}

public:
			OBSERVER_SET() noexcept : pobserver(), ocid(0) {}
			OBSERVER_SET(_TOBSERVER* _pobserver, typename _TOBSERVER::observer_channel_t _ocid) noexcept : pobserver(_pobserver), ocid(_ocid)	{}
};


//-----------------------------------------------------------------------------
//
// observable::MEMBER_SET_ARRAY
//
// Array형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TOBSERVER, class _TOBSERVER_DATA>
struct observable::OBSERVER_SET_DATA : public OBSERVER_SET<_TOBSERVER>
{
public:
			_TOBSERVER_DATA		observer_data;

public:
			OBSERVER_SET_DATA() noexcept : OBSERVER_SET<_TOBSERVER>(), observer_data()	{}
			OBSERVER_SET_DATA(_TOBSERVER* _pobserver, typename _TOBSERVER::observer_channel_t _ocid) noexcept : OBSERVER_SET<_TOBSERVER>(_pobserver, _ocid), observer_data()	{}
			OBSERVER_SET_DATA(_TOBSERVER* _pobserver, typename _TOBSERVER::observer_channel_t _ocid, const _TOBSERVER_DATA& _observer_data) noexcept : OBSERVER_SET<_TOBSERVER>(_pobserver, _ocid), observer_data(_observer_data) {}

			void				set_observer_data(const _TOBSERVER_DATA& _observer_data) const { const_cast<_TOBSERVER_DATA&>(observer_data) = _observer_data;}
};


}