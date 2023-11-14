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
// ----------------------------------------------------------------------------
//
// 1. Defintions
//
// ----------------------------------------------------------------------------
// 1) 최대 로그 문자열 길이 (주의! 수정하면 안된다!)
#define	MAX_TRACE_STRING_LENGTH	2048


//-----------------------------------------------------------------------------
/**

@class		log_type_t

@brief		로그의 종류 정의
@todo		로그의 종류를 의미한다.
@ref
@details	로그의 각 종류는 다음과 같은 용도를 의미한다.

			log_type_t::info		상태나 설정 등 각종 정보 (설정 혹은 값 등을 표시한다.)
			log_type_t::progress	진행 상태 (순서가 있는 처리의 진행 상태를 표시한다.)
			log_type_t::debug		디버그용
			log_type_t::fatal		예외 (처리를 중단한다.)
			log_type_t::error		오류가 발생 (처리를 중단한다.)
			log_type_t::warning		경고 (처리를 중단하지 않는다.)
			log_type_t::user		사용자 정의
			log_type_t::system		시스템 내부적으로 사용
*/
//-----------------------------------------------------------------------------
enum class log_type_t : uint32_t
{
	info		 = 0,
	progress	 = 1,
	debug		 = 2,
	fatal		 = 3,
	error		 = 4,
	warning		 = 5,
	user		 = 6,
	system		 = 7,
	max_,		// 8
	continue_	 = 0x80000000,

