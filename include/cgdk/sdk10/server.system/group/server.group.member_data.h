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
//-----------------------------------------------------------------------------
//
// group::MEMBER_SET
//
//-----------------------------------------------------------------------------
namespace CGDK
{

//-----------------------------------------------------------------------------
/**
 @class		array
*///-----------------------------------------------------------------------------
template <class _TMEMBER>
struct group::MEMBER_SET
{
public:
	using member_t = _TMEMBER;

public:
			MEMBER_SET() noexcept : m_pmember(), m_pgroup(nullptr), m_member_serial(0) {}
			MEMBER_SET(Igroup<member_t>* _pgroup) noexcept : m_pmember(), m_pgroup(_pgroup), m_member_serial(0) {}

public:
	[[nodiscard]] object_ptr<Igroup<member_t>> get_group() const noexcept { return this->m_pgroup;}
			void				set_group(Igroup<member_t>* _pgroup) noexcept { this->m_pgroup = _pgroup;}

	[[nodiscard]] object_ptr<member_t> member() const noexcept { return this->m_pmember;}
			void				member(member_t* _pmember) noexcept { this->m_pmember=_pmember;}
			void				reset_member() noexcept { this->m_pmember.reset();}

	[[nodiscard]] group_member_id_t	member_serial() const noexcept { return this->m_member_serial;}
			void				member_serial(group_member_id_t p_iMemberSerial) noexcept { this->m_member_serial = p_iMemberSerial;}
			void				reset_member_serial() noexcept { this->m_member_serial=-1;}

	[[nodiscard]] bool			exist() const noexcept { return this->m_pmember.exist();}
	[[nodiscard]] bool			empty() const noexcept { return this->m_pmember.empty();}

	[[nodiscard]] bool			is_member_of(const Igroup<member_t>* _pgroup) const noexcept { return this->m_pmember->_is_member_of(_pgroup);}

public:
	[[nodiscard]] 				operator const object_ptr<member_t>&() const noexcept { return this->m_pmember;}

	[[nodiscard]] object_ptr<member_t>& operator->() noexcept { return this->m_pmember;}
	[[nodiscard]] const object_ptr<member_t>& operator->() const noexcept { return this->m_pmember;}
	[[nodiscard]] object_ptr<member_t>& operator*() noexcept { return this->m_pmember;}
	[[nodiscard]] const object_ptr<member_t>& operator*() const noexcept { return this->m_pmember;}

			MEMBER_SET&			operator=(member_t* _rhs) { this->m_pmember=_rhs; return *this;}
			MEMBER_SET&			operator=(const object_ptr<member_t>& _rhs) { this->m_pmember=_rhs; return *this;}

	[[nodiscard]] bool			operator==(const member_t* _rhs) const noexcept { return this->m_pmember == _rhs;}
	[[nodiscard]] bool			operator!=(const member_t* _rhs) const noexcept { return this->m_pmember != _rhs;}
	[[nodiscard]] bool			operator==(const Igroup<member_t>* _rhs) const noexcept { return this->m_pgroup == _rhs;}
	[[nodiscard]] bool			operator!=(const Igroup<member_t>* _rhs) const noexcept { return this->m_pgroup != _rhs;}

private:
			object_ptr<member_t> m_pmember;
			Igroup<member_t>*	m_pgroup;
			group_member_id_t	m_member_serial;
};


//-----------------------------------------------------------------------------
//
// group::MEMBER_SET_ARRAY
//
// Array형 Group의 MemberData
//
//-----------------------------------------------------------------------------

template <class _TMEMBER, class _TMEMBER_DATA>
struct group::MEMBER_SET_ARRAY : public MEMBER_SET<_TMEMBER>
{
public:
	using member_data_t = _TMEMBER_DATA;

public:
			MEMBER_SET_ARRAY() noexcept : MEMBER_SET<_TMEMBER>(), m_member_data() {}
			MEMBER_SET_ARRAY(Igroup<_TMEMBER>* _pgroup) noexcept : MEMBER_SET<_TMEMBER>(_pgroup), m_member_data() {}
public:
			member_data_t		m_member_data;

public:
			MEMBER_SET_ARRAY&	operator=(_TMEMBER* _rhs) noexcept { this->member(_rhs); return *this;}
};


//-----------------------------------------------------------------------------
//
// group::MEMBER_SET_LIST
//
// List형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TMEMBER, class _TMEMBER_DATA>
struct group::MEMBER_SET_LIST : public MEMBER_SET<_TMEMBER>
{
public:
	using member_data_t = _TMEMBER_DATA;

public:
			MEMBER_SET_LIST() noexcept : MEMBER_SET<_TMEMBER>(), m_member_data() {}
			MEMBER_SET_LIST(Igroup<_TMEMBER>* _pgroup) noexcept : MEMBER_SET<_TMEMBER>(_pgroup), m_member_data() {}
public:
			member_data_t		m_member_data;
public:
	typename circular_list<MEMBER_SET_LIST<_TMEMBER, _TMEMBER_DATA>>::const_iterator	iter;

			MEMBER_SET_LIST&	operator=(_TMEMBER* _rhs) noexcept { this->MEMBER_SET<_TMEMBER>::m_pmember=_rhs; return *this;}
};


//-----------------------------------------------------------------------------
//
// group::MEMBER_SET_MAP
//
// List형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TMEMBER, class _TKEY, class _TPARAM, class _TMEMBER_DATA>
struct group::MEMBER_SET_MAP : public MEMBER_SET<_TMEMBER>
{
public:
	using member_data_t = _TMEMBER_DATA;

public:
			MEMBER_SET_MAP() noexcept : MEMBER_SET<_TMEMBER>(), m_member_data() {}
			MEMBER_SET_MAP(Igroup<_TMEMBER>* _pgroup) noexcept : MEMBER_SET<_TMEMBER>(_pgroup), m_member_data() {}
public:
			member_data_t		m_member_data;
public:
#if defined(_MSC_VER)
	typename std::map<_TKEY, MEMBER_SET_MAP<_TMEMBER, _TKEY, _TPARAM, _TMEMBER_DATA>>::const_iterator	iter;
#else
			_TKEY				key;
#endif

			MEMBER_SET_MAP&		operator=(_TMEMBER* _rhs) noexcept { this->MEMBER_SET<_TMEMBER>::m_pmember=_rhs; return *this;}
};


}