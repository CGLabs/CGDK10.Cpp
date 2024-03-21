#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.group.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket class
class socket_tcp :
	public net::socket::tcp<>,
	public Igroupable<socket_tcp>,
	public Nmessage_transmitter
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;

public:
	int m_member_serial;
	int m_received_message = 0;
};

class group_simple : 
	public group::list_sender<socket_tcp>,
	public net::io::messageable::Nbase
{
protected:
	virtual	void	on_member_entered(socket_tcp* _pmember, sMESSAGE& /*param*/) override
	{
		// trace) 
		std::cout << "on_member_entered>> member entered id:"sv << _pmember->m_member_serial << '\n';

		// 1) 새로운 Member가 들어오면 this를 메시지 전달처로 등록한다.
		_pmember->register_messageable(this);

		// 2) 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(256) << uint32_t() << uint32_t(eMESSAGE_TYPE::ENTER_MEMBER) << _pmember->m_member_serial << "test_id"sv << SET_LENGTH());
	}
	virtual	uintptr_t on_member_leaving(socket_tcp* _pmember, uintptr_t /*_param*/) override
	{
		// 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(12) << uint32_t(12) << uint32_t(eMESSAGE_TYPE::LEAVE_MEMBER) << _pmember->m_member_serial);

		// 2) message mediator에서 등록 해제한다.
		_pmember->unregister_messageable(this);

		// trace)
		std::cout << "on_member_leaving>> member leaved id:"sv << _pmember->m_member_serial << '\n';

		// return) 
		return 0;
	}
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// 1) source
		auto psource = _msg.get_source<socket_tcp>();

		// 2) psource에게 받은 message 수를 증가한다.
		++psource->m_received_message;

		// trace)
		std::cout << "message received! ("sv << psource->m_received_message << ")"sv << std::endl;

		// 3) member 전체에게 메시지를 전달한다.
		send(_msg.buf_message);

		// return) 
		return eRESULT::BYPASS;
	}
};

own_ptr<group_simple> g_pgroup;
int g_member_serial = 0;

void socket_tcp::on_connect()
{
	// 1) 접속하면 먼저 Member Serial을 써넣는다.
	m_member_serial = g_member_serial++;

	// 2) group에 Enter시킨다.
	g_pgroup->enter(this);
}

void socket_tcp::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	// 1) 접속이 종료되면 group에서 나간다.
	leave_group();
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) set source
	_msg.set_source(this);

	// 2) dispatch message
	TRANSMIT_MESSAGE(_msg);

	// return) 
	return eRESULT::BYPASS;
}

int main()
{
	// trace) 
	std::cout << "CGCII tutorial.group.server 02..."sv << std::endl;

	// 1) group 객체를 생성한다 / create group object
	g_pgroup = make_own<group_simple>();

	// 2) group에 입장 가능하게 설정한다 / enable entering of group object
	g_pgroup->enable_member_enter();

	// 3) Acceptor 객체를 생성한다 / create acceptor object
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 4) 20000번 포트에 Listen을 시작한다 / start listening on 20000 port
	pacceptor->start({{ net::ip::tcp::v6(), 20000 }});

	// 5) ESC를 눌러 종료하기를 기다린다. / waiting input ESC key and exit 
	while(_getch() != 27);

	// 6) Acceptor를 닫는다 / close acceptor
	pacceptor->stop();

	return 0;
}
