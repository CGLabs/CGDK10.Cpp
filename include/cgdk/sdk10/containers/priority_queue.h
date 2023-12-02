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
// 1. CGDK::priority_queue란!
//     CGDK::array는 기본적인 형태는 모두 vector와 동일하지만 크기가 고정적이다
//    는 것이 차이점이라고 말할수 있다. 이 때문에 vector와 몇가지 차이점이 발생
//    하는데 그것은 다음과 같다.
//
//    - allocator가 존재하지 않는다.
//    - 생성이 지역변수공간(stack)에 생성되어 사용 시 동적할당을 하지 않는다.
//    - reserve 등을 통해 조절할 수 없고 단지 선언 시 설정해야 한다.
//    - 따라서 자동으로 크기가 커지는(auto expend)도 없다.
//    - 전반적인 성능은 vector보다 훨씬 우수하며 지역변수로 사용해도 부하가 거의
//      없다. (동적할당을 하지 않기 때문)
//    - 동작은 vector와 동일하다.
//
//
// 2. CGDK::array의 표준 준수 사항
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) array는 list와 다르게 random access operator를 제공해 준다.
//
//
// 3. exception-safe level.
//    1) Strong guarantee.
//       - 아무런 Option이 주어지지 않으면 기본적으로 strong exception safe
//         guarantee를 제공해준다.
//      -  걱 Operation을 수행할 때 exception safe확보를 위한 if문장들이 추가
//         된다.
//
//    2) No guarantee (With _CGD_NO_EXCEPTION_GUARANTEE flag)
//       - flag를 설정하면 No Execption safe guarantee를 제공해줄수 있다.
//       - 추가적으로 exception처리를 하지 않거나 혹은 안정성보다 빠른 속도를
//         원할 경우 Exception Guarantee를 제거할 경우 안전을 위한 추가적인
//         if문들이 제거되어 조금 더 빠른 code를 제공해 줄수 있다.
//       - 이를 통해 inline처리되는 확률이 늘어나는 것이 속도향상의 핵심이다.
//
//
// 4. Option) CGDK::array의 주요 옵션.
// 
//	  1) 없음...
//
// *주의: 이런 주석문들은 comiler에게 쓸모없는 부하를 줄수 있습니다. 따라서...
//        컴파일 시간이 느리면 이런 주석들을 모조리 지워주시기 바랍니다.
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
//     1) X:value_type			Contain에 담긴 값들의 형.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:size_type			X의 크기를 나타낼때 사용되는 형.
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

