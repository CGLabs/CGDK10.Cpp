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

template <class TDATA, size_t TSIZE=32, class TALLOCATOR=std::allocator<TDATA>>
class fast_vector
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type		Contain�� ��� ������ ��.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator	��ȸ�� �� ���Ǵ� �ݺ���(const��)
//     6) X:difference_type	�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type		X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator ����ȯ �� ���Ǵ� �ݺ���.
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

	// Allocator)
	typedef TALLOCATOR		allocator_type;

	// Self) �ڱ��ڽ�(ǥ�� �ƴ�.)
	typedef	fast_vector<TDATA, TSIZE, TALLOCATOR>	_mytype;

	// Rebinder) 
	template<class TOTHER_DATA, size_t TOTHER_SIZE, class TOTHER_ALLOCATOR=TALLOCATOR>
	struct rebind
	{
		typedef fast_vector<TOTHER_DATA, TOTHER_SIZE, TOTHER_ALLOCATOR> other;
	};


// ****************************************************************************
// Common Container Standard)
//
//  * Common Container Requirement
//     1) X();				Default Constructor
//     2) X(a);				Copy Constrctor.(�ҿ�ð��� ������)
//		  X u(a);
//     3) (&a)->~X();		Destructor.(�ҿ�ð��� ������)
//     4) a.begin(); 		Container ��ȸ�� ����� ���۰� �� iterator 
//		  a.end();
//     5) a==b; a!=b;		Container ��� ���� ������ true.(�ҿ�ð� ������)
//     6) a.size();			Container�� ��� ������ ������ �����Ѵ�.
//     7) a.max_size();		Container�� ���� �� �ִ� �ִ� ���� ������ �����Ѵ�.
//     8) a.empty();		Container�� ��� �ִ� ����� true�� �����Ѵ�.
//     9) a<b; a>b; 		�� ����(�ҿ�ð� ������)
//		  a<=b; a>=b;
//    10) r=a;				Container ���Կ���(�ҿ�ð� ������)
//    11) a.swap(b);		������ Ÿ���� �� Ŀ���̳ʸ� ���� �¹ٲ۴�.
//
//  * Reversible Requirement
//     1) a.rbegin(); 		�ݴ���� ��ȸ�� ���� ���۰� �� iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	fast_vector();
	fast_vector(const _mytype& _right);
	fast_vector(_mytype&& _right);
	~fast_vector();

public:
	// Common Standard 1) Status Function
	size_type				size() const noexcept { return (this->m_ptr_last - this->m_ptr_first);}
	size_type				max_size() const noexcept { return 0x7fffffff;}
	bool					empty() const noexcept { return (this->m_ptr_last == this->m_ptr_first);}

	// Common Standard 2) 
	iterator				begin() noexcept { return iterator(this->m_ptr_first);}
	const_iterator			begin() const noexcept { return const_iterator(this->m_ptr_first);}
	const_iterator			cbegin() const noexcept { return const_iterator(this->m_ptr_first);}
	iterator				end() noexcept { return iterator(this->m_ptr_last);}
	const_iterator			end() const noexcept { return const_iterator(this->m_ptr_last);}
	const_iterator			cend() const noexcept { return const_iterator(this->m_ptr_last);}
	reverse_iterator		rbegin() noexcept { return reverse_iterator(iterator(this->m_ptr_last - 1));}
	const_reverse_iterator	rbegin() const noexcept { return const_iterator(this->m_ptr_last - 1);}
	const_reverse_iterator	crbegin() const noexcept { return const_iterator(this->m_ptr_last - 1);}
	reverse_iterator		rend() noexcept { return reverse_iterator(iterator(this->m_ptr_first - 1));}
	const_reverse_iterator	rend() const noexcept { return const_iterator(this->m_ptr_first - 1);}
	const_reverse_iterator	crend() const noexcept { return const_iterator(this->m_ptr_first - 1);}

	// Common Standard 3) 
	void					swap(_mytype& _right);

	// Common Standard 5) Operators
	bool					operator==(const _mytype& _right) const;
	bool					operator!=(const _mytype& _right) const;
	bool					operator<(const _mytype& _right) const;
	bool					operator>(const _mytype& _right) const;
	bool					operator<=(const _mytype& _right) const;
	bool					operator>=(const _mytype& _right) const;

	// Common Standard 6) Assignment operator
	_mytype&				operator=(const _mytype& _right);
	_mytype&				operator=(_mytype&& _right);
	template<size_t XSIZE, class XALLOCATOR>
	_mytype&				operator=(const fast_vector<TDATA, XSIZE, XALLOCATOR>& _right);
	template<size_t XSIZE, class XALLOCATOR>
	_mytype&				operator=(fast_vector<TDATA, XSIZE, XALLOCATOR>&& _right);


// ****************************************************************************
// Sequence Container Standard)
//
//  * Sequence Container Requirement
//    1) X(n, t);			t�� ���纻 n���� ������ Sequence�� �����Ѵ�.
//		 X a(n, t);	
//    2) X(i, j); 			����[i,j]�� ����� ������ Sequence�� �����Ѵ�.
//		 X a(i, j);
//    3) a.insert(p,t);		p�տ� t�� ���纻�� �����Ѵ�. ���ϰ��� ���Ե�
//							���Ҹ� ����Ű�� �ݺ����̴�.
//    4) a.insert(p,n,t);	p�տ� t�� ���纻 n���� �����Ѵ�.
//    5) a.insert(p,i,j);	p�տ� [i,j]�� ��� ���ҵ��� ���纻�� �����Ѵ�.
//							i,j�� �ݺ���
//    6) a.erase(q);		q�� ����Ű�� ���Ҹ� �����Ѵ�. ���ϰ��� �����Ǳ�
//							���� q������ ��ġ�ߴ� ���Ҹ� ����Ű�� �ݺ���
//    7) a.erase(q1,q2);	����[q1,q2]�� ���Ե� ���ҵ��� �����Ѵ�. ���ϰ���
//							�����Ǳ� ���� q2������ ��ġ�ߴ� ���Ҹ� ����Ű��
//							�ݺ���.
//    8) a.clear();			�����̳ʿ� ��� ���� ���Ҹ� �����Ѵ�. 
//							a.erase(a.begin(), a.end())�� �����ϴ�.
//
// ----------------------------------------------------------------------------
public:
	fast_vector(size_type _count );
	fast_vector(size_type _count , const TDATA& _val);
	fast_vector(size_type _count , const TDATA& _val, const TALLOCATOR& _Al);
	template<class TITERATOR>
	fast_vector(TITERATOR _first, TITERATOR _last);
	template<class TITERATOR>
	fast_vector(TITERATOR _first, TITERATOR _last, const TALLOCATOR& _Al);

