#include "pch.h"

void print_title();
void print_statistics_info();

mutable_buffer make_message(size_t _size)
{
	// check) 
	assert(_size % 4 == 0);

	// - alloc buffer
	char* buf_temp = reinterpret_cast<char*>(::malloc(_size));

	// - make message
	auto buf_append = buf_temp;
	*(uint32_t*)buf_append = static_cast<uint32_t>(_size); buf_append += sizeof(uint32_t);
	*(uint32_t*)buf_append = 0; buf_append += sizeof(uint32_t);
	for (auto buf_end = buf_temp + _size; buf_append < buf_end; buf_append += sizeof(uint32_t))
	{
		*(uint32_t*)buf_append = 0;
	}

	return { buf_temp, _size };
}

int main()
{
	// 1) print title
	print_title();

	// declare) 
	std::shared_ptr<asio::acceptor<socket_tcp>> pacceptor;

	try
	{
		// 1) create boost tcp echo server
		pacceptor = std::make_shared<asio::acceptor<socket_tcp>>();

		// 2) start accept
		pacceptor->start(tcp::endpoint{ boost::asio::ip::tcp::v6(), 20000 });
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: "sv << e.what() << '\n';
	}

	// 3) wait press any key 
	for (;;)
	{
		// - output traffic info
		print_statistics_info();

		// - key pressed
		if (_kbhit())
		{
			// - get key value
			int	ch = _getch();

			// - exit if esc key
			if (ch == 27)
				break;

			switch (ch)
			{
			// disconnect
			case	'6':
					{
						std::unique_lock cs(pacceptor->get_lockable());

						if (pacceptor->count() != 0)
						{
							(*pacceptor->begin())->closesocket();
						}
					}
					break;
			case	'7':
					pacceptor->close_connectable_all();
					break;

			// closesocket
			case	'8':
					{
						std::unique_lock cs(pacceptor->get_lockable());

						if (pacceptor->count() != 0)
						{
							(*pacceptor->begin())->disconnect();
						}
					}
					break;
			case	'9':
					pacceptor->disconnect_connectable_all();
					break;

		#if defined(_WIN32)
			case	0xe0:
					{
						// - extended key (for windows)
						/*auto key = */_getch();
					}
					break;
		#endif
			}
		}

		// - sleep
		std::this_thread::sleep_for(100ms);
	}

	// 4) close asio 
	pacceptor.reset();

	// 5) exit
	std::cout << "\x1b[4B\n tcp echo server closed...\n"sv;
}

void print_title()
{
	// 1) initialization
	std::ostringstream buf_output;
	buf_output.str().reserve(8192);
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	buf_output << "     boost.asio tcp echo relay test\n"sv;
	buf_output << "\n"sv;
	buf_output << "\n"sv;
	buf_output << "  [command]\n"sv;
	buf_output << "\n"sv;
	buf_output << "   \x1b[90m- close session\x1b[0m		'6'(-1), '7'(all)\n"sv;
	buf_output << "   \x1b[90m- disconnect session\x1b[0m		'8'(-1), '9'(all)\n"sv;
	buf_output << "\n"sv;
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	std::cout << buf_output.str();
}

