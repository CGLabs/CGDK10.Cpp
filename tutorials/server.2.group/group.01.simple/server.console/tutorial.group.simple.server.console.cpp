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
	public Igroupable<socket_tcp>
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;

public:
	int	 m_member_serial;
};

class group_simple : 
	public group::list_sender<socket_tcp>	// @) List형 group을 만든다.
{
protected:
	// @) group에 새로운 멤버가 입장했을 때 호출되는 함수.
	virtual	void	on_member_entered(socket_tcp* _pmember, sMESSAGE& /*param*/) override
	{
		// trace) 
		std::cout << "on_member_entered>> member entered (id:"sv << _pmember->m_member_serial << ")\n"sv;

		// - 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(256) 
			<< uint32_t()
			<< uint32_t(eMESSAGE_TYPE::ENTER_MEMBER)
			<< _pmember->m_member_serial
			<< "test_id"sv
			<< SET_LENGTH());
	}

	// @) group에서 멤버가 나갈 때 호출되는 함수.
	virtual	uintptr_t on_member_leaving(socket_tcp* _pmember, uintptr_t /*_param*/) override
	{
		// 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(12)
			<< uint32_t(12)
			<< uint32_t(eMESSAGE_TYPE::LEAVE_MEMBER)
			<< _pmember->m_member_serial);

		// trace) 
		std::cout << "on_member_leaving>> member leaved (id:"sv << _pmember->m_member_serial << ")\n"sv;

		return	0;
	}
};

own_ptr<group_simple> g_pgroup;
std::atomic<int> g_member_serial{ 0 };

void socket_tcp::on_connect()
{
	// 1) 접속하면 먼저 Member Serial을 써넣는다.
	m_member_serial = g_member_serial++;

	// trace) 
	std::cout << "on_connect>> connected id:"sv << m_member_serial << '\n';

	// 2) group에 Enter시킨다.
	g_pgroup->enter(this);
}

void socket_tcp::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	// trace) 
	std::cout << "on_disconnect>> disconnected id:"sv << m_member_serial << '\n';

	// 1) 접속이 종료되면 group에서 나간다.
	leave_group();
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) group 전체에게 메시지를 echo 전송한다.
	g_pgroup->send(_msg.buf_message);

	// return) 
	return eRESULT::DONE;
}

int main(int /*argc*/, char* /*argv*/[])
{
	// trace) 
	std::cout << "CGCII tutorial.group.server 01..."sv << '\n';

	// 1) group 객체를 생성한다 / create group object
	g_pgroup = make_own<group_simple>();

	// 2) group에 입장 가능하게 설정한다 / enable entering of group object
	g_pgroup->enable_member_enter();

	// 3) Acceptor 객체를 생성한다 / create acceptor object
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 4) 20000번 포트에 Listen을 시작한다 / start listening on 20000 port
	pacceptor->start({{ net::ip::tcp::v6(), 20000 }});

	// 5) ESC를 눌러 종료하기를 기다린다. / wait for exit pressing ESC key
	while(_getch() != 27);

	// 6) Acceptor를 닫는다 / close acceptor
	pacceptor->stop();

	return 0;
}
