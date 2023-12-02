#include "pch.h"
#include "echo_client.h"

own_ptr<test_tcp_relay_echo_client> g_ptest_tcp_relay_echo_client;


void socket_tcp::on_connect()
{
	this->send(g_ptest_tcp_relay_echo_client->m_buf_message[g_ptest_tcp_relay_echo_client->m_selected_message_size]);
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	this->send(_msg.buf_message);

	return eRESULT::DONE;
}

void test_tcp_relay_echo_client::set_endpoint(net::ip::tcp::endpoint _endpoint)
{
	this->m_endpoint_connect = _endpoint;
}

bool test_tcp_relay_echo_client::set_endpoint(const std::string& _address, const std::string& _port)
{
	if (_address.empty() == false && _port.empty() == false)
	{
		// 1) ...
		auto result = net::ip::tcp::resolver().resolve(_address, _port);

		// check)
		RETURN_IF(result.size() == 0, false);

		// 2) set endpoint
		this->m_endpoint_connect = result.at(0);
	}
	else if (_address.empty() == false)
	{
		// 1) ...
		auto result = net::ip::tcp::resolver().resolve(_address);

		// check)
		RETURN_IF(result.size() == 0, false);

		// 2) set endpoint
		this->m_endpoint_connect.address(result.at(0).endpoint().address());
	}
	else if (_port.empty() == false)
	{
		this->m_endpoint_connect.port(static_cast<unsigned short>(std::stoi(_port)));
	}

	// return)
	return true;
}

void test_tcp_relay_echo_client::increase_message_size()
{
	RETURN_IF(this->m_selected_message_size >= 10);

	++this->m_selected_message_size;
}

void test_tcp_relay_echo_client::decrease_message_size()
{
	RETURN_IF(this->m_selected_message_size == 0);

	--this->m_selected_message_size;
}

void test_tcp_relay_echo_client::set_message_size(std::size_t _index)
{
	RETURN_IF(this->m_selected_message_size >= 10);
	RETURN_IF(this->m_selected_message_size == _index);

	this->m_selected_message_size = _index;
}

void test_tcp_relay_echo_client::request_connect(std::size_t _count)
{
	for (std::size_t i = 0; i < _count; i++)
	{
		this->m_pconnector_socket->request_connect(this->m_endpoint_connect);
	}
}

void test_tcp_relay_echo_client::request_closesocket(std::size_t _count)
{
	std::size_t disconnected = 0;

	scoped_lock(this->m_pconnector_socket->get_lockable())
	{
		// 주의) closesocket을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
		//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

		auto iter = this->m_pconnector_socket->begin();
		auto iter_end = this->m_pconnector_socket->end();

		while (iter != iter_end)
		{
			auto iter_now = iter++;

			if ((*iter_now)->closesocket())
			{
				BREAK_IF((++disconnected) == _count);
			}
		}
	}
}

void test_tcp_relay_echo_client::request_closesocket_all()
{
	this->m_pconnector_socket->close_connectable_all();
}

void test_tcp_relay_echo_client::request_disconnect_socket(std::size_t _count)
{
	std::size_t disconnected = 0;

	scoped_lock(this->m_pconnector_socket->get_lockable())
	{
		// 주의) disconnect을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
		//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

		auto iter = this->m_pconnector_socket->begin();
		auto iter_end = this->m_pconnector_socket->end();

		while (iter != iter_end)
		{
			auto iter_now = iter++;

			if ((*iter_now)->disconnect())
			{
				BREAK_IF((++disconnected) == _count);
			}
		}
	}
}

void test_tcp_relay_echo_client::request_disconnect_socket_all()
{
	this->m_pconnector_socket->disconnect_connectable_all();
}

void test_tcp_relay_echo_client::request_send_immidiately()
{
	this->process_send_message(this->m_selected_message_size);
}

shared_buffer generate_message(size_t _message_size)
{
	// 1) alloc buffer
	auto buffer_temp = alloc_shared_buffer(_message_size);

	// 2) append message size
	buffer_temp.append<uint32_t>(static_cast<uint32_t>(_message_size));

	// 3) append random value 
	for (std::size_t k = 0; k < (_message_size - 8); k += sizeof(uint32_t))
		buffer_temp.append<uint32_t>(rand());

	// 4) set message size
	buffer_temp.front<uint32_t>() = static_cast<uint32_t>(buffer_temp.size() + SIZE_OF_CRC);

	// 5) calculare CRC and append
	buffer_temp.append(crc());

	// return) 
	return buffer_temp;
}

