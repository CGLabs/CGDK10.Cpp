#include "cgdk/sdk10/net.update.h"
using namespace CGDK;

#include "../define_message.h"
#include "socket_update.h"
#include <iostream>
extern own_ptr<update::resource_manager> g_presource_manager;

shared_buffer message_UPDATE_RESPONSE(eRESULT _result)
{
	// declare)
	const auto MESSAGE_SIZE = 8 + sizeof(_result);

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>(static_cast<uint32_t>(MESSAGE_SIZE));
	buf_temp.append<uint32_t>(eMESSAGE::UPDATE::RESPONSE);

	// 3) ...
	buf_temp.append<eRESULT>(_result);

	// 4) write message size
	CGASSERT_ERROR(buf_temp.size() == MESSAGE_SIZE);

	// return) 
	return buf_temp;
}

void socket_update::on_connect()
{
}

void socket_update::on_disconnect(uint64_t)
{
	// 1) unreigster all 
	this->reset_message_transmitter();
}

result_code socket_update::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) transmit message
	TRANSMIT_MESSAGE(_msg);

	// 2) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(eMESSAGE::UPDATE::REQUEST, on_message_UPDATE_REQUEST, sMESSAGE_NETWORK);
			ON_CGMESSAGE(eMESSAGE::UPDATE::COMPLETE, on_message_UPDATE_COMPLETE, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

	// return) 
	return eRESULT::BYPASS;
}

result_code socket_update::on_message_UPDATE_REQUEST(sMESSAGE_NETWORK& _msg)
{
	// 1) get buffer for message de-serialize
	auto buf_recv = _msg.buf_message + offset(8);

	// 2) resource id를 받아서..
	auto resource_id = buf_recv.extract<update::UPDATE_RESOURCE_ID>();

	try
	{
		// 3) get resource
		auto resource_update = g_presource_manager->get_resource(resource_id);

		// check)
		THROW_IF(resource_update.empty(), throwable::failure(eRESULT::NOT_EXIST, 0, "resource not found"sv));

		// 4) make sender
		auto psender = make_object<update::sender_lambda>();

		// 5) initialzing sender
		{
			// - set transmitter
			psender->set_transmitter(this);
			psender->add(resource_update);

			// - set lambda functions
			psender->set_function_update_begin([=](update::sender_lambda* /*_psender*/, const update::sUPDATE_REQUEST_INFO& /*_update_request_info*/) {
				std::cout << "@ update begin" << std::endl;
				});

			// - set on~ functions 
			psender->set_function_update_end([=](update::sender_lambda* _psender, eRESULT /*_result*/) {
				std::cout << "@ update complete" << std::endl;
				std::cout << "  - total transfered files: " << NFMT::format("{}", _psender->get_total_transfered_files()) << std::endl;
				std::cout << "  - total transfered bytes: " << NFMT::format("{}", _psender->get_total_transfered_bytes()) << std::endl;
				});
			psender->set_function_updatable_begin([=](update::sender_lambda* /*_psender*/, const resource::Iupdatable* /*_resource*/, const resource::sUPDATABLE_FILE_META_INFO& _updatable_info) {
				std::cout << "  [send] updating file: " << _updatable_info.filename << std::endl;
				});
			psender->set_function_updatable_process([=](update::sender_lambda* /*_psender*/, const resource::Iupdatable* /*_resource*/, const resource::sMETA_FILE_BLOCK& /*_block_info*/) {
				});
			psender->set_function_updatable_end([=](update::sender_lambda* /*_psender*/, const resource::Iupdatable* /*_resource*/, eRESULT /*_result*/) {
				});
		}

		// 6) 성공 메시지를 보낸다.
		this->send(message_UPDATE_RESPONSE(eRESULT::SUCCESS));

		// 7) start update
		psender->start();
	}
	catch (throwable::failure& _e)
	{
		this->send(message_UPDATE_RESPONSE(_e.reason()));
	}
	catch (...)
	{
		this->send(message_UPDATE_RESPONSE(eRESULT::EXCEPTION));
	}

	// return)
	return eRESULT::DONE;
}

result_code socket_update::on_message_UPDATE_COMPLETE(sMESSAGE_NETWORK& /*_msg*/)
{
	// 1) unreigster all 
	this->reset_message_transmitter();

	// return)
	return eRESULT::DONE;
}
