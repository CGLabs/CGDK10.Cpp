//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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

namespace CGDK::net::ip
{
template<class InternetProtocol>
class basic_resolver : public resolver_base
{
public:
	// types:
	//using executor_type = io_context::executor_type;
	using protocol_type = InternetProtocol;
	using endpoint_type = typename InternetProtocol::endpoint;
	using results_type  = basic_resolver_results<InternetProtocol>;

	void CompletionToken(
		const std::error_code& error,
		results_type results
	);

public:
	// 21.17.1, construct / copy / destroy:
	explicit basic_resolver() noexcept {}
			basic_resolver(const basic_resolver&) = delete;
			basic_resolver(basic_resolver&& _rhs) noexcept {}
			~basic_resolver() noexcept {}
public:
	// 21.17.4, basic_resolver operations:
			//void				cancel();
	[[nodiscard]] static results_type resolve(std::string_view _host_name) { return resolve(_host_name, std::string_view()); }
	[[nodiscard]] static results_type resolve(std::string_view _host_name, std::string_view _service_name) { return resolve(_host_name, _service_name, AI_ALL); }
	[[nodiscard]] static results_type resolve(std::string_view _host_name, std::string_view _service_name, std::error_code& _error_code) { return resolve(_host_name, _service_name, AI_ALL, _error_code); }
	[[nodiscard]] static results_type resolve(std::string_view _host_name, std::string_view _service_name, flags _flag) { std::error_code error_code; return resolve(_host_name, _service_name, _flag, error_code); }
	[[nodiscard]] static results_type resolve(std::string_view _host_name, std::string_view _service_name, flags _flag, std::error_code& _error_code) { return _resolve(AF_UNSPEC, endpoint_type().protocol().type(), endpoint_type().protocol().protocol(), _host_name, _service_name, _flag, _error_code); }
			template<class TCOMPLETION_TOKEN>
	static	auto				async_resolve(std::string_view _host_name, std::string_view _service_name, TCOMPLETION_TOKEN&& _token) { return system_executor::post([=]() { _token.results = resolve(_host_name, _service_name, _token.error); }); }
			template<class TCOMPLETION_TOKEN>
	static	auto				async_resolve(std::string_view _host_name, std::string_view _service_name, flags _flag, TCOMPLETION_TOKEN&& _token) { return system_executor::post([=]() { _token.results = resolve(_host_name, _service_name, _flag, _token.error); }); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name) { return resolve(_protocol, _host_name, std::string_view(), AI_ALL); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name) { return resolve(_protocol, _host_name, _service_name, AI_ALL); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, std::error_code& _error_code) { return resolve(_protocol, _host_name, std::string_view(), AI_ALL, _error_code); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name, std::error_code& _error_code) { return resolve(_protocol, _host_name, _service_name, AI_ALL, _error_code); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, flags _flag) { std::error_code error_code; return resolve(_protocol, _host_name, std::string_view(), _flag, error_code); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name, flags _flag) { std::error_code error_code; return resolve(_protocol, _host_name, _service_name, _flag, error_code); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, flags _flag, std::error_code& _error_code) { return _resolve(_protocol.family(), _protocol.type(), _protocol.protocol(), _host_name, std::string_view(), _flag, _error_code); }
	[[nodiscard]] static results_type resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name, flags _flag, std::error_code& _error_code) { return _resolve(_protocol.family(), _protocol.type(), _protocol.protocol(), _host_name, _service_name, _flag, _error_code); }

			template<class TCOMPLETION_TOKEN>
	static	auto				async_resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name, TCOMPLETION_TOKEN&& _token) { return system_executor::post([=]() { _token.results = resolve(_protocol, _host_name, _service_name, _token.error); }); }
			template<class TCOMPLETION_TOKEN>
	static	auto				async_resolve(const protocol_type& _protocol, std::string_view _host_name, std::string_view _service_name, flags _flag, TCOMPLETION_TOKEN&& _token) { return system_executor::post([=]() { _token.results = resolve(_protocol, _host_name, _service_name, _flag, _token.error); }); }
	[[nodiscard]] static results_type resolve(const endpoint_type& _endpoint) { std::error_code error_code; return resolve(_endpoint, error_code); }
	[[nodiscard]] static results_type resolve(const endpoint_type& _endpoint, std::error_code& _error_code) { return _resolve(endpoint_type().protocol().type(), _endpoint.data(), _error_code); }
			template<class TCOMPLETION_TOKEN>
	static	auto				async_resolve(const endpoint_type& _endpoint, TCOMPLETION_TOKEN&& _token) { return system_executor::post([=]() { _token.results = resolve(_endpoint, _token.error); }); }
public:
			basic_resolver&		operator = (const basic_resolver&) = delete;
			basic_resolver&		operator = (basic_resolver&& _rhs) { return *this; }
protected:
	[[nodiscard]] static results_type _resolve(int _protocol_family, int _protocol_type, int _protocol_protocol, std::string_view _host_name, std::string_view _service_name, net::ip::resolver_base::flags _flag, std::error_code& _error_code) noexcept;
	[[nodiscard]] static results_type _resolve(int _protocol_type, const net::sockaddr& _sockaddr, std::error_code& _error_code) noexcept;
};


}