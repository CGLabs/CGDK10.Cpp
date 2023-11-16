#include "pch.h"


void socket_peer::set_update_sender(own_ptr<update::sender>&& _update_sender)
{
	// check) 
	CGASSERT_ERROR(_update_sender.exist());

	// check) 
	THROW_IF(_update_sender.empty(), throwable::failure(eRESULT::INVALID_ARGUMENT, 0, "_update_sender is nullptr"sv));

	// 1) update sender를 socket과 연결한다.
	_update_sender->set_transmitter(this);

	// 2) socket에 update sender를 등록한다.
	this->m_pupdate_sender = std::move(_update_sender);
}

void socket_peer::reset_update_sender() noexcept
{
	// 1) reset update sender
	auto pupdate_sender = std::move(this->m_pupdate_sender);

	// check)
	RETURN_IF(pupdate_sender.empty());

	// 2) reset 
	pupdate_sender->reset_transmitter(this);
}

void socket_peer::on_connect()
{
	g_pservice->m_pgroup_socket_immigration->enter(this);
}

void socket_peer::on_disconnect(uint64_t)
{
	this->leave_group();
}

result_code socket_peer::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) set source
	_msg.set_source(this);

	// 2) transmit message
	TRANSMIT_MESSAGE(_msg);

	// return) 
	return eRESULT::BYPASS;
}
