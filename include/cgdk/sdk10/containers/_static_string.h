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

#define __CGDK_STATIC_STRING

namespace CGDK
{

template <class TDATA, size_t TSIZE>
class basic_static_string
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
	typedef uint32_t		size_type;
	typedef ptrdiff_t		difference_type;

	// Standard 5) Iterators
	class iterator;
	class const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	basic_static_string<TDATA, TSIZE>	_mytype;

	// Rebinder) 
	template<class TOTHER_DATA, size_t TOTHER_SIZE>
	struct rebind
	{
		typedef basic_static_string<TOTHER_DATA, TOTHER_SIZE> other;
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
	basic_static_string() noexcept;
	basic_static_string(const _mytype& _rhs) noexcept;
	basic_static_string(_mytype&& _rhs) noexcept;
	~basic_static_string() noexcept;

public:
	basic_static_string(std::basic_string_view<TDATA>&& _string);
	basic_static_string(const std::basic_string_view<TDATA>& _string);

	basic_static_string(std::basic_string<TDATA>&& _string);
	basic_static_string(const std::basic_string<TDATA>& _string);

	template<size_t A>
	basic_static_string(const TDATA(&_string)[A]);
	template<size_t A>
	basic_static_string(const basic_static_string<TDATA, A>& _string);

	basic_static_string(const TDATA* _string);

public:
	// Common Standard 1) Status Function
	size_type				size() const noexcept						{ return m_size;}
	size_type				max_size() const noexcept					{ return TSIZE;}
	bool					empty() const noexcept						{ return m_size == 0;}
																		  
	// Common Standard 2) 												  
	iterator				begin() noexcept							{ return iterator(m_ptr_first);}
	const_iterator			begin() const noexcept						{ return const_iterator(m_ptr_first);}
	const_iterator			cbegin() const noexcept						{ return const_iterator(m_ptr_first);}
	iterator				end() noexcept								{ return iterator(m_ptr_first + m_size);}
	const_iterator			end() const noexcept						{ return const_iterator(m_ptr_first + m_size);}
	const_iterator			cend() const noexcept						{ return const_iterator(m_ptr_first + m_size);}
	reverse_iterator		rbegin() noexcept							{ return reverse_iterator(iterator(m_ptr_first + m_size - 1));}
	const_reverse_iterator	rbegin() const noexcept						{ return const_reverse_iterator(const_iterator(m_ptr_first + m_size - 1));}
	const_reverse_iterator	crbegin() const noexcept					{ return const_reverse_iterator(const_iterator(m_ptr_first + m_size - 1));}
	reverse_iterator		rend() noexcept								{ return reverse_iterator(iterator(m_ptr_first - 1));}
	const_reverse_iterator	rend() const noexcept						{ return const_reverse_iterator(const_iterator(m_ptr_first + m_size - 1));}
	const_reverse_iterator	crend() const noexcept						{ return const_reverse_iterator(const_iterator(m_ptr_first + m_size - 1));}

	// Common Standard 3) 
	void					swap(_mytype& _rhs) noexcept;

	// Common Standard 4) Operators
	_mytype&				operator=(const _mytype& _rhs) noexcept;
	_mytype&				operator=(_mytype&& _rhs) noexcept;
	// String) 
	_mytype&				operator=(const std::basic_string<TDATA>& _rhs);
	_mytype&				operator=(std::basic_string<TDATA>&& _rhs);
	_mytype&				operator=(const std::basic_string_view<TDATA>& _rhs);
	_mytype&				operator=(std::basic_string_view<TDATA>&& _rhs);
	_mytype&				operator=(const TDATA* _rhs);

	template <class A, size_t B>
	_mytype&				operator=(const basic_static_string<A,B>& _rhs);
	template <class A, size_t B>
	_mytype&				operator=(basic_static_string<A,B>&& _rhs);
	template<size_t A>
	_mytype&				operator=(const TDATA(&_rhs)[A]);

							operator std::basic_string_view<TDATA>() const noexcept { return std::basic_string_view<TDATA>(m_ptr_first, m_size);}
							//operator std::basic_string<TDATA>() const noexcept { return std::basic_string<TDATA>(m_ptr_first, m_size); }


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
	template<class TITERATOR>
	basic_static_string(TITERATOR _first, TITERATOR _last);

public:
	// Sequence Standard 1) insert member function
	template<class TITERATOR>
	void				insert(const_iterator _where, TITERATOR _first, TITERATOR _last);
	iterator			insert(const_iterator _where, const value_type& _val);
	iterator			insert(const_iterator _where, value_type&& _val);
	void				insert(const_iterator _where, size_type _count, const value_type& _val);

	// Sequence Standard 2) erase member function
	iterator			erase(const_iterator _where) noexcept;
	iterator			erase(const_iterator _first, const_iterator _last) noexcept;

	// Sequence Standard 3) clear
	void				clear() noexcept;


// ****************************************************************************
// basic_static_string Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const noexcept					{ return TSIZE;}
	size_type				remained() const noexcept					{ return TSIZE-size();}
																		  
	// 2) Data															  
	reference				front() noexcept							{ return *_get_ptr_first<value_type>();}
	const_reference			front() const noexcept						{ return *_get_ptr_first<value_type>();}
																		  
	reference				back() noexcept								{ return *(m_ptr_first + (m_size - 1) * sizeof(value_type));}
	const_reference			back() const noexcept						{ return *(m_ptr_first + (m_size - 1) * sizeof(value_type));}
																		  
