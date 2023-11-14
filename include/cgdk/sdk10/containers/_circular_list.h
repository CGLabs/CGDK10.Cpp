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

template <class TDATA, class TALLOCATOR=allocator_pool<TDATA> >
class circular_list
{
// ****************************************************************************
// Type definitions for Standard)
//
//  * Common Container Requirement
//     1) X:value_type		Contain�� ��� ������ ��.
//     2) X:reference		X:value_type&.
//     3) X:const_reference	const X:value_type&.
//     4) X:iterator		��ȸ�� �� ���Ǵ� �ݺ���.
//     5) X:const_iterator	��ȸ�� �� ���Ǵ� �ݺ���(const����)
//     6) X:difference_type	�� iterator�� ��� ���� �Ÿ��� ��Ÿ���� Ÿ��.
//     7) X:size_type		X�� ũ�⸦ ��Ÿ���� ���Ǵ� ��.
//
//  * Reversible Requirement
//     1) X::reverse_iterator ����ȯ �� ���Ǵ� �ݺ���.
//     2) X::const_reverse_iterator	����ȯ �� ���Ǵ� �ݺ���.(const����)
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
	typedef	circular_list<value_type, TALLOCATOR>	_mytype;

	// Rebinder) 
	template<typename TOTHER_DATA, typename TOTHER_ALLOCATOR=TALLOCATOR>
	struct rebind
	{
		typedef circular_list<TOTHER_DATA, TOTHER_ALLOCATOR> other;
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
//     1) a.rbegin();		�ݴ���� ��ȸ�� ���� ���۰� �� iterator
//		  a.rend();
//
// ----------------------------------------------------------------------------
public:
	circular_list() noexcept;
	circular_list(const _mytype& _right);
	circular_list(_mytype&& _right) noexcept;
	~circular_list() noexcept;

public:
	// Common Standard 1) Status Function
	size_type				size() const							{	return m_size;}
	size_type				max_size() const						{	return std::numeric_limits<size_t>::max();}
	bool					empty() const							{	return m_size==0;}

	// Common Standard 2) 
	iterator				begin()									{	return iterator(m_head);}
	const_iterator			begin() const							{	return const_iterator(m_head);}
	const_iterator			cbegin() const							{	return const_iterator(m_head);}
	iterator				end()									{	return iterator(m_tail);}
	const_iterator			end() const								{	return const_iterator(m_tail);}
	const_iterator			cend() const							{	return const_iterator(m_tail);}
	reverse_iterator		rbegin()								{	return reverse_iterator(iterator(m_tail->_pre));}
	const_reverse_iterator	rbegin() const							{	return const_reverse_iterator(const_iterator(m_tail->_pre));}
	const_reverse_iterator	crbegin() const							{	return const_reverse_iterator(const_iterator(m_tail->_pre));}
	reverse_iterator		rend()									{	return reverse_iterator(iterator(m_head->_pre));}
	const_reverse_iterator	rend() const							{	return const_reverse_iterator(const_iterator(m_head->_pre));}
	const_reverse_iterator	crend() const							{	return const_reverse_iterator(const_iterator(m_head->_pre));}

	// Common Standard 3) 
	void					swap(_mytype& _right);

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
	circular_list(size_type _count);
	circular_list(size_type _count, const_reference _val);
	circular_list(size_type _count, const_reference _val, const TALLOCATOR& _Al);
	template<class TITERATOR>
	circular_list(TITERATOR _first, TITERATOR _last);
	template<class TITERATOR>
	circular_list(TITERATOR _first, TITERATOR _last, const TALLOCATOR& _Al);

public:
	// Sequence Standard 1) insert member function
	template<class TITERATOR>
	void					insert(const_iterator _where, TITERATOR _first, TITERATOR _last);
	iterator				insert(const_iterator _where, const_reference _val);
	void					insert(const_iterator _where, int _count, const_reference _val);

	// Sequence Standard 2) erase member function
	iterator				erase(const_iterator _where);
	iterator				erase(const_iterator _first, const_iterator _last);

	// Sequence Standard 3) clear
	void					clear();

	// CGDK Native) attach/detach function
	void					attach(const_iterator _where, const_iterator _node);
	void					detach(const_iterator _where);


// ****************************************************************************
// List Member)
//
//
//
//
// ----------------------------------------------------------------------------
public:
	// 1) Capacity
	size_type				capacity() const { return m_capacity;}
																	  
	// 2) Data														  
	reference				front() { return m_head->_data;}
	const_reference			front() const { return m_head->_data;}
																	  
	reference				back() { return m_tail->_pre->_data;}
	const_reference			back() const { return m_tail->_pre->_data;}
																	  
	// 3) Unique
	template<typename _Pr2>
	void					unique(_Pr2 _pred);
	void					unique();

	// 4) Push & Pop Front
	void					push_front(const_reference _val);
	void					push_front(value_type&& _val);
	reference				push_front();
	void					pop_front();
	void					emplace_front(value_type&& _val) { push_front(std::move(_val)); };

	void					push_back(const_reference _val);
	void					push_back(value_type&& _val);
	reference				push_back();
	void					pop_back();
	void					emplace_back(value_type&& _val) { push_back(std::move(_val)); };

	// 5) remove
	template<typename _Pr1>
	void					remove_if(_Pr1 _pred);
	void					remove(const_reference _data);

	// 6) Reserve & Resize
	void					reserve(size_type _count);
	void					resize(size_type _new_size) {resize(_new_size, value_type());}
	void					resize(size_type _new_size, const value_type& _val);

	// 7) splice
	void					splice(const_iterator _where, _mytype& _right);
	void					splice(const_iterator _where, _mytype& _right, const_iterator _first);
	void					splice(const_iterator _where, _mytype& _right, const_iterator _first, const_iterator _last);

	// 8) Assign.
	template<class ITERATOR>
	void					assign(ITERATOR _first, ITERATOR _last);
	void					assign(size_type _count, const_reference _val);

	// 9) merge(�ΰ��� circular_list�� ��ġ�� �Լ�.)
	template<typename _Pr3>
	void					merge(_mytype& _right, _Pr3 _pred);
	void					merge(_mytype& _right);

	// 10) sort
	template<typename _Pr3>
	void					sort(_Pr3 _pred);
	void					sort();

	// 11) shrink(List�� size�� �°� ���̴� �Լ�.)
	void					shrink();

	// 12) Allocation
	allocator_type			get_allocator() const { return m_alloc_val;}


// ****************************************************************************
// 2. List
// ----------------------------------------------------------------------------
public:
	// Node Structure)
	struct _node
	{
		_node*				_pre;
		_node*				_next;
		value_type			_data;

		_node()				{}
		_node(const value_type& p_data) : _data(p_data)	{}
	};

protected:
	// 1) Head & Tail Pointer
	_node*					m_head;					// Linked List�� Head�� �ٷ� ��~
	_node*					m_tail;					// Linked List�� Tail�� �ٷ� ��~

	// 2) Size & Capacity
	size_type				m_size;					// ���� ������� Node��.
	size_type				m_capacity;				// ��ü Node��.

	// 3) Allocator
	allocator_type			m_alloc_val;
	typename TALLOCATOR::template rebind<_node>::other	m_alloc_node;

private:
	_node*					_make_node(const value_type& _val);
	_node*					_make_node(value_type&& _val);
	_node*					_make_node();
	void					_merge_for_sort(_node& temp_list, _node& nowList);
	template<typename _Pr3>
	void					_merge_for_sort(_node& temp_list, _node& nowList, _Pr3 _pred);
	void					_slice_for_sort(_node& temp_list, _node*& node_now);




// ****************************************************************************
// Iterator Definitions.
// 
// 1. Bi-Directional Iterator Standard Requirement
//    1) Cousturctors(Xu; X(); X(a); X u(a); X u=a;)
//    2) a==b; a!=b;
//    3) r=a; *a; a->m; 
//    4) ++r; r++; *r++;
//    5) --r; r--; *r--;
// ----------------------------------------------------------------------------
public:
	class const_iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular_list<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::const_pointer		pointer;
		typedef typename _mytype::const_reference	reference;

		friend			iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		const_iterator() noexcept : _Ptr(nullptr)					{}
		explicit const_iterator(_node* _now) noexcept : _Ptr(_now)	{}

		// 2) ����
		const_iterator&		operator=(_node* _right)				{ _Ptr=_right; return *this;}
		pointer				operator->()							{ return &**this;}
																	  
		// 3) �ݺ�												    
		reference			operator*() const						{ return _Ptr->_data;}
		const_iterator&		operator++()							{ _Ptr=_Ptr->_next; return *this;}
		const_iterator		operator++(int)							{ const_iterator tIter(_Ptr); _Ptr=_Ptr->_next; return tIter;}
		const_iterator&		operator--()							{ _Ptr=_Ptr->_pre; return *this;}
		const_iterator		operator--(int)							{ const_iterator tIter(_Ptr); _Ptr=_Ptr->_pre; return tIter;}
		const_iterator		operator+(difference_type _right) const	{ const_iterator temp(_Ptr); temp+=_right; return temp;}
		void				operator+=(difference_type _right)		{ while(_right){_Ptr=_Ptr->_next;--_right;}}
		const_iterator		operator-(difference_type _right) const	{ const_iterator temp(_Ptr); temp-=_right; return temp;}
		void				operator-=(difference_type _right)		{ while(_right){_Ptr=_Ptr->_pre;--_right;}}

		// 4) ��
		bool				operator==(const iterator& _right) const{ return _Ptr==_right._Ptr;}
		bool				operator!=(const iterator& _right) const{ return _Ptr!=_right._Ptr;}

		bool				operator==(const const_iterator& _right) const{	return _Ptr==_right._Ptr;}
		bool				operator!=(const const_iterator& _right) const{	return _Ptr!=_right._Ptr;}

		// 5) reset
		void				reset() noexcept						{ _Ptr =nullptr;}

	public:
		_node*				_Ptr;
	};


	class iterator
	{
	public:
	// ----------------------------------------------------------------
	// Types) 
		friend	circular_list<TDATA, TALLOCATOR>;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef TDATA								value_type;
		typedef typename _mytype::difference_type	difference_type;
		typedef typename _mytype::pointer			pointer;
		typedef typename _mytype::reference			reference;

		friend			const_iterator;
	// ----------------------------------------------------------------
	public:
		// 1) ������
		iterator() noexcept : _Ptr(nullptr)							{}
		explicit iterator(_node* _now) noexcept : _Ptr(_now)		{}

		// 2) ����
		void				operator=(_node* _right)				{ _Ptr=_right;}
		pointer				operator->()							{ return &**this;}
							operator const_iterator()				{ return const_iterator(_Ptr);}
																	  
		// 3) �ݺ�												    
		reference			operator*() const						{ return _Ptr->_data;}
		iterator&			operator++()							{ _Ptr=_Ptr->_next; return *this;}
		iterator			operator++(int)							{ iterator tIter(_Ptr); _Ptr=_Ptr->_next; return tIter;}
		iterator&			operator--()							{ _Ptr=_Ptr->_pre; return *this;}
		iterator			operator--(int)							{ iterator tIter(_Ptr); _Ptr=_Ptr->_pre; return tIter;}
		iterator			operator+(difference_type _right) const	{ iterator temp(_Ptr); temp+=_right; return temp;}
		void				operator+=(difference_type _right)		{ while(_right){_Ptr=_Ptr->_next;--_right;}}
		iterator			operator-(difference_type _right) const	{ iterator temp(_Ptr); temp-=_right; return temp;}
		void				operator-=(difference_type _right)		{ while(_right){_Ptr=_Ptr->_pre;--_right;}}

		// 4) ��
		bool				operator==(const iterator& _right) const{ return _Ptr==_right._Ptr;}
		bool				operator!=(const iterator& _right) const{ return _Ptr!=_right._Ptr;}

		bool				operator==(const const_iterator& _right) const{	return _Ptr==_right._Ptr;}
		bool				operator!=(const const_iterator& _right) const{	return _Ptr!=_right._Ptr;}

