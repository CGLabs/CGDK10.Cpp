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
//  Settings
// ----------------------------------------------------------------------------
// 1) send receive shared_buffer (TCP socket의 내부 send/receive shared_buffer 크기)
static const std::size_t MIN_TCP_SEND_BUFFER_SIZE					= (              1024);
static const std::size_t MAX_TCP_SEND_BUFFER_SIZE					= (	  8 * 1024 * 1024);
static const std::size_t MIN_TCP_RECEIVE_BUFFER_SIZE				= (          4 * 1024);
static const std::size_t MAX_TCP_RECEIVE_BUFFER_SIZE				= (	  8 * 1024 * 1024);
static const std::size_t MIN_TCP_MESSAGE_SIZE						= (              1024);
static const std::size_t MAX_TCP_MESSAGE_SIZE						= ( 512 * 1024 * 1024);

// 2) tcp nodelay default setting
#if defined(_WINSOCK2API_)
	#define	DEFAULT_ENABLE_TCP_NODELAY					true
#else
	#define	DEFAULT_ENABLE_TCP_NODELAY					true
#endif

// 3) For TCP receiveable
static const std::size_t DEFAULT_BYTES_TCP_MESSAGE_BUFFER			= (          1 * 1024);
static const std::size_t DEFAULT_BYTES_MAX_TCP_MESSAGE_BUFFER		= (MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK);
static const std::size_t DEFAULT_BYTES_MAX_MESSAGE_RECEIVE_QUEUE	= ( 256 * 1024 * 1024);

// 4) For TCP sendable with gathering
static const std::size_t DEFAULT_MAX_DEPTH_OF_MESSAGE_SEND_QUEUE	= (               256); // - 이 숫자는 반드시 2의 승수(2,4,8,16,32,64,128,256 ...)여야 한다.
static const std::size_t DEFAULT_BYTES_MAX_MESSAGE_SEND_QUEUE		= (   8 * 1024 * 1024); // -   8M bytes
static const std::size_t BYTES_SEND_ASYNC_THRESHOLD					= (          4 * 1024); // -  32k bytes
static const std::size_t COUNT_SEND_GATHER_START_DEPTH				= (                16); // -   16 
static const std::size_t BYTES_SEND_GATHER_BUFFER_MIN				= (          1 * 1024); // -  64k bytes
static const std::size_t BYTES_SEND_GATHER_BUFFER_MAX				= (         64 * 1024); // - 256k bytes
static const std::size_t BYTES_SEND_GATHER_SHIFT_MAX				= (                 6); // - 2 ^ N

// 5) for UDP
static const std::size_t DEFAULT_UDP_SEND_BUFFER_SIZE				= (   8 * 1024 * 1024);
static const std::size_t DEFAULT_UDP_RECEIVE_BUFFER_SIZE			= (   8 * 1024 * 1024);
static const std::size_t DEFAULT_UDP_COUNT_RECEIVE_BUFFER			= 32;
static const std::size_t DEFAULT_UDP_MESSAGE_BUFFER_SIZE			= (         64 * 1024);
static const std::size_t MIN_UDP_MESSAGE_SIZE						= 4;
static const std::size_t MAX_UDP_MESSAGE_SIZE						= (         64 * 1024);


// ----------------------------------------------------------------------------
//  definitions
// ----------------------------------------------------------------------------
// 1) Return If
#define	ERROR_RETURN_IF_INVALID_SOCKET(value, state)	if(native_handle() == INVALID_SOCKET) { state; return value;}
#define	ERROR_RETURN_IF_DISCONNECTED(value, state)		if(socket_state() <= eSOCKET_STATE::SYN) { state; return value;}

#if defined(_WINSOCK2API_)
	using CGSOCKET   = SOCKET;
	using LPCGSOCKET = SOCKET*;
	using RPCGSOCKET = SOCKET&;
#else 
	using CGSOCKET   = int;
	using LPCGSOCKET = int*;
	using RPCGSOCKET = int&;
#endif

// 2) socket Type
#if defined(_WINSOCK2API_)
#else 
	using ADDRESS_FAMILY = uint16_t;

	#define INVALID_SOCKET	(CGSOCKET)(~0)
	#define SOCKET_ERROR	(-1)

	#define SD_SEND         0x01

	using LPWSAOVERLAPPED = void*;
	using LPWSAOVERLAPPED_COMPLETION_ROUTINE = void*;

	#define	ERROR_SUCCESS			0
	#define	ERROR_PORT_UNREACHABLE	0
