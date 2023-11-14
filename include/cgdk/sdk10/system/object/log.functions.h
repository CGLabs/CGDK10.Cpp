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
// 1. Default Tracer
//
//-----------------------------------------------------------------------------
// 10) Default Tracer
object_ptr<Ilogger>		get_default_logger();
object_ptr<Ilogger>		set_default_logger(Ilogger* _plogger);
object_ptr<Ilogger>		reset_default_logger(Ilogger* _plogger = nullptr);
#define	DEFAULT_LOGGER	get_default_logger()


//-----------------------------------------------------------------------------
//
// 2. _log functions
//
//-----------------------------------------------------------------------------
// 1) log function 1
void _log(Ilogger* _plogger, LOG_RECORD* _plog_record) noexcept;
void _log(Ilogger* _plogger, const std::vector<object_ptr<LOG_RECORD>>& _vector_plog_record) noexcept;

// 2) log function 2
void _log(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::string_view _message) noexcept;
void _log(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::wstring_view _message) noexcept;

// 3) Log function {fmt}
#if defined(FMT_FORMAT_H_)
inline void _log_fmt(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::string_view _message) noexcept
{
	_log(_plogger, _type, _level, _character_set, _message);
}
inline void _log_fmt(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::wstring_view _message) noexcept
{
	_log(_plogger, _type, _level, _character_set, _message);
}
template <class TA, class... TARGS>
void _log_fmt(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::basic_string_view<char> _format, TA _A, TARGS... _args) noexcept
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// 1) set default value if character_set is eCHARACTER_SET::NONE
	if (_character_set == eCHARACTER_SET::NONE)
	{
		_character_set = _DEFAULT_CHAR_CHARACTER_SET;
	}

	try
	{
		// declare) 
		fmt::basic_memory_buffer<char> temp_buffer;

		// 3) Generate trace Message
		fmt::format_to(temp_buffer, _format.data(), _A, _args...);

		// check)
		CGASSERT_ERROR(temp_buffer.size() >= 0);

		// check)
		RETURN_IF(temp_buffer.size() < 0);

		// 2) call _log
		_log(_plogger, _type, _level, _character_set, std::basic_string_view<char>(temp_buffer.data(), temp_buffer.size()));
	}
	catch (...)
	{
	}
}

template <class TA, class... TARGS>
void _log_fmt(Ilogger* _plogger, log_type_t _type, int _level, eCHARACTER_SET _character_set, const std::basic_string_view<wchar_t> _format, TA _A, TARGS... _args) noexcept
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// 1) set default value if character_set is eCHARACTER_SET::NONE
	if (_character_set == eCHARACTER_SET::NONE)
	{
		_character_set = _DEFAULT_WCHAR_CHARACTER_SET;
	}

	try
	{
		// declare) 
		fmt::basic_memory_buffer<wchar_t> temp_buffer;

		// 3) Generate trace Message
		fmt::format_to(temp_buffer, _format.data(), _A, _args...);

		// check)
		CGASSERT_ERROR(temp_buffer.size() >= 0);

		// check)
		RETURN_IF(temp_buffer.size() < 0);

		// 2) call _log
		_log(_plogger, _type, _level, _character_set, std::basic_string_view<wchar_t>(temp_buffer.data(), temp_buffer.size()));
	}
	catch (...)
	{
	}
}
#endif


}