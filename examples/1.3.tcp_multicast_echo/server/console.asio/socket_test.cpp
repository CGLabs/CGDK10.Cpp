#include "pch.h"


void socket_tcp::on_connect()
{
	g_pgroup->add_member(this->shared_from_this());
}

void socket_tcp::on_disconnect() noexcept
{
	g_pgroup->remove_member(this->shared_from_this());
}

int socket_tcp::on_message(const const_buffer& _msg)
{
	if (g_disable_echo)
		return 0;

	// 1) send messag to all member
	g_pgroup->send(_msg);

	// return) 
	return 1;
}
