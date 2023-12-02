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
// net::io::Iconnective(���� �߰��)
//
// 1. Iconnective��~
//    1) ���� connectable�� ������ ������ ó�����ִ� ����� ������ �����Ѵ�.
//    2) connectable�� ��ӹ��� ��ü�� ������ ���ش�.
//    3) ��ǥ���� ������ TCP�� acceptor�� Connetor�� �ִ�.
//       connective::acceptor�� ������ �޾� Iconnectable�� ��������ִ� ���̰�
//       connective::connector�� Ŭ���̾�Ʈ�� ������ �õ����ִ� ���̴�.
//    4) �� Ŭ������ ��ӹ޾� ������ ��ü�� ��� connective::manager�� ��ϵǸ�
//       connective::manager���� ã�� ����� �� �ִ�.
//    5) �� Ŭ������ Nameable�� ��ӹ޾� �⺻������ �̸��� ������.
//
// 2. ���� �Լ�.
//    1) process_connective_connect()
//       - ����ó���� �Ǵ� ������ �����ϴ� �Լ�.
//
//    2) process_connective_disconnect()
//       - ���������Ǵ� ������ �����ϴ� �Լ�.
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