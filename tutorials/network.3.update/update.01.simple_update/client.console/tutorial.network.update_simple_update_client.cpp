#include "cgdk/sdk10/net.update.h"
#include "../define_message.h"
#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


shared_buffer message_UPDATE_REQUEST(const sREQUEST_UPDATE& _update_request)
{
	// 1) alloc buffer
	auto buf_temp = alloc_shared_buffer(8 + get_size_of(_update_request));

	// 2) message head
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::UPDATE::REQUEST);

	// 3) message body
	buf_temp.append<sREQUEST_UPDATE>(_update_request);

	// 4) write mesage size
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return)
	return buf_temp;
}

own_ptr<update::md5_caching> g_pmd5_caching;

class socket_tcp_client : 
	public net::socket::tcp_client<>,
	public Nmessage_transmitter
{
	virtual void on_connect() override
	{
		std::cout << " @ connected"sv << '\n';

		// 1) make client info 
		sREQUEST_UPDATE temp_update_request;
		temp_update_request.version_now = CGDK::update::sUPDATE_VERSION{ 0,0 };
		temp_update_request.version_request = CGDK::update::sUPDATE_VERSION{ 0,0 };

		// 2) request update request
		this->send(message_UPDATE_REQUEST(temp_update_request));
	}
	virtual void on_fail_connect(uint64_t /*_disconnect_reason*/) override
	{
		std::cout << " @ fail to connecting"sv << '\n';
	}
	virtual void on_disconnect(uint64_t) override
	{
		std::cout << " @ disconnected"sv << '\n';
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// 1) transmit message
		TRANSMIT_MESSAGE(_msg);

		// 2) execute message
		BEGIN_NESTED_CGMESSAGE_MAP
			CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
				ON_CGMESSAGE(CGDK::eMESSAGE::UPDATE::BEGIN_REQUEST, on_message_UPDATE_BEGIN_REQUEST, sMESSAGE_NETWORK);
			END_SUB_CGMESSAGE_MAP
		END_NESTED_CGMESSAGE_MAP

		// return) 
		return eRESULT::BYPASS;
	}

	result_code on_message_UPDATE_BEGIN_REQUEST(sMESSAGE_NETWORK& _msg)
	{
		// 1) receiver를 생성한다.
		auto preceiver = make_object<update::receiver_lambda>();

		// 2) receiver를 초기화 한다.
		{
			// - set transmitter
			preceiver->set_transmitter(this);

			// - set lambda functions
			preceiver->set_function_update_begin([=](update::receiver_lambda* /*_preceiver*/, const update::sUPDATE_REQUEST_INFO& _update_request_info)
				{
					std::cout << " @ update begin  " << NFMT::format("{} files, {} bytes "sv, _update_request_info.total_count, _update_request_info.total_bytes) << std::endl;
				});

			preceiver->set_function_update_end([=](update::receiver_lambda* _preceiver, eRESULT /*_result*/)
				{
					std::cout << "   total \x1b[33m"sv << NFMT::format("{}"sv, _preceiver->get_total_transfered_files()) << "\x1b[0m files"sv << std::endl;
					std::cout << "   total \x1b[33m"sv << NFMT::format("{}"sv, _preceiver->get_total_transfered_bytes()) << "\x1b[0m bytes"sv << std::endl;
					std::cout << " @ update complete"sv << std::endl;
				});

			preceiver->set_function_updatable_begin([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable, uint64_t /*_pos_begin*/)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;
					if ((updatable_file_info.flag & CGDK::resource::eFILE_FLAG::RECREATE) != CGDK::resource::eFILE_FLAG::RECREATE)
						std::cout << "   \x1b[92m[  0%]\x1b[0m "sv << updatable_file_info.path << "/"sv << updatable_file_info.filename;
					else
						std::cout << "\r   \x1b[92m[  0%]\x1b[0m "sv << updatable_file_info.path << "/"sv << updatable_file_info.filename;
				});

			preceiver->set_function_updatable_process([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable, const resource::sMETA_FILE_BLOCK& _block_info)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;
					auto bytes_now = _block_info.pos + _block_info.size;
					auto bytes_end = updatable_file_info.size;
					auto ratio = static_cast<int>(static_cast<float>(bytes_now) / static_cast<float>(bytes_end) * 100.0f);
					std::cout << "\r   \x1b[92m["sv << NFMT::format("{:3}"sv, ratio) << "%]\x1b[0m "sv;
				});

			preceiver->set_function_updatable_end([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* _preceivable, eRESULT /*_result*/)
				{
					const auto& updatable_file_info = _preceivable->m_meta_info;
					std::cout << "\r   \x1b[92m[100%]\x1b[0m " << updatable_file_info.path << "/"sv << updatable_file_info.filename << std::endl;
				});

			// - md5 캐싱 파일을 설정해 준다.
			preceiver->set_md5_caching(g_pmd5_caching);

			// - root 폴더를 설정해 준다.(이 폴더 이하에 생성될 것이다.)
			preceiver->set_root_path("destination"sv);
		}

		// 3) start!
		preceiver->start();

		// 4) message bypass
		preceiver->request_process_message(_msg);

		// return) 
		return eRESULT::DONE;
	}
};

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	// trace) 
	std::cout << "start client [tut.update.01.simple_update.client]..."sv << '\n';

	g_pmd5_caching = make_own<update::md5_caching>();
	g_pmd5_caching->start("destination/update_caching.info"sv);

	// 1) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp_client>();

	// 2) 최대 메시지 크기를 늘려준다.
	psocket->maximum_message_buffer_size(16 * 1024 * 1024); // 16Mbyte

	// 2) 20000번 포트에서 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({ { net::ip::address_v4::loopback(), 31000 } });

	// 3) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop client [tut.update.01.simple_update.client]..."sv << '\n';

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;

	// end) 종료
	return 0;
}
