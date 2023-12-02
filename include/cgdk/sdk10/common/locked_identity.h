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
// 1. CGDK::locked_identity<ISIZE>��??
//    1) �⺻������ CGDK::identity�� ���������� Thread safe�ϰ� �����Ѵٴ� �͸�
//       ���̰� �ִ�.
//    2) ���� ���ϼ��� ���������� ���� ������ �������� �ʴ´�.
//       *���� �������� �����ϱ⸦ ���Ѵٸ� CGDK::seat�� ����϶�
//
// 2. ����
//    1) �ִ� ���� template�� ���ڸ� �Ѱ� �����Ѵ�. 
//
//       locked_identity<200>   tempseat;
//
//    2) ���� �Ҵ�ޱ� ���ؼ��� alloc_object()�Լ��� ����϶�.
//
//       int value = tempseat.alloc_object();
//
//    3) ���� ����� �������� free()�Լ��� ����Ͽ� ���� ��ȯ�Ѵ�.
//
//       tempseat.free(value);
//
//    4) ������ �Լ��� ����Ͽ� ���� ���¸� Ȯ���� �� �ִ�.
//       size()   <- ���� ���� �ִ� seat�� ����
//       max_size <- �ִ� seat�� �� ����� template ���ڷ� �־��� ���̴�.
//       empty()  <- ������ ��� �ִ����� Ȯ���ϴ� �Լ�.
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