	reference				at(size_type _pos);							  
	const_reference			at(size_type _pos) const;					  
																		  
	const TDATA*			c_str() const noexcept						{ return m_ptr_first;}
	std::basic_string_view<TDATA> to_string_view() const noexcept		{ return std::basic_string_view<TDATA>(m_ptr_first, m_size); }

	reference				operator [] (size_type _pos);
	const_reference			operator [] (size_type _pos) const;

	// 3) push/pop
	void					push_front(const value_type& _val);
	void					push_front(value_type&& _val);
	void					pop_front();
	void					push_back(const value_type& _val);
	void					push_back(value_type&& _val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	template <class ITERATOR>
	void					assign(ITERATOR _first, ITERATOR _last);
	void					assign(size_type _count, const value_type& _val);

	// 5) Resize
	void					resize(size_type _new_size);


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) Array
	size_type				m_size;
	value_type				m_ptr_first[TSIZE + 1];

public:
	auto					_get_size() const noexcept { return m_size;}
	void					_reset_size() noexcept { m_size = 0;}
	void					_reset_size(size_t _size);
	template<class T = char>											  
	const T*				_get_ptr_first() const noexcept { return m_ptr_first;}
	template<class T = char>											  
	T*						_get_ptr_first() noexcept { return m_ptr_first;}

private:
	void					_assign(const std::basic_string_view<TDATA> _string);


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	basic_static_string<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator() noexcept													{}
		explicit const_iterator(pointer _pnow) noexcept								{ m_ptr = _pnow;}
																					  
		// 2) ����																    
		const_iterator&		operator=(const const_iterator& _rhs) noexcept			{ m_ptr = _rhs.m_ptr; return *this;}
		pointer				operator->()											{ return &**this;}
																					  
		// 3) �ݺ�																    
		const_reference		operator*() const										{ return *m_ptr;}
		const_iterator&		operator++() noexcept									{ ++m_ptr; return *this;}
		const_iterator		operator++(int) noexcept								{ return const_iterator(m_ptr++);}
		const_iterator&		operator--() noexcept									{ --m_ptr; return *this;}
		const_iterator		operator--(int) noexcept								{ return const_iterator(m_ptr--);}
		const_iterator		operator+(difference_type _rhs) const noexcept			{ return const_iterator(m_ptr+_rhs);}
		void				operator+=(difference_type _rhs) noexcept				{ m_ptr +=_rhs;}
		const_iterator		operator-(difference_type _rhs) const noexcept			{ return const_iterator(m_ptr-_rhs);}
		void				operator-=(difference_type _rhs) noexcept				{ m_ptr -=_rhs;}
		size_type			operator-(const const_iterator& _rhs) const noexcept	{ return static_cast<size_type>(m_ptr-_rhs.m_ptr);}
		size_type			operator-(const iterator& _rhs) const noexcept			{ return static_cast<size_type>(m_ptr-_rhs.m_ptr);}
																					  
		// 4) ��																    
		bool				operator==(const const_iterator& _rhs) const noexcept	{ return m_ptr==_rhs.m_ptr;}
		bool				operator!=(const const_iterator& _rhs) const noexcept	{ return m_ptr!=_rhs.m_ptr;}
																					  
		bool				operator>(const const_iterator&  _rhs) const noexcept	{ return m_ptr>_rhs.m_ptr;}
		bool				operator>=(const const_iterator&  _rhs) noexcept		{ return m_ptr>=_rhs.m_ptr;}
		bool				operator<(const const_iterator&  _rhs) const noexcept	{ return m_ptr<_rhs.m_ptr;}
		bool				operator<=(const const_iterator&  _rhs) noexcept		{ return m_ptr<=_rhs.m_ptr;}
																					  
		bool				operator>(const iterator&  _rhs) const noexcept			{ return m_ptr>_rhs.m_ptr;}
		bool				operator>=(const iterator&  _rhs) noexcept				{ return m_ptr>=_rhs.m_ptr;}
		bool				operator<(const iterator&  _rhs) const noexcept			{ return m_ptr<_rhs.m_ptr;}
		bool				operator<=(const iterator&  _rhs) noexcept				{ return m_ptr<=_rhs.m_ptr;}

	private:
		pointer				m_ptr;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	basic_static_string<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator() noexcept															{}
		explicit iterator(pointer _pnow) noexcept									{ m_ptr = _pnow;}
																					  
		// 2) ����																    
		iterator&			operator=(const iterator& _rhs) noexcept				{ m_ptr = _rhs.m_ptr; return *this;}
		iterator&			operator=(const const_iterator& _rhs) noexcept			{ m_ptr = _rhs.m_ptr; return *this;}
		pointer				operator->()											{ return &**this;}
							operator const_iterator() noexcept						{ return const_iterator(m_ptr);}
																					  
		// 3) �ݺ�																    
		reference			operator*() const										{ return *m_ptr;}
		iterator&			operator++() noexcept									{ ++m_ptr; return *this;}
		iterator			operator++(int) noexcept								{ return iterator(m_ptr++);}
		iterator&			operator--() noexcept									{ --m_ptr; return *this;}
		iterator			operator--(int) noexcept								{ return iterator(m_ptr--);}
		iterator			operator+(difference_type _rhs) const noexcept			{ return iterator(m_ptr+_rhs);}
		void				operator+=(difference_type _rhs) noexcept				{ m_ptr +=_rhs;}
		iterator			operator-(difference_type _rhs) const noexcept			{ return iterator(m_ptr-_rhs);}
		void				operator-=(difference_type _rhs) noexcept				{ m_ptr -=_rhs;}
		size_type			operator-(const const_iterator& _rhs) const noexcept	{ return static_cast<size_type>(m_ptr-_rhs.m_ptr);}
		size_type			operator-(const iterator& _rhs) const noexcept			{ return static_cast<size_type>(m_ptr-_rhs.m_ptr);}
																					  
