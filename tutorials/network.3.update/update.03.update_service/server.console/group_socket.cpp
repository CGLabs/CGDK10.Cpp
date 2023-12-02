#include "pch.h"


shared_buffer _message_UPDATE_RESPONSE(eRESULT _result)
{
	// declare)
	const auto MESSAGE_SIZE = 8 + sizeof(eRESULT) /*+ get_size_of(_sender_id) + get_size_of(_update_request_info) */;

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>(static_cast<uint32_t>(MESSAGE_SIZE));
	buf_temp.append<uint32_t>(eMESSAGE::UPDATE::RESPONSE);

	// 3) 
	buf_temp.append<eRESULT>(_result);
	//buf_temp.append<update::SENDER_ID>(_sender_id);
	//buf_temp.append<update::UPDATE_REQUEST_INFO>(_update_request_info);

	// 4) write message size
	CGASSERT_ERROR(buf_temp.size() == MESSAGE_SIZE);

	// return) 
	return buf_temp;
}

void group_socket::on_start(context& /*_msg*/)
{
	// 1) 1�и��� �ѹ��� ȣ��ǵ��� Schedulable�� ������ �����Ѵ�.
	execute_interval(10s);

	// 2) Scheduler��  ����Ѵ�.
	system_executor::register_schedulable(this);

	// 3) ������ �ޱ� ����~
	enable_member_enter(true);
}

void group_socket::on_stopping()
{
	// 1) ������ ����
	disable_member_enter();

	// 2) ���� ��� �����Ѵ�.
	system_executor::unregister_schedulable(this);

	// 3) ��� Group�� ������ ��� Member�� ��� ���� �����Ų��.
	for_each_member([=](socket_tcp* _pmember)->bool
		{
			_pmember->closesocket();
			return true;
		});
}

result_code group_socket::on_member_entering(socket_tcp* _pmember, sMESSAGE& /*_msg*/)
{
	// 1) register messageable�Ѵ�.
	_pmember->register_messageable(this);

	// return) 
	return eRESULT::SUCCESS;
}

uintptr_t group_socket::on_member_leaving(socket_tcp* _pmember, uintptr_t _param)
{
	// 1) unregister messageable�Ѵ�.
	_pmember->unregister_messageable(this);

	// 2) reset update sender
	_pmember->reset_update_sender();

	// return) 
	return _param;
}

void group_socket::on_execute()
{
}

result_code group_socket::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) Message Map
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::UPDATE::REQUEST, on_message_UPDATE_REQUEST, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

	// return)
	return eRESULT::BYPASS;
}

result_code group_socket::on_message_UPDATE_REQUEST(sMESSAGE_NETWORK& _msg)
{
	// 1) get socket
	auto psocket_server = _msg.get_source<socket_tcp>();

	// check)
	CGASSERT_ERROR(psocket_server != nullptr);

	// 2) get buffer for message
	auto buf = _msg.buf_message + offset(8);
	try
	{
		// 3) ���� Ŭ���̾�Ʒ�� ������ ��ġ�� ���� ������ �о��.
		/*auto version_required =*/ buf.extract<update::sUPDATE_VERSION>();
		/*auto version_now =*/ buf.extract<update::sUPDATE_VERSION>();

		// 4) ������ ���� ��ġ�� ���ҽ� ����Ʈ�� ��´�.
		auto vector_updtable = g_pservice->m_presource_manager->get_resource(0);

		if (vector_updtable.empty() == false)
		{
			// - update sender ��ü�� �����Ѵ�.
			auto pupdate_sender = make_own<update::sender>();

			// - ������Ʈ�� ���ҽ� ����Ʈ���� ����Ѵ�.
			pupdate_sender->add(vector_updtable);

			// - update_server�� socket�� �����Ѵ�.
			psocket_server->set_update_sender(std::move(pupdate_sender));

			// - UPDATE_UPDATE_RESPONSE �޽����� �����Ѵ�.
			auto result_send = psocket_server->send(_message_UPDATE_RESPONSE(eRESULT::SUCCESS));

			// check)
			THROW_IF(result_send == false, throwable::failure(eRESULT::FAIL, 0, ""sv));

			// - ������Ʈ ����!
			psocket_server->m_pupdate_sender->start();
		}
		else
		{
			// - reset
			psocket_server->reset_update_sender();

			// - send response
			psocket_server->send(_message_UPDATE_RESPONSE(eRESULT::DONE));
		}
	}
	catch (throwable::failure& _e)
	{
		// - send response
		psocket_server->send(_message_UPDATE_RESPONSE(_e.reason()));
	}
	catch (...)
	{
		// - send response
		psocket_server->send(_message_UPDATE_RESPONSE(eRESULT::EXCEPTION));
	}

	// return)
	return eRESULT::DONE;
}
