#include "pch.h"
#include "echo_client.h"

own_ptr<test_tcp_echo_client> g_ptest_tcp_echo_client;


void socket_tcp::on_connect()
{
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& /*_msg*/)
{
	return eRESULT::DONE;
}

void test_tcp_echo_client::add_connect_test_min(std::size_t _count) noexcept
{
	m_connect_test_min += _count;

	if (m_connect_test_min > m_connect_test_max)
		m_connect_test_max = m_connect_test_min;
}
void test_tcp_echo_client::sub_connect_test_min(std::size_t _count) noexcept
{
	if (m_connect_test_min < _count)
		m_connect_test_min = 0;
	else
		m_connect_test_min -= _count;
}
void test_tcp_echo_client::set_connect_test_min(std::size_t _count) noexcept
{
	m_connect_test_max = _count;
}

void test_tcp_echo_client::add_connect_test_max(std::size_t _count) noexcept
{
	m_connect_test_max += _count;
}
void test_tcp_echo_client::sub_connect_test_max(std::size_t _count) noexcept
{
	if (m_connect_test_max < 100 + _count)
		m_connect_test_max = 100;
	else
		m_connect_test_max -= _count;

	if (m_connect_test_max < m_connect_test_min)
	{
		m_connect_test_min = m_connect_test_max;
	}
}
void test_tcp_echo_client::set_connect_test_max(std::size_t _count) noexcept
{
	m_connect_test_max = _count;
}

void test_tcp_echo_client::set_endpoint(net::ip::tcp::endpoint _endpoint)
{
	m_endpoint_connect = _endpoint;
}

bool test_tcp_echo_client::set_endpoint(const std::string& _address, const std::string& _port)
{
	if (_address.empty() == false && _port.empty() == false)
	{
		// 1) ...
		auto result = net::ip::tcp::resolver().resolve(_address, _port);

		// check)
		RETURN_IF(result.size() == 0, false);

		// 2) set endpoint
		m_endpoint_connect = result.at(0);
	}
	else if (_address.empty() == false)
	{
		// 1) ...
		auto result = net::ip::tcp::resolver().resolve(_address);

		// check)
		RETURN_IF(result.size() == 0, false);

		// 2) set endpoint
		m_endpoint_connect.address(result.at(0).endpoint().address());
	}
	else if (_port.empty() == false)
	{
		m_endpoint_connect.port(static_cast<unsigned short>(std::stoi(_port)));
	}

	// return)
	return true;
}

void test_tcp_echo_client::enable_connect_test(bool _enable) noexcept
{
	// check)
	RETURN_IF(m_enable_connect_test == _enable)

	// 1) set flag
	m_enable_connect_test = _enable;
}
void test_tcp_echo_client::enable_traffic_test(bool _enable) noexcept
{
	// check)
	RETURN_IF(m_enable_traffic_test == _enable)

	// 1) set flag
	m_enable_traffic_test = _enable;

	if (_enable == false)
	{
		m_traffic_send_requested = 0;
	}
}

void test_tcp_echo_client::add_traffic_test_count_per_single(std::size_t _count) noexcept
{
	m_traffic_test_count_per_single += _count;
}

void test_tcp_echo_client::sub_traffic_test_count_per_single(std::size_t _count) noexcept
{
	if ((m_traffic_test_count_per_single + 1)  > _count)
	{
		m_traffic_test_count_per_single -= _count;
	}
	else
	{
		m_traffic_test_count_per_single  = 1;
	}
}

void test_tcp_echo_client::set_traffic_test_count_per_single(std::size_t _count) noexcept
{
	if (_count > 1)
	{
		m_traffic_test_count_per_single = _count;
	}
	else
	{
		m_traffic_test_count_per_single = 1;
	}
}

void test_tcp_echo_client::increase_traffic_test_message_size()
{
	RETURN_IF(m_traffic_test_selected >= 10);

	++m_traffic_test_selected;

	process_ready_send_test_message(m_traffic_test_selected);
}

void test_tcp_echo_client::decrease_traffic_test_message_size()
{
	RETURN_IF(m_traffic_test_selected == 0);

	--m_traffic_test_selected;

	process_ready_send_test_message(m_traffic_test_selected);
}
void test_tcp_echo_client::set_traffic_test_message_size(std::size_t _index)
{
	RETURN_IF(m_traffic_test_selected >= 10);
	RETURN_IF(m_traffic_test_selected == _index);

	m_traffic_test_selected = _index;

	process_ready_send_test_message(m_traffic_test_selected);
}

void test_tcp_echo_client::request_connect(std::size_t _count)
{
	for (std::size_t i = 0; i < _count; i++)
	{
		m_pconnector_socket->request_connect(m_endpoint_connect);
	}
}

