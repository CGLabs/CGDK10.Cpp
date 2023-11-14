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
//
// memory Block Pool Definitions
//
// 1. 다양한 형태의 memory Block 크기
//    - 상황에 따라 다른 크기의 Block Size를 설정할 수 있다.
//    - 아래와 같은 종류를 설정할 수 있다.
//
//		* MEMORYPOOLTYPE_UNIFORM_TINY	- 256Byte x64, Max 16KByte
//		* MEMORYPOOLTYPE_UNIFORM_NORMAL	- 1KByte x64, Max 64KByte
//		* MEMORYPOOLTYPE_UNIFORM_LARGE	- 4KByte x64, Max 256KByte
//		* MEMORYPOOLTYPE_UNIFORM_HUGE	- 16KByte x64, Max 1MByte
//		
//		* MEMORYPOOLTYPE_SCALED_TINY	- 64Byte x32, 1KByte x62, Max 64KByte
//		* MEMORYPOOLTYPE_SCALED_NORMAL	- 256Byte x8, 1KByte x62, Max 64KByte
//		* MEMORYPOOLTYPE_SCALED_LARGE	- 256Byte x16, 4KByte x62, Max 256KByte
//		* MEMORYPOOLTYPE_SCALED_HUGE	- 256Byte x16, 16KByte x62, Max 1MByte
//
//    - 일반적으로 Network처리에서 send용으로 가장 많이 사용되는 것이 2KByte
//      이하의 Block들이라 매우 작은 단위를 가지게 하였고 TCP의 receive는  
//      32KByte이상의 큰 Block이 주로 사용되며 UDP의 receive는 2~8KByte Block
//      이 많이 사용된다. 그 외에는 모든 영역이 고르게 사용된다.
// 
//-----------------------------------------------------------------------------
// definitions) 
//#define	MEMORYPOOLTYPE_UNIFORM_TINY
//#define	MEMORYPOOLTYPE_UNIFORM_NORMAL
//#define	MEMORYPOOLTYPE_UNIFORM_LARGE
//#define	MEMORYPOOLTYPE_UNIFORM_HUGE

//#define	MEMORYPOOLTYPE_SCALED_TINY
//#define	MEMORYPOOLTYPE_SCALED_NORMAL
//#define	MEMORYPOOLTYPE_SCALED_LARGE
//#define	MEMORYPOOLTYPE_SCALED_HUGE

// Flag) Pool Sustainment를 사용한다.
#define _CGPOOL_FLAG_USE_SUSTAINMENT


//-----------------------------------------------------------------------------
// Definition of memory Block
//-----------------------------------------------------------------------------
// 1) Uniform memory Block Pool
#if defined(MEMORYPOOLTYPE_UNIFORM_TINY)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			0
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			64
	#define	MEMORYPOOL_SIZE_OF_BLOCK			256
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(MEMORYPOOL_NUMBER_OF_BLOCK*MEMORYPOOL_SIZE_OF_BLOCK)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size-1)>>8); }
#elif defined(MEMORYPOOLTYPE_UNIFORM_NORMAL)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			0
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			64
	#define	MEMORYPOOL_SIZE_OF_BLOCK			1024
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(MEMORYPOOL_NUMBER_OF_BLOCK*MEMORYPOOL_SIZE_OF_BLOCK)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size-1)>>10); }
#elif defined(MEMORYPOOLTYPE_UNIFORM_LARGE)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			0
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			64
	#define	MEMORYPOOL_SIZE_OF_BLOCK			4096
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(MEMORYPOOL_NUMBER_OF_BLOCK*MEMORYPOOL_SIZE_OF_BLOCK)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size-1)>>12); }
#elif defined(MEMORYPOOLTYPE_UNIFORM_HUGE)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			0
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			64
	#define	MEMORYPOOL_SIZE_OF_BLOCK			16384
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(MEMORYPOOL_NUMBER_OF_BLOCK*MEMORYPOOL_SIZE_OF_BLOCK)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size-1)>>14); }

// 2) Scaled memory Block Pool
#elif defined(MEMORYPOOLTYPE_SCALED_TINY)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			1
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			15
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(8192)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size<=1024) ? ((size-1)>>7) : (((size-1)>>10)+7)); }
#elif defined(MEMORYPOOLTYPE_SCALED_NORMAL)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			2
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			29
	#define	MEMORYPOOL_SIZE_OF_BLOCK			0
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(65536)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size<=1024) ? ((size-1)>>7) : ((size<=8192) ? (((size-1)>>10)+7) : (((size-1)>>12)+13))); }
#elif defined(MEMORYPOOLTYPE_SCALED_LARGE)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			3
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			41
	#define	MEMORYPOOL_SIZE_OF_BLOCK			0
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(65536*4)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size<=8192) ? ((size<=1024) ? ((size-1)>>7) : (((size-1)>>10)+7)) : ((size<=65536) ? (((size-1)>>12)+13) : (((size-1)>>14)+25))); }
#elif defined(MEMORYPOOLTYPE_SCALED_HUGE)
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			4
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			53
	#define	MEMORYPOOL_SIZE_OF_BLOCK			0
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(65536*16)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size<=8192) ? ((size<=1024) ? ((size-1)>>7) : (((size-1)>>10)+7)) : ((size<=65536) ? (((size-1)>>12)+13) : ((size<=(65536*4)) ? (((size-1)>>14)+25) : (((size-1)>>16)+37)))); }

// 3) Default
#else	
	#define	MEMORYPOOL_MEMORYPOOL_TYPE			3
	#define	MEMORYPOOL_NUMBER_OF_BLOCK			41
	#define	MEMORYPOOL_SIZE_OF_BLOCK			0
	#define	MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK	(65536*4)
	constexpr int SELECT_BLOCK(size_t size) noexcept { return static_cast<int>((size <= 8192) ? ((size <= 1024) ? ((size - 1) >> 7) : (((size - 1) >> 10) + 7)) : ((size <= 65536) ? (((size - 1) >> 12) + 13) : (((size - 1) >> 14) + 25))); }
#endif

#define	MEM_POOL_FREE(object)					CGDK::factory::memory_block::instance().dealloc(SELECT_BLOCK(object->len), object)
#define	MEM_POOL_PREPARE(size, amount)			CGDK::factory::memory_block::instance().prepare(SELECT_BLOCK(size), amount)
