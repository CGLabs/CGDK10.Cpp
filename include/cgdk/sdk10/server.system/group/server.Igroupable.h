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
 @class		Igroupable
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE, class _TGROUPBASE= Igroup<_TMEMBERBASE>>
class Igroupable : virtual public Ireferenceable
{
// declare) Member�� Type
public:
	using member_base_t = _TMEMBERBASE;
	using group_base_t = _TGROUPBASE;
	using member_set_t = group::MEMBER_SET<_TMEMBERBASE>;

// constructor/destructor)
public:
			Igroupable() noexcept : m_pgroup(), m_lockable_group(), m_pgroup_member_set(nullptr)	{}
	virtual	~Igroupable() noexcept { CGASSERT_ERROR(m_pgroup.empty()); CGASSERT_ERROR(m_pgroup_member_set == nullptr);}

// public)
public:
	//! @brief ���� �׷��� ��´�. @return ���� �׷�
	[[nodiscard]] object_ptr<group_base_t> get_group() const noexcept  { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->_get_group();	}
	[[nodiscard]] bool			is_member_of(const Igroup<member_base_t>* _pgroup) const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_group)); return this->_is_member_of(_pgroup); }

	//! @brief ���� �׷쿡�� ���´�.
			void				leave_group(uintptr_t _param = 0) noexcept;

	//! @brief ��� �����͸� ��´�. @return �׷��� ��� ������
	[[nodiscard]] member_set_t*	member_set() const noexcept { return this->m_pgroup_member_set;}
			void				member_set(member_set_t* _pGMD) noexcept { this->m_pgroup_member_set = _pGMD;}
			void				reset_member_set() noexcept { this->m_pgroup_member_set = nullptr;}
	[[nodiscard]] size_t		member_serial() const noexcept { RETURN_IF(this->m_pgroup_member_set == nullptr, static_cast<size_t>(-1)); return this->m_pgroup_member_set->member_serial();}

	[[nodiscard]] object_ptr<group_base_t> _get_group() const noexcept { return this->m_pgroup;}
	[[nodiscard]] bool			_is_member_of(const Igroup<member_base_t>* _pgroup) const noexcept { return this->m_pgroup == _pgroup;}

// implementation)
private:
	// 1) Group(Memberable�� �����ִ� Group�̴�. Group�� �������� ������ nullptr�� �ȴ�.)
			object_ptr<group_base_t> m_pgroup;
			lockable<>			m_lockable_group;

	// 2) Group Member Data(Group�� ���ӵ� Data)
			member_set_t*		m_pgroup_member_set;

	// 3) �پ� �ִ� Group�� ��� �����ϴ� �Լ�.
	//    - set_group()�� ResetGroup()�� �ǵ��� Group�ۿ����� ������� �ʴ� ���� �ٶ����ϴ�.
			template <class TSETGROUP>
			void				_set_group(TSETGROUP* _pgroup) noexcept { this->m_pgroup = _pgroup;}
			void				_reset_group() noexcept { this->m_pgroup.reset();}

	// Friend)
	friend	Igroup<member_base_t>;
};

template <class _TMEMBERBASE, class _TGROUPBASE>
void Igroupable<_TMEMBERBASE, _TGROUPBASE>::leave_group(uintptr_t _param) noexcept
{
	// declare) 
	auto pgroup = this->get_group();

	// check) �ƿ� Group�� ���� ���� ������ �׳� ������.
	RETURN_IF(pgroup.empty());

	// 1) casting
	auto pmember_base = dynamic_cast<member_base_t*>(this);

	// check)
	CGASSERT_ERROR(pmember_base != nullptr);

	// 2) �ϴ� Group���� Leave�� ���� �Ѵ�.
	group_base_t::request_leave(pgroup.get(), pmember_base, _param);
}


}