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
// net::io::sender::Nstream
//
// 1. net::io::sender::CStream은~
//    1) 가장 일반적인 sender로 net::io::Isend_request의 request_send()함수를 호출해
//       준다.
//    2) 한번의 전송에 한번의 Overlapped I/O를 걸어 send()를 수행하는 sender로
//       가장 일반적이고 기본적인 sender이다. 
//       하지만 작은 message를 대량으로 한꺼번에 보내게 되면 성능이 많이 떨어진다.
//       만약 message를 대량으로 한꺼번에 효율적으로 전송하고 싶다면 Nstream_gather
//       클래스를 사용하길 권장한다.
//
// 2. 핵심함수!
//    1) BOOL send(const buffer& _buffer);
//       말 그대로 전송을 수행하는 함수이다. buffer에 전송할 message를 넣고 send()
//       함수를 호출하며 그 버퍼를 넘기면 전송이 된다.
//
//-----------------------------------------------------------------------------
class net::io::sender::Nhttp : 
// inherited classes)
	virtual protected			net::io::Isendable,
	virtual protected			net::io::Isender,
	virtual protected			net::io::Isocket,
	virtual public				net::io::statistics::Nsocket
{
public:
	// 1) process send
	virtual	bool				process_send( shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};


}