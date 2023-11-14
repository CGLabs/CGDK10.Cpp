//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Group Template Classes                           *
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

#include "cgdk/sdk10/server.system/group/server.group.base.h"

namespace CGDK
{

//-----------------------------------------------------------------------------
/**
 @class		no_manage
*///-----------------------------------------------------------------------------
template <class _TMEMBER, class _TPARAM = sMESSAGE, class _TMEMBERBASE = _TMEMBER>
class group::no_manage : 
	virtual public				Igroup_enterable<_TMEMBERBASE, _TPARAM>
{
public:
	using group_base_t = Igroup_enterable<_TMEMBERBASE, _TPARAM>;
	using member_t = _TMEMBER;
	using member_base_t = _TMEMBERBASE;
	using param_t = _TPARAM;

public:
			no_manage();
	virtual	~no_manage();

public:
			void				lock_member_enter() noexcept { Ireferenceable::add_ref(); m_lockable_enter.lock();}
			void				unlock_member_enter() noexcept { m_lockable_enter.unlock(); Ireferenceable::release();}
	[[nodiscard]] lockable<>&	member_enter_lock() noexcept { return m_lockable_enter;}

protected:
	virtual	void				on_enable_enter () {}
	virtual	void				on_disable_enter () {}

	virtual	result_code			on_member_entering (member_t* /*_pmember*/, param_t& /*_param*/) { return eRESULT::SUCCESS;}
	virtual	void				on_member_entered (member_t* /*_pmember*/, param_t& /*_param*/) {}
	virtual	uintptr_t			on_member_leaving (member_t* /*_pmember*/, uintptr_t _param) { return _param;}
	virtual	void				on_member_leaved (member_t* /*_pmember*/, uintptr_t /*_result*/) {}

protected:
	virtual bool				process_is_enable_member_enter () const noexcept override;
	virtual	bool				process_enable_member_enter	(bool _enable) override;
	virtual	result_code			process_enter (member_base_t* _pmember, param_t& _param) override;
	virtual	void				process_leave (member_base_t* _pmember, uintptr_t _param) noexcept override;

private:
	virtual	result_code			_process_member_entering (member_t* _pmember, param_t& _param);
	virtual	void				_process_member_entered (member_t* _pmember, param_t& _param);
	virtual	uintptr_t			_process_member_leaving	(member_t* _pmember, uintptr_t _param) noexcept;
	virtual	void				_process_member_leaved (member_t* _pmember, uintptr_t _result) noexcept;

private:
			bool				m_enable_enter;
			lockable<>			m_lockable_enter;
};


}

#include "cgdk/sdk10/server.system/group/server.group.no_manage.inl"
