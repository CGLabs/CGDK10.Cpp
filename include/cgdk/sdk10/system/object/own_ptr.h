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
//-----------------------------------------------------------------------------
/**

 @class		own_ptr
 
*/
//-----------------------------------------------------------------------------
template <class TREF>
class own_ptr
{
// definitions) 
public:	
			using value_type = typename _CGTRAITS_PTR<TREF>::value_type;
			using _mytype = own_ptr<TREF>;

			class  OWN_SET
			{
			public:
			constexpr explicit OWN_SET(value_type* _ptr) : ptr(_ptr) {}
			public:
				value_type*	ptr;
			};

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
	constexpr own_ptr() noexcept : m_ref(nullptr) {}
			template <class T>
	constexpr own_ptr(own_ptr<T>&& _ref) noexcept : m_ref(_ref.get()) { _ref._clear(); }
	constexpr ~own_ptr() noexcept;
			
private:
			// 설명) own_ptr 객체 간에는 복사를 허용하지 않는다. 오직 move만을 허용한다.
	constexpr explicit own_ptr(const own_ptr<TREF>& _ref) noexcept = delete;
			template <class T>
	constexpr explicit own_ptr(const own_ptr<T>& _ref) noexcept = delete;
			template <class T>
	constexpr explicit own_ptr(const object_ptr<T>& _ref) noexcept = delete;
			template <class T>
	constexpr explicit own_ptr(T* _ref) noexcept = delete;

public:
	constexpr explicit own_ptr(OWN_SET _set) noexcept : m_ref(_set.ptr)
			{
				if(_set.ptr != nullptr)
				{
					static_cast<Ireferenceable*>(_set.ptr)->add_ref();
				}
			}

// public) 
public:
	// 1) basic operating functions
	constexpr void				destroy() noexcept;
	constexpr void				reset() noexcept { this->_reset_own(); }
			template <class T>
	constexpr void				force_assign(T* _ref) noexcept { this->_reset_own(_ref); }
			template <class T>
	constexpr void				swap(own_ptr<T>& _ref) noexcept { value_type* temp = this->m_ref; this->m_ref = _ref.m_ref; _ref.m_ref = temp; }
			template <class T>
	constexpr void				move(own_ptr<T>&& _rhs) noexcept;
	constexpr void				detach() noexcept { this->_clear(); }

	[[nodiscard]] constexpr value_type* get() const noexcept { return this->m_ref;}
	[[nodiscard]] constexpr value_type** get_ptr() noexcept { return &this->m_ref;}
	[[nodiscard]] constexpr const value_type** get_ptr() const noexcept { return &this->m_ref;}
	[[nodiscard]] constexpr auto get_object_ptr() const noexcept { return object_ptr<value_type>(this->m_ref);}
			template <class T>
	[[nodiscard]] constexpr auto get_object_ptr() noexcept { return object_ptr<T>(this->m_ref); }

	[[nodiscard]] constexpr bool exist() const noexcept { return this->m_ref != nullptr;}
	[[nodiscard]] constexpr bool empty() const noexcept { return this->m_ref == nullptr;}

			template <class T>
	constexpr own_ptr<T>		force_casting_move() noexcept { auto temp = reinterpret_cast<T*>(this->m_ref); this->m_ref = nullptr; return own_ptr<T>(typename own_ptr<T>::OWN_SET(temp)); }

	// 2) operator- assignment-Enabled
			template <class T>
	constexpr _mytype&			operator=(own_ptr<T>&& _rhs) noexcept { this->move<T>(std::move(_rhs)); return (*this);}

	// 4) operator- 
	[[nodiscard]] constexpr value_type* operator->() const { CHECK_NULLPTR(); return this->m_ref;}
	[[nodiscard]] constexpr value_type&	operator*() const { CHECK_NULLPTR(); return *this->m_ref;}
	[[nodiscard]] constexpr value_type& operator[](size_t _index) const	{ CHECK_NULLPTR(); return this->m_ref[_index];}

