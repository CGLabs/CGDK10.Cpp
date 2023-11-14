//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             CG Object Classes                             *
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


//----------------------------------------------------------------------------
// CGCII afxwin Prefix
// 
// �� ������ MFC�� ����� �� stdafx.h ������ "afxwin.h"�� include �ϱ�����
// Include ����� �Ѵ�.
// �� ������ include�� Microsof C++ Core Guide lines�� �������� �ʿ��� �����̴�.
// 
// afxwin.h�� ��ũ���� min()�� max()�� ��ø���� ���� ������ �ذ��ϱ� ���� ���̴�. 
// 
//    1) NOMINMAX�� afxwin.h�� Include �Ǳ� ���� ������ afxwin.h�� min()�� 
//       max()�� ����ȭ�Ѵ�.
//    2) ���� ��ũ�� min()/max()�� ��ü�� �Լ��� �� min()�� max()�� �����Ѵ�.
// 
//----------------------------------------------------------------------------
#if defined(_WIN32)
	#if defined (_M_X64)
		#pragma message("[CGDK10] configure... 'WIN32-x64'")
	#else
		#pragma message("[CGDK10] configure... 'WIN32-x86'")
	#endif
#elif defined(__linux__)
#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#endif

// Debug)
#if defined(_MSC_VER)
	#ifndef NDEBUG
		#define _CRTDBG_MAP_ALLOC
		#if _MSC_VER<_MSC_VER_2015
			#define _INC_MALLOC
		#endif
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#if !defined(min) & !defined(_FUNCTION_MIN)
	#define	_FUNCTION_MIN

	template<class VALUE>
	const VALUE& min(const VALUE& _a, const VALUE& _b)
	{
		return	(_a>_b) ? _b : _a;
	}
#endif

#if !defined(max) & !defined(_FUNCTION_MAX)
	#define	_FUNCTION_MAX

	template<class VALUE>
	const VALUE& max(const VALUE& _a, const VALUE& _b)
	{
		return	(_a>_b) ? _a : _b;
	}
#endif
