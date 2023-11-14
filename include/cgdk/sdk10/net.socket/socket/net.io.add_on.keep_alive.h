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
// net::io::add_on::Nkeep_alive
//
// 1. net::io::add_on::Nkeep_alive란!
//    1) UDP나 TCP에서 접속상태를 유지하거나 확인을 위해 일정시간마다 Ping을 
//       날려주는 역할을 하는 class이다.
//    2) Add-On형식이라 상속받아 결합하는 Class에 부가적으로 붙어서 동작한다.
//
//
// 2. net::io::add_on::Nkeep_alive의 주요 Function의 기능 설명
//    1) start_keep_alive()
//	      이 함수를 수행하면 keep Alive를 수행하기 시작한다.
//    2) stop_keep_alive()
//        이 함수를 수행하면 keep Alive 동작을 중지한다.
//    3) Ping을 날리게 되면 다시 돌아오는 Turn-Around-Time이 구해진다.
//    4) Ping을 날리는 간격을 설정할수 있다.
//
//
//-----------------------------------------------------------------------------
class net::io::add_on::Nkeep_alive :
// inherited classes)
	virtual public				net::io::Isendable,
	virtual	public				net::io::Ipacketable,
	virtual	public				net::io::statistics::Nsocket
{
// constructor/destructor)
protected:
			Nkeep_alive() noexcept;
	virtual ~Nkeep_alive() noexcept { stop_keep_alive();}

// publics)
public:
			bool				start_keep_alive();
			bool				stop_keep_alive() noexcept;

	[[nodiscard]] auto			turn_around_time() const noexcept { return this->m_nested.m_tick_tat;}

			void				ping_interval(chrono::tick::duration _tick) noexcept { this->m_nested.m_tick_ping_interval = _tick; }
	[[nodiscard]] auto			ping_interval() const noexcept { return this->m_nested.m_tick_ping_interval;}

			void				time_out(chrono::tick::duration _tick) noexcept { this->m_nested.m_tick_timeout = _tick; }
	[[nodiscard]] auto			time_out() const noexcept { return this->m_nested.m_tick_timeout;}

// frameworks)
private:
	virtual	void				on_keep_alive_time_out();

// implementation)
private:
	class	nested : 
		public					Imessageable,
		public					schedulable::Iexecutable
	{
	public:
		nested() : m_pParent(nullptr),m_tick_tat(),m_tick_timeout(),m_tick_ping_interval() {}

	public:
		virtual	result_code		process_message(sMESSAGE& _msg) override { return this->m_pParent->nested_process_message(_msg);}
		virtual intptr_t		process_execute(intptr_t, size_t) override { return this->m_pParent->nested_update();}

	public:
				Nkeep_alive*	m_pParent;

				chrono::tick::duration m_tick_tat;
				chrono::tick::duration m_tick_timeout;
				chrono::tick::duration m_tick_ping_interval;
	};
	friend	nested;

private:
			OBJ<nested>			m_nested;
			uint32_t			m_ping_key[2];

private:
			result_code			nested_process_message(sMESSAGE& _msg);
			intptr_t			nested_update();

			bool				send_ping_req() noexcept;
};


}