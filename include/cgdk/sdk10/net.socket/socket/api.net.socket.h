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
//-----------------------------------------------------------------------------
//
// api::socket
//
//
//-----------------------------------------------------------------------------
namespace api
{

std::string					get_host_name() noexcept;
std::string					get_host_id() noexcept;
std::vector<sMAC_ADDRESS>	get_mac_address() noexcept;

class socket
{
public:
	struct resolver_entry
	{
	public:
		net::sockaddr		addr;
		static_string<64>	hostname;
		static_string<64>	servicename;
	};

// constructor/destructor)
private:
			socket() noexcept;
			~socket() noexcept;

// public)
public:
	// 1) Get Instance
	static	socket&				instance() noexcept { static socket socket; return socket;}
	
	// 2) create socket & closesocket
#if defined(_WINSOCK2API_)
	[[nodiscard]] CGSOCKET		create_socket(ADDRESS_FAMILY _address_family = AF_INET, int _socket_type = SOCK_STREAM, int _protocol_info = IPPROTO_TCP, uint32_t _flags = WSA_FLAG_OVERLAPPED) noexcept;
#else
	[[nodiscard]] static CGSOCKET create_socket(ADDRESS_FAMILY _address_family = AF_INET, int _socket_type = SOCK_STREAM, int _protocol_info = IPPROTO_TCP, uint32_t _flags = 0) noexcept;
#endif
	[[nodiscard]] static size_t	get_socket_count() noexcept { return m_socket_count; }
	[[nodiscard]] static size_t	get_max_socket_count() noexcept { return m_socket_count_max; }
	[[nodiscard]] static bool	is_socket_count_overflowed() noexcept;

	static	bool				closesocket(CGSOCKET _handle_socket) noexcept;
	static	bool				graceful_closesocket(CGSOCKET _handle_socket) noexcept;
	static	bool				abortive_closesocket(CGSOCKET _handle_socket) noexcept;

	// 3) Basic Functions
#if defined(_WINSOCK2API_)
	static	bool				get_peer_address(CGSOCKET _handle_socket, ::sockaddr* _paddress, int* _psocket_address_length) noexcept	{ RETURN_IF(_paddress == nullptr || _psocket_address_length==nullptr,false); return ::getpeername(_handle_socket,_paddress,_psocket_address_length) != SOCKET_ERROR;}
	static	bool				get_socket_address(CGSOCKET _handle_socket, ::sockaddr* _paddress, int* _psocket_address_length) noexcept{ RETURN_IF(_paddress == nullptr || _psocket_address_length == nullptr,false); return ::getsockname(_handle_socket,_paddress,_psocket_address_length) != SOCKET_ERROR;}
	static	bool				set_sock_opt(CGSOCKET _handle_socket, int _level, int _option_name, const void* _poption_value, int _option_len) noexcept { return ::setsockopt(_handle_socket, _level, _option_name, reinterpret_cast<const char*>(_poption_value), _option_len) != SOCKET_ERROR; }
	static	bool				get_sock_opt(CGSOCKET _handle_socket, int _option_name, void* _poption_value, int* _poption_length, int _level = SOL_SOCKET) noexcept { return ::getsockopt(_handle_socket, _level, _option_name, reinterpret_cast<char*>(_poption_value), reinterpret_cast<socklen_t*>(_poption_length)) != SOCKET_ERROR; }
	static	size_t				get_pending_read_buffer(CGSOCKET _handle_socket) noexcept { int pending = 0; ::ioctlsocket(_handle_socket, FIONREAD, reinterpret_cast<u_long*>(&pending)); return pending;}
	static	int					get_max_message_size(CGSOCKET _handle_socket) noexcept { int max_msg_size = 0; int ipption_len=sizeof(int); if(get_sock_opt(_handle_socket, SO_MAX_MSG_SIZE, reinterpret_cast<char*>(&max_msg_size), &ipption_len) == false) return -1; return max_msg_size;}
																															  
	static	bool				update_accept_context(CGSOCKET _handle_socket, CGSOCKET _hListenSocket) noexcept { return set_sock_opt(_handle_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char*>(&_hListenSocket), sizeof(_hListenSocket));}
	static	bool				update_connect_context(CGSOCKET _handle_socket) noexcept { return set_sock_opt(_handle_socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0);}
																															  
