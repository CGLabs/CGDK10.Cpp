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

namespace CGDK
{
//-----------------------------------------------------------------------------
//                                                                            
// Definitions
//                                                                            
//-----------------------------------------------------------------------------
enum class eOS_TYPE : uint32_t
{
	NOT_DEFINED			 = 0,
	IOS					 = 1,
	ANDROID				 = 2,
	WINDOWS_NAVTIVE		 = 3,
	WINDOWS_UNIVERSAL	 = 4,
	LINUX				 = 5,
	MACOS				 = 6
};

template <class T=char>	std::basic_string_view<T> to_string(eOS_TYPE /*_os_type*/) noexcept	{ CGASSERT_ERROR(false); return nullptr;}
template <> std::string_view to_string<char>(eOS_TYPE _os_type) noexcept;
template <> std::wstring_view to_string<wchar_t>(eOS_TYPE _os_type) noexcept;


enum class eLANGUAGE : uint32_t
{
	// 1) 
	NOT_DEFINED			 = 0,

	// 2) �ѱ���
	KOREAN				 = 1,				// �ѱ���

	// 3) �ƽþ�
	MANDARIN,								// �ϰ��(���ٸ�)
	CANTONESE,								// ������(ĭ�����)
	JANANESE,								// �Ϻ���
	TAI,									// �±���

	// 4) ����
	ENGLISH,								// ����
	SPAINESE,								// �����ξ�
	PORTUGUESE,								// ������Į��
	FRANCE,									// ��������
	DEUTSCHESE,								// ���Ͼ�
	DUTCH,									// �׵������
	RUSSIAN,								// ���þƾ�
};

template <class T>	std::basic_string_view<T> to_string(eLANGUAGE /*_language*/) noexcept { CGASSERT_ERROR(false); return nullptr; }
template <> std::string_view to_string<char>(eLANGUAGE _language) noexcept;
template <> std::wstring_view to_string<wchar_t>(eLANGUAGE _language) noexcept;


//-----------------------------------------------------------------------------
// 1. Device Info
//-----------------------------------------------------------------------------
#define	PLATFORM_VISUALSTUDIO_EMULATOR_FOR_ANDROID	0
#define	PLATFORM_ANDROID_VIRTUAL_DEVICE				1
#define	PLATFORM_ANDROID_DEVICE_TYPE_0				2
#define	PLATFORM_ANDROID_DEVICE_TYPE_1				3
#define	PLATFORM_IOS_GENERAL						4
#define	PLATFORM_IOS_A9_DEVICE						5
#define	PLATFORM_IOS_A10_DEVICE						6
#define	PLATFORM_UWP_DEVICE							7

#define	CONFIGURE_MINIMUM							0
#define	CONFIGURE_LOW								1
#define	CONFIGURE_NORMAL							2
#define	CONFIGURE_HIGH								3
#define	CONFIGURE_HIGHER							4
#define	CONFIGURE_EXTREME							5


}