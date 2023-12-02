#include "pch.h"


void user::group_immigration::on_execute()
{
	// 1) 현재 시간을 얻는다.
	auto tick_now = chrono::tick::now();

	// 2) 접속한지 10초가 지났는데도 여전히 group_immigration에 있다면 접속을 강제로 끊는다.
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

	// return)message 처리를 하지 못했다!!!
	return eRESULT::BYPASS;
}

result_code user::group_immigration::on_message_REQUEST_USER_CHECKIN(sMESSAGE_NETWORK& _msg)
{
	// 1) 메시지를 전달한 Source를 얻습니다.
	auto psocket = _msg.get_source<user::socket>();

	// check) Source(psocket)이 nullptr일리 없습니다.
	CGASSERT_ERROR(psocket != nullptr);

	// 2) 전달된 데이터버퍼에서 Client_ID를 읽어냅니다.

	// Declare) 데이터를 읽어내기 위한 버퍼포인터 생성
	auto buf = _msg.buf_message + offset(8);

	// 3) ACCOUNT_ID를 읽는다.
	auto& aid = buf.extract<ACCOUNT_ID>();
	auto nickname = buf.extract<std::string>();

	try
	{
		// check) 제대로된 AID인지 확인한다.
		THROW_IF(aid.valid()==false, throwable::failure(eRESULT::INVALID_ARGUMENT));

		// 4) Socket의 aid와 nickname을 설정한다.
		psocket->m_aid = aid;
		psocket->m_nickname = std::move(nickname);
		
		// 5) Checkin을 요청한다.
		g_pservice->m_pmanager_user->register_user(psocket);

		// 7) RESPONSE를 전송한다.
		psocket->send(message_RESPONSE_USER_CHECKIN(eRESULT::SUCCESS));

		// 8) Channel을 찾는다.
		auto pgroup_channel = g_pservice->m_pmanager_channel->get_channel(CHANNEL_ID(1));

		// check) pgroup_channel이 nullptr이면 Error를 리턴한다.
		THROW_IF(pgroup_channel.empty(), throwable::failure(eRESULT::NOT_EXIST));

		// 9) Enter하고 그 결과를 리턴한다.
		pgroup_channel->enter(psocket);
	}
	catch (throwable::failure& _e)
	{
		// - Checkin 실패를 전송한다.
		psocket->send(message_RESPONSE_USER_CHECKIN(_e.reason()));

		// - 접속을 종료한다.
		psocket->disconnect();
	}
	catch(...)
	{
		// - Checkin 실패를 전송한다.
		psocket->send(message_RESPONSE_USER_CHECKIN(eRESULT::FAIL));

		// - 접속을 종료한다.
		psocket->disconnect();
	}

	// Return)
	return eRESULT::DONE;
}
