//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Query odbc Classes                         *
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
// query::rdb::odbc::ODBC_GET_VALUE
//
// 
//-----------------------------------------------------------------------------
// 1) general
template <class T, class F = void>
class _ODBC_DEFAULT_PARAM
{
public:
	using type = T;
};

// 2) for wchar_t
#if defined(__linux__)
template <>
class _ODBC_DEFAULT_PARAM<std::wstring, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};

template <>
class _ODBC_DEFAULT_PARAM<std::wstring_view, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};

template <>
class _ODBC_DEFAULT_PARAM<wchar_t*, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};
#endif

// 3) 
template <class T>
class _ODBC_DEFAULT_PARAM<std::basic_string<T>, void>
{
public:
	using type = T*;
};

template <class T>
class _ODBC_DEFAULT_PARAM<std::basic_string_view<T>, void>
{
public:
	using type = T*;
};

template <class T>
class _ODBC_DEFAULT_PARAM<T*, typename std::enable_if<is_string_type_v<T>>::type>
{
public:
	using type = T*;
};


//-----------------------------------------------------------------------------
//
// general
//
//-----------------------------------------------------------------------------
template <class TSOURCE, class TDEST, class F = void> 
class ODBC_GET_VALUE
{
public:
	using TRETURN = TDEST;
	static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)  { return _get<TDEST>(_handle_stmt, _ordinal); }

	template <class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<TSOURCE, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		TRETURN value = TRETURN(0);
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), _sql_param<TSOURCE>::column_type(), reinterpret_cast<SQLPOINTER>(&value), sizeof(TRETURN), &indicator);

		// return) 
		return (SQL_SUCCEEDED(result) && indicator > 0) ? value : TRETURN();
	} 

	template <class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<TSOURCE, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		TRETURN value = TRETURN(0);
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), _sql_param<TSOURCE>::column_type(), reinterpret_cast<SQLPOINTER>(&value), sizeof(TRETURN), &indicator);

		// return) 
		return static_cast<TRETURN>((SQL_SUCCEEDED(result) && indicator > 0) ? value : TRETURN());
	} 
};


//-----------------------------------------------------------------------------
//
// string
//
//-----------------------------------------------------------------------------
template <class T, class F = void>
class _value_type
{
};

template <class T>
class _value_type<T*, std::enable_if_t<is_string_type_v<T>>>
{
public:
	using type = T;
};

template <class T>
class _value_type<std::basic_string_view<T>, void>
{
public:
	using type = T;
};

template <class T>
class _value_type<std::basic_string<T>, void>
{
public:
	using type = T;
};

shared_buffer _ODBC_get_binary_data(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, SQLSMALLINT _target_type);

template <class TSOURCE, class TDEST>
class ODBC_GET_VALUE<TSOURCE*, TDEST, std::enable_if_t<is_string_type_v<TSOURCE>>>
{
public:
	using value_type = typename _value_type<TDEST>::type;
	using TRETURN = std::basic_string<value_type>;
	[[nodiscard]] static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) { return _get<value_type>(_handle_stmt, _ordinal); }

	template <class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<wchar_t, T> && std::is_same_v<std::decay_t<TSOURCE>, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		// 1) read binary data
		auto buf_result = _ODBC_get_binary_data(_handle_stmt, _ordinal, SQL_C_CHAR);

		// return) 
		return TRETURN(buf_result.data<std::decay_t<TSOURCE>>(), buf_result.size() / sizeof(TSOURCE));
	}

	template <class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<wchar_t, T> && std::is_same_v<std::decay_t<TSOURCE>, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		// 1) read binary data
		auto buf_result = _ODBC_get_binary_data(_handle_stmt, _ordinal, SQL_C_WCHAR);

		// return) 
		return TRETURN(buf_result.data<std::decay_t<TSOURCE>>(), buf_result.size() / sizeof(TSOURCE));
	}
	   
	template <class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<wchar_t, T> && !std::is_same_v<std::decay_t<TSOURCE>, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		// 1) read binary data
		auto buf_result = _ODBC_get_binary_data(_handle_stmt, _ordinal, SQL_C_CHAR);

		// return) 
		return TRETURN(buf_result.data<std::decay_t<TDEST>>(), buf_result.size() / sizeof(TSOURCE));
	}

	template <class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<wchar_t, T> && !std::is_same_v<std::decay_t<TSOURCE>, T>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		// 1) read binary data
		auto buf_result = _ODBC_get_binary_data(_handle_stmt, _ordinal, SQL_C_CHAR);

		// 2) create
		TRETURN str_dest;

		// 4) get size
		auto length = buf_result.size() / sizeof(TSOURCE);

		// 5) resize
		str_dest.resize(length);

		// 6) ...
		encode_string(&str_dest.front(), std::basic_string_view<TSOURCE>{ buf_result.data<TSOURCE>(), length }, length + 1);

		// return) 
		return str_dest;
	}
};


