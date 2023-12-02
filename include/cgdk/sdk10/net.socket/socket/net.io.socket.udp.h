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
//    1) UDP�� socket�̴�.
//    2) UDP������ ���� �����̳� �ɼ��� �⺻������ ����ȴ�.
//    3) UDP�� send/receive ���� ũ�⸦ �Ʒ��� ���� �����ϰ� ���� �� �ִ�.
//    4) ConnectReset�� �뺸 ���� ����.
//       - UDP�� ��� ConnectReset�� �߿��ϴ�. send_to�� �������� �� Ư�� 
//         Address�� �����Ҽ� ���� ��Ȳ�� �� send_to�� ����� �뺸���ִ� ���� 
//         �ƴ϶� receive���� CONNECT_RESET Error�� �߻���Ų��. 
//       - �� CONNECT_RESET�� ��� UDP������ ���������� Error�� �ƴ�����
//         �߿��� ������ �ɼ� �ִ�.
//         ���� �� CONNECT_RESET ��ȣ�� ���� ������ ���� ���� ��������
//         �����Ҽ� �ִ�.
//       - �Ϲ����� UDP ���������� ����� ��� �� �ɼ��� ��������
//         reliable UDP�� ��� �� �ɼ��� �ʿ��ϴ�.
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
	// 6) socket�� reset�ϰų� closesocket�� ���� ������ ������ �Լ�.
	//    (�ʿ��� ��� �������Ҽ� �ִ�.)
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
	// 7) connect reset�� �� ���ΰ� �ƴѰ��� �����ϴ� ������.
			bool				m_enable_report_connect_reset = false;	// UDP ConnectReset Report����

	// 8) UDP socket�� �� �⺻ ����Ǵ� Default send/receive shared_buffer ũ��
	static	std::size_t			m_s_default_maximum_send_buffer_size;
	static	std::size_t			m_s_default_receive_buffer_size;

protected:
#if defined(_SYS_EPOLL_H)
	virtual	intptr_t			process_execute_epoll(intptr_t _event, std::size_t _param) override;
#endif
};


}