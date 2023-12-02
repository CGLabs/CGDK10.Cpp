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
// CGDK::lockfree_self_stack<TDATA, 8>
//
// 1. CGDK::lockfree_self_stack<TDATA, 8>��!
//    1) 64Bit �����͸� ���� CAS atomic�Լ��� ����Ͽ� ������ Lock-free stack�̴�.
//    2) �⺻���� ����� CGDK::lockfree_self_stack�� �����ϴ�. �ٸ� 64bit �����͸� 
//       �����ϴ°͸��� �������̴�.
//
//-----------------------------------------------------------------------------
namespace CGDK {

#ifdef _WIN32

template <class TDATA>
class lockfree_self_stack<TDATA, 8>
{
// ----------------------------------------------------------------------------
// type definitions for standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     5) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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
			lockfree_self_stack() noexcept: m_head() { m_head.alligned.llow = 0; m_head.alligned.lhigh = 0; }
			~lockfree_self_stack() noexcept {}
// public)
public:
			bool				empty() const noexcept { return m_head.ptr == nullptr; }
			size_type			size() const noexcept { return static_cast<size_type>(m_head.header.depth); }
			void				clear() noexcept;

			void				push(TDATA _pdata) noexcept;
			void				push(TDATA _pfirst, TDATA _plast, int _count) noexcept;
			TDATA				pop() noexcept;
			TDATA				pop_all() noexcept;

// implementation)
private:
	union DECLSPEC_ALIGN(16) CGSLIST_HEAD
	{
		struct
		{
			int64_t llow;
			int64_t lhigh;
		}alligned;

		struct
		{
			TDATA	 ptr;
			uint32_t depth;
			uint32_t sequence;
		}header;
	};

