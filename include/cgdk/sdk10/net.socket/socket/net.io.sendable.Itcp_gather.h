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
/**

 @class		Itcp_gather
 @brief		비동기 모움 전송을 수행하는 sendable 클래스
 @todo		
 @ref		
 @details	\n

 비동기 송신 중일 경우나 소켓의 송신버퍼가 꽉차 블록킹된 상태(WOULD_BLOCK)인 상태일 때 
 send를 요청하면 큐잉해 놓았다가 비동기가 완료되거나 블로킹이 해제되면 모아 놓았던 데이터를 
 전송하는 sendable클래스이다.
 송신을 비동기적으로 수행함으로써 송신 성능을 극대화하고 CPU의 사용을 최소화 할수 있다.
 
*/
//-----------------------------------------------------------------------------
class net::io::sendable::Itcp_gather :
	virtual public				net::io::Isendable,
	virtual public				net::io::Iconnectable
{
public:
			Itcp_gather() noexcept;

public:
	[[nodiscard]] size_t		maximum_depth_of_send_buffer() const noexcept { return this->m_max_depth_of_send_buffer; }
			void				maximum_depth_of_send_buffer(std::size_t _depth) noexcept;
	[[nodiscard]] size_t		maximum_depth_of_send_buffer_bytes() const noexcept { return this->m_bytes_max_queued; }
			void				maximum_depth_of_send_buffer_bytes(std::size_t _size) noexcept;
	[[nodiscard]] size_t		sending_queued_bytes_now() const noexcept { return this->process_get_sending_queued_bytes(); }

	static	void				default_maximum_depth_of_send_buffer(std::size_t _max) noexcept;
	[[nodiscard]] static size_t default_maximum_depth_of_send_buffer() noexcept;
	static	void				default_maximum_queued_bytes(std::size_t _max) noexcept;
	[[nodiscard]] static size_t default_maximum_queued_bytes() noexcept;

protected:
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept PURE;

protected:
			std::size_t			m_bytes_max_queued;
			std::size_t			m_max_depth_of_send_buffer;

	static	std::size_t			m_s_default_max_queued_bytes;
	static	std::size_t			m_s_default_max_depth_of_send_buffer;
};


}