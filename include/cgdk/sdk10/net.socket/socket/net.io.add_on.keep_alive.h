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
// 1. net::io::add_on::Nkeep_alive��!
//    1) UDP�� TCP���� ���ӻ��¸� �����ϰų� Ȯ���� ���� �����ð����� Ping�� 
//       �����ִ� ������ �ϴ� class�̴�.
//    2) Add-On�����̶� ��ӹ޾� �����ϴ� Class�� �ΰ������� �پ �����Ѵ�.
//
//
// 2. net::io::add_on::Nkeep_alive�� �ֿ� Function�� ��� ����
//    1) start_keep_alive()
//	      �� �Լ��� �����ϸ� keep Alive�� �����ϱ� �����Ѵ�.
//    2) stop_keep_alive()
//        �� �Լ��� �����ϸ� keep Alive ������ �����Ѵ�.
//    3) Ping�� ������ �Ǹ� �ٽ� ���ƿ��� Turn-Around-Time�� ��������.
//    4) Ping�� ������ ������ �����Ҽ� �ִ�.
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