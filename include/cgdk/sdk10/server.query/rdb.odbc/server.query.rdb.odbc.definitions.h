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
//----------------------------------------------------------------------------
//
//  query odbc classes
//
//----------------------------------------------------------------------------
namespace query
{
namespace rdb
{
namespace odbc
{
	void						_dump_error_records(throwable::failure_ex& _e, SQLSMALLINT _handle_type, SQLHANDLE _handle) noexcept;
	throwable::failure_ex		_dump_error_records(SQLRETURN _result, const std::string_view _command, SQLHSTMT _handle_stmt) noexcept;

	throwable::failure_ex		_dump_error_records_env	(SQLHENV _handle_env) noexcept;
	throwable::failure_ex		_dump_error_records_dbc	(SQLHDBC _handle_dbc) noexcept;
	void						_dump_error_records_stmt(throwable::failure_ex& _e, SQLHSTMT _handle_stmt) noexcept;

	throwable::failure_ex trace_error_records(Iquery* _pquery, SQLRETURN _result, const std::string_view _str_query_string);
	void regen_session(session* _psession);

}
}
}

// definitions)
struct SERVER_QUERY_ERROR_INFO
{
	object_ptr<Iquerier>		pquerier;
	object_ptr<Iserver_query>	pquery;

	intptr_t					result = 0;
	const char*					str_query = nullptr;
	Ndescription_ex				exception;
};

// definitions)
struct ODBC_DRIVER_INFO
{
	std::string					driver;
	std::string					attribute;
};


//----------------------------------------------------------------------------
//
//  query odbc fuctions
//
//----------------------------------------------------------------------------
[[nodiscard]] NUMERIC				__to_numeric(const SQL_NUMERIC_STRUCT& _decimal) noexcept;
[[nodiscard]] SQL_NUMERIC_STRUCT	__to_sql_numeric_struct(const NUMERIC& _numeric) noexcept;
[[nodiscard]] SQL_TIMESTAMP_STRUCT  __to_sql_TIMESTAMP_struct(const chrono::time::time_point& _time) noexcept;
[[nodiscard]] SQL_TIMESTAMP_STRUCT  __to_sql_TIMESTAMP_struct(const chrono::time::utc::time_point& _time) noexcept;
[[nodiscard]] SQL_TIMESTAMP_STRUCT  __to_sql_TIMESTAMP_struct(const chrono::time::local::time_point& _time) noexcept;

template<class TTYPE>
		   class _sql_param						{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_BINARY; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_BINARY; } };
template<> class _sql_param<bool>				{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_BIT; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_BIT; } };
template<> class _sql_param<int8_t>				{ public: using type = int8_t;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_STINYINT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_TINYINT; } };
template<> class _sql_param<uint8_t>			{ public: using type = uint8_t;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_UTINYINT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_TINYINT; } };
template<> class _sql_param<int16_t>			{ public: using type = SQLSMALLINT; [[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_SSHORT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_SMALLINT; } };
template<> class _sql_param<uint16_t>			{ public: using type = SQLUSMALLINT;[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_USHORT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_SMALLINT; } };
template<> class _sql_param<int32_t>			{ public: using type = SQLINTEGER;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_SLONG; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_INTEGER; } };
template<> class _sql_param<uint32_t>			{ public: using type = SQLUINTEGER;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_ULONG; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_INTEGER; } };
template<> class _sql_param<int64_t>			{ public: using type = SQLBIGINT;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_SBIGINT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_BIGINT; } };
template<> class _sql_param<uint64_t>			{ public: using type = SQLUBIGINT;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_UBIGINT; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_BIGINT; } };
template<> class _sql_param<float>				{ public: using type = SQLREAL;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_FLOAT; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_REAL; } };
template<> class _sql_param<double>				{ public: using type = SQLDOUBLE;   [[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_DOUBLE; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_DOUBLE; } };

template<> class _sql_param<void*>				{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_BINARY; }	[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_BINARY; } };
template<> class _sql_param<char*>				{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_CHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_CHAR; } };
template<> class _sql_param<wchar_t*>			{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<char16_t*>			{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<char32_t*>			{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_WLONGVARCHAR; }[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WLONGVARCHAR; } };
template<> class _sql_param<std::string>		{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_CHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_CHAR; } };
template<> class _sql_param<std::wstring>		{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<std::u16string>		{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<std::u32string>		{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_WLONGVARCHAR; }[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WLONGVARCHAR; } };
template<> class _sql_param<std::string_view>	{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_CHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_CHAR; } };
template<> class _sql_param<std::wstring_view>	{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<std::u16string_view>{ public: using type = SQLWCHAR;	[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_C_WCHAR; }		[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WCHAR; } };
template<> class _sql_param<std::u32string_view>{ public: using type = SQLCHAR;		[[nodiscard]] static SQLSMALLINT column_type() noexcept { return SQL_WLONGVARCHAR; }[[nodiscard]] static SQLSMALLINT data_type() noexcept { return SQL_WLONGVARCHAR; } };


}
