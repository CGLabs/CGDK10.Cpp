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
// CGDK::placement_vector<T>
//
// 1. CGDK::placement_vector란!
//     CGDK::placement_vector는 기본적인 형태는 모두 vector와 동일하지만 이미 할당된
//    메모리에 vector를 구현하는 것을 의미한다.
//
//    - allocator가 존재하지 않는다.
//    - reserve 등을 통해 조절할 수 없고 단지 선언 시 설정해야 한다.
//    - 따라서 자동으로 크기가 커지는(auto expend)도 없다.
//    - 전반적인 성능은 vector보다 훨씬 우수하며 지역변수로 사용해도 부하가 거의
//      없다. (동적할당을 하지 않기 때문)
//    - 동작은 vector와 동일하다.
//
//
// 2. CGDK::placement_vector의 표준 준수 사항
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) placement_vector는 list와 다르게 random access operator를 제공해 준다.
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
// 4. Option) CGDK::placement_vector의 주요 옵션.
// 
//	  1) 없음...
//
// *주의: 이런 주석문들은 comiler에게 쓸모없는 부하를 줄수 있습니다. 따라서...
//        컴파일 시간이 느리면 이런 주석들을 모조리 지워주시기 바랍니다.
//
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/_definitions.h"
#include <stdexcept>

namespace CGDK
{

template <typename TDATA>
class placement_vector
{
// ****************************************************************************
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
//  * Reversible Requirement
//     1) X::reverse_iterator	역순환 때 사용되는 반복자.
//     2) X::const_reverse_iterator	역순환 때 사용되는 반복자.(const형)
// ----------------------------------------------------------------------------
public:
	// Standard 1) value type
	typedef TDATA			value_type;

	// Standard 2) Pointer
	typedef TDATA*			pointer;
	typedef const TDATA*	const_pointer;

	// Standard 3) Reference
	typedef TDATA&			reference;
	typedef const TDATA&	const_reference;

	// Standard 4) size of type & difference type
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Self) 자기자신(표준 아님.)
	typedef	placement_vector<TDATA>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, int TOTHER_SIZE>
	struct rebind
	{
		typedef placement_vector<TOTHER_DATA> other;
	};


// ****************************************************************************
// Common Container Standard)
//
//  * Common Container Requirement
//     1) X();			Default Constructor
//     2) X(a);			Copy Constrctor.(소요시간은 선형적)
//		  X u(a);
//     3) (&a)->~X();	Destructor.(소요시간은 선형적)
//     4) a.begin(); 	Container 순회에 사용할 시작과 끝 iterator 
//		  a.end();
//     5) a==b; a!=b;	Container 모든 원소 같으면 true.(소요시간 선형적)
//     6) a.size();		Container에 담김 원소의 갯수를 리턴한다.
//     7) a.max_size();	Container가 담을 수 있는 최대 원소 개수를 리턴한다.
//     8) a.empty();	Container가 비어 있는 경우라면 true를 리턴한다.
//     9) a<b; a>b; 	비교 연산(소요시간 선형적)
//		  a<=b; a>=b;
//    10) r=a;			Container 대입연산(소요시간 선형적)
//    11) a.swap(b);	동일한 타입의 두 커테이너를 서로 맞바꾼다.
//
//  * Reversible Requirement
//     1) a.rbegin(); 	반대방향 순회에 사용될 시작과 끝 iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	placement_vector(void* p_ptr, int _maxsize, int _size=0);
	placement_vector(const _mytype& _right);
	~placement_vector() noexcept;

public:
	void					placement(void* p_ptr, int _maxsize, int _size=0);
	void					unplacement();

public:
	// Common Standard 1) Status Function
	size_type				size() const noexcept { return m_ptr_last - m_ptr_first;}
	size_type				max_size() const noexcept { return m_iMaxSize;}
	bool					empty() const noexcept { return (size() == 0);}
																		  
