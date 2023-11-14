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
// net::connector
//
//  1) 여려 개의 클라이언트 socket을 접속관리하는 객체이다.
//
//-----------------------------------------------------------------------------
template <class TSOCKET, class FLAG = void>
class net::connector
{
};

//-----------------------------------------------------------------------------
// socket for connect
//-----------------------------------------------------------------------------
template <class TSOCKET>
class CONNECTABLE_SOCKET_TCP :
	public TSOCKET,
	public net::io::connect_requestable::Ntcp_reconnect
{
public: virtual ~CONNECTABLE_SOCKET_TCP() noexcept {}
};

namespace factory
{
	template<class T> class _factory_name<CONNECTABLE_SOCKET_TCP<T>>
	{
	public:
		static std::string_view get_default_name() noexcept
		{
			return std::string_view(typeid(T).name());
		}
	};
}

}