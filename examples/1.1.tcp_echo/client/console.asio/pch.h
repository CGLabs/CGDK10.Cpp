#ifndef PCH_H
#define PCH_H

// 1) CGCII header files
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <set>
#include <deque>
#include <memory>

// 
using namespace boost::asio::ip;
using boost::asio::mutable_buffer;
using boost::asio::const_buffer;

// 2) C++ standard header files
#if defined(_WIN32)
	#include <conio.h>
#endif

#endif //PCH_H
