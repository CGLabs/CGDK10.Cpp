//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           CGCII Script Classes                            *
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
// Class Definition
//-----------------------------------------------------------------------------
#define	CGDYNAMIC_CLASSES


//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------
// 1) Memory Classes
#include "CGPoolClasses.h"
#include "CGDynamicClasses.h"


//----------------------------------------------------------------------------
// Messageable & Dispatcher
//----------------------------------------------------------------------------
// 1) ICGObject
#include "CGScriptClasses/ICGScriptCommandable.h"

// 2) Script
#include "CGCompilerClasses.h"
#include "CGScriptClasses/CGDynamicScript.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _LIB

#if !defined(_MSC_PLATFORM_TOOLSET)
	#if _MSC_VER>=_MSC_VER_2022
		#define	_MSC_PLATFORM_TOOLSET	143
	#elif _MSC_VER>=_MSC_VER_2019
		#define	_MSC_PLATFORM_TOOLSET	142
	#elif _MSC_VER>=_MSC_VER_2017
		#define	_MSC_PLATFORM_TOOLSET	141
	#elif _MSC_VER>=_MSC_VER_2015
		#define	_MSC_PLATFORM_TOOLSET	140
	#elif _MSC_VER>=_MSC_VER_2013
		#define	_MSC_PLATFORM_TOOLSET	120
	#elif _MSC_VER>=_MSC_VER_2012
		#define	_MSC_PLATFORM_TOOLSET	110
	#elif _MSC_VER>=_MSC_VER_2010
		#define	_MSC_PLATFORM_TOOLSET	100
	#elif _MSC_VER>=_MSC_VER_2008
		#define	_MSC_PLATFORM_TOOLSET	90
	#else
		#define	_MSC_PLATFORM_TOOLSET	80
	#endif
#endif


//----------------------------------------------------------------------------
// * vs15 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=142

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_DLL_v142.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_DLL_v142_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_v142.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_v142_Debug.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_DLL_v142.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_DLL_v142_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_v142.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_v142_Debug.lib")
		#endif
	#endif
#else
	#error "Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * vs15 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=141

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_DLL_v141.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_DLL_v141_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_v141.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_v141_Debug.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_DLL_v141.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_DLL_v141_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_v141.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_v141_Debug.lib")
		#endif
	#endif
#else
	#error "Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * vs14 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_DLL_v140.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_DLL_v140_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses64_v140.lib")
		#else
			#pragma comment(lib,"CGScriptClasses64_v140_Debug.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_DLL_v140.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_DLL_v140_Debug.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef NDEBUG
			#pragma comment(lib,"CGScriptClasses_v140.lib")
		#else
			#pragma comment(lib,"CGScriptClasses_v140_Debug.lib")
		#endif
	#endif
#else
	#error "Unsupport Platform"
#endif

#else
	#error "Unsupport Platform Toolset"
#endif

#endif
