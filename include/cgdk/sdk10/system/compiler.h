//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Complier Classes                             *
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
#define	CGCOMPILER_CLASSES


//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------
// 1) Default Definitions
#include "CGUtilClasses.h"

// 2) Definitions
#include "CGCompilerClasses/CGDefinitionsCompilerProtocol.h"
#include "CGCompilerClasses/CGDefinitionsCompiler.h"

// 3) Souce
#include "CGCompilerClasses/CGCompilerSource.h"
#include "CGCompilerClasses/CGCompilerSourceFile.h"

// 4) Lexer
#include "CGCompilerClasses/CGCompilerLexer.h"
#include "CGCompilerClasses/CGCompilerLexerBase.h"




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
	#if _MSC_PLATFORM_TOOLSET>=143

	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses64_DLL_v143.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses64_DLL_v143_Debug.lib")
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses64_v143.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses64_v143_Debug.lib")
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses_DLL_v143.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses_DLL_v143_Debug.lib")
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses_v143.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses_v143_Debug.lib")
			#endif
		#endif
	#else
		#error "Unsupport Platform"
	#endif


	//----------------------------------------------------------------------------
	// * vs16 Lib 
	//----------------------------------------------------------------------------
	#elif _MSC_PLATFORM_TOOLSET>=142

	#if defined(_M_X64)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses64_DLL_v142.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses64_DLL_v142_Debug.lib")
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses64_v142.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses64_v142_Debug.lib")
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version일 때
		#ifdef _DLL 
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses_DLL_v142.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses_DLL_v142_Debug.lib")
			#endif

		//2) DLL이 아닐 때
		#else
			#ifdef NDEBUG
				#pragma comment(lib,"CGCompilerClasses_v142.lib")
			#else
				#pragma comment(lib,"CGCompilerClasses_v142_Debug.lib")
			#endif
		#endif
	#else
		#error "Unsupport Platform"
	#endif

#else
	#error "Unsupport Platform Toolset"
#endif

#endif
