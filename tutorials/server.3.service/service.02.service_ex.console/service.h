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

class service : public server_system::service_ex
{
public:
	// 1) 생성자에서 service의 구성 객체들을 생성하고 service 객체에 자식 노드로 붙인다.
	service();
	
public:
		own_ptr<net::acceptor<socket_tcp_user>>	m_pacceptor_user = make_own<net::acceptor<socket_tcp_user>>("acceptor_user"sv);
		own_ptr<socket_tcp_server>				m_psocket_tcp = make_own<socket_tcp_server>("socket_tcp"sv);
};
