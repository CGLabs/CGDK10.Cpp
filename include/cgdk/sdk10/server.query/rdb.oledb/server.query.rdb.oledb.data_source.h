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
// query::rdb::oledb::data_source
//
// 1. query::rdb::oledb::data_source란!
//    1) session과 CDataSource를 묶어 놓은 CDataSource을 상속받은 Class이다.
//    2) CDataSource에 IReferenceCount만 추가한 것이다.
//
//
//-----------------------------------------------------------------------------
class query::rdb::oledb::data_source :
// inherited classes)
	public						ATL::CDataSource,
	virtual public				Ireferenceable
{
public:
			void				open(const wstring_param _str_initialization) { auto result = ATL::CDataSource::OpenFromInitializationString(_str_initialization.data()); THROW_IF(FAILED(result), _dump_error_records(result, _str_initialization)); }
};


}