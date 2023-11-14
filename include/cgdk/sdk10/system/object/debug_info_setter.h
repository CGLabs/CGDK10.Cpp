//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
// DEBUG_INFO_SETTER
//
//
//
//-----------------------------------------------------------------------------
class DEBUG_INFO_SETTER
{
public:
	DEBUG_INFO_SETTER(const char* _debug_info_filename, int _debug_info_line) noexcept : m_debug_info_filename(_debug_info_filename), m_debug_info_line(_debug_info_line) {}

	template <class TOBJECT>
	object_ptr<TOBJECT>		operator =(object_ptr<TOBJECT>&& _rhs) const noexcept { CGNEW_DEBUG_INFO_SET(_rhs, m_debug_info_filename, m_debug_info_line); return _rhs; }

	template <class TOBJECT>
	object_ptr<TOBJECT>		operator =(TOBJECT* _rhs) const noexcept { CGNEW_DEBUG_INFO_SET(_rhs,m_debug_info_filename, m_debug_info_line); return _rhs; }

	template <class TOBJECT, class... TARGS>
	object_ptr<TOBJECT>		operator =(const std::tuple<TOBJECT*, TARGS...>& _rhs) const { return _make_object_tuple_begin<TOBJECT>(m_debug_info_filename, m_debug_info_line, _rhs);}

	template <class TOBJECT, class... TARGS>
	object_ptr<TOBJECT>		operator =(std::tuple<TOBJECT*, TARGS...>&& _rhs) const { return _make_object_tuple_begin<TOBJECT>(m_debug_info_filename, m_debug_info_line, std::move(_rhs)); }

public:
	const char*			m_debug_info_filename;
	int					m_debug_info_line;
};


class DEBUG_INFO_SETTER_OWN
{
public:
	DEBUG_INFO_SETTER_OWN(const char* _debug_info_filename, int _debug_info_line) : m_debug_info_filename(_debug_info_filename), m_debug_info_line(_debug_info_line) {}

	template <class TOBJECT>
	CGDK::own_ptr<TOBJECT>	operator =(CGDK::own_ptr<TOBJECT>&& _rhs) const noexcept { CGNEW_DEBUG_INFO_SET(_rhs, m_debug_info_filename, m_debug_info_line); return std::move(_rhs); }

	template <class TOBJECT, class... TARGS>
	CGDK::own_ptr<TOBJECT>	operator =(const std::tuple<TOBJECT*, TARGS...>& _rhs) const { return _make_own_tuple_begin<TOBJECT>(m_debug_info_filename, m_debug_info_line, _rhs);}

	template <class TOBJECT, class... TARGS>
	CGDK::own_ptr<TOBJECT>	operator =(std::tuple<TOBJECT*, TARGS...>&& _rhs) const { return _make_own_tuple_begin<TOBJECT>(m_debug_info_filename, m_debug_info_line, std::move(_rhs)); }

public:
	const char*			m_debug_info_filename;
	int					m_debug_info_line;
};


}