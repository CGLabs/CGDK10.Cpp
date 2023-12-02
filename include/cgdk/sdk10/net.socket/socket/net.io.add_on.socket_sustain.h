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
// net::io::add_on::Nsocket_sustain
//
// 1. net::io::add_on::Nsocket_sustain��!
//    1) socket�� �����ϱ� ���� ó���� �ϴ� Ŭ�����̴�.
//    2) �� Ŭ������ ��ӹ޾� �����ϰ� �Ǹ� �����ø� ���� ProcessSustain()�Լ���
//       ȣ���� �Ǹ� �� �� �Ϲ����� socket�� ������ ���� ó���� �����ϰ� �ȴ�.
//    3) �Ϲ������� Ghost�� �� socket�̸� �����ϰų� �����ð� ���� �ۼ����� ���� ��
//       ������ �����Ű�� ���� ������ �Ѵ�.
//    4) �⺻������ ���ӵ� socket�� ���� �ð� ���� �ƹ��� �۽��̳� ������ ���� ��
//       ���� OnReceiveTimeOut(), OnSendTimeOut()�� ȣ�����ش�.
//    5) Add-On�����̶� ��ӹ޾� �����ϴ� Class�� �ΰ������� �پ �����Ѵ�.
//    6) �Ϲ������� Server���� socket�� ���ȴ�.
//
//
// 2. net::io::add_on::Nsocket_sustain�� �ֿ� Function�� ��� ����
//    1) set_connect_time_out()�Լ��� ConnectTimeOut ����.
//
//		 virtual void on_timeout_connect();
//
//	     ���ӵ� �� on_timeout_connect()�� ������ ȣ����� �ð��� ��Ÿ���� ����
//       �̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void set_connect_time_out(tick::time_point _tick)
//		 tick:duration get_connect_time_out()
//
//    2) on_timeout_disconnect()�Լ��� DisconnectTimeOut ����.
//
//		 virtual void on_timeout_disconnect();
//
//	     ��������� ���� �� �� on_timeout_disconnect()�� ȣ����� �ð��� 
//       ��Ÿ���� �����̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void set_disconnect_time_out(tick::time_point _tick)
//		 tick:duration get_disconnect_time_out()
//
//    3) on_timeout_send()�Լ��� SendTimeOut ����.
//
//		 virtual void on_timeout_send();
//
//	     �� ���� send�� ����� on_timeout_send()�� ȣ����� �ð��� ��Ÿ���� ����
//       �̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void set_send_time_out(tick::time_point _tick)
//		 tick:duration get_send_time_out()
//
//    4) on_timeout_receive()�Լ��� ReceiveTimeOut
//
//		 virtual void on_timeout_receive();
//
//	     �� ���� receive�� ����� on_timeout_receive()�� ȣ����� �ð��� ��Ÿ����
//       �����̴�.
//       �̴� �����ϰų� ��� �Լ��� �Ʒ��� ����.
//
//		 void set_receive_time_out(tick::time_point _tick)
//		 tick:duration get_receive_time_out()
//
//    5) �� Ŭ������ Add-On���� socket�� �����Ǵ� ��� �����ϰ� �ȴ�.
//    6) �ڵ����� ������ ����ó���� �ϴ� ���� socket�� eSOCKET_STATE::ESTABLISED
//       �� ���� ���۵ȴ�. �� ���� ���� ���� ���۵ȴ�.
//
//    7) ������ Time-Out���� 0���� �����Ǹ� �ش� Time-Out�� �������� �ʵ���
//       Disable�ȴ�.
//    8) OnTimeOut�� �ѹ�  ����� ���Ŀ� ���ο��� �ٽ� TimeOut�� �������� �ʴ���
//       TimeOut�� 0���� reset�Ǿ OnTimeOut...()�Լ����� �ѹ��� ����ȴ�.
//       ���� OnTimeOut...()�Լ������� �ٽ� Set...TimeOut()�Լ��� ����Ͽ�
//       TimeOut()�� �ٽ� �����Ѵٸ� �ٽ� Time Out�� �߻��Ѵ�.
//       (�̶� connect�� disconnect�� Time-Out�� ������ ���ӽ��� Ȥ�� ���� ���� 
//       ������ �������� �ϴ� �Լ��Ƿ� �����ؾ� �Ѵ�.
//
//       ����) OnTimeOut�Լ��� ȣ��� �� �ش� m_tick_timeout...������ �̹� 0����
//             reset�� ���ĹǷ� �� ���� �����ϰ� �Ǹ� 0�� ���� ���̴�.
//
//  3. ����
//     1) ��� Time-Out�� �������� 0x7fffffff���� �۾ƾ� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
class net::io::add_on::Nsocket_sustain :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual	public				net::io::statistics::Nsocket
{
// constructor/destructor) 
protected:
			Nsocket_sustain();
	virtual ~Nsocket_sustain();

// publics) 
public:
	// 1) keep Alive.
			bool				start_socket_sustain();
			bool				stop_socket_sustain();

	// 2) Time ���� ����.
			void				time_out_connect(chrono::tick::duration _tick) noexcept { this->m_tick_timeout_connect = _tick; }
	[[nodiscard]] auto			time_out_connect() const noexcept { return m_tick_timeout_connect;}
			void				reset_time_out_connect() noexcept { this->time_out_connect(chrono::tick::duration::zero());}

			void				time_out_disconnect(chrono::tick::duration _tick) noexcept { this->m_tick_timeout_disconnect = _tick; }
	[[nodiscard]] auto			time_out_disconnect() const noexcept { return m_tick_timeout_disconnect;}
			void				reset_time_out_disconnect() noexcept { this->time_out_disconnect(chrono::tick::duration::zero());}
																				  
			void				time_out_receive(chrono::tick::duration _tick) noexcept { this->m_tick_timeout_receive = _tick; }
	[[nodiscard]] auto			time_out_receive() const noexcept { return m_tick_timeout_receive;}
			void				reset_time_out_receive() noexcept { this->time_out_receive(chrono::tick::duration::zero());}
																				  
			void				time_out_send(chrono::tick::duration _tick) noexcept { this->m_tick_timeout_send = _tick; }
	[[nodiscard]] auto			time_out_send() const noexcept { return m_tick_timeout_send;}
			void				reset_time_out_send() noexcept { this->time_out_send(chrono::tick::duration::zero());}

// frameworks) 
private:
	virtual	void				on_timeout_connect(chrono::tick::duration /*p_tickdifferExecute*/) {}
	virtual	void				on_timeout_disconnect(chrono::tick::duration /*p_tickdifferExecute*/) {}
	virtual	void				on_timeout_receive(chrono::tick::duration /*p_tickdifferExecute*/) { this->process_close_socket(DISCONNECT_REASON_ACTIVE | DISCONNECT_REASON_ABORTIVE); }
	virtual	void				on_timeout_send(chrono::tick::duration /*p_tickdifferExecute*/) {}

// implementation)
private:
	// Friend) 
	friend class manager_socket_sustain;

	// 1) Time-Out ����
			chrono::tick::duration	m_tick_timeout_connect;
			chrono::tick::duration	m_tick_timeout_disconnect;
			chrono::tick::duration	m_tick_timeout_receive;
			chrono::tick::duration	m_tick_timeout_send;

	// 2) Iterator�� ���� ���� ����...
			circular_list<Nsocket_sustain*>::iterator m_iter_list_socket_sustain;
			object_ptr<manager_socket_sustain> m_pmanager;

private:
	// 1) Process AutoClose
	virtual void				process_socket_sustain();

public:
	static	void				detach_instance() noexcept;
};


}