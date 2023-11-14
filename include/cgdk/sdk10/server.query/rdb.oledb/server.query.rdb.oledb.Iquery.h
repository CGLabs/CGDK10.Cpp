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
//    5) open과 Close는 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//       함수가 종료되면 session도 반납되게 된다.
//
// 2. Accessor의 선택
//    1) 사용할 수 closecessor는 기본적으로 크게 두가지가 있다.
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
//		 - ATL::CNoMultipleResults		한꺼번에 여러 개의 결과물을 받지 않는다.
//		 - ATL::CMultipleResults		한꺼번에 여러 개의 결과물을 받는다.
//
// 5. Datatype Mapping
//
//    SQL				OLE-DB definition			C++ 
//   -------------------------------
//						DBTYPE_EMPTY
//						DBTYPE_NULL
//						DBTYPE_DATE					DBDATE
//						DBTYPE_UI2					unsigned short
//						DBTYPE_UI4					unsigned char
//						DBTYPE_UI8					unsigned char
//						DBTYPE_HRESULT
//						DBTYPE_LPSTR
//						DBTYPE_LPWSTR
//						DBTYPE_FILETIME
//						DBTYPE_BLOB					BLOB
//						DBTYPE_UUID
//						DBTYPE_DBEXPR
//						DBTYPE_COLUMNID				DBCOLUMNID
//						DBTYPE_CHARS
//						DBTYPE_WCHARS
//						DBTYPE_ANYVARIANT			DBVARIANT
//
//    bigint			DBTYPE_I8					LARGE_INTEGER
//    binary			DBTYPE_BYTES								BLOB
//    bit				DBTYPE_BOOL					VARIANT_BOOL
//    char				DBTYPE_STR									BSTR
//    datetime			DBTYPE_DBTIMESTAMP			DBTIM
//    datetime2			DBTYPE_DBTIME2				DBTIME2
//    decimal			DBTYPE_NUMERIC				DB_NUMERIC
//    float				DBTYPE_R8					double
//    image				DBTYPE_BYTES								BLOB
//    int				DBTYPE_I4					LONG
//    money				DBTYPE_CY					LARGE_INTEGER
//    nchar				DBTYPE_WSTR
//    ntext				DBTYPE_WSTR
//    numeric			DBTYPE_NUMERIC
//    nvarchar			DBTYPE_WSTR
//    real				DBTYPE_R4					float
//    smalldatetime		DBTYPE_DBTIMESTAMP			DBTIMESTAMP
//    smallint			DBTYPE_I2					SHORT
//    smallmoney		DBTYPE_CY					CY
//    sql_variant		DBTYPE_VARIANT				DBVARIANT
//						DBTYPE_SQLVARIANT
//    sysname			DBTYPE_WSTR					LPWSTR
//    text				DBTYPE_STR								BSTR
//    timestamp			DBTYPE_BYTES
//    tinyint			DBTYPE_UI1					BYTE
//    UDT				DBTYPE_UDT
//    uniqueidentifier	DBTYPE_GUID					GUID
//    varbinary			DBTYPE_BYTES							BLOB
//    varchar			DBTYPE_STR								BSTR
//    XML				DBTYPE_XML
//						DBTYPE_DBTIMESTAMPOFSET		DBTIMESTAMPOFSET
// 
//-----------------------------------------------------------------------------
class query::rdb::oledb::Iquery :
	virtual public				Iserver_query
{
public:
	typedef	Iquery				IQUERY;
	typedef	querier				QUERIER;

public:
	[[nodiscard]] object_ptr<session>	get_session() const noexcept { return this->m_psession;}
			void				set_session(session* _psession) { this->process_set_session(_psession);}
			void				reset_session() noexcept { this->process_reset_session();}

	[[nodiscard]] uint64_t		get_affected_row() const noexcept { return this->m_row_affected;}

			template <class TLOCK>
			void				wait(TLOCK& _cs) { this->m_cv_complete.wait(_cs); }
			void				wait() { std::unique_lock<std::recursive_mutex> cs(this->m_lockable_wait); this->m_cv_complete.wait(cs); }

public:
			void				process_set_session(session* _psession);
	virtual	void				process_reset_session() noexcept override;

public:
			object_ptr<session>	m_psession;
			uint64_t			m_row_affected = 0;

			std::condition_variable_any m_cv_complete;
			std::recursive_mutex m_lockable_wait;

			std::recursive_mutex m_lockable_state_query;

	virtual	void				on_final_release() noexcept override { this->reset_session(); this->m_prequestor.reset();}

			void				_process_notify_to_requestor() noexcept;
			void				_process_regenerate_session();
};


}