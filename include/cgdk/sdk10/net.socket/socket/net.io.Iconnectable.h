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
// net::io::Iconnectable
//
// 1. net::io::Iconnectable��~
//    1) ������ �ʿ��� socket�� �ʿ��� connectable�̴�.
//    2) �Ϲ������� TCP socket�̳� Reliable UDP�� ���ȴ�.
//    3) TCP socket�� ��� Server���̳� Client���̳� ��� ������ �ʿ��ϹǷ� 
//       TCP socket�� ��� ICGConnectable�� ��ӹ��� ���̴�.
//    4) ���� �� ó�� ������ �ۼ��ϴ� Ŭ������ �Ʒ��� ���� �ֿ� �Լ��� �ִ�.
//
//       - bool process_complete_connect(uintptr_t _result);
//         ���� �Ϸ� �� ó�������� �����ϴ� �Լ��̴�.
//
//       - bool process_complete_disconnect();
//         ���� ���� �� ���� ����ó�������� �����ϴ� �Լ��̴�.
//
//       - bool disconnect();
//         ���� ���� �䱸�� ó���� �����ϴ� �Լ��̴�.
//
//    5) ICGConnectable�� ������ �����ǰų� Ȥ�� ���� ó���� ������ �� ó�� ������
//       �����ϴ� Ŭ�����̴�. 
//       ������ �䱸�ϴ� Ŭ������ Iconnect_requestable�� connective::Iacceptor�� ����ؾ�
//       �Ѵ�.
// 
// 
//-----------------------------------------------------------------------------
class net::io::Iconnectable : 
	virtual	public				net::io::Isocket,
	virtual public				net::io::statistics::Nsocket
{
public:
			Iconnectable() noexcept {}
	virtual ~Iconnectable() noexcept {}

public:
	// 1) disconnect�� ������ �� �θ��� �Լ��̴�.(Graceful)
	virtual	bool				disconnect(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept PURE;

public:
	// 1) reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				process_reset_connectable() noexcept PURE;
	// 2) Accept/connect�� ��û�� ��
	virtual	void				process_request_connect (const net::sockaddr& _address) PURE;
	// 3) CompleteConnect
	virtual	bool				process_complete_connect (uintptr_t _result) PURE;
	virtual	bool				process_complete_disconnect () PURE;

public:
	// 4) connective
			Iconnectable_notify* m_pconnectable_notify = nullptr;
			flexible<32>		m_flexible;
			circular_list<Iconnectable*>::iterator	m_iter_connectable;
			void				set_as_client_socket() noexcept { this->m_is_client_socket = true; }
}
;


}