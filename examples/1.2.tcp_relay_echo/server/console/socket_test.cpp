#include "pch.h"


void socket_tcp::on_connect(net::io::Iconnective* /*_pacceptor*/)
{
}
void socket_tcp::on_disconnect(uint64_t /*_disconnect_reason*/)
{
}
result_code socket_tcp::on_message(sMESSAGE_NETWORK & _msg)
{
	// 1) echo send
	this->send(_msg.buf_message);

	// return) 
	return eRESULT::DONE;
}
