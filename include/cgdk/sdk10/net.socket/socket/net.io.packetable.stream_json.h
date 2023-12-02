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
/*!
 * @class Nstream_json
 *
 * @ingroup net::io::packetable
 *
 * @brief JSON¿ë packetable Class
 *
 */
 //-----------------------------------------------------------------------------
class net::io::packetable::Nstream_json :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ipacketable,
	virtual public				Imessageable,
	virtual public				net::io::statistics::Nsocket
{
// implementation)
protected:
	virtual	void				process_pre_message(sMESSAGE_NETWORK& /*_msg*/) {}
	virtual	std::size_t			process_packet(shared_buffer& _buffer, const net::sockaddr& _address) override;
	virtual	void				process_reset_packetable() noexcept override { reset_message_history();}
};


}