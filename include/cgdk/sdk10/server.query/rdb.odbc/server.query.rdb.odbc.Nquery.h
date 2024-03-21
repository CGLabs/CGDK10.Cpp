//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Query odbc Classes                         *
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
// query::rdb::odbc::Nquery
//
// 
//-----------------------------------------------------------------------------
class query::rdb::odbc::Nquery : 
	virtual public				Iquery
{
public:
			Nquery() noexcept;
	virtual ~Nquery() noexcept;

	// 1) create command and set the command text
			void				prepare_query(const std::string_view _command);

	// 2) QUery open/close
			void				execute_query(const std::string_view _command);
			void				execute_query();
			template <class TFIRST, class... TARGS>
			void				execute_query(const std::string_view _command, TFIRST&& _first, TARGS&&... _args);

			void				open_query();
			void				close_query() noexcept;

	// 3) Move FIrst/Move Next
			result_code			move_first();
			result_code			move_next() noexcept;

			result_code			get_next_result(bool _bind = true) noexcept;

	// 4) Query String
			void				set_query_string(const std::string_view _command) { this->m_query_string = _command; }
			const std::string&	get_query_string() const noexcept { return this->m_query_string;}

	// 5) get_value/ set_param/ get_param
			// - set Param
			template<class TTYPE>
			void				set_param(std::size_t _ordinal, const TTYPE& _data)
			{
				// check)
				THROW_IF(_ordinal >= this->m_vector_params.size(), throwable::failure_ex(eRESULT::OUT_OF_RANGE, 0, std::string_view("(error) parameter index is out of range")));

				// 1) set param
				auto result = ODBC_SET_PARAM<TTYPE>(this->m_handle_stmt, this->m_vector_params[_ordinal], _ordinal, _data);

				// check)
				if (SQL_SUCCEEDED(result) == false)
				{
					// raise)
					throw trace_error_records(this, result, std::string_view());
				}
			}
			void				set_param(std::size_t _ordinal, SQLSMALLINT _inputoutput_type, SQLSMALLINT _value_type, SQLSMALLINT _parameter_type, SQLULEN _column_size, SQLSMALLINT _decimal_digits, SQLPOINTER _parameter_value_ptr, SQLLEN _buffer_length, SQLLEN* _strlen_or_int_ptr = 0);

			// - get_param
			template<class TTYPE>
	[[nodiscard]] TTYPE			get_param(std::size_t _ordinal) { return ODBC_GET_PARAM<TTYPE>(this->m_handle_stmt, _ordinal);}
			template<class TTYPE>
	[[nodiscard]] TTYPE			get_param(const std::string_view _column_name) { this->get_param<TTYPE>(this->get_ordinal(_column_name)); }

			// - ordinals
	[[nodiscard]] std::size_t	get_ordinal(const std::string_view _column);

			// - get result
			template<class TDEST>
	[[nodiscard]] auto			get_result()
								{
									std::vector<typename ODBC_GET_VALUE<typename _ODBC_DEFAULT_PARAM<TDEST>::type, TDEST>::TRETURN> result;
									this->move_first();
									do
									{
										result.push_back(ODBC_GET_VALUE<typename _ODBC_DEFAULT_PARAM<TDEST>::type, TDEST>::get(this->m_handle_stmt, static_cast<SQLUSMALLINT>(1)));
									} while (this->move_next() == eRESULT::SUCCESS);
									this->get_next_result();
									return result;
								}

			template <class TOBJECT>
			struct _ITEM
			{
			public:
				TOBJECT*			pquery;

			public:
			[[nodiscard]] bool		exist(std::size_t _ordinal) const noexcept { return pquery != nullptr; }
			[[nodiscard]] bool		empty(std::size_t _ordinal) const noexcept { return pquery == nullptr; }
			[[nodiscard]] std::size_t get_length(std::size_t _ordinal) const noexcept { return 0; }

			[[nodiscard]] bool		is_success() const noexcept { return pquery != nullptr; }
			[[nodiscard]] bool		is_failed() const noexcept { return !this->is_success(); }
			[[nodiscard]] 			operator bool() const noexcept { return this->is_success(); }

			template<class TDEST, class TSOURCE = typename _ODBC_DEFAULT_PARAM<TDEST>::type>
			[[nodiscard]] typename ODBC_GET_VALUE<TSOURCE, TDEST>::TRETURN
									get_value(std::size_t _ordinal = 1) const { return ODBC_GET_VALUE<TSOURCE, TDEST>::get(pquery->m_handle_stmt, static_cast<SQLUSMALLINT>(_ordinal)); }
			template<class TDEST, class TSOURCE = typename _ODBC_DEFAULT_PARAM<TDEST>::type>
			[[nodiscard]] typename ODBC_GET_VALUE<TSOURCE, TDEST>::TRETURN
									get_value(const std::string_view _column_name) const { return this->get_value(pquery->get_ordinal(_column_name)); }
			};

			template <class TOBJECT>
			struct _ITERATOR
			{
			public:
				_ITERATOR(const _ITERATOR& _copy) : item { _copy.item }, result(_copy.result) {}
				_ITERATOR(TOBJECT* _query, result_code _result) : item { _query }, result(_result) {}

			public:
				_ITEM<TOBJECT>			item;
				result_code				result;

			public:
				_ITERATOR&				operator =  (const _ITERATOR& _rhs) noexcept { item =_rhs.item; result=_rhs.result; return (*this); }
			[[nodiscard]] _ITEM<TOBJECT>& operator -> () const noexcept { return item; }
			[[nodiscard]] _ITEM<TOBJECT>& operator *  () noexcept { return item; }
			[[nodiscard]] const _ITEM<TOBJECT>&	operator * () const noexcept { return item; }
			[[nodiscard]] bool			operator == (const _ITERATOR& _rhs) const { return result != _rhs.result; }
			[[nodiscard]] bool			operator != (const _ITERATOR& _rhs) const { return result == _rhs.result; }
				_ITERATOR&				operator ++ () { result = item.pquery->move_next(); return *this; }
				_ITERATOR&				operator ++ (int) { result = item.pquery->move_next(); return *this; }
			};
			template <typename TOBJECT> using ITERATOR = _ITERATOR<TOBJECT>;

	// 6) SQL handle STMT and Query String
			std::string			m_query_string;
			std::vector<sPARAM>	m_vector_params;
			std::map<std::string, std::size_t> m_map_column;

protected:
	virtual	void				process_execute_query() override;
	virtual	void				process_reset_session() noexcept override;
			void				_execute_query(std::string_view _command);
			void				_execute_query();
			SQLRETURN			_prepare_query(std::string_view _command, SQLHSTMT _handle_stmt);
			SQLRETURN			_prepare_query(std::wstring_view _command, SQLHSTMT _handle_stmt);

private:
	virtual	void				on_final_release() noexcept override { this->close_query(); CGDK::query::rdb::odbc::Iquery::on_final_release();}
};

template <std::size_t INDEX=1, class T>
inline void query_recursive_set_param(query::rdb::odbc::Nquery* _pquery, const T& _last)
{
	_pquery->set_param<T>(INDEX, _last);
}

template <std::size_t INDEX=1, class TFIRST, class... TREST>
inline void query_recursive_set_param(query::rdb::odbc::Nquery* _pquery, const TFIRST& _first, const TREST&... _args)
{
	_pquery->set_param<TFIRST>(INDEX, _first);
	query_recursive_set_param<INDEX+1, TREST...>(_pquery, _args...);
}

template <class TFIRST, class... TARGS>
void query::rdb::odbc::Nquery::execute_query(const std::string_view _command, TFIRST&& _first, TARGS&&... _args)
{
	// 1) execute query
	this->prepare_query(_command);	

	// 2) set params
	query_recursive_set_param(this, _first, _args...);

	// 3) execute query
	this->execute_query();
}



}