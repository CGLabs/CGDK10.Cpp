//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                        tutorials service - simple                         *
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

class socket_tcp_user : public net::socket::tcp<>
{
private:
	virtual void on_connect() override
	{
		LOG_INFO << "'socket_tcp_user' connected ("sv << to_string<char>(remote_endpoint()) << ")"sv;
	}
	virtual void on_disconnect(uint64_t /*_disconnect_reason*/) override
	{
		LOG_INFO << "'socket_tcp_user' disconnected"sv;
	}
};
