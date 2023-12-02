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
// net::io::IBindable
//
// 1. IBindable��~
//    bind�� ���� bind Interface�� ���� Interface Class��.
//
// 2. �ֿ���ó.
//    1) UDP socket�� ���� binder�̴�.
//    2) ���� UDP socket�� Ư���� �ּҿ� Port�� bind�ؾ� �Ѵٸ� �� binder Ŭ������
//       ��ӹ޾� bind()�Լ��� ����Ͽ� Ư�� �ּҿ� ��Ʈ�� bind�� �� �ִ�.
//    3) binder�� �ȴٸ� ���������� binder manager�� ��ϵȴ�. �� closesocket()
//       �Ǹ� binder manager���� ��������ȴ�.
//    4) ��ϵ� binder���� �̱����� net::io::binder::manager ��ü�� ���� ������
//       ���� �� �ִ�.
//
//-----------------------------------------------------------------------------
class net::io::Ibinder : 
	virtual	public				net::io::Isocket,
	virtual public				Imessageable,
	virtual	public				object::Inameable
{
public:
			Ibinder() noexcept {}
	virtual	~Ibinder() noexcept {}

// public)
public:
	// 1) �߰� bind�Լ�
			bool				bind( const net::sockaddr& _address);
			bool				bind( u_short p_dwPort = 0);

public:
	// 2) bind�Լ�
	virtual	bool				process_request_bind( const net::sockaddr& _address) PURE;

	// 3) reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				process_reset_binder() PURE;

protected:
			void				register_binder(net::io::statistics::Nsocket* _pstatistics_socket);
			void				unregister_binder() noexcept;

public:
			lockable<>			m_lockable_manager_binder;
			binder::manager*	m_pmanager_binder = nullptr;
};


}
