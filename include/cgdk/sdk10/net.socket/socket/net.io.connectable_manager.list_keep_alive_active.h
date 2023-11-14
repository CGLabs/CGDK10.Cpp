//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// net::io::connectable_manager::CListKeepAliveActive
//
// 1. net::io::connectable_manager::CListKeepAliveActive
//    1) acceptor�� �޾� ���ӿ� ������ socket�鿡 ���ؼ� Active-KeepAlive�� �����ϴ� 
//       connectable manager�̴�.
//    2) Active keep-alive�� �� socket���� ������ ���۹��� �ð����κ��� �����ð��� 
//       ������ keep alive�� �����ϱ� ���� Ping�� �����Ѵ�.
//       Ŭ���̾�Ʈ�� �� Ping�� ���۹����� Ping�� �ٽ� �����ϰ� �� ���̴�.
//       �׷��� �Ǹ� ������ ���۹��� �ð��� �ٽ� ����ǰ� �Ǿ� ��� keep-alive��
//       �����ϰ� �Ǵ� ���̴�.
//        ���� Ŭ���̾�Ʈ���� Ping�� �ݼ����� �ʴ´ٸ� Ÿ�Ӿƿ��� �ɷ� ������
//       �����Ų��.
//    3) ���� socket���� keep Alive�� �ϰ� �ʹٸ� �̰��� ���� ���� socket�� 
//       keep alive Add-On�� ��ӹ޴� ���� ����.
//    4) enable_keep_alive()�Լ��� disable_keep_alive()�� ����Ͽ� keep alive�����
//       �Ѱ� ���� �ִ�.
//       ������ acceptor�������� �������ִ� keep alive�� socket���� keep alive
//       ����� �Ѱ� ������ ����.
//    5) set_keep_alive_time_out()�Լ��� ����Ͽ� keep alive Ÿ�Ӿƿ� �ð��� ������ 
//       �� �ִ�. (�⺻���� 2��(120000tick)���� �����Ǿ� �ִ�.)
//    6) SetPingInterval()�Լ��� ����Ͽ� Ping�� �����ϴ� ������ ������ �� �ִ�.
//    7) keep alive�� ���е��� 1�� �����̱� ������ �ִ� 2���� ������ �� �� �ִ�.
//
//
//-----------------------------------------------------------------------------
#define	KEEPALIVE_ACTIVE	net::io::connectable_manager::list_keep_alive_active

template <class TCONNECTABLE=net::io::Iconnectable>
class net::io::connectable_manager::list_keep_alive_active : 
// inherited classes)
	public						list_keep_alive_passive<TCONNECTABLE>
{
// constructor/destructor)
public:
			list_keep_alive_active();
	virtual	~list_keep_alive_active();

// publics) 
public:
	// 1) Ping send Gap
	[[nodiscard]] auto			ping_interval() const noexcept { return this->m_tick_diff_ping;}
			void				ping_interval(chrono::tick::duration _ping_interval) noexcept { this->m_tick_diff_ping = _ping_interval; }

// implementation) 
private:
			chrono::tick::duration	m_tick_diff_ping;
};


template <class TCONNECTABLE>
net::io::connectable_manager::list_keep_alive_active<TCONNECTABLE>::list_keep_alive_active() :
	m_tick_diff_ping(chrono::seconds(1))
{
}

template <class TCONNECTABLE>
net::io::connectable_manager::list_keep_alive_active<TCONNECTABLE>::~list_keep_alive_active()
{
}

template <class TCONNECTABLE>
intptr_t net::io::connectable_manager::list_keep_alive_active<TCONNECTABLE>::process_execute(intptr_t /*_result*/, size_t /*_param*/)
{
	// check) ���� KeepAlive�� false��� keep Alive�� �������� �ʴ´�.
	RETURN_IF(this->m_enable_keep_alive == false, intptr_t(1));

	// 1) ������ Tick�� ��´�.
	auto tick_now = tick::now();

	// 2) Ping ���ۿ� �޽����� �����.
	auto buffer_ping = alloc_shared_buffer(16);
	buffer_ping.append<uint32_t>(16);
	buffer_ping.append<uint32_t>(eMESSAGE_SYSTEM_PING_REQ);
	buffer_ping.append<tick::time_point>(tick_now);

	// 3) ��� connectable�� ���ư��� keep Alive �׽�Ʈ�� �����Ѵ�.
	scoped_lock(this->m_list_connectable)
	{
		for(auto& iter:this->m_list_connectable)
		{
			auto pconnectable= *iter;

			// - ������ ���� receive tick�� ��´�.
			auto tick_last_receive = pconnectable->statistics_get_tick_last_receive();

			// check) ���� Tick���� ������ receive Tick�� ũ�ų� ������ ���� �������� �Ѿ��.
			CONTINUE_IF(tick_now <= tick_last_receive);

			// - ������ ���۹��� ���� ���� �ð��� ���Ѵ�.
			auto toclGap = tick_now-tick_last_receive;

			// - ���� ������ ���۹��� �� �����ð��� PingInterval���� �������� Ping�� �����Ѵ�.
			if(tick_differ_execute > this->m_tick_diff_ping)
			{
				pconnectable->send(buffer_ping);
			}

			// - ���� ������ ���۹��� �� �����ð��� keep-Alive Time-Out�ð����� �������� ������ �����Ѵ�.
			if(tick_differ_execute > m_dwTimeOutKeepAlive)
			{
				pconnectable->closesocket(DISCONNECT_REASON_KEEP_ALIVE_TIME_OUT);
			}
		}
	}

	// return) Success!
	return intptr_t(0);
}


}