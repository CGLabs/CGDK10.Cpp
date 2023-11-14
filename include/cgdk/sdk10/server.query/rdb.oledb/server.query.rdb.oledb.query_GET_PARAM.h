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
//  1) Iserver_query와 Command를 상속받아 만든 기본 Query다.
//  2) Querier에 Query를 Post하거나 request하게 되면 session을 할당받게 된다.
//  3) session을 할당받게 되면 Query String을 넘겨 execute_query함수를 호출함으로써
//     Query를 수행할 수 있다.
//  4) 그리고 Query가 완료된 후 close_query를 호출하여 Query를 종료할 수 있다.
//  5) start와 stop은 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//     함수가 종료되면 session도 반납되게 된다.
//
// 
//-----------------------------------------------------------------------------
	template <class TTYPE>
	[[nodiscard]] inline TTYPE										OLEDB_GET_PARAM(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return TTYPE(); }
	template<> [[nodiscard]] inline NUMERIC							OLEDB_GET_PARAM<NUMERIC>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return NUMERIC(); }
	template<> [[nodiscard]] inline std::string						OLEDB_GET_PARAM<std::string>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::string(); }
	template<> [[nodiscard]] inline std::wstring					OLEDB_GET_PARAM<std::wstring>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::wstring(); }
	template<> [[nodiscard]] inline std::u8string					OLEDB_GET_PARAM<std::u8string>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u8string(); }
	template<> [[nodiscard]] inline std::u16string					OLEDB_GET_PARAM<std::u16string>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u16string(); }
	template<> [[nodiscard]] inline std::u32string					OLEDB_GET_PARAM<std::u32string>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return std::u32string(); }
	template<> [[nodiscard]] inline chrono::time::time_point		OLEDB_GET_PARAM<chrono::time::time_point>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::time_point(); }
	template<> [[nodiscard]] inline chrono::time::utc::time_point	OLEDB_GET_PARAM<chrono::time::utc::time_point>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::utc::time_point(); }
	template<> [[nodiscard]] inline chrono::time::local::time_point	OLEDB_GET_PARAM<chrono::time::local::time_point>(SQLHSTMT /*_handle_stmt*/, SQLUSMALLINT /*_ordinal*/) noexcept { return chrono::time::local::time_point(); }
}