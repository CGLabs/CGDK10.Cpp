//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               Redis Classes                               *
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
// net::io::sender::Nredis
//
//
//-----------------------------------------------------------------------------
class query::redis::querier : 
// inherited classes)
	public						Iquerier,
	public						object::Nnameable,
	public						object::Ninitializable_startable,
	public						Nmessage_transmitter,
	virtual public				Imessageable
{
// Definitiions)
public:
	using	end_point_type = net::ip::tcp::endpoint;
			struct START_PARAMETER
			{
				end_point_type		remote_endpoint;
				std::size_t			count_session = 32;
				int					wait_seconds = 0;
				object_ptr<executor::Iio_context> pio_context;
			};

// constructor/destructor)
public:
			querier();
			querier(const std::string_view _name);
	virtual	~querier() noexcept;

// Publics)
public:
	// 1) open
			result_code			start() { context context_start; return object::Nstartable::start(context_start);}
			result_code			start(const context& _context) { return this->object::Nstartable::start(_context);}
	virtual	result_code			start(context& _context) override { return this->object::Nstartable::start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }; return this->start(temp); }

	// 2) request Query (Sync/Async)
			object_ptr<Iquery>	execute_query(std::string_view _command);
			template <class TA, class... TARGS>
			object_ptr<Iquery>	execute_query(const std::string_view _format, TA _first, TARGS... _args);

			template<class TQUERY>
			void				post_execute_query(std::string_view _command, std::function<void(TQUERY*)>&& _response);
			void				post_execute_query(std::string_view _command, std::function<void(redis::query*)>&& _response) { this->post_execute_query<redis::query>(_command, std::move(_response)); }
	virtual	bool				cancel_query(Iserver_query* _pquery) noexcept;

			template <class TQUERY = query>
	[[nodiscard]] object_ptr<TQUERY> alloc_query() { auto pquery = make_object<TQUERY>(); alloc_session(pquery); return pquery;}
			template <class TQUERY = query>
			void				post_alloc_query(const std::function<void(TQUERY*)>& _response);

			void				alloc_session(Iquery* _pquery);
			void				post_alloc_session(Iquery* _pquery);
	virtual	void				free_session(session* _psession) noexcept;

	// statistics)
	[[nodiscard]] std::size_t	get_created_session_count() const { return static_cast<std::size_t>(this->statistics_get_exist_session());}
	[[nodiscard]] std::size_t	get_prcessing_session_count() const { std::lock_guard<std::recursive_mutex> cs(const_cast<std::recursive_mutex&>(this->m_lockable_query)); return this->m_count_session_created - this->m_stack_session.size(); }
	[[nodiscard]] std::size_t	get_stacked_session_count() const noexcept { std::lock_guard<std::recursive_mutex> cs(const_cast<std::recursive_mutex&>(this->m_lockable_query)); return this->m_stack_session.size(); }
	[[nodiscard]] std::size_t	get_queued_query_count() const noexcept { return this->m_count_query_queued;}

// implementation)
public:
	//2) process_execute_query
	virtual	void				process_execute_query(Iserver_query* _pquery);
	virtual	void				process_post_execute_query(Iserver_query* _pquery);
	virtual	void				process_execute_query(Iquery* _pquery);
	virtual	void				process_post_execute_query(Iquery* _pquery);
	[[nodiscard]] virtual uint16_t process_get_default_port() noexcept { return 6379; }

protected:
	// 2) Status
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	// 3) process Message
	virtual	result_code			process_message(sMESSAGE& _msg) override;
	
protected:
	// 4) Register/unregister
			void				register_session(session* _psocket);
			void				unregister_session(session* _psocket) noexcept;

	// 5) dispatch
	virtual	result_code			process_transmit_message(sMESSAGE& _msg) override;

