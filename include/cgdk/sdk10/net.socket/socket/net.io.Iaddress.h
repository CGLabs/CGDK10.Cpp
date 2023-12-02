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
// net::io::Iaddress
//
// 1. net::io::Iaddress��!
//    1) socket Address�� peer Address�� ���ϴ� �Լ��� ���� Interface Class
//    2) socket Address : �ڱ� socket Address
//       peer Address : ���ӵ� ����� �ּ�
//
//-----------------------------------------------------------------------------
class net::io::Iaddress : 
	virtual public				Ireferenceable
{
public:
	[[nodiscard]] net::sockaddr	remote_endpoint() const noexcept { std::error_code error_code; return remote_endpoint(error_code); };
	[[nodiscard]] net::sockaddr	remote_endpoint(std::error_code& _error_code) const noexcept { return process_get_peer_address(_error_code); };
	[[nodiscard]] net::sockaddr	local_endpoint() const noexcept { std::error_code error_code; return local_endpoint(error_code); };
	[[nodiscard]] net::sockaddr	local_endpoint(std::error_code& _error_code) const noexcept { return process_get_socket_address(_error_code); };

protected:
	[[nodiscard]] virtual net::sockaddr process_get_socket_address(std::error_code& _error_code) const noexcept PURE;
	[[nodiscard]] virtual net::sockaddr process_get_peer_address(std::error_code& _error_code) const noexcept PURE;
};


}
