//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query oledb Classes                         *
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
// query::rdb::odbc::OLEDB_GET_PARAM
//
//  1) Iserver_query�� Command�� ��ӹ޾� ���� �⺻ Query��.
//  2) Querier�� Query�� Post�ϰų� request�ϰ� �Ǹ� session�� �Ҵ�ް� �ȴ�.
//  3) session�� �Ҵ�ް� �Ǹ� Query String�� �Ѱ� execute_query�Լ��� ȣ�������ν�
//     Query�� ������ �� �ִ�.
//  4) �׸��� Query�� �Ϸ�� �� close_query�� ȣ���Ͽ� Query�� ������ �� �ִ�.
//  5) start�� stop�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
//     �Լ��� ����Ǹ� session�� �ݳ��ǰ� �ȴ�.
//
// 
//-----------------------------------------------------------------------------
template <class TTYPE>
			inline bool						OLEDB_SET_PARAM										(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const TTYPE&					   _data) noexcept	{ /*SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, _get_sql_column_type<TTYPE>(), _get_sql_data_type<TTYPE>(), _column_size, 0, const_cast<TTYPE*>(&_data), sizeof(TTYPE), &_out_len); return SQL_SUCCEEDED(result);*/ return false; }
//template<>	inline bool						OLEDB_SET_PARAM<NUMERIC>							(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const NUMERIC&				   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; SQL_NUMERIC_STRUCT value=__to_sql_numeric_struct(_data); auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_NUMERIC, SQL_NUMERIC, _column_size, 0, &value, sizeof(SQL_NUMERIC_STRUCT), &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::string>						(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::string&			   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char*>    (_data.c_str()), _data.size() * sizeof(char),      &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::wstring>						(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::wstring&			   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WCHAR, _column_size, 0, const_cast<wchar_t*> (_data.c_str()), _data.size() * sizeof(wchar_t),   &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u8string>						(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u8string&			   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char8_t*> (_data.c_str()), _data.size() * sizeof(char8_t),   &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u16string>						(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u16string&		   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char16_t*>(_data.c_str()), _data.size() * sizeof(char16_t),  &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u32string>						(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u32string&		   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char32_t*>(_data.c_str()), _data.size() * sizeof(char32_t),  &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::string_view>					(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::string_view&		   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char*>    (_data.data()), _data.length() * sizeof(char),     &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::wstring_view>					(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::wstring_view&		   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WCHAR, _column_size, 0, const_cast<wchar_t*> (_data.data()), _data.length() * sizeof(wchar_t),  &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u8string_view>					(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u8string_view&	   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char8_t*> (_data.data()), _data.length() * sizeof(char8_t),  &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u16string_view>				(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u16string_view&	   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char16_t*>(_data.data()), _data.length() * sizeof(char16_t), &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<std::u32string_view>				(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const std::u32string_view&	   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,  _column_size, 0, const_cast<char32_t*>(_data.data()), _data.length() * sizeof(char32_t), &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<chrono::time::time_point>			(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const time::time_point&		   _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; SQL_TIMESTAMP_STRUCT value=__to_sql_TIMESTAMP_struct(_data); auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TIMESTAMP, _column_size, 0, &value, sizeof(SQL_TIMESTAMP_STRUCT), &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<chrono::time::utc::time_point>		(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const time::utc::time_point& _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; SQL_TIMESTAMP_STRUCT value=__to_sql_TIMESTAMP_struct(_data); auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TIMESTAMP, _column_size, 0, &value, sizeof(SQL_TIMESTAMP_STRUCT), &_out_len); return SQL_SUCCEEDED(result); }
//template<>	inline bool						OLEDB_SET_PARAM<chrono::time::local::time_point>	(SQLHSTMT _handle_stmt, SQLUSMALLINT _ordinal, const time::local::time_point&  _data) noexcept	{ SQLLEN _out_len = 0; SQLULEN _column_size = 0; SQL_TIMESTAMP_STRUCT value=__to_sql_TIMESTAMP_struct(_data); auto result = SQLBindParameter(_handle_stmt, _ordinal, SQL_PARAM_INPUT, SQL_C_TIMESTAMP, SQL_TIMESTAMP, _column_size, 0, &value, sizeof(SQL_TIMESTAMP_STRUCT), &_out_len); return SQL_SUCCEEDED(result); }


}