protected:
			struct QUEUED_QUERY
			{
			public:
				QUEUED_QUERY(Ireferenceable* ) noexcept : f_execute(nullptr) {}
				QUEUED_QUERY(const QUEUED_QUERY& _copy) noexcept : f_execute(_copy.f_execute), pquery(_copy.pquery) {}
				QUEUED_QUERY(QUEUED_QUERY&& _move) noexcept : f_execute(_move.f_execute), pquery(std::move(_move.pquery)) { _move.reset();}

			public:
				std::function<void()> f_execute;
				object_ptr<Iquery>	pquery;

				QUEUED_QUERY&	operator=(QUEUED_QUERY&& _move) noexcept { f_execute = std::move(_move.f_execute); this->pquery = std::move(_move.pquery); return *this; }
				bool			operator!=(Iserver_query* _pquery) const noexcept { return this->pquery!=_pquery;}
				bool			operator==(Iserver_query* _pquery) const noexcept { return this->pquery==_pquery;}

				void			reset() noexcept { this->pquery.reset();}
			};

protected:
	// 6) OLE-DB용 DB session(connection)
			std::recursive_mutex m_lockable_query;
			circular_list<object_ptr<session>>	m_stack_session;
			circular_list<QUEUED_QUERY> m_queue_query;
			std::atomic<std::size_t> m_count_session_created;
			std::atomic<std::size_t> m_count_query_queued{ 0 };

			std::atomic<uint64_t> m_statiistics_request = 0;
			std::atomic<uint64_t> m_statiistics_received = 0;
			std::atomic<uint64_t> m_statiistics_complete = 0;


	// 7) Query수행 함수.
			void				_post_alloc_session(Iquery* _pquery, std::function<void()>&& _f_response);
			void				query_alloc_session(Iquery* _pquery);
			void				query_post_alloc_session(Iquery* _pquery);

	// 8) executor
			object_ptr<executor::Iio_context>	m_pio_context;
			own_ptr<executor::Iio_context>		m_pio_context_own;
			
	// Friend)
			class executable_query;
			friend class	Iquery;
			friend class	session;
			friend class	executable_query;
};

template <class TA, class... TARGS>
object_ptr<query::redis::Iquery> query::redis::querier::execute_query(const std::string_view _format, TA _first, TARGS... _args)
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// check) 
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) alloc shared_buffer
	auto buf_query_string = alloc_shared_buffer(65536 * sizeof(char));

	// 2) generate string
	auto str_length = __sprintf(buf_query_string.data(), 65536, _format.data(), _first, _args...);

	// 3) execute query
	return this->execute_query(std::string_view(buf_query_string.data(), str_length));
}

template <class TQUERY>
void query::redis::querier::post_execute_query(std::string_view _command, std::function<void(TQUERY*)>&& _response)
{
	// check) 
	THROW_IF(_command.empty(), throwable::failure(eRESULT::INVALID_ARGUMENT, 0, std::string_view("parameter['_command'] is empty")));

	// 1) 새로운 Query를 생성한다.
	auto pquery = this->alloc_query<TQUERY>();

	// 2) post execute
	pquery->post_execute_query(_command, [response=std::move(_response),pquery]() { response(pquery); });
}

template <class TQUERY>
void query::redis::querier::post_alloc_query(const std::function<void(TQUERY*)>& _response)
{
	// check) 
	THROW_IF(this->get_object_state() != eOBJECT_STATE::RUNNING && this->get_object_state() != eOBJECT_STATE::START_PENDING, throwable::failure(eRESULT::NOT_READY, 0, std::string_view("querier is not started")));

	// 1) create query object
	auto pquery = make_object<TQUERY>();

	// 2) post execute
	this->post_alloc_query(pquery, [this, _response, pquery]()
	{
		// check) m_psession이 nullptr이면 안됀다.
		CGASSERT_ERROR(pquery->get_session().exist());

		try
		{
			if (_response != nullptr)
			{
				_response(pquery);
			}
		}
		catch (...)
		{
			// statistics) 
			this->statistics_on_query_fail();

			// - reset session
			pquery->reset_session();
		}
	});
}


}