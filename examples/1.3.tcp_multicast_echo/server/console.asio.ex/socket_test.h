#pragma once

class socket_tcp : public asio::Nsocket_tcp
{
public:
	virtual void on_connect() override;
	virtual void on_disconnect(boost::system::error_code _error_code) noexcept override;
	virtual int on_message(shared_buffer& _msg) override;
};
