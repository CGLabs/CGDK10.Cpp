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
// 1. CGDK::identity_priority<ISIZE>��??
//    1) CGDK::seat�� ��ɰ� ������ �����ϴ� �ٸ� CGDK::seat�� ũ�⸦ ���� ��
//       �������� ������ �� �ִ� �ݸ� CGDK::identity_priority�� ������ �� ��������
//       ������ �� ���ٴ� ���� ���̰� �ִ�.
//    2) ���� CGDK::seat���� ������ �� ����ϴ�.
//
// 4. ���� 
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
	// check) Empty�̸� -1�� Return�Ѵ�.
	if(this->empty())
	{
		return -1;
	}

	// declare) �����ٰ�
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
	// 1) ���� Stack�� ��ġ�� ���Ѵ�.
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
	// 1) �ϴ� clear�Ѵ�.
	this->m_queued_count = ISIZE + 1;

	// 2) Seat���� 0���� SIZE-1���� ������ �ִ´�.
	int* pstack = this->m_array_queue+1;
	for(int i=0; i<ISIZE; ++i,++pstack)
	{
		*pstack = i;
	}
}


}