#endif


// ----------------------------------------------------------------------------
// Basic
// ----------------------------------------------------------------------------
// 1) CG Network socket의 상태를 나타탬
enum class eSOCKET_STATE : int32_t
{
	CLOSED				 = 0,	//  0 : 접속이 종료된 상태
	BINDED				 = 1,	//  1 : Binded
	SYN					 = 2,	//  2 : 접속진행 중인 상태
	SEND_DISCONNECTED	 = 3,	//  3 : (Active) 접속종료 진행상태
	FIN_WAIT_1			 = 4,	//  4 : (Active) 접속종료 진행상태
	FIN_WAIT_2			 = 5,	//  5 : (Active) 접속종료 진행상태
	TIME_WAIT			 = 6,	//  6 : (Active) 접속종료 진행상태
	CLOSE_WAIT			 = 7,	//  7 : (Passive) 접속종료 진행상태
	LAST_ACK			 = 8,	//  8 : (Passive) 접속종료 진행상태
	ESTABLISHED			 = 9,	//  9 : 접속만 된 상태
	LISTEN				 = 10,	// 10 : listen상태
	CERTIFIED			 = 11,	// 11 : 접속이 되고 Client검증이 끝난 상태.
	LOGINED				 = 12,	// 12 : ID와 Password를 넣고 Log-In이 된 상태.
	MAX
};
template <class T>
std::basic_string_view<T>		to_string(eSOCKET_STATE _state) noexcept;
template<> std::string_view		to_string<char>(eSOCKET_STATE _state) noexcept;
template<> std::wstring_view	to_string<wchar_t>(eSOCKET_STATE _state) noexcept;

// 2) acceptor
#define	NO_START_ACCEPT						(-1)

const uint64_t	DISCONNECT_REASON_NODISCONNECTEX			 = 0x1000000000000000;	// Mask

const uint64_t	DISCONNECT_REASON_NONE						 = 0x0000'0000'0000'0000;	// 일상적인 처리 과정일 경우
const uint64_t	DISCONNECT_REASON_FAIL						 = 0x0000'0001'0000'0000;	// 오류로 인한 접속 종료인 경우(송수신 중 오류, 상대방에 의한 강제접속 종료)
const uint64_t	DISCONNECT_REASON_ACTIVE					 = 0x0000'0002'0000'0000;	// 접속 종료를 요청한 측일 경우(설정되어 있지 않으면 Passive)
const uint64_t	DISCONNECT_REASON_ABORTIVE					 = 0x0000'0004'0000'0000;	// 강제 접속종료일 경우(설정되어 있지 않으면 Graceful)
const uint64_t	DISCONNECT_REASON_EXCEPTION					 = 0x0000'0008'0000'0000;	// 예외로 인해 것일 경우
const uint64_t	DISCONNECT_REASON_MASK						 = 0x0000'ffff'0000'0000;	// mask
const uint64_t	DISCONNECT_REASON_MASK_USER					 = 0x0000'0000'ffff'ffff;	// user 정의

