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
// net::io::Nrestorable_client
//
// 1. net::io::Nrestorable_client��~
//    1) Restore ����� �����ϴ� socket�� Client�� Component�̴�.
//
//
//    2) �ֿ� �����...
//
//       - ������ ��뿡 ���� ����Ǿ��� ��� �����ӽ� ���� �����ϵ��� �Ѵ�.
//       - �ٸ� ������ ���� ������ ����� socket���� �ٽ� ������ ��û�ؾ�
//         ���� ����� �۵��ȴ�.
//
//
//    3) Hook �Լ���
//
//       - on_connecting()
//         ���� ���������� ������ �Ǿ��� �� ȣ��ȴ�.
//
//       - on_connect()
//         ������ ���� ���� �������� ��� �Ǿ��� �� ȣ��ȴ�.
//
//       - on_suspend()
//         ������ ��뿡 ���� ���� ó�� ���Ŀ� ȣ��ȴ�.
//
//       - on_restoring()
//         �������� ���� ������ ���۵� �� ȣ��ȴ�.
//         ���� ó�� ���ӽó� ���� ������ ���ǵǾ� reset�� ��� ȣ����� �ʴ´�.
//
//       - on_restore()
//         ������ �� ������ �Ϸ�Ǿ��� �� ȣ��ȴ�.
//
//       - OnDisconnecting()
//         ���������� ���� ����Ǿ��� �� ȣ��ȴ�.
//
//       - on_disconnect()
//         ������ ����Ǿ��� �� ȣ��ȴ�.
//
//
//    4) ����
//
//       - ���������� ó�� ������ �ϰ� �Ǹ� ������ on_connecting�� ȣ��ȴ�.
//
//       - Ŭ���̾�Ʈ �������� ��û�� ���� ������ ����� ���� �ƴ϶�� 
//         on_disconnect�� �ٷ� ȣ����� �ʰ� ���߿� ������ �� ������ �غ��ϸ�
//         on_disconnect��� on_suspend()�Լ��� ȣ��ȴ�.
//
//       - ���� �������� �ǰ� �Ǹ� on_restoring()�� on_restore()�Լ��� ȣ��ȴ�.
//
//       - Ŭ���̾�Ʈ �ʿ��� closesocket()�̳� disconnect()�� ȣ���� ����
//         �ٷ� suspend�� ���� �ʰ� �ٷ� on_disconnect()�� ȣ��ȴ�.
//
//       - suspend ���¿��� closesocket�̳� disconnect()�� ȣ���� ����
//         on_disconnect()�� ȣ��ȴ�.
//         
//       - on_disconnect()�� ȣ��Ǹ� ���ķδ� ������ �Ǵ��� ����(Restore)��
//         ���� �ʴ´�.
//
//
//    5) �Լ��� pairing ó��
//
//       - on_connecting()�Լ��� ȣ�� �� ���� ������ ����Ǵ��� on_disconnect()
//         �Լ��� ȣ����� �ʴ´�.
//
//       - on_restoring()�Լ��� ȣ��Ǵ� Exception�� �߻��ǰų� ���̻� ó������
//         ���� ��� �ٷ� on_disconnect()�� ȣ��ȴ�.
//       - on_restore()�Լ��� ȣ��Ǵ� �� Exception�� �߻��ϰ� �Ǿ��� ����
//         on_disconnect()�� ȣ��ȴ� ���� on_restore()�Լ��� ������ �߻��Ǹ�
//         on_restoring���� ó���� �͵� �����ؾ� �Ѵ�.
//
//       - on_suspend()�Լ��� ȣ��Ǵ� Exception�� �߻��ϸ� on_disconnect()�Լ���
//         ȣ��ȴ�.
//
//
//-----------------------------------------------------------------------------
class net::io::Nrestorable_client : 
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::io::connectable::Ntcp,
	virtual public				Irestorable
{
protected:
	virtual	void				on_socket_connect() { request_io_restore();}
	virtual	void				on_socket_disconnect() {}

	virtual	void				on_connect () override {}
	virtual	void				on_suspend (uint64_t /*_disconnect_reason*/) {}
	virtual	void				on_restoring () {}
	virtual	void				on_restore () {}
	virtual	void				on_disconnect (uint64_t /*_disconnect_reason*/) override	{}

protected:
	virtual void				process_on_connect () override;
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state) override;
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason) override;

	virtual	void				process_on_restoring ();
	virtual	void				process_on_restore ();
	virtual	bool				process_on_suspend (uint64_t _disconnect_reason);

	virtual	void				process_request_io_restore	(result_code _result, SEQUENCE_ID _ack_received) override;
	virtual	void				process_response_io_restore	(result_code _result, SEQUENCE_ID _ack_received) override;
	virtual	void				process_complete_io_restore	(result_code _result) override;
};


}