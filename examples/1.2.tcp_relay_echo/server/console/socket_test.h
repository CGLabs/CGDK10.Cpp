#pragma once

class socket_tcp : public net::socket::tcp_buffered<>
{
private:
	virtual void on_connect(net::io::Iconnective* _pacceptor);
	virtual void on_disconnect(uint64_t _disconnect_reason);
	virtual result_code on_message(sMESSAGE_NETWORK& _msg);
};