//*****************************************************************************
//*                                                                           *
//*                     CGCII simple chatting system (1)                      *
//*                                                                           *
//*                             chatting Server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// user::group_immigration
//
//-----------------------------------------------------------------------------
class user::group_immigration : public group::preset<user::socket>, public schedulable::Nexecutable
{
private:
	virtual	void				on_execute() override;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg);
			result_code			on_message_REQUEST_USER_CHECKIN(sMESSAGE_NETWORK& _msg);
};
