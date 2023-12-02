#if defined(_WIN32)
	#include <conio.h>
#endif

#include "cgdk/sdk10/net.update.h"
#include "../define_message.h"
#include <iostream>

using namespace CGDK;


own_ptr<update::resource_manager> g_presource_manager;
std::vector<object_ptr<resource::Iupdatable>> g_vector_resource_updatable;

class socket_tcp_server : 
	public net::socket::tcp<>,
	public Nmessage_transmitter
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;
			result_code on_message_UPDATE_REQUEST(sMESSAGE_NETWORK& _msg);
};

void socket_tcp_server::on_connect()
{
}

void socket_tcp_server::on_disconnect(uint64_t)
{
	// 1) unreigster all 
	this->reset_message_transmitter();
}

result_code socket_tcp_server::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) transmit message
	TRANSMIT_MESSAGE(_msg);

	// 2) execute message
	BEGIN_NESTED_CGMESSAGE_MAP
		CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, ((sMESSAGE_BUFFER&)_msg).buf_message.front<uint32_t>(4))
			ON_CGMESSAGE(CGDK::eMESSAGE::UPDATE::REQUEST, on_message_UPDATE_REQUEST, sMESSAGE_NETWORK);
		END_SUB_CGMESSAGE_MAP
	END_NESTED_CGMESSAGE_MAP

	// return) 
	return eRESULT::BYPASS;
}

