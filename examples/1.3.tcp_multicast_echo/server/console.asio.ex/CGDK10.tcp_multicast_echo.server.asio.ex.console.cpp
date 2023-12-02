#include "pch.h"


std::unique_ptr<group_test> g_pgroup;
bool g_disable_echo = false;

void print_statistics_info();
void print_setting_info();

shared_buffer make_message(size_t _size)
{
	// check) 
	assert(_size%4 == 0);

	// - alloc buffer
	auto buf = alloc_shared_buffer(_size);

	// - make message
	buf.append<uint32_t>(static_cast<uint32_t>(_size));
	buf.append<uint32_t>(0);
	while(buf.size() < _size)
	{
		buf.append<uint32_t>(0);
	}

	return buf;
}

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	// 1) print title
	std::ostringstream buf_output; 
	buf_output.str().reserve(8192);
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	buf_output << "     boost.asio tcp multi echo server.ex\n"sv;
	buf_output << "\n"sv;
	buf_output << "\n"sv;
	buf_output << "  [command]\n"sv;
	buf_output << "\n"sv;
	buf_output << "   \x1b[90m- close session\x1b[0m		'6'(-1), '7'(all)\n"sv;
	buf_output << "   \x1b[90m- disconnect session\x1b[0m		'8'(-1), '9'(all)\n"sv;
	buf_output << "   \x1b[90m- single send\x1b[0m		'u'(8byte), 'i'(1kbyte), 'o'(64kbyte)\n"sv;
	buf_output << "   \x1b[90m- send gathering\x1b[0m		'\\'\n"sv;
	buf_output << "\n"sv;
	buf_output << "   multi echo test\n"sv;
	buf_output << "   \x1b[90m- echo on/off\x1b[0m		'a'\n"sv;
	buf_output << "\n"sv;
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	std::cout << buf_output.str();

	// declare) 
	std::shared_ptr<asio::acceptor<socket_tcp>> pacceptor;

	// 2) initialization
	try
	{
		// - prepare group
		g_pgroup = std::make_unique<group_test>();;

		// - create boost tcp echo server
		pacceptor = std::make_shared<asio::acceptor<socket_tcp>>();

		// - start accept
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
						std::scoped_lock cs_lock(pacceptor->get_lockable());

						if (pacceptor->count() != 0)
						{
							(*pacceptor->begin())->disconnect();
						}
					}
					break;

			case	'7':
					pacceptor->close_connectable_all();
					break;

			// closesocket
			case	'8':
					{
						std::scoped_lock cs_lock(pacceptor->get_lockable());

						if (pacceptor->count() != 0)
						{
							(*pacceptor->begin())->closesocket();
						}
					}
					break;

			case	'9':
					pacceptor->disconnect_connectable_all();
					break;

			// send
			case	'U':
			case	'u':
					{
						auto buf_send = make_message(8);
						pacceptor->send(buf_send);
						free(buf_send.data());
					}
					break;

			case	'I':
			case	'i':
					{
						auto buf_send = make_message(1024);
						pacceptor->send(buf_send);
						free(buf_send.data());
					}
					break;

			case	'O':
			case	'o':
					{
						auto buf_send = make_message(65536);
						pacceptor->send(buf_send);
						free(buf_send.data());
					}
					break;

			// echo on/off
			case	'a':
					g_disable_echo = !g_disable_echo;
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

			// output setting info
			print_setting_info();
		}

		// - sleep
		std::this_thread::sleep_for(100ms);
	}

	// 5) close asio 
	pacceptor.reset();

	// 5) exit
	std::cout << "\x1b[4B\n tcp echo server closed...\n"sv;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;
}

void _print_setting_info(std::ostringstream& _buffer_output)
{
	// 1) move cursor
	_buffer_output << "\x1b[5B"sv;

	// 2) ...
	_buffer_output << "\x1b[37m [multi echo test]   \x1b[0m"sv;
	_buffer_output << "\x1b[90mecho \x1b[0m"sv << ((g_disable_echo == false) ? "\x1b[47m\x1b[30m on \x1b[0m"sv : "\x1b[90m off\x1b[0m"sv);
	_buffer_output << "\x1b[K\n"sv;

	// 3) move cursor
	_buffer_output << "\x1b[6A"sv;
}

void print_setting_info()
{
	// 1) alloc buffer
	std::ostringstream buf_output;
	buf_output.str().reserve(8192);

	// 2) text
	_print_setting_info(buf_output);

	// 3) write
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
		buf_output << " [connection]"sv;
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
	#else
		sprintf(temp_string, "%.2f", total_sended_message_per_sec);
	#endif
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
		buf_output << "\x1b[90m   bytes/s \x1b[0m"sv << static_cast<uint64_t>(total_sended_byte_per_sec);
		buf_output << "\x1b[90m   failed \x1b[0m"sv << now_count_send_failed << "\x1b[K\n"sv;

		// - received
		buf_output << " [receive] "sv;
		buf_output << "\x1b[90m   messages \x1b[0m"sv << std::setw(12) << now_count_received;
	#if defined(_WIN32)
		sprintf_s(temp_string, "%.2f", total_receive_message_per_sec);
	#else
		sprintf(temp_string, "%.2f", total_receive_message_per_sec);
	#endif
		buf_output << "\x1b[90m   messages/s \x1b[0m"sv << temp_string;
		buf_output << "\x1b[90m   bytes/s \x1b[0m"sv << static_cast<uint64_t>(total_receive_byte_per_sec) << "\x1b[K\n"sv;
		buf_output << "\n"sv;
	}

	// 3) move cursor
	buf_output << "\x1b[5A"sv;

	// 4) setting info
	_print_setting_info(buf_output);

	// 5) output
	std::cout << buf_output.str();
}
