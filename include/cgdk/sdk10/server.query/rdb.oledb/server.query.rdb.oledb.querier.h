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
// query::rdb::oledb::querier
//
// 1. query::rdb::oledb::querier란!
//    1) Ole-DB를 사용하여 Query를 수행하는 Querier이다.
//
// 2. query::rdb::oledb::querier의 핵심! Function의 기능 설명
//    1) OpenDB		처음 사용할 때 DB를 여는 함수로 처음에 반드시 호출하여야 하는
//	                함수.
//					여기서 DB연결에 필요한 로그인을 수행하고 session을 만든다
//	  2) CloseDB	로그인 된 DB를 로그아웃하는 것을 의미한다.
//    3) Query
//		 - post_execute_query	비동기적으로 Query를 수행하는 함수다.
//		 - execute_query		동기적으로 Query를 수행하는 함수로 Query가 완료될 때
//							까지 함수가 완료되지 않는다.
//
// 3. Parameters
//    1) "session"
//    2) "connection_string"
//    3) "provider"
//       "data_source"
//       "user_id"
//       "password"
//       "initial_catalog"
//
//    [CASE MSSQL]
//		"provider"			 = "SQLOLEDB.1"
//		"data_source"		 = "TEST_SERVER"
//		"user_id"			 = "sa"
//		"password"			 = "12341234"
//		"initial_catalog"	 = "Test"
//
//    [CASE MySQL]
//		"provider"			 = "MSDASQL.1"
//		"data_source"		 = "TEST_SERVER"
//		"user_id"			 = "sa"
//		"password"			 = "12341234"
//		"initial_catalog"	 = "Test"
//
// 3. 주의 사항
//    1) execute_query를 사용중 PostQuery의 사용에 중의해야 한다.
//       execute_query가 session을 모두 물고 데드락 현상이 발생할 수 있기 때문이다.
//       requestQueyry를 사용한다면 기존 session을 해제하고 다른 Query를
//       수행하기를 권장한다.
//
//-----------------------------------------------------------------------------
class query::rdb::oledb::querier :
// inherited classes)
	virtual public				Iquerier,
	public						object::Nnameable,
	public                      object::Ninitializable_startable,
	public						Nmessage_transmitter,
	virtual public				Imessageable
{
// definitions)
public:
	using	IQUERY = Iquery;
	using	QUERIER = querier;
			struct START_PARAMETER
			{
				eDB_PROVIDER	provider = eDB_PROVIDER::NONE;
				std::string		data_source;
				std::string		user_id;
				std::string		password;
				std::string		initial_catalog;
				std::string		options;
				std::size_t		count_session = 0;
				std::size_t		count_data_source = 0;
				uint64_t		additional = 0;
			};

// constructor/destructor) 
public:
			querier();
			querier(const std::string_view _name);
	virtual ~querier() noexcept;
	
// public) 
public:
	// 1) start
			result_code			start(const context& _context) { return this->object::Nstartable::start(_context);}
	virtual	result_code			start(context& _context) override { return this->object::Nstartable::start(_context);}
			result_code			start(Iexecutor* _pexecutor, const std::string_view _connection_string, std::size_t _count_session=32, std::size_t _count_data_source = 1);
			result_code			start(const std::string_view _connection_string, std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(eDB_PROVIDER _provider, const std::string_view _data_source, const std::string_view _user_id = std::string_view(), const std::string_view _password = std::string_view(), const std::string_view _initial_catalog = std::string_view(), const std::string_view _option = std::string_view(), std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(const std::string_view _provider, const std::string_view _data_source, const std::string_view _user_id = std::string_view(), const std::string_view _password = std::string_view(), const std::string_view _initial_catalog = std::string_view(), const std::string_view _option = std::string_view(), std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) };  return start(temp); }

	[[nodiscard]] object_ptr<Iexecutor> executor() const { return this->m_pexecutor; }

	// 2) execute_query/post_execute_query/Cancel
			template <class TQUERY = query_t>
			object_ptr<TQUERY>	execute_query(const wstring_param _command);
			auto				execute_query(const wstring_param _command) { return this->execute_query<query_t>(_command); }
			template <class TQUERY = query_param_t, class T1, class... TARGS>
			object_ptr<TQUERY>	execute_query(const wstring_param _command, T1&& _first, TARGS&&... _args);
			void				execute_query(Iserver_query* _pquery) { this->process_execute_query(_pquery); }

			template <class TQUERY = query_t>
			void				post_execute_query(const wstring_param _command, const std::function<void(throwable::failure_ex&, TQUERY*)>& _lambda);
			void				post_execute_query(const wstring_param _command, const std::function<void(throwable::failure_ex&, query_t*)>& _lambda) { this->post_execute_query<query_t>(_command, _lambda); }
			template <class TQUERY = query_t>
			void				post_execute_query(const wstring_param _command, std::function<void(throwable::failure_ex&,TQUERY*)>&& _lambda);
			void				post_execute_query(const wstring_param _command, std::function<void(throwable::failure_ex&, query_t*)>&& _lambda) { this->post_execute_query<query_t>(_command, std::move(_lambda)); }
			void				post_execute_query(Iserver_query* _pquery) { this->process_post_execute_query(_pquery); }

			template <class TQUERY = query_param_t>
	[[nodiscard]] object_ptr<TQUERY> prepare_query(const wstring_param _command);

	virtual	bool				cancel_query(Iserver_query* _pquery) noexcept;
			void				cancel_all_queries() noexcept;

	// 3) alloc_query/post_alloc_query
			template <class TQUERY = query_t>
	[[nodiscard]] object_ptr<TQUERY> alloc_query() { auto pquery = make_object<TQUERY>(); this->alloc_session(pquery); return pquery;}
			template <class TQUERY = query_t>
			void				post_alloc_query(const std::function<void(TQUERY*)>& _lambda);
			template <class TQUERY = query_t>
			void				post_alloc_query(std::function<void(TQUERY*)>&& _lambda);

	// 4) alloc_session/free_session
			void				alloc_session(Iquery* _pquery);
	virtual	void				free_session(session* _psession) noexcept;

	// 5) options
	static	void				enable_logging_warning_info(bool _enable = true) noexcept { m_s_enable_logging_warning_info = _enable; }
	static	void				disable_logging_warning_info() noexcept { enable_logging_warning_info(false); }
	[[nodiscard]] static bool	is_enable_logging_warning_info() noexcept { return m_s_enable_logging_warning_info; }
	[[nodiscard]] static bool	is_disable_logging_warning_info() noexcept { return !is_enable_logging_warning_info(); }

// implementation) 
protected:
	// 6) status
	virtual	result_code			process_start(context& _context) override;
	virtual	result_code			process_stop() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	// 7) query
	virtual	void				process_execute_query(Iserver_query* _pquery);
	virtual	void				process_post_execute_query(Iserver_query* _pquery);
	[[nodiscard]] circular_list<object_ptr<session>> process_create_session(std::wstring_view _connection_string, std::size_t _count_session=32, std::size_t _count_data_source=1);

	// 8) Process Message
	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// 9) transmit_message
	virtual	result_code			process_transmit_message(sMESSAGE& _msg) override;

protected:
			struct QUEUED_QUERY
			{
			public:
				QUEUED_QUERY(Ireferenceable* ) noexcept : f_execute(),pquery() {}
				QUEUED_QUERY(const QUEUED_QUERY& _copy) noexcept : f_execute(_copy.f_execute), pquery(_copy.pquery) {}
				QUEUED_QUERY(QUEUED_QUERY&& _move) noexcept : f_execute(_move.f_execute), pquery(std::move(_move.pquery)) { _move.reset();}

			public:
				QUEUED_QUERY& operator=(QUEUED_QUERY&& _move) noexcept { f_execute=_move.f_execute; this->pquery = std::move(_move.pquery); return *this;}

				void (querier::*f_execute)(Iquery*);
				object_ptr<Iquery>	pquery;
				[[nodiscard]] bool operator!=(Iserver_query* _pquery) const noexcept { return this->pquery!=_pquery;}
				[[nodiscard]] bool operator==(Iserver_query* _pquery) const noexcept { return this->pquery==_pquery;}

				void			reset() noexcept { this->pquery.reset();}
			};

protected:
	// 10) OLE-DB용 DB session(connection)
			std::recursive_mutex m_lockable_query;
			circular_list<object_ptr<session>> m_stack_session;
			circular_list<QUEUED_QUERY> m_queue_query;
			std::atomic<std::size_t> m_count_session_created = 0;
			std::size_t			m_interval_regeneration = 0;
	static	bool				m_s_enable_logging_warning_info;

	// 11) Query수행 함수.
			void				query_request(Iquery* _pquery);
			void				query_post(Iquery* _pquery);

	// 12) executor
			object_ptr<Iexecutor> m_pexecutor;
			own_ptr<Iexecutor>	m_pexecutor_own;

	// declare) 
			template <class TQUERY> class query_executable;
			class executable_query;
			friend class executable_query;
};

