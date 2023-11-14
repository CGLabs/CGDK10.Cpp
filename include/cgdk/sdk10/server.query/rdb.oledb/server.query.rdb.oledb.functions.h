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
//----------------------------------------------------------------------------
//
//
//  Query oledb Classes
//
//
//----------------------------------------------------------------------------
namespace query
{
namespace rdb
{
namespace oledb
{

throwable::failure_ex trace_error_records(query::rdb::oledb::Iquery* _pquery, HRESULT _result, const wstring_param _query_string) noexcept;
void regen_session(query::rdb::oledb::session* _psession, HRESULT _result);

}
}
}

}