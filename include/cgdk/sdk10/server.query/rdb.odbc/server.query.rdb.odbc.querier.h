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
// query::rdb::odbc::querier
//
// * Parameters
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
//-----------------------------------------------------------------------------
class query::rdb::odbc::querier :
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
				std::string		character_set;
				std::string		options;
				std::size_t		count_session = 32;
				std::size_t		count_data_source = 1;
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
			result_code			start(Iexecutor* _pexecutor, const std::string_view _connection_string, std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(const std::string_view _connection_string, std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(eDB_PROVIDER _provider, const std::string_view _server, const std::string_view _user_id = std::string_view(), const std::string_view _password = std::string_view(), const std::string_view _initial_catalog = std::string_view(), const std::string_view _character_set = std::string_view(), const std::string_view _option = std::string_view(), std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(const std::string_view _provider, const std::string_view _server, const std::string_view _user_id = std::string_view(), const std::string_view _password = std::string_view(), const std::string_view _initial_catalog = std::string_view(), const std::string_view _character_set = std::string_view(), const std::string_view _option = std::string_view(), std::size_t _count_session = 32, std::size_t _count_data_source = 1);
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }; return start(temp); }

	[[nodiscard]] object_ptr<Iexecutor> executor() const { return this->m_pexecutor; }

	// 2) execute_query/post_execute_query/Cancel
			template <class TQUERY = query_t>
			object_ptr<TQUERY>	execute_query(const std::string_view _command);
			auto				execute_query(const std::string_view _command) { return this->execute_query<query_t>(_command); }
			template <class TQUERY = query::rdb::query_param_t, class T1, class... TARGS>
			object_ptr<TQUERY>	execute_query(const std::string_view _command, T1&& _first, TARGS&&... _args);

			template <class TQUERY = query_t>
			void				post_execute_query(const std::string_view _command, std::function<void(TQUERY*)>&& _lambda = nullptr);
			void				post_execute_query(const std::string_view _command, std::function<void(query::rdb::query_t*)>&& _lambda) { this->post_execute_query<query_t>(_command, std::move(_lambda)); }
			template <class TQUERY = query_t>
			void				post_execute_query(const std::string_view _command, const std::function<void(TQUERY*)>& _lambda) { this->post_execute_query<query_t>(_command, std::function<void(TQUERY*)>(_lambda)); }
			void				post_execute_query(const std::string_view _command, const std::function<void(query_t*)>& _lambda) { this->post_execute_query<query_t>(_command, std::function<void(query_t*)>(_lambda)); }

			template <class TQUERY = query_param_t>
	[[nodiscard]] object_ptr<TQUERY> prepare_query(const std::string_view _command);

			void				cancel_queries() noexcept;

	// 4) alloc_session/free_session
			object_ptr<session_t> alloc_session();
			void				post_alloc_session(std::function<void(session_t*)>&& _lambda);
	virtual	void				free_session(session* _psession) noexcept;

	// 5) alloc query
	template <class TQUERY = query_t>
	[[nodiscard]] object_ptr<TQUERY> alloc_query();

	// 6) options
	static	void				enable_logging_warning_info(bool _enable = true) noexcept { m_s_enable_logging_warning_info = _enable; }
	static	void				disable_logging_warning_info() noexcept { enable_logging_warning_info(false); }
	[[nodiscard]] static bool	is_enable_logging_warning_info() noexcept { return m_s_enable_logging_warning_info; }
	[[nodiscard]] static bool	is_disable_logging_warning_info() noexcept { return is_enable_logging_warning_info(); }

protected:
	// declare) 
	class Iexecutable_query : public Iexecutable, public factory::_traits_memory
	{
	public:
		virtual	void		on_final_release() noexcept override { this->m_psession.reset(); }
		object_ptr<session> m_psession;
	};
	friend class Iexecutable_query;

	virtual	result_code			process_start(context& _context) override;
	virtual	result_code			process_stop() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

			circular_list<object_ptr<session>> process_create_session(std::string_view _str_initialization, std::size_t _count_session=32, std::size_t _count_data_source=1);
			void				process_post_alloc_session(object_ptr<Iexecutable_query>&& _pexecutable);

	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// 7) process_transmit_message
	virtual	result_code			process_transmit_message(sMESSAGE& _msg) override;

protected:
			struct QUEUED_QUERY
			{
				std::function<void(object_ptr<session>&&)> f_execute;
			};

			std::recursive_mutex m_lockable_query;
			circular_list<object_ptr<session>> m_stack_session;
			circular_list<QUEUED_QUERY>	m_queue_query;
			std::atomic<std::size_t> m_count_session_created = 0;
			std::size_t			m_interval_regeneration = 0;
	static	bool				m_s_enable_logging_warning_info;

	// 11) executor
			object_ptr<Iexecutor> m_pexecutor;
			own_ptr<Iexecutor>	m_pexecutor_own;

};

