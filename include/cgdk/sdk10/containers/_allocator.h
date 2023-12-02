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
//    �� �״�� list�̴�. �� list�� Ư¡�� circular linked list�� �����Ͽ�
//    push�� pop�� ���ϸ� ���� ���ϼ������� �ٿ��ٰ� �Ҽ� �ִ�. ����������
//    vector�� ���� ���� ������ ���Ϸ� ���� �� �ִ�.
//     node���� circulare linked list�� ����Ǿ� �ְ� head�� tail�� �����͵���
//    ������ �ִ�. 
//     �̶� push�� �ϸ� head�� �����͸� ��ĭ �ڷ� �л��̸� pop�Ҷ��� ��ĭ ����
//    ���̴�. �� �̶� ��ĭ �а����� ���� ���� ������ �׶����� �����ؼ� �����Ѵ�.
//     �ѹ� push�Ҷ� ������ Node�� pop�� ������� �ʰ� pointer�� ��ĭ �о����
//    ���ν� �������� ������ �Ͼ�� ������ ������ push�Ҷ� �����͸� ��ĭ �о�
//    �������ν� pop�� �ؼ� ������� �ʰԵ� node�� �ٽ� ����ϴ� ���� �ȴ�.
//     �� �߰��� node�� insert�Ҷ��� erase�ϰų� remove�ϰ� �� ��� �����̳� 
//    ������ �Ͼ�Ƿ� �� �κп� ���ؼ��� ������ list�� ������ �Ȱ���.
//
// 2. CGDK::list�� �ٽ�! Function�� ��� ����.
//    1) Add                ������
//    2) Detach             ȣȣȣ
//
// 3. CGDK::list�� �ֿ� ��� �뵵
//    ���α׷��� �����...
//
//
//-----------------------------------------------------------------------------
#include <new>

namespace CGDK	{

template<typename TDATA>
class allocator
{
public:
	typedef TDATA				value_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;
	typedef const value_type*	const_pointer;
	typedef const value_type&	const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;

	template<typename _Other>
	struct rebind
	{
		typedef allocator<_Other> other;
	};


	allocator()														{}
	allocator(const allocator<TDATA>&) 								{}
	
	template<typename _Other>
	allocator(const allocator<_Other>&) 							{}


	template<typename _Other>
	allocator<TDATA>& operator=(const allocator<_Other>&)			{	return (*this);}

	pointer				address(reference _Val) const				{	return &_Val;}
	const_pointer		address(const_reference _Val) const			{	return &_Val;}

	pointer				allocate(size_type _Count)					{	return ((TDATA*)::operator new(_Count * sizeof (TDATA)));}
	pointer				allocate(size_type _Count, const void*)		{	return allocate(_Count);}
	void				deallocate(pointer _ptr, size_type)			{	::operator delete(_ptr);}

	void				construct(pointer _Ptr)						{	::new (_Ptr) TDATA;}
	void				construct(pointer _Ptr, const TDATA& _Val)	{	::new (_Ptr) TDATA(_Val);}
	void				construct(pointer _Ptr, TDATA&& _Val)		{	::new (_Ptr) TDATA(std::forward(_Val)); }

	void				destroy(pointer _ptr)						{	_ptr->~TDATA(); _ptr;}
	
	static size_type	max_size()		 							{	size_t _Count = (size_t)(-1) / sizeof (TDATA);	return (0 < _Count ? _Count : 1);}
};

template<class TALLOC, class TOTHER>
bool operator==(const allocator<TALLOC>&, const allocator<TOTHER>&) throw()
{
	return true;
}

template<class TALLOC, class TOTHER> 
bool operator!=(const allocator<TALLOC>&, const allocator<TOTHER>&) throw()
{
	return false;
}

}
