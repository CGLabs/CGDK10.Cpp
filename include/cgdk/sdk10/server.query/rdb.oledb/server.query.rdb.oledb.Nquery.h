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
// query::rdb::oledb::Nquery
//
// 1. query::rdb::oledb::Nquery��!
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
//		 - ATL::CNoMultipleResults		�Ѳ����� ���� ���� ������� ���� �ʴ´�.
//		 - ATL::CMultipleResults		�Ѳ����� ���� ���� ������� �޴´�.
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR=ATL::CDynamicAccessor, template <class T> class TROWSET = CRowset, class TMULTIPLE = CMultipleResults>
class query::rdb::oledb::Nquery :
// inherited classes)
	public						CCommand<TACCESSOR, TROWSET, TMULTIPLE>,
	virtual public				query::rdb::oledb::Iquery
{
// public) 
public:
	// 1) query
	[[nodiscard]] virtual std::wstring_view get_query_string() const noexcept PURE;
	virtual void				set_query_string(const wstring_param _command) PURE;

			void				execute_query(const wstring_param _command);

	// 2) qUery open/close
	virtual	void				close_query() noexcept;

	// 3) get next result
			result_code			get_next_result() noexcept { return static_cast<eRESULT>(this->GetNextResult(reinterpret_cast<DBROWCOUNT*>(&m_row_affected)));}

	// 4) move first/move next
			result_code			move_first() { return static_cast<eRESULT>(this->MoveFirst()); }
			result_code			move_next() { return static_cast<eRESULT>(this->MoveNext()); }

// framework) 
protected:
	virtual void				on_final_release() noexcept override { this->close_query(); query::rdb::oledb::Iquery::on_final_release(); }

// implementations) 
protected:
	virtual	void				process_reset_session() noexcept override;
			void				_execute_query(std::wstring_view _command);
};

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::Nquery<TACCESSOR, TROWSET, TMULTIPLE>::process_reset_session() noexcept
{
	scoped_lock(this->m_lockable_state_query)
	{
		// 1) close query first
		this->close_query();

		// 2) and then call parent's PrcessresetSession()
		query::rdb::oledb::Iquery::process_reset_session();
	}
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::Nquery<TACCESSOR, TROWSET, TMULTIPLE>::close_query() noexcept
{
	scoped_lock(this->m_lockable_state_query)
	{
		// check) 
		RETURN_IF(this->m_state_query != eOBJECT_STATE::PROCESSED && this->m_state_query != eOBJECT_STATE::REQUESTING);

		// 3) set state
		this->m_state_query = eOBJECT_STATE::READY;

		// 1) release command
		this->ReleaseCommand();

		// 2) close query command
		this->Close();

		// 3) close result
		__if_exists(TMULTIPLE::GetMultiplePtr)
		{
			if (this->GetMultiplePtr() != NULL)
			{
				this->GetMultiplePtr()->Release();
				*this->GetMultiplePtrAddress() = NULL;
			}
		}
	}
}

template<class TACCESSOR, template <typename T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::Nquery<TACCESSOR, TROWSET, TMULTIPLE>::execute_query(const wstring_param _command)
{
	// 1) set query string
	set_query_string(_command);

	// 2) execute query
	this->_execute_query(get_query_string());
}


template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::Nquery<TACCESSOR, TROWSET, TMULTIPLE>::_execute_query(std::wstring_view _command)
{
	// 1) Property set
	CDBPropSet propset(DBPROPSET_ROWSET);

	// 2) PropSet
	__if_exists(TACCESSOR::GetRowsetProperties)
	{
		__if_exists(HasBookmark)
		{
			if( HasBookmark() )
				propset.AddProperty(DBPROP_IRowsetLocate, true);
		}
		__if_exists(TACCESSOR::DataClass)
		{
			this->GetRowsetProperties(&propset);
		}
	}
	__if_not_exists(TACCESSOR::GetRowsetProperties)
	{
		__if_exists(HasBookmark)
		{
			if( HasBookmark() )
			{
				propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
		}
	}

	scoped_lock(m_lockable_state_query)
	{
		// check) m_psession must not be nullptr
		CGASSERT_ERROR(this->m_psession.exist());

		// check) throw exception if m_psession is nullptr
		THROW_IF(this->m_psession.empty(), throwable::failure(eRESULT::INVALID_ARGUMENT, 0, std::string_view("parameter['m_psession'] is nullptr")));

		// declare) 
		auto pquerier = this->m_psession->m_pquerier;

		// check) pquerier must not be nullptr
		CGASSERT_ERROR(pquerier != nullptr);

		// check) throw exception if pquerier is nullptr
		THROW_IF(pquerier == nullptr, throwable::failure(eRESULT::NOT_READY));

		// check) m_psession->m_spOpenRowset must not be nullptr
		THROW_IF(this->m_psession->m_spOpenRowset == nullptr, throwable::failure(eRESULT::NOT_READY));

		// check) m_state_query must be eOBJECT_STATE::READY
		CGASSERT_ERROR(this->m_state_query == eOBJECT_STATE::READY);

		// check) m_state_query must be eOBJECT_STATE::READY
		THROW_IF(this->m_state_query != eOBJECT_STATE::READY, throwable::failure(eRESULT::NOT_READY));

		// statistics) 
		pquerier->statistics_on_query_try();

		// 1) open session
		auto result = this->Open(*this->m_psession, _command.data(), &propset, reinterpret_cast<DBROWCOUNT*>(&this->m_row_affected), DBGUID_DEFAULT, true, 0);

		if (FAILED(result))
		{
			// declare) 
			auto e = trace_error_records(this, result, _command);
			auto result_last = result;
			size_t retry = 0;

			do
			{
				// - get max retry count
				auto max_retry = this->m_psession->m_pquerier->get_max_retry_on_fail();
				
				// check) retry count out or error is not 0x80040005
				if (retry >= max_retry || (result & 0x00000000ffffffff) != 0x0000000080004005)
				{
					// - add result
					if (retry > 1)
					{
						e.add_description(NFMT::format("       * total {} tries and failed", retry));
					}

					// statistics) 
					pquerier->statistics_on_query_fail();

					// raise)
					throw e;
				}

				// - add oledb error records
				if (result_last != result)
				{
					// - add result
					e.add_description(NFMT::format("       * result: {}", result));

					// - get oledb new result
					query::rdb::oledb::_dump_error_records(e);

					// - update last result
					result_last = result;
				}

				// statistics) 
				pquerier->statistics_on_query_retry();

				// - decrease retry count
				++retry;

				// - regen session
				regen_session(this->m_psession, result);

				// check) m_psession->m_spOpenRowset must not be nullptr
				CONTINUE_IF(this->m_psession->m_spOpenRowset == nullptr);

				// - retry query
				result = this->Open(*this->m_psession, _command.data(), &propset, reinterpret_cast<DBROWCOUNT*>(&this->m_row_affected), DBGUID_DEFAULT, true, 0);

			} while (result != S_OK);
		}

		// 3) set state
		this->m_state_query = eOBJECT_STATE::PROCESSED;

		// statistics) 
		pquerier->statistics_on_query_success();
	}
}


}
