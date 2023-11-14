//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
	template <class TREF> class own_ptr;

//-----------------------------------------------------------------------------
/**

 @class		object_ptr
 
*/
//-----------------------------------------------------------------------------
template <class TREF>
class object_ptr : public _CGTRAITS_PTR<TREF>
{
// definitions) 
public:	
			using value_type = typename _CGTRAITS_PTR<TREF>::value_type;
			using _mytype = object_ptr<TREF>;

private:
		#ifdef _USE_CHECK_NULLPTR
			void CHECK_NULLPTR() const
			{
				CGASSERT_ERROR(this->m_ref != nullptr);

				if (this->m_ref == nullptr)
					throw std::invalid_argument();
			}
		#else
			void CHECK_NULLPTR() const
			{
				CGASSERT_ERROR(this->m_ref != nullptr);
			}
		#endif

// constructor/destructor) 
public:
	constexpr object_ptr() noexcept : m_ref(nullptr) {}
			template <class T>
	constexpr object_ptr(T* _ref)  noexcept : m_ref(_ref)							
			{
				if(_ref != nullptr)
				{
					_ref->add_ref();
				}
			}
	constexpr object_ptr(const object_ptr<TREF>& _ref)  noexcept : m_ref(_ref.get())
			{
				auto ptr = _ref.get();
				if (ptr != nullptr)
				{
					ptr->add_ref();
				}
			}
			template <class T>
	constexpr object_ptr(const object_ptr<T>& _ref) noexcept : m_ref(_ref.get())
			{
				auto ptr = _ref.get();
				if (ptr != nullptr)
				{
					ptr->add_ref();
				}
			}
	constexpr object_ptr(object_ptr<TREF>&& _ref) noexcept : m_ref(_ref.get()) { _ref._clear();}
			template <class T>													  
	constexpr object_ptr(object_ptr<T>&&  _ref) noexcept : m_ref(_ref.get()) { _ref._clear(); }
			template <class T>													  
	constexpr object_ptr(own_ptr<T>&&) noexcept = delete;
			template <class T>													  
	constexpr object_ptr(const own_ptr<T>& _ref)  noexcept : m_ref(_ref.get())
			{
				auto ptr = _ref.get();
				if (ptr != nullptr)
				{
					ptr->add_ref();
				}
			}
	constexpr ~object_ptr() noexcept												
			{ 
				if(m_ref != nullptr)
				{
					m_ref->release();
					
					_clear();
				}
			}

// public) 
public:
	// 1) basic operating functions
	constexpr void				reset() noexcept { this->_reset();}
			template <class T>													  
	constexpr void				reset(T* _ref) noexcept { this->_reset(_ref);}
			template <class T>													  
	constexpr void				reset(const object_ptr<T>& _ref) noexcept { this->_reset(_ref.get());}
			template <class T>													  
	constexpr void				reset(object_ptr<T>&& _ref) noexcept { this->template move<T>(_ref);}
			template <class T>													  
	constexpr void				swap(object_ptr<T>& _ref) noexcept { value_type* temp = m_ref; m_ref = _ref.m_ref; _ref.m_ref = temp;}
	constexpr void				detach() noexcept { this->_clear(); }

			template <class T>													  
	constexpr void				move(object_ptr<T>& _ref) noexcept				
			{
				auto p = _ref.get();
				auto old = this->m_ref;
				
				if(p == old)
					return;
				
				this->m_ref=p;
				
				_ref._clear();
				
				if (old != nullptr)
				{
					old->release();
				}
			}
			template <class T>													  
	constexpr void				move(object_ptr<T>&& _rhs) noexcept
			{
				auto p = this->m_ref;
				
				this->m_ref = _rhs.get();

				_rhs._clear();
				
				if (p != nullptr)
				{
					p->release();
				}
			}
	[[nodiscard]] constexpr value_type* get() const noexcept { return this->m_ref;}
	[[nodiscard]] constexpr value_type** get_ptr() noexcept { return &this->m_ref;}
	[[nodiscard]] constexpr const value_type** get_ptr() const noexcept { return &this->m_ref;}
																				  
	[[nodiscard]] constexpr bool exist() const noexcept { return this->m_ref != nullptr;}
	[[nodiscard]] constexpr bool empty() const noexcept { return this->m_ref == nullptr;}

	// 2) operator- Assignment-A												  
	constexpr _mytype&			operator=(value_type* _rhs) noexcept { this->_reset(_rhs); return (*this);}
			template <class T>													  
	constexpr _mytype&			operator=(T* _rhs) noexcept { this->_reset(_rhs); return (*this);}
	constexpr _mytype&			operator=(const _mytype& _rhs) noexcept { this->_reset(_rhs.get()); return (*this);}
	constexpr _mytype&			operator=(_mytype&& _rhs) noexcept { this->template move<TREF>(_rhs); return (*this);}
	constexpr _mytype&			operator=(const own_ptr<TREF>&) noexcept;
	constexpr _mytype&			operator=(own_ptr<TREF>&&) = delete;

