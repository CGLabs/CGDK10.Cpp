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
// query::rdb::oledb::Cquery
//
// 1. query::rdb::oledb::Cquery란!
//    1) Iserver_query와 Command를 상속받아 만든 기본 Query다.
//    2) Querier에 Query를 Post하거나 request하게 되면 session을 할당받게 된다.
//    3) session을 할당받게 되면 Query String을 넘겨 execute_query함수를 호출함으로써
//       Query를 수행할 수 있다.
//    4) 그리고 Query가 완료된 후 close_query를 호출하여 Query를 종료할 수 있다.
//    5) start와 stop은 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//       함수가 종료되면 session도 반납되게 된다.
//
// 2. Accessor의 선택
//    1) 사용할 수 있는 Accessor는 기본적으로 크게 두가지가 있다.
//					
//       - ATL::CAccessor<TACCESSOR>	기본 Accessor로 Query의 설정 및 결과값을 클래스
//										내부 변수에 받도록 미리 정의해 놓도록 한 것이다.
//       - ATL::CDynamicAccessor		Query의 내용 및 결과를 필요에 따라 얻어 쓸수 
//										있도록 한 것으로 간단한 Query에 유용하다.
//
// 3. Rowset의 선택
//    1) Query의 결과 1개가 하나의 Row이다. 이것을 처리하기 위한 것이 RowSet이다.
//       기본적으로 3가지의 RowSet을 사용할 수 있다.
//      
//       - ATL::CNoRowset				Rowset을 사용하지 않는다.
//		 - ATL::CRowset					Rowset을 사용한다.
//		 - ATL::CMultiRowset			여러 개의 Rowset을 가질 수 있도록 한다.
//
// 4. ATL::CMultipleResults의 선택
//	  1) 선택한 결과의 갯수를 선정하는 것이다. 자체적으로 처리되는 내용은 없고
//		 다만 선택을 위한 Class로 선택사항은 아래와 같다.
//
//		 - ATL::CNoMultipleResults		여러 개의 결과물을 받지 않는다.
//		 - ATL::CMultipleResults		여러 개의 결과물을 받는다.
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR = ATL::CDynamicAccessor, template <class T> class TROWSET = ATL::CRowset, class TMULTIPLE = ATL::CMultipleResults>
class query::rdb::oledb::Cquery : public _query<TACCESSOR, TROWSET, TMULTIPLE>
{
public:
			typedef	Cquery<TACCESSOR, TROWSET, TMULTIPLE>										TSELF;
			typedef typename _query<TACCESSOR, TROWSET, TMULTIPLE>::template ITERATOR<TSELF>	TITERATOR;

	[[nodiscard]] TITERATOR		begin() { return TITERATOR(this, (this->m_spRowset != nullptr) ? this->move_first() : result_code(E_FAIL)); }
	[[nodiscard]] TITERATOR		end() { return TITERATOR(nullptr, eRESULT::SUCCESS); }
};

template<template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::Cquery<ATL::CDynamicAccessor, TROWSET, TMULTIPLE> : public _query_dynamic<ATL::CDynamicAccessor, TROWSET, TMULTIPLE>
{
public:
			typedef	Cquery<ATL::CDynamicAccessor,TROWSET,TMULTIPLE>												 TSELF;
			typedef typename _query_dynamic<ATL::CDynamicAccessor, TROWSET, TMULTIPLE>::template ITERATOR<TSELF> TITERATOR;

	[[nodiscard]] TITERATOR		begin() { return TITERATOR(this, (this->m_spRowset != nullptr) ? this->move_first() : result_code(E_FAIL)); }
	[[nodiscard]] TITERATOR		end() { return TITERATOR(nullptr, eRESULT::SUCCESS); }
};

template<template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::Cquery<ATL::CDynamicParameterAccessor, TROWSET, TMULTIPLE> : public _query_dynamic_parameter<ATL::CDynamicParameterAccessor, TROWSET, TMULTIPLE>
{
public:
			typedef	Cquery<ATL::CDynamicParameterAccessor, TROWSET, TMULTIPLE>														TSELF;
			typedef typename _query_dynamic_parameter<ATL::CDynamicParameterAccessor, TROWSET, TMULTIPLE>::template ITERATOR<TSELF>	TITERATOR;

	[[nodiscard]] TITERATOR		begin() { return TITERATOR(this, (this->m_spRowset != nullptr) ? this->move_first() : result_code(E_FAIL)); }
	[[nodiscard]] TITERATOR		end() { return TITERATOR(nullptr, eRESULT::SUCCESS); }
};


}