	static	bool				set_nonblock(CGSOCKET _handle_socket, bool _enable=true) noexcept { u_long value=(_enable) ? 1: 0; return ::ioctlsocket(_handle_socket, FIONBIO, &value)!=SOCKET_ERROR;}
	static	bool				set_loopback_fast_path(CGSOCKET _handle_socket, bool _enable = true) { int32_t option_value = (_enable) ? 1 : 0; uint32_t bytes_returned = 0;  return api::socket::io_ctrl(_handle_socket, SIO_LOOPBACK_FAST_PATH, &option_value, sizeof(option_value), nullptr, 0, &bytes_returned);}
#else
	static	bool				get_peer_address(CGSOCKET _handle_socket, ::sockaddr* _paddress, int* _psocket_address_length) noexcept { RETURN_IF(_paddress == nullptr || _psocket_address_length == nullptr,false); return ::getpeername(_handle_socket, reinterpret_cast<sockaddr*>(_paddress), reinterpret_cast<socklen_t*>(_psocket_address_length)) != SOCKET_ERROR;}
	static	bool				get_socket_address(CGSOCKET _handle_socket, ::sockaddr* _paddress, int* _psocket_address_length) noexcept { RETURN_IF(_paddress == nullptr || _psocket_address_length == nullptr,false); return ::getsockname(_handle_socket, reinterpret_cast<sockaddr*>(_paddress), reinterpret_cast<socklen_t*>(_psocket_address_length)) != SOCKET_ERROR;}
	static	bool				set_sock_opt(CGSOCKET _handle_socket, int _level, int _option_name, const void* _poption_value, int _option_len) noexcept	{ return ::setsockopt(_handle_socket, _level, _option_name, reinterpret_cast<const char*>(_poption_value), _option_len) != SOCKET_ERROR; }
	static	bool				get_sock_opt(CGSOCKET _handle_socket, int _option_name, void* _poption_value, int* _poption_length, int _level = SOL_SOCKET) noexcept { return ::getsockopt(_handle_socket, _level, _option_name, reinterpret_cast<void*>(_poption_value), reinterpret_cast<socklen_t*>(_poption_length)) != SOCKET_ERROR; }
	static	size_t				get_pending_read_buffer(CGSOCKET _handle_socket) noexcept { uint32_t bytes=0; ::ioctl(_handle_socket, FIONREAD, &bytes); return bytes;}
	static	int					get_max_message_size(CGSOCKET) noexcept { return (1024 * 1024 * 1024); }
																															  
