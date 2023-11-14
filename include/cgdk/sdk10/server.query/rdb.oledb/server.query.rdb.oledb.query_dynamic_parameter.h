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
// query::rdb::oledb::_query_dynamic_parameter
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::_query_dynamic_parameter :
// inherited classes)
	public						_query_dynamic<TACCESSOR, TROWSET, TMULTIPLE>
{
// contructor) 
public:
			_query_dynamic_parameter() : m_bprepared(false)  {}

// public) 
public:
	// 1) create command and set the command text
			void				prepare_query(wstring_param _command, REFGUID _guid_command = DBGUID_DEFAULT);
			void				execute_query();
			template <class TFIRST, class... TARGS>
			void				execute_query(const wstring_param _command, TFIRST&& _first, TARGS&&... _args);

	// 2) close query
	virtual	void				close_query() noexcept override;

	// 3) parameter
			// - set_param
			typedef	char*		CHAR_PTR;
			typedef	wchar_t*	WCHAR_PTR;

			template<class TTYPE>
			void							set_param(int _ordinal, const TTYPE& _data, DBSTATUS _status = DBSTATUS_S_OK) 
			{
				auto result = this->SetParam(_ordinal, &_data, _status);
				THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']"));
			}
			template<>
			void							set_param<CHAR_PTR>(int _ordinal, const CHAR_PTR& _string, DBSTATUS _status) { auto result = this->SetParamString(_ordinal, _string, _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }
			template<>
			void							set_param<WCHAR_PTR>(int _ordinal, const WCHAR_PTR& _string, DBSTATUS _status) { auto result = this->SetParamString(_ordinal, _string, _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }
			template<>
			void							set_param<std::string_view>(int _ordinal, const std::string_view& _string, DBSTATUS _status) { auto result = this->SetParamString(_ordinal, _string.data(), _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }
			template<>
			void							set_param<std::wstring_view>(int _ordinal, const std::wstring_view& _string, DBSTATUS _status) { auto result = this->SetParamString(_ordinal, _string.data(), _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }
			template<>
			void							set_param<chrono::time::time_point>(int _ordinal, const chrono::time::time_point& _data, DBSTATUS _status) { DBTIMESTAMP timestamp(_data); auto result = this->SetParam(_ordinal, &timestamp, _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }
			template<>
			void							set_param<chrono::time::local::time_point>(int _ordinal, const chrono::time::local::time_point& _data, DBSTATUS _status) { DBTIMESTAMP timestamp(_data); auto result = this->SetParam(_ordinal, &timestamp, _status); THROW_IF(result == false, trace_error_records(this, result, L"[fail 'set_param']")); }

			// - get_param
			template<class TTYPE>
	[[nodiscard]] TTYPE						get_param(std::size_t _ordinal) { return *(TTYPE*)this->GetParam(_ordinal);}
			template<class TTYPE>
	[[nodiscard]] TTYPE						get_param(const std::string_view _column_name) { return *(TTYPE*)this->GetParam(_column_name.data());}

			template<>
	[[nodiscard]] std::string_view			get_param<std::string_view>(std::size_t _ordinal) { return std::string_view((char*)this->GetParam(_ordinal));}
			template<>
	[[nodiscard]] std::string_view			get_param<std::string_view>(const std::string_view _column_name) { return std::string_view((char*)this->GetParam(_column_name.data()));}

			template<>
	[[nodiscard]] std::wstring_view			get_param<std::wstring_view>(std::size_t _ordinal) { return std::wstring_view((wchar_t*)this->GetParam(_ordinal));}
			template<>
	[[nodiscard]] std::wstring_view			get_param<std::wstring_view>(const std::string_view _column_name) { return std::wstring_view((wchar_t*)this->GetParam(_column_name.data()));}

			template<>
	[[nodiscard]] chrono::time::time_point	get_param<chrono::time::time_point>(std::size_t _ordinal) { return static_cast<chrono::time::time_point>(*(DBTIMESTAMP*)this->GetParam(_ordinal)); }
			template<>
	[[nodiscard]] chrono::time::time_point	get_param<chrono::time::time_point>(const std::string_view _column_name) { return static_cast<chrono::time::time_point>(*(DBTIMESTAMP*)this->GetParam(_column_name.data())); }

			template<>
	[[nodiscard]] chrono::time::utc::time_point	get_param<chrono::time::utc::time_point>(std::size_t _ordinal) { return static_cast<chrono::time::utc::time_point>(*(DBTIMESTAMP*)this->GetParam(_ordinal)); }
			template<>
	[[nodiscard]] chrono::time::utc::time_point	get_param<chrono::time::utc::time_point>(const std::string_view _column_name) { return static_cast<chrono::time::utc::time_point>(*(DBTIMESTAMP*)this->GetParam(_column_name.data())); }

			template<>
	[[nodiscard]] chrono::time::local::time_point get_param<chrono::time::local::time_point>(std::size_t _ordinal) { return static_cast<chrono::time::local::time_point>(*(DBTIMESTAMP*)this->GetParam(_ordinal)); }
			template<>
	[[nodiscard]] chrono::time::local::time_point get_param<chrono::time::local::time_point>(const std::string_view _column_name) { return static_cast<chrono::time::local::time_point>(*(DBTIMESTAMP*)this->GetParam(_column_name.data())); }

			template<class TTYPE>																											  
	[[nodiscard]] std::basic_string_view<TTYPE>	get_param_string(int _ordinal) { CGASSERT_ERROR(false);}
			template<>																														  
	[[nodiscard]] std::string_view			get_param_string<char>(int _ordinal) { return (char*)this->GetParam(_ordinal);}
			template<>																														
	[[nodiscard]] std::wstring_view			get_param_string<wchar_t>(int _ordinal) { return (wchar_t*)this->GetParam(_ordinal);}

protected:
			HRESULT				_prepare_query(wstring_param _command, REFGUID _guid_command);
			bool				m_bprepared;

};

template <int INDEX = 1, class TQUERY, class T>
inline void query_recursive_set_param(TQUERY* _pquery, const T& _last)
{
	_pquery->set_param<T>(INDEX, _last);
}

template <int INDEX = 1, class TQUERY, class TFIRST, class... TREST>
inline void query_recursive_set_param(TQUERY* _pquery, const TFIRST& _first, const TREST&... _args)
{
	_pquery->set_param<TFIRST>(INDEX, _first);
	query_recursive_set_param<INDEX+1, TQUERY, TREST...>(_pquery, _args...);
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
template <class TFIRST, class... TARGS>
void query::rdb::oledb::_query_dynamic_parameter<TACCESSOR, TROWSET, TMULTIPLE>::execute_query(const wstring_param _command, TFIRST&& _first, TARGS&&... _args)
{
	// 1) execute query
	this->prepare_query(_command);

	// 2) set param
	query_recursive_set_param(this, _first, _args...);

	// 3) execute query
	this->execute_query();
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::_query_dynamic_parameter<TACCESSOR, TROWSET, TMULTIPLE>::prepare_query(wstring_param _command, REFGUID _guid_command)
{
	// declare) 
	HRESULT result;
	int retry = 0;
	auto pquerier = this->m_psession->m_pquerier;

	// check) pquerier must not be nullptr
	CGASSERT_ERROR(pquerier != nullptr);

	// check) throw exception if pquerier is nullptr
	THROW_IF(pquerier == nullptr, throwable::failure(eRESULT::NOT_READY));

	scoped_lock(this->m_lockable_state_query)
	{
		// check)
		CGASSERT_ERROR(this->m_state_query == eOBJECT_STATE::READY);

		// check) must be preapre
		THROW_IF(this->m_state_query != eOBJECT_STATE::READY, throwable::failure(eRESULT::NOT_READY));

		// statistics) 
		pquerier->statistics_on_query_try();

		// 1) prepare query
		result = _prepare_query(_command, _guid_command);

		if (FAILED(result))
		{
			// declare) 
			auto e = trace_error_records(this, result, _command);
			auto result_last = result;

			do
			{
				// - get max retry count
				auto max_retry = this->m_psession->m_pquerier->get_max_retry_on_fail();

				// check) retry count out
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
				result = this->_prepare_query(_command, _guid_command);

			} while (result != S_OK);
		}

		// 2) success to preparing
		m_bprepared	 = true;
	}
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
HRESULT query::rdb::oledb::_query_dynamic_parameter<TACCESSOR, TROWSET, TMULTIPLE>::_prepare_query(wstring_param _command, REFGUID _guid_command)
{
	// declare) 
	HRESULT	result;

	// 1) create Command
	result = CCommand<TACCESSOR, TROWSET, TMULTIPLE>::Create(*this->m_psession, _command.data(), _guid_command);

	// check) throw if failed
	RETURN_IF(result != S_OK, result);

	// 2) prepare
	result = this->Prepare();

	// check) throw if failed
	RETURN_IF(result != S_OK, result);

	// declare) 
	void* pdummy;

	// 3) bind parameter
	result = TACCESSOR::BindParameters(&this->m_hParameterAccessor, this->m_spCommand, &pdummy, true, true);

	// check) throw if failed
	RETURN_IF(result != S_OK, result);

	// return)
	return	result;
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::_query_dynamic_parameter<TACCESSOR, TROWSET, TMULTIPLE>::execute_query()
{
	scoped_lock(this->m_lockable_state_query)
	{
		// declare) 
		HRESULT result = 0;
		auto pquerier = this->m_psession->m_pquerier;

		// check) pquerier must not be nullptr
		CGASSERT_ERROR(pquerier != nullptr);

		// check) throw exception if pquerier is nullptr
		THROW_IF(pquerier == nullptr, throwable::failure(eRESULT::NOT_READY));

		// check) 
		CGASSERT_ERROR(this->m_state_query == eOBJECT_STATE::READY);

		// check) must be preapre
		THROW_IF(this->m_state_query != eOBJECT_STATE::READY, throwable::failure(eRESULT::NOT_READY));

		// check) must be preapre
		THROW_IF(m_bprepared == false, throwable::failure(eRESULT::NOT_READY));

		// 2) open_query
		result = this->Open(nullptr, nullptr, true, 0);

		// check)
		if (FAILED(result))
		{
			// statistics_  
			pquerier->statistics_on_query_fail();

			// - ...
			m_bprepared = false;

			// raise)
			throw trace_error_records(this, result, this->m_query_string);
		}

		// statistics)
		pquerier->statistics_on_query_success();

		// 2) set false 
		m_bprepared = false;

		// 3) set state 
		this->m_state_query = eOBJECT_STATE::PROCESSED;
	}
}

template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
void query::rdb::oledb::_query_dynamic_parameter<TACCESSOR, TROWSET, TMULTIPLE>::close_query() noexcept
{
	scoped_lock(this->m_lockable_state_query)
	{
		// check) 
		RETURN_IF(this->m_psession.empty());

		// 1) close_query...
		Nquery<TACCESSOR, TROWSET, TMULTIPLE>::close_query();

		// 2) get querier
		auto pquerier = this->m_psession->m_pquerier;

		// 3) prepared 
		if (m_bprepared == true)
		{
			// - 
			if (pquerier != nullptr)
			{
				pquerier->statistics_on_query_fail();
			}

			// - set false 
			m_bprepared = false;
		}

		// 4) ParameterEntry용 버퍼를 할당해제
		SAFE_DELETE_ARRAY(this->m_pParameterEntry);

		// 5) ParameterName용 Buffer를 할당해제
		if (this->m_ppParamName != NULL)
		{
			CoTaskMemFree(*this->m_ppParamName);
			SAFE_DELETE(this->m_ppParamName);
		}

		// 6) m_pParameterBuffer 버퍼를 할당해제
		SAFE_DELETE(this->m_pParameterBuffer)

		// 7) ...
		this->m_nParameterBufferSize = 0;
		this->m_nParams = 0;
	}
}


}