const uint64_t	DISCONNECT_REASON_OVERFLOW_MAX_MESSAGES		 = 0x0000'0000'0000'0001;	// send시 message 수의 Overflow로 접속을 종료했다.
const uint64_t	DISCONNECT_REASON_OVERFLOW_MAX_BYTES		 = 0x0000'0000'0000'0002;	// send시 Bytes 수의 Overflow로 접속을 종료했다.
const uint64_t	DISCONNECT_REASON_MESSAGE_LENGTH_TOO_LONG	 = 0x0000'0000'0000'0003;	// message의 길이가 너무 길다
const uint64_t	DISCONNECT_REASON_MESSAGE_LENGTH_TOO_SHORT	 = 0x0000'0000'0000'0004;	// message의 길이가 너무 짧다
const uint64_t	DISCONNECT_REASON_MESSAGE_UNHANDLED_EXCEPTION= 0x0000'0000'0000'0005;	// message처리 중 핸들링 되지 않은 Exception
const uint64_t	DISCONNECT_REASON_BUFFER_IS_NULL			 = 0x0000'0000'0000'0006;	// shared_buffer의 buf값이 nullptr이다.
const uint64_t	DISCONNECT_REASON_INVALID_STATE				 = 0x0000'0000'0000'0007;	// 처리 과정상 있을 수 없는 상태이다.
const uint64_t	DISCONNECT_REASON_INVALID_SOCKET_HANDLE		 = 0x0000'0000'0000'0008;	// socket handle이 INVALID_SOCKET_HANDLE이다.
const uint64_t	DISCONNECT_REASON_FAIL_TO_SOCKET_PREPARE	 = 0x0000'0000'0000'0009;	// socket의 prepare단계에서 실패했다.
const uint64_t	DISCONNECT_REASON_FAIL_TO_SOCKET_ACCEPT		 = 0x0000'0000'0000'000a;	// socket의 Accept 과정에서실패했다.
const uint64_t	DISCONNECT_REASON_FAIL_TO_SOCKET_CONNECT	 = 0x0000'0000'0000'000b;	// socket의 connect 단계에서 실패했다.
const uint64_t	DISCONNECT_REASON_FAIL_TO_SOCKET_BIND		 = 0x0000'0000'0000'000c;	// socket의 최대 생성 수를 초과해 접속이 종료되었다.
const uint64_t	DISCONNECT_REASON_KEEP_ALIVE_TIME_OUT		 = 0x0000'0000'0000'000d;	// socket의 prepare단계에서 실패했다.
const uint64_t	DISCONNECT_REASON_DISABLED					 = 0x0000'0000'0000'000e;	// acceptor나 connector가 disabled된 상태이다.
const uint64_t	DISCONNECT_REASON_CONNECTION_FULL			 = 0x0000'0000'0000'000f;	// 최대접속수를 초과해 접속종료되어다.
const uint64_t	DISCONNECT_REASON_EXCEPTION_OCCURED			 = 0x0000'0000'0000'0010;	// 처리중 예외가 발생해 접속이 종료되었다.
const uint64_t	DISCONNECT_REASON_OPEN_SOCKET_LIMITS		 = 0x0000'0000'0000'0011;	// socket의 최대 생성 수를 초과해 접속이 종료되었다.

const uint64_t	DISCONNECT_REASON_SUCCESS					 = 0;
const uint64_t	DISCONNECT_REASON_GRACEFUL					 = 0;
const uint64_t	DISCONNECT_REASON_FAIL_TIMEOUT				 = (DISCONNECT_REASON_FAIL | DISCONNECT_REASON_ACTIVE);
const uint64_t	DISCONNECT_REASON_FAIL_ABORTIVE				 = (DISCONNECT_REASON_FAIL | DISCONNECT_REASON_ABORTIVE | DISCONNECT_REASON_ACTIVE);
const uint64_t	DISCONNECT_REASON_FAIL_EXCEPTION			 = (DISCONNECT_REASON_FAIL | DISCONNECT_REASON_EXCEPTION);


// ----------------------------------------------------------------------------
// ...
// ----------------------------------------------------------------------------
#define	MINIMUM_REMAINED_RECEIVE_BUFFER		64


// ----------------------------------------------------------------------------
// Object Type
// ----------------------------------------------------------------------------
// 1) Network
#define		CGOBJECTTYPE_NETWORK			0x200000
#define		CGOBJECTTYPE_NETWORK_ACCEPTOR	(CGOBJECTTYPE_NETWORK | 0x0100)
#define		CGOBJECTTYPE_NETWORK_CONNECTOR	(CGOBJECTTYPE_NETWORK | 0x0300)
#define		CGOBJECTTYPE_NETWORK_SOCKET		(CGOBJECTTYPE_NETWORK | 0x0200)


// ----------------------------------------------------------------------------
// Defaults
// ----------------------------------------------------------------------------
namespace net
{
namespace io
{
	namespace socket
	{
		namespace tcp
		{
			using Ndefault	 = net::io::socket::Ntcp;
		}
	}

	namespace connect_requestable
	{
		namespace tcp
		{
			using Ndefault = net::io::connect_requestable::Ntcp;
		}
	}

	namespace connectable
	{
		namespace tcp
		{
			using Ndefault = net::io::connectable::Ntcp;
		}
	}

	namespace sendable
	{
		namespace tcp
		{
			using Ndefault = net::io::sendable::Ntcp_async_gather;
		}
	}

	namespace send_request
	{
		namespace tcp
		{
		using Ndefault = net::io::send_request::Nbase;
		}
	}

	namespace sender
	{
		namespace tcp
		{
			template <class HEADER_T = uint32_t> using Ndefault = net::io::sender::Nstream_header<HEADER_T>;
		}
	}

