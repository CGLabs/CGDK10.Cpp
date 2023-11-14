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
// CGDK::stack<T, T>
//
// 1. CGDK::array��!
//     CGDK::array�� �⺻���� ���´� ��� vector�� ���������� ũ�Ⱑ �������̴�
//    �� ���� �������̶�� ���Ҽ� �ִ�. �� ������ vector�� ��� �������� �߻�
//    �ϴµ� �װ��� ������ ����.
//
//    - allocator�� �������� �ʴ´�.
//    - ������ ������������(stack)�� �����Ǿ� ��� �� �����Ҵ��� ���� �ʴ´�.
//    - reserve ���� ���� ������ �� ���� ���� ���� �� �����ؾ� �Ѵ�.
//    - ���� �ڵ����� ũ�Ⱑ Ŀ����(auto expend)�� ����.
//    - �������� ������ vector���� �ξ� ����ϸ� ���������� ����ص� ���ϰ� ����
//      ����. (�����Ҵ��� ���� �ʱ� ����)
//    - ������ vector�� �����ϴ�.
//
//
// 2. CGDK::array�� ǥ�� �ؼ� ����
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) array�� list�� �ٸ��� random access operator�� ������ �ش�.
//
//
// 3. exception-safe level.
//    1) Strong guarantee.
//       - �ƹ��� Option�� �־����� ������ �⺻������ strong exception safe
//         guarantee�� �������ش�.
//      -  �� Operation�� ������ �� exception safeȮ���� ���� if������� �߰�
//         �ȴ�.
//
//    2) No guarantee (With _CGD_NO_EXCEPTION_GUARANTEE flag)
//       - flag�� �����ϸ� No Execption safe guarantee�� �������ټ� �ִ�.
//       - �߰������� exceptionó���� ���� �ʰų� Ȥ�� ���������� ���� �ӵ���
//         ���� ��� Exception Guarantee�� ������ ��� ������ ���� �߰�����
//         if������ ���ŵǾ� ���� �� ���� code�� ������ �ټ� �ִ�.
//       - �̸� ���� inlineó���Ǵ� Ȯ���� �þ�� ���� �ӵ������ �ٽ��̴�.
//
//
// 4. Option) CGDK::array�� �ֿ� �ɼ�.
// 
//	  1) ����...
//
// *����: �̷� �ּ������� comiler���� ������� ���ϸ� �ټ� �ֽ��ϴ�. ����...
//        ������ �ð��� ������ �̷� �ּ����� ������ �����ֽñ� �ٶ��ϴ�.
//
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"
#include <stdexcept>

namespace CGDK
{

template <typename TDATA, typename TCONTAINER=std::vector<TDATA> >
class stack
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
// ----------------------------------------------------------------------------
public:
	typedef TCONTAINER								container_type;
	typedef typename TCONTAINER::value_type			value_type;
	typedef typename TCONTAINER::size_type			size_type;
	typedef typename TCONTAINER::reference			reference;
	typedef typename TCONTAINER::const_reference	const_reference;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_CONTAINER>
	struct rebind
	{
		typedef stack<TOTHER_DATA, TOTHER_CONTAINER> other;
	};


// constructor/destructor)
// ----------------------------------------------------------------------------
public:
			stack()		{}
	explicit stack(const TCONTAINER& _Container) : m_container(_Container)	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Push/Pop (���� �ٽ�)
			void		push(const value_type& _Val)			{ m_container.push_back(_Val);}
			void		pop()									{ m_container.pop_back();}
																  
	// 2) ���� ��� �Լ�.											 
			reference	top()									{ return m_container.back();}
			const_reference	top() const							{ return m_container.back();}
																  
	// 3) State�Լ�.											    
			bool		empty() const							{ return m_container.empty();}
			size_type	size() const							{ return m_container.size();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			TCONTAINER	m_container;

};


}