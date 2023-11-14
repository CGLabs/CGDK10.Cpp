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
// net::io::Naddress
//
// 1. net::io::Iaddress는!
//    1) socket Address와 peer Address를 구하는 함수를 가진 Interface Class
//    2) socket Address : 자기 socket Address
//       peer Address : 접속된 상대의 주소
//
//-----------------------------------------------------------------------------
class net::io::Naddress :
// inherited classes)
	virtual public				net::io::Iaddress
{
// constructor/destructor)
protected:
			Naddress() noexcept {}
	virtual	~Naddress() noexcept {}

// public)
public:
	virtual	net::sockaddr		process_get_socket_address(std::error_code& _error_code) const noexcept override { CGASSERT_ERROR(false); _error_code = std::make_error_code(std::errc::bad_address); return net::sockaddr();}
	virtual	net::sockaddr		process_get_peer_address(std::error_code& _error_code) const noexcept override { _error_code = this->m_endpoint_remote.exist() ? std::error_code() : std::make_error_code(std::errc::bad_address); return this->m_endpoint_remote;}

// implementation)
protected:
			net::sockaddr		m_endpoint_remote;
};


}