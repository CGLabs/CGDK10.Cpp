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
// 1. CGDK::placement_vector��!
//     CGDK::placement_vector�� �⺻���� ���´� ��� vector�� ���������� �̹� �Ҵ��
//    �޸𸮿� vector�� �����ϴ� ���� �ǹ��Ѵ�.
//
//    - allocator�� �������� �ʴ´�.
//    - reserve ���� ���� ������ �� ���� ���� ���� �� �����ؾ� �Ѵ�.
//    - ���� �ڵ����� ũ�Ⱑ Ŀ����(auto expend)�� ����.
//    - �������� ������ vector���� �ξ� ����ϸ� ���������� ����ص� ���ϰ� ����
//      ����. (�����Ҵ��� ���� �ʱ� ����)
//    - ������ vector�� �����ϴ�.
//
//
// 2. CGDK::placement_vector�� ǥ�� �ؼ� ����
//    1) (o) Common Container Standard 
//    2) (o) Reversible Standard 
//    3) (o) Sequence Container Standard 
//    4) (x) Assosiative Container Standard 
//
//    (*) placement_vector�� list�� �ٸ��� random access operator�� ������ �ش�.
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
// 4. Option) CGDK::placement_vector�� �ֿ� �ɼ�.
// 
//	  1) ����...
//
// *����: �̷� �ּ������� comiler���� ������� ���ϸ� �ټ� �ֽ��ϴ�. ����...
//        ������ �ð��� ������ �̷� �ּ����� ������ �����ֽñ� �ٶ��ϴ�.
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
//     1) X:value_type			Contain�� ��� ������ ��.
//     2) X:reference			X:value_type&.
//     3) X:const_reference		const X:value_type&.
//     4) X:iterator			��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator		��ȸ�� �� ���Ǵ� �ݺ���(const��)
//     6) X:difference_type		�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type			X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.
//     2) X::const_reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.(const��)
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

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
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
//     2) X(a);			Copy Constrctor.(�ҿ�ð��� ������)
//		  X u(a);
//     3) (&a)->~X();	Destructor.(�ҿ�ð��� ������)
//     4) a.begin(); 	Container ��ȸ�� ����� ���۰� �� iterator 
//		  a.end();
//     5) a==b; a!=b;	Container ��� ���� ������ true.(�ҿ�ð� ������)
//     6) a.size();		Container�� ��� ������ ������ �����Ѵ�.
//     7) a.max_size();	Container�� ���� �� �ִ� �ִ� ���� ������ �����Ѵ�.
//     8) a.empty();	Container�� ��� �ִ� ����� true�� �����Ѵ�.
//     9) a<b; a>b; 	�� ����(�ҿ�ð� ������)
//		  a<=b; a>=b;
//    10) r=a;			Container ���Կ���(�ҿ�ð� ������)
//    11) a.swap(b);	������ Ÿ���� �� Ŀ���̳ʸ� ���� �¹ٲ۴�.
//
//  * Reversible Requirement
//     1) a.rbegin(); 	�ݴ���� ��ȸ�� ���� ���۰� �� iterator
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
//    1) X(n, t);		t�� ���纻 n���� ������ Sequence�� �����Ѵ�.
//		 X a(n, t);	
//    2) X(i, j); 		����[i,j]�� ����� ������ Sequence�� �����Ѵ�.
//		 X a(i, j);
//    3) a.insert(p,t);	p�տ� t�� ���纻�� �����Ѵ�. ���ϰ��� ���Ե�
//						���Ҹ� ����Ű�� �ݺ����̴�.
//    4) a.insert(p,n,t);p�տ� t�� ���纻 n���� �����Ѵ�.
//    5) a.insert(p,i,j);p�տ� [i,j]�� ��� ���ҵ��� ���纻�� �����Ѵ�.
//						i,j�� �ݺ���
//    6) a.erase(q);	q�� ����Ű�� ���Ҹ� �����Ѵ�. ���ϰ��� �����Ǳ�
//						���� q������ ��ġ�ߴ� ���Ҹ� ����Ű�� �ݺ���
//    7) a.erase(q1,q2);����[q1,q2]�� ���Ե� ���ҵ��� �����Ѵ�. ���ϰ���
//						�����Ǳ� ���� q2������ ��ġ�ߴ� ���Ҹ� ����Ű��
//						�ݺ���.
//    8) a.clear();		�����̳ʿ� ��� ���� ���Ҹ� �����Ѵ�. 
//						a.erase(a.begin(), a.end())�� �����ϴ�.
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
		// 1) ������
		const_iterator() noexcept {}
		explicit const_iterator(pointer p_pNow) noexcept { m_ptr_last=p_pNow;}

		// 2) ����
		const_iterator&		operator=(const const_iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		pointer				operator->() { return &**this;}

		// 3) �ݺ�
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

		// 4) ��
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
		// 1) ������
		iterator() noexcept {}
		explicit iterator(pointer p_pNow) noexcept { m_ptr_last = p_pNow;}

		// 2) ����
		iterator&			operator=(const iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		iterator&			operator=(const const_iterator& _right) noexcept { m_ptr_last=_right.m_ptr_last; return *this;}
		pointer				operator->() { return &**this;}
							operator const_iterator() noexcept { return const_iterator(m_ptr_last);}
																		  
		// 3) �ݺ�													    
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

		// 4) ��
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
	// check) vector���� �ڷῩ������ �ȴ�.
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

	// check) vector���� �ڷῩ������ �ȴ�.
	CGDASSERT_ERROR((this->m_ptr_first + 1) == *(_first + 1));
}

template <typename TDATA>
placement_vector<TDATA>::~placement_vector() noexcept
{
	// 1) ��� �����.
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
	// 1) �ϴ� ������ �� �����.
	this->clear();

	// 2) �����سִ´�.
	CGD_TRY
	{
		this->insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// return) �ڱ� �ڽ� Return
	return	*this;
}


// ���Լ���
template <typename TDATA>
bool placement_vector<TDATA>::operator==(const _mytype& _right) const
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return (iter_dest == _right.end());

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� false����!
		if(*iter_src != *iter_dest)
			return false;

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator!=(const _mytype& _right) const	
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return	(iter_dest != _right.end());

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return true;

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator<(const _mytype& _right) const	
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return false;

		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return (*iter_src < *iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator>(const _mytype& _right) const	
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return	false;

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return	(*iter_src > *iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator<=(const _mytype& _right) const	
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return true;

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return	false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return	(*iter_src<*iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
bool placement_vector<TDATA>::operator>=(const _mytype& _right) const	
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = this->begin();
	auto iter_dest = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return true;

		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return	(*iter_src>*iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <typename TDATA>
TDATA& placement_vector<TDATA>::at(size_type _pos)
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK exception: out of rangeS."))

	// 1) ���� �о �ǵ�����.
	return this->m_ptr_first[_pos];
}

template <typename TDATA>
const TDATA& placement_vector<TDATA>::at(size_type _pos) const
{
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK exception: out of range."))

	// 1) ���� �о �ǵ�����.
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
	// 1) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) max_size()���� ���� ũ�⿩������ �ȴ�.
	CGD_THROW_IF(_new_size > this->max_size(), std::length_error("CGDK exception: invalid size."));

	// 1) 
	auto iter = this->end();
	auto new_end(this->begin() + _new_size);

	CGD_TRY
	{
		// 2) �þ �κб��� Reset�� �Ѵ�.
		for(; iter < new_end; ++iter)
		{
			new (&(*iter)) TDATA();
		}

		// 3) �پ���???(������)
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
		{
			_alval.destroy(&(*iter_roll), 1);
		}

		// re-throw)
		CGD_RETHROW;
	}

	// 2) Size�� ���� �����Ѵ�.
	this->m_ptr_last = new_end;
}


template <typename TDATA>
void placement_vector<TDATA>::clear() noexcept
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGD_RETURN_IF(m_ptr_first == nullptr)

	// 1) ��� Item�� Destructor�� ȣ���Ѵ�.
	for(iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		(*iter).~TDATA();
	}

	// 2) Last�� First�� ����� 0�� �����.
	this->m_ptr_last = this->m_ptr_first;
}


template <typename TDATA>
void placement_vector<TDATA>::push_back(const TDATA& _val)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptr_first != nullptr);

	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct�� ȣ���Ѵ�.
	new (this->m_ptr_last) TDATA(_val);
	
	// 2) Last ������ ������Ŵ
	++this->m_ptr_last;
}

template <typename TDATA>
void placement_vector<TDATA>::push_back()
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct�� ȣ���Ѵ�.
	new (this->m_ptr_last) TDATA();
	
	// 2) Last ������ ������Ŵ
	++this->m_ptr_last;
}

template <typename TDATA>
void placement_vector<TDATA>::pop_back()
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!this->empty());
#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	CGD_RETURN_IF(this->empty());
#endif

	// 1) Pop�Ѵ�.
	{
		// - ũ�⸦ ���δ�.
		--this->m_ptr_last;

		// - Destructor�� ȣ���Ѵ�.
		this->m_ptr_last->~TDATA();
	}
}

