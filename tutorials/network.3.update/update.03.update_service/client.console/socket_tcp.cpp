#include "pch.h"

extern own_ptr<update::md5_caching> g_pmd5_caching;


shared_buffer message_NETWORK_CERTIFY_REQUEST()
{
	// declare)
	const auto MESSAGE_SIZE = 64;

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::NETWORK::CERTIFY_REQUEST);

	// 4) write message body
	//buf_temp.append<>();
	//buf_temp.append<>();

	// 5) write message size
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

shared_buffer message_UPDATE_REQUEST(update::sUPDATE_VERSION _version_required, update::sUPDATE_VERSION _version_now)
{
	// declare)
	const auto MESSAGE_SIZE = 8 + sizeof(update::sUPDATE_VERSION) + sizeof(update::sUPDATE_VERSION);

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>(static_cast<uint32_t>(MESSAGE_SIZE));
	buf_temp.append<uint32_t>(eMESSAGE::UPDATE::REQUEST);

	// 3) 
	buf_temp.append<update::sUPDATE_VERSION>(_version_required);
	buf_temp.append<update::sUPDATE_VERSION>(_version_now);

	// 4) write message size
	CGASSERT_ERROR(buf_temp.size() == MESSAGE_SIZE);

	// return) 
	return buf_temp;
}

void socket_tcp::on_connect()
{
	// 1) send
	this->send(message_NETWORK_CERTIFY_REQUEST());

}

void socket_tcp::on_fail_connect(uint64_t /*_disconnect_reason*/)
{
}

void socket_tcp::on_disconnect(uint64_t)
{
	// 1) get..
	auto pupdate_receiver = std::move(this->m_pupdate_receiver);

	// check)
	if (pupdate_receiver.exist())
	{
		// - reset transmitter
		pupdate_receiver->reset_transmitter(this);
	}
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) transmit message
	TRANSMIT_MESSAGE(_msg);

	// 2) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(CGDK::eMESSAGE::NETWORK::CERTIFY_RESPONSE, on_message_NETWORK_CERTIFY_RESPONSE, sMESSAGE_NETWORK);
			ON_CGMESSAGE(CGDK::eMESSAGE::UPDATE::RESPONSE, on_message_UPDATE_RESPONSE, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

	// return) 
	return eRESULT::BYPASS;
}

result_code socket_tcp::on_message_NETWORK_CERTIFY_RESPONSE(sMESSAGE_NETWORK& /*_msg*/)
{
	// 1) get version of now and required
	update::sUPDATE_VERSION version_required {0, 0}; // {0.0} is last version
	update::sUPDATE_VERSION version_now {0, 0};

	// 2) send
	this->send(message_UPDATE_REQUEST(version_required, version_now));

	// return)
	return eRESULT::BYPASS;
}

result_code socket_tcp::on_message_UPDATE_RESPONSE(sMESSAGE_NETWORK& _msg)
{
	// 1) get buffer for message
	auto buf = _msg.buf_message + offset(8);

	try
	{
		// 2) get result
		auto result = buf.extract<eRESULT>();

		if (result == eRESULT::SUCCESS)
		{
			// 4) update sender를 생성하고 설정한다.
			{
				// - update sender 각체를 생성한다.
				auto pupdate_receiver = make_own<update::receiver_lambda>();

				// - update sender를 socket과 연결한다.
				pupdate_receiver->set_transmitter(this);

				// - destination folder를 설정한다.
				pupdate_receiver->set_root_path("./destination"sv);

				// - set lambda functions
				pupdate_receiver->set_function_update_begin([=](update::receiver_lambda* /*_pupdate_receiver*/, const update::sUPDATE_REQUEST_INFO& _update_request_info) {
					std::cout << " @ update begin  " << NFMT::format("{} files, {} bytes "sv, _update_request_info.total_count, _update_request_info.total_bytes) << std::endl;
					struct UPDATE_REQUEST_INFO
					{
					};
					});

				pupdate_receiver->set_function_update_end([=](update::receiver_lambda* _pupdate_receiver, eRESULT /*_result*/) {
					std::cout << " @ update complete" << std::endl;
					std::cout << "   - total transfered files: " << NFMT::format("{}", _pupdate_receiver->get_total_transfered_files()) << std::endl;
					std::cout << "   - total transfered bytes: " << NFMT::format("{}", _pupdate_receiver->get_total_transfered_bytes()) << std::endl;
					});

				pupdate_receiver->set_function_updatable_begin([=](update::receiver_lambda* /*_pupdate_receiver*/, update::Ireceivable* _preceivable, uint64_t /*_pos_begin*/) {
					const auto& updatable_file_info = _preceivable->m_meta_info;

					if ((updatable_file_info.flag & CGDK::resource::eFILE_FLAG::RECREATE) != CGDK::resource::eFILE_FLAG::RECREATE)
						std::cout << "   [receive] updating file: " << updatable_file_info.filename << std::endl;
					else
						std::cout << "             - retry file: " << updatable_file_info.filename << std::endl;

					});

				pupdate_receiver->set_function_updatable_process([=](update::receiver_lambda* /*_pupdate_receiver*/, update::Ireceivable* /*_preceivable*/, const resource::sMETA_FILE_BLOCK& /*_block_info*/) {
					});

				pupdate_receiver->set_function_updatable_end([=](update::receiver_lambda* /*_pupdate_receiver*/, update::Ireceivable* /*_preceivable*/, eRESULT /*_result*/) {
					});

				pupdate_receiver->set_md5_caching(g_pmd5_caching);

				// - socket에 update sender를 등록한다.
				this->m_pupdate_receiver = std::move(pupdate_receiver);
			}

			// 5) 업데이트 시작!
			this->m_pupdate_receiver->start();
		}
		else if (result == eRESULT::DONE)
		{
			std::cout << " @ aleady done!" << std::endl;
		}
		else
		{
			throw throwable::failure(result, 0, ""sv);
		}
	}
	catch (...)
	{

	}

	// return)
	return eRESULT::BYPASS;
}