		// 4) ��																    
		bool				operator==(const iterator& _rhs) const noexcept			{ return m_ptr==_rhs.m_ptr;}
		bool				operator!=(const iterator& _rhs) const noexcept			{ return m_ptr!=_rhs.m_ptr;}
																					  
		bool				operator==(const const_iterator& _rhs) const noexcept	{ return m_ptr==_rhs.m_ptr;}
		bool				operator!=(const const_iterator& _rhs) const noexcept	{ return m_ptr!=_rhs.m_ptr;}
																					  
		bool				operator>(const const_iterator&  _rhs) const noexcept	{ return m_ptr>_rhs.m_ptr;}
		bool				operator>=(const const_iterator&  _rhs) noexcept		{ return m_ptr>=_rhs.m_ptr;}
		bool				operator<(const const_iterator&  _rhs) const noexcept	{ return m_ptr<_rhs.m_ptr;}
		bool				operator<=(const const_iterator&  _rhs)					{ return m_ptr<=_rhs.m_ptr;}
																					  
		bool				operator>(const iterator&  _rhs) const noexcept			{ return m_ptr>_rhs.m_ptr;}
		bool				operator>=(const iterator&  _rhs) noexcept				{ return m_ptr>=_rhs.m_ptr;}
		bool				operator<(const iterator&  _rhs) const noexcept			{ return m_ptr<_rhs.m_ptr;}
		bool				operator<=(const iterator&  _rhs) noexcept				{ return m_ptr<=_rhs.m_ptr;}

