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
class query::redis::Iquery :
	virtual public				Iserver_query
{
public:
	typedef	Iquery					IQUERY;
	typedef	querier					QUERIER;
	typedef	sMESSAGE_REDIS_RESPONSE	RESPONSE;

public:
			Iquery();
	virtual ~Iquery();

// public)
public:
	[[nodiscard]] object_ptr<session> get_session() const noexcept { return this->m_psession;}
			void				set_session(session* _psession) { this->process_set_session(_psession);}
			void				reset_session() noexcept { this->process_reset_session();}

			template <class TLOCK>
			void				wait(TLOCK& _cs) { m_cv_complete.wait(_cs); }
			void				wait() { std::unique_lock<std::recursive_mutex> cs(this->m_lockable_wait); this->m_cv_complete.wait(cs); }
			void				notify() noexcept { std::unique_lock<std::recursive_mutex> cs(this->m_lockable_wait); this->m_cv_complete.notify_one(); }
			void				execute_query(std::string_view _command);
			template <class TA, class... TARGS>
			void				execute_query(const std::string_view _format, TA _first, TARGS... _args);

			void				post_execute_query(std::string_view _command);
			void				post_execute_query(std::string_view _command, std::function<void()>&& _response);

	virtual	void				close_query() noexcept;

	[[nodiscard]] const resp_data&  result() const noexcept { return this->m_result; }

public:
	virtual	void				process_response();
	virtual	void				process_execute_query() override;
			void				process_set_session(session* _psession);
	virtual	void				process_reset_session() noexcept override;

public:
			shared_buffer		m_buffer_query;
			resp_data			m_result;

public:
			std::condition_variable_any m_cv_complete;
			std::recursive_mutex m_lockable_wait;

private:
			object_ptr<session>	m_psession;
			std::recursive_mutex m_lockable_state_query;
			std::vector<std::function<void()>> m_queue_query;

	virtual	void				on_final_release() noexcept override { this->reset_session(); this->m_result.reset(); }

			void				_process_notify_to_requestor() noexcept;
			void				_process_regenerate_session();
			void				_process_next_execute_query();
};

template <class TA, class... TARGS>
void query::redis::Iquery::execute_query(const std::string_view _format, TA _first, TARGS... _args)
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// 1) alloc shared_buffer
	auto buf_query_string = alloc_shared_buffer(65536 * sizeof(char));

	// 2) generate string
	auto str_length = __sprintf(buf_query_string.data(), 65536, _format.data(), _first, _args...);

	// 3) execute query
	return this->execute_query(std::string_view(buf_query_string.data(), str_length));
}


}