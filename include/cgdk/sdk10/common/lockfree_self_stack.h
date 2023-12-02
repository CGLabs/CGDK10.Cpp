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
// CGDK::lockfree_self_stack<T>
//
// 1. CGDK::lockfree_self_stack<T>란!
//    1) CAS atomic함수를 사용하여 제작한 Lock-free stack이다.
//    2) ABA문제 해결을 위해 64Bit CAS를 사용하였다.
//    3) head의 내용 중 depth는 Stack된 Item의 갯수를 의미한다.
//    4) head의 내용 중 sequence는 ABA문제 해결을 위해 Operation마다 증가한다.
//    5) 파라메터로 받는 T의 형은 반드시 포인터형이여만 한다.
//       포인터가 아니면 절대로 동작하지 않을 수 있다.
//    6) 자체적인 node를 생성하지 않고 객체를 직접 node로 사용한다.
//       따라서 포인터 이외에 다른 형태는 stack되지 않으면 또 같은 객체를 
//       동시에 2개의 lockfree_self_stack에 넣을 수 없다.
//
// 2. 특징
//
//    1) 장점
//       - 매우 빠르다.
//       - Lock Fee의 특성상 Dead lock의 염려를 줄일 수 있다.
//
//    2) 단점
//       - Lock free는 순차 운행을 하거나 검색을 할수 없다.
//       - 단지 push와 pop을 수행할 때 Thread-safe할 뿐이다. Thread-safe한
//         운행(Traverse)가 필요할 경우 ciriticalsection을 사용한 queue를 
//         사용할 것을 권한다.
//       - node를 따로 생성하지 않기 때문에 동시에 두개의 lockfree_self_stack에
//         넣을 수 없다.
//       - data는 반드시 volatile long형의 Next 변수가 필요로 한다.
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{
template<class TDATA, unsigned IBYTES=sizeof(TDATA*)>
class lockfree_self_stack {};

#ifdef _WIN32

template <class TDATA>
class lockfree_self_stack<TDATA, 4>
{
// ----------------------------------------------------------------------------
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain에 담긴 값들의 형.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			순회할 때 사용되는 반복자.
//     5) X:const_iterator		순회할 때 사용되는 반복자(const형)
//     6) X:difference_type		두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type			X의 크기를 나타낼때 사용되는 형.
//
// ----------------------------------------------------------------------------
public:
	// Standard 1) value type.
	using value_type = TDATA;

	// Standard 2) Pointer.
	using pointer = TDATA*;
	using const_pointer = const TDATA*;

	// Standard 3) Reference.
	using reference = TDATA&;
	using const_reference = const TDATA&;

	// Standard 4) size of type & difference type.
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	// Self) 자기자신(표준 아님.)
	using _mytype = lockfree_self_stack<TDATA>;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		using other = lockfree_self_stack<TOTHER_DATA>;
	};


// constructor/destructor)
public:
			lockfree_self_stack() {clear();}
			~lockfree_self_stack() {}

// public)
public:
			size_t				size() const noexcept;
			void				clear() noexcept;

			void				push(TDATA _pdata) noexcept;
			void				push(TDATA _pfirst, TDATA _plast, int _count) noexcept;
			TDATA				pop() noexcept;
			TDATA				pop_all() noexcept;

// implementation)
private:
			union CGSLIST_HEAD
			{
				int64_t			alligned;

				struct
				{
				TDATA			phead;
				unsigned short	depth;
				unsigned short	sequence;
				} partial;
			};

	volatile CGSLIST_HEAD 		m_head;
};


template <class TDATA>
size_t lockfree_self_stack<TDATA, 4>::size() const noexcept
{
	return m_head.partial.depth;
}

template <class TDATA>
void lockfree_self_stack<TDATA, 4>::clear() noexcept
{
	pop_all();
}

template <class TDATA>
void lockfree_self_stack<TDATA, 4>::push(TDATA _pdata) noexcept
{
	#pragma warning(disable:26494)

	// check) 
	CGASSERT_ERROR(m_head.partial.phead!=_pdata);

	// declare)
	CGSLIST_HEAD temp_head;
	CGSLIST_HEAD temp_head_new;

	do
	{
		// 1) 기존 head를 얻어놓는다.
		temp_head.alligned = m_head.alligned;

		// 2) Next를 미리 맞춰놓느다.
		_pdata->Next = m_head.partial.phead;

		// 3) _pdata의 Next를 지금의 head로 설정해놓는다.
		temp_head_new.partial.phead = _pdata;
		temp_head_new.partial.depth = temp_head.partial.depth+1;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

		// 4) head랑 바꾼다.(바뀔 때까지..)
	} while(_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned)!=temp_head.alligned);

	#pragma warning(default:26494)
}

template <class TDATA>
void lockfree_self_stack<TDATA, 4>::push(TDATA _pfirst, TDATA _plast, int _count) noexcept
{
#pragma warning(disable:26494)

	// check) 
	CGASSERT_ERROR(m_head.partial.phead != _pfirst);

	// declare)
	CGSLIST_HEAD temp_head;
	CGSLIST_HEAD temp_head_new;

	do
	{
		// 1) 기존 head를 얻어놓는다.
		temp_head.alligned = m_head.alligned;

		// 2) Next를 미리 맞춰놓느다.
		_plast->Next = m_head.partial.phead;

		// 3) _pdata의 Next를 지금의 head로 설정해놓는다.
		temp_head_new.partial.phead = _pfirst;
		temp_head_new.partial.depth = temp_head.partial.depth + _count;
		temp_head_new.partial.sequence = temp_head.partial.sequence + 1;

		// 4) head랑 바꾼다.(바뀔 때까지..)
	} while (_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned) != temp_head.alligned);

#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop() noexcept
{
	#pragma warning(disable:26494)

	// declare) 
	CGSLIST_HEAD temp_head;
	CGSLIST_HEAD temp_head_new;

	// 1) CAS로 제거한다.
	do
	{
		// 1) 일단 head를 얻어놓는다.(Return해줄 것이다.)
		temp_head.alligned = m_head.alligned;

		// check)
		if(temp_head.partial.phead == 0)
		{
			return 0;
		}

		// 2) 얻은 head의 Next가 새로운 head가 될 것이다.
		temp_head_new.partial.phead = temp_head.partial.phead->Next;
		temp_head_new.partial.depth = temp_head.partial.depth-1;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

		// 3) head랑 바꾼다.(바뀔 때까지..)
	} while(_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned)!=temp_head.alligned);

	// return) 되돌린다#

	return	temp_head.partial.phead;

	#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop_all() noexcept
{
	#pragma warning(disable:26494)

	CGSLIST_HEAD temp_head;
	CGSLIST_HEAD temp_head_new;

	// 1) CAS로 전체를 떼낸다.
	do
	{
		// - 일단 head를 얻어놓는다.
		temp_head.alligned = m_head.alligned;

		temp_head_new.partial.phead = 0;
		temp_head_new.partial.depth = 0;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

	} while(_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned)!=temp_head.alligned);

	// return) head를 되돌린다.
	return temp_head.partial.phead;

	#pragma warning(default:26494)
}

#endif
}
