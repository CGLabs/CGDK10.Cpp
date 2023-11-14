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
//     1) X:value_type		Contain에 담긴 값들의 형.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		순회할 때 사용되는 반복자.
//     5) X:const_iterator	순회할 때 사용되는 반복자(const형)
//     6) X:difference_type	두 iterator에 담김 값의 거리를 나타내는 타입.
//     7) X:size_type		X의 크기를 나타낼때 사용되는 형.
//
//  * Reversible Requirement
//     1) X::reverse_iterator 역순환 때 사용되는 반복자.
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

	// Allocator)
	typedef TALLOCATOR		allocator_type;

	// Self) 자기자신(표준 아님.)
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
//     2) X(a);				Copy Constrctor.(소요시간은 선형적)
//		  X u(a);
//     3) (&a)->~X();		Destructor.(소요시간은 선형적)
//     4) a.begin(); 		Container 순회에 사용할 시작과 끝 iterator 
//		  a.end();
//     5) a==b; a!=b;		Container 모든 원소 같으면 true.(소요시간 선형적)
//     6) a.size();			Container에 담김 원소의 갯수를 리턴한다.
//     7) a.max_size();		Container가 담을 수 있는 최대 원소 개수를 리턴한다.
//     8) a.empty();		Container가 비어 있는 경우라면 true를 리턴한다.
//     9) a<b; a>b; 		비교 연산(소요시간 선형적)
//		  a<=b; a>=b;
//    10) r=a;				Container 대입연산(소요시간 선형적)
//    11) a.swap(b);		동일한 타입의 두 커테이너를 서로 맞바꾼다.
//
//  * Reversible Requirement
//     1) a.rbegin(); 		반대방향 순회에 사용될 시작과 끝 iterator
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
//    1) X(n, t);			t의 복사본 n개로 구성된 Sequence를 생성한다.
//		 X a(n, t);	
//    2) X(i, j); 			구간[i,j]의 내용과 동일한 Sequence를 생성한다.
//		 X a(i, j);
//    3) a.insert(p,t);		p앞에 t의 복사본을 삽입한다. 리턴값은 삽입된
//							원소를 가리키는 반복자이다.
//    4) a.insert(p,n,t);	p앞에 t의 복사본 n개를 삽입한다.
//    5) a.insert(p,i,j);	p앞에 [i,j]에 담긴 원소들의 복사본을 삽입한다.
//							i,j는 반복자
//    6) a.erase(q);		q가 가리키는 원소를 삭제한다. 리턴값은 삭제되기
//							전에 q다음에 위치했던 원소를 가리키는 반복자
//    7) a.erase(q1,q2);	구간[q1,q2]에 포함된 원소들을 삭제한다. 리턴값은
//							삭제되기 전에 q2다음에 위치했던 원소를 가리키는
//							반복자.
//    8) a.clear();			컨테이너에 담긴 뭐든 원소를 삭제한다. 
//							a.erase(a.begin(), a.end())와 동일하다.
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
	TDATA*					m_ptr_first;		// Array의 처음 위치...
	TDATA*					m_ptr_last;		// Array에서 사용되고 있는 제일 끝~()
	TDATA*					m_ptr_end;		// Array할당받은 제일 끝~(reserved)

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
		// 1) 생성자
		const_iterator() noexcept {}
		explicit const_iterator(data_pointer _pnow) noexcept : m_ptr_last(_pnow)  {}

		// 2) 대입
		const_iterator&	operator=(const const_iterator& _right)  noexcept{ this->m_ptr_last=_right.m_ptr_last; return *this;}
		pointer			operator->() { return &**this;}
																		  
		// 3) 반복													    
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
																		  
		// 4) 비교													    
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
		// 1) 생성자
		iterator() noexcept {}
		iterator(const const_iterator& _copy) noexcept : m_ptr_last(_copy.m_ptr_last){}
		explicit iterator(pointer _now) noexcept : m_ptr_last(_now) {}

		// 2) 대입
		iterator&		operator=(const iterator& _right) noexcept { this->m_ptr_last=_right.m_ptr_last; return *this;}
		iterator&		operator=(const const_iterator& _right) noexcept { this->m_ptr_last=_right.m_ptr_last; return *this;}
		pointer			operator->() { return &**this;}
						operator const_iterator() const noexcept { return const_iterator(this->m_ptr_last);}
																		  
		// 3) 반복													    
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
																		  
		// 4) 비교													    
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
		// 1) 삽입해넣는다.
		this->insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(_mytype&& _right) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// declare) 데이터 크기를 얻는다.
		auto size_right = _right.size();

		// 1) 만약 TSIZE보다 크면 바로 Move하고 끝!
		if(size_right > TSIZE)
		{
			// - 그대로 복사한다.
			this->m_ptr_first = _right.m_ptr_first;
			this->m_ptr_last = _right.m_ptr_last;
			this->m_ptr_end = _right.m_ptr_end;
			this->m_alloc_val = _right.m_alloc_val;

			// - Right는 Reset!
			_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
		}
		else
		{
			// - 개별 데이터를 Move한다.
			auto iter_source = _right.m_ptr_first;
			auto iter_dest = this->m_ptr_first;
			for(; iter_source != _right.m_ptr_last; ++iter_source, ++iter_dest)
			{
				*iter_dest = std::forward<TDATA>(*iter_source);
			}

			// - Last를 설정한다.
			this->m_ptr_last = iter_dest;

			// - _right를 Clear한다.
			for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
			{
				_right.m_alloc_val.destroy(iter_destroy);
			}

			// - Right는 Reset!
			_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
			_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
		}
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count ) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) 크기를 조절한다.
		this->resize(_count);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count , const TDATA& _val) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		this->insert(this->begin(), _count , _val);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::fast_vector(size_type _count , const TDATA& _val, const TALLOCATOR& _Al) : 