	// Common Standard 2) 												  
	iterator				begin() noexcept { return iterator(m_ptr_first);}
	const_iterator			begin() const  noexcept { return const_iterator(m_ptr_first);}
	iterator				end() noexcept { return iterator(m_ptr_last);}
	const_iterator			end() const  noexcept { return const_iterator(m_ptr_last);}
	reverse_iterator		rbegin()  noexcept { return reverse_iterator(iterator(m_ptr_last-1));}
	const_reverse_iterator	rbegin() const noexcept { return const_reverse_iterator(const_iterator(m_ptr_last-1));}
	reverse_iterator		rend() noexcept { return reverse_iterator(iterator((m_ptr_first)-1));}
	const_reverse_iterator	rend() const noexcept { return const_reverse_iterator(const_iterator((m_ptr_first)-1));}

	// Common Standard 3) 
	void					swap(_mytype& _right) noexcept;

	// Common Standard 5) Operators
	bool					operator==(const _mytype& _right) const;
	bool					operator!=(const _mytype& _right) const;
	bool					operator<(const _mytype& _right) const;
	bool					operator>(const _mytype& _right) const;
	bool					operator<=(const _mytype& _right) const;
	bool					operator>=(const _mytype& _right) const;
	_mytype&				operator=(const _mytype& _right);


// ****************************************************************************
// Sequence Container Standard)
//
//  * Sequence Container Requirement
//    1) X(n, t);		t의 복사본 n개로 구성된 Sequence를 생성한다.
//		 X a(n, t);	
//    2) X(i, j); 		구간[i,j]의 내용과 동일한 Sequence를 생성한다.
//		 X a(i, j);
//    3) a.insert(p,t);	p앞에 t의 복사본을 삽입한다. 리턴값은 삽입된
//						원소를 가리키는 반복자이다.
//    4) a.insert(p,n,t);p앞에 t의 복사본 n개를 삽입한다.
//    5) a.insert(p,i,j);p앞에 [i,j]에 담긴 원소들의 복사본을 삽입한다.
//						i,j는 반복자
//    6) a.erase(q);	q가 가리키는 원소를 삭제한다. 리턴값은 삭제되기
//						전에 q다음에 위치했던 원소를 가리키는 반복자
//    7) a.erase(q1,q2);구간[q1,q2]에 포함된 원소들을 삭제한다. 리턴값은
//						삭제되기 전에 q2다음에 위치했던 원소를 가리키는
//						반복자.
//    8) a.clear();		컨테이너에 담긴 뭐든 원소를 삭제한다. 
//						a.erase(a.begin(), a.end())와 동일하다.
//
// ----------------------------------------------------------------------------
public:
	placement_vector();
	placement_vector(size_type _count);
	placement_vector(size_type _count, const TDATA& _val);
	template<typename TITERATOR>
	placement_vector(TITERATOR _first, TITERATOR _last);

public:
	// Sequence Standard 1) insert member function
	template<typename TITERATOR>
	void				insert(const_iterator _where, TITERATOR _first, TITERATOR _last);
	iterator			insert(const_iterator _where, const TDATA& _val);
	void				insert(const_iterator _where, size_type _count, const TDATA& _val);

	// Sequence Standard 2) erase member function
	iterator			erase(const_iterator _where);
	iterator			erase(const_iterator _first, const_iterator _last);

	// Sequence Standard 3) clear
	void				clear() noexcept;


// ****************************************************************************
// placement_vector Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const noexcept {	return m_size_max;}
	size_type				remained() const noexcept { return m_size_max-size();}

	// 2) Data
	reference				front() { return *m_ptr_first;}
	const_reference			front() const { return *m_ptr_first;}

	reference				back() { return *(m_ptr_last-1);}
	const_reference			back() const { return *(m_ptr_last-1);}

	reference				at(size_type _pos);
	const_reference			at(size_type _pos) const;

	reference				operator [] (size_type _pos);
	const_reference			operator [] (size_type _pos) const;

