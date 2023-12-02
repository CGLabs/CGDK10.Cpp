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
 @class		Igroup_enterable
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE, class _TPARAM = sMESSAGE>
class Igroup_enterable :
// inherited cClasses)
	public						Igroup<_TMEMBERBASE>
{
// declare)
public:
	using member_base_t = _TMEMBERBASE;
	using param_t = _TPARAM;
	using group_t = typename _TMEMBERBASE::group_base_t;

// publics) 
public:
	//! @brief '멤버 객체'를 입장시킨다. @param _pmember 입장할 '멤버 객체' @param _param 입장할 때 전달할 메시지 @return eRESULT::SUCCESS 성공 @return !eRESULT::SUCCESS 실패
			result_code			enter(member_base_t* _pmember, param_t& _param) { return this->process_enter(_pmember, _param); }
			result_code			enter(member_base_t* _pmember) { param_t msg; return this->process_enter(_pmember, msg); }

	//! @brief 입장을 허용한다. @param _pEnable 허용/불허 @return true 성공 @return false 실패
	[[nodiscard]] bool			is_member_enterable() const noexcept { return this->process_is_enable_member_enter(); }
			bool				enable_member_enter(bool _enable=true) { return this->process_enable_member_enter(_enable);}
			bool				disable_member_enter() noexcept { return this->process_enable_member_enter(false);}

// implementation)
protected:
	//! @brief 입장 가능 여부를 설정하는 과정을 정의한다. @param _pEnable 입장 가능 여부 @return true 성공 @return false 실패
	virtual bool				process_is_enable_member_enter() const noexcept PURE;
	virtual	bool				process_enable_member_enter(bool _enable) PURE;
	virtual	result_code			process_enter(member_base_t* _pmember, param_t& _param) PURE;
};



}