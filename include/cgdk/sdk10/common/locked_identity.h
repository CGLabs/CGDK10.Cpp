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

//-----------------------------------------------------------------------------
//
// CGDK::locked_identity<ISIZE>
//
// 1. CGDK::locked_identity<ISIZE>란??
//    1) 기본적으로 CGDK::identity와 동일하지면 Thread safe하게 동작한다는 것만
//       차이가 있다.
//    2) 값의 유일성은 보장하지만 값의 순서는 보장하지 않는다.
//       *값의 순서까지 보장하기를 원한다면 CGDK::seat를 사용하라
//
// 2. 사용법
//    1) 최대 값은 template의 임자를 넘겨 선언한다. 
//
//       locked_identity<200>   tempseat;
//
//    2) 값을 할당받기 위해서는 alloc_object()함수를 사용하라.
//
//       int value = tempseat.alloc_object();
//
//    3) 값의 사용이 끝났으면 free()함수를 사용하여 값을 반환한다.
//
//       tempseat.free(value);
//
//    4) 다음의 함수를 사용하여 현재 상태를 확인할 수 있다.
//       size()   <- 현재 남아 있는 seat의 갯수
//       max_size <- 최대 seat의 수 선언시 template 인자로 넣었던 값이다.
//       empty()  <- 완전히 비어 있는지를 확인하는 함수.
//
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <int ISIZE>
class locked_identity
{
public:
			locked_identity() noexcept { reset();}
			~locked_identity() noexcept {}

public:
			int			alloc_seat() noexcept;
			void		free_seat(int _seat) noexcept;
			void		reset() noexcept;

			int			size() const noexcept { return m_identity.size();}
			int			max_size() const noexcept { return m_identity.max_size();}
			bool		empty() const noexcept { return m_identity.empty();}

private:
			lockable<identity<ISIZE>> m_identity;
};

template <int ISIZE>
int locked_identity<ISIZE>::alloc_seat() noexcept
{
	scoped_lock(m_identity)
	{
		return	m_identity.alloc_seat();
	}
}

template <int ISIZE>
void locked_identity<ISIZE>::free_seat(int _seat) noexcept
{
	scoped_lock(m_identity)
	{
		m_identity.free_seat(_seat);
	}
}

template <int ISIZE>
void locked_identity<ISIZE>::reset() noexcept
{
	scoped_lock(m_identity)
	{
		m_identity.reset();
	}
}


}