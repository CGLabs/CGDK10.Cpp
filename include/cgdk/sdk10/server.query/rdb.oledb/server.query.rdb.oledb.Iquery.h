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
//    5) open�� Close�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
//       �Լ��� ����Ǹ� session�� �ݳ��ǰ� �ȴ�.
//
// 2. Accessor�� ����
//    1) ����� �� closecessor�� �⺻������ ũ�� �ΰ����� �ִ�.
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
//		 - ATL::CNoMultipleResults		�Ѳ����� ���� ���� ������� ���� �ʴ´�.
//		 - ATL::CMultipleResults		�Ѳ����� ���� ���� ������� �޴´�.
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