#include "pch.h"


void socket_tcp::on_connect()
{
	g_pgroup->enter(this);
}

void socket_tcp::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	this->leave_group();
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// check)
	RETURN_IF(g_disable_echo, eRESULT::BYPASS);

	// 1) echo send
	g_pgroup->send(_msg.buf_message);

	// return) 
	return eRESULT::DONE;
}