void print_statistics_info()
{
	// 1) 현재 Tick과 Tick Gap을 구한다.
	static auto tick_last = std::chrono::steady_clock::time_point(std::chrono::steady_clock::duration::zero());
	auto tick_now = std::chrono::steady_clock::now();
	auto tick_differ = std::chrono::duration_cast<std::chrono::milliseconds>(tick_now - tick_last);

	// check) tickdiffer가 10ms이하면 그냥 끝낸다.
	if (tick_differ < 1s)
		return;

	// 2) 최종 시간을 Update한다.
	tick_last = tick_now;

	// 3) alloc buffer
	std::ostringstream buf_output;
	buf_output.str().reserve(8192);

	// 4) connection info
	{
		// declare) 
		static uint64_t	last_count_try = 0;
		static uint64_t	last_count_success = 0;
		static uint64_t	last_count_disconnected = 0;

		// - 이전과 현재의 차이를 구한다. (Overflow가 났을 경우를 대비하여 계산해야 한다.)
		auto now_count_keep = asio::Nstatistics::statistics_connect_keep.load();
		auto now_count_try = asio::Nstatistics::statistics_connect_try.load();
		auto now_count_success = asio::Nstatistics::statistics_connect_success.load();
		auto now_count_disconnected = asio::Nstatistics::statistics_connect_disconnect.load();

		// - 초당 전송률을 구한다.
		auto total_try_per_sec = ((float)(now_count_try - last_count_try)) * 1000.0f / tick_differ.count();
		auto total_success_per_sec = ((float)(now_count_success - last_count_success)) * 1000.0f / tick_differ.count();
		auto total_disconnected_per_sec = ((float)(now_count_disconnected - last_count_disconnected)) * 1000.0f / tick_differ.count();

		// - 이전 값을 현재 값으로 Update한다.(다음 Frame에서의 계산을 위해)
		last_count_try = now_count_try;
		last_count_success = now_count_success;
		last_count_disconnected = now_count_disconnected;

		// - sended
		buf_output << " [connection]";
		buf_output << "\x1b[1m now \x1b[0m"sv << now_count_keep;
		buf_output << "\x1b[1m   try \x1b[0m"sv << now_count_try;
		buf_output << "\x1b[1m   try/s \x1b[0m"sv << total_try_per_sec;
		buf_output << "\x1b[1m   success/s \x1b[0m"sv << total_success_per_sec;
		buf_output << "\x1b[1m   dis/s \x1b[0m"sv << total_disconnected_per_sec << "\x1b[K\n\n"sv;
	}


	// 5) traffic info
	{
		// declare) 
		static uint64_t	last_count_sended = 0;
		static uint64_t	last_count_received = 0;
		static uint64_t	last_count_sendedByte = 0;
		static uint64_t	last_count_received_byte = 0;

		// - 이전과 현재의 차이를 구한다. (Overflow가 났을 경우를 대비하여 계산해야 한다.)
		auto now_count_sended = asio::Nstatistics::statistics_send_messages.load();
		auto now_count_sendedByte = asio::Nstatistics::statistics_send_bytes.load();
		auto now_count_send_failed = asio::Nstatistics::statistics_send_error.load();
		auto now_count_received = asio::Nstatistics::statistics_receive_messages.load();
		auto now_count_received_byte = asio::Nstatistics::statistics_receive_bytes.load();

		// - 초당 전송률을 구한다.
		auto total_sended_message_per_sec = ((float)(now_count_sended - last_count_sended)) * 1000.0f / tick_differ.count();
		auto total_sended_byte_per_sec = ((float)(now_count_sendedByte - last_count_sendedByte)) * 1000.0f / tick_differ.count();
		auto total_receive_message_per_sec = ((float)(now_count_received - last_count_received)) * 1000.0f / tick_differ.count();
		auto total_receive_byte_per_sec = ((float)(now_count_received_byte - last_count_received_byte)) * 1000.0f / tick_differ.count();

		// - 이전 값을 현재 값으로 Update한다.(다음 Frame에서의 계산을 위해)
		last_count_sended = now_count_sended;
		last_count_sendedByte = now_count_sendedByte;
		last_count_received = now_count_received;
		last_count_received_byte = now_count_received_byte;

		// declare) 
		char temp_string[256] = { 0, };

		// - sended
		buf_output << " [send]    "sv;
		buf_output << "\x1b[90m   messages \x1b[0m"sv << std::setw(12) << now_count_sended;
	#if defined(_WIN32)
		sprintf_s(temp_string, "%.2f", total_sended_message_per_sec);
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
	#else
		sprintf(temp_string, "%.2f", total_sended_message_per_sec);
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
	#endif
		buf_output << "\x1b[90m   bytes/s \x1b[0m"sv << static_cast<uint64_t>(total_sended_byte_per_sec);
		buf_output << "\x1b[90m   failed \x1b[0m"sv << now_count_send_failed << "\x1b[K\n"sv;

		// - received
		buf_output << " [receive] "sv;
		buf_output << "\x1b[90m   messages \x1b[0m"sv << std::setw(12) << now_count_received;
	#if defined(_WIN32)
		sprintf_s(temp_string, "%.2f", total_receive_message_per_sec);
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
	#else
		sprintf(temp_string, "%.2f", total_receive_message_per_sec);
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
	#endif
		buf_output << "\x1b[90m   bytes/s \x1b[0m"sv << static_cast<uint64_t>(total_receive_byte_per_sec) << "\x1b[K\n"sv;
		buf_output << "\n"sv;
	}

	// 3) move cursor
	buf_output << "\x1b[5A"sv;

	// 5) output
	std::cout << buf_output.str();
}
