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

 @class		Nudp
 @brief		비동기 전송을 하는 UDP sendable 클래스
 @todo		
 @ref		
 @details	\n

 비동기 전송을 수행하는 UDP sendable 클래스이다.
 Overlapped를 사용해 전송을 수행한다.
*/
//-----------------------------------------------------------------------------
class net::io::sendable::Nudp : 
	virtual public				net::io::Isocket,
	virtual public				net::io::Isendable,
	virtual public				net::io::statistics::Nsocket
{
protected:
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable( uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;

#if defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable( intptr_t _event, std::size_t _param) override;
#endif

	//! @brief 초기화 될 때 호출되는 함수.
	virtual	void				process_reset_sendable() noexcept override;
};


}