template <typename TDATA>
void placement_vector<TDATA>::assign(size_type _count, const TDATA& _val)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) �ִ� �������� ũ�� ������!
	CGD_THROW_IF(this->remained() < _count, std::length_error("CGDK exception: invalid size."));

	// 1) ������� First�� Last�� ����Ű�� Iterator
	auto first = this->m_ptr_last;

	// 2) End�� ���Ѵ�.
	auto new_end = this->m_ptr_last + _count;

	CGD_TRY
	{
		// 3) ���� �ִ´�.
		for(; first != new_end; ++first)
		{
			new (first) TDATA(_val);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(TDATA* proll = this->m_ptr_last; proll != first; ++proll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*proll).~TDATA();
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 4) �Ϸ������� m_ptr_last�� new_end�� �ٲ۴�.
	this->m_ptr_last += new_end;
}

template <typename TDATA>
template <typename ITERATOR>
void placement_vector<TDATA>::assign(ITERATOR _first, ITERATOR _last)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) m_ptr_first�� nullptr�̸� ������.
	CGD_THROW_IF(this->m_ptr_first == nullptr, std::length_error("CGDK exception: fail to placement."))

	// 1) ������� First�� Last�� ����Ű�� Iterator
	auto first = this->m_ptr_last;

	CGD_TRY
	{
		// 2) ���� �ִ´�.
		for(; _first != _last; ++_first, ++first)
		{
			// check) Remained�� 0�̸� �ȉ´�.
			CGD_THROW_IF(this->remained() != 0, std::length_error("CGDK exception: invalid size."));

			new (first) TDATA(*_first);
		}
	}
	CGD_CATCH_ALL
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(TDATA* proll = this->m_ptr_last; proll != first; ++proll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*proll).~TDATA();
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) �Ϸ������� m_ptr_last�� new_end�� �ٲ۴�.
	m_ptr_last += new_end;
}

