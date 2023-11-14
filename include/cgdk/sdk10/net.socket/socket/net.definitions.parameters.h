//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
// ----------------------------------------------------------------------------
//  CONNECTION_PAARAMETER
// ----------------------------------------------------------------------------
struct sSOCKET_ENDPOINT
{
	std::string				str_address;
	std::string				str_service = "0";
	int						flag = 0;
};
sSOCKET_ENDPOINT get_parameter_endpoint(const context& _context, bool _is_enable_log = false);

struct sSOCKET_CONNECT_REQUEST_PARAMETER
{
public:
	net::ip::tcp::endpoint	remote_endpoint;
	net::ip::tcp::endpoint	bind_endpoint;

	chrono::tick::duration	reconnection_interval{ chrono::tick::seconds{5} };
	int						reconnection_enable{ 0 };
	int						flag_wait_complete_connecting{ 0 };
	int						flag_wait_complete_disconnecting{ 0 };
	bool					enable_progress_log = true;

public:
	sSOCKET_CONNECT_REQUEST_PARAMETER() {} 
	sSOCKET_CONNECT_REQUEST_PARAMETER(net::ip::tcp::endpoint _remote_endpoint) : remote_endpoint{ _remote_endpoint } {}
	sSOCKET_CONNECT_REQUEST_PARAMETER(net::ip::tcp::endpoint _remote_endpoint, net::ip::tcp::endpoint _bind_endpoint) : remote_endpoint{ _remote_endpoint }, bind_endpoint{ _bind_endpoint } {}
	sSOCKET_CONNECT_REQUEST_PARAMETER(net::ip::tcp::endpoint _remote_endpoint, net::ip::tcp::endpoint _bind_endpoint, chrono::tick::duration _reconnection_interval, int _reconnection_enable, int _flag_wait_complete_connecting = 0, int _flag_wait_complete_disconnecting = 0, bool _enable_progress_log = true) : remote_endpoint{ _remote_endpoint }, bind_endpoint{ _bind_endpoint }, reconnection_interval{ _reconnection_interval }, reconnection_enable{ _reconnection_enable }, flag_wait_complete_connecting{ _flag_wait_complete_connecting }, flag_wait_complete_disconnecting{ _flag_wait_complete_disconnecting }, enable_progress_log{ _enable_progress_log } {}
	sSOCKET_CONNECT_REQUEST_PARAMETER(net::ip::tcp::endpoint _remote_endpoint, chrono::tick::duration _reconnection_interval, int _reconnection_enable, int _flag_wait_complete_connecting = 0, int _flag_wait_complete_disconnecting = 0, bool _enable_progress_log = true) : remote_endpoint{ _remote_endpoint }, reconnection_interval{ _reconnection_interval }, reconnection_enable{ _reconnection_enable }, flag_wait_complete_connecting{ _flag_wait_complete_connecting }, flag_wait_complete_disconnecting{ _flag_wait_complete_disconnecting }, enable_progress_log{ _enable_progress_log } {}
};
sSOCKET_CONNECT_REQUEST_PARAMETER get_parameter_connection(const context& _context, bool _is_enable_log);

struct sSOCKET_ACCEPT_PARAMETER
{
public:
	net::ip::tcp::endpoint	local_endpoint;
	net::ip::tcp::endpoint	accept_endpoint;
	std::size_t				prepare_on_start = 0;
	std::size_t				must_prepare = 0;
	uint64_t				flag_option = 0;
	bool					enable_progress_log = true;

public:
	sSOCKET_ACCEPT_PARAMETER() {}
	sSOCKET_ACCEPT_PARAMETER(uint16_t _port) : local_endpoint{ net::ip::tcp::v6(), _port } {}
	sSOCKET_ACCEPT_PARAMETER(net::ip::tcp::endpoint _local_endpoint) : local_endpoint{ _local_endpoint } {}
	sSOCKET_ACCEPT_PARAMETER(net::ip::tcp::endpoint _local_endpoint, net::ip::tcp::endpoint _accept_endpoint) : local_endpoint{ _local_endpoint }, accept_endpoint{ _accept_endpoint } {}
	sSOCKET_ACCEPT_PARAMETER(net::ip::tcp::endpoint _local_endpoint, net::ip::tcp::endpoint _accept_endpoint, std::size_t _prepare_on_start, std::size_t _must_prepare = 0, uint64_t _flag_option = 0, bool _enable_progress_log = true) : local_endpoint{ _local_endpoint }, accept_endpoint{ _accept_endpoint }, prepare_on_start{ _prepare_on_start }, must_prepare{ _must_prepare }, flag_option{ _flag_option }, enable_progress_log{ _enable_progress_log } {}
	sSOCKET_ACCEPT_PARAMETER(net::ip::tcp::endpoint _local_endpoint, std::size_t _prepare_on_start, std::size_t _must_prepare = 0, uint64_t _flag_option = 0, bool _enable_progress_log = true) : local_endpoint{ _local_endpoint }, prepare_on_start{ _prepare_on_start }, must_prepare{ _must_prepare }, flag_option{ _flag_option }, enable_progress_log{ _enable_progress_log } {}
	sSOCKET_ACCEPT_PARAMETER(uint16_t _port, std::size_t _prepare_on_start, std::size_t _must_prepare = 0, uint64_t _flag_option = 0, bool _enable_progress_log = true) : local_endpoint{ net::ip::tcp::v6(), _port }, prepare_on_start{ _prepare_on_start }, must_prepare{ _must_prepare }, flag_option{ _flag_option }, enable_progress_log{ _enable_progress_log } {}
};




}