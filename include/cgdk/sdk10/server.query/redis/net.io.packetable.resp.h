//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Redis Classes                              *
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
// net::io::packetable::Nresp
//
//
//-----------------------------------------------------------------------------
class net::io::packetable::Nresp :
// inherited classes)
	virtual public				net::io::Ipacketable,
	virtual protected			Imessageable,
	virtual protected			net::io::statistics::Nsocket,
	virtual public				net::io::Isender
{
// implementation)
protected:
	virtual	void				process_pre_message(sMESSAGE_RESP& /*_msg*/) {}
	virtual	std::size_t			process_packet( shared_buffer& _buffer, const net::sockaddr& _address) override;
	virtual	void				process_reset_packetable() noexcept override;

private:
			sMESSAGE_RESP		m_msg_resp;
};


}