//-----------------------------------------------------------------------------
//
// numeric
//
//-----------------------------------------------------------------------------
template <class TDEST>
class ODBC_GET_VALUE<NUMERIC, TDEST, void>
{
public:
	using TRETURN = TDEST;
	static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)  { return _get<TDEST>(_handle_stmt, _ordinal);	}

	template <class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<NUMERIC, TDEST>, TRETURN>
	_get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		SQL_NUMERIC_STRUCT value;
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_C_NUMERIC, reinterpret_cast<SQLPOINTER>(&value), sizeof(SQL_NUMERIC_STRUCT), &indicator);

		// return) 
		return (SQL_SUCCEEDED(result) && indicator > 0) ? __to_numeric(value) : NUMERIC();
	}
};

//-----------------------------------------------------------------------------
//
// time_point (time_stamp, datetime)
//
//-----------------------------------------------------------------------------
template <class TDEST>
class ODBC_GET_VALUE<chrono::time::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	[[nodiscard]] static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)  { return _get<TDEST>(_handle_stmt, _ordinal); }

	template <class T>
	[[nodiscard]] static TRETURN _get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		chrono::date_time value;
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_TIMESTAMP, reinterpret_cast<SQLPOINTER>(&value), sizeof(TIMESTAMP_STRUCT), &indicator);

		// return) 
		return (SQL_SUCCEEDED(result) && indicator > 0) ? chrono::from_date_time<chrono::time::time_point>(value) : chrono::time::time_point();
	}
};

template <class TDEST>
class ODBC_GET_VALUE<chrono::time::utc::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	[[nodiscard]] static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		chrono::date_time value;
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_TIMESTAMP, reinterpret_cast<SQLPOINTER>(&value), sizeof(TIMESTAMP_STRUCT), &indicator);

		// return) 
		return (SQL_SUCCEEDED(result) && indicator > 0) ? chrono::from_date_time<chrono::time::utc::time_point>(value) : chrono::time::utc::time_point();
	}
};

template <class TDEST>
class ODBC_GET_VALUE<chrono::time::local::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	[[nodiscard]] static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal) 
	{
		// declare) 
		chrono::date_time value;
		SQLLEN indicator = 0;

		// 1) SQLGetData
		auto result = SQLGetData(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_TIMESTAMP, reinterpret_cast<SQLPOINTER>(&value), sizeof(TIMESTAMP_STRUCT), &indicator);

		// return) 
		return (SQL_SUCCEEDED(result) && indicator > 0) ? chrono::from_date_time<chrono::time::local::time_point>(value) : chrono::time::local::time_point();
	}
};


//-----------------------------------------------------------------------------
//
// binary (shared_buffer)
//
//-----------------------------------------------------------------------------
template <class TDEST>
class ODBC_GET_VALUE<shared_buffer, TDEST, void>
{
public:
	using TRETURN = TDEST;
	[[nodiscard]] static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		return _ODBC_get_binary_data(_handle_stmt, _ordinal, SQL_C_BINARY);
	}
};


//-----------------------------------------------------------------------------
//
// struct
//
//-----------------------------------------------------------------------------
template <std::size_t INDEX>
struct any_constructor_get_value
{
	SQLHSTMT handle_stmt;
	SQLUSMALLINT ordinal;
	template <class Type>
	constexpr operator Type() const 
	{
		return ODBC_GET_VALUE<typename _ODBC_DEFAULT_PARAM<Type>::type, Type>::get(handle_stmt, static_cast<SQLUSMALLINT>(ordinal + INDEX));
	}
};

template <class T, std::size_t... I>
constexpr T get_value_member_impl(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, std::index_sequence<I...>)
{
	return T{ any_constructor_get_value<I>{_handle_stmt, _ordinal}... };
}

template <class T, class TDEST>
class ODBC_GET_VALUE<T, TDEST, std::enable_if_t<is_struct_serializable_v<T>>>
{
public:
	using TRETURN = TDEST;
	static TRETURN get(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal)
	{
		// check)
		static_assert(!std::is_polymorphic<T>::value, "'struct_serializable' class must not be polymorphic (no virtual fuction)");

		// check)
		static_assert(std::is_default_constructible<T>::value, "'struct_serializable' class must have default constructor (remove construtor)");

		return get_value_member_impl<T>(_handle_stmt, _ordinal, std::make_index_sequence<constexpr_field_count<T>>());
	}
};


}