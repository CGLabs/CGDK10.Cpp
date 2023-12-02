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
  any_ptr
 
*/
//-----------------------------------------------------------------------------
class any_ptr
{
// constructor/destructor) 
public:
	constexpr any_ptr() noexcept : m_data() {}
			any_ptr(const any_ptr& _ref)  noexcept : m_data(_ref.m_data) {}
			any_ptr(any_ptr&& _ref)  noexcept { m_data.swap(_ref.m_data); }
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			any_ptr(T* _ref)  noexcept : m_data(object_ptr<T>(_ref)) {}
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			any_ptr(const object_ptr<T>& _ref) noexcept : m_data(_ref) {}
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			any_ptr(object_ptr<T>&& _ref) noexcept : m_data(std::move(_ref)) {}
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			any_ptr(own_ptr<T>&&) noexcept = delete;
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			any_ptr(const own_ptr<T>& _ref)  noexcept : m_data(object_ptr<T>(_ref.get())) {}
			~any_ptr() noexcept {}

// public) 
public:
	// 1) basic operating functions
			void				reset() noexcept { _reset(); }
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								reset(T* _ref) noexcept { _reset<T>(_ref); }
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								reset(const object_ptr<T>& _ref) noexcept { _reset<T>(_ref); }
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								reset(object_ptr<T>&& _ref) noexcept { _reset<T>(_ref); }

			void				swap(any_ptr& _ref) noexcept { m_data.swap(_ref.m_data); }
			void				swap(std::any& _ref) noexcept { m_data.swap(_ref); }
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								swap(object_ptr<T>& _ref) { std::any_cast<object_ptr<T>&>(m_data).swap(_ref);}
			template <class T>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								swap(own_ptr<T>& _ref) noexcept = delete;

			void				move(std::any&& _ref) noexcept { _reset(std::move(_ref)); }
			template <class T>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, void>
								move(object_ptr<T>&& _ref) noexcept { _reset(std::move(_ref)); }

			template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, object_ptr<T>&>
								get() { return std::any_cast<object_ptr<T>&>(m_data); }
			template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, const object_ptr<T>&>
								get() const { return std::any_cast<const object_ptr<T>&>(m_data); }
			template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, T*>
								get_ptr() const { return std::any_cast<const object_ptr<T>&>(m_data).get(); }
																				  
	[[nodiscard]] bool			has_value() const noexcept { return m_data.has_value(); }
			template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, bool>
								exist() const { return m_data.has_value() ? (std::any_cast<object_ptr<T>&>(m_data).exist()) : false; }
			template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, bool>
								empty() const { return !exist<T>(); }

	// 2) operator- Assignment-A
			any_ptr&			operator = (const any_ptr& _rhs) noexcept { m_data = _rhs.m_data; return (*this); }
			any_ptr&			operator = (any_ptr&& _rhs) noexcept { m_data.swap(_rhs.m_data); _rhs.m_data.reset(); return (*this); }
			any_ptr&			operator = (const std::any& _rhs) noexcept { _reset(_rhs); return (*this);}
			any_ptr&			operator = (std::any&& _rhs) noexcept { _reset(std::move(_rhs)); return (*this);}
	// 3) operator- Assignment-B
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
								operator = (T* _rhs) noexcept { _reset<T>(_rhs); return (*this);}
	// 4) operator- Assignment-C
			template <class T>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
								operator = (const object_ptr<T>& _rhs) { _reset(_rhs); return (*this);}
			template <class T>													  
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
								operator = (object_ptr<T>&& _rhs) noexcept { _reset(std::move(_rhs)); return (*this);}
			template <class T>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
								operator = (own_ptr<T>&& _rhs) noexcept;
			template <class T>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, T>, any_ptr&>
								operator = (const own_ptr<T>& _rhs) noexcept;
	// 5) operator- conversion
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			[[nodiscard]]		operator object_ptr<T>() const noexcept { return std::any_cast<object_ptr<T>>(m_data); }
			template <class T, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, T>>>
			[[nodiscard]] 		operator T*() const noexcept { return std::any_cast<object_ptr<T>&>(m_data).get(); }

// implementation) 
protected:
			void				_reset() noexcept  { m_data.reset(); }
			void				_reset(const any_ptr& _ref) noexcept { m_data = _ref.m_data; }
			void				_reset(any_ptr&& _ref) noexcept { m_data.swap(_ref.m_data); _ref.m_data.reset(); }
			void				_reset(const std::any& _ref) noexcept { m_data = _ref; }
			void				_reset(std::any&& _ref) noexcept { m_data.swap(_ref); _ref.reset(); }
			template <class T>
			void				_reset(const object_ptr<T>& _ref) noexcept { m_data = _ref; }
			template <class T>
			void				_reset(object_ptr<T>&& _ref) noexcept { m_data = std::move(_ref); }
			template <class T>
			void				_reset(T* _ref) noexcept { m_data = object_ptr<T>(_ref); }

private:
			std::any			m_data;
};


}