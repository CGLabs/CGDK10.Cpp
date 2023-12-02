//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
//
//  Query Classes
//
//
//----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ...
// ----------------------------------------------------------------------------
// 1) float type
template<class T>	class is_float_type : public std::false_type {};
template<>			class is_float_type<float> : public std::true_type {};
template<>			class is_float_type<double> : public std::true_type {};

// 2) integer type
template<class T>	class is_integer_type : public std::false_type {};
template<>			class is_integer_type<int8_t> : public std::true_type {};
template<>			class is_integer_type<uint8_t> : public std::true_type {};
template<>			class is_integer_type<int16_t> : public std::true_type {};
template<>			class is_integer_type<uint16_t> : public std::true_type {};
template<>			class is_integer_type<int32_t> : public std::true_type {};
template<>			class is_integer_type<uint32_t> : public std::true_type {};
template<>			class is_integer_type<int64_t> : public std::true_type {};
template<>			class is_integer_type<uint64_t> : public std::true_type {};

inline bool QUERY_SUCCESSED(result_code _result)
{
	return _result == result_code(eRESULT::SUCCESS);
}

inline bool QUERY_FAILED(result_code _result)
{
	return !QUERY_SUCCESSED(_result);
}


// ----------------------------------------------------------------------------
// DB driver
// ----------------------------------------------------------------------------
enum class eDB_PROVIDER : uint32_t
{
	NONE				 = 0x00000000,
	DSN					 = 0x00000001,	// {DSN}
	SQL_SERVER			 = 0x00000101,	// {SQL Server}
	SQL_SERVER_18		 = 0x00000102,	// {SQL Server 18}
	SQL_SERVER_NATIVE	 = 0x00000103,	// {SQL Server}
	SQL_SERVER_ODBC		 = 0x00000104,	// {ODBC Driver 17 for SQL Server}
	MYSQL				 = 0x00000201,	// {MySQL ODBC Driver}
	MYSQL_ANSI			 = 0x00000202,	// {MySQL ODBC Driver}
	MYSQL_UNICODE		 = 0x00000203,	// {MySQL ODBC Driver}
	MYSQL_3_5			 = 0x00000204,	// {MySQL ODBC 3.5 Driver}
	MYSQL_5_1			 = 0x00000205,	// {MySQL ODBC 5.1 Driver}
	MYSQL_5_1_ANSI		 = 0x00000206,	// {MySQL ODBC 5.1 ANSI Driver}
	MYSQL_5_1_UNICODE	 = 0x00000207,	// {MySQL ODBC 5.1 UNICODE Driver}
	MYSQL_5_2			 = 0x00000208,	// {MySQL ODBC 5.2 Driver}
	MYSQL_5_2_ANSI		 = 0x00000209,	// {MySQL ODBC 5.2 ANSI Driver}
	MYSQL_5_2_UNICODE	 = 0x0000020a,	// {MySQL ODBC 5.2 ANSI Driver}
	MYSQL_5_3			 = 0x0000020b,	// {MySQL ODBC 5.3 Driver}
	MYSQL_5_3_ANSI		 = 0x0000020c,	// {MySQL ODBC 5.3 ANSI Driver}
	MYSQL_5_3_UNICODE	 = 0x0000020d,	// {MySQL ODBC 5.3 Unicode Driver}
	MYSQL_8				 = 0x0000020e,	// {MySQL ODBC 8.0 Driver}
	MYSQL_8_ANSI		 = 0x0000020f,	// {MySQL ODBC 8.0 ANSI Driver}
	MYSQL_8_UNICODE		 = 0x00000210,	// {MySQL ODBC 8.0 Unicode Driver}
	MARIADB				 = 0x00000301,	// {MariaDB ODBC Driver}
	MARIADB_3_1			 = 0x00000302,	// {MariaDB ODBC 3.01 Driver}
	EXCEL				 = 0x00000401,	// {Microsoft Excel Driver}
	ACCESS				 = 0x00000402,	// {Microsoft Access Text Driver}
	ACCESS_DBASE		 = 0x00000403,	// {Microsoft Access dBASE Text Driver}
	ACCESS_TEXT			 = 0x00000404,	// {Microsoft Access Text Driver}
	MASK_				 = 0x00ffffff,	// 

	CREATE_				 = 0x01000000,	// create
	MASK_OPTION_		 = 0x0f000000,	// 

	EXCEL_CREATE_		 = EXCEL | CREATE_,
};
CGDEFINE_ENUM_FLAG_OPERATORS_UINT32(eDB_PROVIDER);

}

