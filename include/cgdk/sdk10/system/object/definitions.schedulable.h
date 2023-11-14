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

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// definitions
//
//-----------------------------------------------------------------------------
enum class eSCHEDULABLE_TYPE : int32_t
{
	DEFAULT				 = 0,	// default
	SYSTEM				 = 1,	// system scheduler
	USER				 = 2,	// user scheduler
	MAX
};

// 2) to_string functions
template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(eSCHEDULABLE_TYPE _character_set) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(eSCHEDULABLE_TYPE _character_set) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(eSCHEDULABLE_TYPE _character_set) noexcept;

namespace statistics
{
	struct schedulable
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id = 0;
		eSCHEDULABLE_TYPE		type = eSCHEDULABLE_TYPE::USER;
		std::atomic<uint64_t>	count_execute = 0;
	};
}

}