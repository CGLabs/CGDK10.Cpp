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
// 4. CMultipleResults의 선택
//	  1) 선택한 결과의 갯수를 선정하는 것이다. 자체적으로 처리되는 내용은 없고
//		 다만 선택을 위한 Class로 선택사항은 아래와 같다.
//
//		 - ATL::CNoMultipleResults		한꺼번에 여러 개의 결과물을 받지 않는다.
//		 - ATL::CMultipleResults		한꺼번에 여러 개의 결과물을 받는다.
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::_query :
	// inherited classes)
	public						Nquery <TACCESSOR,TROWSET,TMULTIPLE>
{
// public) 
public:
	// 4) For DefaultCommand
	__if_exists(GetDefaultCommand)
	{
	[[nodiscard]] virtual std::wstring_view get_query_string() const noexcept override { wchar_t* temp; GetDefaultCommand((LPCWSTR*)&temp); return temp; }
	virtual	void				set_query_string(const wstring_param /*_command*/) override { CGASSERT_ERROR(false); throw throwable::failure (eRESULT::FAIL); }

	}																	 
	__if_not_exists(GetDefaultCommand)									 
	{																	 
	[[nodiscard]] virtual std::string_view get_query_string() const noexcept override { return m_query_string;}
	virtual void				set_query_string(const std::string_view _command) override { m_query_string = _command;}
	virtual	void				close_query() noexcept { Nquery<TACCESSOR, TROWSET, TMULTIPLE>::close_query(); m_query_string.clear(); }

			std::string			m_query_string;
	}																	 
																		 
	virtual	void				process_execute_query() override { this->execute_query(get_query_string()); }
};


}