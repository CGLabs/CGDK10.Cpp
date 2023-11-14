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

class resolver_base
{
public:
	using flags = int;
	static const flags passive			 = AI_PASSIVE;		// AI_PASSIVE		Returned endpoints are intended for use as locally bound socket endpoints.
	static const flags canonical_name	 = AI_CANONNAME;	// AI_CANONNAME		Determine the canonical name of the host specified in the query.
	static const flags numeric_host		 = AI_NUMERICHOST;	// AI_NUMERICHOST	Host name should be treated as a numeric string defining an IPv4 or IPv6 address and no host name resolution should be attempted.
	static const flags numeric_service	 = AI_NUMERICSERV;	// AI_NUMERICSERV	Service name should be treated as a numeric string defining a port number and no service name resolution should be attempted.
	static const flags v4_mapped		 = AI_V4MAPPED;		// AI_V4MAPPED		If the protocol is specified as an IPv6 protocol, return IPv4-mapped IPv6 addresses on finding no IPv6 addresses.
	static const flags all_matching		 = AI_ALL;			// AI_ALL			If used with v4_mapped, return all matching IPv6 and IPv4 addresses.
	static const flags address_configured= AI_ADDRCONFIG;	// AI_ADDRCONFIG	Only return IPv4 addresses if a non-loopback IPv4 address is configured for the system.
															//					Only return IPv6 addresses if a non-loopback IPv6 address is configured for the system.
protected:
	resolver_base() noexcept {}
	~resolver_base() noexcept {}
};


}