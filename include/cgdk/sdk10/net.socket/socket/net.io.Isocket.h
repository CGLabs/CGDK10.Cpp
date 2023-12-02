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
// net::io::Isocket
//
// 1. net::io::Isocket
//    1) socket Interface로 socket의 Handle을 가지고 있다.
//    2) socket의 상태값(eSOCKET_STATE)을 가지고 있다.
//    3) socket의 생성과 소멸을 위한 함수를 가지고 있다.
//    4) socket을 재사용시 reset하는 함수를 가지고 있다.
//
// 2. net::io::Isocket의 주요 함수
//    1) ProcessResetSocket()	socket의 생성과정을 정의하는 함수이다.
//    2) process_close_socket(uint64_t _disconnect_reason)	socket의 파괴과정을 정의하는 함수이다.
//    3) ResetSocket()			socket의 재사용을 위해 reset하는 과정을 정의하는 함수이다.
//    4) 기타함수들...
//       - socket의 상태를 확인하는 함수.
//       - socket의 Handle에 관련된 함수.
//
//
//-----------------------------------------------------------------------------
class net::io::Isocket :
	virtual public				Iaddress
{
public:
			Isocket() {}
	virtual	~Isocket() noexcept {}

public:
	// 1) socket을 준비하고 닫을 때 호출하는 함수.
	virtual	void				process_create_socket(ADDRESS_FAMILY _address_family = AF_INET) PURE;
	virtual	void				process_prepare_socket(ADDRESS_FAMILY _address_family = AF_INET) PURE;
	virtual void				process_dispose_socket() noexcept PURE;
	virtual	bool				process_close_socket(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept PURE;

public:
	// 2) prepare socket
			void				prepare_socket(ADDRESS_FAMILY _address_family = AF_INET) { this->process_prepare_socket(_address_family);}
			bool				closesocket(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept;

	// 3) native handle
			CGSOCKET			native_handle( CGSOCKET _handle_socket) noexcept{ return this->m_native_handle.exchange(_handle_socket);}
	[[nodiscard]] CGSOCKET		native_handle() const noexcept { return this->m_native_handle;}
	[[nodiscard]] bool			is_valid_native_handle() const noexcept { return this->m_native_handle != INVALID_SOCKET; }
	[[nodiscard]] bool			is_invalid_native_handle() const noexcept { return this->m_native_handle == INVALID_SOCKET;}

	// 4) executor
			void				io_context(executor::Iio_context* _pio_context) noexcept { this->m_pio_context = _pio_context;}
	[[nodiscard]] auto			io_context() const noexcept { return this->m_pio_context;}
			void				reset_io_context() noexcept { this->m_pio_context.reset(); }

	// 5) socket state
			eSOCKET_STATE		socket_state( eSOCKET_STATE _status) noexcept {	return this->m_socket_status.exchange(_status);}
	[[nodiscard]] eSOCKET_STATE	socket_state() const noexcept {	return this->m_socket_status;}
			bool				set_socket_state_if( eSOCKET_STATE _status_comparend, eSOCKET_STATE _status_new) noexcept { return this->m_socket_status.compare_exchange_weak(_status_comparend, _status_new);}
			bool				exchange_socket_state_if( eSOCKET_STATE& _status_comparend, eSOCKET_STATE _status_new) noexcept { return this->m_socket_status.compare_exchange_weak(_status_comparend, _status_new);}

	[[nodiscard]] bool			is_disconnected() const noexcept { return (this->m_socket_status == eSOCKET_STATE::CLOSED);}	// 0 : 접속이 종료된 상태.
	[[nodiscard]] bool			is_binded() const noexcept { return (this->m_socket_status >= eSOCKET_STATE::BINDED);}			// 1 : listen중인가?
	[[nodiscard]] bool			is_connected() const noexcept { return (this->m_socket_status >= eSOCKET_STATE::ESTABLISHED);}	// 2 : 접속만 된 상태.
	[[nodiscard]] bool			is_certified() const noexcept { return (this->m_socket_status >= eSOCKET_STATE::CERTIFIED);}	// 3 : 접속이 되고 Client검증이 끝난 상태.
	[[nodiscard]] bool			is_logined() const noexcept { return (this->m_socket_status >= eSOCKET_STATE::LOGINED);}		// 4 : ID와 Password를 넣고 Log-In이 된 상태.
	[[nodiscard]] bool			is_listening() const noexcept { return (this->m_socket_status == eSOCKET_STATE::LISTEN);}		// 9 : listen중인가?
	[[nodiscard]] bool			is_client_socket() const noexcept { return this->m_is_client_socket; }

	// 6) socket reason (disconnect reason)
			void				disconnect_reason( uint64_t _disconnect_reason) noexcept { this->m_disconnect_reason = _disconnect_reason;}
	[[nodiscard]] uint64_t		disconnect_reason() const noexcept { return this->m_disconnect_reason;}

	// 7) socket address
			void				address_family(ADDRESS_FAMILY _af) noexcept { this->m_address_family = _af;}
			auto				address_family() const noexcept { return this->m_address_family;}
	[[nodiscard]] net::sockaddr	socket_address_in_public(std::error_code& _error_code) const noexcept;
	[[nodiscard]] net::sockaddr	socket_address_in_public() const noexcept { std::error_code error_code; return socket_address_in_public(error_code);}

	// 9) options
			void				maximum_send_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	maximum_send_buffer_size() const noexcept { return this->m_maximum_send_buffer_size;}

			void				maximum_receive_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	maximum_receive_buffer_size() const noexcept { return this->m_maximum_receive_buffer_size;}

			void				exception_on_send_overflow(bool _enable) noexcept { this->m_is_exception_on_send_overflow = _enable; }
	[[nodiscard]] bool			exception_on_send_overflow() const noexcept { return this->m_is_exception_on_send_overflow;}

	[[nodiscard]] int			get_last_socket_error() const noexcept { return m_last_socket_error; }

// implementation)
protected:
	virtual	net::sockaddr		process_get_socket_address(std::error_code& _error_code) const noexcept override;
	virtual	net::sockaddr		process_get_peer_address(std::error_code& _error_code) const noexcept override;

			bool				m_is_client_socket = false;

			std::atomic<eSOCKET_STATE> m_socket_status{ eSOCKET_STATE::CLOSED };
			object_ptr<executor::Iio_context> m_pio_context;

public:		int					m_last_socket_error{ 0 };
protected:	uint64_t			m_disconnect_reason{ 0 };
			std::atomic<int>	m_io_pending_receive{ 0 };
			ADDRESS_FAMILY		m_address_family{ AF_UNSPEC };

			std::size_t			m_maximum_send_buffer_size{ 0 };
			std::size_t			m_maximum_receive_buffer_size{ 0 };

			bool				m_is_exception_on_send_overflow {false};

			std::atomic<CGSOCKET> m_native_handle{ INVALID_SOCKET };

#if defined(_SYS_EPOLL_H)
public:
			class executable_socket : virtual public Iexecutable, public Npoolable<executable_socket>, public factory::_traits_system
			{
			public:
				virtual ~executable_socket() noexcept {}
			public:
				virtual	intptr_t process_execute( intptr_t _result, std::size_t _param) override { auto psocket = this->m_psocket; RETURN_IF(psocket == nullptr, 0); return psocket->process_execute_epoll(_result, _param); }
				virtual	void on_final_release() noexcept override { this->reset_socket(); }
				void set_socket(Isocket* _psocket) noexcept { if (this->m_psocket == _psocket) return; if (this->m_psocket != nullptr) this->m_psocket->release(); this->m_psocket = _psocket; _psocket->add_ref();}
				void reset_socket() noexcept { auto psocket = this->m_psocket; if (psocket != nullptr) { this->m_psocket = nullptr; psocket->release(); } }
				Isocket* get_socket() const noexcept { return this->m_psocket; }
			private:
				Isocket* m_psocket = nullptr;
			};

			object_ptr<executable_socket> m_pexecutable_socket;
			lockable<>			m_epoll_event_cs;
			CGHANDLE			m_epoll_handle = INVALID_SOCKET;
			uint32_t			m_epoll_event_flag = 0;
			uint32_t			m_epoll_event_flag_queued = 0;
			bool				m_epoll_event_processing_now = false;

			[[nodiscard]] CGHANDLE get_epoll_handle() const noexcept { return this->m_epoll_handle; }
			void				set_epoll_handle(CGHANDLE _handle_epoll) noexcept { this->m_epoll_handle = _handle_epoll; }
			CGHANDLE			reset_epoll_handle() noexcept { auto temp = this->m_epoll_handle; this->m_epoll_handle = INVALID_SOCKET; return temp; }
			CGHANDLE			detach_epoll_handle() noexcept;
			[[nodiscard]] uint32_t get_epoll_event_flag() noexcept { return this->m_epoll_event_flag; }
			void				set_epoll_event_flag(uint32_t _event) noexcept { this->m_epoll_event_flag = _event; }
			void				add_epoll_event_flag(uint32_t _event) noexcept { this->m_epoll_event_flag |= _event; }
			void				remove_epoll_event_flag(uint32_t _event) noexcept { this->m_epoll_event_flag &= (~_event); }
			void				reset_epoll_event_flag() noexcept;
			void				post_epoll_event_EPOLLOUT() noexcept;
			void				process_prepare_executable_socket() { this->m_pexecutable_socket = make_object<executable_socket>(); }
			void				process_reset_executable_socket() noexcept { this->m_pexecutable_socket.reset(); }
	virtual	intptr_t			process_execute_epoll(intptr_t _event, std::size_t _param);
#endif
};

namespace net
{
namespace io
{
	void set_default_socket_debug_logger(Ilogger* _logger) noexcept;
	object_ptr<Ilogger> reset_default_socket_debug_logger() noexcept;
	[[nodiscard]] object_ptr<Ilogger> get_default_socket_logger() noexcept;
	void enable_default_socket_debug_logging(bool _enable = true) noexcept;
	void disable_default_socket_debug_logging() noexcept;
	[[nodiscard]] bool is_default_socket_debug_logging_enabled() noexcept;

	void _debug_log_socket_connected(CGSOCKET _hsocket, net::sockaddr _sockaddr);
	void _debug_log_socket_disconnected(CGSOCKET _hsocket, uint64_t _reason);
	void _debug_log_socket_received(CGSOCKET _hsocket, uint64_t _length, uint64_t _stacked);
	void _debug_log_socket_on_message(CGSOCKET _hsocket, buffer_view _buf_message);
	void _debug_log_socket_send_message(net::io::Isocket* _psocket, buffer_view _buf_message);
}
}

}