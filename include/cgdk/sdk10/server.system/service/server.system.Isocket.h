//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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

class server_admin::Isocket : public net::socket::tcp_buffered<>
{
public:
			Isocket();
	virtual	~Isocket() noexcept;

public:
	[[nodiscard]] auto&			lockable_remote_service_setting() noexcept { return this->m_cs_remote_service_setting; }
	[[nodiscard]] const auto&	remote_service_setting() const noexcept { return this->m_remote_service_setting; }

protected:
			lockable<>			m_cs_remote_service_setting;
			server_admin::sSERVICE_SETTING m_remote_service_setting;
};

} 