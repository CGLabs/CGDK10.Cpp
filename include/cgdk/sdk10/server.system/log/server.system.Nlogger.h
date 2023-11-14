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
// 1. I_logFilter��~
//    ������ Log�� ����ϰų� �����ϱ� ���� Filtering�� �����ϴ� Class�̴�.
//    �Ϲ������� C_logFile�̳� Server MFC control�� CChild_logger_view_ex� ���ȴ�.
//
// 2. I_logFilter�� �ٽ� �Լ�
//		1) Filtering �Լ�
//
//         bool process_filtering(const sMESSAGE_LOG& _msg) PURE;
//
//         ���������Լ��� process_filtering�� �������Ͽ� Log�� ���� �ʿ䰡 �ִ�
//         ��Ȳ�� true�� ���ϵǾ� ������ �Լ��� ������ �ָ� �ȴ�.
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