#pragma once

class socket_tcp : public asio::Nsocket_tcp
{
public:
	virtual void on_connect() override;
	virtual void on_disconnect() noexcept override;
	virtual int on_message(const const_buffer& _msg) override;
};
