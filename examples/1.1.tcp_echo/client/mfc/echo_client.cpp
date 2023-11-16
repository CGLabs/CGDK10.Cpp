#include "pch.h"
#include "echo_client.h"

bool test_tcp_echo_client::m_enable_relay_echo_test = false;
bool test_tcp_echo_client::m_enable_disconnect_on_response = false;
own_ptr<test_tcp_echo_client> g_ptest_tcp_echo_client;


void socket_tcp::on_connect()
{
	if (test_tcp_echo_client::m_enable_disconnect_on_response == true)
	{
		this->send(g_ptest_tcp_echo_client->m_traffic_test_buf_message[g_ptest_tcp_echo_client->m_traffic_test_selected]);
	}
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	if (test_tcp_echo_client::m_enable_disconnect_on_response == true)
	{
		this->closesocket();
		return eRESULT::DONE;
	}

	if (test_tcp_echo_client::m_enable_relay_echo_test == true)
	{
		this->send(_msg.buf_message);
	}

	return eRESULT::DONE;
}

void test_tcp_echo_client::add_connect_test_min(int64_t _count) noexcept
{
	this->m_connect_test_min += _count;

	if (this->m_connect_test_min > this->m_connect_test_max)
		this->m_connect_test_max = this->m_connect_test_min;
}
void test_tcp_echo_client::sub_connect_test_min(int64_t _count) noexcept
{
	if (this->m_connect_test_min < _count)
		this->m_connect_test_min = 0;
	else
		this->m_connect_test_min -= _count;
}
void test_tcp_echo_client::set_connect_test_min(int64_t _count) noexcept
{
	this->m_connect_test_max = _count;
}

void test_tcp_echo_client::add_connect_test_max(int64_t _count) noexcept
{
	this->m_connect_test_max += _count;
}
void test_tcp_echo_client::sub_connect_test_max(int64_t _count) noexcept
{
	if (this->m_connect_test_max < 100 + _count)
		this->m_connect_test_max = 100;
	else
		this->m_connect_test_max -= _count;

	if (this->m_connect_test_max < this->m_connect_test_min)
	{
		this->m_connect_test_min = this->m_connect_test_max;
	}
}
void test_tcp_echo_client::set_connect_test_max(int64_t _count) noexcept
{
	this->m_connect_test_max = _count;
}

void test_tcp_echo_client::enable_connect_test(bool _enable) noexcept
{
	// check)
	RETURN_IF(m_enable_connect_test == _enable)

	// 1) set flag
	this->m_enable_connect_test = _enable;
}
void test_tcp_echo_client::enable_traffic_test(bool _enable) noexcept
{
	// check)
	RETURN_IF(this->m_enable_traffic_test == _enable)

	// 1) set flag
	this->m_enable_traffic_test = _enable;

	if (_enable == false)
	{
		this->m_traffic_send_requested = 0;
	}
}

void test_tcp_echo_client::add_traffic_test_count_per_single(int64_t _count) noexcept
{
	this->m_traffic_test_count_per_single += _count;
}

void test_tcp_echo_client::sub_traffic_test_count_per_single(int64_t _count) noexcept
{
	if ((this->m_traffic_test_count_per_single + 1)  > _count)
	{
		this->m_traffic_test_count_per_single -= _count;
	}
	else
	{
		this->m_traffic_test_count_per_single  = 1;
	}
}

void test_tcp_echo_client::set_traffic_test_count_per_single(int64_t _count) noexcept
{
	if (_count > 1)
	{
		this->m_traffic_test_count_per_single = _count;
	}
	else
	{
		this->m_traffic_test_count_per_single = 1;
	}
}

void test_tcp_echo_client::increase_traffic_test_message_size()
{
	RETURN_IF(this->m_traffic_test_selected >= 10);

	++this->m_traffic_test_selected;

	this->process_ready_send_test_message(this->m_traffic_test_selected);
}

void test_tcp_echo_client::decrease_traffic_test_message_size()
{
	RETURN_IF(this->m_traffic_test_selected == 0);

	--this->m_traffic_test_selected;

	this->process_ready_send_test_message(this->m_traffic_test_selected);
}
void test_tcp_echo_client::set_traffic_test_message_size(std::size_t _index)
{
	RETURN_IF(this->m_traffic_test_selected >= 10);
	RETURN_IF(this->m_traffic_test_selected == _index);

	this->m_traffic_test_selected = _index;

	this->process_ready_send_test_message(this->m_traffic_test_selected);
}

