#include "pch.h"


channel::group_chatting::group_chatting()
{
	this->m_type_channel = eCHANNEL_TYPE::CHATTING;
	this->m_option_channel = eCHANNEL_OPTION::DESTROY_ON_EMPTY;
	this->member_capacity(12);
}

channel::group_chatting::~group_chatting() noexcept
{
}

void channel::group_chatting::on_destroy()
{
	// 1) get manager
	auto pmanager = m_pmanager;

	// 2) unregister group
	if (pmanager.exist())
	{
		pmanager->unregister_channel(this->m_id_channel);
	}
}

void channel::group_chatting::on_member_entered(user::socket* _pmember, sMESSAGE& /*_param*/)
{
	// 1) Register Mediator�Ѵ�.
	_pmember->register_messageable(this);

	// 2) message�� �����Ѵ�.
	_pmember->send(message_NOTIFY_ENTER_CHANNEL(this->m_id_channel, eRESULT::SUCCESS, name().data()));
}

void channel::group_chatting::on_member_leaved(user::socket* _pmember, uintptr_t /*_result*/)
{
	// 1) Unregister Mediator�Ѵ�.
	_pmember->unregister_messageable(this);

	// 2) _result�� 0�� �ƴϸ� Destroy�Ѵ�.
	if ((this->m_option_channel & eCHANNEL_OPTION::DESTROY_ON_EMPTY) != eCHANNEL_OPTION::NONE && this->member_count() == 0)
	{
		this->destroy();
	}
}

result_code channel::group_chatting::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::SEND_CHATTING_MESSAGE,		on_message_SEND_CHATTING_MESSAGE,	sMESSAGE_NETWORK);
			ON_CGMESSAGE(eMESSAGE::REQUEST_ENTER_CHANNEL,		on_message_REQUEST_ENTER_CHANNEL,	sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP
	
	// return)message ó���� ���� ���ߴ�!!!
	return eRESULT::BYPASS;
}

result_code channel::group_chatting::on_message_SEND_CHATTING_MESSAGE(sMESSAGE_NETWORK& _msg)
{
	// 1) ��ü���� ���� Buffer�� �״�� �����Ѵ�.
	this->send(_msg.buf_message);

	// return)
	return eRESULT::DONE;
}

result_code channel::group_chatting::on_message_REQUEST_ENTER_CHANNEL(sMESSAGE_NETWORK& _msg)
{
	// 1) �޽����� ������ Source�� ����ϴ�.
	auto psocket = _msg.get_source<user::socket>();

	// check) Source(psocket)�� nullptr�ϸ� �����ϴ�.
	CGASSERT_ERROR(psocket != nullptr);

	// 2) CHANNEL_ID�� CHANNEL_OPTION�� �о���δ�.
	auto buf = _msg.buf_message + offset(8);
	auto cid = buf.extract<CHANNEL_ID>();

	try
	{
		// check) �о���� CHANNEL_ID�� �߸��� ID���� Ȯ���Ѵ�.(�ϴ� ���⼭�� 0�̸� ����.)
		THROW_IF(cid == 0, throwable::failure(eRESULT::INVALID_ARGUMENT));

		// 8) Channel�� ã�´�.
		auto pgroup_channel = g_pservice->m_pmanager_channel->get_channel(cid);

		// check) pgroup_channel�� nullptr�̸� Error�� �����Ѵ�.
		THROW_IF(pgroup_channel.empty(), throwable::failure(eRESULT::NOT_EXIST));

		// 9) Enter�ϰ� �� ����� �����Ѵ�.
		auto result = pgroup_channel->enter(psocket);

		// check) ���� ����� SUCCESS�� �ƴϸ� Excetion�� ������.
		THROW_IF(result != eRESULT::SUCCESS, throwable::failure(result));
	}
	catch (throwable::failure& e)
	{
		// - Error ����� �����Ѵ�.
		this->send(message_NOTIFY_ENTER_CHANNEL(cid, static_cast<eRESULT>(e.m_reason)));
	}
	catch (...)
	{
		// - Error ����� �����Ѵ�.
		this->send(message_NOTIFY_ENTER_CHANNEL(cid, eRESULT::EXCEPTION));
	}

	// return)
	return eRESULT::DONE;
}
