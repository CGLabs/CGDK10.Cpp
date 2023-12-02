//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
//
// I_logFilter
//
// 1. I_logFilter은~
//    설정된 Log만 출력하거나 저장하기 위해 Filtering을 수행하는 Class이다.
//    일반적으로 C_logFile이나 Server MFC control의 CChild_logger_view_ex등에 사용된다.
//
// 2. I_logFilter의 핵심 함수
//		1) Filtering 함수
//
//         bool process_filtering(const sMESSAGE_LOG& _msg) PURE;
//
//         순수가상함수인 process_filtering을 재정의하여 Log를 남길 필요가 있는
//         상황에 true가 리턴되어 오도록 함수를 정의해 주면 된다.
//
//-----------------------------------------------------------------------------
class Nlogger :
	virtual public				Ilogger,
	public						object::Nnameable,
	public						object::Nstate,
	public						object::Ninitializable
{
public:
			Nlogger() noexcept = default;
			Nlogger(const std::string_view _name) : Nnameable(_name) {}
	virtual ~Nlogger() noexcept {}

protected:
	virtual result_code			_process_initializing(context& _context) override;
};


}