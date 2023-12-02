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

namespace CGDK
{

template <typename TDATA>
class slist
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type		Contain에 담긴 값들의 형.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		순회할 때 사용되는 반복자.
//     5) X:const_iterator	순회할 때 사용되는 반복자(const형)
//     6) X:difference_type	두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type		X의 크기를 나타낼때 사용되는 형.
//
// ----------------------------------------------------------------------------
public:
	// Standard 1) value type.
	typedef TDATA			value_type;

	// Standard 2) Pointer.
	typedef TDATA*			pointer;
	typedef const TDATA*	const_pointer;

	// Standard 3) Reference.
	typedef TDATA&			reference;
	typedef const TDATA&	const_reference;

	// Standard 4) size of type & difference type.
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;

	// Self) 자기자신(표준 아님.)
	typedef	slist<TDATA>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA>
	struct rebind
	{
		typedef slist<TOTHER_DATA> other;
	};


// ****************************************************************************
// constructor/destructor)
// ----------------------------------------------------------------------------
public:
			slist()									{ m_head =0; m_size =0;}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Status Function
			TDATA&			front()					{	return *m_head;}
			const TDATA&	front() const			{	return *m_head;}

	// 2) Push & Pop.
			void			push_front(TDATA _Val);
			void			push(TDATA _Val)		{	push_front(_Val);}

			void			pop_front();
			TDATA			pop();

	// 3) 다 지움.
			void			clear()					{ m_head =0;}

	// 4) attribute
			bool			empty()					{	return (m_head ==0);}
			size_t			size() const			{	return m_size;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			TDATA			m_head;
			size_t			m_size;
};


template <typename TDATA>
void slist<TDATA>::push_front(TDATA _Val)
{
	_Val->Next	 = m_head;
	m_head		 = _Val;
	
	++m_size;
}

template <typename TDATA>
void slist<TDATA>::pop_front()
{
	if(m_head==0) return;
	
	m_head=m_head->Next;
	--m_size;
}

template <typename TDATA>
TDATA slist<TDATA>::pop()
{
	if(m_head==0) return 0;
	
	TDATA temp=m_head;
	m_head=m_head->Next;
	--m_size;

	return temp;
}




}