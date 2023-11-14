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
// net::io::sendable::Ntcp_sync
//
// 1. net::io::sendable::Ntcp_sync란!
//    1) TCP용 send로 한번의 send를 한번의 Overlapped I/O로 걸어서 수행하는 
//       sendable이다.
//    2) 한번의 send에 한번의 Overlapped I/O를 쓰기 때문에 구조가 간단하여 send
//       빈도가 낮은 socket에서는 좋은 성능을 낸다.
//    3) 하지만 send의 빈도가 높은 socket에서는 많은 I/O가 오히려 성능이 떨어질
//       수 있으므로 빈도가 높은 send를 수행하는 socket에서는 이 sendable대신
//       send Gathering을 수행하는 TCPGathering을 사용하도록 권한다.
//    4) 대부분의 Server socket이나 Client socket의 경우 이 간단한 sendable로
//       충분하다.
//
// 2. net::io::sendable::CTCP의 핵심! Function의 기능 설명
//    1) process_sendable()		buffer를 전송한다.
//
//
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_sync :
	virtual public				net::io::Isendable,
	virtual public				net::io::Iconnectable
{
protected:
	virtual	bool				process_sendable(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
	virtual	void				process_reset_sendable() noexcept override;

#if defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable(intptr_t _event, std::size_t _param) override;
#endif

	#if defined(_WINSOCK2API_)
			bool				process_sendable_async(CGSOCKET _handle_socket, const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message);
	#endif
};


}