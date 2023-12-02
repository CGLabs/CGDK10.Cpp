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
// net::io::connectable_manager::list_keep_alive_passive
//
// 1. net::io::connectable_manager::list_keep_alive_passive
//    1) acceptor가 받아 접속에 성공한 socket들에 대해서 KeepAlive를 수행하는 
//       connectable manager이다.
//       (엄밀하게 말하면 keep-Alive라기 보다는 Ghost socket 제거기라 할수 있다.)
//    2) 각 socket에서 마지막 전송받은 시간으로부터 일정시간이 지나면 그 socket의 
//       접속을 종료시켜버린다.
//       Active keep alive와 다른 점은 Active keep alive와 같이 마지막 전송받은
//       시간 이후로 일정 시간이 지나면 접속을 유지하기 위해 Ping을 날리지 않는다는
//       접이 다르다.
//       즉 일정 시간 전송을 받지 못하면 끊어버린다.
//    3) 만약 socket별로 keep Alive를 하고 싶다면 이것을 쓰지 말고 socket에 
//       keep alive Add-On을 상속받는 것이 좋다.
//    4) enable_keep_alive()함수와 disable_keep_alive()를 사용하여 keep alive기능을
//       켜고 끌수 있다.
//       하지만 acceptor차원에서 제공해주는 keep alive는 socket별로 keep alive
//       기능을 켜고 끌수는 없다.
//    5) set_keep_alive_time_out()함수를 사용하여 keep alive 타임아웃 시간을 설정할 
//       수 있다. (기본값은 2분(120000tick)으로 설정되어 있다.)
//    6) keep alive의 정밀도는 1초 단위이기 때문에 최대 2초의 오차가 날 수 있다.
//
// 2. Passive와 Active keep-alive 추가적인 설명
//    1) 일반적으로 Server의 입장에서는 Passive keep-alive를 사용하고 Client쪽에서
//       일정시간마다 keep-alive용 message를 전송하도록 하는 것이 Server의 입장
//       에서는 훨씬 효율적이다.
//    2) Active keep-alive는 keep-Alive를 위해 Ping을 먼저 날려야 하기 때문에
//       Server측에서 더 많은 부하를 주게 될 뿐만 아니라 전반적으로 더 많은
//       Traffic을 발생시킨다.
//       따라서 Client에서 일정 시간마다 keep alive용 message를 전송할 수 없는
//       상황에만 사용하는 것이 좋다.
//
//-----------------------------------------------------------------------------
#define	KEEPALIVE_PASSIVE	net::io::connectable_manager::list_keep_alive_passive

template <class TCONNECTABLE=net::io::Iconnectable>
class net::io::connectable_manager::list_keep_alive_passive :
	// inherited classes)
	public						net::io::connectable_manager::list<TCONNECTABLE>,
	public						executor::Nexecutable
{
// constructor/destructor)
public:
			list_keep_alive_passive();
	virtual	~list_keep_alive_passive() noexcept;

// publics) 
public:
	// 1) Add/Remove/RemoveAll
	virtual	bool				add_connectable(Iconnectable* _pconnectable) override;
	virtual	bool				remove_connectable(Iconnectable* _pconnectable) noexcept override;
			void				remove_all_connectable() noexcept;

	// 2) keep alive enable/Disable
	[[nodiscard]] bool			is_enable_keep_alive() const noexcept { return m_enable_keep_alive;}
			bool				enable_keep_alive(bool _result = true) noexcept { m_enable_keep_alive = _result; }
			bool				disable_keep_alive() noexcept { m_enable_keep_alive = false;}

	// 3) keep-alive Time-Out
	[[nodiscard]] auto			get_keep_alive_time_out() const noexcept { return m_tick_time_out_keep_alive;}
			void				set_keep_alive_time_out(chrono::tick::duration _tick) noexcept { m_tick_time_out_keep_alive = _tick; }

// implementation) 
protected:
			bool				m_enable_keep_alive;
			chrono::tick::duration	m_tick_time_out_keep_alive;

protected:
	virtual	intptr_t			process_execute(intptr_t _result, size_t _param) override;
};


