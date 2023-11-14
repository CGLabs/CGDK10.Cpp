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
// 1. query::rdb::oledb::Cquery��!
//    1) Iserver_query�� Command�� ��ӹ޾� ���� �⺻ Query��.
//    2) Querier�� Query�� Post�ϰų� request�ϰ� �Ǹ� session�� �Ҵ�ް� �ȴ�.
//    3) session�� �Ҵ�ް� �Ǹ� Query String�� �Ѱ� execute_query�Լ��� ȣ�������ν�
//       Query�� ������ �� �ִ�.
//    4) �׸��� Query�� �Ϸ�� �� close_query�� ȣ���Ͽ� Query�� ������ �� �ִ�.
//    5) start�� stop�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
//       �Լ��� ����Ǹ� session�� �ݳ��ǰ� �ȴ�.
//
// 2. Accessor�� ����
//    1) ����� �� �ִ� Accessor�� �⺻������ ũ�� �ΰ����� �ִ�.
//					
//       - ATL::CAccessor<TACCESSOR>	�⺻ Accessor�� Query�� ���� �� ������� Ŭ����
//										���� ������ �޵��� �̸� ������ ������ �� ���̴�.
//       - ATL::CDynamicAccessor		Query�� ���� �� ����� �ʿ信 ���� ��� ���� 
//										�ֵ��� �� ������ ������ Query�� �����ϴ�.
//
// 3. Rowset�� ����
//    1) Query�� ��� 1���� �ϳ��� Row�̴�. �̰��� ó���ϱ� ���� ���� RowSet�̴�.
//       �⺻������ 3������ RowSet�� ����� �� �ִ�.
//      
//       - ATL::CNoRowset				Rowset�� ������� �ʴ´�.
//		 - ATL::CRowset					Rowset�� ����Ѵ�.
//		 - ATL::CMultiRowset			���� ���� Rowset�� ���� �� �ֵ��� �Ѵ�.
//
// 4. ATL::CMultipleResults�� ����
//	  1) ������ ����� ������ �����ϴ� ���̴�. ��ü������ ó���Ǵ� ������ ����
//		 �ٸ� ������ ���� Class�� ���û����� �Ʒ��� ����.
//
//		 - ATL::CNoMultipleResults		���� ���� ������� ���� �ʴ´�.
//		 - ATL::CMultipleResults		���� ���� ������� �޴´�.
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