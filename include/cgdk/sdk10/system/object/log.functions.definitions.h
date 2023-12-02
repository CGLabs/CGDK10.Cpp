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
// ----------------------------------------------------------------------------
//
// 1. Configures for log functions
//
//    1) enable Log
//    - _ENABLE_LOG_SYSTEM
//    - _ENABLE_LOG_FATAL
//    - _ENABLE_LOG_ERROR
//    - _ENABLE_LOG_USER
//    - _ENABLE_LOG_INFO
//    - _ENABLE_LOG_INFO_LOW
//    - _ENABLE_LOG_PROGRESS
//
//    2) MAX_TRACE_STRING_LENGTH
//
// ----------------------------------------------------------------------------
#if !defined(_AFXEXT)
	#define	_ENABLE_LOG_SYSTEM
	#define	_ENABLE_LOG_FATAL
	#define	_ENABLE_LOG_ERROR
	#define	_ENABLE_LOG_WARNING
	#define	_ENABLE_LOG_USER

	#if !defined(NDEBUG)
		#define	_ENABLE_LOG_DEBUG
	#endif
	#define	_ENABLE_LOG_INFO
	//#define _ENABLE_LOG_INFO_LOW
	#define	_ENABLE_LOG_PROGRESS
#endif

#define	__LOG_FUNCTION	CGDK::_log_fmt


// ----------------------------------------------------------------------------
//
// 2. Log Funtions
//
// ----------------------------------------------------------------------------
// 1) Log
#define	LOG_FMT(target, type, level, ...)					CGDK::_log_fmt(target, type, level, CGDK::eCHARACTER_SET::NONE, ## __VA_ARGS__)
#define	LOG_FMT_IF(cond, target, type, level, ...)			if(cond) CGDK::_log_fmt(target, type, level, CGDK::eCHARACTER_SET::NONE, ## __VA_ARGS__)
#define LOG_STREAM(...)										CGDK::_log_end() = CGDK::_log_stream(__VA_ARGS__)
#define	LOG_STREAM_IF(cond, ...)							if(cond) CGDK::_log_end() = CGDK::_log_stream(__VA_ARGS__)
#define LOG(...)											LOG_STREAM(__VA_ARGS__)
#define	LOG_IF(...)											LOG_STREAM_IF(__VA_ARGS__)

// 2) Information Log
#ifdef _ENABLE_LOG_SYSTEM
	#define	LOG_SYSTEM			LOG(CGDK::log_type_t::system)
#else
	#define	LOG_SYSTEM			LOG_MESSAGE_EMPTY()
#endif

// 3) information log
#ifdef _ENABLE_LOG_INFO
	#define	LOG_INFO			LOG(CGDK::log_type_t::info)
#else
	#define	LOG_INFO			LOG_MESSAGE_EMPTY()
#endif

#ifdef _ENABLE_LOG_INFO_LOW
	#define	LOG_INFO_LOW		LOG(CGDK::log_type_t::info, CGDK::eLOG_LEVEL::LOWER)
#else
	#define	LOG_INFO_LOW		LOG_MESSAGE_EMPTY()
#endif

// 4) progress log
#ifdef _ENABLE_LOG_PROGRESS
	#define	LOG_PROGRESS		LOG(CGDK::log_type_t::progress)
#else
	#define	LOG_PROGRESS		LOG_MESSAGE_EMPTY()
#endif

// 5) debug log
#ifdef _ENABLE_LOG_DEBUG
	#define	LOG_DEBUG			LOG(CGDK::log_type_t::debug)
#else
	#define	LOG_DEBUG			LOG_MESSAGE_EMPTY()
#endif

// 6) exception log
#ifdef _ENABLE_LOG_FATAL	
	#define	LOG_FATAL			LOG(CGDK::log_type_t::fatal)
#else
	#define	LOG_FATAL			LOG_MESSAGE_EMPTY()
#endif

// 7) error log
#ifdef _ENABLE_LOG_ERROR
	#define	LOG_ERROR			LOG(CGDK::log_type_t::error)
#else
	#define	LOG_ERROR			LOG_MESSAGE_EMPTY()
#endif

// 8) warning log
#ifdef _ENABLE_LOG_WARNING
	#define	LOG_WARNING			LOG(CGDK::log_type_t::warning)
#else
	#define	LOG_WARNING			LOG_MESSAGE_EMPTY()
#endif

// 9) user log
#ifdef _ENABLE_LOG_USER
	#define	LOG_USER			LOG(CGDK::log_type_t::user)
#else
	#define	LOG_USER			LOG_MESSAGE_EMPTY()
#endif
