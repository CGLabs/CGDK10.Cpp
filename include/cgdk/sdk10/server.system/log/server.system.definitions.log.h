//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
// ----------------------------------------------------------------------------
//
// Log (configure)
//
// ----------------------------------------------------------------------------
// 1) Original Time
enum class eORIGIN_TIME_TYPE : uint32_t
{
	NOW			 = 0,
	MINUTE_BEGIN = 1,
	HOUR_BEGIN	 = 2,
	DAY_BEGIN	 = 3,
	WEEK_BEGIN	 = 4,
	MONTH_BEGIN	 = 5,
	YEAR_BEGIN	 = 6,
	SPECIFIED	 = 7,
	MAX,

	DEFAULT		 = NOW
};

// 2) functions
template <class T>	[[nodiscard]] std::basic_string_view<T> to_string(eORIGIN_TIME_TYPE _origin_time_type, bool _upper_case=true) noexcept;
template <>			[[nodiscard]] std::string_view to_string<char>(eORIGIN_TIME_TYPE _origin_time_type, bool _upper_case) noexcept;
template <>			[[nodiscard]] std::wstring_view to_string<wchar_t>(eORIGIN_TIME_TYPE _origin_time_type, bool _upper_case) noexcept;

#if defined(_WIN32)
	#define	DEFAULT_CONSOLE_CHARACTER_SET	eCHARACTER_SET::MBCS
#else
	#define	DEFAULT_CONSOLE_CHARACTER_SET	eCHARACTER_SET::UTF8
#endif


}