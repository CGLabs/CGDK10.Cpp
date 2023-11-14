//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// net::io::messageable::Nqueue
//
//-----------------------------------------------------------------------------
class net::io::messageable::Nqueue : 
// inherited classes) 
	virtual public				Imessageable
{
// publics) 
public:
	// 1) 
	virtual	result_code			request_process_message(sMESSAGE& _msg) override;
			result_code			request_process_message(sMESSAGE&& _msg) { return this->request_process_message(_msg); }
			result_code			request_post_process_message(sMESSAGE_NETWORK& _msg);
			result_code			request_post_process_message(sMESSAGE_NETWORK&& _msg) { return this->request_post_process_message(_msg); }
			result_code			continue_process_message();

// frameworks) 
protected:
	virtual result_code			on_message(sMESSAGE_NETWORK& /*_msg*/) { return eRESULT::BYPASS;}

private:
			lockable<>			m_lockable_queue_message;
			circular_list<sMESSAGE_NETWORK> m_queue_message;
			bool				m_flag_processing = false;

public:
	virtual	result_code			process_message(sMESSAGE& _msg) override;
};


}