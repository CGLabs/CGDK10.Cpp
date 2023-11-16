#include "asio.h"


void asio::Nsocket_tcp_client::start(tcp::endpoint _endpoint_connect)
{
	// statistics) 
	++Nstatistics::statistics_connect_try;

	// 3) request connect
	this->native_handle().async_connect(_endpoint_connect, [=,this](const boost::system::error_code& _error)
		{
			this->process_connect_request_complete(_error);
		});
}

void asio::Nsocket_tcp_client::process_connect_request_complete(const boost::system::error_code& _error)
{
	// check) 실패했을 경우 등록해제하고 소켓을 닫고 끝낸다.
	if (_error)
		return;

	// 1) process connect socket
	this->process_connect_complate();

	// statistics) 
	++Nstatistics::statistics_connect_success;
	++Nstatistics::statistics_connect_keep;
}