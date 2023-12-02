#pragma once

class socket_tcp :
	public net::io::socket::tcp::Ndefault,
	public net::io::connectable::tcp::Ndefault,
	public net::io::sendable::Ntcp_async_gather_buffered,
	public net::io::send_request::tcp::Ndefault,
	public net::io::sender::Nstream_header<uint32_t>,
	public net::io::receivable::Nstream,
	public net::io::packetable::tcp::Ndefault<uint32_t>,
	public net::io::messageable::tcp::Ndefault,
	public Igroupable<socket_tcp>
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t _disconnect_reason) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;
};