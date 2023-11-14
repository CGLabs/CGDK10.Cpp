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
// CGDK::seat
//
// 1. CGDK::seat란!
//     게임 Room과 같은 것을 제작할 때 사용자의 관리를 위해 좌석번호의 할당이
//    필요한 경우가 상당히 많다. 
//     예를 들면 전체 8자리가 있는 방의 경우 사용자가 들락날락하게 되면 방들이
//    순차적으로 차거나 비는 것이 아니라 중간 중간 좌석이 비거나 차거나 한다.
//    이때 입실을 할때마다 빈자리를 찾도록 하는 과정이 필요로 한다. 이때
//    seat는 남은 방번호를 stack형태로 보관하고 있다가 비어있는 자리를 즉시
//    제공해 준다.
//
//    - 방번호의 할당은 작은 번호부터 높은 번호로 할당을 해준다.
//    - priority queue를 사용하여 항당 최소 번호를 되돌려 준다.
//    - 할당된 번호를 다시 되돌려 받을 때 Sort가 일어난다.
//    - 좌석번호의 증가나 축소는 가능하다.
//      * 증가를 할때는 이미 할당된 번호 이후의 값을 stack을 하며
//      * 감소를 할때는 stack중 감소된 좌석번호 이후 값들을 stack에서 찾아
//        제거한다. 이미 할당된 것은 다시 free되어 돌아왔을 때 stack을 하지 
//        않는다.
//
//
// 2. CGDK::seat의 표준 준수 사항
//    1) create_seat
//       - 새로 seat를 생성한다.(일반적으로 처음 한번만 생성한다.)
//       - 한번 생성한 이후에 새로 생성할 경우그 차이만큼의 좌석을 조정한다.
//    2) reset_seat
//       - seat를 clear하고 다시 설정한다. 이때 이미 할당되어간 seat가 다시
//         돌아올 경우 문제가 있을 수 있으므로 동작 중에는 사용하지 않도록
//         해야 한다.
//    3) alloc_seat
//       - 새로운 seat를 할당해 준다. stack된 seat번호 중 가장 작은 번호를
//         할당해준다.
//    4) free_seat
//       - 할당된seat를 되돌려 받는다.
//       - 되돌려 받은 후 stack에 집어 넣고 sort를 수행한다.
//
// 3. 추가설명 or 사용예제
//
// 4. 연관 
//    CGDK::identity
//    CGDK::identity_priority
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <class TSEAT>
class seat 
{
public:
			seat() {}
			seat(size_t _max_count, TSEAT _begin = 0, TSEAT _step = 1) : m_begin(_begin), m_step(_step) { create(_max_count, _begin, _step);}
public:
	// 1) Seat Create & Reset
	inline	void			create(size_t _max_seat_count, TSEAT _begin=0, TSEAT _step=1);
	inline	void			reset() noexcept;
	// 2) Seat Alloc & Free
	inline	TSEAT			alloc_seat();
	inline	void			free_seat(TSEAT _seat);
	// 3) Status
			size_t			remained_seat() const noexcept { return m_vector_seat.size()-1;}
			size_t			max_seat() const noexcept { return m_vector_seat.capacity()-1;}
			bool			empty() const noexcept { return m_vector_seat.size()==1;}
	// 4) Info												  
			TSEAT			begin() const noexcept { return m_begin;}
			TSEAT			step() const noexcept { return m_step;}

private:
			TSEAT			m_begin = 0;
			TSEAT			m_step = 0;
			std::vector<TSEAT> m_vector_seat;
};

template <class TSEAT>
TSEAT seat<TSEAT>::alloc_seat()
{
	// 1) 사용 가능한 Seat가 0개이면 -1로 한다.
	if(empty())
	{
		return	static_cast<TSEAT>(-1);
	}

	// declare) 돌려줄값
	TSEAT seat_return = m_vector_seat[1];

	// 2) Down Heap
	TSEAT value = m_vector_seat.back();

	size_t parent = 1;
	size_t child = 2;
	size_t end = m_vector_seat.size()-2;

	while(child<=end)
	{
		if(child<end && m_vector_seat[child]>m_vector_seat[child+1])
			++child;

		if(value<=m_vector_seat[child])	
			break;

		m_vector_seat[parent] = m_vector_seat[child];

		parent = child;
		child <<= 1;
	}
	m_vector_seat[parent] = value;
	m_vector_seat.pop_back();

	// return) 
	return	seat_return;
}

template <class TSEAT>
void seat<TSEAT>::free_seat(TSEAT _seat)
{
	// 1) child...
	size_t child = m_vector_seat.size();

	// 2) 마지막에 Push한다.
	m_vector_seat.push_back(_seat);

	// 3) Up Heap
	size_t parent = (child>>1);
	while(parent && m_vector_seat[parent]>_seat)
	{
		m_vector_seat[child] = m_vector_seat[parent];

		child = parent;
		parent >>= 1;
	}
	m_vector_seat[child] = _seat;
}

template <class TSEAT>
void seat<TSEAT>::create(size_t _max_seat_count, TSEAT _begin, TSEAT _step)
{
	// check) p_iMaxSeatCount이 0인지를 확인한다.
	if(_max_seat_count == 0)
	{
		return;
	}

	// check) _step이 0인지를 확인한다.
	if(_step < 1)
	{
		return;
	}

	// check) _max_seat_count이 _stop보다도 작으면 그냥 Return한다.
	if(_max_seat_count<static_cast<size_t>(_step))
	{
		return;
	}

	// 1) 값을 설정한다.
	m_vector_seat.reserve(_max_seat_count+1);

	// 2) Step을 설정한다.
	m_begin = _begin;
	m_step = _step;

	// 3) 모두 지운다.
	reset();
}

template <class TSEAT>
void seat<TSEAT>::reset() noexcept
{
	// 1) 일단 clear한다.
	m_vector_seat.clear();

	// 2) 설정한다.
	TSEAT i = begin();
	TSEAT end = static_cast<TSEAT>(max_seat());

	// 3) Push back~~
	for(;i<end;i+=m_step)
	{
		m_vector_seat.push_back(i);
	}
}


}