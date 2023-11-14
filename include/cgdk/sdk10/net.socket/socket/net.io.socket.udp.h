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
// net::io::socket::Nudp
//
//    1) UDP용 socket이다.
//    2) UDP용으로 각종 설정이나 옵션이 기본적으로 적용된다.
//    3) UDP의 send/receive 버퍼 크기를 아래와 같이 설정하고 얻을 수 있다.
//    4) ConnectReset의 통보 여부 설정.
//       - UDP의 경우 ConnectReset이 중요하다. send_to로 전송했을 때 특정 
//         Address에 전달할수 없는 상황일 때 send_to의 결과로 통보해주는 것이 
//         아니라 receive에서 CONNECT_RESET Error를 발생시킨다. 
//       - 이 CONNECT_RESET의 경우 UDP에서는 실질적으로 Error가 아니지만
//         중요한 정보가 될수 있다.
//         따라서 이 CONNECT_RESET 신호를 받을 것인지 받지 않을 것인지를
//         설정할수 있다.
//       - 일반적인 UDP 소켓으로의 사용일 경우 이 옵션은 꺼주지만
//         reliable UDP의 경우 이 옵션이 필요하다.
//
//-----------------------------------------------------------------------------
class net::io::socket::Nudp :
#if defined(_WINSOCK2API_)
	public						Nbase,
	public                      object::Ninitializable_startable,
	virtual public				net::io::Ibinder
#elif defined(_SYS_EPOLL_H)
	public						Nbase,
	public                      object::Ninitializable_startable,
	virtual public				net::io::Ibinder,
	virtual public				net::io::Isendable,
	virtual	public				net::io::Ireceivable_datagram
#endif
{
public:
			using end_point_type = net::ip::udp::endpoint;
			struct START_PARAMETER
			{
				end_point_type	bind_endpoint = end_point_type{ net::ip::address_v4::any(), 0 };
				bool			enable_report_connect_reset = false;
			};

protected:
			Nudp();
	virtual	~Nudp() noexcept;

public:
	// 1) start
			result_code			start() { return this->object::Nstartable::start(); }
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) };  return this->start(temp); }
			result_code			start(const context& _context ) { return this->object::Nstartable::start(_context); }
	virtual	result_code			start(context& _context) override { return this->object::Nstartable::start(_context); }

	// 2) udp send/receive shared_buffer
	static	void				set_default_maximum_send_buffer_size(std::size_t _size) noexcept { m_s_default_maximum_send_buffer_size = _size;}
	[[nodiscard]] static std::size_t default_maximum_send_buffer_size() noexcept { return m_s_default_maximum_send_buffer_size;}
																						  
	static	void				set_default_receive_buffer_size(std::size_t _size) noexcept	{ m_s_default_receive_buffer_size = _size;}
	[[nodiscard]] static std::size_t get_default_receive_buffer_size() noexcept { return m_s_default_receive_buffer_size;}

	// 3) for Multicast
			bool				set_multicast_ttl(int _TTL);
			bool				set_multicast_loopback(bool _enable=false);
			bool				add_multicast_membership(const ip_mreq& _ip_mreq_add);
			bool				drop_multicast_membership(const ip_mreq& _ip_mreq_drop);

protected:
	// 6) socket을 reset하거나 closesocket할 때의 과정을 정의한 함수.
	//    (필요할 경우 재정의할수 있다.)
	virtual	void				process_create_socket(ADDRESS_FAMILY _address_family = AF_INET) override;
	virtual void				process_dispose_socket() noexcept override;
	virtual	bool				process_close_socket(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

	virtual	result_code			process_start(context& _context) override;
	virtual	result_code			process_stop() noexcept override;
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;

	virtual	net::sockaddr		process_get_peer_address(std::error_code& _error_code) const noexcept override { _error_code = std::error_code(); return net::ip::udp::endpoint(); }

// implementation) 
private:
	// 7) connect reset을 할 것인가 아닌가를 설정하는 변수임.
			bool				m_enable_report_connect_reset = false;	// UDP ConnectReset Report여부

	// 8) UDP socket에 에 기본 적용되는 Default send/receive shared_buffer 크기
	static	std::size_t			m_s_default_maximum_send_buffer_size;
	static	std::size_t			m_s_default_receive_buffer_size;

protected:
#if defined(_SYS_EPOLL_H)
	virtual	intptr_t			process_execute_epoll(intptr_t _event, std::size_t _param) override;
#endif
};


}