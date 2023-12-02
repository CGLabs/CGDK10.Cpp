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