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
//-----------------------------------------------------------------------------
/**
 @class		_CGTRAITS_PTR
*/
//-----------------------------------------------------------------------------
template <class TREF>
class _CGTRAITS_PTR
{
public:
	using value_type = typename std::remove_reference_t<std::remove_const_t<TREF>>;
};

#if defined(_ENABLE_DEBUG_NEW)
	#define	CGNEW_DEBUG_INFO_INITIALIZE						m_debug_info_filename(nullptr), m_debug_info_line(0)
	#define	CGNEW_DEBUG_INFO_PARAMETERS						[[maybe_unused]] const char* _filename, [[maybe_unused]] int _line
	#define	CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT		[[maybe_unused]] const char* _filename=__FILE__, [[maybe_unused]] int _line=__LINE__
	#define	CGNEW_DEBUG_INFO_PARAMETERS_PASSING				_filename, _line
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL				__FILE__, __LINE__
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL_2			m_debug_info_filename, m_debug_info_line
	#define	CGNEW_DEBUG_INFO_PARAMETERS_MALLOC				_NORMAL_BLOCK, __FILE__, __LINE__
	#define	CGNEW_DEBUG_INFO_COMMA							,
	#define	CGNEW_DEBUG_INFO_COLON							:
	#define	CGNEW_DEBUG_INFO_SET(pobject, filename, line)	pobject->set_debug_info(filename, line)
	#define	CGNEW_DEBUG_INFO_RESET(pobject)					pobject->reset_debug_info()
	#define	CGNEW_DEBUG_INFO_DECLARE						public: void set_debug_info(const char* _filename, int _line) { m_debug_info_filename=_filename; m_debug_info_line=_line;} \
															void reset_debug_info() { m_debug_info_filename=nullptr; m_debug_info_line=0;} \
															const char* m_debug_info_filename=nullptr; int m_debug_info_line=0;
#else
	#define	CGNEW_DEBUG_INFO_INITIALIZE
	#define	CGNEW_DEBUG_INFO_PARAMETERS						
	#define	CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT
	#define	CGNEW_DEBUG_INFO_PARAMETERS_PASSING				
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL
	#define	CGNEW_DEBUG_INFO_PARAMETERS_INITIAL_2
	#define	CGNEW_DEBUG_INFO_PARAMETERS_MALLOC
	#define	CGNEW_DEBUG_INFO_COMMA							
	#define	CGNEW_DEBUG_INFO_COLON
	#define	CGNEW_DEBUG_INFO_SET(pobject, filename, line)	
	#define	CGNEW_DEBUG_INFO_RESET(pobject)					
	#define	CGNEW_DEBUG_INFO_DECLARE						public: void set_debug_info(const char* , int )	{} \
															void reset_debug_info()  {}
#endif


//-----------------------------------------------------------------------------
/**
@class		make_object
*/
//-----------------------------------------------------------------------------
#if defined(_ENABLE_DEBUG_NEW)
#if defined(_WIN32)
	#define	MALLOC											_malloc_dbg
#else
	#define	MALLOC											::malloc
#endif
	#define	make_object										CGDK::DEBUG_INFO_SETTER(__FILE__, __LINE__)=CGDK::_make_create_parameters
	#define	make_own										CGDK::DEBUG_INFO_SETTER_OWN(__FILE__, __LINE__)=CGDK::_make_own_parameters
	#define	alloc_object									CGDK::DEBUG_INFO_SETTER(__FILE__, __LINE__)=CGDK::_alloc_object
	#define	mem_alloc(size)									CGDK::_mem_alloc(size, __FILE__, __LINE__)
	#define	mem_alloc_with_debug_info(size, f, l)			CGDK::_mem_alloc(size, f, l)
	#define	mem_pool_alloc(size)							CGDK::_mem_pool_alloc(size, __FILE__, __LINE__)
	#define	mem_pool_free(p)								CGDK::_mem_pool_free(p)
	#define	alloc_shared_buffer(size)						CGDK::_alloc_shared_buffer(size, __FILE__, __LINE__)
	#define	MEM_POOL_ALLOC_WITH_DEBUG_INFO(size, f, l)		CGDK::_alloc_shared_buffer(size, f, l)
	#define	make_shared_buffer(value, ...)					CGDK::_make_shared_buffer(__FILE__, __LINE__, value, ##__VA_ARGS__)
#else
	#define	MALLOC											::malloc
	#define	make_object										CGDK::_make_object
	#define	make_own										CGDK::_make_own
	#define	alloc_object									CGDK::_alloc_object
	#define	mem_alloc(size)									CGDK::_mem_alloc(size)
	#define	mem_alloc_with_debug_info(size, f, l)			CGDK::_mem_alloc(size)
	#define	mem_pool_alloc(size)							CGDK::_mem_pool_alloc(size)
	#define	mem_pool_free(p)								CGDK::_mem_pool_free(p)
	#define	alloc_shared_buffer(size)						CGDK::_alloc_shared_buffer(size)
	#define	MEM_POOL_ALLOC_WITH_DEBUG_INFO(size, f, l)		CGDK::_alloc_shared_buffer(size)
	#define	make_shared_buffer(value, ...)					CGDK::_make_shared_buffer(value, ##__VA_ARGS__)
#endif
