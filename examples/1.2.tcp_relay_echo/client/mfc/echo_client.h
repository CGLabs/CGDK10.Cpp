#pragma once

class socket_tcp : 
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::sendable::Ntcp_sync,
	public				 		net::io::send_request::tcp::Ndefault,
	public						net::io::sender::tcp::Ndefault<uint32_t>,
	public						net::io::receivable::tcp::Ndefault,
	public						net::io::packetable::tcp::Ndefault<uint32_t>,
	public						net::io::messageable::tcp::Ndefault
{
protected:
	virtual void				on_connect() override;
	virtual void				on_fail_connect(uint64_t /*_disconnect_reason*/) override {}
	virtual void				on_disconnect(uint64_t /*_disconnect_reason*/) override {}
	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
};

class test_tcp_relay_echo_client :
	public object::Ninitializable_startable,
	public schedulable::Nexecutable
{
public:
			void				increase_message_size();
			void				decrease_message_size();
			void				set_message_size(std::size_t _index);

			void				set_endpoint(net::ip::tcp::endpoint _endpoint);
			bool				set_endpoint(const std::string& _address, const std::string& _port);
			const auto&			get_endpoint() const noexcept { return m_endpoint_connect; }

			void				request_connect(std::size_t _count);
			void				request_closesocket(std::size_t _count);
			void				request_closesocket_all();
			void				request_disconnect_socket(std::size_t _count);
			void				request_disconnect_socket_all();
			void				request_send_immidiately();

public:
	static const size_t			TEST_MESSAGE_TYPE_COUNT = 9;
			std::size_t			m_selected_message_size = 0;
			shared_buffer		m_buf_message[TEST_MESSAGE_TYPE_COUNT];
			std::chrono::system_clock::time_point m_time_last;
			uint64_t			m_count_received_message_last;
			uint64_t			m_count_received_bytes_last;
			float				m_receive_message_per_sec;
			float				m_receive_byte_per_sec;

			net::ip::tcp::endpoint m_endpoint_connect;
			own_ptr<net::connector<socket_tcp>> m_pconnector_socket;

public:
	virtual	void				on_starting(context& _context) override;
	virtual	void				on_stopping() override;
	virtual	void				on_execute() override;

public:
			void				process_connect(std::size_t _n);
			void				process_send_message(std::size_t _index);
};
