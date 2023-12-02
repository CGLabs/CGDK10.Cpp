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
//    1) acceptor�� �޾� ���ӿ� ������ socket�鿡 ���ؼ� KeepAlive�� �����ϴ� 
//       connectable manager�̴�.
//       (�����ϰ� ���ϸ� keep-Alive��� ���ٴ� Ghost socket ���ű�� �Ҽ� �ִ�.)
//    2) �� socket���� ������ ���۹��� �ð����κ��� �����ð��� ������ �� socket�� 
//       ������ ������ѹ�����.
//       Active keep alive�� �ٸ� ���� Active keep alive�� ���� ������ ���۹���
//       �ð� ���ķ� ���� �ð��� ������ ������ �����ϱ� ���� Ping�� ������ �ʴ´ٴ�
//       ���� �ٸ���.
//       �� ���� �ð� ������ ���� ���ϸ� ���������.
//    3) ���� socket���� keep Alive�� �ϰ� �ʹٸ� �̰��� ���� ���� socket�� 
//       keep alive Add-On�� ��ӹ޴� ���� ����.
//    4) enable_keep_alive()�Լ��� disable_keep_alive()�� ����Ͽ� keep alive�����
//       �Ѱ� ���� �ִ�.
//       ������ acceptor�������� �������ִ� keep alive�� socket���� keep alive
//       ����� �Ѱ� ������ ����.
//    5) set_keep_alive_time_out()�Լ��� ����Ͽ� keep alive Ÿ�Ӿƿ� �ð��� ������ 
//       �� �ִ�. (�⺻���� 2��(120000tick)���� �����Ǿ� �ִ�.)
//    6) keep alive�� ���е��� 1�� �����̱� ������ �ִ� 2���� ������ �� �� �ִ�.
//
// 2. Passive�� Active keep-alive �߰����� ����
//    1) �Ϲ������� Server�� ���忡���� Passive keep-alive�� ����ϰ� Client�ʿ���
//       �����ð����� keep-alive�� message�� �����ϵ��� �ϴ� ���� Server�� ����
//       ������ �ξ� ȿ�����̴�.
//    2) Active keep-alive�� keep-Alive�� ���� Ping�� ���� ������ �ϱ� ������
//       Server������ �� ���� ���ϸ� �ְ� �� �Ӹ� �ƴ϶� ���������� �� ����
//       Traffic�� �߻���Ų��.
//       ���� Client���� ���� �ð����� keep alive�� message�� ������ �� ����
//       ��Ȳ���� ����ϴ� ���� ����.
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
		// 1) connectable�� �߰��Ѵ�.
		result = net::io::cnnectable_manager::list<TCONNECTABLE>::add_connectable(_pconnectable);

		// check) �߰��� �����ߴٸ� �׳� ������.
		RETURN_IF(result == false, false);

		// 2) ���� ù��° �����ڶ�� KeepAlive�� �����Ѵ�.
		if(this->m_list_connectable.size() == 1)
		{
			// - executor�� ���δ�.
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
		// 1) connectable�� �����Ѵ�.
		result = net::io::connectable_manager::list<TCONNECTABLE>::remove_connectable(_pconnectable);

		// check) ���ſ� �����ߴٸ� ������.
		RETURN_IF(result == false, false);

		// 2) ���� �����ڰ� 0����� KeepAlive�� �����.
		if(this->m_list_connectable.size() == 0)
		{
			// - executor���� ������.
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
	// 1) ��� ������ �����Ѵ�.
	net::io::cnnectable_manager::list<TCONNECTABLE>::remove_all_connectable();

	// 2) executor���� ������.
	scoped_lock(this->m_list_connectable)
	{
		// - executor���� �����.
		system_executor::instance()->unregister_executor(this);

		// trace) 
		LOG_INFO << "(prgr) remove all connectable"sv;
	}
}

template <class TCONNECTABLE>
intptr_t net::io::connectable_manager::list_keep_alive_passive<TCONNECTABLE>::process_execute(intptr_t /*_result*/, size_t /*_param*/)
{
	// check) ���� KeepAlive�� false��� keep Alive�� �������� �ʴ´�.
	RETURN_IF(this->m_enable_keep_alive == false, intptr_t(1));

	// 1) ������ Tick�� ��´�.
	auto tick_now = tick::now();

	// 2) ��� connectable�� ���ư��� keep Alive �׽�Ʈ�� �����Ѵ�.
	scoped_lock(this->m_list_connectable)
	{
		for(auto& iter:this->m_list_connectable)
		{
			auto pconnectable = iter;

			// - ������ ���� receive tick�� ��´�.
			auto tickLastReceive = pconnectable->statistics_get_tick_last_receive();

			// check) ���� Tick���� ������ receive Tick�� ũ�ų� ������ ���� �������� �Ѿ��.
			CONTINUE_IF(tick_now <= tickLastReceive);

			// 2) ������ ���۹��� ���� ���� �ð��� ���Ѵ�.
			auto tick_differ_execute = tick_now-tickLastReceive;

			// check) ���� ������ ���۹��� �� �����ð��� keep-Alive Time-Out�ð����� �������� ������ �����Ѵ�.
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