void test_tcp_echo_client::request_closesocket(std::size_t _count)
{
	std::size_t disconnected = 0;

	scoped_lock(m_pconnector_socket->get_lockable())
	{
		// 주의) closesocket을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
		//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

		auto iter = m_pconnector_socket->begin();
		auto iter_end = m_pconnector_socket->end();

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

void test_tcp_echo_client::request_closesocket_all()
{
	m_pconnector_socket->close_connectable_all();
}

void test_tcp_echo_client::request_disconnect_socket(std::size_t _count)
{
	std::size_t disconnected = 0;

	scoped_lock(m_pconnector_socket->get_lockable())
	{
		// 주의) disconnect을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
		//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

		auto iter = m_pconnector_socket->begin();
		auto iter_end = m_pconnector_socket->end();

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

void test_tcp_echo_client::request_disconnect_socket_all()
{
	m_pconnector_socket->disconnect_connectable_all();
}

void test_tcp_echo_client::request_send()
{
	// 1) ...
	auto value = ++m_traffic_send_requested;

	// check) iPre가 1이면 Interlocked걸기.
	if (value == 1)
	{
		object_ptr<test_tcp_echo_client> self(this);

		system_executor::post(make_executable([=]()
		{
			self->process_execute_send();
		}));
	}
}

void test_tcp_echo_client::request_send_immidiately(std::size_t _count)
{
	// 1) send
	process_send_message(m_traffic_test_selected, _count);
}

void test_tcp_echo_client::request_send_error_message_zero()
{
	auto tempBuffer = alloc_shared_buffer(256);
	tempBuffer.append<uint32_t>(0);
	tempBuffer.append<uint32_t>(1);

	process_send_message(tempBuffer);
}

void test_tcp_echo_client::on_starting(context& /*_context*/)
{
	// 1) connect test
	m_enable_connect_test = false;
	m_connect_test_min = 500;
	m_connect_test_max = 800;

	// 2) send test
	m_traffic_send_requested = 0;
	m_enable_traffic_test = false;
	m_traffic_test_selected = 0;
	m_traffic_test_count_per_single = 30;

	// 3) ready messges for send test
	process_ready_send_test_message(m_traffic_test_selected);

	// 4) Connector를 생성한다.
	m_pconnector_socket = make_own<net::connector<socket_tcp>>();
	m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::address_v4::loopback(), 20000 };
	//m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::address_v6::loopback(), 20000 };

	// 5) disable test
	enable_connect_test(false);
	enable_traffic_test(false);

	// 6) Connector를 시작한다.
	m_pconnector_socket->start();

	// 7) start schedulable
	system_executor::register_schedulable(this);
}

struct TEST_MESSAGE_TYPE
{
	std::size_t size;
	std::size_t count;
};

#define BUFFER_SIZE_SCALE 2
#define TEST_MESSAGE_TYPE_COUNT 12
const TEST_MESSAGE_TYPE g_test_message_info[TEST_MESSAGE_TYPE_COUNT]
{
	{                8, 1024 * 1024 * BUFFER_SIZE_SCALE}, // 0:   8 byte
	{               64,  256 * 1024 * BUFFER_SIZE_SCALE}, // 1:  64 byte
	{              256,   64 * 1024 * BUFFER_SIZE_SCALE}, // 2: 256 byte
	{             1024,   16 * 1024 * BUFFER_SIZE_SCALE}, // 3:  1K byte
	{         4 * 1024,    2 * 1024 * BUFFER_SIZE_SCALE}, // 4:  4K byte
	{        16 * 1024,    1 * 1024 * BUFFER_SIZE_SCALE}, // 5: 16K byte
	{        64 * 1024,         256 * BUFFER_SIZE_SCALE}, // 6: 64K byte
	{       256 * 1024,          64 * BUFFER_SIZE_SCALE}, // 6:256K byte
	{  1 * 1024 * 1024,          16 * BUFFER_SIZE_SCALE}, // 7:  1M byte
	{  4 * 1024 * 1024,           4 * BUFFER_SIZE_SCALE}, // 8:  4M byte
	{ 32 * 1024 * 1024,           1},                     // 9: 32M byte
	{256 * 1024 * 1024,           1}                      // 10:256M byte
};

CGDK::shared_buffer generate_message(size_t _message_size, size_t _count)
{
	// check)
	CGASSERT_ERROR(_message_size > 0);

	auto buffer_temp = alloc_shared_buffer(_message_size);
	buffer_temp.append<uint32_t>(static_cast<uint32_t>(_message_size));
	for (std::size_t k = 0; k < (_message_size - 8); k += sizeof(uint32_t))
		buffer_temp.append<uint32_t>(rand());
	buffer_temp.front<uint32_t>() = static_cast<uint32_t>(buffer_temp.size() + SIZE_OF_CRC);
	buffer_temp.append(crc());

	auto buf_message = alloc_shared_buffer(_message_size * _count);
	for (std::size_t j = 0; j < _count; ++j)
	{
		buf_message += buffer_temp;
	}

	return buf_message;
}

void test_tcp_echo_client::process_ready_send_test_message(std::size_t _index)
{
	// check)
	CGASSERT_ERROR(_index < TEST_MESSAGE_TYPE_COUNT);

	// check)
	THROW_IF(_index >= TEST_MESSAGE_TYPE_COUNT, std::exception());

	// check)
	RETURN_IF(m_traffic_test_buf_message[_index].exist());

	// 1) get message_buffer
	m_traffic_test_buf_message[_index] = generate_message(g_test_message_info[_index].size, g_test_message_info[_index].count);
}

void test_tcp_echo_client::on_stopping()
{
	// 1) disable test
	m_enable_connect_test = false;
	m_enable_traffic_test = false;

	// 2) unregister...
	system_executor::unregister_schedulable(this);

	// 3) destry
	m_pconnector_socket->destroy();
}

void test_tcp_echo_client::process_execute_send()
{
	// check)
	CGASSERT_ERROR(m_traffic_test_count_per_single != 0);

	// 1) send
	process_send_message(m_traffic_test_selected, m_traffic_test_count_per_single);

	// check)
	RETURN_IF(m_enable_traffic_test == false);

	// 2) ...
	auto value = --m_traffic_send_requested;

	// check) 0이 아닐 경우 또 걸기...
	if (value != 0)
	{
		object_ptr<test_tcp_echo_client> self(this);

		system_executor::post(make_executable([=]() 
		{
			self->process_execute_send();
		}));
	}
}

intptr_t test_tcp_echo_client::process_execute(intptr_t /*_return*/, std::size_t /*_param*/)
{
	// 1) traffice test
	process_traffic_test();

	// 2) connection test
	process_connect_test();

	// return) 
	return 0;
}

void test_tcp_echo_client::process_connect_test()
{
	// check) 
	RETURN_IF(m_enable_connect_test == false);

	// 1) disconnect
	std::size_t disconnected = 0;

	scoped_lock(m_pconnector_socket->get_lockable())
	{
		auto count_socket = m_pconnector_socket->count();

		if (count_socket > m_connect_test_min)
		{
			std::size_t range = count_socket - m_connect_test_min;
			std::size_t disconnect = (range) ? rand() % range : 0;

			// 주의) closesocket을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
			//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

			auto iter = m_pconnector_socket->begin();
			auto iter_end = m_pconnector_socket->end();

			while(iter != iter_end)
			{
				auto iter_now = iter++;

				if ((*iter_now)->closesocket())
				{
					BREAK_IF((++disconnected) == disconnect);
				}
			}
		}
	}

	// 2) connect
	{
		auto count_socket = m_pconnector_socket->allocated_socket_count() - disconnected;

		std::size_t nConnect;
		if (count_socket < m_connect_test_min)
		{
			// MinConnect보다 낮을 시 Min Connect만큼 한꺼번에 접속해버린다.
			nConnect = m_connect_test_min - count_socket;
		}
		else if (count_socket < m_connect_test_max)
		{
			auto range = m_connect_test_max - count_socket;

			// 여유최대 Remained/8(12.5%)의 값을 신규로 접속시도한다.
			nConnect = (range) ? rand() % range : 0;
		}
		else
		{
			nConnect = 0;
		}

		process_connect(nConnect);
	}
}

void test_tcp_echo_client::process_traffic_test()
{
	// check)
	RETURN_IF(m_enable_traffic_test == false);

	// 1) send 
	request_send();
}

void test_tcp_echo_client::process_connect(std::size_t _n)
{
	// 1) 접속한다.
	for (std::size_t i = 0; i < _n; i++)
	{
		m_pconnector_socket->request_connect(m_endpoint_connect);
	}
}

void test_tcp_echo_client::process_send_message(std::size_t _index, std::size_t _count)
{
	try
	{
		const auto message_info = g_test_message_info[_index];
		auto buf_message = m_traffic_test_buf_message[_index];

		scoped_lock(m_pconnector_socket->get_lockable())
		{
			for (auto& iter : *m_pconnector_socket)
			{
				std::size_t	nSend = _count;
				auto buf_send = buf_message;

				for (; nSend >= message_info.count; nSend -= message_info.count)
				{
					iter->send({ buf_send, message_info.count });
				}

				if (nSend != 0)
				{
					buf_send.set_size(message_info.size * nSend);
					iter->send({ buf_send, nSend });
				}
			}
		}
	}
	catch (...)
	{
	}
}

void test_tcp_echo_client::process_send_message(shared_buffer _buffer)
{
	try
	{
		scoped_lock(m_pconnector_socket->get_lockable())
		{
			for (auto& iter : *m_pconnector_socket)
			{
				iter->send(_buffer);
			}
		}
	}
	catch (...)
	{
	}
}