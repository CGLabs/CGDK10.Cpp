#include "pch.h"


void user::group_immigration::on_execute()
{
	// 1) ���� �ð��� ��´�.
	auto tick_now = chrono::tick::now();

	// 2) �������� 10�ʰ� �����µ��� ������ group_immigration�� �ִٸ� ������ ������ ���´�.
	for_each_member([=](user::socket* _pmember)
	{
		if (_pmember->statistics_get_tick_connect() + 10s < tick_now)
		{
			_pmember->closesocket();
		}

		// return)
		return true;
	});
}

result_code user::group_immigration::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::REQUEST_USER_CHECKIN, on_message_REQUEST_USER_CHECKIN, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

	// return)message ó���� ���� ���ߴ�!!!
	return eRESULT::BYPASS;
}

result_code user::group_immigration::on_message_REQUEST_USER_CHECKIN(sMESSAGE_NETWORK& _msg)
{
	// 1) �޽����� ������ Source�� ����ϴ�.
	auto psocket = _msg.get_source<user::socket>();

	// check) Source(psocket)�� nullptr�ϸ� �����ϴ�.
	CGASSERT_ERROR(psocket != nullptr);

	// 2) ���޵� �����͹��ۿ��� Client_ID�� �о���ϴ�.

	// Declare) �����͸� �о�� ���� ���������� ����
	auto buf = _msg.buf_message + offset(8);

	// 3) ACCOUNT_ID�� �д´�.
	auto& aid = buf.extract<ACCOUNT_ID>();
	auto nickname = buf.extract<std::string>();

	try
	{
		// check) ����ε� AID���� Ȯ���Ѵ�.
		THROW_IF(aid.valid()==false, throwable::failure(eRESULT::INVALID_ARGUMENT));

		// 4) Socket�� aid�� nickname�� �����Ѵ�.
		psocket->m_aid = aid;
		psocket->m_nickname = std::move(nickname);
		
		// 5) Checkin�� ��û�Ѵ�.
		g_pservice->m_pmanager_user->register_user(psocket);

		// 7) RESPONSE�� �����Ѵ�.
		psocket->send(message_RESPONSE_USER_CHECKIN(eRESULT::SUCCESS));

		// 8) Channel�� ã�´�.
		auto pgroup_channel = g_pservice->m_pmanager_channel->get_channel(CHANNEL_ID(1));

		// check) pgroup_channel�� nullptr�̸� Error�� �����Ѵ�.
		THROW_IF(pgroup_channel.empty(), throwable::failure(eRESULT::NOT_EXIST));

		// 9) Enter�ϰ� �� ����� �����Ѵ�.
		pgroup_channel->enter(psocket);
	}
	catch (throwable::failure& _e)
	{
		// - Checkin ���и� �����Ѵ�.
		psocket->send(message_RESPONSE_USER_CHECKIN(_e.reason()));

		// - ������ �����Ѵ�.
		psocket->disconnect();
	}
	catch(...)
	{
		// - Checkin ���и� �����Ѵ�.
		psocket->send(message_RESPONSE_USER_CHECKIN(eRESULT::FAIL));

		// - ������ �����Ѵ�.
		psocket->disconnect();
	}

	// Return)
	return eRESULT::DONE;
}
