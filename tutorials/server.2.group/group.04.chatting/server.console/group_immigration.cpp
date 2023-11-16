#include "pch.h"


void group_immigration::on_member_entered(socket_user* _pmember, CGDK::sMESSAGE& /*param*/)
{
	// 1) this를 _pmember의 메시지 전달 대상으로 등록한다.
	_pmember->register_messageable(this);
}
uintptr_t group_immigration::on_member_leaving(socket_user* _pmember, uintptr_t /*_param*/)
{
	// 1) _pmember의 메시지 전달 대상에서 this를 해제한다.
	_pmember->unregister_messageable(this);

	// return) 
	return 0;
}
CGDK::result_code group_immigration::on_message(CGDK::sMESSAGE_NETWORK& _msg)
{
	// 1) message_type을 얻는다.
	auto message_type = _msg.buf_message.front<eMESSAGE_TYPE>(4);

	// 2) message 종류에 따라 처리한다.
	switch (message_type)
	{
	case	eMESSAGE_TYPE::REQUEST_LOGIN:
			return this->on_message_REQUEST_LOGIN(_msg);
			break;

	default:
			break;
	}

	// return) 
	return eRESULT::BYPASS;
}

CGDK::result_code group_immigration::on_message_REQUEST_LOGIN(CGDK::sMESSAGE_NETWORK& _msg)
{
	// 1) source 얻기
	auto psource = _msg.get_source<socket_user>();

	// 2) message 읽어내기
	/*auto msg = */_msg.buf_message.front<sMESSAGE_REQUEST_LOGIN>();

	try
	{
		// 3) user를 등록한다.
		g_pmanager_user->register_user(psource); // msg.nickname

		// 4) message 작성
		sMESSAGE_RESPONSE_LOGIN msg_send;
		msg_send.message_type	 = eMESSAGE_TYPE::RESPONSE_LOGIN;
		msg_send.result			 = eRESULT::SUCCESS;
		msg_send.user_id		 = psource->m_user_id;

		// 5) 결과 전송
		psource->send(make_shared_buffer(msg_send));
	}
	catch (CGDK::throwable::failure& _e)
	{
		// - message 작성
		sMESSAGE_RESPONSE_LOGIN msg_send;
		msg_send.message_type	 = eMESSAGE_TYPE::RESPONSE_LOGIN;
		msg_send.result			 = _e.reason();
		msg_send.result_message	 = _e.m_description;
		msg_send.user_id		 = psource->m_user_id;

		// - 결과 전송
		psource->send(make_shared_buffer(msg_send));
	}
	catch (...)
	{
		// - message 작성
		sMESSAGE_RESPONSE_LOGIN msg_send;
		msg_send.message_type	 = eMESSAGE_TYPE::RESPONSE_LOGIN;
		msg_send.result			 = eRESULT::EXCEPTION;
		msg_send.result_message	 = "unknowned exception";
		msg_send.user_id		 = psource->m_user_id;

		// - 결과 전송
		psource->send(make_shared_buffer(msg_send));
	}

	// return)
	return eRESULT::DONE;
}
