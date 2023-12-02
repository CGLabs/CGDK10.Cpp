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
// net::socket::smtp
//
//    1) 기본적인 tcp 소켓으로 send/receive 등을 수행할 수 있다.
//
// ----------------------------------------------------------------------------
class net::email::smtp::socket:
	public						net::io::connect_requestable::Ntcp,
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::sendable::tcp::Ndefault,
	public						net::io::receivable::tcp::Ndefault,
	virtual public				net::io::Ipacketable
{
public:
			void				request_send(sREQUEST&& _email_send_request);
			bool				cancel_sending() noexcept;

			bool				is_exist() const noexcept;

protected:
	virtual void				on_connect() override;
	virtual	void				on_disconnect(uint64_t _reason) override;

	virtual	void				on_email_sending(sREQUEST& /*_email_send_request*/) {}
	virtual	void				on_email_sended(const sRESULT& /*_email_send_result*/) {}

private:
	virtual	result_code			process_message(sMESSAGE& _msg) override;
	virtual	std::size_t			process_packet(shared_buffer& _buffer, const net::sockaddr& _address_peer) override;
	virtual	void				process_reset_packetable() noexcept override;
			void				process_email_complete();

			lockable<>			m_cs_email_smtp_result;
			sRESULT				m_email_smtp_result;
			object_ptr<smtp>	m_psmtp;

			friend class smtp;
};


}