	namespace receivable
	{
		namespace tcp
		{
			using Ndefault	= net::io::receivable::Nstream;
		}
	}

	namespace packetable
	{
		namespace tcp
		{
			template <class HEADER_T = uint32_t> using Ndefault = net::io::packetable::Nstream<HEADER_T>;
		}
	}

	namespace messageable
	{
		namespace tcp
		{
			using Ndefault	= net::io::messageable::Nbase;
		}
	}
}
}


// ----------------------------------------------------------------------------
// addres to string
// ----------------------------------------------------------------------------
// Functions) 
bool operator == (const sockaddr_in& _lhs, const sockaddr_in& _rhs);

net::sockaddr								from_string			(std::string_view		_address, uint16_t _port, ADDRESS_FAMILY _af_prefer) noexcept;
net::sockaddr								from_string			(std::wstring_view		_address, uint16_t _port, ADDRESS_FAMILY _af_prefer) noexcept;
net::sockaddr								from_string			(std::u16string_view	_address, uint16_t _port, ADDRESS_FAMILY _af_prefer) noexcept;
net::sockaddr								from_string			(std::u32string_view	_address, uint16_t _port, ADDRESS_FAMILY _af_prefer) noexcept;
net::sockaddr								from_string			(std::string_view		_address, uint16_t _port = 0, const addrinfo* _hints = nullptr) noexcept;
net::sockaddr								from_string			(std::wstring_view		_address, uint16_t _port = 0, const addrinfo* _hints = nullptr) noexcept;
net::sockaddr								from_string			(std::u16string_view	_address, uint16_t _port = 0, const addrinfo* _hints = nullptr) noexcept;
net::sockaddr								from_string			(std::u32string_view	_address, uint16_t _port = 0, const addrinfo* _hints = nullptr) noexcept;
net::sockaddr								from_string			(std::string_view		_address, std::string_view		_service, int _socket_type = SOCK_STREAM, int _protocol = IPPROTO_RESERVED_MAX) noexcept;
net::sockaddr								from_string			(std::wstring_view		_address, std::wstring_view		_service, int _socket_type = SOCK_STREAM, int _protocol = IPPROTO_RESERVED_MAX) noexcept;
net::sockaddr								from_string			(std::u16string_view	_address, std::u16string_view	_service, int _socket_type = SOCK_STREAM, int _protocol = IPPROTO_RESERVED_MAX) noexcept;
net::sockaddr								from_string			(std::u32string_view	_address, std::u32string_view	_service, int _socket_type = SOCK_STREAM, int _protocol = IPPROTO_RESERVED_MAX) noexcept;

template <class T>
std::basic_string_view<T>					to_string			(T* _str_address, std::size_t _max_length, const net::sockaddr& _sockaddr) noexcept;
template<> std::string_view					to_string<char>		(char* _str_address, std::size_t _max_length, const net::sockaddr& _sockaddr) noexcept;
template<> std::wstring_view				to_string<wchar_t>	(wchar_t* _str_address, std::size_t _max_length, const net::sockaddr& _sockaddr) noexcept;

template <class T>
std::basic_string<T>
to_string(const net::sockaddr& _address) noexcept { T temp[256]; return std::basic_string<T>(to_string<T>(temp, 256, _address)); }
template <class T>
std::basic_string<T>
to_string(const net::ip::address& _address) noexcept { T temp_str[256]; return std::basic_string<T>(to_string<T>(temp_str, 256, _address)); }
template <class T>
std::basic_string<T>
to_string(const net::ip::address_v4& _address) noexcept { T temp_str[256]; return std::basic_string<T>(to_string<T>(temp_str, 256, _address)); }
template <class T>
std::basic_string<T>
to_string(const net::ip::address_v6& _address) noexcept { T temp_str[256]; return std::basic_string<T>(to_string<T>(temp_str, 256, _address)); }