public:
	// Sequence Standard 1) insert member function
	template<class TITERATOR>
	void					insert(const_iterator _where, TITERATOR _first, TITERATOR _last);
	iterator				insert(const_iterator _where, const TDATA& _val);
	iterator				insert(const_iterator _where, TDATA&& _val);
	void					insert(const_iterator _where, int _count , const TDATA& _val);

	// Sequence Standard 2) erase member function
	iterator				erase(const_iterator _where);
	iterator				erase(const_iterator _first, const_iterator _last);

	// Sequence Standard 3) clear
	void					clear() noexcept;

	// Added) Find (No Stantard)
	iterator				find(const_reference _val) noexcept;



// ****************************************************************************
// fast_vector Member)
// 
// 
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const noexcept { return (this->m_ptr_end - this->m_ptr_first);}
	size_type				remained() const noexcept { return (this->m_ptr_end - this->m_ptr_last);}

	// 2) Data
	reference				front() { return *this->m_ptr_first;}
	const_reference			front() const { return *this->m_ptr_first;}

	reference				back() { return *(this->m_ptr_last-1);}
	const_reference			back() const { return *(this->m_ptr_last-1);}

	reference				at(size_type _pos);
	const_reference			at(size_type _pos) const;

	reference				operator [] (size_type _pos);
	const_reference			operator [] (size_type _pos) const;

	// 3) push/pop back
	void					push_front(const TDATA& _val) { this->insert(begin(), _val);}
	void					push_front(TDATA&& _val) { this->insert(begin(), std::forward<TDATA>(_val));}
	void					push_front() { this->insert(begin(), TDATA());}
	void					pop_front() { this->erase(begin());}

	void					push_back(const TDATA& _val);
	void					push_back(TDATA&& _val);
	void					push_back();
	void					pop_back();

	// 4) Assign
	template <class ITERATOR>
	void					assign(ITERATOR _first, ITERATOR _last);
	void					assign(size_type _count , const TDATA& _val);

	// 5) Reserve
	void					reserve(size_type _count );

	// 6) Resize
	void					resize(size_type _new_size);
	void					resize(size_type _new_size, TDATA _val);

	// 7) Shrink
	void					shrink_to_fit();

	// 8) Allocation
	allocator_type			get_allocator() const noexcept { return this->m_alloc_val;}

	// 9) others
	bool					is_own_data() const noexcept { return this->m_ptr_first == this->m_array;}


// ****************************************************************************
// Member Variable) 
// ----------------------------------------------------------------------------
public:
	// 1) Array
	TDATA*					m_ptr_first;		// Array�� ó�� ��ġ...
	TDATA*					m_ptr_last;		// Array���� ���ǰ� �ִ� ���� ��~()
	TDATA*					m_ptr_end;		// Array�Ҵ���� ���� ��~(reserved)

	// 2) Default Container
	char					m_array[sizeof(value_type)*TSIZE];

	// 2) Allocator
	allocator_type			m_alloc_val;

private:
	void					_Expand(size_type _count , const_iterator _where, size_type _room);