template <class TQUERY>
object_ptr<TQUERY> query::rdb::odbc::querier::execute_query(const std::string_view _command)
{
	// 1) alloc session
	auto psession = this->alloc_session();

	// check) 
	CGASSERT_ERROR(psession.exist());

	// 2) alloc query
	auto pquery = psession->alloc_query<TQUERY>();

	// check) 
	CGASSERT_ERROR(pquery.exist());

	// check) 
	CGASSERT_ERROR(pquery->m_psession.exist());

	// s3) execute query
	pquery->execute_query(_command);

	// return) 
	return pquery;
}

template <class TQUERY, class T1, class... TARGS>
object_ptr<TQUERY> query::rdb::odbc::querier::execute_query(const std::string_view _format, T1&& _first, TARGS&&... _args)
{
	// 1) alloc session
	auto psession = this->alloc_session();

	// check) 
	CGASSERT_ERROR(psession.exist());

	// 2) alloc query
	auto pquery = psession->alloc_query<TQUERY>();

	// check) 
	CGASSERT_ERROR(pquery.exist());

	// check) 
	CGASSERT_ERROR(pquery->m_psession.exist());

	// 3) execute query
	pquery->execute_query(_format, _first, std::forward<TARGS>(_args)...);

	// return) 
	return pquery;
}

template <class TQUERY>
void query::rdb::odbc::querier::post_execute_query(const std::string_view _command, std::function<void(TQUERY*)>&& _lambda)
{
	// check) is ready?
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	class executable_query : public Iexecutable_query
	{
	public:
		virtual	intptr_t process_execute(intptr_t, std::size_t) override
		{
			// 1) get session
			auto psession = std::move(this->m_psession);
			auto command = std::move(this->m_command);

			// check)
			CGASSERT_ERROR(psession.exist());

			// check)
			CGASSERT_ERROR(command.empty() == false);

			// 2) alloc query
			auto pquery = psession->alloc_query<TQUERY>();

			// 3) query
			pquery->execute_query(command);
		
			// 4) reset session
			this->m_lambda(pquery);

			// 5) reset
			pquery->reset_session();
		
			// return) 
			return 1;
		}

		std::function<void(TQUERY*)> m_lambda;
		std::string m_command;
	};

	// 1) create query object
	auto pexecutable_query = make_object<executable_query>();
	pexecutable_query->m_lambda = std::move(_lambda);
	pexecutable_query->m_command = _command;

	// 2) post  
	this->process_post_alloc_session(std::move(pexecutable_query));
}

template <class TQUERY>
object_ptr<TQUERY> query::rdb::odbc::querier::prepare_query(const std::string_view _command)
{
	// 1) alloc query
	auto pquery = this->alloc_query();

	// check) 
	CGASSERT_ERROR(pquery.exist());

	// check) 
	CGASSERT_ERROR(pquery->m_psession.exist());

	// s3) execute query
	pquery->prepare_query(_command);

	// return) 
	return pquery;
}

template <class TQUERY>
object_ptr<TQUERY> query::rdb::odbc::querier::alloc_query()
{
	// 1) alloc session
	auto psession = this->alloc_session();

	// check) 
	CGASSERT_ERROR(psession.exist());

	// 2) alloc query and return
	return psession->alloc_query<TQUERY>();
}


}