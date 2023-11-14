//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::io::connect_requestable::Ntcp_reconnect (자동재접속 기능을 가진 TCP 연결자)
//
//
//-----------------------------------------------------------------------------
class net::io::connect_requestable::Ntcp_reconnect_secure :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp_reconnect,
	virtual public				Icryptable
{
// constructor/destructor)
protected:
			Ntcp_reconnect_secure() noexcept;
			Ntcp_reconnect_secure(std::string_view _name);
	virtual	~Ntcp_reconnect_secure() noexcept;

// public) 
public:
			void				prepare_ssl(bool _flag_enable);

// implementation) 
protected:
	//! @brief reset할때 호출하는 함수.
	virtual	void				process_reset_connector() noexcept override;
	virtual	void				process_complete_connecting(uintptr_t _result) override;

protected:
	object_ptr<crypt::ssl_context>	m_pssl_context;
};


}