	// 5) operator- conversion
	[[nodiscard]] constexpr		operator object_ptr<value_type>() const noexcept { return object_ptr<value_type>(this->m_ref);}
	[[nodiscard]] constexpr 	operator value_type*() const noexcept { return this->m_ref;}

private:
	// 5) operator- Assignment-Disabled
	constexpr _mytype&			operator=(const own_ptr<TREF>& _rhs) = delete;
			template <class T>
	constexpr _mytype&			operator=(object_ptr<T>&& _rhs) noexcept = delete;
			template <class T>
	constexpr _mytype&			operator=(const object_ptr<T>& _rhs) noexcept = delete;
			template <class T>
	constexpr _mytype&			operator=(const own_ptr<T>& _rhs) = delete;
			template <class T>
	constexpr _mytype&			operator=(T* _rhs) noexcept = delete;

public:
	constexpr void				_clear() noexcept { m_ref = nullptr;}
private:
	static constexpr void		_destroy_own(value_type* _ref) noexcept;

	constexpr void				_reset_own() noexcept;
	constexpr void				_reset_own(value_type* _ref) noexcept;

// members)
private:
			value_type*			m_ref;

#if defined(_MSC_VER)
			friend class object_ptr<TREF>;
			friend class own_ptr<TREF>;
#endif
};

