#include "pch.h"


void group_channel::on_member_entered(socket_user* _pmember, CGDK::sMESSAGE& /*param*/)
{
	// 1) ���ο� Member�� ������ this�� �޽��� ����ó�� ����Ѵ�.
	_pmember->register_messageable(this);

	// 2) ��� group ������� _pmember�� ������ �˸���.
	this->send(alloc_shared_buffer(256) << uint32_t() << uint32_t(eMESSAGE_TYPE::ENTER_MEMBER) << _pmember->m_user_id << "test_id" << CGDK::SET_LENGTH());

	// 3) _pmember���� ������ �˸���.
	//_pmember->send();
}

uintptr_t group_channel::on_member_leaving(socket_user* _pmember, uintptr_t /*_param*/)
{
	// 1) ��� group ����� _pmember�� ������ �˸���.
	this->send(alloc_shared_buffer(12) << uint32_t(12) << uint32_t(eMESSAGE_TYPE::LEAVE_MEMBER) << _pmember->m_user_id);

	// 2) message mediator���� ��� �����Ѵ�.
	_pmember->unregister_messageable(this);

	// return) 
	return 0;
}

CGDK::result_code group_channel::on_message(CGDK::sMESSAGE_NETWORK& _msg)
{
	// 1) message_type�� ��´�.
	auto message_type = _msg.buf_message.front<eMESSAGE_TYPE>(4);

	// 3) message ������ ���� ó���Ѵ�.
	switch (message_type)
	{
	case	eMESSAGE_TYPE::SEND_CHAT:
			return on_message_SEND_CHAT(_msg);
			break;

	case	eMESSAGE_TYPE::ENTER_MEMBER:
			return on_message_REQUEST_ENTER(_msg);
			break;

	default:
			break;
	}

	// return) 
	return eRESULT::BYPASS;
}

CGDK::result_code group_channel::on_message_SEND_CHAT(CGDK::sMESSAGE_NETWORK& _msg)
{
	// 1) ��ü���� �ٷ� �����Ѵ�.
	this->send(_msg.buf_message);

	// return) 
	return eRESULT::DONE;
}

CGDK::result_code group_channel::on_message_REQUEST_ENTER(CGDK::sMESSAGE_NETWORK& /*_msg*/)
{
	// return)
	return eRESULT::DONE;
}
