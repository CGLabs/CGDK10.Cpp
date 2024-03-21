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
	int	 m_member_serial;
};

class group_a :
	public group::array_seat_sender<socket_tcp>,
	public net::io::messageable::Nbase
{
protected:
	virtual	void	on_member_entered(socket_tcp* _pmember, sMESSAGE& /*param*/) override
	{
		// trace) 
		std::cout << "on_member_entered> member entered ('group_a')\n"sv << std::endl;

		// - send message to all group member
		send(alloc_shared_buffer(256) << uint32_t() << uint32_t(eMESSAGE_TYPE::ENTER_MEMBER) << _pmember->m_member_serial << "test_id"sv << SET_LENGTH());
	}
	virtual	uintptr_t on_member_leaving(socket_tcp* /*_pmember*/, uintptr_t /*_param*/) override
	{
		// trace) 
		std::cout << "on_member_leaving> member leaved ('group_a')\n"sv << std::endl;

		// return) 
		return	0;
	}
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// trace)
		std::cout << "one_message> message received! ('group_a')\n"sv << std::endl;

		// - echo message to all group member
		send(_msg.buf_message);

		// return) 
		return eRESULT::BYPASS;
	}
};

class group_b :
	public group::count<socket_tcp>,
	public net::io::messageable::Nbase
{
protected:
	virtual	void	on_member_entered(socket_tcp* /*_pmember*/, sMESSAGE& /*param*/) override
	{
		// trace) 
		std::cout << "on_member_entered> member entered ('group_b')\n"sv << std::endl;
	}
	virtual	uintptr_t on_member_leaving(socket_tcp* /*_pmember*/, uintptr_t /*_param*/) override
	{
		// trace) 
		std::cout << "on_member_leaving> member leaved ('group_b')\n"sv << std::endl;

		// return) 
		return	0;
	}
	virtual result_code on_message(sMESSAGE_NETWORK& /*_msg*/) override
	{
		// trace)
		std::cout << "one_message> message received! ('group_b')\n"sv << std::endl;

		// return) 
		return	eRESULT::BYPASS;
	}
};

class group_c :
	public group::Nmap_sender<socket_tcp, int64_t>,
	public net::io::messageable::Nbase
{
protected:
	virtual	void on_member_entered(socket_tcp* _pmember, sMESSAGE& /*param*/) override
	{
		// trace) 
		std::cout << "on_member_entered> member entered ('group_c')\n"sv << std::endl;

		// - send message to all group member
		send(alloc_shared_buffer(256) << uint32_t() << uint32_t(eMESSAGE_TYPE::ENTER_MEMBER) << _pmember->m_member_serial << "test_id"sv << SET_LENGTH());
	}
	virtual	uintptr_t on_member_leaving(socket_tcp* /*_pmember*/, uintptr_t /*_param*/) override
	{
		// trace) 
		std::cout << "on_member_leaving> member leaved ('group_c')\n"sv << std::endl;

		// return) 
		return	0;
	}
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// trace)
		std::cout << "one_message> message received! ('group_c')\n"sv << std::endl;

		// - echo message to all group member
		send(_msg.buf_message);

		// return) 
		return eRESULT::BYPASS;
	}
	// @) 멤버의 고유 키를  리턴해주는 함수다. group::Nmap_sender클래스 group의 경우 이걸 반드시 정의해줘야한다.
	virtual	int64_t process_get_member_key(socket_tcp* _pmember) override
	{
		return _pmember->m_member_serial;
	}
};

own_ptr<group_a> g_pgroup_a;
own_ptr<group_b> g_pgroup_b;
own_ptr<group_c> g_pgroup_c;
int g_member_serial = 0;

void socket_tcp::on_connect()
{
	// 1) 접속하면 먼저 Member Serial을 써넣는다.
	m_member_serial	 = g_member_serial++;

	// 2) group에 Enter시킨다.
	g_pgroup_a->enter(this);
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

int main(int /*argc*/, char* /*argv*/[])
{
	// trace) 
	std::cout << "CGCII tutorial.group.server ex01..."sv << std::endl;

	// 1) group_a, group_b, group_c를 생성한다.
	g_pgroup_a = make_own<group_a>();
	g_pgroup_b = make_own<group_b>();
	g_pgroup_c = make_own<group_c>();

	// 2) group에 입장 가능하게 설정한다.
	g_pgroup_a->enable_member_enter();
	g_pgroup_b->enable_member_enter();
	g_pgroup_c->enable_member_enter();

	// 3) Acceptor 객체를 생성한다 / create Acceptor object
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 4) 20000번 포트에 Listen을 시작한다 / start listening on 20000 port
	pacceptor->start({{ net::ip::tcp::v6(), 20000 }});

	// 5) ESC를 눌러 종료하기를 기다린다. / wait for exit pressing ESC key
	while(_getch() != 27);

	// 6) Acceptor를 닫는다 / close Acceptor
	pacceptor->stop();

	return 0;
}

