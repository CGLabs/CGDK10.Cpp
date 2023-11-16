#include "pch.h"


void socket_user::on_connect()
{
	//g_pgroup_immigration->enter(this);
}

void socket_user::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	//leave_group();
}

CGDK::result_code socket_user::on_message(CGDK::sMESSAGE_NETWORK& _msg)
{
	// 1) set source
	_msg.set_source(this);

	// 2) dispatch message
	TRANSMIT_MESSAGE(_msg);

	// return) 
	return eRESULT::BYPASS;
}
