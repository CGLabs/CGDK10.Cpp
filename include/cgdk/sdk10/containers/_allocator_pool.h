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
// CGDK::allocator<T>
//
// 1. CGDK::list��!
//    �� �״�� list�̴�. �� list�� Ư¡�� ring������ linked list�� �����Ͽ�
//    push�� pop�� ���ϸ� ���� ���ϼ����̶�� �Ҽ� �ִ�.
//    �ִ� rist�� �Ѿ ��쿡�� list�� ���� ���� �߰��ϴ� ���ϰ� ����
//    �����̴�. 
//    �ִ�ũ���� list�� �ѹ� ����� ���� �״������ʹ� ���ϰ� ���� ���ٰ� ���� �ȴ�.
//    ���� �� linked-list �ְ� ���ɴ� �ְ��� ������ ��Ÿ����.
//    �׷��� list�� ���� �����ϰų� Ȥ�� ����� �Ǹ� ���� ���ϸ� �����ϹǷ� 
//    Temporary�� ���Ǵ� �뵵�δ� �� list�� ����� ��õ���� �ʴ´�. 
//
// 2. CGNetTplHeadArray�� �ٽ�! Function�� ��� ����.
//    1) Add                ������
//    2) Detach             ȣȣȣ
//
// 3. CGNetTplHeadArray�� �ֿ� ��� �뵵
//    ��ȭȭȭȭ
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{

template<typename TYPE>
class allocator_pool
{
// ****************************************************************************
// definitions)
// ----------------------------------------------------------------------------
public:
	// 1) Default type
	typedef TYPE				value_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;
	typedef const value_type*	const_pointer;
	typedef const value_type&	const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	// 2) convert an allocator<TYPE> to an allocator <_Other>
	template<typename _Other>
	struct rebind
	{	
		typedef allocator_pool<_Other> other;
	};


// ****************************************************************************
// Constructors)
// ----------------------------------------------------------------------------
public:
	allocator_pool() noexcept : m_pHead(nullptr)							{}
	allocator_pool(const allocator_pool<TYPE>&) noexcept : m_pHead(nullptr)	{}
	template<typename _Other>
	allocator_pool(const allocator_pool<_Other>&) noexcept : m_pHead(nullptr){}

	~allocator_pool() noexcept;

	
// ****************************************************************************
// Allocator�� Opeartion
// ----------------------------------------------------------------------------
public:
	// 1) Address
	pointer				address(reference _Val) const				{	return (&_Val);}
	const_pointer		address(const_reference _Val) const			{	return (&_Val);}

	// 2) Assignment Opeator
	template<typename _Other>
	allocator_pool<TYPE>& operator=(const allocator_pool<_Other>&)	{	return (*this);}	// assign from a related allocator (do nothing)

	// 3) Allocate(�Ҵ��ϴ� �Լ�)
	pointer				allocate(size_type _Count);
	pointer				allocate(size_type _Count, const void*)		{	return allocate(_Count);}

	// 4) Deallocate(�Ҵ� �����ϴ� �Լ�.)
	void				deallocate(const pointer _Ptr, size_type) noexcept;

	// 5) Construct/Destroy (�ּ����� �����ڿ� �Ҹ��� ȣ��)
	void				construct(pointer _Ptr)
	{
	#pragma push_macro("new")
	#undef new
		new (_Ptr) TYPE();
	#pragma pop_macro("new")
	}
	void				construct(pointer _Ptr, const TYPE& _Val)	
	{
	#pragma push_macro("new")
	#undef new
		new (_Ptr) TYPE(_Val);
	#pragma pop_macro("new")
	}
	void				construct(pointer _Ptr, TYPE&& _Val)	
	{
	#pragma push_macro("new")
	#undef new
		new (_Ptr) TYPE(std::move(_Val));
	#pragma pop_macro("new")
	}
	void				destroy([[maybe_unused]] pointer _Ptr)		{ (_Ptr)->~TYPE();}

	// 6) Max Size (�ִ� �Ҵ� ����)
	size_type			max_size() const							{ size_type count = (size_type)(-1) / sizeof (TYPE);	return (0 < count ? count : 1);}	// estimate maximum array size


// ****************************************************************************
// Pool
// ----------------------------------------------------------------------------
private:
				TYPE*	m_pHead;

	#undef	NO_WARNNING
};


template<typename TYPE>
allocator_pool<TYPE>::~allocator_pool() noexcept
{
	while(m_pHead !=0)
	{
		TYPE*	pHead	 = m_pHead;
		m_pHead = *reinterpret_cast<TYPE**>(m_pHead);

		::operator delete(pHead);
	}
}
	


template<typename TYPE>
typename allocator_pool<TYPE>::pointer allocator_pool<TYPE>::allocate(size_type /*_Count*/)
{
	if(m_pHead ==0)
	{
#pragma push_macro("new")
#undef new
		return ((TYPE*)::operator new(sizeof(TYPE)));
#pragma pop_macro("new")
	}

	TYPE*	pHead	 = m_pHead;

	m_pHead = *reinterpret_cast<TYPE**>(m_pHead);

	// �����ϰ� �׳�... _Count��ŭ new �� ������ �����ش�.
	return pHead;
}

template<typename TYPE>
void allocator_pool<TYPE>::deallocate(const pointer _Ptr, size_type) noexcept
{
	*reinterpret_cast<TYPE**>(_Ptr)	 = m_pHead;
	m_pHead			 = (TYPE*)_Ptr;
}

template<class TALLOC, class TOTHER>
bool operator==(const allocator_pool<TALLOC>&, const allocator_pool<TOTHER>&) noexcept
{
	return true;
}

template<class TALLOC, class TOTHER> 
bool operator!=(const allocator_pool<TALLOC>&, const allocator_pool<TOTHER>&) noexcept
{
	return false;
}

}