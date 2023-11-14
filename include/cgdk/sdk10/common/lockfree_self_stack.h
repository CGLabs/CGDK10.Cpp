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
// 1. CGDK::lockfree_self_stack<T>��!
//    1) CAS atomic�Լ��� ����Ͽ� ������ Lock-free stack�̴�.
//    2) ABA���� �ذ��� ���� 64Bit CAS�� ����Ͽ���.
//    3) head�� ���� �� depth�� Stack�� Item�� ������ �ǹ��Ѵ�.
//    4) head�� ���� �� sequence�� ABA���� �ذ��� ���� Operation���� �����Ѵ�.
//    5) �Ķ���ͷ� �޴� T�� ���� �ݵ�� ���������̿��� �Ѵ�.
//       �����Ͱ� �ƴϸ� ����� �������� ���� �� �ִ�.
//    6) ��ü���� node�� �������� �ʰ� ��ü�� ���� node�� ����Ѵ�.
//       ���� ������ �̿ܿ� �ٸ� ���´� stack���� ������ �� ���� ��ü�� 
//       ���ÿ� 2���� lockfree_self_stack�� ���� �� ����.
//
// 2. Ư¡
//
//    1) ����
//       - �ſ� ������.
//       - Lock Fee�� Ư���� Dead lock�� ������ ���� �� �ִ�.
//
//    2) ����
//       - Lock free�� ���� ������ �ϰų� �˻��� �Ҽ� ����.
//       - ���� push�� pop�� ������ �� Thread-safe�� ���̴�. Thread-safe��
//         ����(Traverse)�� �ʿ��� ��� ciriticalsection�� ����� queue�� 
//         ����� ���� ���Ѵ�.
//       - node�� ���� �������� �ʱ� ������ ���ÿ� �ΰ��� lockfree_self_stack��
//         ���� �� ����.
//       - data�� �ݵ�� volatile long���� Next ������ �ʿ�� �Ѵ�.
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
		// 1) ���� head�� �����´�.
		temp_head.alligned = m_head.alligned;

		// 2) Next�� �̸� ���������.
		_pdata->Next = m_head.partial.phead;

		// 3) _pdata�� Next�� ������ head�� �����س��´�.
		temp_head_new.partial.phead = _pdata;
		temp_head_new.partial.depth = temp_head.partial.depth+1;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
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
		// 1) ���� head�� �����´�.
		temp_head.alligned = m_head.alligned;

		// 2) Next�� �̸� ���������.
		_plast->Next = m_head.partial.phead;

		// 3) _pdata�� Next�� ������ head�� �����س��´�.
		temp_head_new.partial.phead = _pfirst;
		temp_head_new.partial.depth = temp_head.partial.depth + _count;
		temp_head_new.partial.sequence = temp_head.partial.sequence + 1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
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

	// 1) CAS�� �����Ѵ�.
	do
	{
		// 1) �ϴ� head�� �����´�.(Return���� ���̴�.)
		temp_head.alligned = m_head.alligned;

		// check)
		if(temp_head.partial.phead == 0)
		{
			return 0;
		}

		// 2) ���� head�� Next�� ���ο� head�� �� ���̴�.
		temp_head_new.partial.phead = temp_head.partial.phead->Next;
		temp_head_new.partial.depth = temp_head.partial.depth-1;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

		// 3) head�� �ٲ۴�.(�ٲ� ������..)
	} while(_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned)!=temp_head.alligned);

	// return) �ǵ�����#

	return	temp_head.partial.phead;

	#pragma warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 4>::pop_all() noexcept
{
	#pragma warning(disable:26494)

	CGSLIST_HEAD temp_head;
	CGSLIST_HEAD temp_head_new;

	// 1) CAS�� ��ü�� ������.
	do
	{
		// - �ϴ� head�� �����´�.
		temp_head.alligned = m_head.alligned;

		temp_head_new.partial.phead = 0;
		temp_head_new.partial.depth = 0;
		temp_head_new.partial.sequence = temp_head.partial.sequence+1;

	} while(_InterlockedCompareExchange64(&m_head.alligned, temp_head_new.alligned, temp_head.alligned)!=temp_head.alligned);

	// return) head�� �ǵ�����.
	return temp_head.partial.phead;

	#pragma warning(default:26494)
}

#endif
}
