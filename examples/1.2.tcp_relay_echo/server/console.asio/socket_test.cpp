#include "pch.h"


void socket_tcp::on_connect()
{
}
void socket_tcp::on_disconnect() noexcept
{
}
int socket_tcp::on_message(const const_buffer& _msg)
{
	// 1) echo send
	this->send(_msg);

	// return) 
	return 1;
}