template <class T, class Allocator = std::allocator<T>>
std::basic_string<T, std::char_traits<T>, Allocator>
to_string (const net::sockaddr& _address, const Allocator& _allocator) noexcept { T temp_str[256]; return std::basic_string<T, std::char_traits<T>, Allocator>(to_string<T>(temp_str, 256, _address), _allocator); }
template <class T, class Allocator = std::allocator<T>>
std::basic_string<T, std::char_traits<T>, Allocator>
to_string (const net::ip::address& _address, const Allocator& _allocator) noexcept { T temp_str[256]; return std::basic_string<T, std::char_traits<T>, Allocator>(to_string<T>(temp_str, 256, _address), _allocator); }
template <class T, class Allocator = std::allocator<T>>
std::basic_string<T, std::char_traits<T>, Allocator>
to_string (const net::ip::address_v4& _address, const Allocator& _allocator) noexcept { T temp_str[256]; return	std::basic_string<T, std::char_traits<T>, Allocator>(to_string<T>(temp_str, 256, _address), _allocator); }
template <class T, class Allocator = std::allocator<T>>
std::basic_string<T, std::char_traits<T>, Allocator>
to_string (const net::ip::address_v6& _address, const Allocator& _allocator) noexcept { T temp_str[256]; return	std::basic_string<T, std::char_traits<T>, Allocator>(to_string<T>(temp_str, 256, _address), _allocator); }


// ----------------------------------------------------------------------------
// SFINAE) 
// ----------------------------------------------------------------------------
// shared_buffer linear container<T>)
template<class T>					struct is_send_container_buffer : public std::false_type {};
template<class A>					struct is_send_container_buffer<std::vector<shared_buffer, A>> : public std::true_type {};
template<class A>					struct is_send_container_buffer<std::list<shared_buffer, A>> : public std::true_type {};
template<class A>					struct is_send_container_buffer<std::deque<shared_buffer, A>> : public std::true_type {};
template<std::size_t A>				struct is_send_container_buffer<std::array<shared_buffer, A>> : public std::true_type {};
template<class A>					struct is_send_container_buffer<circular_list<shared_buffer, A>> : public std::true_type {};
template<std::size_t A>				struct is_send_container_buffer<static_vector<shared_buffer, A>> : public std::true_type {};

// linear container<T>)
template<class T>					struct is_send_container : public std::false_type {};
template<class A, class B>			struct is_send_container<std::vector<A, B>> : public std::true_type {};
template<class A, class B>			struct is_send_container<std::list<A, B>> : public std::true_type {};
template<class A, class B>			struct is_send_container<std::deque<A, B>> : public std::true_type {};
template<class A, std::size_t B>	struct is_send_container<std::array<A, B>> : public std::true_type {};
template<class A, class B>			struct is_send_container<circular_list<A, B>> : public std::true_type {};
template<class A, std::size_t B>	struct is_send_container<static_vector<A, B>> : public std::true_type {};

enum class eSSL_PROTOCOL : uint8_t
{
	CHANGE_CIPER_SPEC	 = 20,
	ALERT				 = 21,
	HANDSHAKE			 = 22,
	APPLICATION			 = 23
};

enum class eSSL_ALEART_LEVEL : uint8_t
{
	WARNING				 = 1,
	FATAL				 = 2		// SSL terminates connection, other connections in same session continue, no new connections allow
};

enum class eSSL_HANDSHAKE_TYPE : uint8_t
{
	HELLO_REQUEST		 = 0,
	CLIENT_HELLO		 = 1,
	SERVER_HELLO		 = 2,
	CERTIFICATE			 = 11,
	SERVER_KEY_EXCHANGE	 = 12,
	CERTIFICATE_REQUEST	 = 13,
	SERVER_HELLO_DONE	 = 14,
	CERTIFICATE_VERIFY	 = 15,
	CLIENT_KEY_EXCHANGE	 = 16,
	FINISHED			 = 20
};

struct sSSL_VERSION
{
public:
	uint8_t		major;
	uint8_t		minor;
};

extern std::map<int, const char*> ssl_version_tbl;
extern std::map<int, const char*> ssl_content_tbl;
extern std::map<int, const char*> ssl_handshake_tbl;
extern std::map<int, const char*> ssl_ciphers_tbl;
extern std::map<int, const char*> ssl_comp_tbl;
extern std::map<int, const char*> ssl_exts_tbl;
extern std::map<int, const char*> ssl_curve_tbl;
extern std::map<int, const char*> ssl_point_tbl;
extern std::map<int, const char*> ssl_md_tbl;
extern std::map<int, const char*> ssl_sig_tbl;
extern std::map<int, const char*> ssl_hb_tbl;
extern std::map<int, const char*> ssl_hb_type_tbl;
extern std::map<int, const char*> ssl_ctype_tbl;

namespace api
{
	bool	crack_url();
}


}