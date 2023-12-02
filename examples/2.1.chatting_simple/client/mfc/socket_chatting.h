//*****************************************************************************
//*                                                                           *
//*                     CGCII Sample Chatting System (1)                      *
//*                                                                           *
//*                           Sample Chatting Client                          *
//*                                                                           *
//*  Programmed by Cho SangHyun(sangduck@cgcii.co.kr) 2016/02/01.             *
//*                                                                           *
//*  Updated : 2017/04/16                                                     *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// socket_chatting
//
// ----------------------------------------------------------------------------
class socket_chatting :
	public						net::socket::tcp_client<>
{
public:
			socket_chatting();
	virtual ~socket_chatting();

protected:
	virtual void				on_request_connect(const net::sockaddr& _address);
	virtual void				on_connect() override;
	virtual	void				on_disconnect(uint64_t _disconnect_reason) override;
	virtual	void				on_fail_connect(uint64_t _disconnect_reason) override;

protected:
	DECLARE_CGMESSAGE_MAP

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;

			result_code			on_message_RESPONSE_USER_CHECKIN(sMESSAGE_NETWORK& _msg);
			result_code			on_message_NOTIFY_ENTER_CHANNEL	(sMESSAGE_NETWORK& _msg);
			result_code			on_message_SEND_CHATTING_MESSAGE(sMESSAGE_NETWORK& _msg);
};