	undefined	 = 0xffff,
};
[[nodiscard]] constexpr log_type_t operator & (log_type_t _lhs, log_type_t _rhs) { return static_cast<log_type_t>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
[[nodiscard]] constexpr log_type_t operator | (log_type_t _lhs, log_type_t _rhs) { return static_cast<log_type_t>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}
[[nodiscard]] constexpr log_type_t operator & (log_type_t _lhs, uint32_t _rhs) { return static_cast<log_type_t>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
[[nodiscard]] constexpr log_type_t operator | (log_type_t _lhs, uint32_t _rhs) { return static_cast<log_type_t>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}

[[nodiscard]] constexpr bool operator == (log_type_t _lhs, log_type_t _rhs) noexcept { return static_cast<uint32_t>(_lhs) == static_cast<uint32_t>(_rhs); }
[[nodiscard]] constexpr bool operator != (log_type_t _lhs, log_type_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_type_t _lhs, log_type_t _rhs) noexcept { return static_cast<uint32_t>(_lhs) >  static_cast<uint32_t>(_rhs); }
[[nodiscard]] constexpr bool operator >= (log_type_t _lhs, log_type_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_type_t _lhs, log_type_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_type_t _lhs, log_type_t _rhs) noexcept { return !(_lhs > _rhs); }

const size_t MAX_LOG_TYPE = static_cast<size_t>(log_type_t::max_) + 1;


//-----------------------------------------------------------------------------
/**

@class		log_level_t

@brief		로그의 중요도 레벨
@todo
@ref
@details	로그의 레벨을 의미하는 것으로 int32_t형 정수범위에서 임의로 설정이 가능하다.
			다만 사용의 기준을 잡기 위해 로그 레벨의 값을 사전에 정의한 거서이다.
			0을 기준 값으로 0이하일 경우 중요도가 낮으며 0이상일 경우 중요도가 높은 것으로 정의했다.
			이 값들은 특별한 의미가 있는 값이 아니라 제시된 값이므로 임의로 설정가능하다.

*/
//-----------------------------------------------------------------------------
struct log_level_t
{
	int value;

	[[nodiscard]] static constexpr log_level_t min_() noexcept { return log_level_t{ INT_MIN }; };
	[[nodiscard]] static constexpr log_level_t max_() noexcept { return log_level_t{ INT_MAX }; };
	[[nodiscard]] static constexpr log_level_t default_() noexcept { return log_level_t{ 0 }; };

	[[nodiscard]] static constexpr log_level_t lowest() noexcept { return min_(); };
	[[nodiscard]] static constexpr log_level_t lower() noexcept { return log_level_t{ -256 }; };
	[[nodiscard]] static constexpr log_level_t normal() noexcept { return default_(); };
	[[nodiscard]] static constexpr log_level_t higher() noexcept { return log_level_t{ 256 }; };
	[[nodiscard]] static constexpr log_level_t highest() noexcept { return max_(); };

	[[nodiscard]] static constexpr log_level_t important() noexcept { return higher(); };

	[[nodiscard]] operator int() const noexcept { return value; }
};
[[nodiscard]] constexpr bool operator == (log_level_t _lhs, log_level_t _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (log_level_t _lhs, log_level_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_level_t _lhs, log_level_t _rhs) noexcept { return _lhs.value > _rhs.value; }
[[nodiscard]] constexpr bool operator >= (log_level_t _lhs, log_level_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_level_t _lhs, log_level_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_level_t _lhs, log_level_t _rhs) noexcept { return !(_lhs > _rhs); }


//-----------------------------------------------------------------------------
/**

@class		log_attribute_t

@brief		로그의 속성
@todo
@ref
@details	사용자 이용
*/
//-----------------------------------------------------------------------------
struct log_attribute_t
{
	uint64_t value;

	[[nodiscard]] static constexpr log_attribute_t min_() noexcept { return log_attribute_t{ 0 }; };
	[[nodiscard]] static constexpr log_attribute_t max_() noexcept { return log_attribute_t{ UINT64_MAX }; };
	[[nodiscard]] static constexpr log_attribute_t default_() noexcept { return log_attribute_t{ 0 }; };
};
[[nodiscard]] constexpr bool operator == (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return _lhs.value > _rhs.value; }
[[nodiscard]] constexpr bool operator >= (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_attribute_t _lhs, log_attribute_t _rhs) noexcept { return !(_lhs > _rhs); }


//-----------------------------------------------------------------------------
/**

@class		log_origin_t

@brief		로그 발원지
@todo
@ref
@details	사용자 이용
*/
//-----------------------------------------------------------------------------
struct log_origin_t
{
	uint64_t value;

	[[nodiscard]] static constexpr log_origin_t min_() noexcept { return log_origin_t{ 0 }; };
	[[nodiscard]] static constexpr log_origin_t max_() noexcept { return log_origin_t{ UINT64_MAX }; };
	[[nodiscard]] static constexpr log_origin_t default_() noexcept { return log_origin_t{ 0 }; };
};
[[nodiscard]] constexpr bool operator == (log_origin_t _lhs, log_origin_t _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (log_origin_t _lhs, log_origin_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_origin_t _lhs, log_origin_t _rhs) noexcept { return _lhs.value > _rhs.value; }
[[nodiscard]] constexpr bool operator >= (log_origin_t _lhs, log_origin_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_origin_t _lhs, log_origin_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_origin_t _lhs, log_origin_t _rhs) noexcept { return !(_lhs > _rhs); }


//-----------------------------------------------------------------------------
/**

@class		log_source_t

@brief		로그를 발행한 소스
@todo
@ref
@details	사용자 이용
*/
//-----------------------------------------------------------------------------
struct log_source_t
{
	uint64_t value;

	[[nodiscard]] static constexpr log_source_t min_() noexcept { return log_source_t{ 0 }; };
	[[nodiscard]] static constexpr log_source_t max_() noexcept { return log_source_t{ UINT64_MAX }; };
	[[nodiscard]] static constexpr log_source_t default_() noexcept { return log_source_t{ 0 }; };
};
[[nodiscard]] constexpr bool operator == (log_source_t _lhs, log_source_t _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (log_source_t _lhs, log_source_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_source_t _lhs, log_source_t _rhs) noexcept { return _lhs.value > _rhs.value; }
[[nodiscard]] constexpr bool operator >= (log_source_t _lhs, log_source_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_source_t _lhs, log_source_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_source_t _lhs, log_source_t _rhs) noexcept { return !(_lhs > _rhs); }


//-----------------------------------------------------------------------------
/**

@class		log_destination_t

@brief		로그를 받을 목표
@todo
@ref
@details	사용자 이용
*/
//-----------------------------------------------------------------------------
struct log_destination_t
{
	uint64_t value;

	[[nodiscard]] static constexpr log_destination_t min_() noexcept { return log_destination_t{ 0 }; };
	[[nodiscard]] static constexpr log_destination_t max_() noexcept { return log_destination_t{ UINT64_MAX }; };
	[[nodiscard]] static constexpr log_destination_t default_() noexcept { return log_destination_t{ 0 }; };
};
[[nodiscard]] constexpr bool operator == (log_destination_t _lhs, log_destination_t _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (log_destination_t _lhs, log_destination_t _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator >  (log_destination_t _lhs, log_destination_t _rhs) noexcept { return _lhs.value > _rhs.value; }
[[nodiscard]] constexpr bool operator >= (log_destination_t _lhs, log_destination_t _rhs) noexcept { return !(_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <  (log_destination_t _lhs, log_destination_t _rhs) noexcept { return  (_rhs > _lhs); }
[[nodiscard]] constexpr bool operator <= (log_destination_t _lhs, log_destination_t _rhs) noexcept { return !(_lhs > _rhs); }

}

template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(CGDK::log_type_t _log_type) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(CGDK::log_type_t _log_type) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(CGDK::log_type_t _log_type) noexcept;