	// 3) push/pop
	void					push_back(const TDATA& _val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	template <typename ITERATOR>
	void					assign(ITERATOR _first, ITERATOR _last);
	void					assign(size_type p_Count, const TDATA& _val);

	// 5) Resize
	void					resize(size_type _new_size);


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) placement_vector
		TDATA*				m_ptr_first;
		TDATA*				m_ptr_last;
		int					m_size_max;


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	placement_vector<TDATA>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		const_iterator() noexcept {}
		explicit const_iterator(pointer p_pNow) noexcept { m_ptr_last=p_pNow;}

		// 2) 대입
		const_iterator&		operator=(const const_iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		pointer				operator->() { return &**this;}

		// 3) 반복
		const_reference		operator*() const { return *m_ptr_last;}
		const_iterator&		operator++() noexcept { ++m_ptr_last; return *this;}
		const_iterator		operator++(int) noexcept { return const_iterator(m_ptr_last++);}
		const_iterator&		operator--()  noexcept { --m_ptr_last; return *this;}
		const_iterator		operator--(int) noexcept { return const_iterator(m_ptr_last--);}
		const_iterator		operator+(difference_type _right) const noexcept { return const_iterator(m_ptr_last + _right);}
		void				operator+=(difference_type _right) noexcept { m_posNow += _right;}
		const_iterator		operator-(difference_type _right) const noexcept { return const_iterator(m_ptr_last - _right);}
		void				operator-=(difference_type _right) noexcept { m_posNow -= _right;}
		size_type			operator-(const const_iterator& _right) const noexcept { return m_ptr_last - _right.m_ptr_last;}
		size_type			operator-(const iterator& _right) const noexcept { return m_ptr_last - _right.m_ptr_last;}

		// 4) 비교
		bool				operator==(const const_iterator& _right) const noexcept { return m_ptr_last == _right.m_ptr_last;}
		bool				operator!=(const const_iterator& _right) const noexcept { return m_ptr_last != _right.m_ptr_last;}

		bool				operator>(const const_iterator&  _right) const noexcept { return m_ptr_last>_right.m_ptr_last;}
		bool				operator>=(const const_iterator&  _right) noexcept { return m_ptr_last>=_right.m_ptr_last;}
		bool				operator<(const const_iterator&  _right) const noexcept { return m_ptr_last<_right.m_ptr_last;}
		bool				operator<=(const const_iterator&  _right) noexcept { return m_ptr_last<=_right.m_ptr_last;}

		bool				operator>(const iterator&  _right) const noexcept { return m_ptr_last>_right.m_ptr_last;}
		bool				operator>=(const iterator&  _right) noexcept { return m_ptr_last>=_right.m_ptr_last;}
		bool				operator<(const iterator&  _right) const noexcept { return m_ptr_last<_right.m_ptr_last;}
		bool				operator<=(const iterator&  _right) noexcept { return m_ptr_last<=_right.m_ptr_last;}

	private:
		pointer				m_ptr_last;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	placement_vector<TDATA>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;
	// ----------------------------------------------------------------
	public:
		// 1) 생성자
		iterator() noexcept {}
		explicit iterator(pointer p_pNow) noexcept { m_ptr_last = p_pNow;}

		// 2) 대입
		iterator&			operator=(const iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		iterator&			operator=(const const_iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		pointer				operator->() { return &**this;}
							operator const_iterator() noexcept { return const_iterator(m_ptr_last);}
																		  
		// 3) 반복													    
		reference			operator*() const { return *m_ptr_last;}
		iterator&			operator++() noexcept { ++m_ptr_last; return *this;}
		iterator			operator++(int) noexcept { return iterator(m_ptr_last++);}
		iterator&			operator--() noexcept { --m_ptr_last; return *this;}
		iterator			operator--(int) noexcept { return iterator(m_ptr_last--);}
		iterator			operator+(difference_type _right) const noexcept { return iterator(m_ptr_last+_right);}
		void				operator+=(difference_type _right) noexcept { m_posNow+=_right;}
		iterator			operator-(difference_type _right) const noexcept { return iterator(m_ptr_last-_right);}
		void				operator-=(difference_type _right) noexcept { m_posNow -= _right;}
		size_type			operator-(const const_iterator& _right) const noexcept { return m_ptr_last-_right.m_ptr_last;}
		size_type			operator-(const iterator& _right) const noexcept { return m_ptr_last - _right.m_ptr_last;}

		// 4) 비교
		bool				operator==(const iterator& _right) const noexcept { return m_ptr_last==_right.m_ptr_last;}
		bool				operator!=(const iterator& _right) const noexcept{ return m_ptr_last!=_right.m_ptr_last;}

		bool				operator==(const const_iterator& _right) const { return m_ptr_last==_right.m_ptr_last;}
		bool				operator!=(const const_iterator& _right) const { return m_ptr_last!=_right.m_ptr_last;}
		
		bool				operator>(const const_iterator&  _right) const noexcept { return m_ptr_last > _right.m_ptr_last;}
		bool				operator>=(const const_iterator&  _right) noexcept { return m_ptr_last >= _right.m_ptr_last;}
		bool				operator<(const const_iterator&  _right) const noexcept { return m_ptr_last < _right.m_ptr_last;}
		bool				operator<=(const const_iterator&  _right) noexcept { return m_ptr_last <= _right.m_ptr_last;}

		bool				operator>(const iterator&  _right) const noexcept { return m_ptr_last > _right.m_ptr_last;}
		bool				operator>=(const iterator&  _right) noexcept { return m_ptr_last >= _right.m_ptr_last;}
		bool				operator<(const iterator&  _right) const noexcept { return m_ptr_last < _right.m_ptr_last;}
		bool				operator<=(const iterator&  _right) noexcept  return m_ptr_last <= _right.m_ptr_last;}

	private:
		pointer				m_ptr_last;
	};
};

template <typename TDATA>
placement_vector<TDATA>::placement_vector() : m_ptr_first(nullptr)
{
}

template <typename TDATA>
placement_vector<TDATA>::placement_vector(void* p_ptr, int _maxsize, int _size) : m_ptr_first(p_ptr), m_ptr_last(p_ptr+_size), m_size_max(_maxsize)
{
}

template <typename TDATA>
placement_vector<TDATA>::placement_vector(const _mytype& _right)
{
	// check) vector형의 자료여야지만 된다.
	CGDASSERT_ERROR(++_right.begin()==_right[1]);

	this->m_ptr_first = _right.front();
	this->m_ptr_last = _right.back()+1;
	this->m_size_max = _right.max_size();
}

template <typename TDATA>
template<typename TITERATOR>
placement_vector<TDATA>::placement_vector(TITERATOR _first, TITERATOR _last) : m_ptr_first(nullptr)
{
	this->m_ptr_first = &*_first;
	this->m_ptr_last = &*_last;
	this->m_size_max = _last-_first;

	// check) vector형의 자료여야지만 된다.
	CGDASSERT_ERROR((this->m_ptr_first + 1) == *(_first + 1));
}

template <typename TDATA>
placement_vector<TDATA>::~placement_vector() noexcept
{
	// 1) 모두 지운다.
	this->clear();
}


template <typename TDATA>
void placement_vector<TDATA>::placement(void* p_ptr, int _maxsize, int _size)
{
	this->m_ptr_first = p_ptr;
	this->m_ptr_last = p_ptr+_size;
	this->m_size_max = _maxsize;
}

template <typename TDATA>
void placement_vector<TDATA>::unplacement()
{
	this->m_ptr_first = nullptr;
	this->m_ptr_last = nullptr;
	this->m_size_max = 0;
}

template <typename TDATA>
typename placement_vector<TDATA>::_mytype& placement_vector<TDATA>::operator=(const _mytype& _right)
{
	// 1) 일단 모조리 다 지운다.
	this->clear();

	// 2) 삽입해넣는다.
	CGD_TRY
	{
		this->insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// return) 자기 자신 Return
	return	*this;
}


// 비교함수들
template <typename TDATA>
bool placement_vector<TDATA>::operator==(const _mytype& _right) const
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return (iter_dest == _right.end());

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return false;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 false리턴!
		if(*iter_src != *iter_dest)
			return false;

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator!=(const _mytype& _right) const	
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return	(iter_dest != _right.end());

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return true;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return true;

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator<(const _mytype& _right) const	
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return false;

		// check) Src가 끝인가???
		if(iter_src == this->end())
			return true;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return (*iter_src < *iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator>(const _mytype& _right) const	
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return	false;

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return true;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return	(*iter_src > *iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator<=(const _mytype& _right) const	
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return true;

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return	false;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return	(*iter_src<*iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator>=(const _mytype& _right) const	
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) 처음부터 찾기 위해 준비한다.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return true;

		// check) Src가 끝인가???
		if(iter_src == this->end())
			return false;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return	(*iter_src>*iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
TDATA& placement_vector<TDATA>::at(size_type _pos)
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK exception: out of rangeS."))

	// 1) 값을 읽어서 되돌린다.
	return this->m_ptr_first[_pos];
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::at(size_type _pos) const
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) p_iPosition의 값이 0보다는 크고 _capacity보다는 작어야 한다.
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK exception: out of range."))

	// 1) 값을 읽어서 되돌린다.
	return this->m_ptr_first[_pos];
}

template <typename TDATA>
TDATA& placement_vector<TDATA>::operator [] (size_type _pos)
{
	return this->at(_pos);
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::operator [] (size_type _pos) const
{
	return this->at(_pos);
}

template <typename TDATA>
void placement_vector<TDATA>::resize(size_type _new_size)
{
	// 1) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) max_size()보다 작은 크기여야지만 된다.
	CGD_THROW_IF(_new_size > this->max_size(), std::length_error("CGDK exception: invalid size."));

	// 1) 
	auto iter = this->end();
	auto new_end(this->begin() + _new_size);

	CGD_TRY
	{
		// 2) 늘어난 부분까지 Reset을 한다.
		for(; iter < new_end; ++iter)
		{
			new (&(*iter)) TDATA();
		}

		// 3) 줄어들면???(수정요)
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
		{
			_alval.destroy(&(*iter_roll), 1);
		}

		// re-throw)
		CGD_RETHROW;
	}

	// 2) Size를 새로 설정한다.
	this->m_ptr_last = new_end;
}


template <typename TDATA>
void placement_vector<TDATA>::clear() noexcept
{
	// check) m_ptr_first가 nullptr이면 끝낸다.
	CGD_RETURN_IF(m_ptr_first == nullptr)

	// 1) 모든 Item의 Destructor를 호출한다.
	for(iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		(*iter).~TDATA();
	}

	// 2) Last를 First로 만들어 0을 만든다.
	this->m_ptr_last = this->m_ptr_first;
}


template <typename TDATA>
void placement_vector<TDATA>::push_back(const TDATA& _val)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptr_first != nullptr);

	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct를 호출한다.
	new (this->m_ptr_last) TDATA(_val);
	
	// 2) Last 포인터 증가시킴
	++this->m_ptr_last;
}

template <typename TDATA>
void placement_vector<TDATA>::push_back()
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct를 호출한다.
	new (this->m_ptr_last) TDATA();
	
	// 2) Last 포인터 증가시킴
	++this->m_ptr_last;
}

template <typename TDATA>
void placement_vector<TDATA>::pop_back()
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty를 Check를 하지 않을 경우에 Debug 모드일때 Assert를 띄워준다.
	//   (Release Mode일 때는 아무일도 동작하지 않는다.)
	CGDASSERT_ERROR(!this->empty());
#else
	// Empty를 Check를 할 경우 Empty를 Check하고 비어 있을 경우 아무동작하지 않고 그냥 끝낸다.
	CGD_RETURN_IF(this->empty());
#endif