	// 3) operator- Assignment-B
			template <class T>
	constexpr _mytype&			operator=(const object_ptr<T>& _rhs) noexcept { this->_reset(_rhs.get()); return (*this);}
			template <class T>													  
	constexpr _mytype&			operator=(object_ptr<T>&& _rhs) noexcept { this->template move<TREF>(_rhs); return (*this);}
			template <class T>
	constexpr _mytype&			operator=(const own_ptr<T>& _rhs) noexcept;
			template <class T>
	constexpr _mytype&			operator=(own_ptr<T>&& _rhs) noexcept;

	// 4) Operator- 
	[[nodiscard]] constexpr value_type* operator->() const { CHECK_NULLPTR(); return this->m_ref;}
	[[nodiscard]] constexpr value_type&	operator*() const { CHECK_NULLPTR(); return *this->m_ref;}
	[[nodiscard]] constexpr value_type& operator[](size_t _index) const { CHECK_NULLPTR(); return this->m_ref[_index];}

	// 5) operator- Conversion
	[[nodiscard]] constexpr		operator value_type*() const noexcept { return this->m_ref; }

// implementation) 
public:
	constexpr void				_clear() noexcept { this->m_ref = nullptr;}
private:
	constexpr void				_reset() noexcept
			{
				value_type* ref_old = this->m_ref;
				
				if(ref_old == nullptr)
					return;
				
				this->_clear();
			
				ref_old->release();
			}
	constexpr void				_reset(value_type* _ref) noexcept
			{
				value_type* ref_old = this->m_ref;
				
				if(_ref == ref_old)
					return;
				
				this->m_ref = _ref;
				
				if (_ref != nullptr)
				{
					_ref->add_ref();
				}
				
				if (ref_old != nullptr)
				{
					ref_old->release();
				}
			}

// members)
private:
			value_type*			m_ref;

#if defined(_MSC_VER)
			friend class object_ptr<TREF>;
			friend class own_ptr<TREF>;
#endif
};

template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator==(const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() == _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator!=(const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() != _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator> (const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() > _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator>=(const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() >= _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator< (const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() < _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator<=(const object_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() <= _rhs.get());}
																														   
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator==(const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() == _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator!=(const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() != _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator> (const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() > _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator>=(const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() >= _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator< (const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() < _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator<=(const object_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() <= _rhs.get());}
																															  
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator==(const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() == _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator!=(const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() != _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator> (const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() > _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator>=(const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() >= _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator< (const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() < _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator<=(const object_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() <= _rhs);}
																															  

template <class TONE, class TOTHER>	constexpr void swap_object(object_ptr<TONE>& _lhs, object_ptr<TOTHER>& _rhs) noexcept	
{
	_lhs.swap(_rhs);
}

template <class TTARGET, class TSOURCE>
constexpr object_ptr<TTARGET> static_pointer_cast(const object_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(static_cast<TTARGET*>(_source.get()));
}

template <class TTARGET, class TSOURCE>
[[nodiscard]] constexpr object_ptr<TTARGET> static_pointer_cast(const own_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(static_cast<TTARGET*>(_source.get()));
}

template <class TTARGET, class TSOURCE>
[[nodiscard]] constexpr object_ptr<TTARGET> const_pointer_cast(const object_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(const_cast<TTARGET*>(_source.get()));
}

template <class TTARGET, class TSOURCE>
[[nodiscard]] constexpr object_ptr<TTARGET> const_pointer_cast(const own_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(const_cast<TTARGET*>(_source.get()));
}

template <class TTARGET, class TSOURCE>
[[nodiscard]] constexpr object_ptr<TTARGET> dynamic_pointer_cast(const object_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(dynamic_cast<TTARGET*>(_source.get()));
}

template <class TTARGET, class TSOURCE>
[[nodiscard]] constexpr object_ptr<TTARGET> dynamic_pointer_cast(const own_ptr<TSOURCE>& _source) noexcept
{
	return object_ptr<TTARGET>(dynamic_cast<TTARGET*>(_source.get()));
}

template <class TTYPE>
struct hash_object_ptr
{
	[[nodiscard]] constexpr size_t operator()(const object_ptr<TTYPE>& _rhs) const noexcept
	{
		return static_cast<size_t>(_rhs.get());
	}
};

template <class TTYPE>
struct hash_own_ptr
{
	[[nodiscard]] constexpr size_t operator()(const own_ptr<TTYPE>& _rhs) const noexcept
	{
		return static_cast<size_t>(_rhs.get());
	}
};

}

namespace std
{
	template<class TKEY>
	struct hash<CGDK::object_ptr<TKEY>>
	{
		using argument_type = TKEY*;
		using result_type = size_t;

		[[nodiscard]] constexpr size_t operator()(const CGDK::object_ptr<TKEY>& _keyval) const
		{
			return (std::_Hash_seq(reinterpret_cast<const unsigned char *>(_keyval.get()), sizeof(TKEY*)));
		}
	};

	template<class TKEY>
	struct hash<CGDK::own_ptr<TKEY>>
	{
		using argument_type = TKEY*;
		using result_type = size_t;

		[[nodiscard]] constexpr size_t operator()(const CGDK::own_ptr<TKEY>& _keyval) const
		{
			return (std::_Hash_seq(reinterpret_cast<const unsigned char *>(_keyval.get()), sizeof(TKEY*)));
		}
	};
}
