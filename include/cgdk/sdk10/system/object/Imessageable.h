//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

//-----------------------------------------------------------------------------
/**

 @class		Imessageable

*/
//-----------------------------------------------------------------------------
class CGDK::Imessageable : virtual public Ireferenceable
{
public:
			Imessageable() noexcept {}
			Imessageable(bool _enable) noexcept : m_enable_messageable(_enable) {}
	virtual	~Imessageable() noexcept {}

public:
	virtual	result_code			request_process_message(sMESSAGE& _msg)	{ if(is_messageable_disabled()) return result_code(eRESULT::FAIL_DISABLED); return process_message(_msg);}
			result_code			request_process_message(sMESSAGE&& _msg) { return request_process_message(_msg); }
																		  
			void				enable_messageable() noexcept { m_enable_messageable = true;}
			void				disable_messageable() noexcept { m_enable_messageable = false;}
	[[nodiscard]] bool			is_messageable_enabled() const noexcept	{ return m_enable_messageable;}
	[[nodiscard]] bool			is_messageable_disabled() const noexcept { return !is_messageable_enabled();}

protected:
	virtual	result_code			process_message(sMESSAGE& _msg) PURE;

private:
			bool				m_enable_messageable = true;
};
