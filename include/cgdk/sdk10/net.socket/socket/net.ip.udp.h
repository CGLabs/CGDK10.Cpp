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

namespace CGDK::net::ip
{


class udp
{
// static)  
public:
	[[nodiscard]] static udp v4() noexcept { return udp(AF_INET); }
	[[nodiscard]] static udp v6() noexcept { return udp(AF_INET6); }
						 
// public) 
public:
	 [[nodiscard]] constexpr int type() const noexcept { return SOCK_DGRAM; }
	 [[nodiscard]] constexpr int protocol() const noexcept { return IPPROTO_UDP; }
	 [[nodiscard]] constexpr int family() const noexcept { return family_; }
	 [[nodiscard]] constexpr int size() const noexcept
			{
				switch(family())
				{
				case AF_INET:
					return	sizeof(sockaddr_in);
				case AF_INET6:
					return	sizeof(sockaddr_in6);
				default:
					return	0;
				}
			}

// definitions)
public:
	using endpoint = basic_endpoint<udp>;
	using resolver = basic_resolver<udp>;

	//using socket = basic_datagram_socket<udp>;

	friend bool operator == (const udp& _lhs, const udp& _rhs) noexcept { return _lhs.family_ == _rhs.family_; }
	friend bool operator != (const udp& _lhs, const udp& _rhs) noexcept { return _lhs.family_ != _rhs.family_; }

private:
	constexpr explicit udp(int _protocol_family) noexcept : family_(_protocol_family){}
	int family_;
};


}