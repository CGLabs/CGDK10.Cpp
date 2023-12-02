//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Security Controls                          *
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
// net::io::receivable::Nstream_crypt
//
// 1. net::io::receivable::Nstream_crypt��!
//    1) TCP�� send/receive/connect ���� ������ �� �ִ� socket��. 
//    2) �⺻������ ������ ���� Recycleó���� ��� ����.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� socket manager�� socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. �ٽ� function�� ��� ����
//    1) ó���Լ��� �⺻���� I/Oó���� ���� ó���Լ����̴�.
//					���������� ���� I/O�� ó���ϱ� ���� �ʿ��� �Լ��鿡 ���ؼ� ������ ���̴�.
//    2) �����Լ���	socket�� �� ������ �����ϴ� �Լ����̴�.
//    3) User�Լ���	�����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� �κе��� ������
//					������ socket�� ���ӿ� �°� ����� �ȴ�.
//
// 3. ���� ����
//  run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//-----------------------------------------------------------------------------
class net::io::Ntcp_client_crypt :
	public						net::io::connectable::Ntcp,
	public						net::io::sendable::Ntcp_crypt,
	public						net::io::receivable::Nstream_crypt,
	public						net::io::messageable::Nbase
{
protected:
	virtual	void				on_connecting () {}
	virtual	void				on_connect () override {}
	virtual	void				on_fail_connect (uint64_t /*_disconnect_reason*/) override {}

protected:
	virtual	void				process_request_certification ();

	virtual void				process_on_connect () override;
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state) override;
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason) override;

	virtual	result_code			process_message (sMESSAGE& _msg) override;

			void				on_message_NETWORK_SECURITY_SEND_DECODER_INFO (const shared_buffer& _message);
			void				on_message_NETWORK_SECURITY_ACCEPT_CERTIFICATION (const shared_buffer& _message);

protected:
			class executable_disconnect;
			friend class executable_disconnect;
};


}