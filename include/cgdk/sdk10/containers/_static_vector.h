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

template <typename TDATA, size_t TSIZE>
class static_vector
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
	typedef	static_vector<TDATA, TSIZE>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, size_t TOTHER_SIZE>
	struct rebind
	{
		typedef static_vector<TOTHER_DATA, TOTHER_SIZE> other;
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
	static_vector() noexcept;
	static_vector(const _mytype& _right);
	static_vector(_mytype&& _right) noexcept;
	~static_vector();

public:
	// Common Standard 1) Status Function
	size_type				size() const noexcept		{ return m_size;}
	size_type				max_size() const noexcept	{ return TSIZE;}
	bool					empty() const noexcept		{ return m_size==0;}
														  
	// Common Standard 2) 								  
	iterator				begin() noexcept			{ return iterator(reinterpret_cast<TDATA*>(m_ptr_first));}
	const_iterator			begin() const noexcept		{ return const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first));}
	const_iterator			cbegin() const noexcept		{ return const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first));}
	iterator				end() noexcept				{ return iterator(reinterpret_cast<TDATA*>(m_ptr_first)+m_size);}
	const_iterator			end() const noexcept		{ return const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size);}
	const_iterator			cend() const noexcept		{ return const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size);}
	reverse_iterator		rbegin() noexcept			{ return reverse_iterator(iterator(reinterpret_cast<TDATA*>(m_ptr_first)+m_size-1));}
	const_reverse_iterator	rbegin() const noexcept		{ return const_reverse_iterator(const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size-1));}
	const_reverse_iterator	crbegin() const noexcept	{ return const_reverse_iterator(const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size-1));}
	reverse_iterator		rend() noexcept				{ return reverse_iterator(iterator(reinterpret_cast<TDATA*>(m_ptr_first)-1));}
	const_reverse_iterator	rend() const noexcept		{ return const_reverse_iterator(const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size-1));}
	const_reverse_iterator	crend() const noexcept		{ return const_reverse_iterator(const_iterator(reinterpret_cast<const TDATA*>(m_ptr_first)+m_size-1));}

	// Common Standard 3) 
	void					swap(_mytype& _right) noexcept;

	// Common Standard 5) Operators
	bool					operator==(const _mytype& _right) const noexcept;
	bool					operator!=(const _mytype& _right) const noexcept;
	bool					operator<(const _mytype& _right) const noexcept;
	bool					operator>(const _mytype& _right) const noexcept;
	bool					operator<=(const _mytype& _right) const noexcept;
	bool					operator>=(const _mytype& _right) const noexcept;
	_mytype&				operator=(const _mytype& _right) noexcept;
	template <typename A, size_t B>
	_mytype&				operator=(const static_vector<A,B>& _right);
	_mytype&				operator=(_mytype&& _right) noexcept;
	template <typename A, size_t B>
	_mytype&				operator=(static_vector<A,B>&& _right);


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
	static_vector(size_type _count);
	static_vector(size_type _count, const value_type& _val);
	template<typename TITERATOR>
	static_vector(TITERATOR _first, TITERATOR _last);

public:
	// Sequence Standard 1) insert member function
	template<typename TITERATOR>
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
// static_vector Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const noexcept { return TSIZE;}
	size_type				remained() const noexcept { return TSIZE-size();}
														  
	// 2) Data											  
	reference				front() noexcept { return *_get_ptr_first<value_type>();}
	const_reference			front() const noexcept { return *_get_ptr_first<value_type>();}
														  
	reference				back() noexcept { return *reinterpret_cast<value_type*>(m_ptr_first+(m_size-1)*sizeof(value_type));}
	const_reference			back() const noexcept { return *reinterpret_cast<value_type*>(m_ptr_first+(m_size-1)*sizeof(value_type));}

	reference				at(size_type _pos);
	const_reference			at(size_type _pos) const;

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
	template <typename ITERATOR>
	void					assign(ITERATOR _first, ITERATOR _last);
	void					assign(size_type _count, const value_type& _val);

	// 5) Resize
	void					resize(size_type _Newsize);


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
private:
	// 1) Array
	size_t					m_size;
	char					m_ptr_first[sizeof(value_type)*TSIZE];			// Array�� ó�� ��ġ...

