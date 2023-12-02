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
// channel::group_chatting
//
//-----------------------------------------------------------------------------
class channel::group_chatting : public channel::Igroup
{
public:
			group_chatting();
	virtual ~group_chatting() noexcept;

private:
	virtual	void				on_destroy() override;

	virtual	void				on_member_entered(user::socket* _pmember, sMESSAGE& _param) override;
	virtual	void				on_member_leaved(user::socket* _pmember, uintptr_t _result) override;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg);
			result_code			on_message_SEND_CHATTING_MESSAGE(sMESSAGE_NETWORK& _msg);
			result_code			on_message_REQUEST_ENTER_CHANNEL(sMESSAGE_NETWORK& _msg);
};
