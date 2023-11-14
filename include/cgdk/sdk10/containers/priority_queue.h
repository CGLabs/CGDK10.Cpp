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
// CGDK::priority_queue<T>
//
// 1. CGDK::priority_queue��!
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

template <typename TDATA, typename TCONTAINER=std::vector<TDATA>, typename TPR=std::less<typename TCONTAINER::value_type>>
class priority_queue
{
// ----------------------------------------------------------------------------
// type definitions for standard
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

	// rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_CONTAINER, typename TOTHRER_PR>
	struct rebind
	{
		typedef priority_queue<TOTHER_DATA, TOTHER_CONTAINER, TOTHRER_PR> other;
	};

// constructor/destructor)
public:
			priority_queue() noexcept {}
	explicit priority_queue(const TCONTAINER& _Container) noexcept : m_container(_Container) {}
			priority_queue(const TPR& _pred, const TCONTAINER& _Cont);

			template<typename TITERATOR>
			priority_queue(TITERATOR _First, TITERATOR _Last);
			template<typename TITERATOR>
			priority_queue(TITERATOR _First, TITERATOR _Last, const TPR& _pred);
			template<typename TITERATOR>
			priority_queue(TITERATOR _First, TITERATOR _Last, const TPR& _pred,	const TCONTAINER& _Cont);

// public)
public:
			void		push(const value_type& _Val) { m_container.push_back(_Val); std::push_heap(m_container.begin(), m_container.end(), m_compare);}
			void		pop() { std::pop_heap(m_container.begin(), m_container.end(), m_compare); m_container.pop_back();}

			reference	top() { return m_container.front();}
			const_reference	top() const { return m_container.front();}

			bool		empty() const { return m_container.empty();}
			size_type	size() const { return m_container.size();}

// implementation)
private:
			TCONTAINER	m_container;
			TPR			m_compare;

};


template <typename TDATA, typename TCONTAINER, typename TPR>
priority_queue<TDATA, TCONTAINER, TPR>::priority_queue(const TPR& _pred, const TCONTAINER& _Cont)
	: m_container(_Cont)
	, m_compare(_pred)
{
	std::make_heap(m_container.begin(), m_container.end(), m_compare);
}

template <typename TDATA, typename TCONTAINER, typename TPR>
template<typename TITERATOR>
priority_queue<TDATA, TCONTAINER, TPR>::priority_queue(TITERATOR _First, TITERATOR _Last)
	: m_container(_First, _Last)
	, m_compare()
{
	std::make_heap(m_container.begin(), m_container.end(), m_compare);
}

template <typename TDATA, typename TCONTAINER, typename TPR>
template<typename TITERATOR>
priority_queue<TDATA, TCONTAINER, TPR>::priority_queue(TITERATOR _First, TITERATOR _Last, const TPR& _pred)
	: m_container(_First, _Last)
	, m_compare(_pred)
{
	std::make_heap(m_container.begin(), m_container.end(), m_compare);
}

template <typename TDATA, typename TCONTAINER, typename TPR>
template<typename TITERATOR>
priority_queue<TDATA, TCONTAINER, TPR>::priority_queue(TITERATOR _First, TITERATOR _Last, const TPR& _pred,	const TCONTAINER& _Cont)
	: m_container(_Cont)
	, m_compare(_pred)
{
	m_container.insert(m_container.end(), _First, _Last);
	std::make_heap(m_container.begin(), m_container.end(), m_compare);
}


}

