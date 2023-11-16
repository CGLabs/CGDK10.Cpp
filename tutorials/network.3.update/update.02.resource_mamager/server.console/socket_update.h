//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                   tutorials update - resource manager                     *
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

class socket_update : 
	public net::socket::tcp<>,
	public Nmessage_transmitter
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;
			result_code on_message_UPDATE_REQUEST(sMESSAGE_NETWORK& _msg);
			result_code on_message_UPDATE_COMPLETE(sMESSAGE_NETWORK& _msg);
};
