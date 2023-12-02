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
// net::io::Isendable
//
// 1. net::io::Isendable은~
//    1) 데이터를 전송을 I/O함수를 사용하여 구현한 저수준 처리를 정의하는 함수.
//    2) process_send()는 데이터의 전송을 요청하는 처리 과정을 정의하는 함수.
//    3) process_complete_sendable()는 데이터의 전송이 완료되었을 때 호출되어 처리
//       과정을 정의하는 함수이다.
//
//-----------------------------------------------------------------------------
class net::io::Isendable : virtual public Ireferenceable
{
public:
	//! @brief 전송 처리 과정을 정의하는 함수. @param _array_buffer 전송할 버퍼 배열 @param _count_buffer 버퍼의 개수 @param _powner 전송중 참조계수를 유지할 객체 전송중일 때에는 참조계수가 1 증가하며 전송이 완료되면 1 감소시킨다. @param _paddress 전송할 주소(UDP전용)  @return true 성공  @return false 실패
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _address) PURE;
	//! @brief 전송이 완료되었을 때 처리를 정의하는 함수.
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred, std::size_t _count_message) PURE;

#if defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable( intptr_t _event, std::size_t _param) PURE;
#endif

	//! @brief 초기화 될 때 호출되는 함수.
	virtual	void				process_reset_sendable() noexcept PURE;
};


}