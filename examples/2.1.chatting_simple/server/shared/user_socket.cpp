#include "pch.h"


void user::socket::on_connect()
{
	// 1) 접속시 초기화한다.
	m_aid.reset();
	m_nickname.clear();

	// 2) 일단 접속되면 Immigration Group에 Enter를 합니다.
	g_pservice->m_pgroup_user_immigration->enter(this);
}

void user::socket::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	// 1) group에서 나온다.
	leave_group();

	// 2) user manager에서 제거한다.
	if (m_aid.valid())
	{
		g_pservice->m_pmanager_user->unregister_user(this);
	}
}

result_code user::socket::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) set source
	_msg.set_source(this);

	// 2) dispatch message
	TRANSMIT_MESSAGE(_msg);

	// return)message is not processed
	return eRESULT::BYPASS;
}