template <class TQUERY>
object_ptr<TQUERY> query::rdb::oledb::querier::execute_query(const wstring_param _command)
{
	// 1) alloc query object
	auto pquery = this->alloc_query<TQUERY>();

	// check)
	CGASSERT_ERROR(pquery->m_psession.exist());

	// 2) execute query
	pquery->execute_query(_command);

	// return) 
	return pquery;
}

template <class TQUERY, class T>
inline void recursive_set_param(TQUERY* _pquery, std::size_t _index, const T& _last)
{
	_pquery->set_param<T>(_index, _last);
}

template <class TQUERY, class T1, class... TREST>
inline void recursive_set_param(TQUERY* _pquery, std::size_t _index, const T1& _first, const TREST&... _args)
{
	_pquery->set_param<T1>(_index, _first);
	recursive_set_param<TQUERY, TREST...>(_pquery, _index + 1, _args...);
}

template <class TQUERY, class T1, class... TARGS>
object_ptr<TQUERY> query::rdb::oledb::querier::execute_query(const wstring_param _command, T1&& _first, TARGS&&... _args)
{
	// check) is ready?
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) alloc query object
	auto pquery = this->alloc_query<TQUERY>();

	// check)
	CGASSERT_ERROR(pquery->m_psession.exist());

	// 2) execute query
	pquery->execute_query(_command, _first, _args...);

	// return) 
	return pquery;
}

