#include "pch.h"


channel::group_waiting::group_waiting()
{
	this->m_type_channel = eCHANNEL_TYPE::WAITING;
	this->m_option_channel = eCHANNEL_OPTION::SYSTEM;
}

channel::group_waiting::~group_waiting() noexcept
{
}

void channel::group_waiting::on_destroy()
{
	// 1) get manager
	auto pmanager = this->m_pmanager;

	// 2) unregister group
	if (pmanager.exist())
	{
		pmanager->unregister_channel(m_id_channel);
	}
}

void channel::group_waiting::on_member_entered(user::socket* _pmember, sMESSAGE& /*_param*/)
{
	// 1) Register Mediator한다.
	_pmember->register_messageable(this);

	// 2) message를 전송한다.
	_pmember->send(message_NOTIFY_ENTER_CHANNEL(m_id_channel, eRESULT::SUCCESS, name().data()));
}

void channel::group_waiting::on_member_leaved(user::socket* _pmember, uintptr_t /*_result*/)
{
	// 1) Unregister Mediator한다.
	_pmember->unregister_messageable(this);
}

result_code channel::group_waiting::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::REQUEST_ENTER_CHANNEL,		on_message_REQUEST_ENTER_CHANNEL,	sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP
	
	// return) message 처리를 하지 못했다!!!
	return eRESULT::BYPASS;
}

result_code channel::group_waiting::on_message_REQUEST_ENTER_CHANNEL(sMESSAGE_NETWORK& _msg)
{
	// 1) 메시지를 전달한 Source를 얻습니다.
	auto psocket = _msg.get_source<user::socket>();

	// check) Source(psocket)이 nullptr일리 없습니다.
	CGASSERT_ERROR(psocket != nullptr);

	// 2) CHANNEL_ID와 CHANNEL_OPTION을 읽어들인다.
	auto buf = _msg.buf_message + offset(8);
	auto cid = buf.extract<CHANNEL_ID>();

	try
	{
		// check) 읽어들인 CHANNEL_ID가 잘못된 ID인지 확인한다.(일단 여기서는 0이면 오류.)
		THROW_IF(cid == 0, throwable::failure(eRESULT::INVALID_ARGUMENT));

		// 3) Channel을 찾는다.
		auto pgroup_channel = g_pservice->m_pmanager_channel->get_channel(cid);

		// check) pgroup_channel이 nullptr이면 Error를 리턴한다.
		THROW_IF(pgroup_channel.empty(), throwable::failure(eRESULT::NOT_EXIST));

		// 4) Enter하고 그 결과를 리턴한다.
		auto result = pgroup_channel->enter(psocket);

		// check) 입장 결과가 SUCCESS가 아니면 Excetion을 던진다.
		THROW_IF(result != eRESULT::SUCCESS, throwable::failure(result));
	}
	catch (throwable::failure& e)
	{
		// - error 결과를 전송한다.
		this->send(message_NOTIFY_ENTER_CHANNEL(cid, static_cast<eRESULT>(e.m_reason)));
	}
	catch (...)
	{
		// - error 결과를 전송한다.
		this->send(message_NOTIFY_ENTER_CHANNEL(cid, eRESULT::EXCEPTION));
	}

	// return)
	return eRESULT::DONE;
}
