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
// 1. net::io::IConnectManager은~
//    1) connect Interface를 가진 Interface Class이다.
//    2) 단순히 connect()를 수행하기 위한 Interface들로만 되어 있다.
//
// 2. Public 함수.
//    1) add_connectable(...)/remove_connectable(...)
//       - Iconnectable을 추가하고 삭제하는 함수이다.
//
//    2) DisconnectAll()
//       - 모든 socket을 Graceful close를 수행한다. 내부적으로 각 socket에
//         shutdown()을 수행한다.
//       - Graceful close는 물리적으로 접속이 끊혔지만 접속된 상태로 남아있는
//         socket은 동작을 하지 않을 수 있다.
//       - 접속을 완료하는 과정에서 TIME_WAIT 상태가 유지됨으로써 많은 socket을
//         유지하게 될 가능성이 있다.
//
//    3) CloseAll()
//       - 모든 socket에 대해 Abortive close를 수행한다. 내부적으로 Linger옵션을
//         Abortive로 설정후 closesocket()을 수행한다.
//       - 함수 호출 즉시 socket의 접속이 종료되며 모든 socket관련 할당이 해제된다.
//       - 일반적으로 접속이 종료된 많은 socket을 유지하기가 위험한 Server에서
//         많이 사용된다.
//
//    4) count();
//       - 관리하고 있는 Iconnectable 객체의 수를 돌려준다.
//
//    5) alloc_iterator()
//       - 저장된 connectable의 포인터를 순회하며 직접 얻고 싶을 때 이 함수를
//         호출하여 Iterator를 얻을 수 있다.
//       - 일반적으로 Iterator를 얻게되면 내부 List에 Lock이 걸리게 된다.
//       - 사용 종료 후 얻은 Iterator가 소멸되면 Lock이 해제되게 된다.
//       - alloc_iterator()함수를 통해 얻어진 Iterator는 할당 직후 제일 처음
//         socket에 위치해 있다. 그리고 get_next()함수를 호출하여 다음 Iconnectable을
//         지적할 수 있다.
//       - 끝에 도달하게 되면 nullptr을 가지게 된다.
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
	// 1) connectable의 Add/Remove
	virtual	bool				add_connectable(Iconnectable* _pconnectable) noexcept PURE;
	virtual	bool				remove_connectable(Iconnectable* _pconnectable) noexcept PURE;
	[[nodiscard]] virtual bool	is_exist_connectable(Iconnectable* _pconnectable) const noexcept PURE;

	// 2) disconnect All Accepted socket
	virtual	void				disconnect_connectable_all() noexcept PURE;
	virtual	void				close_connectable_all(uint64_t _flag = 0) noexcept PURE;

	// 3) connectable 수
	[[nodiscard]] virtual size_t count() const noexcept PURE;

	// 4) Iterator얻기
	[[nodiscard]] virtual object_ptr<CONNECTABLE_ITERATOR> alloc_iterator() PURE;
};

class CGDK::net::io::Iconnectable_manager::CONNECTABLE_ITERATOR : virtual public Ireferenceable
{
public:
	virtual	void			reset() PURE;
	[[nodiscard]] virtual Iconnectable*	get_pre() PURE;
	[[nodiscard]] virtual Iconnectable*	get_next() PURE;
};
