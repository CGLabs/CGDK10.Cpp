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
	// 1) 생성자에서 service의 구성 객체들을 생성하고 service 객체에 자식 노드로 붙인다.
	service();
	
protected:
	// 2) service의 후크 함수들...
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
	// 2) service 구성 객체들
	//    - 서버를 구성하는 각종 객체로 service의 생성자에서 생성하고 자식 노드로 붙인다.
	//    - 그러면 자식노드들과 
		own_ptr<net::acceptor<socket_tcp_user>>	m_pacceptor_user = make_own<net::acceptor<socket_tcp_user>>("acceptor_user"sv);
		own_ptr<socket_tcp_server>				m_psocket_tcp = make_own<socket_tcp_server>("socket_tcp"sv);
};