	// 1) Pop한다.
	{
		// - 크기를 줄인다.
		--this->m_ptr_last;

		// - Destructor를 호출한다.
		this->m_ptr_last->~TDATA();
	}
}

template <typename TDATA>
void placement_vector<TDATA>::assign(size_type _count, const TDATA& _val)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) 최대 갯수보다 크면 던진다!
	CGD_THROW_IF(this->remained() < _count, std::length_error("CGDK exception: invalid size."));

	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	auto first = this->m_ptr_last;

	// 2) End를 구한다.
	auto new_end = this->m_ptr_last + _count;

	CGD_TRY
	{
		// 3) 값을 넣는다.
		for(; first != new_end; ++first)
		{
			new (first) TDATA(_val);
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(TDATA* proll = this->m_ptr_last; proll != first; ++proll)
		{
			// - Destroy를 호출한다.
			(*proll).~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 4) 완료했으면 m_ptr_last를 new_end로 바꾼다.
	this->m_ptr_last += new_end;
}

template <typename TDATA>
template <typename ITERATOR>
void placement_vector<TDATA>::assign(ITERATOR _first, ITERATOR _last)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) m_ptr_first가 nullptr이면 던진다.
	CGD_THROW_IF(this->m_ptr_first == nullptr, std::length_error("CGDK exception: fail to placement."))

	// 1) 집어넣을 First와 Last를 가리키는 Iterator
	auto first = this->m_ptr_last;

	CGD_TRY
	{
		// 2) 값을 넣는다.
		for(; _first != _last; ++_first, ++first)
		{
			// check) Remained가 0이면 안됀다.
			CGD_THROW_IF(this->remained() != 0, std::length_error("CGDK exception: invalid size."));

			new (first) TDATA(*_first);
		}
	}
	CGD_CATCH_ALL
	{
		// - 생성했던 것을 다시 다 Destroy한다.
		for(TDATA* proll = this->m_ptr_last; proll != first; ++proll)
		{
			// - Destroy를 호출한다.
			(*proll).~TDATA();
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) 완료했으면 m_ptr_last를 new_end로 바꾼다.
	m_ptr_last += new_end;
}