	volatile CGSLIST_HEAD m_head;
};

template <class TDATA>
void lockfree_self_stack<TDATA, 8>::clear() noexcept
{
	pop_all();
}

template <class TDATA>
void lockfree_self_stack<TDATA, 8>::push(TDATA _pdata) noexcept
{
#pragma warning(disable:26494)
	// check)
	CGASSERT_ERROR(m_head.header.ptr != _pdata);

	// declare)
	CGSLIST_HEAD head_now;
	CGSLIST_HEAD head_new;

	do
	{
		// 1) ���� head�� �����´�.
		head_now.alligned.llow = m_head.alligned.llow;
		head_now.alligned.lhigh = m_head.alligned.lhigh;

		// 2) Next�� �̸� ���������.
		_pdata->Next = m_head.header.ptr;

		// 3) _pdata�� Next�� ������ head�� �����س��´�.
		head_new.header.ptr = _pdata;
		head_new.header.depth = head_now.header.depth+1;
		head_new.header.sequence = head_now.header.sequence+1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
	}while(_InterlockedCompareExchange128(&m_head.alligned.llow, head_new.alligned.lhigh, head_new.alligned.llow, &head_now.alligned.llow)==0);
#pragma  warning(default:26494)
}

template <class TDATA>
void lockfree_self_stack<TDATA, 8>::push(TDATA _pfirst, TDATA _plast, int _count) noexcept
{
#pragma warning(disable:26494)
	// check)
	CGASSERT_ERROR(m_head.header.ptr != _pfirst);

	// declare)
	CGSLIST_HEAD head_now;
	CGSLIST_HEAD head_new;

	do
	{
		// 1) ���� head�� �����´�.
		head_now.alligned.llow = m_head.alligned.llow;
		head_now.alligned.lhigh = m_head.alligned.lhigh;

		// 2) Next�� �̸� ���������.
		_plast->Next = m_head.header.ptr;

		// 3) _plast�� Next�� ������ head�� �����س��´�.
		head_new.header.ptr = _pfirst;
		head_new.header.depth = head_now.header.depth + _count;
		head_new.header.sequence = head_now.header.sequence + 1;

		// 4) head�� �ٲ۴�.(�ٲ� ������..)
	} while (_InterlockedCompareExchange128(&m_head.alligned.llow, head_new.alligned.lhigh, head_new.alligned.llow, &head_now.alligned.llow) == 0);
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop() noexcept
{
#pragma warning(disable:26494)

	// declare)
	CGSLIST_HEAD head_now;
	CGSLIST_HEAD head_new;

	// 1) CAS�� �����Ѵ�.
	do
	{
		// 1) �ϴ� head�� �����´�.(Return���� ���̴�.)
		head_now.alligned.llow = m_head.alligned.llow;
		head_now.alligned.lhigh = m_head.alligned.lhigh;

		// check)
		if(head_now.header.ptr == 0)
			return 0;

		// 2) ���� head�� Next�� ���ο� head�� �� ���̴�.
		head_new.header.depth = head_now.header.depth-1;
		head_new.header.sequence = head_now.header.sequence+1;
		head_new.header.ptr = head_now.header.ptr->Next;

		// 3) head�� �ٲ۴�.(�ٲ� ������..)
	}while(_InterlockedCompareExchange128(&m_head.alligned.llow, head_new.alligned.lhigh, head_new.alligned.llow, &head_now.alligned.llow)==0);

	// return) �ǵ�����.
	return head_now.header.ptr;
#pragma  warning(default:26494)
}

template <class TDATA>
TDATA lockfree_self_stack<TDATA, 8>::pop_all() noexcept
{
#pragma warning(disable:26494)
	CGSLIST_HEAD head_now;
	CGSLIST_HEAD head_new;

	// 1) CAS�� ��ü�� ������.
	do
	{
		// - �ϴ� head�� �����´�.
		head_now.alligned.llow = m_head.alligned.llow;
		head_now.alligned.lhigh = m_head.alligned.lhigh;

		head_new.header.depth = 0;
		head_new.header.sequence = head_now.header.sequence+1;
		head_new.header.ptr = 0;

	}while(_InterlockedCompareExchange128(&m_head.alligned.llow, head_new.alligned.lhigh, head_new.alligned.llow, &head_now.alligned.llow)==0);

	// return) head�� �ǵ�����.
	return head_now.header.ptr;
#pragma  warning(default:26494)
}

#else

// GCC seems to have second thoughts about inlining the list push/pop functions, even at -O3...
#define FORCE_INLINE __attribute__((__always_inline__))

__attribute__((always_inline)) inline bool _Xatomic_compare_exchange_16(volatile __int128* _destination, __int128* _expected, __int128 _desired) noexcept
{
	union alignas(16) __atomic_uint16_t
	{
		unsigned __int128 val;
		struct
		{
			volatile uint64_t lo, hi;
		};
	};

	bool result;
	__atomic_uint16_t e;
	__atomic_uint16_t desired;
	e.val = *_expected;
	desired.val = _desired;
	__asm__ __volatile__(
		"lock cmpxchg16b %1"
		: "=@ccz" (result), "+m" (*_destination), "+a"(e.lo), "+d"(e.hi)
		: "c" (desired.hi), "b" (desired.lo)
		: "cc");
	if (!result)
		*_expected = e.val;

	return result;
}

template <class TDATA>
class lockfree_self_stack<TDATA, 8>
{
// ----------------------------------------------------------------------------
// type definitions for standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     5) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
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
			lockfree_self_stack() noexcept: m_head() { m_head.packed = 0; }
			lockfree_self_stack(const lockfree_self_stack&) = delete;
			lockfree_self_stack& operator = (const lockfree_self_stack&) = delete;
			~lockfree_self_stack() noexcept {}

// public)
public:
			bool				empty() const noexcept { return m_head.ptr == nullptr; }
			size_type			size() const noexcept { return static_cast<size_type>(m_head.depth); }
			void				clear() noexcept { pop_all(); }

	FORCE_INLINE void	push(TDATA _pdata) noexcept
    {
		CGSLIST_HEAD head_new;
		CGSLIST_HEAD head_now;

		head_new.ptr = _pdata;
        head_now.packed = m_head.packed;

        do
		{
			head_new.m_version = head_now.m_version + 1;
			head_new.depth = head_now.depth + 1;
			head_new.sequence = head_now.sequence + 1;

			_pdata->Next = head_now.ptr;

		} while (_Xatomic_compare_exchange_16(&m_head.packed, &head_now.packed, head_new.packed));
	}

	FORCE_INLINE void	push(TDATA _pfirst, TDATA _plast, int _count) noexcept
	{
		CGSLIST_HEAD head_new;
		CGSLIST_HEAD head_now;

		head_new.ptr = _pfirst;
		head_now.packed = m_head.packed;

		do
		{
			head_new.m_version = head_now.m_version + 1;
			head_new.depth = head_now.depth + _count;
			head_new.sequence = head_now.sequence + 1;

			_plast->Next = head_now.ptr;

		} while (_Xatomic_compare_exchange_16(&m_head.packed, &head_now.packed, head_new.packed));
	}


	FORCE_INLINE TDATA	pop() noexcept
    {
		// declare)
		CGSLIST_HEAD head_new;
		CGSLIST_HEAD head_now;

		// 1) �ϴ� head�� ��� ���´�.
		head_now.packed = m_head.packed;

        while (head_now.ptr != nullptr)
        {
			// 2) head_now Next�� ���ο� head�� �� ���̴�.
			head_new.ptr = head_now.ptr->Next;
			head_new.depth = head_now.depth - 1;
			head_new.sequence = head_now.sequence + 1;

			if (_Xatomic_compare_exchange_16(&m_head.packed, &head_now.packed, head_new.packed))
                break;
        }

		// return) 
        return head_now.ptr;
    }

	FORCE_INLINE TDATA	pop_all() noexcept
	{
		// declare)
		CGSLIST_HEAD head_new;
		CGSLIST_HEAD head_now;

		// 1) �ϴ� head�� ��� ���´�.
		head_now.packed = m_head.packed;

		do
		{
			head_new.ptr = 0;
			head_new.depth = 0;
			head_new.sequence = m_head.packed.sequence + 1;

		} while (_Xatomic_compare_exchange_16(&m_head.packed, &head_now.packed, head_new.packed));

		// return) head�� �ǵ�����.
		return head_now.ptr;
	}

private:
	// implementation)
	union alignas(16) CGSLIST_HEAD
    {
        struct
        {
			TDATA ptr;
			uint32_t depth;
			uint32_t sequence;
		};
		__int128 packed;
    };
	CGSLIST_HEAD m_head;

	static_assert(sizeof(CGSLIST_HEAD) == 16, "Bad size!");
	static_assert(alignof(CGSLIST_HEAD) == 16, "Bad alignment!");
};

#endif

}