result_code socket_tcp_server::on_message_UPDATE_REQUEST(sMESSAGE_NETWORK& /*_msg*/)
{
	// 1) ..
	{
		// - make sender
		auto psender = make_object<update::sender_lambda>();

		// - set transmitter
		psender->set_transmitter(this);

		// - add file resource
		//psender->add({ vector_updatable });
		psender->add(g_vector_resource_updatable);

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

		// - connnect and send file
		psender->start();
	}

	// return)
	return eRESULT::DONE;
}

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	try
	{
		std::cout << "load resource..."sv << std::endl;

		// 1) update해줄 파일들읽어 오기
		//    - update 자원인 resource::updatae::file을 생성해 초기화합니다.
		//      resource::updatae::file 객체를 먼저 생성한 후에 file읠 path와 file명을 설정하면 해당 파일을 읽어 드립니다.
		//      다양한 옵션을 사용할 수 있습니다.
		//		이렇게 초기화 한 resource 파일들을 g_vector_resource_updatable에 모아 놓았다가 update sender('update::sender_lambda')를 
		//		생성해 전송을 하기전 추가해 줍니다.
		//		한번 생성된 resource는 계속 update sender에 추가해 사용이 가능합니다.
		//
		// 
		//   - 옵션 설정하기
		// 
		//      (1) 압축 옵션 - resource::eOPTION::BLOCK_COMPRESSED
		//          압축 옵션은 파일을 읽어 들인 후 압축을 하여 저장하기 때문에 초기화에 더 많은 시간이 필요합니다.
		//          이미 압축된 파일인 경우 압축 효율이 낮을 수 있기 때문에 선택적 사용이 필요합니다.
		//          압축 옵션을 사용했다 하더라도 압축된 파일이 원본크기의 95%가 넘을 경우 압축하지 않은 원본을 사용합니다.
		// 
		//      (2) 스트림 옵션 - resource::eOPTION::STREAMS
		//          파일을 한꺼번에 읽어서 준비하는 것이 아니라 업데이트를 진행할 때 필요한 부분만 읽어 들인 후 업데이트를 진행하는 옵션입니다.
		//          초기화 시간이 많이 걸리지 않으며 메모리를 많이 사용하지 않는다는 장점이 있씁니다.
		//          따라서 이 옵션은 다음과 같은 경우 유리합니다.
		// 
		//          - 초기화 시간이 짧을 필요가 있을 경우
		//          - 파일 크기가 매우 커서 한꺼번에 메모리에 올려 놓기 부담스러운 경우.
		//          - 한번의 업데이트만 필요할 경우 혹은 업데이트가 빈번하지 않은 경우.
		//
		//      (3) 재귀 옵션 - resource::eOPTION::RECURSIVE
		//			folder에만 해당하는 옵션으로 하위 folder까지 모두 읽어 들이도록 하는 옵션입니다.
		//
		//		(4) 삭제 옵션 - resource::eOPTION::REMOVE
		//          해당 파일을 찾아 삭제하는 옵션입니다. 
		//          클라이언트의 해당 path와 file의 파일을 찾아 삭제해줍니다.
		//			필요없어진 파일을 정리해주는 용도로 사용되는 옵션입니다.
		//          당연히 server측에는 해당 파일이 존재할 필요가 없습니다.
		//          와일드 카드(* 혹은 ?)를 파일명으로 사용이 가능하며 해당하는 파일을 모구 삭제해줍니다.
		//			다만 삭제 클라이언트 파일의 속성에 따라 실패할 수도 있습니다. 
		//
		//		(5) 폴더 삭제 옵션 - resource::eOPTION::REMOVE_FOLDER
		//          폴더를 삭제하는 옵션입니다.
		// 
		//		(6) 찾기 옵션 - resource::eOPTION::FIND
		//			해당 파일의 존재 여부를 서버측에 통보해줍니다. 
		//			업데이트 종료 후 해당 파일의 존재 여부가 서버측에 통보되서 각종 처리에 이용될수 있습니다.
		//			특정 폴더나 파일 정보를 활용해 업데이트를 결정하거나 혹은 하지 않을 수 있습니다.
		// 
		// 		(7) 이동 옵변 - resource::eOPTION::MOVE
		//			해당파일을 해당 위치로 이동시켜 줍니다.
		//			일반적으로 클라이언트 내에 백업이 필요하나 이동 후 신규 생성 처리를 해야할 필요가 있을 경우 사용됩니다.
		//

		// 2) 일반적인 파일 읽기
		{
			std::cout << " > file > 'data_source/folder_1/999_girl_007.gif'"sv << std::endl;
			auto presource_file = make_object<resource::updatable::file>();
			presource_file->initialize({{ "data_source"s, "folder_1"s, "999_이혜원_007.gif"s},{}, resource::eOPTION::BLOCK_COMPRESSED });
			g_vector_resource_updatable.push_back(presource_file);
		}

		// 3) 용량이 큰 파일 읽기
		{
			std::cout << " > file > 'data_source/folder_1/Mazinger.Z.TV.1972.DVDRip-Hi.x264.AC3.1024.EP01-nezumi.mkv'"sv << std::endl;
			auto presource_file = make_object<resource::updatable::file>();
			presource_file->initialize({ { "data_source"s, "folder_1"s, "Mazinger.Z.TV.1972.DVDRip-Hi.x264.AC3.1024.EP01-nezumi.mkv"s}, {}, resource::eOPTION::BLOCK_COMPRESSED });
			g_vector_resource_updatable.push_back(presource_file);
		}

		// 4) /data_source 폴더 밑 파일 읽기
		{
			std::cout << " > file > './data_source/999_이혜원_007.gif'"sv << std::endl;
			auto presource_file = make_object<resource::updatable::file>();
			presource_file->initialize({ { "data_source"s, "."s, "iu_06.gif"s}, {}, resource::eOPTION::BLOCK_COMPRESSED });
			g_vector_resource_updatable.push_back(presource_file);
		}

		// 5) /data_source 폴더 밑 큰 파일 읽기
		{
			std::cout << " > file './data_source/Mazinger.Z.TV.1972.DVDRip-Hi.x264.AC3.1024.EP01-nezumi.mkv'"sv << std::endl;
			auto presource_file = make_object<resource::updatable::file>();
			presource_file->initialize({ { "data_source"s, "."s, "Mazinger.Z.TV.1972.DVDRip-Hi.x264.AC3.1024.EP01-nezumi.mkv"s}, {}, resource::eOPTION::BLOCK_COMPRESSED });
			g_vector_resource_updatable.push_back(presource_file);
		}

		// 6)  folder 통채로 읽어들이기
		{
			std::cout << " > folder './data_source/folder_2"sv << std::endl;
			auto presource_folder = make_object<resource::updatable::folder>();
			presource_folder->initialize({ {"data_source"s, "."s, "folder_2"s}, {}, resource::eOPTION::BLOCK_COMPRESSED | resource::eOPTION::RECURSIVE });
			g_vector_resource_updatable.push_back(presource_folder);
		}

		std::cout << std::endl;
		std::cout << "start server [tut.update.01.tcp_simple.server]..."sv << std::endl;

		// 2) acceptor 객체를 생성한다.
		auto pacceptor = make_own<net::acceptor<socket_tcp_server>>();

		// 3) acceptor를 시작한다.(20000번 포트에서 listen을 시작한다.)
		pacceptor->start({ { net::ip::make_address("any"sv), 31000 } });

		// 3) ESC키를 누를 때까지 대기한다.
		while (_getch() != 27);
	}
	catch (...)
	{

	}

	// trace) 
	std::cout << "stop server [tut.update.01.tcp_simple.server]..."sv << std::endl;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;

	// end) 서버 종료
	return 0;
}
