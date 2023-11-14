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
// 1) �ִ� �α� ���ڿ� ���� (����! �����ϸ� �ȵȴ�!)
#define	MAX_TRACE_STRING_LENGTH	2048


//-----------------------------------------------------------------------------
/**

@class		log_type_t

@brief		�α��� ���� ����
@todo		�α��� ������ �ǹ��Ѵ�.
@ref
@details	�α��� �� ������ ������ ���� �뵵�� �ǹ��Ѵ�.

			log_type_t::info		���³� ���� �� ���� ���� (���� Ȥ�� �� ���� ǥ���Ѵ�.)
			log_type_t::progress	���� ���� (������ �ִ� ó���� ���� ���¸� ǥ���Ѵ�.)
			log_type_t::debug		����׿�
			log_type_t::fatal		���� (ó���� �ߴ��Ѵ�.)
			log_type_t::error		������ �߻� (ó���� �ߴ��Ѵ�.)
			log_type_t::warning		��� (ó���� �ߴ����� �ʴ´�.)
			log_type_t::user		����� ����
			log_type_t::system		�ý��� ���������� ���
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

@brief		�α��� �߿䵵 ����
@todo
@ref
@details	�α��� ������ �ǹ��ϴ� ������ int32_t�� ������������ ���Ƿ� ������ �����ϴ�.
			�ٸ� ����� ������ ��� ���� �α� ������ ���� ������ ������ �ż��̴�.
			0�� ���� ������ 0������ ��� �߿䵵�� ������ 0�̻��� ��� �߿䵵�� ���� ������ �����ߴ�.
			�� ������ Ư���� �ǹ̰� �ִ� ���� �ƴ϶� ���õ� ���̹Ƿ� ���Ƿ� ���������ϴ�.

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

@brief		�α��� �Ӽ�
@todo
@ref
@details	����� �̿�
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

@brief		�α� �߿���
@todo
@ref
@details	����� �̿�
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

@brief		�α׸� ������ �ҽ�
@todo
@ref
@details	����� �̿�
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

@brief		�α׸� ���� ��ǥ
@todo
@ref
@details	����� �̿�
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
