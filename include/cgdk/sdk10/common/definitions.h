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
//-----------------------------------------------------------------------------
//                                                                            
// Definitions
//                                                                            
//-----------------------------------------------------------------------------
#define	INLINE										inline

#ifndef PURE
	#define	PURE									= 0
#endif

#ifndef EMPTY
	#define	EMPTY									{}
#endif

#ifndef EMPTY_TRUE
	#define	EMPTY_TRUE								{ return true;}
#endif

#ifndef EMPTY_FALSE
	#define	EMPTY_FALSE								{ return false;}
#endif

#ifndef EMPTY_ZERO
	#define	EMPTY_ZERO								{ return 0;}
#endif

#ifndef SAFE_FREE
	#define	SAFE_FREE(p)							if(p){ free(p); p = nullptr;}
#endif

#ifndef SAFE_DELETE
	#define	SAFE_DELETE(p)							if(p){ delete p; p = nullptr;}
#endif

#ifndef SAFE_DELETE_ARRAY
	#define	SAFE_DELETE_ARRAY(p)					if(p){ delete [] p; p = nullptr;}
#endif

#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(p)					{ if(p) { delete[] (p); (p) = nullptr;}}
#endif

#ifndef SAFE_DESTROY
	#define	SAFE_DESTROY(data)						if(data != nullptr){ data->destroy(); data = nullptr;}
#endif

#ifndef SAFE_RELEASE
	#define	SAFE_RELEASE(data)						if(data){ (data)->release();(data) = nullptr;}
#endif

#ifndef SAFE_CLOSEHANDLE
	#define	SAFE_CLOSEHANDLE(data)					if(data != INVALID_CGHANDLE_VALUE){ CloseHandle(data); data = INVALID_CGHANDLE_VALUE;}
#endif

#define	_DELETE			=delete;
#define	_DELETE_RETURN	=delete;


