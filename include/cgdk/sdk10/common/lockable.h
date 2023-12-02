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
 @brief		ũ��Ƽ�� ���� Ŭ����
 @todo		
 @ref		
 @details	\n
 ������ ����ȭ ��ü�� ũ��Ƽ�� ���� Ȥ�� std:recursive_mutex�� ������ Ŭ�����̴�.

*///-----------------------------------------------------------------------------
typedef std::recursive_mutex	lock_object;


//-----------------------------------------------------------------------------
/**

 @class		lockable
 @brief		���� �� Ŭ����
 @todo		
 @ref		
 @details	\n
 ������ ����ȭ ��ü�� ũ��Ƽ�� ���� Ȥ�� std:recursive_mutex�� ������ Ŭ�����̴�.

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