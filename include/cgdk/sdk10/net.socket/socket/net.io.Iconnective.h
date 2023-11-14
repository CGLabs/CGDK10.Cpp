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
// net::io::Iconnective(연결 중계기)
//
// 1. Iconnective은~
//    1) 많은 connectable의 연결을 수행을 처리해주는 기능을 수행을 정의한다.
//    2) connectable을 상속받은 객체를 연결을 해준다.
//    3) 대표적인 것으로 TCP의 acceptor와 Connetor가 있다.
//       connective::acceptor는 연결을 받아 Iconnectable을 연결시켜주는 것이고
//       connective::connector는 클라이언트로 연결을 시도해주는 것이다.
//    4) 이 클래스를 상속받아 생성된 객체는 모두 connective::manager에 등록되며
//       connective::manager에서 찾아 사용할 수 있다.
//    5) 이 클래스는 Nameable을 상속받아 기본적으로 이름을 가진다.
//
// 2. 가상 함수.
//    1) process_connective_connect()
//       - 접속처리과 되는 과정을 정의하는 함수.
//
//    2) process_connective_disconnect()
//       - 접속해제되는 과정을 수행하는 함수.
//
//
//-----------------------------------------------------------------------------
class net::io::Iconnectable_notify : virtual public Ireferenceable
{
public:
	virtual	void				process_connective_connect(net::io::Iconnectable* _pconnectable, uintptr_t _result) PURE;
	virtual	void				process_connective_disconnect(net::io::Iconnectable* _pconnectable) PURE;
};

class net::io::Iconnective :
	virtual public				object::Iinitializable,
	virtual public				object::Istartable,
	virtual public				object::Istate,
	virtual	public				object::Inameable,
	virtual public				object::Ienable,
	virtual public				Iconnectable_notify,
	virtual	public				Iconnectable_manager,
	virtual public				net::io::statistics::Nconnective
{
public:
	// 1) start object
			template <class TSTART>
	[[nodiscard]] object_ptr<TSTART> start_object() const noexcept { return dynamic_pointer_cast<TSTART>(this->m_pobject_start); }
			void				set_start_object(Ireferenceable* _pobject) noexcept { this->m_pobject_start = _pobject;}

	// 2) public finctions
	[[nodiscard]] virtual std::size_t allocated_socket_count() const noexcept PURE;
	[[nodiscard]] virtual std::size_t max_socket_count() const noexcept PURE;
	virtual void				set_max_socket_count(std::size_t _max_allocate) noexcept PURE;


protected:
			void				register_connective() { net::io::connective::manager::instance()->join(this);}
			void				unregister_connective() noexcept { net::io::connective::manager::instance()->leave(this);}

protected:
			object_ptr<Ireferenceable>	m_pobject_start;
};


}