template <typename TDATA>
template<typename TITERATOR>
void placement_vector<TDATA>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert count�� ��´�.
	auto insert_count = _last - _first;

	// 2) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(this->remained() < insert_count, std::length_error("CGDK exception: out of space."));

	// 3) Insert�� �����ϱ� ���� ������ ������ ����.
	const auto psource = const_cast<TDATA*>(_where.m_ptr_last);
	const auto pdest = const_cast<TDATA*>(_where.m_ptr_last + insert_count);
	auto nCount = this->m_ptr_last - psource;

	// 4) placement_vector�� ��ĭ�� �ڷ� �̷��.
	memmove(pdest, psource, sizeof(TDATA) * nCount);

	// 5) Insert�Ѵ�.
	CGD_TRY
	{
		// - ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		for(;_first != _last; ++_first, ++psource)
		{
			new (psource) TDATA(*_first);
		}
	}
	CGD_CATCH_ALL
	{
		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA* pBgn = const_cast<TDATA*>(_where.m_ptr_last);

		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(;pBgn < psource; ++pBgn)
		{
			// - Destroy�� ȣ���Ѵ�.
			pBgn->~TDATA();
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), pdest, sizeof(TDATA) * nCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 6) size�� ������Ų��.
	this->m_ptr_last += insert_count;
}



