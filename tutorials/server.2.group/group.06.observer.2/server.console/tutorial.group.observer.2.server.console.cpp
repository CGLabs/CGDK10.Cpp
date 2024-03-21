#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.observer.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket class
class socket_tcp : 
	public net::socket::tcp<>,
	public Iobserver<socket_tcp>,
	public Nmessage_transmitter
{
private:
	virtual void on_connect() override;
	virtual void on_disconnect(uint64_t) override;
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;

public:
	int	 m_member_serial;
};

class observable_simple : 
	public observable::list_sender<socket_tcp, int64_t>	// @) List형 group을 만든다.
{
protected:
	// @) observer가  입장했을 때 호출되는 함수.
	virtual	void on_observer_registered(socket_tcp* _pmember, observer_channel_t /*_ocid*/, const int64_t& /*_observer_data*/) override
	{
		// trace) 
		std::cout << "observer registered"sv << '\n';

		// - 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(256) << uint32_t() << uint32_t(eMESSAGE_TYPE::ENTER_MEMBER) << _pmember->m_member_serial << "test_id"sv << SET_LENGTH());
	}
	// @) observer가 나갈 때 호출되는 함수.
	virtual	uintptr_t on_observer_unregistering(socket_tcp* _pmember, observer_channel_t /*_ocid*/) override
	{
		// - 모든 group 멤버에 Message 전송
		send(alloc_shared_buffer(12) << uint32_t(12) << uint32_t(eMESSAGE_TYPE::LEAVE_MEMBER) << _pmember->m_member_serial);

		// trace) 
		std::cout << "observer unregistered"sv << '\n';

		// return) 
		return	0;
	}
};

own_ptr<observable_simple> g_pobservable_a;
own_ptr<observable_simple> g_pobservable_b;
int g_member_serial = 0;

void socket_tcp::on_connect()
{
	// 1) 접속하면 먼저 member serial을 써넣는다.
	m_member_serial	 = g_member_serial++;

	// 2) observable channel 1에 등록한다.
	g_pobservable_a->subscribe(this, 1);

	// 3) observable channel 2에 등록한다.
	g_pobservable_a->subscribe(this, 2);
}

void socket_tcp::on_disconnect(uint64_t /*_disconnect_reason*/)
{
	// 1) 모든 observer에서 떼낸다.
	unsubscribe_all();
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
	std::cout << "CGCII tutorial.group.server observer.2..."sv << std::endl;

	// 1) observable 객체를 생성한다.
	g_pobservable_a = make_own<observable_simple>();
	g_pobservable_b = make_own<observable_simple>();

	// 2) Acceptor 객체를 생성한다 / create Acceptor object
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 3) 20000번 포트에 Listen을 시작한다 / start listening on 20000 port
	pacceptor->start({{ net::ip::tcp::v6(), 20000 }});

	// 4) ESC를 눌러 종료하기를 기다린다. / wait for exit pressing ESC key
	while(_getch() != 27);

	// 5) Acceptor를 닫는다 / close Acceptor
	pacceptor->stop();

	// return) 
	return 0;
}
