//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials update - update service                      *
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

class socket_tcp :
	public						net::socket::tcp_client<>,
	public						Nmessage_transmitter
{
private:
	virtual void				on_connect() override;
	virtual void				on_fail_connect(uint64_t _disconnect_reason) override;
	virtual void				on_disconnect(uint64_t) override;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_NETWORK_CERTIFY_RESPONSE(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_RESPONSE(sMESSAGE_NETWORK& _msg);
public:
			own_ptr<update::receiver> m_pupdate_receiver;

};