// ****************************************************************************
// Iterator) 
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	fast_vector<TDATA, TSIZE, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef	typename _mytype::pointer			data_pointer;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;

		friend			iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator() noexcept {}
		explicit const_iterator(data_pointer _pnow) noexcept : m_ptr_last(_pnow)  {}

		// 2) ����
		const_iterator&	operator=(const const_iterator& _right)  noexcept{ this->m_ptr_last=_right.m_ptr_last; return *this;}
		pointer			operator->() { return &**this;}
																		  
		// 3) �ݺ�													    
		reference		operator*() const noexcept { return *this->m_ptr_last;}
		const_iterator&	operator++() noexcept { ++this->m_ptr_last; return *this;}
		const_iterator	operator++(int) noexcept { return const_iterator(this->m_ptr_last++);}
		const_iterator&	operator--() noexcept { --this->m_ptr_last; return *this;}
		const_iterator	operator--(int) noexcept { return const_iterator(this->m_ptr_last--);}
		const_iterator	operator+(difference_type _right) const noexcept { return const_iterator(this->m_ptr_last+_right);}
		void			operator+=(difference_type _right) noexcept { this->m_ptr_last+=_right;}
		const_iterator	operator-(difference_type _right) const noexcept { return const_iterator(this->m_ptr_last-_right);}
		void			operator-=(difference_type _right) noexcept { this->m_ptr_last-=_right;}
		size_type		operator-(const const_iterator& _right) const noexcept { return this->m_ptr_last-_right.m_ptr_last;}
		size_type		operator-(const iterator& _right) const noexcept { return this->m_ptr_last-_right.m_ptr_last;}
																		  
		// 4) ��													    
		bool			operator==(const const_iterator& _right) const	{ return this->m_ptr_last==_right.m_ptr_last;}
		bool			operator!=(const const_iterator& _right) const	{ return this->m_ptr_last!=_right.m_ptr_last;}
																		  
		bool			operator>(const const_iterator&  _right) const noexcept { return this->m_ptr_last>_right.m_ptr_last;}
		bool			operator>=(const const_iterator&  _right) noexcept { return this->m_ptr_last>=_right.m_ptr_last;}
		bool			operator<(const const_iterator&  _right) const noexcept { return this->m_ptr_last<_right.m_ptr_last;}
		bool			operator<=(const const_iterator&  _right) noexcept { return this->m_ptr_last<=_right.m_ptr_last;}
																		  
		bool			operator>(const iterator&  _right) const noexcept { return this->m_ptr_last>_right.m_ptr_last;}
		bool			operator>=(const iterator&  _right) noexcept { return this->m_ptr_last>=_right.m_ptr_last;}
		bool			operator<(const iterator&  _right) const noexcept { return this->m_ptr_last<_right.m_ptr_last;}
		bool			operator<=(const iterator&  _right) noexcept { return this->m_ptr_last<=_right.m_ptr_last;}
																		  
	private:
		data_pointer	m_ptr_last;
	};

	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	fast_vector<TDATA, TSIZE, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef	typename _mytype::pointer			data_pointer;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;

		friend			const_iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator() noexcept {}
		iterator(const const_iterator& _copy) noexcept : m_ptr_last(_copy.m_ptr_last){}
		explicit iterator(pointer _now) noexcept : m_ptr_last(_now) {}

		// 2) ����
		iterator&		operator=(const iterator& _right) noexcept { this->m_ptr_last=_right.m_ptr_last; return *this;}
		iterator&		operator=(const const_iterator& _right) noexcept { this->m_ptr_last=_right.m_ptr_last; return *this;}
		pointer			operator->() { return &**this;}
						operator const_iterator() const noexcept { return const_iterator(this->m_ptr_last);}
																		  
		// 3) �ݺ�													    
		reference		operator*() const noexcept { return *this->m_ptr_last;}
		iterator&		operator++() noexcept { ++this->m_ptr_last; return *this;}
		iterator		operator++(int) noexcept { return iterator(this->m_ptr_last++);}
		iterator&		operator--() noexcept { --this->m_ptr_last; return *this;}
		iterator		operator--(int) noexcept { return iterator(this->m_ptr_last--);}
		iterator		operator+(difference_type _right) const noexcept { return iterator(this->m_ptr_last+_right);}
		void			operator+=(difference_type _right) noexcept { this->m_ptr_last+=_right;}
		iterator		operator-(difference_type _right) const noexcept { return iterator(this->m_ptr_last-_right);}
		void			operator-=(difference_type _right) noexcept { this->m_ptr_last-=_right;}
		size_type		operator-(const const_iterator& _right) const noexcept { return this->m_ptr_last-_right.m_ptr_last;}
		size_type		operator-(const iterator& _right) const noexcept { return this->m_ptr_last-_right.m_ptr_last;}
																		  
		// 4) ��													    
		bool			operator==(const iterator& _right) const noexcept { return this->m_ptr_last==_right.m_ptr_last;}
		bool			operator!=(const iterator& _right) const noexcept { return this->m_ptr_last!=_right.m_ptr_last;}
																		  
		bool			operator==(const const_iterator& _right) const noexcept { return this->m_ptr_last==_right.m_ptr_last;}
		bool			operator!=(const const_iterator& _right) const noexcept { return this->m_ptr_last!=_right.m_ptr_last;}
																		  
		bool			operator>(const const_iterator& _right) const noexcept { return this->m_ptr_last>_right.m_ptr_last;}
		bool			operator>=(const const_iterator& _right) const noexcept { return this->m_ptr_last>=_right.m_ptr_last;}
		bool			operator<(const const_iterator& _right) const noexcept { return this->m_ptr_last<_right.m_ptr_last;}
		bool			operator<=(const const_iterator& _right) const noexcept { return this->m_ptr_last<=_right.m_ptr_last;}
																		  
		bool			operator>(const iterator& _right) const noexcept { return this->m_ptr_last>_right.m_ptr_last;}
		bool			operator>=(const iterator& _right) const noexcept{ return this->m_ptr_last>=_right.m_ptr_last;}
		bool			operator<(const iterator& _right) const noexcept { return this->m_ptr_last<_right.m_ptr_last;}
		bool			operator<=(const iterator& _right) const noexcept { return this->m_ptr_last<=_right.m_ptr_last;}

	private:
		data_pointer	m_ptr_last;
	};
};

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector() : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(const _mytype& _right) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		this->insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(_mytype&& _right) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// declare) ������ ũ�⸦ ��´�.
		auto size_right = _right.size();

		// 1) ���� TSIZE���� ũ�� �ٷ� Move�ϰ� ��!
		if(size_right > TSIZE)
		{
			// - �״�� �����Ѵ�.
			this->m_ptr_first = _right.m_ptr_first;
			this->m_ptr_last = _right.m_ptr_last;
			this->m_ptr_end = _right.m_ptr_end;
			this->m_alloc_val = _right.m_alloc_val;

			// - Right�� Reset!
			_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
		}
		else
		{
			// - ���� �����͸� Move�Ѵ�.
			auto iter_source = _right.m_ptr_first;
			auto iter_dest = this->m_ptr_first;
			for(; iter_source != _right.m_ptr_last; ++iter_source, ++iter_dest)
			{
				*iter_dest = std::forward<TDATA>(*iter_source);
			}

			// - Last�� �����Ѵ�.
			this->m_ptr_last = iter_dest;

			// - _right�� Clear�Ѵ�.
			for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
			{
				_right.m_alloc_val.destroy(iter_destroy);
			}

			// - Right�� Reset!
			_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
		}
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count ) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) ũ�⸦ �����Ѵ�.
		this->resize(_count);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count , const TDATA& _val) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		this->insert(this->begin(), _count , _val);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count , const TDATA& _val, const TALLOCATOR& _Al) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		this->insert(this->begin(), _count , _val);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<class TITERATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(TITERATOR _first, TITERATOR _last) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array) + TSIZE)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		this->insert(this->begin(), _first, _last);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if (m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<class TITERATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(TITERATOR _first, TITERATOR _last, const TALLOCATOR& _Al) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) �����سִ´�.
		this->insert(this->begin(), _first, _last);
	}
	CGD_CATCH_ALL
	{
		// - ��� �����.
		this->clear();

		// - Deallocate�Ѵ�.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::~fast_vector()
{
	// 1) ��� �����.
	this->clear();

	// 2) Deallocate�Ѵ�.
	if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
	{
		this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(const _mytype& _right)
{
	// 1) �ϴ� ������ �� �����.
	this->clear();

	// 2) �����سִ´�.
	CGD_TRY
	{
		insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// return) �ڱ� �ڽ� Return
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(_mytype&& _right)
{
	// declare) ������ ũ�⸦ ��´�.
	auto size_right = _right.size();

	// 1) ���� TSIZE���� ũ�� �ٷ� Move�ϰ� ��!
	if(size_right > TSIZE)
	{
		// - ���� ���� �����͸� clear�Ѵ�.
		this->clear();

		// - �״�� �����Ѵ�.
		this->m_ptr_first = _right.m_ptr_first;
		this->m_ptr_last = _right.m_ptr_last;
		this->m_ptr_end = _right.m_ptr_end;
		this->m_alloc_val = _right.m_alloc_val;

		// - Right�� Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
	}
	else
	{
		// - ���� ���� �����͸� clear�Ѵ�.
		this->clear();

		// - �����͸� Move�Ѵ�.
		auto iter_source = _right.m_ptr_first;
		auto iter_dest = this->m_ptr_first;

		for(; iter_source!=_right.m_ptr_last; ++iter_source, ++iter_dest)
		{
			m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Last�� �����Ѵ�.
		this->m_ptr_last = iter_dest;

		// - _right�� Clear�Ѵ�.
		for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
		{
			_right.m_alloc_val.destroy(iter_destroy);
		}

		// - Right�� Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
	}

	// return) �ڱ� �ڽ� Return
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<size_t XSIZE, class XALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(const fast_vector<TDATA, XSIZE, XALLOCATOR>& _right)
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
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<size_t XSIZE, class XALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(fast_vector<TDATA, XSIZE, XALLOCATOR>&& _right)
{
	// declare) ������ ũ�⸦ ��´�.
	auto size_right = _right.size();

	// 1) ���� TSIZE���� ũ�� �ٷ� Move�ϰ� ��!
	if(size_right>XSIZE && size_right>TSIZE)
	{
		// - ���� ���� �����͸� clear�Ѵ�.
		clear();

		// - �״�� �����Ѵ�.
		this->m_ptr_first = _right.m_ptr_first;
		this->m_ptr_last = _right.m_ptr_last;
		this->m_ptr_end = _right.m_ptr_end;
		this->m_alloc_val = _right.m_alloc_val;

		// - Right�� Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
	}
	else 
	{
		// - ���� ���� �����͸� clear�Ѵ�.
		clear();

		// - ���� �����͸� Destroy�Ѵ�.
		if(size_right > TSIZE)
		{
			// 1) Array�� �����Ѵ�.
			TDATA* temp_array = this->m_alloc_val.allocate(size_right);

			// check) Succeded in allocation?
			CGDASSERT_ERROR(temp_array != nullptr);

			// check) if fail to allocation, throw exception 
			CGD_THROW_IF(temp_array == nullptr, std::bad_alloc());

			this->m_ptr_first = temp_array;
			this->m_ptr_last = temp_array;
			this->m_ptr_end = temp_array + size_right;
		}

		// - �����͸� Move�Ѵ�.
		auto iter_source = _right.m_ptr_first;
		auto iter_dest = this->m_ptr_first;

		for(; iter_source!=_right.m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Last�� �����Ѵ�.
		this->m_ptr_last = iter_dest;

		// - _right�� Clear�Ѵ�.
		for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
		{
			_right.m_alloc_val.destroy(iter_destroy);
		}

		// - Right�� Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
	}

	// return) �ڱ� �ڽ� Return
	return	*this;
}

// ���Լ���
template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator==(const _mytype& _right) const
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return (iter_dest==_right.end());

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator!=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return (iter_dest!=_right.end());

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator<(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator>(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return false;

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return true;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
		{
			return (*iter_src > *iter_dest);
		}

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator<=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == this->end())
			return true;

		// check) Dst�� ���ΰ�?
		if(iter_dest == this->end())
			return false;

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dest)
			return (*iter_src < *iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator>=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dest = _right.begin();

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
			return (*iter_src>*iter_dest);

		// 3) ������~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at(size_type _pos)
{
	// check) _pos is greater than 0 and less than size()
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK Exception: Out of range ('reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at')"))

	// 1) ���� �о �ǵ�����.
	return this->m_ptr_first[_pos];
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::const_reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at(size_type _pos) const
{
	// check) _pos is greater than 0 and less than size()
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK Exception: Out of range ('const_reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at')"))

	// 1) read and return value at _pos
	return this->m_ptr_first[_pos];
}


template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::reference fast_vector<TDATA, TSIZE, TALLOCATOR>::operator [] (size_type _pos)
{
	return this->at(_pos);
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::const_reference fast_vector<TDATA, TSIZE, TALLOCATOR>::operator [] (size_type _pos) const
{
	return this->at(_pos);
}

//-----------------------------------------------------------------
// reserve() �Լ�.
//
// _count ��ŭ buffer�� �̸� Ȯ���ϴ� �Լ��̴�.
//  ����, _count �� ���� reserve�� ũ�⺸�� ���� ��� �ƹ��� ������
// �������� ���� ���̴�.
//  _count �� ���� Reserve�� �������� Ŭ ��� _count ��ŭ���� Ȯ��
// �Ѵ�.
// �� �Լ� ������ size()�� ��ȭ��  ������ max_size()�� ���Ҽ� �ִ�.
//
//  �̶�, ���ο� ũ���� ���ο� buffer�� allocator�κ��� �Ҵ���
// ������ ������ buffer�� deallocate�Ѵ�. 
// ������ ����Ǿ� �ִ� data���� ���� �Ҵ���� buffer�� ���� ��ġ�� 
// ���簡 ��������.(�� constructor�� ȣ����� �ʴ´�.)
//
//  ���� �ִ� ������ �˰� �� ��� �̸� reserve�� ������ �ٽ� �Ҵ� 
// ������ ���� �߰������� ���� ���ϸ� ���� �� �ִ�.
//  std::fast_vector�� ��� �� ���� for_loop���� ���� �����Ͽ����� ���⼭
// �� memcpy�� ���� ����ȴ�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::reserve(size_type _count )
{
	// check) If _count  is less than capacity() or _count  is equare or less than TSIZE, it is return
	if(_count <= this->capacity() || _count <= TSIZE)
		return;

	// 1) ���ο� array�� �Ҵ�޴´�. (Array�� �����Ѵ�.)
	TDATA* temp_array = this->m_alloc_val.allocate(_count ); 

	// 2) ���ο� ũ�⸦ ��´�.
	size_type now_size = this->size();

	// 3) ���� array�� �Ҵ������Ѵ�. (size�� 0�̸� ���� ���� ������ �ʿ�� ����.)
	if(now_size != 0 && temp_array != this->m_ptr_first)
	{
		// - �޸𸮸� �����Ѵ�.
		for(auto iter_source = this->m_ptr_first, iter_dest = temp_array; iter_source != m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - ������ data�� �����.(Destroy�� ȣ������ �ʴ´�.)
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) ���� �����Ѵ�.
	this->m_ptr_first = temp_array;
	this->m_ptr_last = temp_array + now_size;
	this->m_ptr_end = temp_array + _count ;
}

//-----------------------------------------------------------------
// _Expand �Լ�.
//
// �� �Լ��� ���ο����� ���Ǵ� �Լ��̴�.
// reserve�� ���������� �Ȱ��� ũ�⸦ Ȯ���ϴ� �Լ����� �ٸ� ����  
// Ȯ���ϴ� �������� ������ data�� ������ ���� �� _where�κ���
// _room��ŭ�� ���ڸ��� ����ٴ� ���̴�. 
// �ַ� Insert�� �����ϴ� �� Expand�� �Ͼ ��� ���ȴ�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::_Expand(size_type _count , const_iterator _where, size_type _room)
{
	// check) capacity�� �̹� _count ���� ũ�� �׳� �ǵ�����.
	CGD_RETURN_IF(_count  <= this->capacity() || _count  <= TSIZE);

	// 1) ���ο� array�� �Ҵ�޴´�. (Array�� �����Ѵ�.)
	TDATA* temp_array = this->m_alloc_val.allocate(_count ); 

	// check) Succeded in allocation?
	CGDASSERT_ERROR(temp_array != nullptr);

	// check) if fail to allocation, throw exception 
	CGD_THROW_IF(temp_array == nullptr, std::bad_alloc());
	
	// 2) ���� size�� �����´�.
	size_type now_size = this->size();

	// 3) ���� array�� �Ҵ������Ѵ�. (size�� 0�̸� ���� ���� ������ �ʿ�� ����.)
	if(now_size != 0)
	{
		// check) m_ptr_first�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(this->m_ptr_first != 0);

		// check) m_ptr_first�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

		// - ������ Source
		auto iter_source = this->m_ptr_first;
		auto iter_dest = temp_array;

		// - �պκ��� ������ �ű��.
		for(; iter_source!=_where.m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Room��ŭ ����.
		iter_dest		+= _room;
		for(; iter_source!=m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - ���� �������� �Ҹ��ڸ� ȣ���Ѵ�.
		for (auto iter_destroy=m_ptr_first; iter_destroy!=m_ptr_last; ++iter_destroy)
		{
			this->m_alloc_val.destroy(iter_destroy);
		}

		// - ������ �Ҵ���� Memory Chunk�� deallocate�Ѵ�.(Destroy�� ȣ������ �ʴ´�.)
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) ���� �����Ѵ�.
	this->m_ptr_first = temp_array;
	this->m_ptr_last = temp_array + now_size + _room;
	this->m_ptr_end = temp_array + _count ;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::resize(size_type _new_size)
{
	this->resize(_new_size, TDATA());
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::resize(size_type _new_size, TDATA _val)
{
	// 1) reserve�� ũ�� Ȯ��.(�ִ�ũ�⺸�� ũ�� ũ�⸦ �ø���.)
	if(_new_size > this->capacity())
	{
		this->reserve(_new_size);
	}

	// 2) ũ�� �����ϱ�.
	iterator iter = this->end();
	iterator new_end(this->begin() + _new_size);

	if(new_end > iter)
	{
		CGD_TRY
		{
			// 2) �þ �κб��� Reset�� �Ѵ�.
			for(; iter < new_end; ++iter)
			{
				this->m_alloc_val.construct(&(*iter), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for(iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy�� ȣ���Ѵ�.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// Throw) �ٽ� Thread!!!
			CGD_RETHROW;
		}
	}
	else
	{
		for(; new_end < iter ; ++new_end)
		{
			this->m_alloc_val.destroy(&(*new_end));
		}
	}

	// 3) Size�� ���� �����Ѵ�.
	this->m_ptr_last = this->m_ptr_first + _new_size;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::clear() noexcept
{
	// 1) destruct
	for(iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		this->m_alloc_val.destroy(&(*iter));
	}

	// 2) Size�� 0���� �Ѵ�. (Last�� First�� ����� �װ� 0���� ����� ���̴�.)
	this->m_ptr_last = this->m_ptr_first;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::find(const_reference _val) noexcept
{
	// 1) ó������ �������� ����Ÿ�� ã�´�.
	iterator iter = this->begin();
	for(; iter != this->end(); ++iter)
	{
		CGD_BREAK_IF(*iter == _val);
	}

	// return) ����� return�Ѵ�.
	return iter;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back(const TDATA& _val)
{
	// check) ��á���� �ø���.
	if(m_ptr_last==m_ptr_end)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity();

		// - ũ�⸦ 2��� �ø���.
		new_capacity = new_capacity * 2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		new_capacity = (new_capacity>CONTAINER_MIN) ? new_capacity : CONTAINER_MIN;

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		this->reserve(new_capacity);
	}

	// 1) Push�ϱ�.
	{
		// - Construct�� ȣ���Ѵ�.
		this->m_alloc_val.construct(this->m_ptr_last, _val);

		// - Last ������ ������Ŵ.
		++this->m_ptr_last;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back(TDATA&& _val)
{
	// check) ��á���� �ø���.
	if(this->m_ptr_last == m_ptr_end)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity();

		// - ũ�⸦ 2��� �ø���.
		new_capacity = new_capacity * 2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		new_capacity = (new_capacity > CONTAINER_MIN) ? new_capacity : CONTAINER_MIN;

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		this->reserve(new_capacity);
	}

	// 2) Construct�� ȣ���Ѵ�.
	this->m_alloc_val.construct(this->m_ptr_last, std::forward<TDATA>(_val));

	// 3) Last ������ ������Ŵ.
	++this->m_ptr_last;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back()
{
	// check) ��á���� �ø���.
	if(m_ptr_last==m_ptr_end)
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity();

		// - ũ�⸦ 2��� �ø���.
		new_capacity = new_capacity*2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		this->reserve(new_capacity);
	}

	// 1) Construct�� ȣ���Ѵ�.
	this->m_alloc_val.construct(this->m_ptr_last, TDATA());

	// 2) Last ������ ������Ŵ.
	++this->m_ptr_last;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::pop_back()
{
	// check) Empty�˻�.
#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ� �������� �ʰ� �׳� ������.
	if(this->empty())
		return;
#endif

	// 1) pop�ϱ�.(ũ�⸦ ���δ�)
	--this->m_ptr_last;

	// 2) destroy�� ȣ���Ѵ�.
	this->m_alloc_val.destroy(this->m_ptr_last);
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::assign(size_type _count , const TDATA& _val)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// 1. ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�? _size�� _capacity���� ũ�ų� ������ vector�� ũ�⸦ ���δ�.)
	if(this->remained()<_count )
	{
		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity() + _count ;

		// - ũ�⸦ 2��� �ø���.
		new_capacity = new_capacity * 2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		this->reserve(new_capacity);
	}

	// 2) ���� �ִ´�.
	{
		// - ������� First�� Last�� ����Ű�� Iterator
		iterator iter = this->end();
		iterator new_end(this->end() + _count);

		CGD_TRY
		{
			// - ���� ������ Construct�Լ��� �����Ѵ�.
			for (; iter != new_end; ++iter)
			{
				this->m_alloc_val.construct(&(*iter), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for (iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy�� ȣ���Ѵ�.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// throw) �ٽ� Thread!!!
			CGD_RETHROW;
		}
	}

	// 3) Last���� �ٲ۴�.
	this->m_ptr_last += _count;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template <class ITERATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::assign(ITERATOR _first, ITERATOR _last)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) 
	CGDASSERT_ERROR(_last.m_ptr_last > _first.m_ptr_last);

	// 1) size�� ���Ѵ�.
	size_type count = _last - _first;

	// check) count�� 0���̸� �׳� ������.
	CGD_RETURN_IF(count == 0);

	// 2) ���� ���� �˻�.(���԰����� ������ ������ ���� �ֳ�?)
	if(this->remained() < count)
	{
		// _size�� _capacity���� ũ�ų� ������ fast_vector�� ũ�⸦ ���δ�.

		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity() + count;

		// - ũ�⸦ 2��� �ø���.
		new_capacity = new_capacity * 2;

		// - ���Ϻ��� ������ ���Ϸ� �����.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - ���ο� Capacity�� ũ�⸦ �����Ѵ�.
		this->reserve(new_capacity);
	}

	// 3) ���� �ִ´�.
	{
		// 1) ������� First�� Last�� ����Ű�� Iterator
		iterator iter = this->end();

		CGD_TRY
		{
			// 2) ���� ������ Construct�Լ��� �����Ѵ�.
			for (; _first != _last; ++_first,++iter)
			{
				this->m_alloc_val.construct(&(*iter), *_first);
			}
		}
		CGD_CATCH_ALL
		{
			// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for (iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy�� ȣ���Ѵ�.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// re-throw)
			CGD_RETHROW;
		}
	}

	// 4) Last���� �ٲ۴�.
	this->m_ptr_last += count;
}


template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<class TITERATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);


	// 1) count�� �����´�.
	const size_type nCount = _last - _first;

	// 2) Insert�� �����ϱ� ���� ������ ������ ����. (_size�� _capacity���� ũ�ų� ������ fast_vector�� ũ�⸦ ���δ�.)
	if(remained()>=nCount)
	{
		// 3) ���� �ִ´�.(size�� �ڵ� ����...)
		TDATA* psource = const_cast<TDATA*>(_where.m_ptr_last);
		TDATA* pDest = const_cast<TDATA*>(_where.m_ptr_last + nCount);
		size_type nMovCount = this->m_ptr_last - psource;

		// 4) Array�� ��ĭ�� �ڷ� �̷��.
		memmove(pDest, psource, sizeof(TDATA) * nMovCount);

		// 5) m_ptr_last�� ������Ų��.
		this->m_ptr_last += nCount;
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t differ = _where.m_ptr_last - this->m_ptr_first;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity() + nCount;

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(new_capacity + (new_capacity/2), _where, nCount);

		// - Iterator�� ���� �����Ѵ�.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 3) Insert�Ѵ�.
	{
		// For Exception) ���� Roll back�� ���� ������ ���´�.
		iterator iter_roll(const_cast<TDATA*>(_where.m_ptr_last));

		CGD_TRY
		{
			// 2) ���� ������ Construct�Լ��� �����Ѵ�.
			for (; _first != _last; ++_first,++_where)
			{
				this->m_alloc_val.construct(const_cast<TDATA*>(_where.m_ptr_last), *_first);
			}
		}
		CGD_CATCH_ALL
		{
			// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
			this->m_ptr_last -= nCount;

			// - �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for (iterator iter = this->end(); iter != _where; ++iter)
			{
				// - Destroy�� ȣ���Ѵ�.
				this->m_alloc_val.destroy(&(*iter));
			}

			// - ������Ҵ� Room�� �ٽ� �����.
			for (auto iter_dest = &(*iter_roll), iter_source = &(*(iter_roll + nCount)); iter_dest != this->m_ptr_last; ++iter_dest, ++iter_source)
			{
				*iter_dest = std::forward<TDATA>(*iter_source);
			}

			// Throw) �ٽ� Thread!!!
			CGD_RETHROW;
		}
	}
}


//-----------------------------------------------------------------
// CGDK::fast_vector::Insert
//
//  _where�� ���ʿ� _count ��ŭ _val���� �����ϴ� �Լ��̴�.
// 
//  fast_vector�� Insert�� reserved�� ������ ���ڶ��� std::fast_vector�� �ϴ�
// reserve�� �����Ѵ�. �̶� ���ο� buffer�� ���� ������ �����Ѵ�.
// �׸��� ���� �ٽ� insert�� ���� ���縦 �ؼ� �߰��� �ڸ��� �����
// �� �ڸ��� �����Ѵ�.
//  CGDK������ �̷� �κ��� �����Ͽ� ���� insert�� �ٽ� reserve�ϰ� 
// �ȴٸ� reserve�� ���� ���� �Ҵ���� buffer�� insert�� ������
// �̸� ������� ���縦 �Ѵ�. �� �� �� �ڸ��� insert�� ������ 
// ������ �ִ´�.
// �̷��� �ϸ� insert�� �������� ���縦 �ϴ� ������ �ּ�ȭ�Ҽ� �ִ�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, int _count , const TDATA& _val)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDSSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert�� �����ϱ� ���� ������ ������ ����. (_size�� _capacity���� ũ�ų� ������ fast_vector�� ũ�⸦ ���δ�.)
	if(this->remained() >= (size_type)_count )
	{
		// - ���� �ִ´�.(size�� �ڵ� ����...)
		TDATA* psource = const_cast<TDATA*>(&(*_where));
		TDATA* pDest = const_cast<TDATA*>(&(*(_where + _count )));
		size_type nCount = this->m_ptr_last - psource;

		// - Array�� ��ĭ�� �ڷ� �̷��.
		memmove(pDest, psource, sizeof(TDATA) * nCount);

		// - m_ptr_last�� ������Ų��.
		this->m_ptr_last += _count ;
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = capacity()+_count ;

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(new_capacity + (new_capacity/2), _where, _count );

		// - Iterator�� ���� �����Ѵ�.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 2) Insert�Ѵ�.
	{
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
		// for exception) ���� Roll back�� ���� ������ ���´�.
		iterator iter_roll = _where;
	#endif

		CGD_TRY
		{
			// - ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
			const_iterator iter_end = _where + _count;
			for(;_where != iter_end; ++_where)
			{
				// - Construct�� ȣ���Ѵ�.
				this->m_alloc_val.construct(const_cast<TDATA*>(_where.m_ptr_last), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
			this->m_ptr_last -= _count;

			// - �ٽ� ����� ���� �ּҿ� ������ ����Ѵ�.
			TDATA* psource = &(*(iter_roll + _count ));
			TDATA* pDest = &(*iter_roll);
			size_type nMovCount = this->m_ptr_last - pDest;

			// �����ߴ� ���� �ٽ� �� Destroy�Ѵ�.
			for(;iter_roll != _where; ++iter_roll)
			{
				// - Destroy�� ȣ���Ѵ�.
				this->m_alloc_val.destroy(&*iter_roll);
			}

			// - ������Ҵ� Room�� �ٽ� �����.
			memcpy(pDest, psource, (unsigned long)sizeof(TDATA) * nMovCount);

			// Throw) �ٽ� Thread!!!
			CGD_RETHROW;
		}
	}
}


//-----------------------------------------------------------------
// ����) CGDK::fast_vector::Insert
//
//  _where�� ���ʿ� _val �ϳ��� �����ϴ� �Լ��̴�.
// 
// fast_vector�� Insert�� reserved�� ������ ���ڶ��� std::fast_vector�� �ϴ�
// reserve�� �����Ѵ�. �̶� ���ο� buffer�� ���� ������ �����Ѵ�.
// �׸��� ���� �ٽ� insert�� ���� ���縦 �ؼ� �߰��� �ڸ��� �����
// �� �ڸ��� �����Ѵ�.
//  CGDK������ �̷� �κ��� �����Ͽ� ���� insert�� �ٽ� reserve�ϰ� 
// �ȴٸ� reserve�� ���� ���� �Ҵ���� buffer�� insert�� ������
// �̸� ������� ���縦 �Ѵ�. �� �� �� �ڸ��� insert�� ������ 
// ������ �ִ´�.
// �̷��� �ϸ� insert�� �������� ���縦 �ϴ� ������ �ּ�ȭ�Ҽ� �ִ�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, const TDATA& _val)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert�� �����ϱ� ���� ������ ������ ����.(_size�� _capacity���� ũ�ų� ������ fast_vector�� ũ�⸦ ���δ�.)
	if(this->m_ptr_end != this->m_ptr_last)
	{
		// - Array�� ��ĭ�� �ڷ� �̷��.
		memmove((void*)(_where.m_ptr_last+1), (void*)_where.m_ptr_last, (this->m_ptr_last - _where.m_ptr_last)*sizeof(TDATA));

		// - m_ptr_last�� ������Ų��.
		++this->m_ptr_last;
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity();

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(new_capacity + (new_capacity/2), _where, 1);

		// - Iterator�� ���� �����Ѵ�.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 2) Insert�Ѵ�.
	CGD_TRY
	{
		// - ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		this->m_alloc_val.construct((TDATA*)_where.m_ptr_last, _val);
	}
	CGD_CATCH_ALL
	{
		// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
		--this->m_ptr_last;

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_where.m_ptr_last, (void*)(_where.m_ptr_last+1), (unsigned long)(m_ptr_last-_where.m_ptr_last)*sizeof(TDATA));

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator((TDATA*)_where.m_ptr_last);
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, TDATA&& _val)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);


	// 1) Insert�� �����ϱ� ���� ������ ������ ����.(_size�� _capacity���� ũ�ų� ������ fast_vector�� ũ�⸦ ���δ�.)
	if(m_ptr_end != m_ptr_last)
	{
		// - Array�� ��ĭ�� �ڷ� �̷��.
		memmove((void*)(_where.m_ptr_last+1), (void*)_where.m_ptr_last, (this->m_ptr_last - _where.m_ptr_last)*sizeof(TDATA));

		// - m_ptr_last�� ������Ų��.
		++this->m_ptr_last;
	}
	else
	{
		// - ���� �Ҵ������ Iterator�� ��ȿȭ�ǹǷ� �׿� ���� ��� �ؾ��Ѵ�.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - ���� ũ�⸦ ���Ѵ�.
		size_type new_capacity = this->capacity();

		// - ���� ũ���� 1.5��� �ø���.(�ø��鼭 �׸�ŭ�� ������ ����.
		_Expand(new_capacity+(new_capacity/2), _where, 1);

		// - Iterator�� ���� �����Ѵ�.
		_where = const_iterator(m_ptr_first+differ);
	}

	// 2) Insert�Ѵ�.
	CGD_TRY
	{
		// - ��� �ڸ��� Construct�� ȣ���� ���� �����Ѵ�.
		this->m_alloc_val.construct((TDATA*)_where.m_ptr_last, std::forward<TDATA>(_val));
	}
	CGD_CATCH_ALL
	{
		// - roll back�� ���� �ٽ� PtrLast�� ���δ�.
		--this->m_ptr_last;

		// - ������Ҵ� Room�� �ٽ� �����.
		memcpy((void*)_where.m_ptr_last, (void*)(_where.m_ptr_last+1), (unsigned long)(this->m_ptr_last - _where.m_ptr_last) * sizeof(TDATA));

		// Throw) �ٽ� Thread!!!
		CGD_RETHROW;
	}

	// return) �ǵ�����.(Insert�� ��ġ�� Iterator�� �����ش�.)
	return iterator((TDATA*)_where.m_ptr_last);
}


//-----------------------------------------------------------------
// CGDK::fast_vector::erase
//
//  _where��ġ�� Item�� ����� �Լ��̴�.
//
// return���� ���� ���� Item�� Iterator�� �����ش�.
// (Loop���� �� ������� erase()�� �� �� return�Ǿ� ���ƿ��� itreator��
// �ٽ� �޾� end()���� ������ ��� ���������� �ȴ�.
// 
//  ������ std::fast_vector�� �������� ����� �� ���Ŀ� buffer�� ���ܾ�
// �ϴµ� �̶� memcpy�� ����Ͽ� �����.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::erase(const_iterator _where)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last < this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_where.m_ptr_last <= this->m_ptr_last);

	// check) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(this->size() > 0);

	// 1) Last�� ���δ�.
	--this->m_ptr_last;

	// 2) ��ĭ�� ������ ����.
	for(auto iter = _where.m_ptr_last; iter != m_ptr_last; ++iter)
	{
		*iter = std::forward<TDATA>(*(iter + 1));
	}

	// 3) ���� ������ �����͸� �Ҹ��Ų��.
	this->m_alloc_val.destroy(this->m_ptr_last);

	// return)
	return iterator((TDATA*)_where.m_ptr_last);
}

//-----------------------------------------------------------------
// CGDK::fast_vector::erase
//
//  _first���� ���� �����ؼ� _last�� ���ʱ��� Item���� �����.
//
// return���� _last�� Iterator�� ���� ���̴�.
// 
//  ������ std::fast_vector�� �������� ����� �� ���Ŀ� buffer�� ���ܾ�
// �ϴµ� �̶� memcpy�� ����Ͽ� �����.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::erase(const_iterator _first, const_iterator _last)
{
	// ����) CGDK::fast_vector���� max_size()�˻�� �������� �ʽ��ϴ�.

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_first.m_ptr_last >= this->m_ptr_first && _first.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_first.m_ptr_last <= this->m_ptr_last);

	// check) Iterator�� ���� Last������ �˻��Ѵ�.
	CGDASSERT_ERROR(_last.m_ptr_last >= this->m_ptr_first && _last.m_ptr_last <= this->m_ptr_end);

	// check) Iterator�� ���� Container�� ������ �˻��Ѵ�.
	CGDASSERT_ERROR(_last.m_ptr_last <= this->m_ptr_last);

	// check) _size�� 0���� �۰ų� ������ ���̻� pop�� �Ҽ��� ����!
	CGDASSERT_ERROR(this->size() > 0);
	
	// 1) �̵��� ���� Source�� Dest�� ���� �����Ѵ�.
	auto iter_source = _last.m_ptr_last;
	auto iter_dest = _first.m_ptr_last;

	// 2) �����͸� �����.
	for (; iter_source != this->m_ptr_last; ++iter_source, ++iter_dest)
	{
		*iter_dest = std::forward<TDATA>(*iter_source);
	}

	// 3) Last�� �ֱ� ���� �ӽ÷� ������ ���´�.
	auto ptr_last = iter_dest;

	// 4) ���� ������ Data�� ���ؼ��� Destroy�� �Ѵ�.
	for (; iter_dest < this->m_ptr_last; ++iter_dest)
	{
		this->m_alloc_val.destroy(&(*iter_dest));
	}

	// 5) Last�� �ٽ� �����Ѵ�.
	this->m_ptr_last = ptr_last;

	// return)
	return iterator(_last.m_ptr_last);
}


//-----------------------------------------------------------------
// CGDK::fast_vector::swap
//
//  _right�� fast_vector�� ��ä�� �ٲ۴�.
//
// allocator�� ���� ������� �׳� �˸��̸� �ٲٰ� ���࿡ �ٸ��ٸ�
// allocator���� ��ä�� �ٲ۴�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::swap(_mytype& _right)
{
	// check) ���� container�� �׳� return�Ѵ�.
	CGD_RETURN_IF(this == &_right);

	// 1) �Ѵ� �����Ҵ�� �����Ͷ�� �׳� swap�� �Ѵ�.
	if(this->is_own_data() == false && _right.is_own_data() == false)
	{
		CGD_SWAP(this->m_ptr_first, _right.m_ptr_first);
		CGD_SWAP(this->m_ptr_last, _right.m_ptr_last);
		CGD_SWAP(this->m_ptr_end, _right.m_ptr_end);
		CGD_SWAP(this->m_alloc_val, _right.m_alloc_val);
	}
	// 2) �����̶� ���� �����Ͷ�� ������ Move�Ѵ�.
	else
	{
		if(this->is_own_data() == false)
		{
			// ���� ���� �ȉ�.
			CGDASSERT_ERROR(false);
			//// 1) ���� ������ ����.
			//auto prtFirst = m_ptr_first;
			//auto prtLast = m_ptr_last;
			//auto ptrEnd = m_ptr_end;
			//auto allocVal = m_alloc_val;

			//// 2) ����
			//m_ptr_first = reinterpret_cast<TDATA*>(m_array);
			//m_ptr_last = m_ptr_first;
			//m_ptr_end = m_ptr_first + TSIZE;

			//// 3) 
			//m_ptr_first(), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array) + TSIZE)
		}
		else
		{
			// ���� ���� �ȉ�.
			CGDASSERT_ERROR(false);
		}

		// - �ӽ� Container�� �����Ѵ�.
		_mytype temp = _right;
		_right = *this;
		*this = temp;
	}
}


//-----------------------------------------------------------------
// CGDK::fast_vector::shrink_to_fit
//
//  max_size�� ������ size��ŭ�� ũ��� ���̴� �Լ��̴�.
//
// �������� swap()�� ����Ͽ� �����Ͽ����� ���⼭�� �׳� �Լ��� 
// �������ش�.
//
// shrink_to_fit�Լ��� ȣ���ϸ� ���� size()�� �µ��� ���� buffer�� �Ҵ��ϰ�
// �ű⿡ ���� Item���� memcpy�� ����� �����ϰ� ���� buffer��
// deallocate�Ѵ�.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::shrink_to_fit()
{
	// 1) Size�� ��´�.
	size_t temp_size = this->size();

	// check) �̹� size�� capacity�� ������ �׳� �ǵ�����.
	CGD_RETURN_IF(size() == this->capacity() || this->capacity() <= TSIZE);

	// check) m_ptr_first�� m_array�ϼ��� ����!
	CGDASSERT_ERROR(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array));

	// declare) 
	TDATA* temp_array;

	// 2) size�� �´� array�� ���� �Ҵ�޴´�.
	if(temp_size <= TSIZE)
	{
		temp_array = reinterpret_cast<TDATA*>(this->m_array);
		temp_size = TSIZE;
	}
	else
	{
		temp_array = this->m_alloc_val.allocate(size());
	}

	// 3) ���� array�� �Ҵ������Ѵ�.(size�� 0�̸� ���� ���� ������ �ʿ�� ����.)
	if(this->size() != 0)
	{
		// check) m_ptr_first�� 0�̾�� �ȵȴ�.
		CGDASSERT_ERROR(this->m_ptr_first != 0);

		// - �̵��Ѵ�.
		for (auto iter_dest = temp_array, iter_source = this->m_ptr_first; iter_source != this->m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - ���� �������� �Ҹ��ڸ� ȣ���Ѵ�.
		for (auto iter_destroy = m_ptr_first; iter_destroy != this->m_ptr_last; ++iter_destroy)
		{
			this->m_alloc_val.destroy(iter_destroy);
		}

		// - ������ data�� �����.
		if (m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) ���� �����Ѵ�.
	this->m_ptr_first = temp_array;
	this->m_ptr_end = temp_array+size();
	this->m_ptr_last = temp_array+temp_size;
}




}