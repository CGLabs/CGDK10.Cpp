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
// net::io::sendable::Ntcp_async_rio
//
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_async_rio :
	virtual public				net::io::Isendable,
	virtual public				net::io::Iconnectable
{
protected:
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable( uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
	virtual	void				process_reset_sendable() noexcept override;

		#if defined(_WINSOCK2API_)
			bool				process_sendable_async( CGSOCKET _handle_socket, const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message);
		#endif
};


}