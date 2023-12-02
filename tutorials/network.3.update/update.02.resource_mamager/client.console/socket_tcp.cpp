#include "pch.h"

extern own_ptr<update::md5_caching> g_pmd5_caching;


shared_buffer message_UPDATE_UPDATE_REQUEST(update::UPDATE_RESOURCE_ID _updatable_resource_id)
{
	// declare)
	const auto MESSAGE_SIZE = 8 + sizeof(_updatable_resource_id);

	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(MESSAGE_SIZE);

	// 2) write message head
	buf_temp.append<uint32_t>(static_cast<uint32_t>(MESSAGE_SIZE));
	buf_temp.append<uint32_t>(eMESSAGE::UPDATE::REQUEST);

	// 3) ...
	buf_temp.append<update::UPDATE_RESOURCE_ID>(_updatable_resource_id);

	// 4) write message size
	CGASSERT_ERROR(buf_temp.size() == MESSAGE_SIZE);

	// return) 
	return buf_temp;
}

void socket_tcp::on_connect()
{
	// 1) get version of now and required
	update::UPDATE_RESOURCE_ID updatable_resource_id = 106;

	// 2) send
	this->send(message_UPDATE_UPDATE_REQUEST(updatable_resource_id));
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
			ON_CGMESSAGE(CGDK::eMESSAGE::UPDATE::RESPONSE,		on_message_UPDATE_RESPONSE, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

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

		// check)
		THROW_IF(result != eRESULT::SUCCESS, throwable::failure(result));

		// 3) receiver를 생성한다.
		auto preceiver = make_own<update::receiver_lambda>();

		// 4) receiver를 초기화 한다.
		{
			// - set transmitter
			preceiver->set_transmitter(this);

			// - set lambda functions
			preceiver->set_function_update_begin([=](update::receiver_lambda* /*_preceiver*/, const update::sUPDATE_REQUEST_INFO& _update_request_info)
				{
					std::cout << " @ update begin  " << NFMT::format("{} files, {} bytes "sv, _update_request_info.total_count, _update_request_info.total_bytes) << std::endl;
				});

			preceiver->set_function_update_end([=](update::receiver_lambda* _preceiver, eRESULT _result)
				{
					if (_result != eRESULT::DONE)
					{
						std::cout << "  \x1b[31m (!) transfer failed ("sv << to_string<char>(_result) << ")\x1b[0m"sv << std::endl;
					}

					std::cout << "   total \x1b[33m"sv << NFMT::format("{}"sv, _preceiver->get_total_transfered_files()) << "\x1b[0m files"sv << std::endl;
					std::cout << "   total \x1b[33m"sv << NFMT::format("{}"sv, _preceiver->get_total_transfered_bytes()) << "\x1b[0m bytes"sv << std::endl;

					std::cout << " @ update complete"sv << std::endl;
				});

			preceiver->set_function_updatable_prepare([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;
					if ((updatable_file_info.flag & CGDK::resource::eFILE_FLAG::RECREATE) != CGDK::resource::eFILE_FLAG::RECREATE)
						std::cout << "   \x1b[92m[  0%]\x1b[0m "sv << updatable_file_info.path << "/"sv << updatable_file_info.filename;
					else
						std::cout << "\r   \x1b[92m[  0%]\x1b[0m "sv << updatable_file_info.path << "/"sv << updatable_file_info.filename;
				});

			preceiver->set_function_updatable_begin([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* /*_preceivable*/, uint64_t /*_pos_begin*/)
				{
				});

			preceiver->set_function_updatable_process([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable, const resource::sMETA_FILE_BLOCK& _block_info)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;
					auto bytes_now = _block_info.pos + _block_info.size;
					auto bytes_end = updatable_file_info.size;
					auto ratio = static_cast<int>(static_cast<float>(bytes_now) / static_cast<float>(bytes_end) * 100.0f);
					std::cout << "\r   \x1b[92m["sv << NFMT::format("{:3}"sv, ratio) << "%]\x1b[0m "sv;
				});

			preceiver->set_function_updatable_end([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable, eRESULT _result)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;

					if(_result == eRESULT::SUCCESS || _result == eRESULT::ALEADY_DONE)
						std::cout << "\r   \x1b[92m[100%]\x1b[0m " << updatable_file_info.path << "/"sv << updatable_file_info.filename << std::endl;
					else
						std::cout << "\r   \x1b[31m[fail] " << updatable_file_info.path << "/"sv << updatable_file_info.filename << " ("sv <<  to_string<char>(_result) << ")\x1b[0m"sv << std::endl;
				});

			// - md5 캐싱 파일을 설정해 준다.
			preceiver->set_md5_caching(g_pmd5_caching);

			// - root 폴더를 설정해 준다.(이 폴더 이하에 생성될 것이다.)
			preceiver->set_root_path("destination"sv);

			// - socket에 update sender를 등록한다.
			this->m_pupdate_receiver = std::move(preceiver);
		}

		// 5) start!
		this->m_pupdate_receiver->start();
	}
	catch (throwable::failure& _e)
	{
		std::cout << " @ update request failure!!!  ("sv << to_string<char>(_e.reason<eRESULT>()) <<")"sv << std::endl;
	}
	catch (...)
	{
		std::cout << " @ update request failure!!!"sv << std::endl;
	}

	// return)
	return eRESULT::DONE;
}
