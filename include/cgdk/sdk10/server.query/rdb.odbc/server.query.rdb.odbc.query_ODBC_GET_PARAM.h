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
template <class TTYPE>
			[[nodiscard]] inline TTYPE								ODBC_GET_PARAM									(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return TTYPE(); }
template<>	[[nodiscard]] inline NUMERIC							ODBC_GET_PARAM<NUMERIC>							(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return NUMERIC(); }
template<>	[[nodiscard]] inline std::string						ODBC_GET_PARAM<std::string>						(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::string(); }
template<>	[[nodiscard]] inline std::wstring						ODBC_GET_PARAM<std::wstring>					(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::wstring(); }
template<>	[[nodiscard]] inline std::u8string						ODBC_GET_PARAM<std::u8string>					(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u8string(); }
template<>	[[nodiscard]] inline std::u16string						ODBC_GET_PARAM<std::u16string>					(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u16string(); }
template<>	[[nodiscard]] inline std::u32string						ODBC_GET_PARAM<std::u32string>					(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u32string(); }
template<>	[[nodiscard]] inline chrono::time::time_point			ODBC_GET_PARAM<chrono::time::time_point>		(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::time_point(); }
template<>	[[nodiscard]] inline chrono::time::utc::time_point		ODBC_GET_PARAM<chrono::time::utc::time_point>	(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::utc::time_point(); }
template<>	[[nodiscard]] inline chrono::time::local::time_point	ODBC_GET_PARAM<chrono::time::local::time_point>	(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::local::time_point(); }


}