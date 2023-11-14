//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

 @class		lockable
 @brief		크리티컬 섹션 클래스
 @todo		
 @ref		
 @details	\n
 가벼운 동기화 객체인 크리티컬 섹션 혹은 std:recursive_mutex를 포장한 클래스이다.

*///-----------------------------------------------------------------------------
typedef std::recursive_mutex	lock_object;


//-----------------------------------------------------------------------------
/**

 @class		lockable
 @brief		범위 락 클래스
 @todo		
 @ref		
 @details	\n
 가벼운 동기화 객체인 크리티컬 섹션 혹은 std:recursive_mutex를 포장한 클래스이다.

*///-----------------------------------------------------------------------------
template <class TOBJECT=void, class TLOCK = std::recursive_mutex>
class _lockable : public TOBJECT, public TLOCK
{
public:
	template<class... TARGS>
	_lockable(TARGS&&... _arguments) : TOBJECT(std::forward<TARGS>(_arguments)...) {}

public:
			template <class TDATA>
			TOBJECT&			operator=( const TDATA& _data ) noexcept		{ *(TOBJECT*)this=_data; return *this; }
			template <class TDATA>
			TOBJECT&			operator=(TDATA&& _data ) noexcept				{ *(TOBJECT*)this=std::forward<TDATA>(_data); return *this; }

			template <class TDATA>
			bool				operator==(const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this == _rhs; }
			template <class TDATA>
			bool				operator!=(const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this != _rhs; }
			template <class TDATA>
			bool				operator> (const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this >  _rhs; }
			template <class TDATA>
			bool				operator>=(const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this >= _rhs; }
			template <class TDATA>
			bool				operator< (const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this <  _rhs; }
			template <class TDATA>
			bool				operator<=(const TDATA& _rhs) const noexcept	{ return *(TOBJECT*)this <= _rhs; }

			operator _lockable<void, TLOCK>&() noexcept							{ return *reinterpret_cast<_lockable<void, TLOCK>*>(static_cast<TLOCK*>(this)); }
};

template<class TLOCK>
class _lockable<void, TLOCK> : public TLOCK
{
};

template <class TOBJECT = void> using shared_lockable = _lockable<TOBJECT, std::shared_mutex>;
template <class TOBJECT = void> using lockable = _lockable<TOBJECT, std::recursive_mutex>;


}