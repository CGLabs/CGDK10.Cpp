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
// query::rdb::odbc::ODBC_GET_PARAM
//
// 
//-----------------------------------------------------------------------------
// 1) ODBC params info
struct sPARAM
{
public:
	SQLSMALLINT data_type = 0;
	SQLSMALLINT decimal_digits = 0;
	SQLSMALLINT nullable = 0;
	SQLULEN param_size = 0;
	SQLLEN strLen_or_indptr = 0;
	union
	{
		int64_t			data;
		int8_t			data_int8_t;
		SQLINTEGER		data_SQLINTEGER;
		SQLSMALLINT		data_SQLSMALLINT;
		SQLBIGINT		data_SQLBIGINT;
		uint8_t			data_uint8_t;
		SQLUINTEGER		data_SQLUINTEGER;
		SQLUSMALLINT	data_SQLUSMALLINT;
		SQLUBIGINT		data_SQLUBIGINT;
		float			data_float;
		SQLDOUBLE		data_SQLDOUBLE;
		SQLCHAR			data_SQLCHAR;
		SQL_TIMESTAMP_STRUCT data_timestamp;
	};

public:
	template<class T>
	T*			get_data() noexcept { return reinterpret_cast<T*>(&data); }
	template<class T>
	void		set_data(const T& _data) noexcept { reinterpret_cast<T&>(data) = _data; }
};

struct sCOLUMN
{
public:
	SQLSMALLINT index;
	char		name[64];
public:
};


// 2) ODBC set param
template <class TTYPE>
			inline SQLRETURN ODBC_SET_PARAM_signed_integer					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const TTYPE& _data)
{
	// declar) 
	SQLLEN value_max;
	SQLSMALLINT column_type;

	// 1) set param
	_param_info.strLen_or_indptr = 0;
	switch (_param_info.data_type)
	{
	case	SQL_TINYINT: // (-6)
			{
				value_max = sizeof(int8_t);
				column_type = SQL_C_STINYINT;
				_param_info.data_int8_t = static_cast<int8_t>(_data);
			}
			break;

	case	SQL_INTEGER: // 4
			{
				value_max = sizeof(SQLINTEGER);
				column_type = SQL_C_SLONG; // SQL_C_ULONG
				_param_info.data_SQLINTEGER = static_cast<SQLINTEGER>(_data);
			}
			break;

	case	SQL_SMALLINT: // 5
			{
				value_max = sizeof(SQLSMALLINT);
				column_type = SQL_C_SSHORT;
				_param_info.data_SQLSMALLINT = static_cast<SQLSMALLINT>(_data);
			}
			break;

	case	SQL_BIGINT: // (-5)
			{
				value_max = sizeof(SQLBIGINT);
				column_type = SQL_C_SBIGINT;
				_param_info.data_SQLBIGINT = static_cast<SQLBIGINT>(_data);
			}
			break;

	case	SQL_VARCHAR: // (12) mysql always SQL_VARCHAR
			{
				_param_info.data_type = SQL_BIGINT;
				_param_info.param_size = 0;
				_param_info.decimal_digits = 0;
				value_max = sizeof(SQLBIGINT);
				column_type = SQL_C_SBIGINT;
				_param_info.data_SQLBIGINT = static_cast<SQLBIGINT>(_data);
			}
			break;

	default:
		throw throwable::failure_ex(eRESULT::INVALID_ARGUMENT, 0, std::string_view("(error) invalid parameter type"));
	}

	// 2) bind
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, column_type, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, &_param_info.data, value_max, &_param_info.strLen_or_indptr);
}
template <class TTYPE>
			inline SQLRETURN ODBC_SET_PARAM_unsigned_integer				(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const TTYPE& _data)
{
	// declar) 
	SQLLEN value_max;
	SQLSMALLINT column_type;

	// 1) set param
	_param_info.strLen_or_indptr = 0;
	switch (_param_info.data_type)
	{
	case	SQL_TINYINT: // (-6)
			value_max = sizeof(uint8_t);
			column_type = SQL_C_UTINYINT;
			_param_info.data_uint8_t = static_cast<uint8_t>(_data);
			break;

	case	SQL_INTEGER: // 4
			value_max = sizeof(SQLUINTEGER);
			column_type = SQL_C_ULONG;
			_param_info.data_SQLUINTEGER = static_cast<SQLUINTEGER>(_data);
			break;

	case	SQL_SMALLINT: // 5
			value_max = sizeof(SQLUSMALLINT);
			column_type = SQL_C_USHORT;
			_param_info.data_SQLUSMALLINT = static_cast<SQLUSMALLINT>(_data);
			break;

	case	SQL_BIGINT: // (-5)
			value_max = sizeof(SQLUBIGINT);
			column_type = SQL_C_UBIGINT;
			_param_info.data_SQLUBIGINT = static_cast<SQLUBIGINT>(_data);
			break;

	case	SQL_VARCHAR: // (12) mysql always SQL_VARCHAR
			_param_info.data_type = SQL_BIGINT;
			_param_info.param_size = 0;
			_param_info.decimal_digits = 0;
			value_max = sizeof(SQLUBIGINT);
			column_type = SQL_C_UBIGINT;
			_param_info.data_SQLUBIGINT = static_cast<SQLUBIGINT>(_data);
			break;
	default:
		throw throwable::failure_ex(eRESULT::INVALID_ARGUMENT, 0, std::string_view("(error) invalid parameter type"));
	}

	// 2) bind
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, column_type, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, &_param_info.data, value_max, &_param_info.strLen_or_indptr);
}
template <class TTYPE>
			inline SQLRETURN ODBC_SET_PARAM_float							(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const TTYPE& _data)
{
	// declar) 
	SQLLEN value_max;
	SQLSMALLINT column_type;

	// 1) set param
	_param_info.strLen_or_indptr = 0;
	switch (_param_info.data_type)
	{
	case	SQL_FLOAT:
			value_max = sizeof(double);
			column_type = SQL_C_DOUBLE;
			_param_info.data_SQLDOUBLE = static_cast<double>(_data);
			break;

	case	SQL_REAL:
			value_max = sizeof(float);
			column_type = SQL_C_FLOAT;
			_param_info.data_float = static_cast<float>(_data);
			break;

	case	SQL_DOUBLE:
			value_max = sizeof(double);
			column_type = SQL_C_DOUBLE;
			_param_info.data_SQLDOUBLE = static_cast<double>(_data);
			break;

	case	SQL_VARCHAR: // (12) mysql always SQL_VARCHAR
			_param_info.data_type = SQL_DOUBLE;
			_param_info.param_size = 0;
			_param_info.decimal_digits = 0;
			value_max = sizeof(SQLDOUBLE);
			column_type = SQL_C_DOUBLE;
			_param_info.data_SQLDOUBLE = static_cast<double>(_data);
			break;

	default:
		throw throwable::failure_ex(eRESULT::INVALID_ARGUMENT, 0, std::string_view("(error) invalid parameter type"));
	}

	// 2) bind
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, column_type, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, &_param_info.data, value_max, &_param_info.strLen_or_indptr);
}

