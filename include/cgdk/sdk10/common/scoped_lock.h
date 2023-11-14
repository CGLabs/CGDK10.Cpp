//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
// ----------------------------------------------------------------------------
// 2. MUTEX (native)
//    
//    
// 
// ----------------------------------------------------------------------------
namespace CGDK
{
//-----------------------------------------------------------------------------
// 
// CGDK::scoped_lock - for std::shared_mutex
//
//-----------------------------------------------------------------------------
// 1) unique_lock (unnamed)
template <class Tlockable, class TENABLE = void> class _unique_lock : public std::unique_lock<lock_object>									{};
template <class Tlockable> class _unique_lock<Tlockable, std::enable_if_t<std::is_base_of_v<std::mutex, Tlockable>, void>>					{ public: using type = std::unique_lock<std::mutex>; };
template <class Tlockable> class _unique_lock<Tlockable, std::enable_if_t<std::is_base_of_v<std::recursive_mutex, Tlockable>, void>>		{ public: using type = std::unique_lock<std::recursive_mutex>; };
template <class Tlockable> class _unique_lock<Tlockable, std::enable_if_t<std::is_base_of_v<std::shared_mutex, Tlockable>, void>>			{ public: using type = std::unique_lock<std::shared_mutex>; };
template <class Tlockable> class _unique_lock<Tlockable, std::enable_if_t<std::is_base_of_v<std::timed_mutex, Tlockable>, void>>			{ public: using type = std::unique_lock<std::timed_mutex>; };

// 2) unique_lock (named)
template <class Tlockable, class TENABLE = void> class _unique_lock_named : public std::unique_lock<lock_object> { public: using type = std::unique_lock<lock_object>; };
template <class Tlockable> class _unique_lock_named<Tlockable, std::enable_if_t<std::is_base_of_v<std::mutex, Tlockable>, void>>			{ public: using type = std::unique_lock<std::mutex>; };
template <class Tlockable> class _unique_lock_named<Tlockable, std::enable_if_t<std::is_base_of_v<std::recursive_mutex, Tlockable>, void>>	{ public: using type = std::unique_lock<std::recursive_mutex>; };
template <class Tlockable> class _unique_lock_named<Tlockable, std::enable_if_t<std::is_base_of_v<std::shared_mutex, Tlockable>, void>>		{ public: using type = std::unique_lock<std::shared_mutex>; };
template <class Tlockable> class _unique_lock_named<Tlockable, std::enable_if_t<std::is_base_of_v<std::timed_mutex, Tlockable>, void>>		{ public: using type = std::unique_lock<std::timed_mutex>; };

// 3) shared_lock
template <class Tlockable, class TENABLE = void> class _shared_lock : public std::shared_lock<std::shared_mutex>							{};
template <class Tlockable> class _shared_lock<Tlockable, std::enable_if_t<std::is_base_of_v<std::shared_mutex, Tlockable>, void>>			{ public: using type = std::shared_lock<std::shared_mutex>; };

}

// ----------------------------------------------------------------------------
//  CGDK::scoped_lock
// ----------------------------------------------------------------------------
// 1) unique lock
#define	scoped_unique_lock(cs)				if(typename CGDK::_unique_lock<std::decay_t<decltype(cs)>>::type _UNIQUE_TEMPORARY_NAME(_temp_cs_lock) {const_cast<std::decay_t<decltype(cs)>&>(cs)}; true)
#define	scoped_unique_lock_named(cs, name)	if(typename CGDK::_unique_lock_named<std::decay_t<decltype(cs)>>::type name {const_cast<typename std::decay<decltype(cs)>::type&>(cs)}; true)

// 2) shared lock
#define	scoped_shared_lock(cs)				if(typename CGDK::_shared_lock<std::decay_t<decltype(cs)>>::type _UNIQUE_TEMPORARY_NAME(_temp_cs_lock) {const_cast<std::decay_t<decltype(cs)>&>(cs)}; true)
#define	scoped_shared_lock_named(cs, name)	if(typename CGDK::_shared_lock<std::decay_t<decltype(cs)>>::type name {const_cast<std::decay_t<decltype(cs)>&>(cs)}; true)

// 3) lock_guard
#define	scoped_lock(cs)						scoped_unique_lock(cs)
#define	synchronized(cs)					scoped_lock(cs)

// 4) for capability
#define	scoped_lock_named(cs, name)			scoped_unique_lock_named(cs, name)
#define	scoped_lock_leave(name)				name.unlock();

// 5) lock_guard
#define	conditional_lock(cs, name)			if(std::unique_lock<std::mutex> name {cs}; true)