void test_tcp_echo_client::request_connect(int64_t _count)
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			for (int64_t i = 0; i < _count; i++)
			{
				pthis->m_pconnector_socket->request_connect(pthis->m_endpoint_connect);
			}
		}));
}

void test_tcp_echo_client::request_closesocket(int64_t _count)
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			int64_t disconnected = 0;

			scoped_lock(pthis->m_pconnector_socket->get_lockable())
			{
				// 주의) closesocket을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
				//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

				auto iter = pthis->m_pconnector_socket->begin();
				auto iter_end = pthis->m_pconnector_socket->end();

				while (iter != iter_end)
				{
					auto iter_now = iter++;

					if ((*iter_now)->closesocket())
					{
						BREAK_IF((++disconnected) == _count);
					}
				}
			}
		}));
}

void test_tcp_echo_client::request_closesocket_all()
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			pthis->m_pconnector_socket->close_connectable_all();
		}));
}

void test_tcp_echo_client::request_disconnect_socket(int64_t _count)
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			int64_t disconnected = 0;

			scoped_lock(pthis->m_pconnector_socket->get_lockable())
			{
				// 주의) disconnect을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
				//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

				auto iter = pthis->m_pconnector_socket->begin();
				auto iter_end = pthis->m_pconnector_socket->end();

				while (iter != iter_end)
				{
					auto iter_now = iter++;

					if ((*iter_now)->disconnect())
					{
						BREAK_IF((++disconnected) == _count);
					}
				}
			}
		}));
}

void test_tcp_echo_client::request_disconnect_socket_all()
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			pthis->m_pconnector_socket->disconnect_connectable_all();
		}));
}

void test_tcp_echo_client::request_send()
{
	// 1) ...
	auto value = ++this->m_traffic_send_requested;

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

void test_tcp_echo_client::request_send_immidiately(int64_t _count)
{
	// 1) send
	this->process_send_message(m_traffic_test_selected, _count);
}

void test_tcp_echo_client::request_send_error_message_zero()
{
	auto tempBuffer = alloc_shared_buffer(256);
	tempBuffer.append<uint32_t>(0);
	tempBuffer.append<uint32_t>(1);

	this->process_send_message(tempBuffer);
}

void test_tcp_echo_client::on_starting(context& /*_context*/)
{
	// 1) connect test
	this->m_enable_connect_test = false;
	this->m_connect_test_min = 500;
	this->m_connect_test_max = 800;

	// 2) send test
	this->m_traffic_send_requested = 0;
	this->m_enable_traffic_test = false;
	this->m_traffic_test_selected = 0;
	this->m_traffic_test_count_per_single = 200;

	// 3) ready messges for send test
	this->process_ready_send_test_message(m_traffic_test_selected);

	// 4) Connector를 생성한다.
	this->m_pconnector_socket = make_own<net::connector<socket_tcp>>();
	//this->m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::tcp::resolver().resolve("localhost", "20000") };
	this->m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::address_v4::loopback(), 20000 };
	//this->m_endpoint_connect = net::ip::tcp::endpoint{ net::ip::address_v6::loopback(), 20000 };

	// 5) disable test
	this->enable_connect_test(false);
	this->enable_traffic_test(false);

	// 6) Connector를 시작한다.
	this->m_pconnector_socket->start();

	// 7) start schedulable
	system_executor::register_schedulable(this);
}

struct TEST_MESSAGE_TYPE
{
	std::size_t size;
	int64_t count;
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

CGDK::shared_buffer generate_message(size_t _message_size, int64_t _count)
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
	for (int64_t j = 0; j < _count; ++j)
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
	RETURN_IF(this->m_traffic_test_buf_message[_index].exist());

	// check)
	RETURN_IF(this->m_enable_relay_echo_test == true);

	// 1) get message_buffer
	this->m_traffic_test_buf_message[_index] = generate_message(g_test_message_info[_index].size, g_test_message_info[_index].count);
}

void test_tcp_echo_client::on_stopping()
{
	// 1) disable test
	this->m_enable_connect_test = false;
	this->m_enable_traffic_test = false;

	// 2) unregister...
	system_executor::unregister_schedulable(this);

	// 3) destry
	this->m_pconnector_socket->destroy();
}

