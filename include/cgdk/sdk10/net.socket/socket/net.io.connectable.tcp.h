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
// net::io::connectable::Ntcp
//
// 1. net::io::connectable::Ntcp�̶�!
//    1) TCP�� Iconnectable�� ������ Ŭ�����̴�.
//    2) TCP�� ������ �õ��Ͽ� ����ó���� �Ϸ�Ǿ��� ��(������������ �������� ����)
//       �� Ŭ������ ���� ó�������� �����ϰ� �ȴ�.
//    3) �� Ŭ������ Overlapped I/O�� ����� receive�� ó���ϵ��� ���ǵǾ����Ƿ�
//       ���� �� receive()�� �ɵ��� �ۼ��Ǿ���.
//    4) ������ ������ ��� on_connect()�Լ��� ȣ���ϰ� �������� ��� on_fail_connect()��
//       ȣ���Ѵ�.
//    5) ������ ����Ǿ��� �� on_disconnect()�Լ��� ȣ���ϵ��� ���ǵǾ� �ִ�.
//    6) ������ ���Ḧ �䱸�� �� disconnect()�Լ��� ȣ���ϸ� �Ǹ� �̴� Graceful
//       close�� �����ϰ� �ȴ�.
//       ����) ���� Abortive close�� ����ϰ��� �Ѵٸ� Isocket�� closesocket()�Լ���
//             ����ϵ��� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
class CGDK::net::io::connectable::Ntcp :
// inherited classes)
	virtual public				net::io::Iconnectable,
	virtual public				net::io::Ireceivable_stream
{
// publics) 
// - ����ڰ� �� socket�� ����ڰ� �����ϱ� ���� �Լ�.
public:
	// 1) disconnect(graceful close)
	virtual	bool				disconnect (uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

// frameworks)
// - �� �Լ����� ������ �����ν� ���α׷����� �Ѵ�.
// - ��� �۾��� ����Ǿ��� �� �ҷ����� �Լ��̴�.
protected:
	//! @brief ������ �Ǿ��� �� ȣ��ȴ�. @param _pconnective ������ ��û�� connective
	virtual void				on_request_connect (const net::sockaddr& /*_address*/) {}
	virtual void				on_connect () {}
	virtual void				on_disconnect (uint64_t /*_disconnect_reason*/) {}
	virtual void				on_fail_connect (uint64_t /*_disconnect_reason*/) {}

// implementation) 
protected:
	// 1) connect����
	virtual	void				process_request_connect (const net::sockaddr& _address) override;
	virtual bool				process_complete_connect (uintptr_t _result) override;// 1) ���ӵǾ��� ���� ó�� ������ �����ϴ� �Լ�.
	virtual bool				process_complete_disconnect () override;// 2) ����Ǿ��� ���� ó�� ������ �����ϴ� �Լ�.

	virtual void				process_on_connect () { on_connect(); }
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE /*_socket_state*/) { on_disconnect(_disconnect_reason); }
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason) { on_fail_connect(_disconnect_reason); }

	// 3) reset�Ҷ� ȣ���ϴ� �Լ�.
	virtual	void				process_reset_connectable () noexcept override;
			void				process_disconnect () noexcept;

			class	executable_disconnect;
			friend	class executable_disconnect;

	#if defined(_WINSOCK2API_)
			object_ptr<Iexecutable> alloc_executable_disconnect(net::io::connectable::Ntcp* _pconnectable);
	#elif defined(_SYS_EPOLL_H)
public:
			void				process_complete_closesocket() noexcept;
	#endif

private:
			bool				m_enable_tcp_nodelay = DEFAULT_ENABLE_TCP_NODELAY;
};