		// 5) reset
		void				reset() noexcept { _Ptr = nullptr; }

	public:
		_node*				_Ptr;
	};
};




//-----------------------------------------------------------------
// Constructor/Destructor �Լ���.
//
// - �پ��� ������ constructor�� destructor�Լ����̴�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list() noexcept :
	m_head(nullptr),
	m_tail(nullptr),
	m_size(0),
	m_capacity(0)
{
	// 1) 
	m_head = m_alloc_node.allocate(1);
	m_tail = m_head;

	// 2) Head�� Tail�� ����~(head�� head�� link~)
	LINK_NODE(m_head, m_head);
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(const _mytype& _right) : circular_list()
{
	// 1) �����سִ´�.
	try
	{
		insert(begin(), _right.begin(), _right.end());
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}

template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(_mytype&& _right) noexcept : circular_list()
{
	// 1) Head�� �Ҵ��Ѵ�.
	std::swap(m_head, _right.m_head);
	std::swap(m_tail, _right.m_tail);
	std::swap(m_size, _right.m_size);
	std::swap(m_capacity, _right.m_capacity);
}

template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_mytype& circular_list<TDATA, TALLOCATOR>::operator=(const _mytype& _right)
{
	// 1) �ϴ� ������ �� �����.
	clear();

	// 2) �����سִ´�.
	try
	{
		insert(begin(), _right.begin(), _right.end());
	}
	catch(...)
	{
		// throw) �ٽ� Thread!!!
		throw;
	}

	// return)�ڱ� �ڽ� Return
	return	*this;
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _count) : circular_list()
{
	// 1) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	try
	{
		for(;_count>0;--_count)
		{
			push_back();
		}
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _count, const_reference _val) : circular_list()
{
	// 1) �����سִ´�.
	try
	{
		insert(begin(), _count, _val);
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}


template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(size_type _count, const_reference _val, const TALLOCATOR& _Al) : circular_list()
{
	// 1) �����سִ´�.
	try
	{
		insert(begin(), _count, _val);
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}


template <class TDATA, class TALLOCATOR>
template<class TITERATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(TITERATOR _first, TITERATOR _last) : circular_list()
{
	// 1) �����سִ´�.
	try
	{
		insert(begin(), _first, _last);
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}


template <class TDATA, class TALLOCATOR>
template<class TITERATOR>
circular_list<TDATA, TALLOCATOR>::circular_list(TITERATOR _first, TITERATOR _last, const TALLOCATOR& _Al) : circular_list()
{
	// 1) �����سִ´�.
	try
	{
		insert(begin(), _first, _last);
	}
	catch(...)
	{
		m_alloc_node.deallocate(m_head, 1);

		// throw) �ٽ� Thread!!!
		throw;
	}
}

template <class TDATA, class TALLOCATOR>
circular_list<TDATA, TALLOCATOR>::~circular_list() noexcept
{
	// 1) ���� clear�� �ؼ� item���� destory�� ȣ���Ѵ�.
	clear();

	// 2) ��� Node���� �����.
	_node* temp = m_head;
	do
	{
		// - Next node�� �� ������ ���´�.
		_node* temp_next = temp->_next;

		// - Destruct�� ȣ���ϰ� pnode_temp�� �����.
		//   (Destroy�� ȣ������ �ʴ´�.)
		m_alloc_node.deallocate(temp, 1);

		// - ���� Node
		temp = temp_next;
	}while(temp != m_head);
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_node* circular_list<TDATA, TALLOCATOR>::_make_node(const value_type& _val)
{
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ� �޴´�.
	_node* new_node = m_alloc_node.allocate(1);

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	try
	{
		m_alloc_val.construct(&new_node->_data, _val);
	}
	// exception) Exception�� �߻����� ���!!!
	catch(...)
	{
		// - deallocate�� �����Ѵ�.
		m_alloc_node.deallocate(new_node, 1);

		// Re-Throw�� �Ѵ�.
		throw;
	}

	// return)���ο� Node�� Return�Ѵ�.
	return new_node;
}

template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_node* circular_list<TDATA, TALLOCATOR>::_make_node(value_type&& _val)
{
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ� �޴´�.
	_node* new_node = m_alloc_node.allocate(1);

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	try
	{
		m_alloc_val.construct(&new_node->_data, std::move(_val));
	}
	// exception) Exception�� �߻����� ���!!!
	catch(...)
	{
		// - deallocate�� �����Ѵ�.
		m_alloc_node.deallocate(new_node, 1);

		// Re-Throw�� �Ѵ�.
		throw;
	}

	// return)���ο� Node�� Return�Ѵ�.
	return new_node;
}

template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::_node* circular_list<TDATA, TALLOCATOR>::_make_node()
{
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ� �޴´�.
	_node* new_node = m_alloc_node.allocate(1);

	// 2) �Ҵ���� ���ο� Node�� Construct�� �����Ѵ�.
	try
	{
		m_alloc_val.construct(&new_node->_data);
	}
	// exception) Exception�� �߻����� ���!!!
	catch(...)
	{
		// - deallocate�� �����Ѵ�.
		m_alloc_node.deallocate(new_node, 1);

		// Re-Throw�� �Ѵ�.
		throw;
	}

	// return)���ο� Node�� Return�Ѵ�.
	return new_node;
}

// ���Լ���
template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator==(const _mytype& _right) const
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return (iter_dst == _right.end());
		}

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return false;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� false����!
		if(*iter_src!=*iter_dst)
		{
			return false;
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator!=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return (iter_dst != _right.end());
		}

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return true;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
		{
			return true;
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator<(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return false;
		}

		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return true;
		}


		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
		{
			return (*iter_src<*iter_dst);
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator>(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src = begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return false;
		}

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return true;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
		{
			return (*iter_src>*iter_dst);
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator<=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return true;
		}

		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return false;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src!=*iter_dst)
		{
			return (*iter_src<*iter_dst);
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}

template <class TDATA, class TALLOCATOR>
bool circular_list<TDATA, TALLOCATOR>::operator>=(const _mytype& _right) const	
{
	// 1) ó������ ã�� ���� �غ��Ѵ�.
	iterator iter_src=begin();
	typename _mytype::iterator iter_dst = _right.begin();

	for(;;)
	{
		// check) Dst�� ���ΰ�?
		if(iter_dst == end())
		{
			return true;
		}

		// check) Src�� ���ΰ�???
		if(iter_src == end())
		{
			return false;
		}

		// 2) ���� Src�� Dst�� ���� ������ �ٷ� true����!
		if(*iter_src != *iter_dst)
		{
			return (*iter_src>*iter_dst);
		}

		// 3) ������~
		++iter_src;
		++iter_dst;
	}
}



template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::reserve(size_type _count)
{
	//-----------------------------------------------------------------
	// 1. �߰��� Ȯ���� Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// check) �߰��� item�� ������ 0�� ���϶�� �׳� ������.
	CGD_RETURN_IF(_count <= m_capacity);

	//-----------------------------------------------------------------
	// 2. �߰��� Node����ŭ �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���� �߰��� item�� ������ ����Ѵ�.
	size_type added = _count - m_capacity;

	// 1) ������ ��ü�� ���� Node�� ��´�.
	_node* end = m_head->_pre;
	try
	{
		// 2) �߰��� item�� ������ŭ node�� ����� ������.
		for(; added>0; --added)
		{
			// - Node�� ���� �����Ѵ�.
			_node* pnode_new = m_alloc_node.allocate(1);

			// - ������ Node�� end�� ������.
			LINK_NODE(end, pnode_new);

			// - ���� Node�� ���ο� end�� �����Ѵ�.
			end = pnode_new;
		}
	}
	catch(...)
	{
		// 1) Roll back�� ù��° Node�� ��´�.
		_node*	nodeDealloc = m_head->_pre->_next;

		// 2) Loop�� ���� ������ ��� Node�� �����Ѵ�.
		while(nodeDealloc != end)
		{
			// - �ӽ÷� ���� Node�� ��� ���´�.
			_node* temp_next = nodeDealloc->_next;

			// �Ҵ��ߴ� pnode_new�� �����Ѵ�.
			m_alloc_node.deallocate(nodeDealloc, 1);

			// - ���� Node��~
			nodeDealloc = temp_next;
		}

		// 3) m_head�� pre�� Next�� �ٽ� m_head�� �ǵ�����.
		m_head->_pre->_next = m_head;

		// throw) �ٽ� Thread!!!
		throw;
	}

	//-----------------------------------------------------------------
	// 3. Head�� �ʿ��ٰ� ������.
	//-----------------------------------------------------------------
	// 1) ���� node�� head�� ���ʿ� ������.
	LINK_NODE(end, m_head);

	//-----------------------------------------------------------------
	// 4. �����Ͽ� �߰��Ѹ�ŭ ����node�� ���� ������Ų��.
	//-----------------------------------------------------------------
	m_capacity = _count;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::resize(size_type _new_size, const value_type& _val)
{
	// ũ�� ���� ����.
	int	differ = _new_size - m_size;

	//-----------------------------------------------------------------
	// CaseA) ũ�⸦ �ø���.
	//-----------------------------------------------------------------
	// ���� ���� ũ�Ⱑ NewSize���� ������ _val�� �� ���̸�ŭ �����Ѵ�.
	if (differ>0)
	{
		insert(end(), differ, _val);
	}
	//-----------------------------------------------------------------
	// CaseB) ũ�⸦ ���δ�.
	//-----------------------------------------------------------------
	//  ���� ���� ũ�Ⱑ NewSize���� ũ�� ���� Item���� �����Ѵ�.
	else
	{
		// 1) ����ó differ��ŭ ���ʿ������� �����Ѵ�.
		while (differ!=0)
		{
			// - Tail�� ��ĭ �����.
			m_tail = m_tail->_pre;

			// - Destroy�� ȣ���Ѵ�.
			m_alloc_val.destroy(&m_tail->_data);

			differ++;
		}

		// 2) ũ��� ������ _NewSize�Ǵ� �Ŵ�.
		m_size = _new_size;
	}
}

template <class TDATA, class TALLOCATOR>
template<class ITERATOR>
void circular_list<TDATA, TALLOCATOR>::assign(ITERATOR _first, ITERATOR _last)
{
	// 1) ���� List�� ��� �����.
	clear();

	// 2) �����Ѵ�.
	for(; _first != _last; ++_first)
	{
		push_back(*_first);
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::assign(size_type _count, const_reference _val)
{
	// 1) ���� �����.
	clear();

	// 2) _val���� _count��ŭ �����Ѵ�.
	for (; 0 < _count; --_count)
	{
		push_back(_val);
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::clear()
{
	// 1) ��� node�� �Ҵ������Ѵ�.
	for(iterator iter = begin(); iter != end(); ++iter)
	{
		// - Destruct�� ȣ���Ѵ�.
		m_alloc_val.destroy(&(*iter));
	}

	// 2) clear�Ѵ�. (head�� next�� �����Ѵ�.)
	m_tail = m_head;

	// 3) ũ�⸦ 0����..
	m_size = 0;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_front(const_reference _val)
{
	//-----------------------------------------------------------------
	// 1. ���尡 ���� ���� ��� (Node�� �о �߰��Ѵ�.)
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//
	// ����) 1)�׿��� pre�� ���� ���� ���� construct�� ó���ϰ� 3)�׿���
	//       m_head�� ������ _pre�� ���� ������ Exception-safeó����
	//       ���ؼ��̴�. construct�������� exception�� �߻��Ҽ� �ְ�
	//       ���� m_head�� �̸� ���ܳ������� exception�� �߻����� �� �ٽ�
	//       roll-back�� ����� �Ѵ�. �׷��� construct�� ���� ���Ŀ� 
	//       m_head ���� �ٲٴ� ó���� �� ���̴�.
	//       (�� �� ó���� code�� �ӵ��� ���� ������ ����.)
	//-----------------------------------------------------------------
	if(m_size!=m_capacity)
	{
		// 1) ���ο� Head�� �� Node�� ��´�.
		_node* pnow = m_head->_pre;

		// 2) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
		m_alloc_val.construct(&pnow->_data, _val);

		// 3) �׳� �ϳ� �����.
		m_head = pnow;

		// 4) ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	//-----------------------------------------------------------------
	// 2. ���� ���� ��� �� ��带 �����ؼ� �߰��Ѵ�.
	//
	// - ���� node�� ����(m_size�� allocated������ ���� Node�� ���� ���̴�.)
	//   ������ ���� ����� �߰��Ѵ�.
	//   (�̰��� ������� �ʵ��� �ִ��� reserve�� �̷� �صѰ��� ���Ѵ�.)
	//-----------------------------------------------------------------
	else
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = _make_node(_val);

		// 2) Node�� Head�� �����Ѵ�.
		LINK_NODE(m_head->_pre, pnode_new);
		LINK_NODE(pnode_new, m_head);

		// 3) ���� �Ҵ���� pNodeNode�� ���ο� Head���ȴ�.
		m_head = pnode_new;

		// 4) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_front(value_type&& _val)
{
	//-----------------------------------------------------------------
	// push_front()�Լ��� ����(std::move�� ����Ѵٴ� �͸� �ٸ�)
	//-----------------------------------------------------------------
	// Case-A) ���尡 ���� ���� ���
	if (m_size != m_capacity)
	{
		// 2) ���� ���� ���...
		_node* pnow = m_head->_pre;

		// 2) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
		m_alloc_val.construct(&pnow->_data, std::move(_val));

		// 3) �׳� �ϳ� �����.
		m_head = pnow;

		// 4) ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	// Case-B) ���� ���� ��� �� ��带 �����ؼ� �߰��Ѵ�.
	else
	{
		// - ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = _make_node(std::move(_val));

		// - Node�� Head�� �����Ѵ�.
		LINK_NODE(m_head->_pre, pnode_new);
		LINK_NODE(pnode_new, m_head);

		// - ���� �Ҵ���� pNodeNode�� ���ο� Head���ȴ�.
		m_head = pnode_new;

		// - �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}

}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::reference circular_list<TDATA, TALLOCATOR>::push_front()
{
	//-----------------------------------------------------------------
	// 1. ���� �����ؼ� �߰��Ѵ�.
	//
	// - ���� node(m_size�� allocated������ ���� Node�� ���� ���̴�.)��
	//   ������ ���� ����� �߰��Ѵ�.
	//   (�̰��� ������� �ʵ��� �ִ��� reserve�� �̷� �صѰ��� ���Ѵ�.)
	//-----------------------------------------------------------------
	if(m_size == m_capacity)
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = _make_node();

		// 2) Node�� Head�� �����Ѵ�.
		LINK_NODE(m_head->_pre, pnode_new);
		LINK_NODE(pnode_new, m_head);

		// 3) ���� �Ҵ���� pNodeNode�� ���ο� Head�� �ȴ�.
		m_head = pnode_new;

		// 4) �Ҵ���� ���� ũ�⸦ 1�� �ø���.
		++m_size;
		++m_capacity;

		// return)Data�� Reference�� �ǵ�����.
		return pnode_new->_data;
	}

	//-----------------------------------------------------------------
	// 2. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//
	// ����) 1)�׿��� pre�� ���� ���� ���� construct�� ó���ϰ� 3)�׿���
	//       m_head�� ������ _pre�� ���� ������ Exception-safe�� ó����
	//       ���ؼ��̴�. construct�������� exception�� �߻��Ҽ� �ְ�
	//       ���� m_head�� �̸� ���ܳ������� exception�� �߻����� �� �ٽ�
	//       roll-back�� ����� �Ѵ�. �׷��� construct�� ���� ���Ŀ� 
	//       m_head ���� �ٲٴ� ó���� �� ���̴�.
	//       (�� �� ó���� code�� �ӵ��� ���� ������ ����.)
	//-----------------------------------------------------------------
	// 1) ���ο� Head�� �� Node�� ��´�.
	_node* pnow = m_head->_pre;

	// 2) ��ġ�� ��´�.
	TDATA& temp_data = pnow->_data;

	// 3) Constructor�� ȣ���Ѵ�.
	m_alloc_val.construct(&pnow->_data);

	// 4) �׳� �ϳ� �����.
	m_head = pnow;

	// 5) ũ��(size)�� 1 ���δ�.
	++m_size;

	// return)
	return temp_data;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_back(const_reference _val)
{
	//-----------------------------------------------------------------
	// 1. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//-----------------------------------------------------------------
	// 1) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
	m_alloc_val.construct(&m_tail->_data, _val);

	// 2-1) ���� Node�� ���� ���
	if(m_size != m_capacity)
	{
		// - �׳� �ϳ� �����.
		m_tail = m_tail->_next;

		// - ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	// 2-2) ���� Node�� ���� ���
	else
	{
		// - ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = m_alloc_node.allocate(1);

		// - �Ҵ���� ���ο� Node�� ���� �ִ´�.
		LINK_NODE(pnode_new, m_tail->_next);
		LINK_NODE(m_tail, pnode_new);

		// - m_tail���� �����Ѵ�.
		m_tail = pnode_new;

		// - �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::push_back(value_type&& _val)
{
	//-----------------------------------------------------------------
	// ���� push_back�� ���� costruct()ȣ��� std::move�� ����Ѵٴ� 
	// �͸� �ٸ�.
	//-----------------------------------------------------------------
	// 1) Constructor�� ȣ���Ѵ�.(Copy constructor�� ȣ��)
	m_alloc_val.construct(&m_tail->_data, std::move(_val));

	// 2-1) ���� Node�� ���� ���
	if (m_size!=m_capacity)
	{
		// - �׳� �ϳ� �����.
		m_tail = m_tail->_next;

		// - ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	// 2-2) ���� Node�� ���� ���
	else
	{
		// 2) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = m_alloc_node.allocate(1);

		// 3) �Ҵ���� ���ο� Node�� ���� �ִ´�.
		LINK_NODE(pnode_new, m_tail->_next);
		LINK_NODE(m_tail, pnode_new);

		// 4) m_tail���� �����Ѵ�.
		m_tail = pnode_new;

		// 5) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::reference circular_list<TDATA, TALLOCATOR>::push_back()
{
	//-----------------------------------------------------------------
	// 1. Node�� �о �߰��Ѵ�.
	//
	// - Circulare List�� �ٱ��ʿ� ���� Node�� �ִ� ����.
	// - �׳� �ϳ� �а� �ű⿡�ٰ� ���� �߰��� �ϸ� �ȴ�.
	//-----------------------------------------------------------------
	// 1) ��(value)�� ��ġ�� �����س��´�.
	value_type&	temp_data = m_tail->_data;

	// 2-1) ���� Node�� ���� ���
	if(m_size!=m_capacity)
	{
		// 1) �׳� �ϳ� �����.
		m_tail = m_tail->_next;

		// 2) ũ��(size)�� 1 ���δ�.
		++m_size;
	}
	// 2-2) ���� Node�� ���� ���
	else
	{
		// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
		_node* pnode_new = m_alloc_node.allocate(1);

		// 2) �Ҵ���� ���ο� Node�� ���� �ִ´�.
		LINK_NODE(pnode_new, m_tail->_next);
		LINK_NODE(m_tail, pnode_new);

		// 3) m_tail���� �����Ѵ�.
		m_tail = pnode_new;

		// 4) �Ҵ���� ���� ũ�⸦ 1 �ø���.
		++m_size;
		++m_capacity;
	}

	// return)
	return temp_data;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::pop_front()
{
	// check) ��� �ִµ� pop�� �ϸ� �ȵȴ�.
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	if(empty())
	{
		return;
	}
	#endif

	// 1) Destroy�� ȣ���Ѵ�.
	m_alloc_val.destroy(&m_head->_data);

	// 2) Head�� ��ĭ �����.
	m_head = m_head->_next;

	// 3) ũ��(size)�� 1 ���δ�.
	--m_size;
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::pop_back()
{
	// check) Empty�˻�.
	#ifdef _CGD_NOCHECK_EMPTY_POP
	// * Empty�� Check�� ���� ���� ��쿡 Debug ����϶� Assert�� ����ش�.
	//   (Release Mode�� ���� �ƹ��ϵ� �������� �ʴ´�.)
	CGDASSERT_ERROR(!empty());
	#else
	// Empty�� Check�� �� ��� Empty�� Check�ϰ� ��� ���� ��� �ƹ��������� �ʰ� �׳� ������.
	CGD_RETURN_IF(empty());
	#endif

	// 1) Tail�� ��ĭ �����.
	m_tail = m_tail->_pre;

	// 2) Destroy�� ȣ���Ѵ�.
	m_alloc_val.destroy(&m_tail->_data);

	// 3) ũ��(size)�� 1 ���δ�.
	--m_size;
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::insert(const_iterator _where, const_reference _val)
{
	//-----------------------------------------------------------------
	// 1. Head�� ���.
	//-----------------------------------------------------------------
	// - Head�� ��� push_front�� ��.
	if(_where==begin())
	{
		// - push_front�� ��.
		push_front(_val);

		// - begin()�� return��~
		return begin();
	}

	//-----------------------------------------------------------------
	// 2. ���� node�� �����ϰ� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ���ο� Node�� Allocator�κ��� �Ҵ�޴´�.
	_node* pnode_new;

	if(m_size==m_capacity)
	{
		// - ���ο� Node�� �Ҵ�޴´�.
		pnode_new = _make_node(_val);

		// - Capacity�� �����Ѵ�.(���� �Ҵ�޴� �Ŵϱ�...)
		++m_capacity;
	}
	else
	{
		// - ��� Node�� ����.
		pnode_new = m_tail->_next;

		// - �ʱ�ȭ�Ѵ�.
		m_alloc_val.construct(&pnode_new->_data, _val);

		// - �� Node�� �����Ѵ�. List���� �����Ѵ�.
		LINK_NODE(m_tail, pnode_new->_next);
	}

	// 2) ������ �� Node
	_node* pnode = _where._Ptr;

	// 3) Link�� �Ǵ�.
	LINK_NODE(pnode->_pre, pnode_new);
	LINK_NODE(pnode_new, pnode);

	// 4) �Ҵ���� ����(allocated)�� ũ��(size)�� 1 �ø���.
	++m_size;

	// return)
	return iterator(pnode_new);
}


//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  insert: _val���� circular_list���� �����Ѵ�.
//
// ����)
//  Iist Insert ���� ������ �ٽ��� �ٷ� circular�� backside�� ������
//  Node���� �̹� circular_list�� ����Ǿ��� ���̹Ƿ� �̰Ϳ��ٰ� ���ʷ� 
//  ���� ������ �� Insert�Ҹ�ŭ�� ����� Insert�� ���ϴ� ��(_where)�� 
//  ����ִ� �ٴ� ���̴�.
//   ���⼭ ���� ������ Node�� ������ ��쿡�� ���� �����Ͽ� Node��
//  ����ó���� �Ѵ�.
//   ó�� �˰��� ���� �׿� ���� �ۼ��Ǿ��� �ִ�.
//  �Ѳ����� �����Ϸ��� node�� ������ ���� ���� ������ std::list��
//  insert�� ���� �������̸� ����.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::insert(const_iterator _where, int _count, const_reference _val)
{
	// check) _count�� 0�̰ų� ���� ������ �ٷ� �����Ѵ�.
	CGD_RETURN_IF(_count <= 0);


	//-----------------------------------------------------------------
	// 1. ���鼭 �����Ѵ�.
	//-----------------------------------------------------------------
	// declare) 
	iterator iter_insert;
	iterator iter_end;
	int count;
	size_type capacity_inc = 0;

	try
	{
		// 1) �߰��� �ϱ� ���� ���� Node�� ��´�.
		//    (tail�� next���Ͱ� ���� Node�̴�.)
		iter_insert = ++end();	// m_tail�� _next.

		// 2) ���� Node�� ���� Insert�ϱ� �����Ѵ�.
		for (count=_count; (count >0) && (iter_insert!=begin()); --count, ++iter_insert)
		{
			// - Construct�Ѵ�.
			m_alloc_val.construct(&(*iter_insert), _val);
		}

		// 3) ����� ������ Node�� �����Ѵ�.(��� Node�� �������� ����...)
		//    (iter_insert�� ���� Node�� �̾ ������ �Ѵ�.)
		iter_end = iter_insert--;

		// 4) �߰��Ҵ� �Ǵ� Node ������ �����Ѵ�.
		//    (���� count�� �߰��ؾ��� Node���̴�.)
		capacity_inc = count;

		// 5) �����ؼ� ������ Node���� �߰��Ѵ�.
		for (; count >0; --count)
		{
			// - Node�� ���� �����Ѵ�.
			_node* pnode_new = _make_node(_val);

			// - Node�� �߰��Ѵ�.
			LINK_NODE(iter_insert._Ptr, pnode_new);

			// - iter_insert�� pnode_new�� �Ѵ�.
			iter_insert = pnode_new;
		}
	}
	// exception) Roll back�Ѵ�.
	catch(...)
	{
		// 1) �� Node��..
		iterator iter_rollback = ++end();

		// 2) Role back�ϸ� destroy�Ѵ�.
		while(iter_rollback!=iter_insert)
		{
			// - node�� destroy�Ѵ�.
			m_alloc_val.destroy(&(*iter_rollback));

			// - ���� Node�� �����Ѵ�.
			--iter_rollback;
		}

		// 3) �߰��Ҵ��ߴ� Node���� ��� Deallocate�Ѵ�.
		while(iter_end!=iter_insert)
		{
			// - ��������� �̸� Next�� �����´�.
			iterator temp = iter_end++;

			// - node�� destroy�Ѵ�.
			m_alloc_val.destroy(&(*temp));
		}

		// throw) �ٽ� Throw!!!
		throw;
	}


	//-----------------------------------------------------------------
	// 2. Link�߰��ϱ�.
	//-----------------------------------------------------------------
	// 1) ������ ù��° Node�� ���.
	_node* pnode_start = m_tail->_next;

	// 2) _where�� Head�� ��� Head�� �ٲٱ�.
	if(_where._Ptr == m_head)
	{
		m_head = pnode_start;
	}

	// 3) �߰��� List�� �ϴ� ������ Circular List�� �ݴ´�.
	LINK_NODE(m_tail, iter_end._Ptr);

	// 4) _where�� ����ֱ�
	LINK_NODE(_where._Ptr->_pre, pnode_start);
	LINK_NODE(iter_insert._Ptr, _where._Ptr);


	//-----------------------------------------------------------------
	// 3. Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �Ҵ���� ����(allocated)�� ũ��(size)�� _count��ŭ �ø���.
	m_size += _count;

	// 2) capacity�� �����Ѵ�.
	m_capacity += capacity_inc;
}


template <class TDATA, class TALLOCATOR>
template <class TITERATOR>
void circular_list<TDATA, TALLOCATOR>::insert(const_iterator _where, TITERATOR _first, TITERATOR _last)
{
	// check) �ϳ��� ���ٸ� �ٷ� ����...
	CGD_RETURN_IF(_first==_last);


	//-----------------------------------------------------------------
	// 1. ���鼭 �����Ѵ�.
	//-----------------------------------------------------------------
	// declare) 
	iterator iter_insert;
	iterator iter_end;
	int count = 0;
	size_type capacity_inc = 0;

	try
	{
		// 1) �߰��� �ϱ� ���� ���� Node�� ��´�.
		//    (tail�� next���Ͱ� ���� Node�̴�.)
		iter_insert = ++end();	// m_tail�� _next.

		// 2) ���� Node�� ���� Insert�ϱ� �����Ѵ�.
		for (count=0; (_first != _last) && (iter_insert!=begin()); ++_first, ++iter_insert, ++count)
		{
			// - Construct�Ѵ�.
			m_alloc_val.construct(&(*iter_insert), *_first);
		}

		// 3) ����� ������ Node�� �����Ѵ�.(��� Node�� �������� ����...)
		//    (iter_insert�� ���� Node�� �̾ ������ �Ѵ�.)
		iter_end = iter_insert--;

		// 4) �����ؼ� ������ Node���� �߰��Ѵ�.
		for (capacity_inc=0; _first != _last; ++_first, ++capacity_inc)
		{
			// - Node�� ���� �����Ѵ�.
			_node* pnode_new = _make_node(*_first);

			// - Node�� �߰��Ѵ�.
			LINK_NODE(iter_insert._Ptr, pnode_new);

			// - iter_insert�� pnode_new�� �Ѵ�.
			iter_insert = pnode_new;
		}
	}
	// exception) Roll back�Ѵ�.
	catch(...)
	{
		// 1) �� Node��..
		iterator iter_rollback = ++end();

		// 2) Role back�ϸ� destroy�Ѵ�.
		while(iter_rollback!=iter_insert)
		{
			// - node�� destroy�Ѵ�.
			m_alloc_val.destroy(&(*iter_rollback));

			// - ���� Node�� �����Ѵ�.
			--iter_rollback;
		}

		// 3) �߰��Ҵ��ߴ� Node���� ��� Deallocate�Ѵ�.
		while(iter_end != iter_insert)
		{
			// - ��������� �̸� Next�� �����´�.
			iterator temp = iter_end++;

			// - node�� destroy�Ѵ�.
			m_alloc_val.destroy(&(*temp));
		}

		// throw) �ٽ� Throw!!!
		throw;
	}


	//-----------------------------------------------------------------
	// 2. Link�߰��ϱ�.
	//-----------------------------------------------------------------
	// 1) ������ ù��° Node�� ���.
	_node* pnode_start = m_tail->_next;

	// 2) _where�� Head�� ��� Head�� �ٲٱ�.
	if(_where._Ptr == m_head)
	{
		m_head = pnode_start;
	}

	// 3) �߰��� List�� �ϴ� ������ Circular List�� �ݴ´�.
	LINK_NODE(m_tail, iter_end._Ptr);

	// 4) _where�� ����ֱ�
	LINK_NODE(_where._Ptr->_pre, pnode_start);
	LINK_NODE(iter_insert._Ptr, _where._Ptr);


	//-----------------------------------------------------------------
	// 3. Node������ ����Ѵ�.
	//-----------------------------------------------------------------
	// 1) �Ҵ���� ����(allocated)�� ũ��(size)�� _count��ŭ �ø���.
	m_size += (count+capacity_inc);

	// 2) capacity�� �����Ѵ�.
	m_capacity += capacity_inc;
}



//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  erase: ���õ� node���� �����Ѵ�.
//
// ����)
//   erase�Լ��� _where�� ���ؼ� ������ ��ġ�� Ȥ�� ������ ������
//  node�� �����ϴ� �Լ��̴�. 
//   erase�Լ��� �ش��ϴ� �κ��� node���� ���Ÿ� ������ �ش� node
//  ���� deallocate��Ű���� �ʴ´�. ���ŵ� node���� tail�� ������
//  ������ node�� ������ ���� insert�� push ���� �� �� ��Ȱ��ȴ�.
//  ���� deallocate�� �ɸ��� �ð� ��ŭ �ð��� ������ �� �ִ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::erase(const_iterator _where)
{
	//-----------------------------------------------------------------
	// ChecK)
	//-----------------------------------------------------------------
	// 1) _where�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_where != end());

	// 2) �̰� ��.. �翬�ϴ�~
	CGDASSERT(_where._Ptr != 0, iterator());


	//-----------------------------------------------------------------
	// 1. Head�� ��� pop_front�� ��.
	//-----------------------------------------------------------------
	// - Head�� ��� push_front�� ��.
	if(_where == begin())
	{
		// - push_front�� ��.
		pop_front();

		// - begin()�� return��.
		return	begin();
	}


	//-----------------------------------------------------------------
	// 2. List���� ����
	//-----------------------------------------------------------------
	// 1) ���� Node
	_node* pnode_temp = _where._Ptr;

	// 2) ���� Node���� ������.
	_node* pnode_pre = pnode_temp->_pre;
	_node* pnode_next = pnode_temp->_next;

	// 3) Link�Ѵ�.
	LINK_NODE(pnode_pre, pnode_next);


	//-----------------------------------------------------------------
	// 3. ���� Node�� �Ҵ������Ѵ�.
	//-----------------------------------------------------------------
	// 1) Destruct�� ȣ���Ѵ�.
	m_alloc_node.destroy(pnode_temp);

	// 2) �����.
	LINK_NODE(pnode_temp, m_tail->_next); 
	LINK_NODE(m_tail, pnode_temp);


	//-----------------------------------------------------------------
	// 4. Node���� ó��
	//-----------------------------------------------------------------
	// 1) ũ�⸦ 1 ���δ�.
	--m_size;


	// return)Next Node�� Iterator�� �ǵ����ش�.
	return	iterator(pnode_next);
}


template <class TDATA, class TALLOCATOR>
typename circular_list<TDATA, TALLOCATOR>::iterator circular_list<TDATA, TALLOCATOR>::erase(const_iterator _first, const_iterator _last)
{
	//-----------------------------------------------------------------
	// 1. Destroy�ϸ� ���� ���Ƹ���...
	//-----------------------------------------------------------------
	// 1) First Node�� PreNode�� �̸� ���س��´�.
	_node* temp_node_first = _first._Ptr->_pre;

	// 2) ����... �پ��� ���ڸ� Ȯ���ϱ� ���� ������.
	size_type count = 0;
	const_iterator temp = _first;
	while(temp != _last)
	{
		// check) temp�� end���� ���� �ȵȴ�.
		CGDASSERT_ERROR(temp!=end());

		// declare) ���� Node�� ������ ����.
		iterator tempDel;

		// - Delete�� Node�� �ް� ���� Node��...
		tempDel = temp++;

		// - Destruct�� ȣ���Ѵ�.
		m_alloc_val.destroy(&(*tempDel));

		// - ���ڸ� ���Ѵ�.
		++count;
	}

	// check) ���࿡ ������ 0����� �׳� return
	CGD_RETURN_IF(count == 0, iterator(temp._Ptr));


	//-----------------------------------------------------------------
	// 2. ���� �����ϱ�.
	//-----------------------------------------------------------------
	// 1) erase�� ��ŭ ũ�⸦ ���δ�.
	m_size -= count;

	// 2) ó���� ��� Head�� �����.
	if(_first==begin())
	{
		// - Head�� �����...
		m_head = _last._Ptr;
		
		// return) �ǵ�����..
		return iterator(temp._Ptr);;
	}

	// 3) ���� ��� Tail�� �����.
	if(_last==end())
	{
		// - Tail�� �����...
		m_tail = temp._Ptr;
		
		// return) �ǵ�����..
		return iterator(temp._Ptr);
	}

	// 4) Tail�ڿ� ���̱�.
	LINK_NODE(temp._Ptr->_pre, m_tail->_next); 
	LINK_NODE(m_tail, _first._Ptr);

	// 5) ���� List�� ������.
	LINK_NODE(temp_node_first, temp._Ptr);


	// return)
	return iterator(temp._Ptr);
}



//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  attach: _where�� _node�� node ��ä�� ���δ�.
//  detach : _where�� _node�� node ��ä�� ������.
//
// ����)
//  insert�� erase�� ���� ����� �Լ��̴�. �׷��� attach�� detach��
//  node ��ä�� ����� �Լ��̴�.
//  splice�� �� ����� ���� circular_list��� �Ѵٸ� �� �Լ��� �׳� �ش� node
//  ���� ������� �Ѵ�. �� node��ü�� �����Ҵٰ� node��ü�� ���δ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::attach(const_iterator _where, const_iterator _pnode)
{
	// check) _where�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_where != end());

	// check) �̰� ��.. �翬�ϴ�~
	CGDASSERT_ERROR(_where._Ptr != 0);

	// 1) ������ �� Node
	_node* pnode = _where._Ptr;
	_node* pnode_new = _pnode._Ptr;

	// 2) Link�� �Ǵ�.
	LINK_NODE(pnode->_pre, pnode_new);
	LINK_NODE(pnode_new, pnode);

	// 3) _where�� Head�� ��� m_head�� _pnode�� �����.
	if(_where == begin())
	{
		m_head = pnode_new;
	}

	// 4) �Ҵ���� ����(allocated)�� ũ��(size)�� 1 �ø���.
	++m_size;
	++m_capacity;
}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::detach(const_iterator _where)
{
	// check) _where�� tail�̸� �ȵȴ�.
	CGDASSERT_ERROR(_where != end());

	// check) �̰� ��.. �翬�ϴ�~
	CGASSERT_ERROR(_where._Ptr != 0);

	// 1) head�� ��� ��ĭ �δ�.
	if(_where == begin())
	{
		m_head = m_head->_next;
	}

	// 2) ���� Node
	_node* pnode_temp = _where._Ptr;

	// 2) ���� Node���� ������.
	_node* pnode_pre = pnode_temp->_pre;
	_node* pnode_next = pnode_temp->_next;

	LINK_NODE(pnode_pre, pnode_next);

	// 3) ũ�⸦ 1 ���δ�.
	--m_size;
	--m_capacity;
}


//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  remove: _val���� circular_list���� �����Ѵ�.
//
// ����)
//  �Ϲ������� vector���� ��� remove�� �����ϰ� �Ǹ� ������ ����
//  ������ ������ circular_list�� ��� remove�� �� ���Ŀ� size�� ���δ�.
//  �˰���� ������ std::list�� unique�� ���̰� ����.
//  (�� erase��ü�� ó���ӵ��� ���� �ణ�� ��������� ���� �� �ִ�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::remove(const_reference _val)
{
	//-----------------------------------------------------------------
	// 1. ������... �ش��ϴ� ���� �����Ѵ�.
	//-----------------------------------------------------------------
	int count = 0;
	iterator iter_end = end();
	for(iterator iter=begin();iter!=iter_end;)
	{
		if(*iter == _val)
		{
			// - iterator�� ������ ����Ű���ϰ� ���� iterator�� �޾� ���´�.
			iterator iter_remove = iter++;

			// - Destruct�� ȣ���ϰ� pnode_temp�� �����.
			m_alloc_val.destroy(&(*iter_remove));

			// - ���� Node �� ���.
			++count;

			// check) ó���� ��� Head�� �����.
			if(iter_remove == begin())
			{
				// - Head�� �����...
				m_head = m_head->_next;
				continue;
			}

			// check) ���� ��� Tail�� �����.
			if(iter==end())
			{
				// - Tail�� �����...
				m_tail = m_tail->_pre;
				continue;
			}

			// - ���� Node���� ������.
			LINK_NODE(iter_remove._Ptr->_pre, iter_remove._Ptr->_next);

			// - Node�� Deallocate�Ѵ�.
			LINK_NODE(iter_remove._Ptr, m_tail->_next); 
			LINK_NODE(m_tail, iter_remove._Ptr);

			// ����~
			continue;
		}

		// - ����...
		++iter;
	}


	//-----------------------------------------------------------------
	// 2. ���ŵ� ������ŭ ���δ�.
	//-----------------------------------------------------------------
	// ���ŭ ũ�⸦ ���δ�.
	m_size -= count;
	m_capacity-= count;
}


//-----------------------------------------------------------------
//
//  remove_if: _pred�Լ��� ����� TRUE�� �Լ��� �����Ѵ�.
//
// ����)
//  �������� �˻��ϴ� �κ��� _pred�Լ��� ȣ���ϵ��� ��ü�Ͽ� �ش�
//  �Լ��� ����� TRUE�� ��� �ش� node�� ����� remove�Լ��̴�.
//  Ư�� ���ǿ� �����ϴ� node�� �����ϰ� ���� �� ����ϸ� �ȴ�.
//  _pred�Լ����� �ش� node�� iterator�� �����Ǹ� return�Ǵ� ����
//  true�̸� �ش� node�� �����Ѵ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
template<typename _Pr1>
void circular_list<TDATA, TALLOCATOR>::remove_if(_Pr1 _pred)
{
	int count = 0;
	iterator iter_end = end();
	for(iterator iter=begin();iter!=iter_end;)
	{
		if(_pred(*iter))
		{
			// - iterator�� ������ ����Ű���ϰ� ���� iterator�� �޾� ���´�.
			iterator iter_remove = iter++;

			// - Destruct�� ȣ���ϰ� pnode_temp�� �����.
			m_alloc_val.destroy(&(*iter_remove));

			// - ���� Node �� ���.
			++count;

			// check) ó���� ��� Head�� �����.
			if(iter_remove == begin())
			{
				// - Head�� �����...
				m_head = m_head->_next;
				continue;
			}

			// check) ���� ��� Tail�� �����.
			if(iter==end())
			{
				// - Tail�� �����...
				m_tail = m_tail->_pre;
				continue;
			}

			// - ���� Node���� ������.
			LINK_NODE(iter_remove._Ptr->_pre, iter_remove._Ptr->_next);

			// - Node�� Deallocate�Ѵ�.
			LINK_NODE(iter_remove._Ptr, m_tail->_next); 
			LINK_NODE(m_tail, iter_remove._Ptr);

			// ����~
			continue;
		}

		// - ����...
		++iter;
	}

	// ���ŭ ũ�⸦ ���δ�.
	m_size -= count;
	m_capacity -= count;
}




template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::swap(_mytype& _right)
{
	// check) ���� Container�� ��� �׳� �ǵ�����.
	CGD_RETURN_IF(&_right==this);


	// CaseA) Allocator�� ������...
	if (m_alloc_val == _right.m_alloc_val)
	{
		// �ٲ۴�~(������~)
		CGD_SWAP(m_head, _right.m_head);
		CGD_SWAP(m_tail, _right.m_tail);
		CGD_SWAP(m_size, _right.m_size);
		CGD_SWAP(m_capacity,_right.m_capacity);
	}
	// CaseB) Allocator�� �ٸ���...
	else
	{
		iterator _where = begin();
		splice(_where, _right);
		_right.splice(_right.begin(), *this, _where, end());
	}
}


//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  unique: List���� ���������� ���� ���� ������ Node�� �����Ѵ�.
//
// ����)
//  List���� ���������� ���� ���� ������ node�� �����ϴ� �Լ���
//  sort�� �� ���Ŀ� ����ؾ� ��Ȯ�� unique�� ���鸸 ���� �� �ִ�.
//  �˰���� ������ std::list�� unique�� ���̰� ����.
//  (�� erase��ü�� ó���ӵ��� ���� �ణ�� ��������� ���� �� �ִ�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::unique()
{
	//-----------------------------------------------------------------
	// ����) Unique�Լ�.
	//   Unique�Լ��� �������� �ߺ������� �����ϴ� �Լ��̴�.
	//   ���� ������ ó������ ������ iteration�� ���鼭 ������ ����
	//   �� �����. ��~
	//-----------------------------------------------------------------
	// check) ũ�Ⱑ 2���� ������ �׳� �ǵ�����.
	CGD_RETURN_IF(m_size<2);

	// 1) ���� �� �����ϱ�...
	iterator _first = begin();
	iterator _after = _first;

	// 2) Iteration�� ����.
	for (++_after; _after != end(); )
	{
		// check) _first�� _after�� ������ _after�� �����.
		if (_pred(*_first, *_after))
		{
			_after = erase(_after);
			continue;
		}

		// - ����~(_after�� _first�� �ִ´�.)
		_first = _after++;
	}
}

template <class TDATA, class TALLOCATOR>
template<typename _Pr2>
void circular_list<TDATA, TALLOCATOR>::unique(_Pr2 _pred)
{
	// check) ũ�Ⱑ 2���� ������ �׳� �ǵ�����.
	CGD_RETURN_IF(m_size < 2);

	// 1) ���� ���� �����Ѵ�.
	iterator _first = begin();
	iterator _after = _first;

	// 2) Iteration�� ����.
	for (++_after; _after != end();)
	{
		// check) _first�� _after�� ������ _after�� �����.
		if (*_first == *_after)
		{
			_after = erase(_after);
			continue;
		}

		// - ����~(_after�� _first�� �ִ´�.)
		_first = _after++;
	}
}



//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  splice: ������ node���� ��ä�� �ű��.
//
// ����)
//   circular_list�� ���� node����� container�� ���� ���� �߿� �ϳ��� 
//  Ư�� node�� move�Ҷ� �ش��ϴ� node�� ���Ḹ �� ���� ���� ���ϴ� ������
//  �̵��� �����ϴ�. splice�� �ٷ� �̷� ������ �ϴ� �Լ��̴�.
//  std::list������ sort������ ���� ���ȴ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _where, _mytype& _right)
{
	// check) 
	CGD_RETURN_IF(this == &_right || _right.empty());

	// 1) Right���� ������.
	_node* right_first = _right.m_head;
	_node* right_last = _right.m_tail->_pre;

	// 2) List�� 0��...
	_node* right_pre = right_first->_pre;
	LINK_NODE(right_pre, _right.m_tail);
	_right.m_head = _right.m_tail;

	// 3) Size�� Capasity�� ����Ѵ�.
	_right.m_capacity -= _right.m_size;
	m_size += _right.m_size; // ���� ���ϱ�~
	m_capacity += _right.m_size;

	// 4) Right�� Size�� 0����..
	_right.m_size = 0;

	// 5) �����ų �հ� �� Node
	_node* pnode_next = _where._Ptr;
	_node* pnode_pre = pnode_next->_pre;

	// 6) right First�� pnode_pre�� ����
	LINK_NODE(pnode_pre, right_first);

	// 7) right Last�� pnode_next�� ����
	LINK_NODE(right_last, pnode_next);

	// 8) _where�� Head�� ���...
	if(_where._Ptr == m_head)
	{
		m_head = right_first;
	}
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _where, _mytype& _right, const_iterator _first)
{
	// check) ���� _right�� ������ ���� �ϳ��� ������ Return
	CGD_RETURN_IF(_first == _right.end());

	// check) _right�� this�̸鼭 ó���̳� ���̸� Return~
	CGD_RETURN_IF(this == &_right && (_where == _first || _where == end()));


	// 1) ���Ŀ� ó���� ���� ��� �κ��� �����س��´�.
	_node* right_first = _first._Ptr;
	_node* right_last = _right.m_tail->_pre;

	// 2) ���� ��ü�� ������ ���Ƹ���.
	int count = 0;
	for(; _first!=_right.end(); ++_first)
	{
		++count;
	}

	// 3) Right�� List���� �ش� �κ��� ����� �� �յڸ�����~
	LINK_NODE(_first._pre, _right.m_tail);

	// 4) Size�� Capasity�� ����Ѵ�.
	_right.m_capacity -= count;
	_right.m_size -= count;
	m_size += count;	// ���� ���ϱ�~
	m_capacity += count;


	// 5) �����ų �հ� �� Node
	_node* pnode_next = _where._Ptr;
	_node* pnode_pre = pnode_next->_pre;

	// 6) right First�� pnode_pre�� ����
	LINK_NODE(pnode_pre, right_first);

	// 7) right Last�� pnode_next�� ����
	LINK_NODE(right_last, pnode_next);

	// 8) _where�� Head�� ���...
	if (_where._Ptr == m_head)
	{
		m_head = right_first;
	}
}


template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::splice(const_iterator _where, _mytype& _right, const_iterator _first, const_iterator _last)
{
	// check) 
	CGD_RETURN_IF(_first == _last || (this == &_right && _where == _last));


	// 1) ���Ŀ� ó���� ���� ��� �κ��� �����س��´�.
	_node* right_first = _first._Ptr;
	_node* right_last = _last._Ptr->_pre;

	// 2) ���� ��ü�� ������ ���Ƹ���.
	size_type count = 0;

	// 3-1) ���� Container��� ������ȭ�� ����! ���� �� �ʿ����.
	if (this == &_right)
	{
	}
	// 3-2) ��ä�ζ� �� �ʿ����.
	else if (_first == _right.begin() && _last == _right.end())
	{
		count = _right.m_size;	
	}
	else
	{
		for(; _first!=_last; ++_first)
		{
			++count;
		}
	}

	// 4) Right�� List���� �ش� �κ��� ����� �� �յڸ�����~
	LINK_NODE(_first._Ptr->_pre, _last._Ptr);

	// 5) Size�� Capasity�� ����Ѵ�.
	_right.m_capacity -= count;
	_right.m_size -= count;
	m_size += count; // ���� ���ϱ�~
	m_capacity += count;

	// 6) �����ų �հ� �� Node
	_node* pnode_next = _where._Ptr;
	_node* pnode_pre = pnode_next->_pre;

	// 7) right First�� pnode_pre�� ����
	LINK_NODE(pnode_pre, right_first);

	// 8) right Last�� pnode_next�� ����
	LINK_NODE(right_last, pnode_next);
}




//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  merge: _right list�� _pred���ǿ� ���� ���� list�� ��ģ��.
//
// ����)
//   _right list�� _pred ���ǿ� ���� ���� list�� ��ģ��. 
//  �� list�� ��� sort�� �Ǿ� �־�� ���ϴ� ������ ��Ȯ�� ������ 
//  ����.
//  �⺻���� �˰����� std::list�� �����ϴ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
template<typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::merge(_mytype& _right, _Pr3 _pred)
{
	// check) ���� list��� Merge�� �� �ʿ� ����.
	CGD_RETURN_IF(&_right == this);

	// 1) ������������ Ȯ���Ѵ�.
	if(front() >= _right.back())
	{
		// - Right�� m_head �տ� ��ä�� ���̱�.
		LINK_NODE(m_head->_pre, _right.m_head)
		LINK_NODE(_right.m_tail->pre, m_head)
	}
	// 2) ������������ Ȯ���Ѵ�.
	else if(back() <= _right.front())
	{
		// - _right�� m_tail �ڿ� ��ä�� ���̱�
		LINK_NODE(m_tail->_pre, _right.m_head)
		LINK_NODE(_right.m_tail->_pre, m_tail)
	}
	// 3) ���ʷ� ���̱�...(temp_list�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	else
	{
		// NodeA�� NodeB�� �����Ѵ�.
		_node*	node_a = m_head;
		node_a->_pre  = m_head->_pre;
		_node*	node_b = _right.m_head;

		for(;;)
		{
			// B�� Next��(B�� A�տ� ���� �ִ´�.)
			if(_pred(node_a->_data, node_b->_data))
			{
				// - node_b�� ��� ��� ���´�.
				_node* temp_b_next = node_b->_next;

				// - node_b�� NodeA�տ� ���δ�.
				LINK_NODE(node_a->_pre, node_b);
				LINK_NODE(node_b, node_a);

				// - node_b�� �������� �ű��.
				node_b = temp_b_next;

				// - node_b�� ������ Ȯ���Ѵ�.
				CGD_BREAK_IF(temp_b_next==_right.m_tail);
			}
			// A�� Next��(�׳� �ѱ��.)
			else
			{
				// node_a�� �������� �ű��.
				_node* temp_a_next = node_a->_next;

				// node_a�� ������ Ȯ���Ѵ�.
				if(temp_a_next==m_tail)
				{
					// node_a�ڿ� node_b�� ���δ�.
					LINK_NODE(node_a, node_b);
					LINK_NODE(node_b, m_tail);

					break;
				}

				node_a = temp_a_next;
			}
		}
	}


	// 4) _right.m_size�� �ӽ÷� ������ ���´�.
	size_type temp_size = _right.m_size;

	// 5) List�� Size�� count�� �����Ѵ�.
	m_size += temp_size;
	m_size += temp_size;

	// 6) Right List�� Size�� count�� �����Ѵ�.
	_right.m_size = 0;
	_right.m_size -= temp_size;

	// 7) Right List�� �����Ѵ�.
	LINK_NODE(_right.m_head, _right.m_head);
	_right.m_tail = _right.m_head;

}

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::merge(_mytype& _right)
{
	// check) ���� list��� Merge�� �� �ʿ� ����.
	CGD_RETURN_IF(&_right == this);


	// 1) ������������ Ȯ���Ѵ�.
	if(front() >= _right.back())
	{
		// - Right�� m_head �տ� ��ä�� ���̱�.
		LINK_NODE(m_head->_pre, _right.m_head)
		LINK_NODE(_right.m_tail->pre, m_head)
	}
	// 2) ������������ Ȯ���Ѵ�.
	else if(back() <= _right.front())
	{
		// - _right�� m_tail �ڿ� ��ä�� ���̱�
		LINK_NODE(m_tail->_pre, _right.m_head)
		LINK_NODE(_right.m_tail->_pre, m_tail)
	}
	// 3) ���ʷ� ���̱�...(temp_list�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	else
	{
		// NodeA�� NodeB�� �����Ѵ�.
		_node*	node_a = m_head;
		node_a->_pre = m_head->_pre;
		_node*	node_b = _right.m_head;

		for(;;)
		{
			// B�� �������� B�� Next��...
			if(node_a->_data > node_b->_data)
			{
				// - node_b�� ��� ��� ���´�.
				_node* temp_b_next = node_b->_next;

				// - node_b�� NodeA�տ� ���δ�.
				LINK_NODE(node_a->_pre, node_b);
				LINK_NODE(node_b, node_a);

				// - node_b�� �������� �ű��.
				node_b = temp_b_next;

				// - node_b�� ������ Ȯ���Ѵ�.
				CGD_BREAK_IF(temp_b_next == _right.m_tail);
			}
			// A�� Next��(�׳� �ѱ��.)
			else
			{
				// node_a�� �������� �ű��.
				_node* temp_a_next = node_a->_next;

				// node_a�� ������ Ȯ���Ѵ�.
				if(temp_a_next == m_tail)
				{
					// node_a�ڿ� node_b�� ���δ�.
					LINK_NODE(node_a, node_b);
					LINK_NODE(node_b, m_tail);

					break;
				}

				node_a = temp_a_next;
			}
		}
	}


	// 4) _right.m_size�� �ӽ÷� ������ ���´�.
	size_type temp_size = _right.m_size;

	// 5) List�� Size�� count�� �����Ѵ�.
	m_size += temp_size;
	m_size += temp_size;

	// 6) Right List�� Size�� count�� �����Ѵ�.
	_right.m_size = 0;
	_right.m_size -= temp_size;

	// 7) Right List�� �����Ѵ�.
	LINK_NODE(_right.m_head, _right.m_head);
	_right.m_tail = _right.m_head;
}

#ifdef _CGD_LIST_FAST_SORT
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_slice_for_sort(_node& temp_list, _node*& node_now)
{
	//-----------------------------------------------------------------
	// ����)
	//  merge sort�� ���� list�� ���� ������ ���� ������ �ϴ� �� �Լ��̴�.
	//  �� �Լ��� 4���� �����ؼ� �����ִ� �Լ��̴�.
	//  �Ѳ����� 4���� node�� �������� ���� sort�� �Ͽ� �����ֱ� ������
	//  2���� ���� �Լ��� ���� �뷫 10%~20%���� �ӵ������ ������ �ش�.
	//  ������ code�� ����ġ�� ����� ���� �����Ƿ� code�� ���� �߿���
	//  ��� 2���� ���� �Լ��� ����ϱ⸦ ���Ѵ�.
	//  (std::list�� ��� 1���� ��� ó���ϵ��� �ؼ� �ӵ����� ���ذ�
	//  �ִ�.)
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// 1. ù���� ������
	//-----------------------------------------------------------------
	// 1) ù��° Node�� ��´�.
	temp_list._next = node_now;

	// 2) ���� Node
	node_now = node_now->_next;

	// 3) 1�� ���� ��� ������.
	if(node_now==0)
	{
		_node* temp = temp_list._next;

		temp_list._pre = temp;
		temp->_next = 0;

		return;
	}


	//-----------------------------------------------------------------
	// 2. �ι�° ������
	//-----------------------------------------------------------------
	// 1) 2��° Node�� ��´�.
	_node* pnode_second = node_now;

	// 2) ���� Node
	node_now = node_now->_next;

	// 3) 2���� Sort�Ѵ�.
	if(temp_list._next->_data > pnode_second->_data)
	{
		LINK_NODE(pnode_second, temp_list._next)

		// check) 2�� ���� ��� ������.
		if(node_now==0)
		{
			_node* temp = temp_list._next;

			temp_list._pre = temp;
			temp->_next = 0;
			temp_list._next = pnode_second;

			return;
		}

		LINK_NODE(temp_list._next, node_now)
		CGD_SWAP(pnode_second, temp_list._next);
	}

	// check) 2�� ���� ��� ������.
	if(node_now==0)
	{
		temp_list._pre = pnode_second;
		pnode_second->_next	 = 0;
		return;
	}


	//-----------------------------------------------------------------
	// 3. ����° ������
	//-----------------------------------------------------------------
	// 1) 3��° Node�� ��´�.
	_node* pnode_third = node_now;

	// 2) ���� Node
	node_now = node_now->_next;

	// 3) 3���� Sort�Ѵ�.
	if(pnode_second->_data > pnode_third->_data)
	{
		CGD_SWAP(pnode_third, pnode_second);

		if(temp_list._next->_data > pnode_second->_data)
		{
			LINK_NODE(pnode_second, temp_list._next)
			LINK_NODE(temp_list._next, pnode_third)

			CGD_SWAP(pnode_second, temp_list._next);
		}
		else
		{
			LINK_NODE(temp_list._next, pnode_second);
			LINK_NODE(pnode_second, pnode_third);
		}
	}

	// 4) 3�� ���� ��� ������.
	if(node_now!=0)
	{
		LINK_NODE(pnode_third, node_now)
	}
	else
	{
		temp_list._pre = pnode_third;
		pnode_third->_next = 0;
		return;
	}


	//-----------------------------------------------------------------
	// 3. �׹�° ������
	//-----------------------------------------------------------------
	// 1) nodwNow�� 4��°���̴�.
	_node* nodeForth = node_now;

	// 2) ���� Node
	node_now = node_now->_next;

	// Sort 4) 4���� Sort�Ѵ�.
	if(pnode_third->_data > nodeForth->_data)
	{
		temp_list._pre = pnode_third;
		pnode_third->_next = 0;

		if(pnode_second->_data > nodeForth->_data)
		{
			if(temp_list._next->_data > nodeForth->_data)
			{
				LINK_NODE(nodeForth, temp_list._next);
				temp_list._next	 = nodeForth;
			}
			else
			{
				LINK_NODE(temp_list._next, nodeForth);
				LINK_NODE(nodeForth, pnode_second);
			}
		}
		else
		{
			LINK_NODE(pnode_second, nodeForth);
			LINK_NODE(nodeForth, pnode_third);
		}
	}
	else
	{
		temp_list._pre = nodeForth;
		nodeForth->_next = 0;
	}
}
#else

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_slice_for_sort(_node& temp_list, _node*& node_now)
{
	//-----------------------------------------------------------------
	// ����)
	//  merge sort�� ���� list�� ���� ������ ���� ������ �ϴ� �� �Լ��̴�.
	//  �� �Լ��� 2���� �����ؼ� �����ִ� �Լ��̴�.
	//  ���� �Լ��� 4���� �����ִ� �Լ����� ������� ������ �ڵ尡 Ŀ����
	//  �ֱ� ������ ������ code�� ���� ��� �� �Լ��� ����ϱ⸦ ���Ѵ�.
	//  �ӵ��� 10~20%���� �������� code�� ���� 1/3�� ���� �ʴ´�.
	//-----------------------------------------------------------------

	// 1) �ΰ��� Node�� �о���δ�.
	_node* nodeFirst = node_now;
	_node* pnode_second = node_now->_next;

	// ChecK) 1�����ΰ��� �˻��Ѵ�.
	if(pnode_second == 0)
	{
		temp_list._next = nodeFirst;
		temp_list._pre = nodeFirst;
		nodeFirst->_next = 0;

		return;
	}

	// 2) ���� Node~
	node_now = pnode_second->_next;

	// Case A) First�� �� ũ�� �ٲ۴�.
	if(nodeFirst->_data > pnode_second->_data)
	{
		LINK_NODE(pnode_second, nodeFirst);

		temp_list._next = pnode_second;
		temp_list._pre = nodeFirst;
		nodeFirst->_next = 0;
	}
	// Case B) Second�� �� ũ�ų� ������ �״�� �д�.
	else
	{
		temp_list._next = nodeFirst;
		temp_list._pre = pnode_second;
		pnode_second->_next = 0;
	}
}
#endif

template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::_merge_for_sort(_node& temp_list, _node& nowList)
{
	//-----------------------------------------------------------------
	// ����)
	//   merge sort�� ���� �ΰ��� �������� list�� �����ִ� �Լ��̴�.
	//  �ϳ��� list�� �������� �ٸ� �ϳ��� list������ ������ �Ǵ� list
	//  ���̿� �����ִ� ���·� code�� �����ȴ�.
	//   ������ lstd::list�� ���ؼ� 0�񱳸� �ϰ� �����ν� ���� �񱳿�
	//  �� ���� �ӵ� ����� ���Ͽ��� ���������� ���� list�� �ٸ� ��
	//  list�� ���� ������ ũ�ų� ���� node�ΰ��� �˻��ϴ� �κ��� �־�
	//  ���� ���� ���ĵ� ��� �ſ� ���� sort�� �����ϵ��� �˰�����
	//  �����Ǿ���. �� �� �κ��� ������ ������ ���� �ʴ� data�� ������
	//  node�� ���� ���� ��� hit�Ǵ� Ȯ���� ���� sort�� ������ ����
	//  ������ �ش�.
	//-----------------------------------------------------------------

	// ChecK) ������������ Ȯ���Ѵ�.
	if(temp_list._next->_data >= nowList._pre->_data)
	{
		// - Link~
		LINK_NODE(nowList._pre, temp_list._next)

		// - Tail ����~
		temp_list._next = nowList._next;

		// - Merge������ bin_list�� Reset�Ѵ�.
		nowList._next = 0;

		// - binList Clear
		return;
	}

	// ChecK) 
	if(temp_list._pre->_data <= nowList._next->_data)
	{
		// - Link~
		LINK_NODE(temp_list._pre, nowList._next)

		// - Tail ����~
		temp_list._pre = nowList._pre;

		// - Merge������ bin_list�� Reset�Ѵ�.
		nowList._next = 0;

		// - binList Clear
		return;
	}

	// 3) ���ʷ� ���̱�...(temp_list�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	_node*	node_a = temp_list._next;
	node_a->_pre = &temp_list;
	_node*	node_b = nowList._next;
	for(;;)
	{
		// - B�� A���̿� �������� B�� Next��...
		if(node_a->_data > node_b->_data)
		{
			// declare) 
			_node* node_b_pre;

			// - node_b�� NodeA�տ� ���δ�.
			LINK_NODE(node_a->_pre, node_b);

			// - ���� B��...
			node_b_pre = node_b;
			node_b = node_b->_next;

			// - B�� Ŭ������... ������..
			HERE:

			if(node_b==0)
			{
				// - Node�� �����Ѵ�.
				LINK_NODE(node_b_pre, node_a);

				// - Merge������ bin_list�� Reset�Ѵ�.
				nowList._next = 0;

				return;
			}

			if(node_a->_data > node_b->_data)
			{
				// ����~
				node_b_pre = node_b;
				node_b = node_b->_next;

				goto HERE;
			}

			// - Node�� �����Ѵ�.
			LINK_NODE(node_b_pre, node_a);
		}

		// - A�� ��������...
		_node* temp_a_next = node_a->_next;

		// node_a�� ������ Ȯ���Ѵ�.
		if(temp_a_next==0)
		{
			// node_a�ڿ� node_b�� ���δ�.
			LINK_NODE(node_a, node_b);
			temp_list._pre = nowList._pre;

			// - Merge������ bin_list�� Reset�Ѵ�.
			nowList._next = 0;

			return;
		}

		node_a = temp_a_next;
	}
}


template <class TDATA, class TALLOCATOR>
template <typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::_merge_for_sort(_node& temp_list, _node& nowList, _Pr3 _pred)
{
	//-----------------------------------------------------------------
	// ����)
	//   merge sort�� ���� �ΰ��� �������� list�� �����ִ� �Լ��̴�.
	//  �ϳ��� list�� �������� �ٸ� �ϳ��� list������ ������ �Ǵ� list
	//  ���̿� �����ִ� ���·� code�� �����ȴ�.
	//   ������ lstd::list�� ���ؼ� 0�񱳸� �ϰ� �����ν� ���� �񱳿�
	//  �� ���� �ӵ� ����� ���Ͽ��� ���������� ���� list�� �ٸ� ��
	//  list�� ���� ������ ũ�ų� ���� node�ΰ��� �˻��ϴ� �κ��� �־�
	//  ���� ���� ���ĵ� ��� �ſ� ���� sort�� �����ϵ��� �˰�����
	//  �����Ǿ���. �� �� �κ��� ������ ������ ���� �ʴ� data�� ������
	//  node�� ���� ���� ��� hit�Ǵ� Ȯ���� ���� sort�� ������ ����
	//  ������ �ش�.
	//-----------------------------------------------------------------

	// ChecK) ������������ Ȯ���Ѵ�.
	if(!_pred(temp_list._next->_data, nowList._pre->_data))	// if(temp_list._next->_data >= nowList._pre->_data)
	{
		// - Link~
		LINK_NODE(nowList._pre, temp_list._next)

		// - Tail ����~
		temp_list._next = nowList._next;

		// - Merge������ bin_list�� Reset�Ѵ�.
		nowList._next = 0;

		// - binList Clear
		return;
	}

	// ChecK) 
	if(!_pred(nowList._next->_data, temp_list._pre->_data))	// if(temp_list._pre->_data <= nowList._next->_data)
	{
		// - Link~
		LINK_NODE(temp_list._pre, nowList._next)

		// - Tail ����~
		temp_list._pre = nowList._pre;

		// - Merge������ bin_list�� Reset�Ѵ�.
		nowList._next = 0;

		// - binList Clear
		return;
	}

	// 3) ���ʷ� ���̱�...(temp_list�� Main�̰� binList�� ���⿡ �ٴ� ����.)				
	_node*	node_a = temp_list._next;
	node_a->_pre = &temp_list;
	_node*	node_b = nowList._next;
	for(;;)
	{
		// - B�� A���̿� �������� B�� Next��...
		if(_pred(node_b->_data, node_a->_data))	// if(node_a->_data > node_b->_data)
		{
			// declare) 
			_node* node_b_pre;

			// - node_b�� NodeA�տ� ���δ�.
			LINK_NODE(node_a->_pre, node_b);

			// - ���� B��...
			node_b_pre = node_b;
			node_b = node_b->_next;

			// - B�� Ŭ������... ������..
			HERE:

			if(node_b == 0)
			{
				// - Node�� �����Ѵ�.
				LINK_NODE(node_b_pre, node_a);

				// - Merge������ bin_list�� Reset�Ѵ�.
				nowList._next = 0;

				return;
			}

			if(_pred(node_b->_data, node_a->_data))	// if(node_a->_data > node_b->_data)
			{
				// ����~
				node_b_pre = node_b;
				node_b = node_b->_next;

				goto HERE;
			}

			// - Node�� �����Ѵ�.
			LINK_NODE(node_b_pre, node_a);
		}

		// - A�� ��������...
		_node* temp_a_next = node_a->_next;

		// node_a�� ������ Ȯ���Ѵ�.
		if(temp_a_next == 0)
		{
			// node_a�ڿ� node_b�� ���δ�.
			LINK_NODE(node_a, node_b);
			temp_list._pre = nowList._pre;

			// - Merge������ bin_list�� Reset�Ѵ�.
			nowList._next = 0;

			return;
		}

		node_a = temp_a_next;
	}
}

//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  sort: ������ �����Ѵ�.
//
// ����)
//  vector�� ���� ���������� ������ ��� standard algorithm�� ���
//  �Ͽ� sort�� ����ϸ� ȿ�������� ����ȴ�. �׷��� list�� ���
//  �ſ� ��ȿ�������� �����ϱ� ������ ���������� ��ü���� sort��
//  ������ �ִ�.
// 
//  * �˰��� ���� ����
//   - �⺻�� �˰����� Merge Sort�� ����ϸ�  std::list�� sort��
//     �����ϴ�. ������ �������� �˰����� �������� �����Ǿ���.
//   - �־��� ��� O(N) = NlogN�� �ؼ��Ѵ�.(std::list�� ����.)
//   - �ּ��� ��� �ð����⵵�� ȹ�������� �ٿ���.
//     (�ּ��� ��� N/2+logN�����̴�.)
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::sort()
{
	//-----------------------------------------------------------------
	// check) 
	//-----------------------------------------------------------------
	// 1) ũ�Ⱑ 2������ ��� �׳� �ǵ�����.
	CGD_RETURN_IF(m_size < 2);


	//-----------------------------------------------------------------
	// 1. Sort�� �����Ѵ�.
	//-----------------------------------------------------------------
	size_type _max_bin = 0;
	_node bin_list[32];

	// declare) Sliced Node.
	_node temp_list;
	//size_type		bin;

	// 1) ���� Size
	size_type now_size = m_size;

	// 2) ���� ó��~
	_node* node_head_pre = m_head->_pre;
	_node* node_now = m_head;
	size_type last_bin;

	if(now_size>=4)
	{
		for(;;)	// 4���� merge�Ѵ�.
		{
			//-------------------------------------
			// Step1. 4���� �߶󳽴�.
			//-------------------------------------
			// 1) Now Node
			temp_list._next = node_now; node_now=node_now->_next;

			// 2) First�� Second�� ���Ѵ�.
			_node*	psecond = node_now; node_now=node_now->_next;
			if(temp_list._next->_data>psecond->_data)
			{
				LINK_NODE(psecond, temp_list._next);
				LINK_NODE(temp_list._next, node_now);
				CGD_SWAP(temp_list._next, psecond);
			}

			// 3) Second�� Third�� ���Ѵ�.
			_node* pthird = node_now; node_now=node_now->_next;
			if(psecond->_data>pthird->_data)
			{
				// - Third<First<Second
				if(temp_list._next->_data>=pthird->_data)
				{
					LINK_NODE(pthird, temp_list._next);

					_node* temp = psecond;
					psecond = temp_list._next;
					temp_list._next = pthird;
					pthird = temp;
				}
				// - First<Third<Second
				else
				{
					LINK_NODE(temp_list._next, pthird);
					LINK_NODE(pthird, psecond);
					CGD_SWAP(psecond, pthird);
				}

				LINK_NODE(pthird, node_now);
			}

			// 4) Third�� Forth�� ���Ѵ�.
			temp_list._pre = node_now; node_now=node_now->_next;
			if(pthird->_data>temp_list._pre->_data)
			{
				// - First<Second<=Forth<Third
				if(psecond->_data<=temp_list._pre->_data)
				{
					LINK_NODE(psecond, temp_list._pre);
					LINK_NODE(temp_list._pre, pthird);
				}
				// - First<Forth<Second<Third
				else if(temp_list._next->_data<temp_list._pre->_data)
				{
					LINK_NODE(temp_list._next, temp_list._pre);
					LINK_NODE(temp_list._pre, psecond);
				}
				// - Forth<=First<Second<Third
				else
				{
					LINK_NODE(temp_list._pre, temp_list._next);
					temp_list._next = temp_list._pre;
				}

				temp_list._pre = pthird;
			}

			temp_list._pre->_next = 0;


			//-------------------------------------
			// Step2. Merge�� �Ѵ�.
			//-------------------------------------
			size_type bin=0;
			for(; bin_list[bin]._next!=0; ++bin)
			{
				// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
				if(bin==_max_bin)
				{
					_max_bin = bin+1;
					break;
				}

				// 1) temp_list�� Merge~
				_merge_for_sort(temp_list, bin_list[bin]);
			}

			// 1) 
			bin_list[bin] = temp_list;

			//-------------------------------------
			// Step3. Merge����� binList�� �����Ѵ�.
			//-------------------------------------
			// 1) Size�� ���δ�.
			now_size -=4;

			// check) ������ �ƴ��� Ȯ��
			if(now_size<4)
			{
				last_bin = bin + 1;
				break;
			}
		}
	}
	else
	{
	}

	// 3�� ���� Merge
	if(now_size!=0)
	{
		//-------------------------------------
		// Step1. Node�� �����.
		//-------------------------------------
		for(;;)
		{
			// 1) 1�� ���� ���...
			temp_list._next = node_now;

			if(now_size==1)
			{
				temp_list._pre = node_now;
				break;
			}

			// 2) 2���� ���...
			node_now = node_now->_next; temp_list._pre = node_now->_next;
			if(temp_list._next->_data>node_now->_data)
			{
				LINK_NODE(node_now, temp_list._next);
				LINK_NODE(temp_list._next, temp_list._pre);
				CGD_SWAP(temp_list._next, node_now);
			}

			if(now_size==2)
			{
				temp_list._pre = node_now;
				break;
			}

			// 3) 3���� ���...
			if(node_now->_data>temp_list._pre->_data)
			{
				// third<first<second
				if(temp_list._next->_data>temp_list._pre->_data)
				{
					LINK_NODE(temp_list._pre, temp_list._next);
					temp_list._next = temp_list._pre;
				}
				// first<third<second
				else
				{
					LINK_NODE(temp_list._next, temp_list._pre);
					LINK_NODE(temp_list._pre, node_now);
				}

				temp_list._pre = node_now;
			}
			break;
		}
		temp_list._pre->_next = 0;

		//-------------------------------------
		// Step2. Merge�� �Ѵ�.
		//-------------------------------------
		size_type bin=0;
		for(; bin_list[bin]._next!=0; ++bin)
		{
			// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
			if(bin==_max_bin)
			{
				_max_bin = bin+1;
				break;
			}

			// 1) temp_list�� Merge~
			_merge_for_sort(temp_list, bin_list[bin]);
		}

		last_bin = bin+1;
	}

	//-------------------------------------
	// Step4. ������ Merge�ؼ� ���Ѵ�.
	//-------------------------------------
	// 2) ��ġ��~
	for(; last_bin<_max_bin; ++last_bin)
	{
		// 1) Check bin_list�� ��� ������ ����~
		CGD_CONTINUE_IF(bin_list[last_bin]._next==0);

		// 2) temp_list�� Merge~
		_merge_for_sort(temp_list, bin_list[last_bin]);
	}

	//-------------------------------------
	// Step5. ���������� List�� �����ϱ�.
	//-------------------------------------
	// 1) Sort�Ϸ�� List Link�� �Ǵ�.
	LINK_NODE(node_head_pre, temp_list._next);
	LINK_NODE(temp_list._pre, m_tail);

	// 2) Head�� ���� �����Ѵ�.
	m_head = temp_list._next;
}


template <class TDATA, class TALLOCATOR>
template<typename _Pr3>
void circular_list<TDATA, TALLOCATOR>::sort(_Pr3 _pred)
{
	//-----------------------------------------------------------------
	// check) 
	//-----------------------------------------------------------------
	// 1) ũ�Ⱑ 2������ ��� �׳� �ǵ�����.
	CGD_RETURN_IF(m_size < 2);


	//-----------------------------------------------------------------
	// 1. Sort�� �����Ѵ�.
	//-----------------------------------------------------------------
	size_type _max_bin = 0;
	_node bin_list[32];

	// declare) Sliced Node.
	_node temp_list;
	//size_type bin;

	// 1) ���� Size
	size_type now_size = m_size;

	// 2) ���� ó��~
	_node* node_head_pre = m_head->_pre;
	_node* node_now = m_head;
	size_type last_bin;

	if(now_size>=4)
	{
		for(;;)	// 4���� merge�Ѵ�.
		{
			//-------------------------------------
			// Step1. 4���� �߶󳽴�.
			//-------------------------------------
			// 1) Now Node
			temp_list._next = node_now; node_now=node_now->_next;

			// 2) First�� Second�� ���Ѵ�.
			_node*	psecond = node_now; node_now = node_now->_next;
			if(_pred(psecond->_data, temp_list._next->_data)) //if(temp_list._next->_data>psecond->_data)
			{
				LINK_NODE(psecond, temp_list._next);
				LINK_NODE(temp_list._next, node_now);
				CGD_SWAP(temp_list._next, psecond);
			}

			// 3) Second�� Third�� ���Ѵ�.
			_node* pthird = node_now; node_now=node_now->_next;
			if(_pred(pthird->_data, psecond->_data)) // if(psecond->_data>pthird->_data)
			{
				// - Third<First<Second
				if(!_pred(temp_list._next->_data, pthird->_data))	// if(temp_list._next->_data>=pthird->_data)
				{
					LINK_NODE(pthird, temp_list._next);

					_node* temp = psecond;
					psecond = temp_list._next;
					temp_list._next = pthird;
					pthird = temp;
				}
				// - First<Third<Second
				else
				{
					LINK_NODE(temp_list._next, pthird);
					LINK_NODE(pthird, psecond);
					CGD_SWAP(psecond, pthird);
				}

				LINK_NODE(pthird, node_now);
			}

			// 4) Third�� Forth�� ���Ѵ�.
			temp_list._pre = node_now; node_now=node_now->_next;
			if(_pred(temp_list._pre->_data, pthird->_data))	// if(pthird->_data>temp_list._pre->_data)
			{
				// - First<Second<=Forth<Third
				if(!_pred(psecond->_data, temp_list._pre->_data))	// if(psecond->_data<=temp_list._pre->_data)
				{
					LINK_NODE(psecond, temp_list._pre);
					LINK_NODE(temp_list._pre, pthird);
				}
				// - First<Forth<Second<Third
				else if(_pred(temp_list._next->_data, temp_list._pre->_data))	// else if(temp_list._next->_data<temp_list._pre->_data)
				{
					LINK_NODE(temp_list._next, temp_list._pre);
					LINK_NODE(temp_list._pre, psecond);
				}
				// - Forth<=First<Second<Third
				else
				{
					LINK_NODE(temp_list._pre, temp_list._next);
					temp_list._next = temp_list._pre;
				}

				temp_list._pre = pthird;
			}

			temp_list._pre->_next = 0;


			//-------------------------------------
			// Step2. Merge�� �Ѵ�.
			//-------------------------------------
			size_type bin = 0;
			for(; bin_list[bin]._next != 0; ++bin)
			{
				// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
				if(bin==_max_bin)
				{
					_max_bin = bin+1;
					break;
				}

				// 1) temp_list�� Merge~
				_merge_for_sort(temp_list, bin_list[bin], _pred);
			}

			// 1) 
			bin_list[bin] = temp_list;

			//-------------------------------------
			// Step3. Merge����� binList�� �����Ѵ�.
			//-------------------------------------
			// 1) Size�� ���δ�.
			now_size -=4;

			// check) ������ �ƴ��� Ȯ��
			if(now_size<4)
			{
				last_bin = bin+1;
				break;
			}
		}
	}
	else
	{
	}

	// 3�� ���� Merge
	if(now_size!=0)
	{
		//-------------------------------------
		// Step1. Node�� �����.
		//-------------------------------------
		for(;;)
		{
			// 1) 1�� ���� ���...
			temp_list._next = node_now;

			if(now_size==1)
			{
				temp_list._pre = node_now;
				break;
			}

			// 2) 2���� ���...
			node_now = node_now->_next; temp_list._pre = node_now->_next;
			if(_pred(node_now->_data, temp_list._next->_data))	// if(temp_list._next->_data>node_now->_data)
			{
				LINK_NODE(node_now, temp_list._next);
				LINK_NODE(temp_list._next, temp_list._pre);
				CGD_SWAP(temp_list._next, node_now);
			}

			if(now_size==2)
			{
				temp_list._pre = node_now;
				break;
			}

			// 3) 3���� ���...
			if(_pred(temp_list._pre->_data, node_now->_data))	// if(node_now->_data>temp_list._pre->_data)
			{
				// third<first<second
				if(_pred(temp_list._pre->_data, temp_list._next->_data))	// if(temp_list._next->_data>temp_list._pre->_data)
				{
					LINK_NODE(temp_list._pre, temp_list._next);
					temp_list._next	 = temp_list._pre;
				}
				// first<third<second
				else
				{
					LINK_NODE(temp_list._next, temp_list._pre);
					LINK_NODE(temp_list._pre, node_now);
				}

				temp_list._pre = node_now;
			}
			break;
		}
		temp_list._pre->_next = 0;


		//-------------------------------------
		// Step2. Merge�� �Ѵ�.
		//-------------------------------------
		size_type bin = 0;
		for(; bin_list[bin]._next != 0; ++bin)
		{
			// ChecK) MaxBin���� ������ Loop�� Ż���Ѵ�.(�̶� Max Bin���� ������Ų��.)
			if(bin==_max_bin)
			{
				_max_bin = bin+1;
				break;
			}

			// 1) temp_list�� Merge~
			_merge_for_sort(temp_list, bin_list[bin], _pred);
		}

		last_bin = bin+1;
	}

	//-------------------------------------
	// Step4. ������ Merge�ؼ� ���Ѵ�.
	//-------------------------------------
	for(; last_bin<_max_bin; ++last_bin)
	{
		// 1) Check bin_list�� ��� ������ ����~
		CGD_CONTINUE_IF(bin_list[last_bin]._next == 0);

		// 2) temp_list�� Merge~
		_merge_for_sort(temp_list, bin_list[last_bin], _pred);
	}

	//-------------------------------------
	// Step5. ���������� List�� �����ϱ�.
	//-------------------------------------
	// 1) Sort�Ϸ�� List Link�� �Ǵ�.
	LINK_NODE(node_head_pre, temp_list._next);
	LINK_NODE(temp_list._pre, m_tail);

	// 2) Head�� ���� �����Ѵ�.
	m_head = temp_list._next;
}




//-----------------------------------------------------------------
// CGDK::circular_list)
//
//  shrink: ������ node�� �����Ѵ�.
//
// ����)
//  CGDK::circular_list�� ��� pop�̳� clear, erase Ȥ�� remove�� ������ ��  
//  ���� node�� �������� �ʰ� �ű�⸸ �Ѵ�. ���� �ѹ� ������ node�� 
//  container�� �ı��ϱ� ������ �������� �ʴ´�.
//   shrink�� ������ node�� �����ϴ� �Լ��̴�. ������ node�� ������
//  �ʿ䰡 ������ �� �Լ��� ����ϸ� size��ŭ�� node�� �����ϰ��
//  ��� �����Ѵ�.
//-----------------------------------------------------------------
template <class TDATA, class TALLOCATOR>
void circular_list<TDATA, TALLOCATOR>::shrink()
{
	//-----------------------------------------------------------------
	// 1. ���鼭 ���� node���� ��� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) ����... �پ��� ���ڸ� Ȯ���ϱ� ���� ������.
	size_type count = 0;

	// 2) ���� head�� tail�� ����.
	_node* temp_first = m_tail->_next;
	_node* temp_last = m_head;
	while(temp_first != temp_last)
	{
		// - Destruct�� ȣ���Ѵ�.
		m_alloc_val.destroy(&temp_first->_data);

		// - Destruct�� ȣ���ϰ� pnode_temp�� �����.
		//   (Destroy�� ȣ������ �ʴ´�.)
		m_alloc_node.deallocate(temp_first, 1);

		// - ���ڸ� ���Ѵ�.
		++count;

		// - ����...
		temp_first= temp_first->_next;
	}


	//-----------------------------------------------------------------
	// 2. Node�� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) m_head�� m_tail�� �ڷ� ���̱�.
	LINK_NODE(m_tail, m_head);

	// 2) �Ҵ���� ���� ũ�⸦ 1 ���δ�.
	m_size -= count;
}


}
