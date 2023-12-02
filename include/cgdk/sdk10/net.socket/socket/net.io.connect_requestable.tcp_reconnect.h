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

//-----------------------------------------------------------------------------
//
// net::io::connect_requestable::Ntcp_reconnect (�ڵ������� ����� ���� TCP ������)
//
// 1. net::io::connective::Ntcp_reconnect�̶�!
//    1) �ڵ� ������ ����� �ִ� connect_requestable�̴�.
//    2) net::io::connect_requestable::Ntcp�� ��ӹ޾� ���� ����� �ڵ� ������ ����� �߰�
//       �� ���̴�.
//
// 2. �ٽ� �Լ���.
//    1) �������� �⺻������ connect()�� ���� �� �ϳ��� �ּҿ��� �̷������.
//    2) �ʿ信 ���� ���� �ּҷ� �������� ������ �� �ִ�.
//       - ������ ����Ǹ� ��ϵ� �ּҵ鿡 ���ʴ�� ���ӿ䱸�� �����ϰ� �ȴ�.
//
//		 - ������ �ּҸ� �߰��ϰ� ������ �� �ִ�.
//			bool add_peer_address((const ::sockaddr* _paddress_peer);
//			bool remove_peer_address(const ::sockaddr* _paddress_peer);
//          void remove_all_peer_address();
//
//    3) ������ connect�Լ��� ����Ͽ� �����Ѵ�.
//    4) Address�� ���� ���� ��� ��ϵ� peer�ּҷ� ������ �õ��Ѵ�.
//    5) �Ʒ��� �Լ��� ����Ͽ�  ������ ����� �Ѱų� �� �� �ִ�.
//       
//       void enable_reconnect(bool _enable=true);
//       void disable_reconnect();
//
//       is_enable()�Լ��� ����Ͽ� ������ ����� ���ۿ��θ� Ȯ���� �� �ִ�.
//
//       bool is_enable() const
//
//    6) ������ �õ�  �ð��� �����ϰų� ���� �� �ִ�.
//       ������ �õ��� ������ ������ ������ �������� ���� ����� �ȴ�.
//       ���� ������ ���� ������ �õ� �ð��� �ʰ��� ������ ����Ǿ��� ���
//       �ٷ� �������� ����ȴ�.
//
//       void			set_reconnect_interval(chrono::tick::duration p_tick);
//       chrono::tick::duration get_reconnect_interval() const;
//
//    7) ������ �� ���� ��� ����� ����Ǿ�� �Ѵٸ� ���� virtual�Լ���
//       �������Ͽ� ����� �߰��� �� �ִ�.
//
//       virtual void on_request_reconnect(net::io::Iconnective* _pconnective);
// 
//    
//    ����) ������ ������ ���� �ݵ�� �Ʒ��� ���� disable_reconnect()�Լ��� 
//          ���� ȣ���Ͽ� ������ ����� ��Ȱ��ȭ ���� ������ �����ؾ� �Ѵ�.
//
//           psocket->disable_reconnection();
//           psocket->closesocket();
//
// 3. initialize/start String
//
//	  1) "reconnection"
//	     - "enable"				������ Ȱ��ȭ
//       - "disable"			������ ��Ȱ��ȭ
//	     - "default"			�⺻��(��Ȱ��ȭ)
//
//	  2) "reconnection_interval"
//	     �������� �õ��ϴ� ����. ms�����̴�. �� 1000�� 1�ʸ� �ǹ��Ѵ�.  
//
//    ��)  ��ü���� "foo"�̶�� �Ѵٸ�....
//
//		   sMESSAGE msg_context;
//         context_setting["foo"]["reconnection"] = false;
//         context_setting["foo"]["reconnection_interval"] = 1000;
//
//-----------------------------------------------------------------------------
class CGDK::net::io::connect_requestable::Ntcp_reconnect :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp,
	virtual public				net::io::Ireconnectable,
	virtual public				net::io::Iconnectable_notify
{
// constructor/destructor)
protected:
			Ntcp_reconnect() noexcept;
			Ntcp_reconnect(std::string_view _name);
	virtual	~Ntcp_reconnect() noexcept;

// framework)
protected:
	// 2) �������� �õ��ϱ� �� ȣ��Ǵ� �Լ�.
	virtual	void				on_request_reconnect(net::io::Iconnective* /*_pconnective*/) {}

// implementation) 
protected:
	// 3) request_connect
	virtual	bool				process_request_connecting(const net::sockaddr& _address_peer) override;
	virtual	void				process_complete_connecting(uintptr_t _result) override;
	virtual	void				process_connective_connect(net::io::Iconnectable* _pconnectable, uintptr_t _result) override;
	virtual	void				process_connective_disconnect(net::io::Iconnectable* _pconnectable) noexcept override;

	// 4) start/stop
	virtual result_code			process_start(context& _context) override;
	virtual result_code			process_stop() noexcept override;

public:
	// 5) Reconnect�� �����ϴ� �Լ��̴�.
			bool				process_wait_reconnect();
			void				process_request_reconnect();
			void				process_cancel_reconnector() noexcept;
public:
			class manager_reconnector;
private:
			object_ptr<manager_reconnector>	m_pmanager_reconnector;
public:
	static	void				detach_instance() noexcept;
};
