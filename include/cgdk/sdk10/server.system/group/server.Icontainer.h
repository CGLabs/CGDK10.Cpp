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
 @brief		옵저버를 가질수 있기 위한 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
 동작 형태는 그룹과 동일하다 다만 그룹과 다르게 배타적으로 동작하지 않는다.
 즉 옵저버는 동시에 여러 객체를 옵저빙할수 있다.
       
*///-----------------------------------------------------------------------------
template <class _TOBJECT>
class Iserver_container :
// inherited cClasses)
	virtual public				Ireferenceable
{
// declare) Member의 Type
public:
	using object_t = _TOBJECT;

// publics) 
public:
	//! @brief 등록된 '옵저버 객체'를 해제한다. @param _pobserver 등록 해제할 '옵저버 객체' @return true 성공 @return false 실패
	virtual	bool				unregister_object(_TOBJECT* _pobject) noexcept PURE;
	virtual	void				unsubscribe_all() noexcept PURE;

	//! @brief 락을 건다.
			void				lock_objects() noexcept { Ireferenceable::add_ref(); this->m_lockable_container.lock();}	// Group List에 Lock걸기.
			void				unlock_objects() noexcept { this->m_lockable_container.unlock(); Ireferenceable::release();}	// Group List의 Lock풀기.
	[[nodiscard]] 				operator lockable<>&() { return this->m_lockable_container;}	// 연산자 overlading(LOCKU용)

// implementation)
protected:
			lockable<>			m_lockable_container_enter;
			lockable<>			m_lockable_container;
};


}