template <typename TDATA>
void placement_vector<TDATA>::insert(const_iterator _where, size_type _count, const TDATA& _val)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// check) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<_count, std::length_error("CGDK exception: out of space."));

	// 1) Insert�� �����ϱ� ���� ������ ������ ����.
	const auto psource = const_cast<TDATA*>(_where.m_ptr_last);
	const auto pdest = const_cast<TDATA*>(_where.m_ptr_last + _count);
	auto nCount = this->m_ptr_last - psource;

	// 2) placement_vector�� ��ĭ�� �ڷ� �̷��.
	memmove(pdest, psource, sizeof(TDATA) * nCount);

	// 3) Insert�Ѵ�.
	CGD_TRY
	{
		// - ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		for(;psource < pdest; ++psource)
		{
			// - Construct�� ȣ���Ѵ�.
			new (psource) TDATA(_val);
		}
	}
	CGD_CATCH_ALL
	{
		// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
		TDATA* pBgn = const_cast<TDATA*>(_where.m_ptr_last);
		TDATA* pEnd = pdest-1;

		// �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(pBgn; pBgn < psource; ++pBgn)
		{
			// - Destroy�� ȣ���Ѵ�.
			pBgn->~TDATA();
		}

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), pdest, sizeof(TDATA) * nCount);

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 4) size�� ������Ų��.
	this->m_ptr_last += _count;
}


template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::insert(const_iterator _where, const TDATA& _val)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= m_ptr_last);

	// check) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(this->remained() <= 0, std::length_error("CGDK exception: out of space."));

	// 1) Insert�� �����ϱ� ���� ������ ������ ����. (placement_vector�� ��ĭ�� �ڷ� �̷��.)
	memmove(reinterpret_cast<void*>(_where.m_ptr_last + 1), reinterpret_cast<void*>(_where.m_ptr_last), (m_ptr_last-_where.m_ptr_last)*sizeof(TDATA));

	// 2) Insert�Ѵ�.
	CGD_TRY
	{
		// - ��� �ڸ��� Constructor�� ȣ���� ���� �����Ѵ�.
		new (_where.m_ptr_last) TDATA(_val);
	}
	CGD_CATCH_ALL
	{
		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy(reinterpret_cast<void*>(_where.m_ptr_last), reinterpret_cast<void*>(_where.m_ptr_last + 1), (m_ptr_last - _where.m_ptr_last) * sizeof(TDATA));

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// 3) size�� ������Ų��.
	++this->m_ptr_last;

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator(_where.m_ptr_last);
}



template <typename TDATA>
typename placement_vector<TDATA>::iterator  placement_vector<TDATA>::erase(const_iterator _where)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(this->m_ptr_first != nullptr);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last < this->m_ptr_last);

	// check) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(this->size() > 0);

	// 1) �ش���ġ�� Destructor�� ȣ���� �ش�.
	(_where.m_ptr_last)->~TDATA();

	// 2) �ش���ġ�� �����.
	memcpy(reinterpret_cast<void*>(_where.m_ptr_last), reinterpret_cast<void*>(_where.m_ptr_last + 1), (m_ptr_last - _where.m_ptr_last - 1)*sizeof(TDATA));

	// 3) Last�� ���δ�.
	--this->m_ptr_last;

	// return)
	return iterator(_where.m_ptr_last);
}

template <typename TDATA>
typename placement_vector<TDATA>::iterator placement_vector<TDATA>::erase(const_iterator _first, const_iterator _last)
{
	// check) m_ptr_first�� nullptr�̸� ������.
	CGDASSERT_ERROR(m_ptr_first!=nullptr);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_first.m_ptr_last >= m_ptr_first && _first.m_ptr_last <= m_ptr_last);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_last.m_ptr_last >= m_ptr_first && _last.m_ptr_last <= m_ptr_last);

	// 1) First�� Last�� ���ٸ� �׳� �ǵ���.
	int	iter_count = _last-_first;

	// check) ItemCount�� 0�̸� �׳� ������.
	CGD_RETURN_IF(iter_count == 0, iterator(_last.m_ptr_last));

	// 2) Destroy�Լ��� ȣ���Ѵ�.
	for(const_iterator iter = _first; iter != _last; ++iter)
	{
		(*iter).~TDATA();
	}

	// 3) �ش���ġ�� �����.(���������.)
	memcpy(reinterpret_cast<void*>(_first.m_ptr_last), reinterpret_cast<void*>(_last.m_ptr_last), (_PtrLast - _last.m_ptr_last) * sizeof(TDATA));

	// 4) Size�� ���δ�.
	this->m_ptr_last -= iter_count;

	// return)
	return iterator(_last.m_ptr_last);
}

template <typename TDATA>
void placement_vector<TDATA>::swap(_mytype& _right) noexcept
{
	// check) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_right);

	// 1) ������ ��ä�� �ٲ۴�.(Allocator�� ����ġ �ʴ´�. ���� ����...)
	CGD_SWAP(*this, _right);
}


}