	private:
		pointer				m_ptr;
	};
};

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::_assign(const std::basic_string_view<TDATA> _string)
{
	// check)
	CGDASSERT_ERROR(_string.size() <= TSIZE);

	// check)
	CGD_THROW_IF(_string.size() > TSIZE, std::overflow_error("CGDK exception:: string is too long"))

	// 1) clear all
	clear();

	// 2) get string length
	auto length = (_string.size() < TSIZE) ? _string.size() : TSIZE;

	// 3) copy string
	memcpy(m_ptr_first, _string.data(), length * sizeof(TDATA));

	// 4) set null
	*(m_ptr_first + length) = 0;

	// 5) set length
	m_size = static_cast<size_type>(length);
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string() noexcept : m_size(0), m_ptr_first{}
{
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(const _mytype& _copy) noexcept : m_size(0), m_ptr_first{}
{
	_assign(std::basic_string_view<TDATA>(_copy.c_str(), _copy.size()));
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(_mytype&& _move) noexcept :	m_size(0), m_ptr_first{}
{
	// 1) assign
	_assign(std::basic_string_view<TDATA>(_move.c_str(), _move.size()));

	// 2) clear source
	_move.clear();
}

template <class TDATA, size_t TSIZE>
template<class TITERATOR>
basic_static_string<TDATA, TSIZE>::basic_static_string(TITERATOR _first, TITERATOR _last) : m_size(0), m_ptr_first{}
{
	try
	{
		// 1) �����سִ´�.
		insert(begin(), _first, _last);
	}
	catch(...)
	{
		// - ��� �����.
		clear();

		// reraise)
		throw;
	}
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(const std::basic_string_view<TDATA>& _string) : m_size(0), m_ptr_first{}
{
	_assign(_string);
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(std::basic_string_view<TDATA>&& _string) :	m_size(0), m_ptr_first{}
{
	// 1) assign
	_assign(_string);

	// 2) clear source
	_string = std::basic_string_view<TDATA>();
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(const std::basic_string<TDATA>& _string) : m_size(0), m_ptr_first{}
{
	_assign(std::basic_string_view<TDATA>(_string));
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(std::basic_string<TDATA>&& _string) : m_size(0), m_ptr_first{}
{
	// 1) assign
	_assign(_string);

	// 2) clear source
	_string = std::basic_string_view<TDATA>();
}

template <class TDATA, size_t TSIZE>
template <size_t A>
basic_static_string<TDATA, TSIZE>::basic_static_string(const basic_static_string<TDATA,A>& _string) : m_size(0), m_ptr_first{}
{
	_assign(std::basic_string_view<TDATA>(_string.c_str(), _string.size()));
}


template <class TDATA, size_t TSIZE>
template<size_t A>
basic_static_string<TDATA, TSIZE>::basic_static_string(const TDATA(&_string)[A]) :	m_size(0), m_ptr_first{}
{
	// check)
	static_assert(A != 0, "string is zero");

	// check) 
	static_assert(A <= (TSIZE + 1), "string is too long");

	// 1) clear all
	clear();

	// 2) Preparing move
	auto iter_src = _string;
	auto iter_src_end = _string + (((A - 1) > TSIZE) ? TSIZE : (A - 1));
	auto iter_dst = m_ptr_first;

	// 3) copy string
	for (; iter_src < iter_src_end && *iter_src != 0; ++iter_src, ++iter_dst)
	{
		*iter_dst = *iter_src;
	}

	// 4) add NULL
	*iter_dst = 0;

	// 5) Copy size value
	m_size = static_cast<size_type>(iter_src - _string);
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::basic_static_string(const TDATA* _string) : m_size(0), m_ptr_first{}
{
	if (_string != nullptr)
	{
		// 1) Preparing move
		auto iter_src = _string;
		auto iter_dst = m_ptr_first;
		auto iter_dst_end = iter_dst + TSIZE;

		// 2) copy string
		for (; iter_dst < iter_dst_end && *iter_src != 0; ++iter_src, ++iter_dst)
		{
			*iter_dst = *iter_src;
		}

		// 3) add NULL
		*iter_dst = 0;

		// 4) Copy size value
		m_size = static_cast<size_type>(iter_src - _string);
	}
}

template <class TDATA, size_t TSIZE>
basic_static_string<TDATA, TSIZE>::~basic_static_string() noexcept
{
	// 1) ��� �����.
	clear();
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::_reset_size(size_t _size)
{
	// check) 
	CGDASSERT_ERROR(_size <= TSIZE)

	// check)
	CGD_THROW_IF(_size > TSIZE, std::overflow_error("CGDK exception:: string is too long"))

	// 1) set length
	m_size = static_cast<size_type>(_size);
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const _mytype& _rhs) noexcept
{
	// 1) assign
	_assign(std::basic_string_view<TDATA>(_rhs.c_str(), _rhs.size()));

	// return)
	return	*this;
}

template <class TDATA, size_t TSIZE>
template <class A, size_t B>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const basic_static_string<A,B>& _rhs)
{
	// check) 
	CGDASSERT_ERROR(_rhs.size() <= (TSIZE + 1))

	// check)
	CGD_THROW_IF(_rhs.size() > (TSIZE+1), std::overflow_error("CGDK exception:: _rhs size is too big."))

	// 1) clear all
	clear();

	// 2) Preparing move
	auto iter_src = _rhs.template _get_ptr_first<value_type>();
	auto iter_src_end = _rhs.template _get_ptr_first<value_type>()+_rhs._get_size();
	auto iter_dst = m_ptr_first;

	// 3) move all by move-constructor
	for(; iter_src != iter_src_end; ++iter_src, ++iter_dst)
	{
	#pragma push_macro("new")
	#undef new
		new (iter_dst) value_type(*iter_src);
	#pragma pop_macro("new")
	}

	// 4) add NULL
	*iter_dst = 0;

	// 5) Copy size value
	m_size = static_cast<size_type>(_rhs._get_size());

	// return)
	return *this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(_mytype&& _rhs) noexcept
{
	// 1) assign
	_assign(std::basic_string_view<TDATA>(_rhs.c_str(), _rhs.size()));

	// 2) clear r-value container
	_rhs._reset_size();

	// return) 
	return *this;
}

template <class TDATA, size_t TSIZE>
template <class A, size_t B>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(basic_static_string<A,B>&& _rhs)
{
	// check) 
	CGDASSERT_ERROR(_rhs.size() <= TSIZE)

	// check)
	CGD_THROW_IF(_rhs.size() > TSIZE, std::overflow_error("CGDK exception:: _rhs size is too big."))

	// 1) clear all
	clear();

	// 2) Preparing move
	auto iter_src = _rhs.template _get_ptr_first<value_type>();
	auto iter_src_end = _rhs.template _get_ptr_first<const value_type>()+_rhs._get_size();
	auto iter_dst = m_ptr_first;

	// 3) move all by move-constructor
	for(; iter_src != iter_src_end; ++iter_src, ++iter_dst)
	{
#pragma push_macro("new")
#undef new
		new (iter_dst) value_type(std::move(*iter_src));
#pragma pop_macro("new")
	}

	// 4) add NULL
	*iter_dst = 0;

	// 5) Copy size value
	m_size = static_cast<size_type>(_rhs._get_size());

	// 6) clear r-value container
	_rhs._reset_size();

	// return) 
	return	*this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const std::basic_string_view<TDATA>& _rhs)
{
	// 1) assign
	_assign(_rhs);

	// return) 
	return *this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(std::basic_string_view<TDATA>&& _rhs)
{
	// 1) assign
	_assign(_rhs);

	// 2) clear source
	_rhs = std::basic_string_view<TDATA>();

	// return) 
	return *this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const std::basic_string<TDATA>& _rhs)
{
	// 1) assign
	_assign(_rhs);

	// return) 
	return	*this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(std::basic_string<TDATA>&& _rhs)
{
	// 1) assign
	_assign(_rhs);

	// 2) clear source
	_rhs.clear();

	// return) 
	return	*this;
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const TDATA* _rhs)
{
	// 1) clear all
	clear();

	if (_rhs != nullptr)
	{
		// 2) Preparing move
		auto iter_src = _rhs;
		auto iter_dst = m_ptr_first;
		auto iter_dst_end = iter_dst + TSIZE;

		// 3) copy string
		for (; iter_dst < iter_dst_end && *iter_src != 0; ++iter_src, ++iter_dst)
		{
			*iter_dst = *iter_src;
		}

		// 4) add NULL
		*iter_dst = 0;

		// 5) Copy size value
		m_size = static_cast<size_type>(iter_src - _rhs);
	}

	// return) 
	return *this;
}

template <class TDATA, size_t TSIZE>
template<size_t A>
typename basic_static_string<TDATA, TSIZE>::_mytype& basic_static_string<TDATA, TSIZE>::operator=(const TDATA(&_rhs)[A])
{
	// check)
	static_assert(A != 0, "string is zero");

	// check)
	static_assert(A <= (TSIZE + 1), "string is too long");

	// 1) clear all
	clear();

	// 2) Preparing move
	auto iter_src = _rhs;
	const auto	iter_src_end = _rhs + (((A-1) > TSIZE) ? TSIZE : (A-1));
	auto iter_dst = m_ptr_first;

	// 3) copy string
	for( ; iter_src < iter_src_end && *iter_src!=0; ++iter_src, ++iter_dst)
	{
		*iter_dst = *iter_src;
	}

	// 4) add NULL
	*iter_dst = 0;

	// 5) Copy size value
	m_size = static_cast<size_type>(iter_src - _rhs);

	// return) 
	return *this;
}

// ���Լ���
template <class TDATA, size_t TSIZE>
bool operator == (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = _lhs.begin();
	auto iter_dst = _rhs.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == _lhs.end())
			return (iter_dst == _rhs.end());

		// check) Dst�� ���ΰ�?
		if(iter_dst == _rhs.end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� false����!
		if(*iter_src != *iter_dst)
			return false;

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}
template <class TDATA, size_t TSIZE>
bool operator >  (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = _lhs.begin();
	auto iter_dst = _rhs.begin();

	for (;;)
	{
		// check) Src�� ���ΰ�???
		if (iter_src == _lhs.end())
			return false;

		// check) Dst�� ���ΰ�?
		if (iter_dst == _rhs.end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if (*iter_src != *iter_dst)
			return (*iter_src > * iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}
template <class TDATA, size_t TSIZE>
bool operator <  (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	auto iter_src = _lhs.begin();
	auto iter_dst = _rhs.begin();

	for (;;)
	{
		// check) Dst�� ���ΰ�?
		if (iter_dst == _rhs.end())
			return false;

		// check) Src�� ���ΰ�???
		if (iter_src == _lhs.end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if (*iter_src != *iter_dst)
			return (*iter_src < *iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}
template <class TDATA, size_t TSIZE>
bool operator != (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	return !(_lhs == _rhs);
}
template <class TDATA, size_t TSIZE>
bool operator >= (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	return !(_lhs < _rhs);
}
template <class TDATA, size_t TSIZE>
bool operator <= (const basic_static_string<TDATA, TSIZE>& _lhs, const std::basic_string_view<TDATA>& _rhs) noexcept
{
	return !(_lhs > _rhs);
}

template <class TDATA, size_t TSIZE>
bool operator == (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>&  _rhs) noexcept
{
	return _rhs == _lhs;
}
template <class TDATA, size_t TSIZE>
bool operator >  (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>& _rhs) noexcept
{
	return _rhs < _lhs;
}
template <class TDATA, size_t TSIZE>
bool operator <  (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>& _rhs) noexcept
{
	return _rhs > _lhs;
}
template <class TDATA, size_t TSIZE>
bool operator != (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>& _rhs) noexcept
{
	return _rhs != _lhs;
}
template <class TDATA, size_t TSIZE>
bool operator >= (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>& _rhs) noexcept
{
	return _rhs <= _lhs;
}
template <class TDATA, size_t TSIZE>
bool operator <= (const std::basic_string_view<TDATA>& _lhs, const basic_static_string<TDATA, TSIZE>& _rhs) noexcept
{
	return _rhs >= _lhs;
}

template <class TDATA, size_t TSIZE>
TDATA& basic_static_string<TDATA, TSIZE>::at(size_type _pos)
{
	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos<0 || _pos>=size(), std::out_of_range("CGDK exception:: Out of range."))

	// 1) ���� �о �ǵ�����.
	return *(((value_type*)m_ptr_first) + _pos);
}

template <class TDATA, size_t TSIZE>
const TDATA& basic_static_string<TDATA, TSIZE>::at(size_type _pos) const
{
	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos<0 || _pos>=size(), std::out_of_range("CGDK exception:: out of range."))

	// 1) ���� �о �ǵ�����.
	return *(((value_type*)m_ptr_first) + _pos);
}

template <class TDATA, size_t TSIZE>
TDATA& basic_static_string<TDATA, TSIZE>::operator [] (size_type _pos)
{
	return at(_pos);
}

template <class TDATA, size_t TSIZE>
const TDATA& basic_static_string<TDATA, TSIZE>::operator [] (size_type _pos) const
{
	return at(_pos);
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::resize(size_type _new_size)
{
	// check) TSIZE���� ���� ũ�⿩������ �ȴ�.
	CGD_THROW_IF(_new_size > TSIZE, std::length_error("CGDK exception:: Invalid Size."));

	// 1) 
	auto iter = end();
	auto newEnd( begin() + _new_size);

	try
	{
		// 2) �þ �κб��� Reset�� �Ѵ�.
		for(; iter < newEnd; ++iter)
		{
		#pragma push_macro("new")
		#undef new
			new (&(*iter)) value_type();
		#pragma pop_macro("new")
		}

		// 3) �پ���???(������)
	}
	catch(...)
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(auto iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*iterRoll).~value_type();
		}

		// reraise) 
		throw;
	}

	// 2) Size�� ���� �����Ѵ�.
	m_size = static_cast<size_type>(newEnd.m_ptr - ((value_type*)m_ptr_first));
}


template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::clear() noexcept
{
	// 1) ��� Item�� Destructor�� ȣ���Ѵ�.
	*m_ptr_first = 0;

	// 2) Last�� First�� ����� 0�� �����.
	m_size = 0;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::push_front(const TDATA& _val)
{
	// CASE-A) if container is empty, just push_back
	if(m_size == 0)
	{
		// - Push Back
		push_back(_val);

		// return) 
		return;
	}

	// 1) get size
	auto ptrFirst = m_ptr_first;
	auto _iter = ((value_type*)m_ptr_first) + m_size;
	auto iSize = _iter - (value_type*)ptrFirst;

	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize == TSIZE, std::length_error("CGDK exception:: It's Full!"));

	// 3) shift back last one by copy-constructing
#pragma push_macro("new")
#undef new
	new (_iter) value_type(std::move(*(_iter-1)));
#pragma pop_macro("new")

	// 4) Others do Moving
	for(--_iter; _iter>(value_type*)ptrFirst; --_iter)
	{
		*_iter = std::move(*(_iter-1));
	}

	// 5) Assignment _val in front
	*(value_type*)ptrFirst = _val;

	// 6) Increase Size
	++m_size;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::push_front(value_type&& _val)
{
	// CASE-A) if container is empty, just push_back
	if(m_size == 0)
	{
		// - Push Back
		push_back(std::move(_val));

		// return) 
		return;
	}

	// 1) get size
	auto _iter = _get_ptr_first<value_type>()+m_size;
	auto iSize = _iter - _get_ptr_first<value_type>();

	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize==TSIZE, std::length_error("CGDK exception:: It's Full!"));

	// 3) shift back last one by copy-constructing
#pragma push_macro("new")
#undef new
	new (_iter) value_type(std::move(*(_iter-1)));
#pragma pop_macro("new")

	// 4) Others do Moving
	for(--_iter; _iter>_get_ptr_first<value_type>(); --_iter)
	{
		*_iter = std::move(*(_iter-1));
	}

	// 5) Assignment _val in front
	*_get_ptr_first<value_type>() = std::move(_val);

	// 6) Increase Size
	++m_size;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::pop_front()
{
	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(m_size == 0, std::length_error("CGDK exception:: It's Full!"));

	// 2) Decrease Size
	--m_size;

	// 3) Destroy First
	_get_ptr_first<value_type>()->~value_type();

	// declare)
	const value_type* ptr_last = _get_ptr_first<const value_type>() + m_size;

	// 4) Moveing...
	for(value_type* _iter=_get_ptr_first<value_type>(); _iter<ptr_last; ++_iter)
	{
		*_iter = std::move(*(_iter+1));
	}
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::push_back(const TDATA& _val)
{
	// check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (m_ptr_first + sizeof(value_type) * m_size) value_type(_val);
#pragma pop_macro("new")
	
	// 2) Last ������ ������Ŵ
	++m_size;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::push_back(TDATA&& _val)
{
	// check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (m_ptr_first + sizeof(value_type) * m_size) value_type(std::move(_val));
#pragma pop_macro("new")

	// 2) Last ������ ������Ŵ
	++m_size;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::push_back()
{
	// check) 
	CGDASSERT_ERROR(size()!=max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (m_ptr_first + sizeof(value_type) * m_size) value_type();
#pragma pop_macro("new")
	
	// 2) Last ������ ������Ŵ
	++m_size;
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::pop_back()
{
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	CGD_RETURN_IF(empty());
	#endif

	// 1) ũ�⸦ ���δ�.
	--m_size;

	// 2) Destructor�� ȣ���Ѵ�.
	(_get_ptr_first<value_type>() + m_size)->~value_type();
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::assign(size_type _count, const value_type& _val)
{
	// check) 
	CGD_THROW_IF(remained()<_count, std::length_error("CGDK exception:: Invalid Size."));

	// 1) ������� First�� Last�� ����Ű�� Iterator
	auto* first = _get_ptr_first<value_type>() + m_size;

	// 2) End�� ���Ѵ�.
	auto* newEnd = first+_count;

	try
	{
		// 3) ���� �ִ´�.
		for(; first != newEnd; ++first)
		{
		#pragma push_macro("new")
		#undef new
			new (first) value_type(_val);
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		const value_type* ptr_last = _get_ptr_first<value_type>() + m_size;

		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(value_type* pRoll=ptr_last; pRoll!=first; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~value_type();
		}

		// reraise) 
		throw;
	}

	// 4) �Ϸ������� m_size�� ���� �����Ѵ�.
	m_size = static_cast<size_type>(newEnd - ((value_type*)m_ptr_first));
}

template <class TDATA, size_t TSIZE>
template <typename ITERATOR>
void basic_static_string<TDATA, TSIZE>::assign(ITERATOR _first, ITERATOR _last)
{
	// 1) ������� First�� Last�� ����Ű�� Iterator
	auto* ptrNow = _get_ptr_first<value_type>() + m_size;

	try
	{
		// 2) ���� �ִ´�.
		for(; _first != _last; ++_first, ++ptrNow)
		{
			// check) Remained�� 0�̸� �ȉ´�.
			CGD_THROW_IF(remained()!=0, std::length_error("CGDK exception:: Invalid Size."));

		#pragma push_macro("new")
		#undef new
			new (ptrNow) value_type(*_first);
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(value_type* pRoll= _get_ptr_first<value_type>() + m_size; pRoll != ptrNow; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~value_type();
		}

		// reraise) 
		throw;
	}

	// 3) �Ϸ������� size�� ���� �����Ѵ�.
	m_size = static_cast<size_type>(ptrNow - (value_type*)m_ptr_first);
}

template <class TDATA, size_t TSIZE>
template<typename TITERATOR>
void basic_static_string<TDATA, TSIZE>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr <= (_get_ptr_first<value_type>() + m_size));

	// 1) Insert Count�� ��´�.
	auto Insertcount = _last-_first;

	// 2) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<Insertcount, std::length_error("CGDK exception:: Full!"));

	// 3) source pointer and destination pointer for moving
	auto* iter_src = _get_ptr_first<value_type>() + m_size;
	auto* _IterEnd = iter_src;
	auto* iter_dst = iter_src +Insertcount;

	// 4) shift back data by move-constructing
	while(iter_dst !=_IterEnd && iter_src>_where.m_ptr)
	{
		--iter_src;
		--iter_dst;

	#pragma push_macro("new")
	#undef new
		new (iter_dst) value_type(std::move(*iter_src));
	#pragma pop_macro("new")
	}

	// 5) shift back others by moving
	while(iter_src>_where.m_ptr)
	{
		--iter_src;
		--iter_dst;

		*iter_dst = std::move(*iter_src);
	}

	try
	{
		// 6) copy data to _where
		for(; _first!=_last; ++_first, ++iter_src)
		{
			// - Construct�� ȣ���Ѵ�.
		#pragma push_macro("new")
		#undef new
			new (iter_src) value_type(*const_cast<value_type*>(_first.m_ptr));
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		auto* _iter_rb_end = _get_ptr_first<value_type>()+m_size;
		auto* _iter_rb_dst = const_cast<value_type*>(_where.m_ptr);
		auto* _iter_rb_src = _iter_rb_dst+Insertcount;

		// - shift front 
		while(_iter_rb_dst!=_iter_rb_end)
		{
			*_iter_rb_dst = std::move(*_iter_rb_src);
		}

		// - destroy remained
		while(_iter_rb_dst<iter_src)
		{
			_iter_rb_dst->~value_type();
		}

		// reraise) 
		throw;
	}

	// 5) size�� ������Ų��.
	m_size += static_cast<size_type>(Insertcount);
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::insert(const_iterator _where, size_type _count, const value_type& _val)
{
	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr <= (_get_ptr_first<value_type>() + m_size));

	// check) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<_count, std::length_error("CGDK exception:: Out of room."));

	// 1) source pointer and destination pointer for moving
	auto* iter_src = _get_ptr_first<value_type>() + m_size;
	auto* _IterEnd = iter_src;
	auto* iter_dst = iter_src +_count;

	// 2) shift back data by move-constructing
	while(iter_dst != _IterEnd && iter_src>_where.m_ptr)
	{
		--iter_src;
		--iter_dst;

	#pragma push_macro("new")
	#undef new
		new (iter_dst) value_type(std::move(*iter_src));
	#pragma pop_macro("new")
	}

	// 3) shift back others by moving
	while(iter_src>_where.m_ptr)
	{
		--iter_src;
		--iter_dst;

		*iter_dst	 = std::move(*iter_src);
	}

	try
	{
		// 4) copy data to _where
		for(; iter_src != iter_dst; ++iter_src)
		{
			// - Construct�� ȣ���Ѵ�.
		#pragma push_macro("new")
		#undef new
			new (iter_src) value_type(_val);
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		auto* _iter_rb_end = _get_ptr_first<value_type>()+m_size;
		auto* _iter_rb_dst = const_cast<value_type*>(_where.m_ptr);
		auto* _iter_rb_src = _iter_rb_dst+_count;

		// - shift front 
		while(_iter_rb_dst!=_iter_rb_end)
		{
			*_iter_rb_dst = std::move(*_iter_rb_src);
		}

		// - destroy remained
		while(_iter_rb_dst<iter_src)
		{
			_iter_rb_dst->~value_type();
		}

		// Throw) �ٽ� Thread!!!
		throw;
	}

	// 2) size�� ������Ų��.
	m_size += static_cast<size_type>(_count);
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::iterator basic_static_string<TDATA, TSIZE>::insert(const_iterator _where, const value_type& _val)
{
	// ����) CGDK::basic_static_string���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr <= (_get_ptr_first<value_type>() + m_size));

	// check) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(remained()<=0, std::length_error("CGDK exception:: Full!"));

	auto* ptr_last = _get_ptr_first<value_type>() + m_size;
	
	if(_where.m_ptr!=ptr_last)
	{
		// 1) set iterator
		auto* _iter = ptr_last;

		// 2) move constructing last one
	#pragma push_macro("new")
	#undef new
		new (_iter) value_type(std::move(*(_iter-1)));
	#pragma pop_macro("new")

		// 3) Shift back others by Moving
		for(--_iter;_iter!=_where.m_ptr;--_iter)
		{
			*_iter = std::move(*(_iter-1));
		}
	}

	try
	{
		// 2) ��� �ڸ��� Constructor�� ȣ���� ���� �����Ѵ�.
	#pragma push_macro("new")
	#undef new
		new (_where.m_ptr) value_type(_val);
	#pragma pop_macro("new")
	}
	catch(...)
	{
		auto* ptr_last = _get_ptr_first<value_type>() + m_size;

		// - shift front 
		for(auto* _iter=const_cast<value_type*>(_where.m_ptr);_iter!=ptr_last;++_iter)
		{
			*_iter = std::move(*(_iter+1));
		}

		// Throw) Reraise
		throw;
	}

	// 3) size�� ������Ų��.
	++m_size;

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::iterator basic_static_string<TDATA, TSIZE>::insert(const_iterator _where, value_type&& _val)
{
	// ����) CGDK::basic_static_string���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr <= (_get_ptr_first<value_type>() + m_size));

	// check) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(remained() <= 0, std::length_error("CGDK exception:: Full!"));

	auto* ptr_last = _get_ptr_first<value_type>() + m_size;
	
	if(_where.m_ptr!=ptr_last)
	{
		// 1) set iterator
		auto* _iter = ptr_last;

		// 2) move constructing last one
	#pragma push_macro("new")
	#undef new
		new (_iter) value_type(std::move(*(_iter-1)));
	#pragma pop_macro("new")

		// 3) Shift back others by Moving
		for(--_iter;_iter!=_where.m_ptr;--_iter)
		{
			*_iter = std::move(*(_iter-1));
		}
	}

	try
	{
		// 2) ��� �ڸ��� Constructor�� ȣ���� ���� �����Ѵ�.
	#pragma push_macro("new")
	#undef new
		new (_where.m_ptr) value_type(std::move(_val));
	#pragma pop_macro("new")
	}
	catch(...)
	{
		auto* ptr_last = _get_ptr_first<value_type>() + m_size;

		// - shift front 
		for(auto* _iter=const_cast<value_type*>(_where.m_ptr);_iter!=ptr_last;++_iter)
		{
			*_iter	 = std::move(*(_iter+1));
		}

		// Throw) Reraise
		throw;
	}

	// 3) size�� ������Ų��.
	++m_size;

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::iterator  basic_static_string<TDATA, TSIZE>::erase(const_iterator _where) noexcept
{
	// Attention) There is no checking of max_size() in CGDK::basic_static_string

	// check) Iterator is invalid (is within m_size)
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr<(_get_ptr_first<value_type>() + m_size));

	// check) Is empty?
	CGDASSERT_ERROR(size() > 0);

	// 1) Call destructor on _where
	(_where.m_ptr)->~value_type();

	// 2) Decrease size
	--m_size;

	// declare)
	auto* const ptr_last = _get_ptr_first<value_type>() + m_size;

	// 3) Moveing forward after _where
	if(_where.m_ptr!=ptr_last)
	{
		// - move-constructing 
	#pragma push_macro("new")
	#undef new
		new (const_cast<value_type*>(_where.m_ptr)) value_type(std::move(*const_cast<value_type*>(_where.m_ptr+1)));
	#pragma pop_macro("new")

		for(++_where.m_ptr; _where.m_ptr<ptr_last; ++_where)
		{
			*const_cast<value_type*>(_where.m_ptr)	 = std::move(*const_cast<value_type*>(_where.m_ptr+1));
		}
	}

	// return)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <class TDATA, size_t TSIZE>
typename basic_static_string<TDATA, TSIZE>::iterator basic_static_string<TDATA, TSIZE>::erase(const_iterator _first, const_iterator _last) noexcept
{
	// ����) CGDK::basic_static_string���� max_size()�˻�� �������� �ʽ��ϴ�.

	auto* ptr_last = _get_ptr_first<value_type>() + m_size;

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_first.m_ptr>= _get_ptr_first<value_type>() && _first.m_ptr<=ptr_last);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_last.m_ptr>= _get_ptr_first<value_type>() && _last.m_ptr<=ptr_last);

	// 1) First�� Last�� ���ٸ� �׳� �ǵ���.
	auto item_count = _last-_first;

	// check) ItemCount�� 0�̸� �׳� ������.
	CGD_RETURN_IF(item_count==0, iterator(const_cast<value_type*>(_last.m_ptr)));

	// 2) Destroying 
	for(auto iter=_first; iter!=_last; ++iter)
	{
		(*iter).~value_type();
	}

	// 3) move Data to _first
	for(; _last.m_ptr<ptr_last; ++_last.m_ptr, ++_first.m_ptr)
	{
		// - move construction
	#pragma push_macro("new")
	#undef new
		new (const_cast<value_type*>(_first.m_ptr)) value_type(std::move(*const_cast<value_type*>(_last.m_ptr)));
	#pragma pop_macro("new")
	}

	// 4) Size�� ���δ�.
	m_size -= static_cast<size_type>(item_count);

	// return)
	return iterator(const_cast<value_type*>(_last.m_ptr));
}

template <class TDATA, size_t TSIZE>
void basic_static_string<TDATA, TSIZE>::swap(_mytype& _rhs) noexcept
{
	// check) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_rhs);

	// 1) ������ ��ä�� �ٲ۴�.(Allocator�� ����ġ �ʴ´�. ���� ����...)
	CGD_SWAP(*this, _rhs);
}

template<size_t I> using static_string	  = basic_static_string<char, I>;
template<size_t I> using static_wstring	  = basic_static_string<wchar_t, I>;
template<size_t I> using static_u8string  = basic_static_string<char8_t, I>;
template<size_t I> using static_u16string = basic_static_string<char16_t, I>;
template<size_t I> using static_u32string = basic_static_string<char32_t, I>;



}