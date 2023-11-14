//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGDK::identity<ISIZE>
//
// 1. CGDK::identity<ISIZE>란??
//    1) 말 그대로 ISIZE만큼의 고유번호를 할당해주는 관리자이다. 
//    2) alloc가 호출되면 0~(ISIZE-1) 사이에서 할당되지 않은 번호를 돌려준다.
//    3) free로 할당받았던 번호가 반환되면 반환된 고유번호는 다음에 다시 할당
//       되어지는 것에 사용된다.
//    4) 더이상 할당할 고유번호가 없으면 -1이 return된다.
//    5) 유사한 Container로는 seat가 있다. seat와 다른 점은 고유번호를 sort하지
//       하지 않는다는 점이다. seat는 할당되지 않은 번호 중에서 가장 작은 번호를
//       할당해주지만 이 identity는 그렇지 않다.
//
// 2. 사용법
//    1) 최대 값은 template의 임자를 넘겨 선언한다. 
//
//       locked_identity<200>   tempseat;
//
//    2) 값을 할당받기 위해서는 alloc()함수를 사용하라.
//       (이때 모든 seat를 다 사용하여 더이상 할당할 seat가 없을 시는 -1을 리턴한다.)
//
//       int value = tempseat.alloc();
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
// 2. 주의점
//    1) 이 Container는 alloc와 free를 할때 Thread-Safe하지 않다. 그러므로
//       만약에 Thread-Safe하게 동작시키고자 한다면 Lock을 걸어 사용해야 한다.
//
// 3. 연관 
//    CGDK::identity_priority
//    CGDK::seat
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <int ISIZE, int IMIN=0, int ISTEP = 1, int IEMPTYCODE = -1>
class identity
{
public:
			identity() noexcept { reset();}
			~identity() noexcept {}

public:
			int			alloc_seat() noexcept;
			void		free_seat(int p_iSeat) noexcept;
			void		reset() noexcept;

			int			size() const noexcept { return m_stacked; }
			int			max_size() const noexcept { return ISIZE; }
			int			min_value() const noexcept { return IMIN; }
			int			max_value() const noexcept { return IMIN+ISTEP * (ISIZE - 1); }
			int			empty_code() const noexcept { return IEMPTYCODE; }
			int			step() const noexcept { return ISTEP; }
			bool		empty() const noexcept { return (size() == 0); }

private:
			int			m_array_stack[ISIZE];
			int			m_stacked;
};


template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
int identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::alloc_seat() noexcept
{
	// check) Empty이면 IEMPTYCODE을 Return한다.
	if(empty())
	{
		return IEMPTYCODE;
	}

	// 1) Seat값을 Pop해서 되돌린다.
	return m_array_stack[--m_stacked];
}

template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
void identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::free_seat(int p_iSeat) noexcept
{
	m_array_stack[m_stacked++] = p_iSeat;
}

template <int ISIZE, int IMIN, int ISTEP, int IEMPTYCODE>
void identity<ISIZE, IMIN, ISTEP, IEMPTYCODE>::reset() noexcept
{
	// 1) 일단 clear한다.
	m_stacked = ISIZE;

	// 2) Seat값을 0부터 SIZE-1까지 값으로 넣는다.
	for(int i=0, value = max_value(); i < ISIZE; ++i, value -= ISTEP)
	{
		m_array_stack[i] = value;
	}
}


}