template <class TCONNECTABLE>
net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::list_keep_alive_passive() :
	executor::Nexecutable(chrono::seconds(1)),
	m_enable_keep_alive(true),
	m_tick_time_out_keep_alive(chrono::seconds(120))
{
}

template <class TCONNECTABLE>
net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::~list_keep_alive_passive() noexcept
{
}

template <class TCONNECTABLE>
bool net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::add_connectable(Iconnectable* _pconnectable)
{
	// declare) 
	bool result;

	scoped_lock(this->m_list_connectable)
	{
		// 1) connectable을 추가한다.
		result = net::io::cnnectable_manager::list<TCONNECTABLE>::add_connectable(_pconnectable);

		// check) 추가에 실패했다면 그냥 끝낸다.
		RETURN_IF(result == false, false);

		// 2) 만약 첫번째 접속자라면 KeepAlive를 시작한다.
		if(this->m_list_connectable.size() == 1)
		{
			// - executor에 붙인다.
			system_executor::instance()->register_executor(this);

			// trace)
			LOG_INFO << "(prgr) start keep alive"sv;
		}
	}

	// return) Return~
	return result;
}

template <class TCONNECTABLE>
bool net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::remove_connectable(Iconnectable* _pconnectable) noexcept
{
	// declare) 
	bool result;

	scoped_lock(this->m_list_connectable)
	{
		// 1) connectable을 제거한다.
		result = net::io::connectable_manager::list<TCONNECTABLE>::remove_connectable(_pconnectable);

		// check) 제거에 실패했다면 끝낸다.
		RETURN_IF(result == false, false);

		// 2) 만약 접속자가 0개라면 KeepAlive를 멈춘다.
		if(this->m_list_connectable.size() == 0)
		{
			// - executor에서 떼낸다.
			system_executor::instance()->unregister_executor(this);

			// trace) 
			LOG_INFO << "(prgr) closing keep alive"sv;
		}
	}

	// return) 
	return	result;
}

template <class TCONNECTABLE>
void net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::remove_all_connectable() noexcept
{
	// 1) 모든 접속을 종료한다.
	net::io::cnnectable_manager::list<TCONNECTABLE>::remove_all_connectable();

	// 2) executor에서 떼낸다.
	scoped_lock(this->m_list_connectable)
	{
		// - executor에서 떼어낸다.
		system_executor::instance()->unregister_executor(this);

		// trace) 
		LOG_INFO << "(prgr) remove all connectable"sv;
	}
}

template <class TCONNECTABLE>
intptr_t net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::process_execute(intptr_t /*_result*/, size_t /*_param*/)
{
	// check) 만약 KeepAlive가 false라면 keep Alive를 수행하지 않는다.
	RETURN_IF(this->m_enable_keep_alive == false, intptr_t(1));

	// 1) 현재의 Tick을 얻는다.
	auto tick_now = tick::now();

	// 2) 모든 connectable을 돌아가며 keep Alive 테스트를 수행한다.
	scoped_lock(this->m_list_connectable)
	{
		for(auto& iter:this->m_list_connectable)
		{
			auto pconnectable = iter;

			// - 마지막 받은 receive tick을 얻는다.
			auto tickLastReceive = pconnectable->statistics_get_tick_last_receive();

			// check) 현재 Tick보다 마지막 receive Tick이 크거나 같으면 다음 소켓으로 넘어간다.
			CONTINUE_IF(tick_now <= tickLastReceive);

			// 2) 마지막 전송받은 이후 지난 시간을 구한다.
			auto tick_differ_execute = tick_now-tickLastReceive;

			// check) 만약 마지막 전송받은 후 지난시간이 keep-Alive Time-Out시간보다 지났으면 접속을 종료한다.
			if(tick_differ_execute>m_tick_time_out_keep_alive)
			{
				pconnectable->closesocket(DISCONNECT_REASON_KEEP_ALIVE_TIME_OUT);
			}
		}
	}

	// return) Success!
	return intptr_t(0);
}


}