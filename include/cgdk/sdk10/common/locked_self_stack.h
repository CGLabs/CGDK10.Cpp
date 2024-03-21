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
// CGDK::Lock::stack<T>
//
// 1. CGDK::Lock::stack란!
//     InterlockedPush/Pop을 사용하여 구현한 stack이다.
//    Thread Safe하게 동작하지만 동작중 Lock을 걸지 않는다.
//
// 2. CGDK::Lock::stack의 핵심! Function의 기능 설명.
//    1) push		Data를 stack에 push하는 함수.
//    2) pop		stack에서 Data를 하나 빼내는 함수.
//    3) pop_all()	stack의 모든 data를 한꺼번에 빼내는 함수. 데이터는 list혀애로
//                  뽛혀져 나온다.
//
// 3. CGDK::Lock::stack의 주의사항
//    data는 반드시 SLIST_ENTRY를 상속받은 객체여야지 된다.
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TDATA>
class locked_self_stack
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
	using _mytype = locked_self_stack<TDATA>;

	// Rebinder) 
	template <class TOTHER_DATA>	
	struct rebind
	{
		using other = locked_self_stack<TOTHER_DATA>;
	};

public:
	locked_self_stack() noexcept : m_phead(nullptr), m_depth(0) {}
	~locked_self_stack() noexcept {}

public:
	// 1) 상태 Function
	size_t				size() const noexcept;

	// 2) stack을 모조리 비우는 함수.
	void				clear() noexcept;

	// 3) 동작 Function
	void				push(TDATA _pdata) noexcept;
	void				push(TDATA _pfirst, TDATA _plast, int _count) noexcept;
	TDATA				pop() noexcept;
	TDATA				pop_all() noexcept;

	std::mutex			m_lockable_head;
	TDATA				m_phead;
	int					m_depth;
};

template <class TDATA>
size_t locked_self_stack<TDATA>::size() const noexcept
{
	return this->m_depth;
}

template <class TDATA>
void locked_self_stack<TDATA>::clear() noexcept
{
	this->pop_all();
}

template <class TDATA>
void locked_self_stack<TDATA>::push(TDATA _pdata) noexcept
{
	std::lock_guard<std::mutex> lock(this->m_lockable_head);

	_pdata->Next = this->m_phead;
	this->m_phead = _pdata;

	++this->m_depth;
}

template <class TDATA>
void locked_self_stack<TDATA>::push(TDATA _pfirst, TDATA _plast, int _count) noexcept
{
	std::lock_guard<std::mutex> lock(this->m_lockable_head);

	_plast->Next = this->m_phead;
	this->m_phead = _pfirst;

	this->m_depth += _count;
}

template <class TDATA>
TDATA locked_self_stack<TDATA>::pop() noexcept
{
	std::lock_guard<std::mutex> lock(this->m_lockable_head);

	if(this->m_phead == nullptr)
		return nullptr;

	auto data = this->m_phead;
	this->m_phead = this->m_phead->Next;

	--this->m_depth;

	return data;
}

template <class TDATA>
TDATA locked_self_stack<TDATA>::pop_all() noexcept
{
	std::lock_guard<std::mutex> lock(this->m_lockable_head);

	auto data = this->m_phead;
	this->m_phead = nullptr;

	this->m_depth = 0;

	return data;
}
}