template <typename TDATA>
template<typename TITERATOR>
void placement_vector<TDATA>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert count를 얻는다.
	auto insert_count = _last - _first;

	// 2) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(this->remained() < insert_count, std::length_error("CGDK exception: out of space."));

	// 3) Insert를 수행하기 위해 삽입할 공간을 비운다.
	const auto psource = const_cast<TDATA*>(_where.m_ptr_last);
	const auto pdest = const_cast<TDATA*>(_where.m_ptr_last + insert_count);
	auto nCount = this->m_ptr_last - psource;

	// 4) placement_vector를 한칸씩 뒤로 미룬다.
	memmove(pdest, psource, sizeof(TDATA) * nCount);

	// 5) Insert한다.
	CGD_TRY
	{
		// - 비운 자리에 Construct를 호출해 값을 복사한다.
		for(;_first != _last; ++_first, ++psource)
		{
			new (psource) TDATA(*_first);
		}
	}
	CGD_CATCH_ALL
	{
		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA* pBgn = const_cast<TDATA*>(_where.m_ptr_last);

		// - 생성했던 것을 다시 다 Destroy한다.
		for(;pBgn < psource; ++pBgn)
		{
			// - Destroy를 호출한다.
			pBgn->~TDATA();
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), pdest, sizeof(TDATA) * nCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 6) size를 증가시킨다.
	this->m_ptr_last += insert_count;
}



