//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Web Classes                                *
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
// query::http::Cquery
//
//
// ----------------------------------------------------------------------------
class query::http::query :
// inherited classes) 
	public						net::http_request,
	virtual public				Iserver_query
{
// definitions)
public:
	typedef	query	IQUERY;
	typedef	querier	QUERIER;

public:
	// 1) execute_query/post_execute_query/Cancel
			void				execute_query(const std::string_view _command);
			template <class TFIRST, class... TARGS>
			void				execute_query(const std::string_view _format, TFIRST _first, TARGS... _args);

			// 2) execute
			void				post_execute_query(const std::string_view _command);
			template <class TQUERY = query>
			void				post_execute_query(const std::string_view _command, const std::function<void(result_code,TQUERY*)>& _response);
			template <class TQUERY = query>
			void				post_execute_query(const std::string_view _command, std::function<void(result_code,TQUERY*)>&& _response = nullptr);
	virtual	void				close_query() noexcept;

	[[nodiscard]] const sMESSAGE_HTTP& result() const noexcept { return m_result; }
public:
	virtual	void				process_execute_query() override {}
			void				porcess_set_querier(querier* _pquerier);
	virtual	void				process_reset_session() noexcept override;
	virtual	int					process_response(sMESSAGE& _msg) override;

public:
	// 1) querier
			object_ptr<querier>	m_pquerier;
			sMESSAGE_HTTP		m_result;

	// 2) ....
			std::recursive_mutex m_lockable_state_query;
};

template <class TFIRST, class... TARGS>
void query::http::query::execute_query(const std::string_view _format, TFIRST _first, TARGS... _args)
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// declare) 
	auto buf_query_string = alloc_shared_buffer(65536);

	// 1) Generate trace Message
	auto str_length = __sprintf(buf_query_string.data<char>(), 65536, _format.data(), _first, _args...);

	// 2) execute_query
	this->execute_query(std::string_view(buf_query_string.data<char>(), str_length));
}

template <class TQUERY>
void query::http::query::post_execute_query(const std::string_view _command, const std::function<void(result_code, TQUERY*)>& _response)
{
	auto response = _response;

	post_execute_query(_command, std::move(response));
}

template <class TQUERY>
void query::http::query::post_execute_query(const std::string_view _command, std::function<void(result_code, TQUERY*)>&& _response)
{
	// 1) set function
	set_function([this, response=std::move(_response)](sMESSAGE_HTTP& /*_msg*/)
	{
		response(eRESULT::SUCCESS, this);
	});

	// 2) execute
	this->post_execute_query(_command);
}


}