template <class TTYPE>
			inline SQLRETURN ODBC_SET_PARAM									(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const TTYPE&						_data)  
			{
				auto data_type = _sql_param<TTYPE>::data_type();

				// check) 
				CGASSERT_ERROR(data_type == _param_info.data_type);

				// 1) set param
				_param_info.strLen_or_indptr = 0;
				_param_info.set_data<typename _sql_param<TTYPE>::type>(_data);
				
				// 2) bind
				return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, _sql_param<TTYPE>::column_type(), _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, _param_info.get_data<typename _sql_param<TTYPE>::type>(), sizeof(TTYPE), &_param_info.strLen_or_indptr);
			}
template <>
			inline SQLRETURN ODBC_SET_PARAM<bool>							(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const bool&						_data)  
			{
				// check) 
				CGASSERT_ERROR(_param_info.data_type == SQL_BIT);

				// check)
				THROW_IF(_param_info.data_type != SQL_BIT, throwable::failure_ex(eRESULT::INVALID_ARGUMENT, 0, std::string_view("(error) invalid parameter type")));

				// 1) set param
				_param_info.strLen_or_indptr = 0;
				_param_info.data_SQLCHAR = static_cast<SQLCHAR>(_data);
				
				// 2) bind
				return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_BIT, SQL_BIT, _param_info.param_size, _param_info.decimal_digits, &_param_info.data, sizeof(SQLCHAR), &_param_info.strLen_or_indptr);
			}