//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
#if defined(_WIN32)
	// * vs16 Lib 
	#if _MSC_VER>=_MSC_VER_2022
	#define	CGDK_CONFIGURATION_COMPILER	"v143"
	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x64.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x64.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x64 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x64 [DEBUG]"
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x86.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x86.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x86 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.x86 [DEBUG]"
			#endif
		#endif
	#else
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.Unsupported [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v143.Unsupported [DEBUG]"
		#endif
	#endif

	// * vs16 Lib 
	#elif _MSC_VER>=_MSC_VER_2019
	#define	CGDK_CONFIGURATION_COMPILER	"v142"
	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x64.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x64.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x64 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x64 [DEBUG]"
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x86.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x86.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x86 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.x86 [DEBUG]"
			#endif
		#endif
	#else
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.Unsupported [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v142.Unsupported [DEBUG]"
		#endif
	#endif

	// * vs15 Lib 
	#elif _MSC_VER>=_MSC_VER_2017
	#define	CGDK_CONFIGURATION_COMPILER	"v141"
	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x64.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x64.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x64 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x64 [DEBUG]"
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x86.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x86.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x86 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.x86 [DEBUG]"
			#endif
		#endif
	#else
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.Unsupported [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v141.Unsupported [DEBUG]"
		#endif
	#endif

	// * vs14 Lib 
	#elif _MSC_VER>=_MSC_VER_2015
	#define	CGDK_CONFIGURATION_COMPILER	"v140"
	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x64.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x64.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x64 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x64 [DEBUG]"
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x86.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x86.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x86 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.x86 [DEBUG]"
			#endif
		#endif
	#else
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.Unsupported [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.Unsupported [DEBUG]"
		#endif
	#endif

	// * Eclips
	#else
	#define	CGDK_CONFIGURATION_COMPILER	"eclips"
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/eclips.x86.DLL [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/eclips.x86.DLL [DEBUG]"
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/eclips.x86 [RELEASE]"
			#else
				#define	CGDK_CONFIGURATION	"cgdk/sdk10/eclips.x86 [DEBUG]"
			#endif
		#endif
	#endif
#elif defined(__ANDROID__)
	#if defined (__arm__)
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.ARM [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.ARM [DEBUG]"
		#endif
	#else
		#ifdef NDEBUG
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.ARM64 [RELEASE]"
		#else
			#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.ARM64 [DEBUG]"
		#endif
	#endif
#elif defined(__APPLE__)
	#ifdef NDEBUG
		#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.iOS [RELEASE]"
	#else
		#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.iOS [DEBUG]"
	#endif
#elif defined(__linux__)
	#ifdef NDEBUG
		#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.LINUX [RELEASE]"
	#else
		#define	CGDK_CONFIGURATION	"cgdk/sdk10/v140.LINUX [DEBUG]"
	#endif
#else
	#define	CGDK_CONFIGURATION	"unknowned platform"
#endif


// ----------------------------------------------------------------------------
// check
// ----------------------------------------------------------------------------
// 1) control State
#define	CONTINUE_IF(equation)									if(equation) { continue;}
#define	DO_AND_CONTINUE_IF(equation, todo)						if(equation) { todo; continue;}
#define	BREAK_IF(equation, ...)									if(equation) { __VA_ARGS__; break;}
#define	THROW_IF(equation, value, ...)							if(equation) { __VA_ARGS__; throw value;}
#define	RETURN_IF(equation, ...)								if(equation) { return __VA_ARGS__;}

// 2) control State with STATE
#define	ERROR_RETURN_IF(equation, value, ...)					if(equation) { __VA_ARGS__; return value;}

// 3) Conditional
#define	EXECUTE_IF(condition, state)							if(condition) { state;}

// 4) Debug Only
#if (defined(_WIN32) && !defined(NDEBUG)) || (!defined(_WIN32) && defined(NDEBUG))
	#define	CGDEBUG_ONLY(a)										a
#else
	#define	CGDEBUG_ONLY(a)
#endif


// ----------------------------------------------------------------------------
// Simple Operations
// ----------------------------------------------------------------------------
// 1) Settings
#define	SET_ZERO(variable)										variable=0
#define SET_ZERO_VECTOR3(variable)								variable.x=variable.y=variable.z=0.0f;
#define SET_ZERO_VECTOR4(variable)								variable.x=variable.y=variable.z=variable.w=0.0f;
#define	SET_NULL(variable)										variable=nullptr
#define	SET_TRUE(variable)										variable=true
#define	SET_FALSE(variable)										variable=false

// 2) Bit operations
// Toggle(true는 false로 false는 true로 바꿉니다.)
#define	TOGGLE(value)											(value) = !(value)

// 3) Simple Operations
template <typename T> T __select_max(T a, T b)					{return (a>b) ? a:b;}
template <typename T> T __select_max(T a, T b, T c)				{return (a>b) ? ((a>c) ? a:c) : ((b>c) ? b:c);}
template <typename T> T __select_max(T a, T b, T c, T d)		{return __select_max(__select_max(a,b), __select_max(c,d));}
template <typename T> T __select_min(T a, T b)					{return (a<b) ? a:b;}
template <typename T> T __select_min(T a, T b, T c)				{return (a<b) ? ((a<c) ? a:c) : ((b<c) ? b:c);}
template <typename T> T __select_min(T a, T b, T c, T d)		{return __select_min(__select_min(a,b), __select_min(c,d));}
template <typename T> T __get_saturated(T _v, T _min, T _max)	{return (_v<_min) ? _min : ((_v>_max) ? _max : _v);}
#define	UPDATE_MAX(a, b)										if(a<(b)) {a=(b);}
#define	UPDATE_MIN(a, c)										if(a>(c)) {a=(c);}
#define	SATURATE_MAX(a, c)										if(a>(c)) a=(c);
#define	SATURATE_MIN(a, b)										if(a<(b)) a=(b);
#define	SATURATE(a, b, c)										if(a<(b)) a=(b); else if(a>(c)) a=(c);
#define	ROUND_MAX(a, c)											if(a>(c)) a-=(c);
#define	ROUND_MIN(a, b)											if(a<(b)) a+=(b);
#define	ROUND_MINIMAX(a, b, c)									if(a<(b)) a+=(b); else if(a>(c)) a-=(c);
#define	UINT_DIFFER(a, b)										(a>=b) ? (a-b) : (UINT_MAX-a+b);

// 4) SWAP
template <typename TA>
void	SWAP(TA& a, TA& b)										{TA t=std::move(a); a=std::move(b); b=std::move(t);}

// 5) Increase/Decrese
#define	INCREASE(value)											++value
#define	INCREASE_IF(condition, value)							if(condition) {++value;}
#define	DECREASE(value)											--value
#define	DECREASE_IF(condition, value)							if(condition) {--value;}
#define	DISCOUNT_TO_ZERO(value)									if(value > 0) {--value;}

// 7) 계산 관련
#define	SQURE(value)											(value*value)
#define	VECTOR3_DISTANCE_SQURE(value)							(value.x*value.x+value.y*value.y+value.z*value.z)

// 8) Unique name
#define _MERGE_(a,b)  a##b
#define _LABEL_(a,b) _MERGE_(a,b)
#define _UNIQUE_TEMPORARY_NAME(name) _LABEL_(name, __LINE__)

// 9) Decay copy
template<class _Ty>
typename std::decay<_Ty>::type DECAY_COPY(_Ty&& _Arg)
{
	return (std::forward<_Ty>(_Arg));
}

// 10) hash_seq
namespace std
{
	inline size_t _Hash_seq(const unsigned char* _first, size_t _count)
	{	// FNV-1a hash function for bytes in [_first, _first + _count)
#if defined(_WIN64)
		static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
		const size_t _FNV_offset_basis = 14695981039346656037ULL;
		const size_t _FNV_prime = 1099511628211ULL;

#elif defined(__ANDROID__) && !defined(__arm__) && !defined(__i386__)
		static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
		const size_t _FNV_offset_basis = 14695981039346656037ULL;
		const size_t _FNV_prime = 1099511628211ULL;

#elif defined(__ANDROID__)
		static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
		const size_t _FNV_offset_basis = 2166136261U;
		const size_t _FNV_prime = 16777619U;

#elif defined(__linux__)
		static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
		const size_t _FNV_offset_basis = 14695981039346656037ULL;
		const size_t _FNV_prime = 1099511628211ULL;

#else
		static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
		const size_t _FNV_offset_basis = 2166136261U;
		const size_t _FNV_prime = 16777619U;

#endif

		size_t _Val = _FNV_offset_basis;
		for (size_t _Next = 0; _Next < _count; ++_Next)
		{
			_Val ^= (size_t)_first[_Next];
			_Val *= _FNV_prime;
		}
		return (_Val);
	}
}


// ----------------------------------------------------------------------------
// for Enum
// ----------------------------------------------------------------------------
#define CGDEFINE_ENUM_FLAG_OPERATORS_UINT32(ENUMTYPE) \
extern "C++" { \
	inline ENUMTYPE		operator |	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE&	operator |= (ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) |= static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE		operator &	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE&	operator &=	(ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) &= static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE		operator ~	(ENUMTYPE  _lhs) noexcept					{ return static_cast<ENUMTYPE>		(~static_cast<uint32_t>(_lhs)); } \
	inline ENUMTYPE		operator ^	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) ^ static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE&	operator ^= (ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) ^= static_cast<uint32_t>(_rhs)); } \
	inline ENUMTYPE		operator |	(ENUMTYPE  _lhs, uint32_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) | _rhs); } \
	inline ENUMTYPE&	operator |= (ENUMTYPE& _lhs, uint32_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) |= _rhs); } \
	inline ENUMTYPE		operator &	(ENUMTYPE  _lhs, uint32_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) & _rhs); } \
	inline ENUMTYPE&	operator &=	(ENUMTYPE& _lhs, uint32_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) &= _rhs); } \
	inline ENUMTYPE		operator ^	(ENUMTYPE  _lhs, uint32_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint32_t>(_lhs) ^ _rhs); } \
	inline ENUMTYPE&	operator ^=	(ENUMTYPE& _lhs, uint32_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint32_t&>(_lhs) ^= _rhs); } \
}

