//*****************************************************************************
//*                                                                           *
//*                            CGCII update system                            *
//*                       simple update server ver.10.0                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
//*                          http://www.CGCIII.co.kr                          *
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
			own_ptr<net::acceptor<socket_peer>> m_pacceptor_tcp;
};
