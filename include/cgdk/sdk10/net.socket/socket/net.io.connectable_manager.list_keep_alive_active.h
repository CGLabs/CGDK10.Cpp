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
//    1) acceptor가 받아 접속에 성공한 socket들에 대해서 Active-KeepAlive를 수행하는 
//       connectable manager이다.
//    2) Active keep-alive란 각 socket에서 마지막 전송받은 시간으로부터 일정시간이 
//       지나면 keep alive를 유지하기 위해 Ping을 전송한다.
//       클라이언트는 이 Ping을 전송받으면 Ping을 다시 전송하게 될 것이다.
//       그렇게 되면 마지막 전송받은 시간이 다시 연장되게 되어 계속 keep-alive를
//       유지하게 되는 것이다.
//        만약 클라이언트에서 Ping을 반송하지 않는다면 타임아웃에 걸려 접속을
//       종료시킨다.
//    3) 만약 socket별로 keep Alive를 하고 싶다면 이것을 쓰지 말고 socket에 
//       keep alive Add-On을 상속받는 것이 좋다.
//    4) enable_keep_alive()함수와 disable_keep_alive()를 사용하여 keep alive기능을
//       켜고 끌수 있다.
//       하지만 acceptor차원에서 제공해주는 keep alive는 socket별로 keep alive
//       기능을 켜고 끌수는 없다.
//    5) set_keep_alive_time_out()함수를 사용하여 keep alive 타임아웃 시간을 설정할 
//       수 있다. (기본값은 2분(120000tick)으로 설정되어 있다.)
//    6) SetPingInterval()함수를 사용하여 Ping을 전송하는 간격을 설정할 수 있다.
//    7) keep alive의 정밀도는 1초 단위이기 때문에 최대 2초의 오차가 날 수 있다.
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
	// check) 만약 KeepAlive가 false라면 keep Alive를 수행하지 않는다.
	RETURN_IF(this->m_enable_keep_alive == false, intptr_t(1));

	// 1) 현재의 Tick을 얻는다.
	auto tick_now = tick::now();

	// 2) Ping 전송용 메시지를 만든다.
	auto buffer_ping = alloc_shared_buffer(16);
	buffer_ping.append<uint32_t>(16);
	buffer_ping.append<uint32_t>(eMESSAGE_SYSTEM_PING_REQ);
	buffer_ping.append<tick::time_point>(tick_now);

	// 3) 모든 connectable을 돌아가며 keep Alive 테스트를 수행한다.
	scoped_lock(this->m_list_connectable)
	{
		for(auto& iter:this->m_list_connectable)
		{
			auto pconnectable= *iter;

			// - 마지막 받은 receive tick을 얻는다.
			auto tick_last_receive = pconnectable->statistics_get_tick_last_receive();

			// check) 현재 Tick보다 마지막 receive Tick이 크거나 같으면 다음 소켓으로 넘어간다.
			CONTINUE_IF(tick_now <= tick_last_receive);

			// - 마지막 전송받은 이후 지난 시간을 구한다.
			auto toclGap = tick_now-tick_last_receive;

			// - 만약 마지막 전송받은 후 지난시간이 PingInterval보다 지났으면 Ping을 전송한다.
			if(tick_differ_execute > this->m_tick_diff_ping)
			{
				pconnectable->send(buffer_ping);
			}

			// - 만약 마지막 전송받은 후 지난시간이 keep-Alive Time-Out시간보다 지났으면 접속을 종료한다.
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