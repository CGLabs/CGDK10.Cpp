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
template <class _TOBSERVER>
class Iobservable :
// inherited cClasses)
	virtual public				Ireferenceable
{
// declare) Member�� Type
public:
	using observer_t = _TOBSERVER;
	using observer_channel_t = typename observer_t::observer_channel_t;

// publics) 
public:
	//! @brief ��ϵ� '������ ��ü'�� �����Ѵ�. @param _pobserver ��� ������ '������ ��ü' @return true ���� @return false ����
	virtual	bool				unsubscribe(observer_t* _pobserver, observer_channel_t _ocid) noexcept PURE;
	virtual	void				unsubscribe_all() noexcept PURE;

	//! @brief �������� ���� �Ǵ�.
			void				lock_observer() noexcept { Ireferenceable::add_ref(); this->m_lockable_observable_enter.lock();}
			void				unlock_observer() noexcept { this->m_lockable_observable_enter.unlock(); Ireferenceable::release();}
			lockable<>&			get_observer_lockable() noexcept { return this->m_lockable_observable;}
			const lockable<>&	get_observer_lockable() const noexcept { return this->m_lockable_observable;}
								operator lockable<>&() noexcept	{ return this->m_lockable_observable;}
								operator const lockable<>& () const noexcept { return this->m_lockable_observable;}

// implementation)
protected:
			lockable<>			m_lockable_observable_enter;
			lockable<>			m_lockable_observable;

protected:
	static	void				_set_observer_data	(_TOBSERVER* _pobserver, void* _pdata) noexcept { _pobserver->m_pobserver_data=_pdata;}
	static	void				_reset_observer_data(_TOBSERVER* _pobserver) noexcept { _pobserver->m_pobserver_data=nullptr; }
	static	void*				_get_observer_data	(_TOBSERVER* _pobserver) noexcept { return _pobserver->m_pobserver_data;}
};


}