	static	bool				set_nonblock(CGSOCKET _handle_socket, bool _enable=true) noexcept { int flags = ::fcntl (_handle_socket, F_GETFL); if(flags == -1) return false; if(_enable) flags|=(O_NONBLOCK); else flags&=(~O_NONBLOCK); return ::fcntl (_handle_socket, F_SETFL, flags)>=0;}
	static	bool				set_loopback_fast_path([[maybe_unused]] CGSOCKET _handle_socket, [[maybe_unused]] bool _enable = true) { return false; }
#endif																														  
	static	bool				set_linger_option(CGSOCKET _handle_socket, uint16_t _enable, uint16_t _time_out=0) noexcept	{ linger temp_linger={_enable, _time_out};return set_sock_opt(_handle_socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char*>(&temp_linger), sizeof(linger));}
	static	bool				set_reuse_address(CGSOCKET _handle_socket, bool _enable) noexcept { int enable = (_enable) ? 1 : 0; return set_sock_opt(_handle_socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&enable), sizeof(enable)) != 0;}
	static	bool				set_tcp_nodelay(CGSOCKET _handle_socket, bool _enable = true) noexcept { int option_value = (_enable) ? 1 : 0; return set_sock_opt(_handle_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&option_value), sizeof(option_value)); }

	static	bool				set_send_buffer_size(CGSOCKET _handle_socket, size_t _size) noexcept { int value = static_cast<int>(_size); return set_sock_opt(_handle_socket, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char*>(&value), sizeof(value));}
	static	bool				set_receive_buffer_size(CGSOCKET _handle_socket, size_t _size) noexcept { int value = static_cast<int>(_size); return set_sock_opt(_handle_socket, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char*>(&value), sizeof(value));}
	static	bool				io_ctrl(
									CGSOCKET			_handle_socket, 
									long				_command, 
									void*				_lpv_in_buffer,
									uint32_t			_cb_in_buffer = sizeof(uint32_t),
									void*				_pout_buffer = nullptr,
									uint32_t			_cb_out_buffer = 0,
									uint32_t*			_pbytes_returned = nullptr) noexcept;

	// 4) bind & connect
	static	int					bind(
									CGSOCKET			_handle_socket,
									const ::sockaddr*	_address,
									int					_paddress_length) noexcept { return ::bind(_handle_socket, _address, _paddress_length); }

	static	bool				listen(CGSOCKET _handle_socket) noexcept { return ::listen(_handle_socket, SOMAXCONN) != SOCKET_ERROR;}

	static	bool				connect(
									CGSOCKET			_handle_socket,
									const ::sockaddr*	_paddress_socket,
									int					_paddress_length) noexcept;

	static	bool				shutdown(
									CGSOCKET			_handle_socket,
									int					_how = SD_SEND) noexcept { return ::shutdown(_handle_socket, _how) != SOCKET_ERROR;}

	// 5) Extention functions(For overlapped)
	static	CGSOCKET			accept(
									CGSOCKET			_handle_socket,
									::sockaddr*			_paddress,
									socklen_t*			_paddress_length) noexcept;
	// 6) send & receive
	static	int					send(
									CGSOCKET			_handle_socket,
									const char*			_buffer,
									int					_len) noexcept	{ RETURN_IF(_handle_socket == INVALID_SOCKET, false); return ::send(_handle_socket, _buffer, _len, 1); }
	static	int					send(
									CGSOCKET			_handle_socket,
									const buffer_view*	_buffer,
									int					_count_buffer) noexcept;


	static	int					recv(
									CGSOCKET			_handle_socket,
									buffer_view*		_pbuffer,
									uint32_t			_flags) noexcept;

	static	int					send_to(
									CGSOCKET			_handle_socket,
									const buffer_view*	_array_buffer,
									int					_count_buffer,
									::sockaddr*			_pto,
									int					_to_length) noexcept;

	static	int					recv_from(
									CGSOCKET			_handle_socket,
									buffer_view*		_array_buffer,
									uint32_t			_flags,
									::sockaddr*			_pfrom,
									int*				_pfrom_len) noexcept;