public:
	size_t				_get_size() const noexcept { return m_size;}
	void					_reset_size() noexcept { m_size=0;}
	template<class T = char>								  
	const T*				_get_ptr_first() const noexcept	{ return reinterpret_cast<const T*>(m_ptr_first);}
	template<class T = char>								  
	T*						_get_ptr_first() noexcept { return reinterpret_cast<T*>(m_ptr_first);}


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	static_vector<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator() noexcept {}
		explicit const_iterator(pointer _pNow) noexcept { m_ptr=_pNow;}
																					  
		// 2) ����																    
		const_iterator&		operator=(const const_iterator& _right) noexcept { m_ptr=_right.m_ptr; return *this;}
		pointer				operator->() { return &**this;}
																					  
		// 3) �ݺ�																    
		const_reference		operator*() const { return *m_ptr;}
		const_iterator&		operator++() noexcept { ++m_ptr; return *this;}
		const_iterator		operator++(int) noexcept { return const_iterator(m_ptr++);}
		const_iterator&		operator--() noexcept { --m_ptr; return *this;}
		const_iterator		operator--(int) noexcept { return const_iterator(m_ptr--);}
		const_iterator		operator+(difference_type _right) const noexcept { return const_iterator(m_ptr+_right);}
		void				operator+=(difference_type _right) noexcept { m_ptr +=_right;}
		const_iterator		operator-(difference_type _right) const noexcept { return const_iterator(m_ptr-_right);}
		void				operator-=(difference_type _right) noexcept { m_ptr -=_right;}
		size_type			operator-(const const_iterator& _right) const noexcept { return m_ptr-_right.m_ptr;}
		size_type			operator-(const iterator& _right) const noexcept { return m_ptr-_right.m_ptr;}
																					  
		// 4) ��																    
		bool				operator==(const const_iterator& _right) const noexcept	{ return m_ptr==_right.m_ptr;}
		bool				operator!=(const const_iterator& _right) const noexcept	{ return m_ptr!=_right.m_ptr;}
																					  
		bool				operator>(const const_iterator&  _right) const noexcept	{ return m_ptr>_right.m_ptr;}
		bool				operator>=(const const_iterator&  _right) noexcept { return m_ptr>=_right.m_ptr;}
		bool				operator<(const const_iterator&  _right) const noexcept	{ return m_ptr<_right.m_ptr;}
		bool				operator<=(const const_iterator&  _right) noexcept { return m_ptr<=_right.m_ptr;}
																					  
		bool				operator>(const iterator&  _right) const noexcept { return m_ptr>_right.m_ptr;}
		bool				operator>=(const iterator&  _right) noexcept { return m_ptr>=_right.m_ptr;}
		bool				operator<(const iterator&  _right) const noexcept { return m_ptr<_right.m_ptr;}
		bool				operator<=(const iterator&  _right) noexcept { return m_ptr<=_right.m_ptr;}

	private:
		pointer				m_ptr;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	static_vector<TDATA, TSIZE>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator() noexcept {}
		explicit iterator(pointer _pNow) noexcept { m_ptr=_pNow;}
																					  
		// 2) ����																    
		iterator&			operator=(const iterator& _right) noexcept { m_ptr=_right.m_ptr; return *this;}
		iterator&			operator=(const const_iterator& _right) noexcept { m_ptr=_right.m_ptr; return *this;}
		pointer				operator->() { return &**this;}
							operator const_iterator() noexcept { return const_iterator(m_ptr);}
																					  
		// 3) �ݺ�																    
		reference			operator*() const { return *m_ptr;}
		iterator&			operator++() noexcept { ++m_ptr; return *this;}
		iterator			operator++(int) noexcept { return iterator(m_ptr++);}
		iterator&			operator--() noexcept { --m_ptr; return *this;}
		iterator			operator--(int) noexcept { return iterator(m_ptr--);}
		iterator			operator+(difference_type _right) const noexcept { return iterator(m_ptr+_right);}
		void				operator+=(difference_type _right) noexcept { m_ptr +=_right;}
		iterator			operator-(difference_type _right) const noexcept { return iterator(m_ptr-_right);}
		void				operator-=(difference_type _right) noexcept { m_ptr -=_right;}
		size_type			operator-(const const_iterator& _right) const noexcept { return m_ptr-_right.m_ptr;}
		size_type			operator-(const iterator& _right) const noexcept { return m_ptr-_right.m_ptr;}
																					  
		// 4) ��																    
		bool				operator==(const iterator& _right) const noexcept { return m_ptr==_right.m_ptr;}
		bool				operator!=(const iterator& _right) const noexcept { return m_ptr!=_right.m_ptr;}
																					  
		bool				operator==(const const_iterator& _right) const noexcept { return m_ptr==_right.m_ptr;}
		bool				operator!=(const const_iterator& _right) const noexcept { return m_ptr!=_right.m_ptr;}
																					  
		bool				operator>(const const_iterator&  _right) const noexcept { return m_ptr>_right.m_ptr;}
		bool				operator>=(const const_iterator&  _right) noexcept { return m_ptr>=_right.m_ptr;}
		bool				operator<(const const_iterator&  _right) const noexcept { return m_ptr<_right.m_ptr;}
		bool				operator<=(const const_iterator&  _right) { return m_ptr<=_right.m_ptr;}
																					  
		bool				operator>(const iterator&  _right) const noexcept { return m_ptr>_right.m_ptr;}
		bool				operator>=(const iterator&  _right) noexcept { return m_ptr>=_right.m_ptr;}
		bool				operator<(const iterator&  _right) const noexcept { return m_ptr<_right.m_ptr;}
		bool				operator<=(const iterator&  _right) noexcept { return m_ptr<=_right.m_ptr;}

	private:
		pointer				m_ptr;
	};
};

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector() noexcept : m_size(0), m_ptr_first{}
{
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(const _mytype& _Copy) : m_size(0)
{
	try
	{
		// 1) �����سִ´�.
		insert(begin(), _Copy.begin(), _Copy.end());
	}
	catch(...)
	{
		// - ��� �����.
		clear();

		// Throw) �ٽ� Thread!!!
		throw;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(_mytype&& _Move) noexcept
{
	// ����) Move�� �ݵ�� nothrow���� �����ϴ�.

	// 1) Preparing move
	auto _iter_src = _Move._get_ptr_first<value_type>();
	auto _iter_src_end = _Move._get_ptr_first<const value_type>()+_Move._get_size();
	auto _iter_dst = _get_ptr_first<value_type>();

	// 2) move all by move-constructor
	for(;_iter_src!=_iter_src_end; ++_iter_src, ++_iter_dst)
	{
	#pragma push_macro("new")
	#undef new
		new (_iter_dst) value_type(std::move(*_iter_src));
	#pragma pop_macro("new")
	}

	// 3) Copy size value
	m_size = _Move._get_size();
}


template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(size_type _count) : m_size(0)
{
	try
	{
		// 1) _count��ŭ �ʱ�ȭ�Ѵ�.
		for(iterator iter = begin(); _count>0; ++iter, --_count)
		{
		#pragma push_macro("new")
		#undef new
			new (&(*iter)) value_type();
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		// - ��� �����.
		clear();

		// Throw) �ٽ� Thread!!!
		throw;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::static_vector(size_type _count, const value_type& _val) : m_size(0)
{
	try
	{
		// 1) �����سִ´�.
		insert(begin(), _count, _val);
	}
	catch(...)
	{
		// - ��� �����.
		clear();

		// Throw) �ٽ� Thread!!!
		throw;
	}
}

template <typename TDATA, size_t TSIZE>
template<typename TITERATOR>
static_vector<TDATA, TSIZE>::static_vector(TITERATOR _first, TITERATOR _last) : m_size(0)
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

		// Throw) �ٽ� Thread!!!
		throw;
	}
}

template <typename TDATA, size_t TSIZE>
static_vector<TDATA, TSIZE>::~static_vector()
{
	// 1) ��� �����.
	clear();
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(const _mytype& _right) noexcept
{
	// 1) clear all
	clear();

	// 2) Preparing move
	auto _iter_src = _right._get_ptr_first<const value_type>();
	auto _iter_src_end = _right._get_ptr_first<const value_type>()+_right._get_size();
	auto _iter_dst = _get_ptr_first<value_type>();

	// 3) move all by move-constructor
	for(;_iter_src != _iter_src_end; ++_iter_src, ++_iter_dst)
	{
	#pragma push_macro("new")
	#undef new
		new (_iter_dst) value_type(*_iter_src);
	#pragma pop_macro("new")
	}

	// 4) Copy size value
	this->m_size = _right._get_size();

	// return)
	return	*this;
}

template <typename TDATA, size_t TSIZE>
template <typename A, size_t B>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(const static_vector<A,B>& _right)
{
	// check) 
	CGDASSERT_ERROR(_right.size()<=TSIZE)

	// check)
	CGD_THROW_IF(_right.size()>TSIZE, std::overflow_error("CGDK exception: _right size of oversize."))

	// 1) clear all
	this->clear();

	// 2) Preparing move
	auto _iter_src = _right.template _get_ptr_first<value_type>();
	auto _iter_src_end = _right.template _get_ptr_first<value_type>()+_right._get_size();
	auto _iter_dst = _get_ptr_first<value_type>();

	// 3) move all by move-constructor
	for(;_iter_src != _iter_src_end; ++_iter_src, ++_iter_dst)
	{
	#pragma push_macro("new")
	#undef new
		new (_iter_dst) value_type(*_iter_src);
	#pragma pop_macro("new")
	}

	// 4) Copy size value
	this->m_size = _right._get_size();

	// return)
	return *this;
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(_mytype&& _right) noexcept
{
	// 1) clear all
	this->clear();

	// 2) Preparing move
	auto _iter_src = _right._get_ptr_first<value_type>();
	auto _iter_src_end = _right._get_ptr_first<const value_type>()+_right._get_size();
	auto _iter_dst = _get_ptr_first<value_type>();

	// 3) move all by move-constructor
	for(;_iter_src!=_iter_src_end; ++_iter_src, ++_iter_dst)
	{
	#pragma push_macro("new")
	#undef new
		new (_iter_dst) value_type(std::move(*_iter_src));
	#pragma pop_macro("new")
	}

	// 4) Copy size value
	this->m_size = _right._get_size();

	// 5) clear r-value container
	_right._reset_size();

	// return) 
	return *this;
}

template <typename TDATA, size_t TSIZE>
template <typename A, size_t B>
typename static_vector<TDATA, TSIZE>::_mytype& static_vector<TDATA, TSIZE>::operator=(static_vector<A,B>&& _right)
{
	// check) 
	CGDASSERT_ERROR(_right.size()<=TSIZE)

	// check)
	CGD_THROW_IF(_right.size()>TSIZE, std::overflow_error("CGDK exception: _right size of oversize."))

	// 1) clear all
	this->clear();

	// 2) Preparing move
	auto _iter_src = _right.template _get_ptr_first<value_type>();
	auto _iter_src_end = _right.template _get_ptr_first<const value_type>()+_right._get_size();
	auto _iter_dst = _get_ptr_first<value_type>();

	// 3) move all by move-constructor
	for(;_iter_src!=_iter_src_end; ++_iter_src, ++_iter_dst)
	{
#pragma push_macro("new")
#undef new
		new (_iter_dst) value_type(std::move(*_iter_src));
#pragma pop_macro("new")
	}

	// 4) Copy size value
	m_size = _right._get_size();

	// 5) clear r-value container
	_right._reset_size();

	// return) 
	return *this;
}


// ���Լ���
template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator==(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
			return (iter_dst == _right.end());

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� false����!
		if(*iter_src != *iter_dst)
			return false;

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator!=(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
			return (iter_dst!=_right.end());

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src!=*iter_dst)
			return true;

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator<(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dst == this->end())
			return false;

		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
			return (*iter_src<*iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator>(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return false;

		// check) Dst�� ���ΰ�?
		if(iter_dst == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
			return (*iter_src > *iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator<=(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return true;

		// check) Dst�� ���ΰ�?
		if(iter_dst == this->end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
			return (*iter_src < *iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
bool static_vector<TDATA, TSIZE>::operator>=(const _mytype& _right) const noexcept
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dst == this->end())
			return true;

		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
			return (*iter_src>*iter_dst);

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <typename TDATA, size_t TSIZE>
TDATA& static_vector<TDATA, TSIZE>::at(size_type _pos)
{
	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos>=size(), std::out_of_range("CGDK exception: Out of range."))

	// 1) ���� �о �ǵ�����.
	return *(((value_type*)m_ptr_first) + _pos);
}

template <typename TDATA, size_t TSIZE>
const TDATA& static_vector<TDATA, TSIZE>::at(size_type _pos) const
{
	// check) p_iPosition�� ���� 0���ٴ� ũ�� _capacity���ٴ� �۾�� �Ѵ�.
	CGD_THROW_IF(_pos<0 || _pos>=size(), std::out_of_range("CGDK exception: out of range."))

	// 1) ���� �о �ǵ�����.
	return *(((value_type*)m_ptr_first) + _pos);
}

template <typename TDATA, size_t TSIZE>
TDATA& static_vector<TDATA, TSIZE>::operator [] (size_type _pos)
{
	return	at(_pos);
}

template <typename TDATA, size_t TSIZE>
const TDATA& static_vector<TDATA, TSIZE>::operator [] (size_type _pos) const
{
	return	at(_pos);
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::resize(size_type _Newsize)
{
	// check) TSIZE���� ���� ũ�⿩������ �ȴ�.
	CGD_THROW_IF(_Newsize>TSIZE, std::length_error("CGDK exception: Invalid Size."));

	// 1) 
	iterator iter=end();
	iterator new_end(begin()+_Newsize);

	try
	{
		// 2) �þ �κб��� Reset�� �Ѵ�.
		for(; iter < new_end; ++iter)
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
		for(iterator iterRoll=end(); iterRoll!=iter; ++iterRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*iterRoll).~value_type();
		}

		// re-throw) �ٽ� Thread!!!
		throw;
	}

	// 2) Size�� ���� �����Ѵ�.
	m_size = new_end.m_ptr-((value_type*)m_ptr_first);
}


template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::clear() noexcept
{
	// 1) ��� Item�� Destructor�� ȣ���Ѵ�.
	for(iterator iter = begin(); iter != end(); ++iter)
	{
		(*iter).~value_type();
	}

	// 2) Last�� First�� ����� 0�� �����.
	m_size	 = 0;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_front(const TDATA& _val)
{
	// CASE-A) if container is empty, just push_back
	if(m_size == 0)
	{
		// - Push Back
		this->push_back(_val);

		// return) 
		return;
	}

	// 1) get size
	void* ptr_first = this->m_ptr_first;
	value_type*	_iter = ((value_type*)this->m_ptr_first) + this->m_size;
	size_t iSize = _iter -(value_type*)ptr_first;

	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize == TSIZE, std::length_error("CGDK exception: it's full!"));

	// 3) shift back last one by copy-constructing
#pragma push_macro("new")
#undef new
	new (reinterpret_cast<value_type*>(_iter)) value_type(std::move(*(_iter-1)));
#pragma pop_macro("new")

	// 4) Others do Moving
	for(--_iter; _iter>(value_type*)ptr_first; --_iter)
	{
		*_iter = std::move(*(_iter-1));
	}

	// 5) Assignment _val in front
	*(value_type*)ptr_first = _val;

	// 6) Increase Size
	++this->m_size;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_front(value_type&& _val)
{
	// CASE-A) if container is empty, just push_back
	if(this->m_size == 0)
	{
		// - Push Back
		this->push_back(std::move(_val));

		// return) 
		return;
	}

	// 1) get size
	value_type*	_iter = _get_ptr_first<value_type>() + this->m_size;
	size_t iSize = _iter - _get_ptr_first<value_type>();

	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(iSize == TSIZE, std::length_error("CGDK exception: it's full!"));

	// 3) shift back last one by copy-constructing
#pragma push_macro("new")
#undef new
	new (reinterpret_cast<value_type*>(_iter)) value_type(std::move(*(_iter-1)));
#pragma pop_macro("new")

	// 4) Others do Moving
	for(--_iter; _iter>_get_ptr_first<value_type>(); --_iter)
	{
		*_iter = std::move(*(_iter-1));
	}

	// 5) Assignment _val in front
	*this->_get_ptr_first<value_type>() = std::move(_val);

	// 6) Increase Size
	++this->m_size;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::pop_front()
{
	// check) There is no room for insert! Throw Exception
	CGD_THROW_IF(this->m_size == 0, std::length_error("CGDK exception: it's full!"));

	// 2) Decrease Size
	--this->m_size;

	// 3) Destroy First
	this->_get_ptr_first<value_type>()->~value_type();

	// declare)
	const value_type* ptr_last = this->_get_ptr_first<const value_type>() +m_size;

	// 4) Moveing...
	for(value_type* _iter = this->_get_ptr_first<value_type>(); _iter<ptr_last; ++_iter)
	{
		*_iter = std::move(*(_iter+1));
	}
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_back(const TDATA& _val)
{
	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (this->m_ptr_first + sizeof(value_type) * this->m_size) value_type(_val);
#pragma pop_macro("new")
	
	// 2) Last ������ ������Ŵ
	++this->m_size;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_back(TDATA&& _val)
{
	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (this->m_ptr_first + sizeof(value_type) * this->m_size) value_type(std::move(_val));
#pragma pop_macro("new")

	// 2) Last ������ ������Ŵ
	++this->m_size;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::push_back()
{
	// check) 
	CGDASSERT_ERROR(this->size() != this->max_size());

	// 1) Construct�� ȣ���Ѵ�.
#pragma push_macro("new")
#undef new
	new (this->m_ptr_first + sizeof(value_type) * this->m_size) value_type();
#pragma pop_macro("new")
	
	// 2) Last ������ ������Ŵ
	++this->m_size;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::pop_back()
{
#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!this->empty());
#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	CGD_RETURN_IF(this->empty());
#endif

	// 1) ũ�⸦ ���δ�.
	--this->m_size;

	// 2) Destructor�� ȣ���Ѵ�.
	(this->_get_ptr_first<value_type>() + this->m_size)->~value_type();
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::assign(size_type _count, const value_type& _val)
{
	// check) 
	CGD_THROW_IF(this->remained() < _count, std::length_error("CGDK exception: invalid size."));

	// 1) ������� First�� Last�� ����Ű�� Iterator
	value_type*	first = this->_get_ptr_first<value_type>() + this->m_size;

	// 2) End�� ���Ѵ�.
	value_type*	new_end = first + _count;

	try
	{
		// 3) ���� �ִ´�.
		for(; first != new_end; ++first)
		{
		#pragma push_macro("new")
		#undef new
			new (first) value_type(_val);
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		const value_type* ptr_last = this->_get_ptr_first<value_type>()+m_size;

		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(value_type* pRoll = ptr_last; pRoll != first; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~value_type();
		}

		// Throw) �ٽ� Thread!!!
		throw;
	}

	// 4) �Ϸ������� m_size�� ���� �����Ѵ�.
	this->m_size = new_end-((value_type*)this->m_ptr_first);
}

template <typename TDATA, size_t TSIZE>
template <typename ITERATOR>
void static_vector<TDATA, TSIZE>::assign(ITERATOR _first, ITERATOR _last)
{
	// 1) ������� First�� Last�� ����Ű�� Iterator
	value_type*	ptr_now = this->_get_ptr_first<value_type>() + this->m_size;

	try
	{
		// 2) ���� �ִ´�.
		for(; _first != _last; ++_first, ++ptr_now)
		{
			// check) Remained�� 0�̸� �ȉ´�.
			CGD_THROW_IF(remained()!=0, std::length_error("CGDK exception: invalid size."));

		#pragma push_macro("new")
		#undef new
			new (ptr_now) value_type(*_first);
		#pragma pop_macro("new")
		}
	}
	catch(...)
	{
		// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
		for(value_type* pRoll= this->_get_ptr_first<value_type>() + this->m_size; pRoll != ptr_now; ++pRoll)
		{
			// - Destroy�� ȣ���Ѵ�.
			(*pRoll).~value_type();
		}

		// Throw) �ٽ� Thread!!!
		throw;
	}

	// 3) �Ϸ������� size�� ���� �����Ѵ�.
	m_size = ptr_now - (value_type*)this->m_ptr_first;
}

template <typename TDATA, size_t TSIZE>
template<typename TITERATOR>
void static_vector<TDATA, TSIZE>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr>= this->_get_ptr_first<value_type>() && _where.m_ptr <= (this->_get_ptr_first<value_type>() + this->m_size));

	// 1) Insert count�� ��´�.
	size_type count_insert = _last-_first;

	// 2) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<count_insert, std::length_error("CGDK exception: full!"));

	// 3) source pointer and destination pointer for moving
	value_type*	iter_src = this->_get_ptr_first<value_type>() + this->m_size;
	value_type*	iter_end = iter_src;
	value_type*	iter_dst = iter_src + count_insert;

	// 4) shift back data by move-constructing
	while(iter_dst != iter_end && iter_src>_where.m_ptr)
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
		value_type*	iter_rb_end = _get_ptr_first<value_type>()+m_size;
		value_type*	iter_rb_dst = const_cast<value_type*>(_where.m_ptr);
		value_type*	iter_rb_src = iter_rb_dst + count_insert;

		// - shift front 
		while(iter_rb_dst != iter_rb_end)
		{
			*iter_rb_dst = std::move(*iter_rb_src);
		}

		// - destroy remained
		while(iter_rb_dst < iter_src)
		{
			iter_rb_dst->~value_type();
		}

		// Throw) �ٽ� Thread!!!
		throw;
	}

	// 5) size�� ������Ų��.
	this->m_size += count_insert;
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::insert(const_iterator _where, size_type _count, const value_type& _val)
{
	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr>= _get_ptr_first<value_type>() && _where.m_ptr<=(_get_ptr_first<value_type>()+m_size));

	// check) �� ������ �����ϴ��� �˻��Ѵ�.
	CGD_THROW_IF(remained()<_count, std::length_error("CGDK exception: out of room."));

	// 1) source pointer and destination pointer for moving
	auto iter_src = _get_ptr_first<value_type>() + m_size;
	auto iter_end = iter_src;
	auto iter_dst = iter_src+_count;

	// 2) shift back data by move-constructing
	while(iter_dst!= iter_end && iter_src>_where.m_ptr)
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

		*iter_dst = std::move(*iter_src);
	}

	try
	{
		// 4) copy data to _where
		for(; iter_src!=iter_dst; ++iter_src)
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
		auto _iter_rb_end = _get_ptr_first<value_type>()+m_size;
		auto _iter_rb_dst = const_cast<value_type*>(_where.m_ptr);
		auto _iter_rb_src = _iter_rb_dst+_count;

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
	m_size += static_cast<int>(_count);
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator static_vector<TDATA, TSIZE>::insert(const_iterator _where, const value_type& _val)
{
	// ����) CGDK::static_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr >= _get_ptr_first<value_type>() && _where.m_ptr <= (_get_ptr_first<value_type>()+m_size));

	// check) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(this->remained() <= 0, std::length_error("CGDK exception: full!"));

	value_type*	ptr_last = _get_ptr_first<value_type>() + this->m_size;
	
	if(_where.m_ptr != ptr_last)
	{
		// 1) set iterator
		value_type*	_iter = ptr_last;

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
		new (reinterpret_cast<value_type*>(_where.m_ptr)) value_type(_val);
	#pragma pop_macro("new")
	}
	catch(...)
	{
		value_type*	ptr_last = this->_get_ptr_first<value_type>() + this->m_size;

		// - shift front 
		for(value_type* _iter=const_cast<value_type*>(_where.m_ptr);_iter!=ptr_last;++_iter)
		{
			*_iter = std::move(*(_iter+1));
		}

		// Throw) Reraise
		throw;
	}

	// 3) size�� ������Ų��.
	++this->m_size;

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator static_vector<TDATA, TSIZE>::insert(const_iterator _where, value_type&& _val)
{
	// ����) CGDK::static_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr>= _get_ptr_first<value_type>() && _where.m_ptr<=(this->_get_ptr_first<value_type>() + this->m_size));

	// check) ���� ������ �ִ��� Ȯ���Ѵ�.
	CGD_THROW_IF(this->remained() <= 0, std::length_error("CGDK exception: full!"));

	value_type*	ptr_last = this->_get_ptr_first<value_type>() + this->m_size;
	
	if(_where.m_ptr != ptr_last)
	{
		// 1) set iterator
		value_type*	_iter = ptr_last;

		// 2) move constructing last one
	#pragma push_macro("new")
	#undef new
		new (_iter) value_type(std::move(*(_iter-1)));
	#pragma pop_macro("new")

		// 3) Shift back others by Moving
		for(--_iter; _iter != _where.m_ptr; --_iter)
		{
			*_iter = std::move(*(_iter-1));
		}
	}

	try
	{
		// 2) ��� �ڸ��� Constructor�� ȣ���� ���� �����Ѵ�.
	#pragma push_macro("new")
	#undef new
		new (reinterpret_cast<value_type*>(_where.m_ptr)) value_type(std::move(_val));
	#pragma pop_macro("new")
	}
	catch(...)
	{
		value_type*	ptr_last = _get_ptr_first<value_type>()+m_size;

		// - shift front 
		for(value_type* _iter=const_cast<value_type*>(_where.m_ptr);_iter!=ptr_last;++_iter)
		{
			*_iter = std::move(*(_iter+1));
		}

		// Throw) Reraise
		throw;
	}

	// 3) size�� ������Ų��.
	++this->m_size;

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator  static_vector<TDATA, TSIZE>::erase(const_iterator _where) noexcept
{
	// Attention) There is no checking of max_size() in CGDK::static_vector

	// check) Iterator is invalid (is within m_size)
	CGDASSERT_ERROR(_where.m_ptr >= this->_get_ptr_first<value_type>() && _where.m_ptr<(this->_get_ptr_first<value_type>() + this->m_size));

	// check) Is empty?
	CGDASSERT_ERROR(this->size() > 0);

	// 1) Call destructor on _where
	(_where.m_ptr)->~value_type();

	// 2) Decrease size
	--this->m_size;

	// declare)
	auto ptr_last = this->_get_ptr_first<value_type>() + this->m_size;

	// 3) Moveing forward after _where
	if(_where.m_ptr != ptr_last)
	{
		// - move-constructing 
	#pragma push_macro("new")
	#undef new
		new (const_cast<value_type*>(_where.m_ptr)) value_type(*const_cast<value_type*>(_where.m_ptr + 1));
	#pragma pop_macro("new")

		for(++_where.m_ptr; _where.m_ptr<ptr_last; ++_where)
		{
			*const_cast<value_type*>(_where.m_ptr) = *const_cast<value_type*>(_where.m_ptr + 1);
		}
	}

	// return)
	return iterator(const_cast<value_type*>(_where.m_ptr));
}

template <typename TDATA, size_t TSIZE>
typename static_vector<TDATA, TSIZE>::iterator static_vector<TDATA, TSIZE>::erase(const_iterator _first, const_iterator _last) noexcept
{
	// ����) CGDK::static_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	value_type*	ptr_last = this->_get_ptr_first<value_type>() + this->m_size;

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_first.m_ptr>= this->_get_ptr_first<value_type>() && _first.m_ptr <= ptr_last);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_last.m_ptr >= this->_get_ptr_first<value_type>() && _last.m_ptr <= ptr_last);

	// 1) First�� Last�� ���ٸ� �׳� �ǵ���.
	size_type item_count = _last-_first;

	// check) ItemCount�� 0�̸� �׳� ������.
	CGD_RETURN_IF(item_count == 0, iterator(const_cast<value_type*>(_last.m_ptr)));

	// 2) Destroying 
	for(const_iterator iter=_first; iter!=_last; ++iter)
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
	this->m_size -= static_cast<int>(item_count);

	// return)
	return iterator(const_cast<value_type*>(_last.m_ptr));
}

template <typename TDATA, size_t TSIZE>
void static_vector<TDATA, TSIZE>::swap(_mytype& _right) noexcept
{
	// check) ���� �Ŷ�� �׳� �ǵ�����.
	CGD_RETURN_IF(this == &_right);

	// 1) ������ ��ä�� �ٲ۴�.(Allocator�� ����ġ �ʴ´�. ���� ����...)
	CGD_SWAP(*this, _right);
}


}