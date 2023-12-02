#pragma once

#include "asio/asio.h"
#include <future>

class socket_tcp : public asio::Nsocket_tcp
{
protected:
	virtual void on_connect() {}
	virtual void on_disconnect() noexcept {}
	virtual int on_message(const const_buffer& /*_msg*/) { return 0; }
};

class test_tcp_echo_client
{
public:
			test_tcp_echo_client();
	virtual ~test_tcp_echo_client() noexcept;

public:
			void				enable_connect_test(bool _enable = true) noexcept;
			void				toggle_connect_test() noexcept { this->enable_connect_test(!this->m_enable_connect_test); }
			void				enable_traffic_test(bool _enable = true) noexcept;
			void				toggle_traffic_test() noexcept { this->enable_traffic_test(!this->m_enable_traffic_test); }
			void				enable_relay_echo_test(bool _enable = true) noexcept { this->m_enable_relay_echo_test = _enable; }
			void				toggle_relay_echo_test() noexcept { this->enable_relay_echo_test(!this->m_enable_relay_echo_test); }
			void				enable_disconnect_on_response(bool _enable = true) noexcept { this->m_enable_disconnect_on_response = _enable; }
			void				toggle_disconnect_on_response() noexcept { this->enable_disconnect_on_response(!this->m_enable_disconnect_on_response); }

			void				add_traffic_test_count_per_single(int64_t _count) noexcept;
			void				sub_traffic_test_count_per_single(int64_t _count) noexcept;
			void				set_traffic_test_count_per_single(int64_t _count) noexcept;

			void				increase_traffic_test_message_size();
			void				decrease_traffic_test_message_size();
			void				set_traffic_test_message_size(std::size_t _index);

			void				add_connect_test_min(int64_t _count) noexcept;
			void				sub_connect_test_min(int64_t _count) noexcept;
			void				set_connect_test_min(int64_t _count) noexcept;
			void				add_connect_test_max(int64_t _count) noexcept;
			void				sub_connect_test_max(int64_t _count) noexcept;
			void				set_connect_test_max(int64_t _count) noexcept;

			void				set_endpoint(boost::asio::ip::tcp::endpoint _endpoint);
			bool				set_endpoint(const std::string& _address, const std::string& _port);
			const auto&			get_endpoint() const noexcept { return this->m_endpoint_connect; }

			void				request_connect(int64_t _count);
			void				request_closesocket(int64_t _count);
			void				request_closesocket_all();
			void				request_disconnect_socket(int64_t _count);
			void				request_disconnect_socket_all();
			void				request_send();
			void				request_send_immidiately(int64_t _count);
			void				request_send_error_message_zero();

public:
	// 1) connect test
			bool				m_enable_connect_test = false;
			int64_t				m_connect_test_min = 0;
			int64_t				m_connect_test_max = 0;

	// 2) send test
			std::atomic<uint64_t> m_traffic_send_requested = 0;
			bool				m_enable_traffic_test = false;
			std::size_t			m_traffic_test_selected = 0;
			int64_t				m_traffic_test_count_per_single = 0;
			mutable_buffer		m_traffic_test_buf_message[11]{};

			bool				m_is_thread_run = false;
			std::future<void>	m_result_future;
			std::unique_ptr<std::thread> m_thread_process;

	static	bool				m_enable_relay_echo_test;
	static	bool				m_enable_disconnect_on_response;

	// 3) connector
			boost::asio::ip::tcp::endpoint m_endpoint_connect;
			std::shared_ptr<asio::connector<socket_tcp>> m_pconnector_socket;

public:
	virtual	void				start();
	virtual	void				destroy();

public:
			void				process_execute();
			void				process_execute_send();

			void				process_connect_test();
			void				process_traffic_test();

			void				process_connect_request(int64_t _n);
			void				process_send_message(std::size_t _index, int64_t _count);
			void				process_send_message(mutable_buffer _buffer);
			void				process_ready_send_test_message(std::size_t _index);
};