void prepare_message(shared_buffer(&_buf_message)[test_tcp_relay_echo_client::TEST_MESSAGE_TYPE_COUNT])
{
	_buf_message[0] = generate_message(8);
	_buf_message[1] = generate_message(64);
	_buf_message[2] = generate_message(256);
	_buf_message[3] = generate_message(1024);
	_buf_message[4] = generate_message(4* 1024);
	_buf_message[5] = generate_message(16 * 1024);
	_buf_message[6] = generate_message(256 * 1024);
	_buf_message[7] = generate_message(1024 * 1024);
	_buf_message[8] = generate_message(4 * 1024 * 1024);
}

void test_tcp_relay_echo_client::on_starting(context& /*_context*/)
{
	// 1) send test
	this->m_selected_message_size = 0;

	// 2) ready messges for send test
	::prepare_message(m_buf_message);

	// 3) Connector를 생성한다.
	this->m_pconnector_socket = make_own<net::connector<socket_tcp>>();
	this->m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::tcp::resolver().resolve("localhost", "20000") };
	//m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::address_v4::loopback(), 20000 };

	// 4) Connector를 시작한다.
	this->m_pconnector_socket->start();

	// 5) 
	this->m_time_last = std::chrono::system_clock::now();
	const auto& statistics_now = net::io::statistics::Nsocket::statistics_get_traffic_info_total();
	this->m_count_received_message_last = statistics_now.count_received_message.load();
	this->m_count_received_bytes_last = statistics_now.count_received_bytes.load();
	this->m_receive_message_per_sec = 0.0f;
	this->m_receive_byte_per_sec = 0.0f;

	// 6) set execute interval
	this->execute_interval(100ms);

	// 7) register schedulable
	system_executor::register_schedulable(this);
}

struct TEST_MESSAGE_TYPE
{
	std::size_t size;
	std::size_t count;
};

void test_tcp_relay_echo_client::on_stopping()
{
	// 1) unregister schedulable
	system_executor::unregister_schedulable(this);

	// 2) destroy
	this->m_pconnector_socket->destroy();
}

void test_tcp_relay_echo_client::on_execute()
{
	auto time_now = std::chrono::system_clock::now();
	auto time_gap = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - this->m_time_last).count();

	if (time_gap > 1000)
	{
		// - get connector
		auto pconnector = this->m_pconnector_socket.get_object_ptr();

		// check)
		RETURN_IF(pconnector.empty(), );

		// - get connection count
		auto count_socket = pconnector->count();

		// check)
		RETURN_IF(count_socket == 0, );

		const auto& statistics_now = net::io::statistics::Nsocket::statistics_get_traffic_info_total();
		auto count_received_message_now = statistics_now.count_received_message.load();
		auto count_received_bytes_now = statistics_now.count_received_bytes.load();

		this->m_receive_message_per_sec = static_cast<float>(count_received_message_now - this->m_count_received_message_last) / float(time_gap) *1000.0f / count_socket;
		this->m_receive_byte_per_sec = static_cast<float>(m_count_received_bytes_last - this->m_count_received_message_last) / float(time_gap) * 1000.0f / count_socket;

		this->m_count_received_message_last = count_received_message_now;
		this->m_count_received_bytes_last = count_received_bytes_now;
		this->m_time_last = time_now;
	}
}

void test_tcp_relay_echo_client::process_connect(std::size_t _n)
{
	// 1) 접속한다.
	for (std::size_t i = 0; i < _n; i++)
	{
		this->m_pconnector_socket->request_connect(this->m_endpoint_connect);
	}
}

void test_tcp_relay_echo_client::process_send_message(std::size_t _index)
{
	try
	{
		auto buf_message = m_buf_message[_index];

		scoped_lock(this->m_pconnector_socket->get_lockable())
		{
			for (auto& iter : *this->m_pconnector_socket)
			{
				iter->send(buf_message);
			}
		}
	}
	catch (...)
	{
	}
}