template <typename TDATA>
void placement_vector<TDATA>::insert(const_iterator _where, size_type _count, const TDATA& _val)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// check) 들어갈 공간이 존재하는지 검사한다.
	CGD_THROW_IF(remained()<_count, std::length_error("CGDK exception: out of space."));

	// 1) Insert를 수행하기 위해 삽입할 공간을 비운다.
	const auto psource = const_cast<TDATA*>(_where.m_ptr_last);
	const auto pdest = const_cast<TDATA*>(_where.m_ptr_last + _count);
	auto nCount = this->m_ptr_last - psource;

	// 2) placement_vector를 한칸씩 뒤로 미룬다.
	memmove(pdest, psource, sizeof(TDATA) * nCount);

	// 3) Insert한다.
	CGD_TRY
	{
		// - 비운 자리에 Construct를 호출해 값을 복사한다.
		for(;psource < pdest; ++psource)
		{
			// - Construct를 호출한다.
			new (psource) TDATA(_val);
		}
	}
	CGD_CATCH_ALL
	{
		// - 다시 땡기기 위해 주소와 갯수를 계산한다.
		TDATA* pBgn = const_cast<TDATA*>(_where.m_ptr_last);
		TDATA* pEnd = pdest-1;

		// 생성했던 것을 다시 다 Destroy한다.
		for(pBgn; pBgn < psource; ++pBgn)
		{
			// - Destroy를 호출한다.
			pBgn->~TDATA();
		}

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), pdest, sizeof(TDATA) * nCount);

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 4) size를 증가시킨다.
	this->m_ptr_last += _count;
}


