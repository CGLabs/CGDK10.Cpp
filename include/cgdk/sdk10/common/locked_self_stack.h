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
// 1. CGDK::Lock::stack��!
//     InterlockedPush/Pop�� ����Ͽ� ������ stack�̴�.
//    Thread Safe�ϰ� ���������� ������ Lock�� ���� �ʴ´�.
//
// 2. CGDK::Lock::stack�� �ٽ�! Function�� ��� ����.
//    1) push		Data�� stack�� push�ϴ� �Լ�.
//    2) pop		stack���� Data�� �ϳ� ������ �Լ�.
//    3) pop_all()	stack�� ��� data�� �Ѳ����� ������ �Լ�. �����ʹ� list���ַ�
//                  ������ ���´�.
//
// 3. CGDK::Lock::stack�� ���ǻ���
//    data�� �ݵ�� SLIST_ENTRY�� ��ӹ��� ��ü������ �ȴ�.
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
	//     1) X:value_type			Contain�� ��� ������ ��.
	//     2) X:reference			X:value_type&.
	//     3) X:const_reference		const X:value_type&.
	//     4) X:iterator			��ȸ�� �� ���Ǵ� �ݺ���.
	//     5) X:const_iterator		��ȸ�� �� ���Ǵ� �ݺ���(const��)
	//     6) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
	//     7) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
	// 1) ���� Function
	size_t				size() const noexcept;

	// 2) stack�� ������ ���� �Լ�.
	void				clear() noexcept;

	// 3) ���� Function
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