void test_tcp_echo_client::process_execute_send()
{
	// check)
	CGASSERT_ERROR(this->m_traffic_test_count_per_single != 0);

	// 1) send
	process_send_message(this->m_traffic_test_selected, this->m_traffic_test_count_per_single);

	// check)
	RETURN_IF(this->m_enable_traffic_test == false);

	// 2) ...
	auto value = --this->m_traffic_send_requested;

	// check) 0이 아닐 경우 또 걸기...
	if (value != 0)
	{
		object_ptr<test_tcp_echo_client> pthis(this);

		system_executor::post(make_executable([=]() 
		{
			pthis->process_execute_send();
		}));
	}
}

intptr_t test_tcp_echo_client::process_execute(intptr_t /*_return*/, std::size_t /*_param*/)
{
	// 1) traffice test
	this->process_traffic_test();

	// 2) connection test
	this->process_connect_test();

	// return) 
	return 0;
}

void test_tcp_echo_client::process_connect_test()
{
	// check) 
	RETURN_IF(this->m_enable_connect_test == false);

	// 1) disconnect
	int64_t disconnected = 0;

	scoped_lock(this->m_pconnector_socket->get_lockable())
	{
		auto count_socket = static_cast<int64_t>(this->m_pconnector_socket->count());

		if (count_socket > this->m_connect_test_min)
		{
			int64_t range = count_socket - this->m_connect_test_min;
			int64_t disconnect = (range) ? rand() % range : 0;

			// 주의) closesocket을 할 경우 m_pconnector의 connectable_list에서 제거될수 있어
			//       iterator 무효화 현상이 발생할 수 있으므로 반드시 iterator 무효화에 대비해 처리해야 한다.

			auto iter = this->m_pconnector_socket->begin();
			auto iter_end = this->m_pconnector_socket->end();

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
		auto count_socket = static_cast<int64_t>(this->m_pconnector_socket->allocated_socket_count()) - disconnected;

		int64_t nConnect;
		if (count_socket < this->m_connect_test_min)
		{
			// - min connect보다 낮을 시 min connect만큼 한꺼번에 접속한다.
			nConnect = this->m_connect_test_min - count_socket;
		}
		else if (count_socket < this->m_connect_test_max)
		{
			auto range = this->m_connect_test_max - count_socket;

			// - 최대 여유 remained/8(12.5%)의 값을 신규로 접속시도한다.
			nConnect = (range) ? rand() % range : 0;
		}
		else
		{
			nConnect = 0;
		}

		this->process_connect_request(nConnect);
	}
}

void test_tcp_echo_client::process_traffic_test()
{
	// check)
	RETURN_IF(this->m_enable_traffic_test == false);

	// 1) send 
	this->request_send();
}

void test_tcp_echo_client::process_connect_request(int64_t _count)
{
	// hold)
	object_ptr<test_tcp_echo_client> pthis = this;

	// post!
	system_executor::post(make_executable([=]()
		{
			for (int64_t i = 0; i < _count; i++)
			{
				pthis->m_pconnector_socket->request_connect(pthis->m_endpoint_connect);
			}
		}));
}

void test_tcp_echo_client::process_send_message(std::size_t _index, int64_t _count)
{
	try
	{
		// check) 
		if (_index >= 11)
			return;

		// check) 
		if (_count <= 0)
			return;

		const auto message_info = g_test_message_info[_index];
		auto buf_message = this->m_traffic_test_buf_message[_index];

		// check)
		if (message_info.count <= 0)
			return;

		std::vector<object_ptr< socket_tcp>> vector_socket;

		scoped_lock(this->m_pconnector_socket->get_lockable())
		{
			vector_socket.reserve(this->m_pconnector_socket->count());

			for (auto& iter : *this->m_pconnector_socket)
			{
				vector_socket.push_back(iter);
			}
		}

		for (auto& iter: vector_socket)
		{
			auto nSend = _count;
			auto buf_send = buf_message;

			for (; nSend >= message_info.count; nSend -= message_info.count)
			{
				auto result = iter->send({ buf_send, static_cast<uint64_t>(message_info.count) });

				if (result == false)
					break;
			}

			if (nSend > 0)
			{
				buf_send.set_size(message_info.size * nSend);
				iter->send({ buf_send, static_cast<uint64_t>(nSend) });
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
		scoped_lock(this->m_pconnector_socket->get_lockable())
		{
			for (auto& iter : *this->m_pconnector_socket)
			{
				iter->send(_buffer);
			}
		}
	}
	catch (...)
	{
	}
}