#define CGDEFINE_ENUM_FLAG_OPERATORS_UINT64(ENUMTYPE) \
extern "C++" { \
	inline ENUMTYPE		operator |	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint64_t>(_lhs) | static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE&	operator |= (ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) |= static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE		operator &	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<uint64_t>		(static_cast<uint64_t>(_lhs) & static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE&	operator &=	(ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) &= static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE		operator ~	(ENUMTYPE  _lhs) noexcept			 		{ return static_cast<ENUMTYPE>		(~static_cast<uint64_t>(_lhs)); } \
	inline ENUMTYPE		operator ^	(ENUMTYPE  _lhs, ENUMTYPE _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint64_t>(_lhs) ^ static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE&	operator ^= (ENUMTYPE& _lhs, ENUMTYPE _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) ^= static_cast<uint64_t>(_rhs)); } \
	inline ENUMTYPE		operator |	(ENUMTYPE  _lhs, uint64_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint64_t>(_lhs) | _rhs); } \
	inline ENUMTYPE&	operator |= (ENUMTYPE& _lhs, uint64_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) |= _rhs); } \
	inline ENUMTYPE		operator &	(ENUMTYPE  _lhs, uint64_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint64_t>(_lhs) & _rhs); } \
	inline ENUMTYPE&	operator &=	(ENUMTYPE& _lhs, uint64_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) &= _rhs); } \
	inline ENUMTYPE		operator ^	(ENUMTYPE  _lhs, uint64_t _rhs) noexcept	{ return static_cast<ENUMTYPE>		(static_cast<uint64_t>(_lhs) ^ _rhs); } \
	inline ENUMTYPE&	operator ^=	(ENUMTYPE& _lhs, uint64_t _rhs) noexcept	{ return reinterpret_cast<ENUMTYPE&>(reinterpret_cast<uint64_t&>(_lhs) ^= _rhs); } \
}
