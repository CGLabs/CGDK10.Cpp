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


class tcp
{
// static)  
public:
	[[nodiscard]] static	tcp v4() noexcept { return tcp(AF_INET); }
	[[nodiscard]] static	tcp v6() noexcept { return tcp(AF_INET6); }

// public) 
public:
	[[nodiscard]] constexpr int type() const noexcept { return SOCK_STREAM; }
	[[nodiscard]] constexpr int protocol() const noexcept { return IPPROTO_TCP; }
	[[nodiscard]] constexpr int family() const noexcept { return family_; }
	[[nodiscard]] constexpr int size() const noexcept
			{
				switch(family())
				{
				case AF_INET:
					return sizeof(sockaddr_in);
				case AF_INET6:
					return sizeof(sockaddr_in6);
				default:
					return 0;
				}
			}

// definitions)
public:
	using endpoint = basic_endpoint<tcp>;
	using resolver = basic_resolver<tcp>;

	//using socket = basic_stream_socket<tcp>;
	//using acceptor = basic_socket_acceptor<tcp>;
	//using iostream = basic_socket_iostream<tcp>;
	//using no_delay = implementation_defined;

	friend bool operator == (const tcp& _lhs, const tcp& _rhs) noexcept { return _lhs.family_ == _rhs.family_; }
	friend bool operator != (const tcp& _lhs, const tcp& _rhs) noexcept { return _lhs.family_ != _rhs.family_; }

private:
	constexpr explicit tcp(int _protocol_family) : family_(_protocol_family){}
	int family_;
};


}