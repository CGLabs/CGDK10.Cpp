//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           asio network classes                            *
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

#if defined(_WIN32)
	#include <SDKDDKVer.h>
#endif

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <set>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

using namespace boost::asio::ip;
using boost::asio::mutable_buffer;
using boost::asio::const_buffer;

namespace asio
{
	class Isocket_tcp;

	class Nstatistics;
	class Nconnective;
	class Nacceptor;
	class Nconnector;
	class Nsocket_tcp;
	class Nsocket_tcp_client;

	template <class> class acceptor;
	template <class> class connector;

	class system;
}
const size_t RECEIVE_BUFFER_SIZE = 8192;

#include "asio.Nstatistics.h"
#include "asio.Isocket_tcp.h"
#include "asio.Nsocket_tcp.h"
#include "asio.Nsocket_tcp_client.h"
#include "asio.Nconnective.h"
#include "asio.Nacceptor.h"
#include "asio.Nconnector.h"
#include "asio.acceptor.h"
#include "asio.connector.h"
#include "asio.system.h"