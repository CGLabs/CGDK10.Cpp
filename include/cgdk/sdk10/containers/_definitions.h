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
// CGDK Definitions
//
// 1. circular��!
//    - ȯ������ �����ϴ� Array�̴�.
//    - list�� ���� ����ð� ����� push/pop�� �����Ѵ�.
//    - array�� ���� Random Indexing�� �����Ѵ�.
//    - std::deque�� ��ü���̶�� ���� �ȴ�.
//    - �Ϲ����� ��� ó���ӵ��� vector�� ���� �����̴�.
//    - ������ expend�� ��û�� ���ϰ� ��ٴ� ������ �ִ�.
//    - size�� �׻� 2�� ����θ� ������ �� �ִ�.
//
// 2. circular�� �ٽ�! Function�� ��� ����.
//    1) 
//    2) 
//
// 3. circular�� �ֿ� ��� �뵵
//    1) vector�� ��ü - ����� push/pop�� �ʿ��ϸ鼭 Random access�� �ʿ��� ��.
//    2) deque�� ��ü  - ����� push/pop�� �ʿ��ϸ鼭 �ſ� ����� iteration�� �ʿ��� ��.
//
//
// 4. Option) CGDK::vector�� �ֿ� �ɼ�.
// 
//    1) No auto expand on push_back operation
//
//		 #define _CGD_CIRCULAR_NO_AUTOEXPAND
//
//       vector�� _CGD_VECTOR_NO_AUTOEXPAND_PUSHBACK�� ���� ������ �ϴ� �ɼ��̴�.
//
//
//-----------------------------------------------------------------------------
#include <stdexcept>
#include <limits>
#include <cstddef>
#include <cassert>
//#define	_CGD_NO_EXCEPTION_GUARANTEE

// ----------------------------------------------------------------------------
// Exception Guarantee Levels) 
// ----------------------------------------------------------------------------
#ifdef _CGD_NO_EXCEPTION_GUARANTEE
#define	ON_EXCEPTION(condition)		if(FALSE)

#define	CGD_TRY			
#define	CGD_CATCH(x)	
#define	CGD_CATCH_ALL	if(FALSE)
#define	CGD_RETHROW

#define	CGD_THROW(x)	
#define	CGD_THROW_IF(c, r)	CGDASSERT_ERROR(!(c));

#else
#define	ON_EXCEPTION(condition)	if(condition)

#define	CGD_TRY					try
#define	CGD_CATCH(x)			catch (x)
#define	CGD_CATCH_ALL			catch (...)
#define	CGD_RETHROW				throw

#define	CGD_THROW(x)			throw(x)
#define	CGD_THROW_IF(c, r)		if(c){	throw r;}

#endif


#define	CGD_NOEXCEPT			noexcept


#define	LINK_NODE(a, b)			a->_next=b; b->_pre=a;
#define	LINK_NODE_SINGLE(a, b)	a->_next=b;

#if defined(_MSC_VER)
	#define	TLS					__declspec( thread )
#else
	#define TLS					__thread
#endif


// ----------------------------------------------------------------------------
// Definitions
// ----------------------------------------------------------------------------
#define	CONTAINER_MIN	8
#define	CONTAINER_MAX	65536

// 1) CGDK::list Sort Option. 
#define	_CGD_LIST_FAST_SORT



//*****************************************************************************
//*                                                                           *
//*                               Definitions                                 *
//*                                                                           *
//*  Definition for Global use of Application                                 *
//*                                                                           *
//*****************************************************************************
#ifndef SAFE_FREE
	#define	SAFE_FREE(p)									if(p){ ::free(p); p = nullptr; }
#endif

#ifndef SAFE_DELETE
	#define	SAFE_DELETE(p)									if(p){ delete p; p = nullptr; }
#endif

#ifndef SAFE_DELETE_ARRAY
	#define	SAFE_DELETE_ARRAY(p)							if(p){ delete [] p; p = nullptr; }
#endif

#ifndef SAFE_RELEASE
	#define	SAFE_RELEASE(data)								if(data){ (data)->Release();(data) = nullptr; }
#endif


// ----------------------------------------------------------------------------
// Trace & Assert
// ----------------------------------------------------------------------------
#ifndef NDEBUG
	#define	_USE_CGDNET_ASSERT
#endif

#ifdef _USE_CGDNET_ASSERT
	#define	CGDASSERT(equation, value)						assert(equation);	if(!(equation))	{ return value;}
	#define	CGDASSERT_TRACE(equation, value, state)			assert(equation);	if(!(equation))	{ state; return value;}
	#define	CGDASSERT_ERROR(equation)						assert(equation);
	#define	CGDASSERT_ERROR_TRACE(equation, state)			assert(equation);	if(!(equation))	{ state;}

	#define	CGDASSERT_ERROR_CRITICAL						assert(FALSE);
#else
	#define	CGDASSERT(equation, value)					
	#define	CGDASSERT_TRACE(equation, value, string)
	#define	CGDASSERT_ERROR(equation)					
	#define	CGDASSERT_ERROR_TRACE(equation, string)

	#define	CGDASSERT_ERROR_CRITICAL
#endif


// ----------------------------------------------------------------------------
// ���
// ----------------------------------------------------------------------------
// 1) ��� Serise
#define	CGD_CONTINUE_IF(equation)							if(equation)			{ continue;}
#define	CGD_BREAK_IF(equation)								if(equation)			{ break;}
#define	CGD_RETURN_IF(equation, ...)						if(equation)			{ return __VA_ARGS__;}


// ----------------------------------------------------------------------------
// ����
// ----------------------------------------------------------------------------
// 1) ��...
#define	CGD_MAX(a, b)										(((a) > (b)) ? (a) : (b))
#define	CGD_MIN(a, b)										(((a) < (b)) ? (a) : (b))

// 2) SATURATE
#define	CGD_SATURATE_MAX(value, max)						if(value > (max)) value=(max);
#define	CGD_SATURATE_MIN(value, min)						if(value < (min)) value=(min);
#define	CGD_SATURATE(value, min, max)						if(value < (min)) value=(min); else if(value > (max)) value=(max);

// 3) Swap
template<typename TA>
void	CGD_SWAP(TA& a, TA& b)								{	TA t=a; a=b; b=t;}


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
#if _MSC_VER>=_MSC_VER_2012
#define	_ACQUIRES_LOCK(value)				_Acquires_lock_(value)
#define	_RELEASES_LOCK(value)				_Releases_lock_(value)
#define	_ACQUIRES_EXCLUSIVE_LOCK(value)		_Acquires_exclusive_lock_(value)
#define	_RELEASES_EXCLUSIVE_LOCK(value)		_Releases_exclusive_lock_(value)
#define	_ACQUIRES_SHARED_LOCK(value)		_Acquires_shared_lock_(value)
#define	_RELEASES_SHARED_LOCK(value)		_Releases_shared_lock_(value)

#pragma warning(disable: 26110)
#pragma warning(disable: 26135)
#pragma warning(disable: 26165)

#else
#define	_ACQUIRES_LOCK(value)
#define	_RELEASES_LOCK(value)
#define	_ACQUIRES_EXCLUSIVE_LOCK(value)
#define	_RELEASES_EXCLUSIVE_LOCK(value)
#define	_ACQUIRES_SHARED_LOCK(value)	
#define	_RELEASES_SHARED_LOCK(value)	
#endif
