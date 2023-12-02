#include "pch.h"


shared_buffer message_NETWORK_CERTIFY_RESPOSNE()
{
	// declare)
	const auto MESSAGE_SIZE = 64;

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::NETWORK::CERTIFY_RESPONSE);

	// 4) write message body
	//buf_temp.append<>();
	//buf_temp.append<>();

	// 5) write message size
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

void group_socket_immigration::on_start(context& /*_msg*/)
{
	// 1) 1분마다 한번씩 호출되도록 Schedulable의 간격을 설정한다.
	execute_interval(10s);

	// 2) Scheduler에  등록한다.
	system_executor::register_schedulable(this);

	// 3) 입장을 받기 시작~
	enable_member_enter(true);
}

void group_socket_immigration::on_stopping()
{
	// 1) 입장을 금지
	disable_member_enter();

	// 2) 실행 등록 해제한다.
	system_executor::unregister_schedulable(this);

	// 3) 모든 Group에 접속한 모든 Member를 모두 접속 종료시킨다.
	for_each_member([=](socket_tcp* _pmember)->bool
	{
		_pmember->closesocket(); 
		return true;
	});
}

result_code group_socket_immigration::on_member_entering(socket_tcp* _pmember, sMESSAGE& /*_msg*/)
{
	// 1) register messageable한다.
	_pmember->register_messageable(this);

	// return) 
	return eRESULT::SUCCESS;
}

uintptr_t group_socket_immigration::on_member_leaving(socket_tcp* _pmember, uintptr_t _param)
{
	// 1) unregister messageable한다.
	_pmember->unregister_messageable(this);

	// return) 
	return _param;
}

void group_socket_immigration::on_execute()
{
	// 1) 현재 시간을 얻는다.
	auto tick_now = chrono::tick::now();

	// 2) 접속한지 10초가 지났는데도 여전히 Immigration에 있다면 접속을 강제로 끊는다.
	for_each_member([=](socket_tcp* _pmember)
	{
		if (_pmember->statistics_get_tick_connect() + 10s < tick_now)
		{
			//_pmember->closesocket();
		}

		// return) 
		return	true;
	});
}

result_code group_socket_immigration::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::NETWORK::CERTIFY_REQUEST, on_message_NETWORK_CERTIFY_REQUEST, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP
	
	// return)
	return eRESULT::BYPASS;
}

result_code group_socket_immigration::on_message_NETWORK_CERTIFY_REQUEST(sMESSAGE_NETWORK& _msg)
{
	// 1) get source
	auto psocket = _msg.get_source<socket_tcp>();

	// 2) get buffer for message
	//auto buf = _msg.buf_message + offset(8);

	// 3) send response message
	psocket->send(message_NETWORK_CERTIFY_RESPOSNE());

	// 4) enter to group
	g_pservice->m_pgroup_socket->enter(psocket);

	// return)
	return eRESULT::DONE;
}