template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::insert(const_iterator _where, const TDATA& _val)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= m_ptr_last);

	// check) 남은 공간이 있는지 확인한다.
	CGD_THROW_IF(this->remained() <= 0, std::length_error("CGDK exception: out of space."));

	// 1) Insert를 수행하기 위해 삽입할 공간을 비운다. (placement_vector를 한칸씩 뒤로 미룬다.)
	memmove(reinterpret_cast<void*>(_where.m_ptr_last + 1), reinterpret_cast<void*>(_where.m_ptr_last), (m_ptr_last-_where.m_ptr_last)*sizeof(TDATA));

	// 2) Insert한다.
	CGD_TRY
	{
		// - 비운 자리에 Constructor를 호출해 값을 복사한다.
		new (_where.m_ptr_last) TDATA(_val);
	}
	CGD_CATCH_ALL
	{
		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), reinterpret_cast<void*>(_where.m_ptr_last + 1), (m_ptr_last - _where.m_ptr_last) * sizeof(TDATA));

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// 3) size를 증가시킨다.
	++this->m_ptr_last;

	// return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return iterator(_where.m_ptr_last);
}



template <typename TDATA>
typename placement_vector<TDATA>::iterator  placement_vector<TDATA>::erase(const_iterator _where)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last < this->m_ptr_last);

	// check) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(this->size() > 0);

	// 1) 해당위치에 Destructor를 호출해 준다.
	(_where.m_ptr_last)->~TDATA();

	// 2) 해당위치로 지운다.
	memcpy(reinterpret_cast<void*>(_where.m_ptr_last), reinterpret_cast<void*>(_where.m_ptr_last + 1), (m_ptr_last - _where.m_ptr_last - 1)*sizeof(TDATA));

	// 3) Last를 줄인다.
	--this->m_ptr_last;

	// return)
	return iterator(_where.m_ptr_last);
}

template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::erase(const_iterator _first, const_iterator _last)
{
	// check) m_ptr_first가 nullptr이면 던진다.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_first.m_ptr_last >= m_ptr_first && _first.m_ptr_last <= m_ptr_last);

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_last.m_ptr_last >= m_ptr_first && _last.m_ptr_last <= m_ptr_last);

	// 1) First와 Last가 같다면 그냥 되돌림.
	int	iter_count = _last-_first;

	// check) ItemCount가 0이면 그냥 끝낸다.
	CGD_RETURN_IF(iter_count == 0, iterator(_last.m_ptr_last));

	// 2) Destroy함수를 호출한다.
	for(const_iterator iter = _first; iter != _last; ++iter)
	{
		(*iter).~TDATA();
	}

	// 3) 해당위치를 지운다.(덥어버린다.)
	memcpy(reinterpret_cast<void*>(_first.m_ptr_last), reinterpret_cast<void*>(_last.m_ptr_last), (_PtrLast - _last.m_ptr_last) * sizeof(TDATA));

	// 4) Size를 줄인다.
	this->m_ptr_last -= iter_count;

	// return)
	return iterator(_last.m_ptr_last);
}

template <typename TDATA>
void placement_vector<TDATA>::swap(_mytype& _right) noexcept
{
	// check) 같은 거라면 그냥 되돌린다.
	CGD_RETURN_IF(this == &_right);

	// 1) 무조건 통채로 바꾼다.(Allocator란 존재치 않는다. 단지 복사...)
	CGD_SWAP(*this, _right);
}


}