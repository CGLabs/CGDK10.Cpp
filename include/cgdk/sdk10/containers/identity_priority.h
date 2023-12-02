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
// CGDK::identity_priority<ISIZE>
//
// 1. CGDK::identity_priority<ISIZE>란??
//    1) CGDK::seat의 기능과 완전히 동일하다 다만 CGDK::seat는 크기를 동작 중
//       동적으로 변경할 수 있는 반면 CGDK::identity_priority는 컴파일 때 정해지며
//       변경할 수 없다는 점만 차이가 있다.
//    2) 따라서 CGDK::seat보다 성능이 더 우수하다.
//
// 4. 연관 
//    CGDK::identity
//    CGDK::seat
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <int ISIZE>
class identity_priority
{
public:
			identity_priority() { reset();}
			~identity_priority() {}

public:
			int			alloc_identity();
			void		free_identity(int _seat);
			void		reset();
			int			size() const { return m_queued_count-1;}
			int			max_size() const { return ISIZE;}
			bool		empty() const { return (size()==0);}

private:
			int			m_array_queue[ISIZE+1];
			int			m_queued_count;
};

template <int ISIZE>
int identity_priority<ISIZE>::alloc_identity()
{
	// check) Empty이면 -1을 Return한다.
	if(this->empty())
	{
		return -1;
	}

	// declare) 돌려줄값
	int	return_value = this->m_array_queue[1];

	// 2) Down Heap
	int	value = this->m_array_queue[--this->m_queued_count];

	int	parent = 1;
	int	child = 2;
	int	end = this->m_queued_count-1;

	while(child<=end)
	{
		if(child<end && this->m_array_queue[child] > this->m_array_queue[child+1])
			++child;

		if(value <= this->m_array_queue[child])
			break;

		this->m_array_queue[parent] = this->m_array_queue[child];

		parent = child;
		child <<= 1;
	}
	this->m_array_queue[parent] = value;

	// return) 
	return return_value;
}

template <int ISIZE>
void identity_priority<ISIZE>::free_identity(int _seat)
{
	// 1) 현재 Stack된 위치를 구한다.
	int	child = this->m_queued_count++;

	// 2) Up Heap
	int	parent = (child>>1);
	while(parent && this->m_array_queue[parent]> _seat)
	{
		this->m_array_queue[child] = this->m_array_queue[parent];

		child = parent;
		parent>>=1;
	}
	this->m_array_queue[child] = _seat;
}

template <int ISIZE>
void identity_priority<ISIZE>::reset()
{
	// 1) 일단 clear한다.
	this->m_queued_count = ISIZE + 1;

	// 2) Seat값을 0부터 SIZE-1까지 값으로 넣는다.
	int* pstack = this->m_array_queue+1;
	for(int i=0; i<ISIZE; ++i,++pstack)
	{
		*pstack = i;
	}
}


}