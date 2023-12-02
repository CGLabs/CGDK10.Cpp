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

namespace CGDK
{
//-----------------------------------------------------------------------------
/**
 @class		Igroup
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE, class _TPARAM = sMESSAGE>
class Igroup_countable :
	virtual public				Igroup_enterable<_TMEMBERBASE, _TPARAM>
{
public:
	using group_base_t = Igroup_enterable<_TMEMBERBASE, _TPARAM>;

public:
	[[nodiscard]] size_t		member_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_count(); }
	[[nodiscard]] size_t		member_capacity() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_capacity(); }
	[[nodiscard]] size_t		member_room_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_capacity() - this->process_get_member_count(); }
			void				member_capacity(size_t _max_count) { this->process_set_member_capacity(_max_count);}
			
	[[nodiscard]] bool			is_member_empty() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_count() == 0; }
	[[nodiscard]] bool			is_member_exist() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_count() != 0; }
	[[nodiscard]] bool			is_member_full() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_count() >= this->process_get_member_capacity(); }
	[[nodiscard]] bool			is_member_room() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->process_get_member_count() < this->process_get_member_capacity(); }

protected:
	[[nodiscard]] virtual size_t process_get_member_count() const noexcept PURE;
	virtual	void				process_set_member_capacity(size_t _max_count) PURE;
	[[nodiscard]] virtual size_t process_get_member_capacity() const noexcept PURE;
};


}