#include "pch.h"


socket_chatting::socket_chatting()
{
}

socket_chatting::~socket_chatting()
{
}

void socket_chatting::on_request_connect(const net::sockaddr& /*_address*/)
{
	if (g_pdlg != nullptr)
	{
		g_pdlg->on_request_connect(this);
	}
}

void socket_chatting::on_connect()
{
	if (g_pdlg != nullptr)
	{
		g_pdlg->OnConnect(this);
	}

	// 1) ...
	send(message_REQUEST_USER_CHECKIN(ACCOUNT_ID(rand()), "TestID"));
}

void socket_chatting::on_fail_connect(uint64_t /*_disconnect_reason*/)
{
	if (g_pdlg != nullptr)
	{
		g_pdlg->on_fail_connect(this);
	}
}

void socket_chatting::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	if (g_pdlg != nullptr)
	{
		g_pdlg->on_disconnect(this);
	}
}

BEGIN_CGMESSAGE_MAP(socket_chatting)
	CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
		ON_CGMESSAGE(eMESSAGE::RESPONSE_USER_CHECKIN,		on_message_RESPONSE_USER_CHECKIN,	sMESSAGE_NETWORK);
		ON_CGMESSAGE(eMESSAGE::NOTIFY_ENTER_CHANNEL,		on_message_NOTIFY_ENTER_CHANNEL,	sMESSAGE_NETWORK);
		ON_CGMESSAGE(eMESSAGE::SEND_CHATTING_MESSAGE,		on_message_SEND_CHATTING_MESSAGE,	sMESSAGE_NETWORK);
	END_SUB_CGMESSAGE_MAP
END_CGMESSAGE_MAP

result_code socket_chatting::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) Message를 처리한다.
	EXECUTE_CGMESSAGE_MAP(_msg);

	// Return) 성공!!!
	return eRESULT::BYPASS;
}

result_code socket_chatting::on_message_RESPONSE_USER_CHECKIN(sMESSAGE_NETWORK& /*_msg*/)
{
	// Return) 
	return eRESULT::DONE;
}

result_code socket_chatting::on_message_NOTIFY_ENTER_CHANNEL(sMESSAGE_NETWORK& _msg)
{
	// 1) ...
	auto buf = _msg.buf_message + offset(8);

	// 2) Message를 읽는다.
	auto cid	 = buf.extract<CHANNEL_ID>();
	auto option	 = buf.extract<eCHANNEL_OPTION>();
	auto str_name = buf.extract<const char*>();

	// 3) Notify~
	if (g_pdlg != nullptr)
	{
		g_pdlg->on_notify_enter_channel(this, cid, option, str_name);
	}

	// return) 
	return eRESULT::DONE;
}

result_code socket_chatting::on_message_SEND_CHATTING_MESSAGE(sMESSAGE_NETWORK& _msg)
{
	// 1) ...
	auto buf = _msg.buf_message + offset(8);

	// 2) Message를 읽는다.
	auto str_chatting = buf.extract<std::string_view>();
	auto str_nickname = buf.extract<std::string_view>();

	// 3) Notify~
	if (g_pdlg != nullptr)
	{
		g_pdlg->on_send_chatting_message(this, str_chatting, str_nickname);
	}
	
	// return) 
	return eRESULT::DONE;
}
