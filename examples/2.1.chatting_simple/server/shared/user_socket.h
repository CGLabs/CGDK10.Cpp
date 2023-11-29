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
// user::socket
//
//-----------------------------------------------------------------------------
class user::socket :
	public						net::socket::tcp<>,
	public						Igroupable<user::socket>,
	public						Nmessage_transmitter
{
private:
	virtual void				on_connect() override;
	virtual	void				on_disconnect(uint64_t _disconnect_reason) override;
	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;

public:
	// - account id
			ACCOUNT_ID			m_aid;

	// - user nickName
			std::string			m_nickname;
};
