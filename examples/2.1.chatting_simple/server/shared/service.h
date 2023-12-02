//*****************************************************************************
//*                                                                           *
//*                     CGCII simple chatting system (1)                      *
//*                                                                           *
//*                             chatting Server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// service
//-----------------------------------------------------------------------------
class service : 
	public						server_system::service_ex
{
public:
			service();
	virtual	~service() noexcept;

public:
			own_ptr<user::manager>				m_pmanager_user;
			own_ptr<channel::manager>			m_pmanager_channel;
			own_ptr<user::group_immigration>	m_pgroup_user_immigration;
			own_ptr<net::acceptor<user::socket>> m_pacceptor_user;
};
