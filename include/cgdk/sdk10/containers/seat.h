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
// 1. CGDK::seat��!
//     ���� Room�� ���� ���� ������ �� ������� ������ ���� �¼���ȣ�� �Ҵ���
//    �ʿ��� ��찡 ����� ����. 
//     ���� ��� ��ü 8�ڸ��� �ִ� ���� ��� ����ڰ� ��������ϰ� �Ǹ� �����
//    ���������� ���ų� ��� ���� �ƴ϶� �߰� �߰� �¼��� ��ų� ���ų� �Ѵ�.
//    �̶� �Խ��� �Ҷ����� ���ڸ��� ã���� �ϴ� ������ �ʿ�� �Ѵ�. �̶�
//    seat�� ���� ���ȣ�� stack���·� �����ϰ� �ִٰ� ����ִ� �ڸ��� ���
//    ������ �ش�.
//
//    - ���ȣ�� �Ҵ��� ���� ��ȣ���� ���� ��ȣ�� �Ҵ��� ���ش�.
//    - priority queue�� ����Ͽ� �״� �ּ� ��ȣ�� �ǵ��� �ش�.
//    - �Ҵ�� ��ȣ�� �ٽ� �ǵ��� ���� �� Sort�� �Ͼ��.
//    - �¼���ȣ�� ������ ��Ҵ� �����ϴ�.
//      * ������ �Ҷ��� �̹� �Ҵ�� ��ȣ ������ ���� stack�� �ϸ�
//      * ���Ҹ� �Ҷ��� stack�� ���ҵ� �¼���ȣ ���� ������ stack���� ã��
//        �����Ѵ�. �̹� �Ҵ�� ���� �ٽ� free�Ǿ� ���ƿ��� �� stack�� ���� 
//        �ʴ´�.
//
//
// 2. CGDK::seat�� ǥ�� �ؼ� ����
//    1) create_seat
//       - ���� seat�� �����Ѵ�.(�Ϲ������� ó�� �ѹ��� �����Ѵ�.)
//       - �ѹ� ������ ���Ŀ� ���� ������ ���� ���̸�ŭ�� �¼��� �����Ѵ�.
//    2) reset_seat
//       - seat�� clear�ϰ� �ٽ� �����Ѵ�. �̶� �̹� �Ҵ�Ǿ seat�� �ٽ�
//         ���ƿ� ��� ������ ���� �� �����Ƿ� ���� �߿��� ������� �ʵ���
//         �ؾ� �Ѵ�.
//    3) alloc_seat
//       - ���ο� seat�� �Ҵ��� �ش�. stack�� seat��ȣ �� ���� ���� ��ȣ��
//         �Ҵ����ش�.
//    4) free_seat
//       - �Ҵ��seat�� �ǵ��� �޴´�.
//       - �ǵ��� ���� �� stack�� ���� �ְ� sort�� �����Ѵ�.
//
// 3. �߰����� or ��뿹��
//
// 4. ���� 
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
	// 1) ��� ������ Seat�� 0���̸� -1�� �Ѵ�.
	if(empty())
	{
		return	static_cast<TSEAT>(-1);
	}

	// declare) �����ٰ�
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

	// 2) �������� Push�Ѵ�.
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
	// check) p_iMaxSeatCount�� 0������ Ȯ���Ѵ�.
	if(_max_seat_count == 0)
	{
		return;
	}

	// check) _step�� 0������ Ȯ���Ѵ�.
	if(_step < 1)
	{
		return;
	}

	// check) _max_seat_count�� _stop���ٵ� ������ �׳� Return�Ѵ�.
	if(_max_seat_count<static_cast<size_t>(_step))
	{
		return;
	}

	// 1) ���� �����Ѵ�.
	m_vector_seat.reserve(_max_seat_count+1);

	// 2) Step�� �����Ѵ�.
	m_begin = _begin;
	m_step = _step;

	// 3) ��� �����.
	reset();
}

template <class TSEAT>
void seat<TSEAT>::reset() noexcept
{
	// 1) �ϴ� clear�Ѵ�.
	m_vector_seat.clear();

	// 2) �����Ѵ�.
	TSEAT i = begin();
	TSEAT end = static_cast<TSEAT>(max_seat());

	// 3) Push back~~
	for(;i<end;i+=m_step)
	{
		m_vector_seat.push_back(i);
	}
}


}