#if defined(_WINSOCK2API_)
	static	bool				accept_async(
									CGSOCKET			_handle_socket,
									CGSOCKET			_handle_accept_socket,
									void*				_poutput_buffer,
									 LPWSAOVERLAPPED	_poverlapped) noexcept;

	static	bool				connect_async(
									CGSOCKET			_handle_socket,
									Iexecutable*		_pexecutable,
									const ::sockaddr*	_paddress,
									int					_addess_length) noexcept;

	static	bool				disconnect_async(
									CGSOCKET			_handle_socket,
									LPWSAOVERLAPPED		_poverlapped,
									uint32_t			_flags = 0) noexcept;

	static	bool				send_async(
									CGSOCKET			_handle_socket,
									LPWSABUF			_array_wsabuf,
									DWORD				_count_buffer,
									LPDWORD				_pbytes_send,
									LPWSAOVERLAPPED		_poverlapped) noexcept;

	static	bool				recv_async(
									CGSOCKET			_handle_socket,
									LPWSABUF			_pbuffer,
									LPDWORD				_bytes_received,
									LPDWORD				_pflags,
									LPWSAOVERLAPPED		_poverlapped) noexcept;

	static	bool				send_to_async(
									CGSOCKET			_handle_socket,
									LPWSABUF			_array_wsabuf,
									DWORD				_count_buffer,
									LPDWORD				_pbytes_send,
									::sockaddr*			_pto,
									int					_to_length,
									LPWSAOVERLAPPED		_poverlapped) noexcept;

	static	bool				recv_from_async(
									CGSOCKET			_handle_socket,
									LPWSABUF			_array_wsabuf,
									DWORD				_count_buffer,
									LPDWORD				_bytes_received,
									LPDWORD				_pflags,
									::sockaddr*			_pfrom,
									int*				_pfrom_len,
									LPWSAOVERLAPPED		_poverlapped) noexcept;

	// 7) RIO Functions
	static	bool				rio_is_enable() noexcept;

	static	BOOL				rio_receive(
									RIO_RQ				_rqSocket,
									PRIO_BUF			_array_riobuf,
									int					_count_buffer,
									DWORD				_flags,
									void*				_request_context) noexcept;

	static	int					rio_receive_ex(
									RIO_RQ				_rqSocket,
									PRIO_BUF			_array_riobuf,
									int					_count_buffer,
									PRIO_BUF			_plocal_address,
									PRIO_BUF			_premote_address,
									PRIO_BUF			_pcontrol_context,
									PRIO_BUF			_pflags,
									DWORD				_flags,
									void*				_request_context) noexcept;

	static	BOOL				rio_send(	 
									RIO_RQ				_rqSocket,
									PRIO_BUF			_array_riobuf,
									int					_count_buffer,
									DWORD				_flags,
									void*				_request_context) noexcept;

	static	BOOL				rio_send_ex( 
									RIO_RQ				_rqSocket,
									PRIO_BUF			_array_riobuf,
									int					_count_buffer,
									PRIO_BUF			_plocal_address,
									PRIO_BUF			_premote_address,
									PRIO_BUF			_pcontrol_context,
									PRIO_BUF			_pflags,
									DWORD				_flags,
									void*				_request_context) noexcept;

	static	void				rio_close_completion_queue( RIO_CQ _CQ) noexcept;


	static	RIO_CQ				rio_create_completion_queue(
									int					_queue_size,
									PRIO_NOTIFICATION_COMPLETION _notification_completion) noexcept;

	static	RIO_RQ				rio_create_request_queue(
									SOCKET				_socket,
									DWORD				_max_outstanding_receive,
									DWORD				_max_receive_data_buffers,
									DWORD				_max_outstanding_send,
									DWORD				_max_send_data_buffers,
									RIO_CQ				_receive_CQ,
									RIO_CQ				_send_CQ,
									void*				_socket_context) noexcept;

	static	ULONG				rio_dequeue_completion(
									RIO_CQ				_CQ,
									PRIORESULT			_array,
									DWORD				_array_size) noexcept;

	static	void				rio_deregister_buffer( RIO_BUFFERID _bufferId) noexcept;
	static	INT					rio_notify( RIO_CQ	_CQ) noexcept;

	static	RIO_BUFFERID		rio_register_buffer(
									PCHAR				_data_buffer,
									DWORD				_data_length) noexcept;

	static	BOOL				rio_resize_completion_queue(
									RIO_CQ				_CQ,
									DWORD				_queue_size) noexcept;

	static	BOOL				rio_resize_request_queue(
									RIO_RQ				_RQ,
									DWORD				_max_outstanding_receive,
									DWORD				_max_outstanding_send) noexcept;
#endif

public:
#if defined(_WINSOCK2API_)
	[[nodiscard]] static bool	has_accept_ex() noexcept { return WSAcceptEx != nullptr;}
	[[nodiscard]] static bool	has_connect_ex() noexcept { return WSConnectEx != nullptr;}
	[[nodiscard]] static bool	has_disconnect_ex() noexcept { return WSDisconnectEx != nullptr;}
#endif

	// 7) Local Address 구하기. (get_local_address()의 결과가 -1이 되돌아올 경우 socket이 초기화 되지 않았다는 의미이다.)
	[[nodiscard]] int			get_local_address_count() noexcept { return static_cast<int>(m_naddress_local); }
	[[nodiscard]] const auto&	get_local_address(int _index = 0) noexcept { return m_addr_local.at(_index); }
	bool						get_local_address_local(net::sockaddr& _socket_address) noexcept;
	[[nodiscard]] net::sockaddr	get_local_address_local() noexcept { net::sockaddr temp; get_local_address_local(temp); return temp; }
	bool						get_local_address_public(net::sockaddr& _socket_address) noexcept;
	[[nodiscard]] net::sockaddr	get_local_address_public() noexcept { net::sockaddr temp; get_local_address_public(temp); return temp; }
	bool						get_local_address_public_first(net::sockaddr& _socket_address) noexcept;
	[[nodiscard]] net::sockaddr	get_local_address_public_first() noexcept { net::sockaddr temp; get_local_address_public_first(temp); return temp; }

	[[nodiscard]] std::vector<resolver_entry> resolve(int _protocol_family, int _protocol_type, int _protocol_protocol, std::string_view _host_name, u_short _port, int _flag, std::error_code& _error_code) noexcept;
	[[nodiscard]] std::vector<resolver_entry> resolve(int _protocol_family, int _protocol_type, int _protocol_protocol, std::string_view _host_name, std::string_view _service_name, int _flag, std::error_code& _error_code) noexcept;
	[[nodiscard]] std::vector<resolver_entry> resolve(int _protocol_type, const net::sockaddr& _sockaddr, std::error_code& _error_code) noexcept;

