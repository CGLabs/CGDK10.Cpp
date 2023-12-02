//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Socket template Classes                           *
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
/**

 @class		array
 @brief		�������� ������ �ֱ� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� ���´� �׷�� �����ϴ� �ٸ� �׷�� �ٸ��� ��Ÿ������ �������� �ʴ´�.
 �� �������� ���ÿ� ���� ��ü�� �������Ҽ� �ִ�.
       
*///-----------------------------------------------------------------------------
template <class _TOBJECT>
class Iserver_container :
// inherited cClasses)
	virtual public				Ireferenceable
{
// declare) Member�� Type
public:
	using object_t = _TOBJECT;

// publics) 
public:
	//! @brief ��ϵ� '������ ��ü'�� �����Ѵ�. @param _pobserver ��� ������ '������ ��ü' @return true ���� @return false ����
	virtual	bool				unregister_object(_TOBJECT* _pobject) noexcept PURE;
	virtual	void				unsubscribe_all() noexcept PURE;

	//! @brief ���� �Ǵ�.
			void				lock_objects() noexcept { Ireferenceable::add_ref(); this->m_lockable_container.lock();}	// Group List�� Lock�ɱ�.
			void				unlock_objects() noexcept { this->m_lockable_container.unlock(); Ireferenceable::release();}	// Group List�� LockǮ��.
	[[nodiscard]] 				operator lockable<>&() { return this->m_lockable_container;}	// ������ overlading(LOCKU��)

// implementation)
protected:
			lockable<>			m_lockable_container_enter;
			lockable<>			m_lockable_container;
};


}