template <class TQUERY>
void query::rdb::oledb::querier::post_execute_query(const wstring_param _command, const std::function<void(throwable::failure_ex&, TQUERY*)>& _lambda)
{
	// check) start된 상태가 아니라면 안됀다.
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) create query object
	auto pquery = make_object<query_function<TQUERY>>();

	// 2) set query info
	pquery->set_query_string(_command);
	pquery->set_function(_lambda);

	// 3) post execute query
	this->process_post_execute_query(pquery);
}

template <class TQUERY>
void query::rdb::oledb::querier::post_execute_query(const wstring_param _command, std::function<void(throwable::failure_ex&, TQUERY*)>&& _lambda)
{
	// check) start된 상태가 아니라면 안됀다.
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) create query object
	auto pquery = make_object<query_function<TQUERY>>();

	// 2) set query info
	pquery->set_query_string(_command);
	pquery->set_function(std::move(_lambda));

	// 3) post execute query
	this->process_post_execute_query(pquery);
}

// declare) 
template <class TQUERY>
class query::rdb::oledb::querier::query_executable : public TQUERY, virtual public Iquery, public Npoolable<query::rdb::oledb::querier::query_executable<TQUERY>>
{
public:
	std::function<void(TQUERY*)>		m_lambda;
	virtual	void	process_execute_query() override { this->m_lambda(this); }
};

template <class TQUERY>
void query::rdb::oledb::querier::post_alloc_query(const std::function<void(TQUERY*)>& _lambda)
{
	// check) start된 상태가 아니라면 안됀다.
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) create query object
	auto pquery = make_object<query_executable<TQUERY>>();

	// 2) set lambda function
	pquery->m_lambda = _lambda;

	// 3) Query를 요청한다.
	this->process_post_execute_query(pquery);
}

template <class TQUERY>
void query::rdb::oledb::querier::post_alloc_query(std::function<void(TQUERY*)>&& _lambda)
{
	// check) start된 상태가 아니라면 안됀다.
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) create query object
	auto pquery = make_object<query_executable<TQUERY>>();

	// 2) set lambda function
	pquery->m_lambda = std::move(_lambda);

	// 3) Query를 요청한다.
	this->process_post_execute_query(pquery);
}

template <class TQUERY>
object_ptr<TQUERY> query::rdb::oledb::querier::prepare_query(const wstring_param _command)
{
	// 1) alloc query object
	auto pquery = this->alloc_query<TQUERY>();

	// check)
	CGASSERT_ERROR(pquery->m_psession.exist());

	// 2) execute query
	pquery->prepare_query(_command);

	// return) 
	return pquery;
}


}