//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                        tutorials service - simple                         *
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

class service : public server_system::service
{
public:
	// 1) �����ڿ��� service�� ���� ��ü���� �����ϰ� service ��ü�� �ڽ� ���� ���δ�.
	service();
	
protected:
	// 2) service�� ��ũ �Լ���...
	virtual	void				on_initialize_request(context& _context) override;
	virtual	void				on_initializing(context& _context) override;
	virtual	void				on_initialize(context& _context) override;

	virtual	void				on_start_request(context& _context) override;
	virtual	void				on_starting(context& _context) override;
	virtual	void				on_start(context& _context) override;

	virtual	void				on_stop_request() override;
	virtual	void				on_stopping() override;
	virtual	void				on_stop() override;

	virtual	void				on_destroy_request() override;
	virtual	void				on_destroying() override;
	virtual	void				on_destroy() override;

public:
	// 2) service ���� ��ü��
	//    - ������ �����ϴ� ���� ��ü�� service�� �����ڿ��� �����ϰ� �ڽ� ���� ���δ�.
	//    - �׷��� �ڽĳ���� 
		own_ptr<net::acceptor<socket_tcp_user>>	m_pacceptor_user = make_own<net::acceptor<socket_tcp_user>>("acceptor_user"sv);
		own_ptr<socket_tcp_server>				m_psocket_tcp = make_own<socket_tcp_server>("socket_tcp"sv);
};
