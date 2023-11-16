//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials update - update service                      *
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
			service();
public:
	// 1) update manager
			own_ptr<update::resource_manager> m_presource_manager;

	// 2) group
			own_ptr<group_socket>		m_pgroup_socket;
			own_ptr<group_socket_immigration> m_pgroup_socket_immigration;

	// 3) acceptor
			own_ptr<net::acceptor<socket_tcp>> m_pacceptor_tcp;
};
