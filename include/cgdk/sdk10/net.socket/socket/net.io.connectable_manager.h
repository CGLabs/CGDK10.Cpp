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
// net::io::IConnectManager
//
// 1. net::io::IConnectManager��~
//    1) connect Interface�� ���� Interface Class�̴�.
//    2) �ܼ��� connect()�� �����ϱ� ���� Interface��θ� �Ǿ� �ִ�.
//
// 2. Public �Լ�.
//    1) add_connectable(...)/remove_connectable(...)
//       - Iconnectable�� �߰��ϰ� �����ϴ� �Լ��̴�.
//
//    2) DisconnectAll()
//       - ��� socket�� Graceful close�� �����Ѵ�. ���������� �� socket��
//         shutdown()�� �����Ѵ�.
//       - Graceful close�� ���������� ������ �������� ���ӵ� ���·� �����ִ�
//         socket�� ������ ���� ���� �� �ִ�.
//       - ������ �Ϸ��ϴ� �������� TIME_WAIT ���°� ���������ν� ���� socket��
//         �����ϰ� �� ���ɼ��� �ִ�.
//
//    3) CloseAll()
//       - ��� socket�� ���� Abortive close�� �����Ѵ�. ���������� Linger�ɼ���
//         Abortive�� ������ closesocket()�� �����Ѵ�.
//       - �Լ� ȣ�� ��� socket�� ������ ����Ǹ� ��� socket���� �Ҵ��� �����ȴ�.
//       - �Ϲ������� ������ ����� ���� socket�� �����ϱⰡ ������ Server����
//         ���� ���ȴ�.
//
//    4) count();
//       - �����ϰ� �ִ� Iconnectable ��ü�� ���� �����ش�.
//
//    5) alloc_iterator()
//       - ����� connectable�� �����͸� ��ȸ�ϸ� ���� ��� ���� �� �� �Լ���
//         ȣ���Ͽ� Iterator�� ���� �� �ִ�.
//       - �Ϲ������� Iterator�� ��ԵǸ� ���� List�� Lock�� �ɸ��� �ȴ�.
//       - ��� ���� �� ���� Iterator�� �Ҹ�Ǹ� Lock�� �����ǰ� �ȴ�.
//       - alloc_iterator()�Լ��� ���� ����� Iterator�� �Ҵ� ���� ���� ó��
//         socket�� ��ġ�� �ִ�. �׸��� get_next()�Լ��� ȣ���Ͽ� ���� Iconnectable��
//         ������ �� �ִ�.
//       - ���� �����ϰ� �Ǹ� nullptr�� ������ �ȴ�.
//
//
//-----------------------------------------------------------------------------
class CGDK::net::io::Iconnectable_manager :
// inherited classes)
	virtual public				net::io::Isender
{
public:
	class	CONNECTABLE_ITERATOR;

// publics)
public:
	// 1) connectable�� Add/Remove
	virtual	bool				add_connectable(Iconnectable* _pconnectable) noexcept PURE;
	virtual	bool				remove_connectable(Iconnectable* _pconnectable) noexcept PURE;
	[[nodiscard]] virtual bool	is_exist_connectable(Iconnectable* _pconnectable) const noexcept PURE;

	// 2) disconnect All Accepted socket
	virtual	void				disconnect_connectable_all() noexcept PURE;
	virtual	void				close_connectable_all(uint64_t _flag = 0) noexcept PURE;

	// 3) connectable ��
	[[nodiscard]] virtual size_t count() const noexcept PURE;

	// 4) Iterator���
	[[nodiscard]] virtual object_ptr<CONNECTABLE_ITERATOR> alloc_iterator() PURE;
};

class CGDK::net::io::Iconnectable_manager::CONNECTABLE_ITERATOR : virtual public Ireferenceable
{
public:
	virtual	void			reset() PURE;
	[[nodiscard]] virtual Iconnectable*	get_pre() PURE;
	[[nodiscard]] virtual Iconnectable*	get_next() PURE;
};