template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator==(const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() == _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator!=(const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() != _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator> (const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() > _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator>=(const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() >= _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator< (const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() < _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator<=(const own_ptr<TONE>& _lhs, const object_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() <= _rhs.get());}

template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator==(const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() == _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator!=(const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() != _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator> (const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() > _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator>=(const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() >= _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator< (const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() < _rhs.get());}
template <class TONE, class TOTHER>	[[nodiscard]] constexpr bool operator<=(const own_ptr<TONE>& _lhs, const own_ptr<TOTHER>& _rhs) noexcept { return (_lhs.get() <= _rhs.get());}

template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator==(const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() == _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator!=(const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() != _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator> (const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() > _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator>=(const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() >= _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator< (const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() < _rhs);}
template <class TONE, class TPTR> [[nodiscard]] constexpr bool operator<=(const own_ptr<TONE>& _lhs, TPTR* _rhs) noexcept { return (_lhs.get() <= _rhs);}


template <class TREF>
constexpr own_ptr<TREF>::~own_ptr() noexcept
{
	// 1) 먼저 m_ptr을 얻는다.
	value_type*	p = this->get();

	// 2) m_ptr이 nullptr이 아니면 destroy처리한다.
	if(p != nullptr)
	{
		this->_destroy_own(p);
	}

	// 3) relaese
	if (this->m_ref != nullptr)
	{
		this->m_ref->release();

		this->_clear();
	}
}

template <class TREF>
constexpr void own_ptr<TREF>::destroy() noexcept
{
	object_ptr<TREF> ptr = *this;

	// 2) destroy한다.
	if(ptr.exist())
	{
		this->_destroy_own(ptr.get());
	}
}

template <class TREF>
template <class T>
constexpr void own_ptr<TREF>::move(own_ptr<T>&& _rhs) noexcept
{
	// 1)  copy m_ref temporary
	auto p = this->m_ref;

	// 2) destroy old object
	if(p != _rhs.get())
	{
		// - destry p
		if (p != nullptr)
			this->_destroy_own(p);

		// - copy ptr
		this->m_ref = _rhs.get();
	}

	// 3) clear _rhs
	_rhs._clear();

	// 4) release if same ptr
	if (p != nullptr)
	{
		p->release();
	}
}

template <class TOBJECT>
constexpr std::enable_if_t<!std::is_base_of_v<CGDK::Imessage_transmitter, TOBJECT>, void>
_destroy_own_detach_notifiable(TOBJECT* _object)
{
	// 1) query Imessage_transmitter interface
	auto* p = dynamic_cast<Imessage_transmitter*>(_object);

	// 2) call 'reset_message_transmitter'
	if (p != nullptr)
	{
		p->reset_message_transmitter();
	}
}

template <class TOBJECT>
constexpr std::enable_if_t<std::is_base_of_v<CGDK::Imessage_transmitter, TOBJECT>, void>
_destroy_own_detach_notifiable(TOBJECT* _object)
{
	_object->reset_message_transmitter();
}

template <class TOBJECT>
constexpr std::enable_if_t<!std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT> && !std::is_base_of_v<CGDK::object::Istartable, TOBJECT>, void>
_destroy_own_destroy(TOBJECT* _object)
{
	// 1) query object::Idestroyable interface
	auto* pdestroyable = dynamic_cast<object::Idestroyable*>(_object);

	// 2) call 'destroy'
	if (pdestroyable != nullptr)
	{
		pdestroyable->destroy();
	}
	else
	{
		// 3) query object::Istartable interface
		auto* pstartable = dynamic_cast<object::Istartable*>(_object);

		// 4) call 'stop'
		if (pstartable != nullptr)
		{
			pstartable->stop();
		}
	}
}

template <class TOBJECT>
constexpr std::enable_if_t<std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT>, void>
_destroy_own_destroy(TOBJECT* _object)
{
	static_cast<CGDK::object::Idestroyable*>(_object)->destroy();
}

template <class TOBJECT>
constexpr std::enable_if_t<!std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT> && std::is_base_of_v<CGDK::object::Istartable, TOBJECT>, void>
_destroy_own_destroy(TOBJECT* _object)
{
	static_cast<CGDK::object::Istartable*>(_object)->stop();
}

template <class TREF>
constexpr void own_ptr<TREF>::_destroy_own(value_type* _ref) noexcept
{
	// 1) call 'destroy' or 'stop'
	_destroy_own_destroy<TREF>(_ref);

	// 2) detach
	_destroy_own_detach_notifiable<TREF>(_ref);

	// 3) Ischedulable
	// 4) Igroupable
	// 5) Iobservable
}

template <class TREF>
constexpr void own_ptr<TREF>::_reset_own() noexcept
{
	// 1) ref_old를 저장해 놓는다.
	auto ref_old = this->m_ref;
	
	// check) ref_old가 nullptr이면 여기서 끝냄.
	if (ref_old == nullptr)
		return;

	// 2) clear)
	this->_clear();

	// 3) destroy를 호출한다.
	this->_destroy_own(ref_old);

	// 4) Reference Count를 줄인다.
	static_cast<Ireferenceable*>(ref_old)->release();
}

template <class TREF>
constexpr void own_ptr<TREF>::_reset_own(value_type* _ref) noexcept
{
	// 1) ref_old를 저장해 놓는다.
	auto ref_old = this->m_ref;
	
	// check) ref_old가 nullptr이면 여기서 끝냄.
	if (_ref == ref_old)
		return;

	// 2) clear)
	this->_clear();

	// 3) destroy를 호출한다.
	this->_destroy_own(ref_old);

	// 4) m_ref를 대입한다.
	this->m_ref = _ref;
	
	// 5) _ref가 nullptr이 아니면 add_ref 한다.
	if (_ref != nullptr)
	{
		static_cast<Ireferenceable*>(_ref)->add_ref();
	}
	
	// 6) ref_old가 nullptr이 아니면 Release 한다.
	if (ref_old != nullptr)
	{
		static_cast<Ireferenceable*>(ref_old)->release();
	}
}

template <class TREF>
template <class T>
constexpr  typename object_ptr<TREF>::_mytype& object_ptr<TREF>::operator = (own_ptr<T>&& _rhs) noexcept
{
	// 1) copy
	this->_reset(_rhs.get());

	// 2) reset
	_rhs.reset();
	
	// return) 
	return (*this);
}

template <class TREF>
constexpr typename object_ptr<TREF>::_mytype& object_ptr<TREF>::operator = (const own_ptr<TREF>& _rhs) noexcept
{
	// 1) setting한다.
	this->_reset(_rhs.get()); 
	
	// return) 
	return (*this);
}

template <class TREF>
template <class T>
constexpr typename object_ptr<TREF>::_mytype& object_ptr<TREF>::operator = (const own_ptr<T>& _rhs) noexcept
{
	// 1) setting한다.
	this->_reset(_rhs.get()); 
	
	// return) 
	return (*this);
}

template <class T>
inline std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
any_ptr::operator = (own_ptr<T>&& _rhs) noexcept
{
	// 1) copy
	this->_reset(_rhs.get());

	// 2) reset
	_rhs.reset();

	return (*this);
}

template <class T>
inline std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
any_ptr::operator = (const own_ptr<T>& _rhs) noexcept
{
	// 1) setting한다.
	this->_reset(_rhs.get());

	return (*this);
}


}