template <>	inline SQLRETURN ODBC_SET_PARAM<int8_t>							(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const int8_t&							_data) { return ODBC_SET_PARAM_signed_integer<int8_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<uint8_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const uint8_t&							_data) { return ODBC_SET_PARAM_unsigned_integer<uint8_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<int16_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const int16_t&							_data) { return ODBC_SET_PARAM_signed_integer<int16_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<uint16_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const uint16_t&							_data) { return ODBC_SET_PARAM_unsigned_integer<uint16_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<int32_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const int32_t&							_data) { return ODBC_SET_PARAM_signed_integer<int32_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<uint32_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const uint32_t&							_data) { return ODBC_SET_PARAM_unsigned_integer<uint32_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<int64_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const int64_t&							_data) { return ODBC_SET_PARAM_signed_integer<int64_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<uint64_t>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const uint64_t&							_data) { return ODBC_SET_PARAM_unsigned_integer<uint64_t>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<float>							(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const float&								_data) { return ODBC_SET_PARAM_float<float>(_handle_stmt, _param_info, _ordinal, _data); }
template <>	inline SQLRETURN ODBC_SET_PARAM<double>							(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const double&							_data) { return ODBC_SET_PARAM_float<double>(_handle_stmt, _param_info, _ordinal, _data); }
template<>	inline SQLRETURN ODBC_SET_PARAM<NUMERIC>						(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const NUMERIC&							_data) { SQL_NUMERIC_STRUCT value = __to_sql_numeric_struct(_data); return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_NUMERIC, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, &value, sizeof(SQL_NUMERIC_STRUCT), &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::string>					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::string&						_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char*>    (_data.c_str()), _data.size() * sizeof(char),      &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::wstring>					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::wstring&						_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_WCHAR, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<wchar_t*> (_data.c_str()), _data.size() * sizeof(wchar_t),   &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u8string>					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u8string&						_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char8_t*> (_data.c_str()), _data.size() * sizeof(char8_t),   &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u16string>					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u16string&					_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_WCHAR, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char16_t*>(_data.c_str()), _data.size() * sizeof(char16_t),  &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u32string>					(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u32string&					_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char32_t*>(_data.c_str()), _data.size() * sizeof(char32_t),  &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::string_view>				(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::string_view&					_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char*>    (_data.data()), _data.length() * sizeof(char),     &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::wstring_view>				(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::wstring_view&					_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_WCHAR, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<wchar_t*> (_data.data()), _data.length() * sizeof(wchar_t),  &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u8string_view>				(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u8string_view&				_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char8_t*> (_data.data()), _data.length() * sizeof(char8_t),  &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u16string_view>			(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u16string_view&				_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_WCHAR, _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char16_t*>(_data.data()), _data.length() * sizeof(char16_t), &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<std::u32string_view>			(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const std::u32string_view&				_data) { return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_CHAR,  _param_info.data_type, _param_info.param_size, _param_info.decimal_digits, const_cast<char32_t*>(_data.data()), _data.length() * sizeof(char32_t), &_param_info.strLen_or_indptr); }
template<>	inline SQLRETURN ODBC_SET_PARAM<chrono::time::time_point>		(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const chrono::time::time_point&			_data) 
{
	_param_info.data_timestamp = __to_sql_TIMESTAMP_struct(_data); 
	_param_info.decimal_digits = 6;
	_param_info.param_size = (static_cast<SQLULEN>(SQL_TIMESTAMP_LEN) + _param_info.decimal_digits + 1);
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TYPE_TIMESTAMP, _param_info.param_size, _param_info.decimal_digits, &_param_info.data_timestamp, sizeof(SQL_TIMESTAMP_STRUCT), &_param_info.strLen_or_indptr);
}
template<>	inline SQLRETURN ODBC_SET_PARAM<chrono::time::utc::time_point>	(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const chrono::time::utc::time_point&		_data) 
{
	_param_info.data_timestamp = __to_sql_TIMESTAMP_struct(_data);
	_param_info.decimal_digits = 6;
	_param_info.param_size = (static_cast<SQLULEN>(SQL_TIMESTAMP_LEN) + _param_info.decimal_digits + 1);
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TYPE_TIMESTAMP, _param_info.param_size, _param_info.decimal_digits, &_param_info.data_timestamp, sizeof(SQL_TIMESTAMP_STRUCT), &_param_info.strLen_or_indptr);
}
template<>	inline SQLRETURN ODBC_SET_PARAM<chrono::time::local::time_point>(SQLHSTMT _handle_stmt, sPARAM& _param_info, std::size_t _ordinal, const chrono::time::local::time_point&	_data) 
{
	_param_info.data_timestamp = __to_sql_TIMESTAMP_struct(_data);
	_param_info.decimal_digits = 6;
	_param_info.param_size = (static_cast<SQLULEN>(SQL_TIMESTAMP_LEN) + _param_info.decimal_digits + 1);
	return SQLBindParameter(_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal), SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TYPE_TIMESTAMP, _param_info.param_size, _param_info.decimal_digits, &_param_info.data_timestamp, sizeof(SQL_TIMESTAMP_STRUCT), &_param_info.strLen_or_indptr);
}


}