m_ptr_first(reinterpret_cast<TDATA*>(m_array)), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array)+TSIZE)
{
	CGD_TRY
	{
		// 1) 삽입해넣는다.
		this->insert(this->begin(), _count , _val);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
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
		// 1) 삽입해넣는다.
		this->insert(this->begin(), _first, _last);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if (m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
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
		// 1) 삽입해넣는다.
		this->insert(this->begin(), _first, _last);
	}
	CGD_CATCH_ALL
	{
		// - 모두 지운다.
		this->clear();

		// - Deallocate한다.
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
fast_vector<TDATA, TSIZE, TALLOCATOR>::~fast_vector()
{
	// 1) 모두 지운다.
	this->clear();

	// 2) Deallocate한다.
	if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
	{
		this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(const _mytype& _right)
{
	// 1) 일단 모조리 다 지운다.
	this->clear();

	// 2) 삽입해넣는다.
	CGD_TRY
	{
		insert(this->begin(), _right.begin(), _right.end());
	}
	CGD_CATCH_ALL
	{
		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// return) 자기 자신 Return
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(_mytype&& _right)
{
	// declare) 데이터 크기를 얻는다.
	auto size_right = _right.size();

	// 1) 만약 TSIZE보다 크면 바로 Move하고 끝!
	if(size_right > TSIZE)
	{
		// - 먼저 기존 데이터를 clear한다.
		this->clear();

		// - 그대로 복사한다.
		this->m_ptr_first = _right.m_ptr_first;
		this->m_ptr_last = _right.m_ptr_last;
		this->m_ptr_end = _right.m_ptr_end;
		this->m_alloc_val = _right.m_alloc_val;

		// - Right는 Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
	}
	else
	{
		// - 먼저 기존 데이터를 clear한다.
		this->clear();

		// - 데이터를 Move한다.
		auto iter_source = _right.m_ptr_first;
		auto iter_dest = this->m_ptr_first;

		for(; iter_source!=_right.m_ptr_last; ++iter_source, ++iter_dest)
		{
			m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Last를 설정한다.
		this->m_ptr_last = iter_dest;

		// - _right를 Clear한다.
		for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
		{
			_right.m_alloc_val.destroy(iter_destroy);
		}

		// - Right는 Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
	}

	// return) 자기 자신 Return
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<size_t XSIZE, class XALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(const fast_vector<TDATA, XSIZE, XALLOCATOR>& _right)
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
	return *this;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<size_t XSIZE, class XALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::_mytype& fast_vector<TDATA, TSIZE, TALLOCATOR>::operator=(fast_vector<TDATA, XSIZE, XALLOCATOR>&& _right)
{
	// declare) 데이터 크기를 얻는다.
	auto size_right = _right.size();

	// 1) 만약 TSIZE보다 크면 바로 Move하고 끝!
	if(size_right>XSIZE && size_right>TSIZE)
	{
		// - 먼저 기존 데이터를 clear한다.
		clear();

		// - 그대로 복사한다.
		this->m_ptr_first = _right.m_ptr_first;
		this->m_ptr_last = _right.m_ptr_last;
		this->m_ptr_end = _right.m_ptr_end;
		this->m_alloc_val = _right.m_alloc_val;

		// - Right는 Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array)+TSIZE;
	}
	else 
	{
		// - 먼저 기존 데이터를 clear한다.
		clear();

		// - 기존 데이터를 Destroy한다.
		if(size_right > TSIZE)
		{
			// 1) Array를 설정한다.
			TDATA* temp_array = this->m_alloc_val.allocate(size_right);

			// check) Succeded in allocation?
			CGDASSERT_ERROR(temp_array != nullptr);

			// check) if fail to allocation, throw exception 
			CGD_THROW_IF(temp_array == nullptr, std::bad_alloc());

			this->m_ptr_first = temp_array;
			this->m_ptr_last = temp_array;
			this->m_ptr_end = temp_array + size_right;
		}

		// - 데이터를 Move한다.
		auto iter_source = _right.m_ptr_first;
		auto iter_dest = this->m_ptr_first;

		for(; iter_source!=_right.m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Last를 설정한다.
		this->m_ptr_last = iter_dest;

		// - _right를 Clear한다.
		for (auto iter_destroy = _right.m_ptr_first; iter_destroy != _right.m_ptr_last; ++iter_destroy)
		{
			_right.m_alloc_val.destroy(iter_destroy);
		}

		// - Right는 Reset
		_right.m_ptr_first = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_last = reinterpret_cast<TDATA*>(_right.m_array);
		_right.m_ptr_end = reinterpret_cast<TDATA*>(_right.m_array) + TSIZE;
	}

	// return) 자기 자신 Return
	return	*this;
}

// 비교함수들
template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator==(const _mytype& _right) const
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return (iter_dest==_right.end());

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator!=(const _mytype& _right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return (iter_dest!=_right.end());

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator<(const _mytype& _right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

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

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator>(const _mytype& _right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return false;

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return true;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
		{
			return (*iter_src > *iter_dest);
		}

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator<=(const _mytype& _right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src = this->begin();
	typename _mytype::iterator iter_dest = _right.begin();

	for(;;)
	{
		// check) Src가 끝인가???
		if(iter_src == this->end())
			return true;

		// check) Dst가 끝인가?
		if(iter_dest == this->end())
			return false;

		// 2) 만약 Src와 Dst가 같지 않으면 바로 true리턴!
		if(*iter_src != *iter_dest)
			return (*iter_src < *iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
bool fast_vector<TDATA, TSIZE, TALLOCATOR>::operator>=(const _mytype& _right) const	
{
	// 1) 처음부터 찾기 위해 준비한다.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dest = _right.begin();

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
			return (*iter_src>*iter_dest);

		// 3) 다음값~
		++iter_src;
		++iter_dest;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at(size_type _pos)
{
	// check) _pos is greater than 0 and less than size()
	CGD_THROW_IF(_pos < 0 || _pos >= this->size(), std::out_of_range("CGDK Exception: Out of range ('reference fast_vector<TDATA, TSIZE, TALLOCATOR>::at')"))

	// 1) 값을 읽어서 되돌린다.
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
// reserve() 함수.
//
// _count 만큼 buffer를 미리 확보하는 함수이다.
//  만약, _count 가 현재 reserve된 크기보다 작을 경우 아무런 동작을
// 수행하지 않을 것이다.
//  _count 가 현재 Reserve된 공간보다 클 경우 _count 만큼으로 확장
// 한다.
// 이 함수 수행해 size()는 변화가  없지만 max_size()는 변할수 있다.
//
//  이때, 새로운 크기의 새로운 buffer를 allocator로부터 할당을
// 받으며 기존의 buffer는 deallocate한다. 
// 기존에 저장되어 있던 data들은 새로 할당받은 buffer의 같은 위치로 
// 복사가 행해진다.(단 constructor는 호출되지 않는다.)
//
//  사용될 최대 갯수를 알게 될 경우 미리 reserve해 놓으면 다시 할당 
// 함으로 인한 추가적으로 들어가는 부하를 줄일 수 있다.
//  std::fast_vector의 경우 이 것을 for_loop문을 통해 복사하였지면 여기서
// 는 memcpy를 통해 수행된다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::reserve(size_type _count )
{
	// check) If _count  is less than capacity() or _count  is equare or less than TSIZE, it is return
	if(_count <= this->capacity() || _count <= TSIZE)
		return;

	// 1) 새로운 array를 할당받는다. (Array를 설정한다.)
	TDATA* temp_array = this->m_alloc_val.allocate(_count ); 

	// 2) 새로운 크기를 얻는다.
	size_type now_size = this->size();

	// 3) 기존 array를 할당해제한다. (size가 0이면 이전 값을 복사할 필요는 없다.)
	if(now_size != 0 && temp_array != this->m_ptr_first)
	{
		// - 메모리를 복사한다.
		for(auto iter_source = this->m_ptr_first, iter_dest = temp_array; iter_source != m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - 기존의 data를 지운다.(Destroy는 호출하지 않는다.)
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) 새로 설정한다.
	this->m_ptr_first = temp_array;
	this->m_ptr_last = temp_array + now_size;
	this->m_ptr_end = temp_array + _count ;
}

//-----------------------------------------------------------------
// _Expand 함수.
//
// 이 함수는 내부에서만 사용되는 함수이다.
// reserve의 변형판으로 똑같이 크기를 확장하는 함수지만 다른 점은  
// 확장하는 과정에서 기존의 data를 복사해 놓을 때 _where로부터
// _room만큼의 빈자리를 만든다는 것이다. 
// 주로 Insert를 수행하는 중 Expand가 일어날 경우 사용된다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::_Expand(size_type _count , const_iterator _where, size_type _room)
{
	// check) capacity가 이미 _count 보다 크면 그냥 되돌린다.
	CGD_RETURN_IF(_count  <= this->capacity() || _count  <= TSIZE);

	// 1) 새로운 array를 할당받는다. (Array를 설정한다.)
	TDATA* temp_array = this->m_alloc_val.allocate(_count ); 

	// check) Succeded in allocation?
	CGDASSERT_ERROR(temp_array != nullptr);

	// check) if fail to allocation, throw exception 
	CGD_THROW_IF(temp_array == nullptr, std::bad_alloc());
	
	// 2) 기존 size를 얻어놓는다.
	size_type now_size = this->size();

	// 3) 기존 array를 할당해제한다. (size가 0이면 이전 값을 복사할 필요는 없다.)
	if(now_size != 0)
	{
		// check) m_ptr_first가 0이어서는 안된다.
		CGDASSERT_ERROR(this->m_ptr_first != 0);

		// check) m_ptr_first가 0이어서는 안된다.
		CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

		// - 전송할 Source
		auto iter_source = this->m_ptr_first;
		auto iter_dest = temp_array;

		// - 앞부분을 복사해 옮긴다.
		for(; iter_source!=_where.m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - Room만큼 띄운다.
		iter_dest		+= _room;
		for(; iter_source!=m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - 기존 데이터의 소멸자를 호출한다.
		for (auto iter_destroy=m_ptr_first; iter_destroy!=m_ptr_last; ++iter_destroy)
		{
			this->m_alloc_val.destroy(iter_destroy);
		}

		// - 기존의 할당받은 Memory Chunk를 deallocate한다.(Destroy는 호출하지 않는다.)
		if (this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) 새로 설정한다.
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
	// 1) reserve된 크기 확인.(최대크기보다 크면 크기를 늘린다.)
	if(_new_size > this->capacity())
	{
		this->reserve(_new_size);
	}

	// 2) 크기 조정하기.
	iterator iter = this->end();
	iterator new_end(this->begin() + _new_size);

	if(new_end > iter)
	{
		CGD_TRY
		{
			// 2) 늘어난 부분까지 Reset을 한다.
			for(; iter < new_end; ++iter)
			{
				this->m_alloc_val.construct(&(*iter), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - 생성했던 것을 다시 다 Destroy한다.
			for(iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy를 호출한다.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// Throw) 다시 Thread!!!
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

	// 3) Size를 새로 설정한다.
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

	// 2) Size를 0으로 한다. (Last를 First로 만들면 그게 0으로 만드는 것이다.)
	this->m_ptr_last = this->m_ptr_first;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::find(const_reference _val) noexcept
{
	// 1) 처음부터 돌려가며 데이타를 찾는다.
	iterator iter = this->begin();
	for(; iter != this->end(); ++iter)
	{
		CGD_BREAK_IF(*iter == _val);
	}

	// return) 결과를 return한다.
	return iter;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back(const TDATA& _val)
{
	// check) 꽉찼으면 늘린다.
	if(m_ptr_last==m_ptr_end)
	{
		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity();

		// - 크기를 2배로 늘린다.
		new_capacity = new_capacity * 2;

		// - 최하보다 작으면 최하로 맞춘다.
		new_capacity = (new_capacity>CONTAINER_MIN) ? new_capacity : CONTAINER_MIN;

		// - 새로운 Capacity를 크기를 예약한다.
		this->reserve(new_capacity);
	}

	// 1) Push하기.
	{
		// - Construct를 호출한다.
		this->m_alloc_val.construct(this->m_ptr_last, _val);

		// - Last 포인터 증가시킴.
		++this->m_ptr_last;
	}
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back(TDATA&& _val)
{
	// check) 꽉찼으면 늘린다.
	if(this->m_ptr_last == m_ptr_end)
	{
		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity();

		// - 크기를 2배로 늘린다.
		new_capacity = new_capacity * 2;

		// - 최하보다 작으면 최하로 맞춘다.
		new_capacity = (new_capacity > CONTAINER_MIN) ? new_capacity : CONTAINER_MIN;

		// - 새로운 Capacity를 크기를 예약한다.
		this->reserve(new_capacity);
	}

	// 2) Construct를 호출한다.
	this->m_alloc_val.construct(this->m_ptr_last, std::forward<TDATA>(_val));

	// 3) Last 포인터 증가시킴.
	++this->m_ptr_last;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::push_back()
{
	// check) 꽉찼으면 늘린다.
	if(m_ptr_last==m_ptr_end)
	{
		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity();

		// - 크기를 2배로 늘린다.
		new_capacity = new_capacity*2;

		// - 최하보다 작으면 최하로 맞춘다.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		this->reserve(new_capacity);
	}

	// 1) Construct를 호출한다.
	this->m_alloc_val.construct(this->m_ptr_last, TDATA());

	// 2) Last 포인터 증가시킴.
	++this->m_ptr_last;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::pop_back()
{
	// check) Empty검사.
#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty를 Check를 하지 않을 경우에 Debug 모드일때 Assert를 띄워준다.
	//   (Release Mode일 때는 아무일도 동작하지 않는다.)
	CGDASSERT_ERROR(!empty());
#else
	// Empty를 Check를 할 경우 Empty를 Check하고 비어 있을 경우 아무 동작하지 않고 그냥 끝낸다.
	if(this->empty())
		return;
#endif

	// 1) pop하기.(크기를 줄인다)
	--this->m_ptr_last;

	// 2) destroy를 호출한다.
	this->m_alloc_val.destroy(this->m_ptr_last);
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::assign(size_type _count , const TDATA& _val)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// 1. 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나? _size가 _capacity보다 크거나 같으면 vector의 크기를 늘인다.)
	if(this->remained()<_count )
	{
		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity() + _count ;

		// - 크기를 2배로 늘린다.
		new_capacity = new_capacity * 2;

		// - 최하보다 작으면 최하로 맞춘다.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		this->reserve(new_capacity);
	}

	// 2) 값을 넣는다.
	{
		// - 집어넣을 First와 Last를 가리키는 Iterator
		iterator iter = this->end();
		iterator new_end(this->end() + _count);

		CGD_TRY
		{
			// - 값을 넣으며 Construct함수를 수행한다.
			for (; iter != new_end; ++iter)
			{
				this->m_alloc_val.construct(&(*iter), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - 생성했던 것을 다시 다 Destroy한다.
			for (iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy를 호출한다.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// throw) 다시 Thread!!!
			CGD_RETHROW;
		}
	}

	// 3) Last값을 바꾼다.
	this->m_ptr_last += _count;
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
template <class ITERATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::assign(ITERATOR _first, ITERATOR _last)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) 
	CGDASSERT_ERROR(_last.m_ptr_last > _first.m_ptr_last);

	// 1) size를 구한다.
	size_type count = _last - _first;

	// check) count가 0개이면 그냥 끝낸다.
	CGD_RETURN_IF(count == 0);

	// 2) 남은 공간 검사.(삽입가능할 정도의 공간이 남아 있나?)
	if(this->remained() < count)
	{
		// _size가 _capacity보다 크거나 같으면 fast_vector의 크기를 늘인다.

		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity() + count;

		// - 크기를 2배로 늘린다.
		new_capacity = new_capacity * 2;

		// - 최하보다 작으면 최하로 맞춘다.
		new_capacity = CGD_MAX(new_capacity, CONTAINER_MIN);

		// - 새로운 Capacity를 크기를 예약한다.
		this->reserve(new_capacity);
	}

	// 3) 값을 넣는다.
	{
		// 1) 집어넣을 First와 Last를 가리키는 Iterator
		iterator iter = this->end();

		CGD_TRY
		{
			// 2) 값을 넣으며 Construct함수를 수행한다.
			for (; _first != _last; ++_first,++iter)
			{
				this->m_alloc_val.construct(&(*iter), *_first);
			}
		}
		CGD_CATCH_ALL
		{
			// - 생성했던 것을 다시 다 Destroy한다.
			for (iterator iter_roll = this->end(); iter_roll != iter; ++iter_roll)
			{
				// - Destroy를 호출한다.
				this->m_alloc_val.destroy(&(*iter_roll));
			}

			// re-throw)
			CGD_RETHROW;
		}
	}

	// 4) Last값을 바꾼다.
	this->m_ptr_last += count;
}


template <class TDATA, size_t TSIZE, class TALLOCATOR>
template<class TITERATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);


	// 1) count를 얻어놓는다.
	const size_type nCount = _last - _first;

	// 2) Insert를 수행하기 위해 삽입할 공간을 비운다. (_size가 _capacity보다 크거나 같으면 fast_vector의 크기를 늘인다.)
	if(remained()>=nCount)
	{
		// 3) 값을 넣는다.(size도 자동 증가...)
		TDATA* psource = const_cast<TDATA*>(_where.m_ptr_last);
		TDATA* pDest = const_cast<TDATA*>(_where.m_ptr_last + nCount);
		size_type nMovCount = this->m_ptr_last - psource;

		// 4) Array를 한칸씩 뒤로 미룬다.
		memmove(pDest, psource, sizeof(TDATA) * nMovCount);

		// 5) m_ptr_last를 증가시킨다.
		this->m_ptr_last += nCount;
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t differ = _where.m_ptr_last - this->m_ptr_first;

		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity() + nCount;

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(new_capacity + (new_capacity/2), _where, nCount);

		// - Iterator를 새로 설정한다.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 3) Insert한다.
	{
		// For Exception) 추후 Roll back을 위해 저장해 놓는다.
		iterator iter_roll(const_cast<TDATA*>(_where.m_ptr_last));

		CGD_TRY
		{
			// 2) 값을 넣으며 Construct함수를 수행한다.
			for (; _first != _last; ++_first,++_where)
			{
				this->m_alloc_val.construct(const_cast<TDATA*>(_where.m_ptr_last), *_first);
			}
		}
		CGD_CATCH_ALL
		{
			// - roll back을 위해 다시 PtrLast를 줄인다.
			this->m_ptr_last -= nCount;

			// - 생성했던 것을 다시 다 Destroy한다.
			for (iterator iter = this->end(); iter != _where; ++iter)
			{
				// - Destroy를 호출한다.
				this->m_alloc_val.destroy(&(*iter));
			}

			// - 비워놓았던 Room을 다시 땡긴다.
			for (auto iter_dest = &(*iter_roll), iter_source = &(*(iter_roll + nCount)); iter_dest != this->m_ptr_last; ++iter_dest, ++iter_source)
			{
				*iter_dest = std::forward<TDATA>(*iter_source);
			}

			// Throw) 다시 Thread!!!
			CGD_RETHROW;
		}
	}
}


//-----------------------------------------------------------------
// CGDK::fast_vector::Insert
//
//  _where의 앞쪽에 _count 만큼 _val값을 삽입하는 함수이다.
// 
//  fast_vector의 Insert시 reserved된 공간이 모자랄때 std::fast_vector는 일단
// reserve를 수행한다. 이때 새로운 buffer로 기존 내용을 복사한다.
// 그리고 나서 다시 insert를 위해 복사를 해서 중간에 자리를 비운후
// 그 자리에 복사한다.
//  CGDK에서는 이런 부분을 개선하여 만약 insert시 다시 reserve하게 
// 된다면 reserve로 인해 새로 할당받은 buffer에 insert될 공간을
// 미리 비워놓고 복사를 한다. 그 후 그 자리에 insert한 내용을 
// 복사해 넣는다.
// 이렇게 하면 insert시 이중으로 복사를 하는 현상을 최소화할수 있다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, int _count , const TDATA& _val)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDSSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert를 수행하기 위해 삽입할 공간을 비운다. (_size가 _capacity보다 크거나 같으면 fast_vector의 크기를 늘인다.)
	if(this->remained() >= (size_type)_count )
	{
		// - 값을 넣는다.(size도 자동 증가...)
		TDATA* psource = const_cast<TDATA*>(&(*_where));
		TDATA* pDest = const_cast<TDATA*>(&(*(_where + _count )));
		size_type nCount = this->m_ptr_last - psource;

		// - Array를 한칸씩 뒤로 미룬다.
		memmove(pDest, psource, sizeof(TDATA) * nCount);

		// - m_ptr_last를 증가시킨다.
		this->m_ptr_last += _count ;
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - 현재 크기를 구한다.
		size_type new_capacity = capacity()+_count ;

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(new_capacity + (new_capacity/2), _where, _count );

		// - Iterator를 새로 설정한다.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 2) Insert한다.
	{
	#ifndef _CGD_NO_EXCEPTION_GUARANTEE
		// for exception) 추후 Roll back을 위해 저장해 놓는다.
		iterator iter_roll = _where;
	#endif

		CGD_TRY
		{
			// - 비운 자리에 Construct를 호출해 값을 복사한다.
			const_iterator iter_end = _where + _count;
			for(;_where != iter_end; ++_where)
			{
				// - Construct를 호출한다.
				this->m_alloc_val.construct(const_cast<TDATA*>(_where.m_ptr_last), _val);
			}
		}
		CGD_CATCH_ALL
		{
			// - roll back을 위해 다시 PtrLast를 줄인다.
			this->m_ptr_last -= _count;

			// - 다시 땡기기 위해 주소와 갯수를 계산한다.
			TDATA* psource = &(*(iter_roll + _count ));
			TDATA* pDest = &(*iter_roll);
			size_type nMovCount = this->m_ptr_last - pDest;

			// 생성했던 것을 다시 다 Destroy한다.
			for(;iter_roll != _where; ++iter_roll)
			{
				// - Destroy를 호출한다.
				this->m_alloc_val.destroy(&*iter_roll);
			}

			// - 비워놓았던 Room을 다시 땡긴다.
			memcpy(pDest, psource, (unsigned long)sizeof(TDATA) * nMovCount);

			// Throw) 다시 Thread!!!
			CGD_RETHROW;
		}
	}
}


//-----------------------------------------------------------------
// 설명) CGDK::fast_vector::Insert
//
//  _where의 앞쪽에 _val 하나만 삽입하는 함수이다.
// 
// fast_vector의 Insert시 reserved된 공간이 모자랄때 std::fast_vector는 일단
// reserve를 수행한다. 이때 새로운 buffer로 기존 내용을 복사한다.
// 그리고 나서 다시 insert를 위해 복사를 해서 중간에 자리를 비운후
// 그 자리에 복사한다.
//  CGDK에서는 이런 부분을 개선하여 만약 insert시 다시 reserve하게 
// 된다면 reserve로 인해 새로 할당받은 buffer에 insert될 공간을
// 미리 비워놓고 복사를 한다. 그 후 그 자리에 insert한 내용을 
// 복사해 넣는다.
// 이렇게 하면 insert시 이중으로 복사를 하는 현상을 최소화할수 있다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, const TDATA& _val)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);

	// 1) Insert를 수행하기 위해 삽입할 공간을 비운다.(_size가 _capacity보다 크거나 같으면 fast_vector의 크기를 늘인다.)
	if(this->m_ptr_end != this->m_ptr_last)
	{
		// - Array를 한칸씩 뒤로 미룬다.
		memmove((void*)(_where.m_ptr_last+1), (void*)_where.m_ptr_last, (this->m_ptr_last - _where.m_ptr_last)*sizeof(TDATA));

		// - m_ptr_last를 증가시킨다.
		++this->m_ptr_last;
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity();

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(new_capacity + (new_capacity/2), _where, 1);

		// - Iterator를 새로 설정한다.
		_where = const_iterator(this->m_ptr_first + differ);
	}

	// 2) Insert한다.
	CGD_TRY
	{
		// - 비운 자리에 Construct를 호출해 값을 복사한다.
		this->m_alloc_val.construct((TDATA*)_where.m_ptr_last, _val);
	}
	CGD_CATCH_ALL
	{
		// - roll back을 위해 다시 PtrLast를 줄인다.
		--this->m_ptr_last;

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_where.m_ptr_last, (void*)(_where.m_ptr_last+1), (unsigned long)(m_ptr_last-_where.m_ptr_last)*sizeof(TDATA));

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return iterator((TDATA*)_where.m_ptr_last);
}

template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::insert(const_iterator _where, TDATA&& _val)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last <= this->m_ptr_last);


	// 1) Insert를 수행하기 위해 삽입할 공간을 비운다.(_size가 _capacity보다 크거나 같으면 fast_vector의 크기를 늘인다.)
	if(m_ptr_end != m_ptr_last)
	{
		// - Array를 한칸씩 뒤로 미룬다.
		memmove((void*)(_where.m_ptr_last+1), (void*)_where.m_ptr_last, (this->m_ptr_last - _where.m_ptr_last)*sizeof(TDATA));

		// - m_ptr_last를 증가시킨다.
		++this->m_ptr_last;
	}
	else
	{
		// - 새로 할당받으면 Iterator가 무효화되므로 그에 대한 대비를 해야한다.
		size_t differ = _where.m_ptr_last-m_ptr_first;

		// - 현재 크기를 구한다.
		size_type new_capacity = this->capacity();

		// - 현재 크기의 1.5배로 늘린다.(늘리면서 그만큼의 공간을 비운다.
		_Expand(new_capacity+(new_capacity/2), _where, 1);

		// - Iterator를 새로 설정한다.
		_where = const_iterator(m_ptr_first+differ);
	}

	// 2) Insert한다.
	CGD_TRY
	{
		// - 비운 자리에 Construct를 호출해 값을 복사한다.
		this->m_alloc_val.construct((TDATA*)_where.m_ptr_last, std::forward<TDATA>(_val));
	}
	CGD_CATCH_ALL
	{
		// - roll back을 위해 다시 PtrLast를 줄인다.
		--this->m_ptr_last;

		// - 비워놓았던 Room을 다시 땡긴다.
		memcpy((void*)_where.m_ptr_last, (void*)(_where.m_ptr_last+1), (unsigned long)(this->m_ptr_last - _where.m_ptr_last) * sizeof(TDATA));

		// Throw) 다시 Thread!!!
		CGD_RETHROW;
	}

	// return) 되돌린다.(Insert한 위치의 Iterator를 돌려준다.)
	return iterator((TDATA*)_where.m_ptr_last);
}


//-----------------------------------------------------------------
// CGDK::fast_vector::erase
//
//  _where위치의 Item을 지우는 함수이다.
//
// return값은 지운 다음 Item의 Iterator를 돌려준다.
// (Loop돌며 다 지울려면 erase()한 후 그 return되어 돌아오는 itreator를
// 다시 받아 end()나올 때까지 계속 지워나가면 된다.
// 
//  기존의 std::fast_vector와 차이점은 지우고 난 이후에 buffer를 땡겨야
// 하는데 이때 memcpy를 사용하여 땡긴다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::erase(const_iterator _where)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last >= this->m_ptr_first && _where.m_ptr_last < this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_where.m_ptr_last <= this->m_ptr_last);

	// check) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(this->size() > 0);

	// 1) Last를 줄인다.
	--this->m_ptr_last;

	// 2) 한칸씩 앞으로 당긴다.
	for(auto iter = _where.m_ptr_last; iter != m_ptr_last; ++iter)
	{
		*iter = std::forward<TDATA>(*(iter + 1));
	}

	// 3) 제일 마지막 데이터를 소멸시킨다.
	this->m_alloc_val.destroy(this->m_ptr_last);

	// return)
	return iterator((TDATA*)_where.m_ptr_last);
}

//-----------------------------------------------------------------
// CGDK::fast_vector::erase
//
//  _first에서 부터 시작해서 _last의 앞쪽까지 Item들을 지운다.
//
// return값은 _last를 Iterator에 넣은 값이다.
// 
//  기존의 std::fast_vector와 차이점은 지우고 난 이후에 buffer를 땡겨야
// 하는데 이때 memcpy를 사용하여 땡긴다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
typename fast_vector<TDATA, TSIZE, TALLOCATOR>::iterator fast_vector<TDATA, TSIZE, TALLOCATOR>::erase(const_iterator _first, const_iterator _last)
{
	// 주의) CGDK::fast_vector에는 max_size()검사는 존재하지 않습니다.

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_first.m_ptr_last >= this->m_ptr_first && _first.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_first.m_ptr_last <= this->m_ptr_last);

	// check) Iterator가 현재 Last안인지 검사한다.
	CGDASSERT_ERROR(_last.m_ptr_last >= this->m_ptr_first && _last.m_ptr_last <= this->m_ptr_end);

	// check) Iterator의 값이 Container의 값인지 검사한다.
	CGDASSERT_ERROR(_last.m_ptr_last <= this->m_ptr_last);

	// check) _size가 0보다 작거나 같으면 더이상 pop을 할수가 없다!
	CGDASSERT_ERROR(this->size() > 0);
	
	// 1) 이동을 위해 Source와 Dest를 먼저 설정한다.
	auto iter_source = _last.m_ptr_last;
	auto iter_dest = _first.m_ptr_last;

	// 2) 데이터를 땡긴다.
	for (; iter_source != this->m_ptr_last; ++iter_source, ++iter_dest)
	{
		*iter_dest = std::forward<TDATA>(*iter_source);
	}

	// 3) Last에 넣기 위해 임시로 저장해 놓는다.
	auto ptr_last = iter_dest;

	// 4) 땡긴 이후의 Data에 대해서는 Destroy를 한다.
	for (; iter_dest < this->m_ptr_last; ++iter_dest)
	{
		this->m_alloc_val.destroy(&(*iter_dest));
	}

	// 5) Last를 다시 설정한다.
	this->m_ptr_last = ptr_last;

	// return)
	return iterator(_last.m_ptr_last);
}


//-----------------------------------------------------------------
// CGDK::fast_vector::swap
//
//  _right의 fast_vector와 통채로 바꾼다.
//
// allocator가 같은 종류라면 그냥 알맹이만 바꾸고 만약에 다르다면
// allocator가지 통채로 바꾼다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::swap(_mytype& _right)
{
	// check) 같은 container면 그냥 return한다.
	CGD_RETURN_IF(this == &_right);

	// 1) 둘다 동적할당된 데이터라면 그냥 swap만 한다.
	if(this->is_own_data() == false && _right.is_own_data() == false)
	{
		CGD_SWAP(this->m_ptr_first, _right.m_ptr_first);
		CGD_SWAP(this->m_ptr_last, _right.m_ptr_last);
		CGD_SWAP(this->m_ptr_end, _right.m_ptr_end);
		CGD_SWAP(this->m_alloc_val, _right.m_alloc_val);
	}
	// 2) 한쪽이라도 정적 데이터라면 일일이 Move한다.
	else
	{
		if(this->is_own_data() == false)
		{
			// 아직 구현 안됌.
			CGDASSERT_ERROR(false);
			//// 1) 먼저 복사해 놓음.
			//auto prtFirst = m_ptr_first;
			//auto prtLast = m_ptr_last;
			//auto ptrEnd = m_ptr_end;
			//auto allocVal = m_alloc_val;

			//// 2) 복원
			//m_ptr_first = reinterpret_cast<TDATA*>(m_array);
			//m_ptr_last = m_ptr_first;
			//m_ptr_end = m_ptr_first + TSIZE;

			//// 3) 
			//m_ptr_first(), m_ptr_last(reinterpret_cast<TDATA*>(m_array)), m_ptr_end(reinterpret_cast<TDATA*>(m_array) + TSIZE)
		}
		else
		{
			// 아직 구현 안됌.
			CGDASSERT_ERROR(false);
		}

		// - 임시 Container에 복사한다.
		_mytype temp = _right;
		_right = *this;
		*this = temp;
	}
}


//-----------------------------------------------------------------
// CGDK::fast_vector::shrink_to_fit
//
//  max_size를 현재의 size만큼의 크기로 줄이는 함수이다.
//
// 기존에는 swap()을 사용하여 구현하였지만 여기서는 그냥 함수로 
// 제공해준다.
//
// shrink_to_fit함수를 호출하면 현재 size()에 맞도록 새로 buffer를 할당하고
// 거기에 기존 Item들을 memcpy를 사용해 복사하고 기존 buffer는
// deallocate한다.
//-----------------------------------------------------------------
template <class TDATA, size_t TSIZE, class TALLOCATOR>
void fast_vector<TDATA, TSIZE, TALLOCATOR>::shrink_to_fit()
{
	// 1) Size를 얻는다.
	size_t temp_size = this->size();

	// check) 이미 size와 capacity가 같으면 그냥 되돌린다.
	CGD_RETURN_IF(size() == this->capacity() || this->capacity() <= TSIZE);

	// check) m_ptr_first가 m_array일수는 없다!
	CGDASSERT_ERROR(this->m_ptr_first != reinterpret_cast<TDATA*>(this->m_array));

	// declare) 
	TDATA* temp_array;

	// 2) size에 맞는 array를 새로 할당받는다.
	if(temp_size <= TSIZE)
	{
		temp_array = reinterpret_cast<TDATA*>(this->m_array);
		temp_size = TSIZE;
	}
	else
	{
		temp_array = this->m_alloc_val.allocate(size());
	}

	// 3) 기존 array를 할당해제한다.(size가 0이면 이전 값을 복사할 필요는 없다.)
	if(this->size() != 0)
	{
		// check) m_ptr_first가 0이어서는 안된다.
		CGDASSERT_ERROR(this->m_ptr_first != 0);

		// - 이동한다.
		for (auto iter_dest = temp_array, iter_source = this->m_ptr_first; iter_source != this->m_ptr_last; ++iter_source, ++iter_dest)
		{
			this->m_alloc_val.construct(&(*iter_dest), std::forward<TDATA>(*iter_source));
		}

		// - 기존 데이터의 소멸자를 호출한다.
		for (auto iter_destroy = m_ptr_first; iter_destroy != this->m_ptr_last; ++iter_destroy)
		{
			this->m_alloc_val.destroy(iter_destroy);
		}

		// - 기존의 data를 지운다.
		if (m_ptr_first != reinterpret_cast<TDATA*>(this->m_array))
		{
			this->m_alloc_val.deallocate(this->m_ptr_first, this->m_ptr_end - this->m_ptr_first);
		}
	}

	// 4) 새로 설정한다.
	this->m_ptr_first = temp_array;
	this->m_ptr_end = temp_array+size();
	this->m_ptr_last = temp_array+temp_size;
}




}