// implementation)
private:
	// 1) socket의 수
	static	std::atomic<size_t>	m_socket_count;
	static	size_t				m_socket_count_max;

	static	volatile long		m_naddress_local;
	static	std::array<net::sockaddr,64> m_addr_local;

private:
#if defined(_WINSOCK2API_)
	// 1) bind & connect
	static	int					(PASCAL FAR* WSAcceptEx)(IN CGSOCKET _sListenSocket, IN CGSOCKET _sAcceptSocket, IN PVOID _lpOutputBuffer, IN uint32_t _dwReceivedDataLength, IN uint32_t _dwLocalAddressLength, IN uint32_t _dwRemoteAddressLength, OUT uint32_t* _lpdwBytesReceived, IN LPOVERLAPPED _lpOverlapped);
	static	int					(PASCAL FAR* WSConnectEx)(IN CGSOCKET _s, IN const struct sockaddr FAR* _name, IN int _namelen, IN void* _lpSendBuffer OPTIONAL, IN uint32_t _dwSendedDataLength, OUT uint32_t* _lpdwBytesSent, IN LPOVERLAPPED _lpOverlapped);
	static	int					(PASCAL FAR* WSDisconnectEx)(IN CGSOCKET _s, IN LPOVERLAPPED _lpOverlapped, IN uint32_t _dwFlags, IN uint32_t _dwReserved);

	// 2) RIO Functions
	static	RIO_EXTENSION_FUNCTION_TABLE m_rio_functions;
#endif

	// 3) Extention Function을 얻는 함수.
	static	void				get_extension_function() noexcept;

	// 4) socket초기화 함수.
	static	bool				init_socket();
	static	void				cleanup_socket() noexcept;
};

inline bool socket::is_socket_count_overflowed() noexcept
{
	auto socket_count = m_socket_count.load();
	auto socket_count_max = m_socket_count_max;

	return socket_count > socket_count_max;
}


}


template<class T, class Allocator>
std::basic_string<T> net::sockaddr::to_string(const Allocator& /*_allocator*/) const noexcept
{
	return CGDK::to_string<T>(*this);
}
template<class T>
std::basic_string_view<T> net::sockaddr::to_string(T* _output, size_t _length) const noexcept
{
	return CGDK::to_string<T>(_output, _length, *this);
}

template<class InternetProtocol>
typename net::ip::basic_resolver<InternetProtocol>::results_type net::ip::basic_resolver<InternetProtocol>::_resolve(int _protocol_family, int _protocol_type, int _protocol_protocol, std::string_view _host_name, std::string_view _service_name, net::ip::resolver_base::flags _flag, std::error_code& _error_code) noexcept
{
	auto resolve_result = api::socket::instance().resolve(_protocol_family, _protocol_type, _protocol_protocol, _host_name, _service_name, _flag, _error_code);

	// declare)
	results_type result;

	for (auto& iter : resolve_result)
		result.m_vector_result.emplace_back(endpoint_type{ iter.addr }, iter.hostname, iter.servicename);

	// returns)
	return result;
}
template<class InternetProtocol>
typename net::ip::basic_resolver<InternetProtocol>::results_type net::ip::basic_resolver<InternetProtocol>::_resolve(int _protocol_type, const net::sockaddr& _sockaddr, std::error_code& _error_code) noexcept
{
	auto resolve_result = api::socket::instance().resolve(_protocol_type, _sockaddr, _error_code);

	// declare)
	results_type result;

	for (auto& iter : resolve_result)
		result.m_vector_result.emplace_back(endpoint_type{ iter.addr }, iter.hostname, iter.servicename);

	// returns)
	return result;
}


}