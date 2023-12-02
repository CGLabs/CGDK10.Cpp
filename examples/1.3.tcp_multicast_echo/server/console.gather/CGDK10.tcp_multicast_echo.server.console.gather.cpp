#include "pch.h"
#include <iostream>
#if defined(_WIN32)
#include <conio.h>
#endif

bool g_disable_echo = false;
object_ptr<group_test> g_pgroup;

void print_title();
void print_statistics_info(const statistics::unit_connective& _pstatistics_connective, bool _update_now = false);
void print_setting_info();

#if defined(_WIN32)
# define ASCII_CODE_ENTER		0x0d
# define ASCII_CODE_BACKSPACE	0x08
# define ASCII_CODE_ESCAPE		0x1b
#elif defined(__linux__)
# define ASCII_CODE_ENTER		0x0a
# define ASCII_CODE_BACKSPACE	0x7f
# define ASCII_CODE_ESCAPE		0x1b
#else
# define ASCII_CODE_ENTER		0x0d
# define ASCII_CODE_BACKSPACE	0x08
# define ASCII_CODE_ESCAPE		0x1b
#endif

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	// 1) print title
	print_title();

	// 2) prepare group
	{
		// - make group
		g_pgroup = make_object<group_test>();

		// -enable member entering
		g_pgroup->enable_member_enter();

		// - send gathered messages every 10ms
		g_pgroup->execute_interval(10ms);

		// - scheduler에 group을 붙인다.
		system_executor::register_schedulable(g_pgroup);
	}

	// 2) create acceptor
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 3) listen on 'localhost:20000'
	pacceptor->start({ { net::ip::tcp::v6(), 20000 } });

	// 5) loop
	for (;;)
	{
		// - output traffic info
		print_statistics_info(pacceptor->statistics_get_connective_info_total());

		// - is key pressed?
		if (_kbhit())
		{
			// - get input
			int	ch = _getch();

			// - exit if esc key
			if (ch == 27)
				break;

			switch (ch)
			{
				// disconnect
			case	'6':
				scoped_lock(pacceptor->get_lockable())
				{
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
				scoped_lock(pacceptor->get_lockable())
				{
					if (pacceptor->count() != 0)
					{
						(*pacceptor->begin())->disconnect();
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
				// - alloc buffer
				auto buf_temp = alloc_shared_buffer(8);

				// - write message
				buf_temp.append<uint32_t>(8);
				buf_temp.append(crc());
				// check)
				CGASSERT_ERROR(buf_temp.size() == 8);

				// - send
				pacceptor->send(buf_temp);
			}
			break;

			case	'I':
			case	'i':
			{
				// 2) alloc buffer
				auto buf_temp = alloc_shared_buffer(1024);

				// 3) write message
				buf_temp.append<uint32_t>(1024);
				buf_temp.append<uint32_t>(0);
				while (buf_temp.size() < 1024 - SIZE_OF_CRC)
				{
					buf_temp.append<uint32_t>(0);
				}
				buf_temp.append(crc());

				// - send
				pacceptor->send(buf_temp);
			}
			break;

			case	'O':
			case	'o':
			{
				// - alloc buffer
				auto buf_temp = alloc_shared_buffer(65536);

				// - write message
				buf_temp.append<uint32_t>(65536);
				buf_temp.append<uint32_t>(0);
				while (buf_temp.size() < 65536 - SIZE_OF_CRC)
				{
					buf_temp.append<uint32_t>(0);
				}
				buf_temp.append(crc());

				// check)
				CGASSERT_ERROR(buf_temp.size() == 65536);

				// - send
				pacceptor->send(buf_temp);
			}
			break;

			// echo on/off
			case	'a':
				g_disable_echo = !g_disable_echo;
				break;

			case	'=':
			{
				factory::manager::print_statistics(true);
				std::cout << "\n";
				print_statistics_info(pacceptor->statistics_get_connective_info_total(), true);
			}
			break;

			case	'+':
			{
				factory::manager::print_statistics();
				std::cout << "\n";
				print_statistics_info(pacceptor->statistics_get_connective_info_total(), true);
			}
			break;

			case	'-':
			{
				executor::manager::print_statistics(true);
				std::cout << "\n";
				print_statistics_info(pacceptor->statistics_get_connective_info_total(), true);
			}
			break;

			case	'_':
			{
				executor::manager::print_statistics();
				std::cout << "\n";
				print_statistics_info(pacceptor->statistics_get_connective_info_total(), true);
			}
			break;

			case	ASCII_CODE_BACKSPACE:
			{
				std::cout << "\033c";
				print_title();
				print_statistics_info(pacceptor->statistics_get_connective_info_total(), true);
			}
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


	// 5) clsoe
	system_executor::register_schedulable(g_pgroup);

	// trace)
	std::cout << "\x1b[4B\n tcp echo server closed...\n"sv;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;
}

void _print_setting_info(shared_buffer& _buffer_output)
{
	// 1) move cursor
	_buffer_output.append_text("\x1b[5B");

	// 2) ...
	_buffer_output.append_text("\x1b[37m [multi echo test]   \x1b[0m"sv);
	_buffer_output.append_text("\x1b[90mecho \x1b[0m"sv); _buffer_output.append_text<char>((g_disable_echo == false) ? "\x1b[47m\x1b[30m on \x1b[0m"sv : "\x1b[90m off\x1b[0m"sv);
	_buffer_output.append_text("\x1b[K\n"sv);

	// 3) move cursor
	_buffer_output.append_text("\x1b[6A"sv);
}

void print_setting_info()
{
	// 1) alloc buffer
	auto buf_output = alloc_shared_buffer(8192);

	// 2) text
	_print_setting_info(buf_output);

	// 3) write
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}

void print_title()
{
	std::ostringstream buf_output;
	buf_output.str().reserve(8192);
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	buf_output << "    CGCII tcp multi echo server with gather\n"sv;
	buf_output << "\n"sv;
	buf_output << "\n"sv;
	buf_output << "  [command]\n"sv;
	buf_output << "\n"sv;
	buf_output << "   \x1b[90m- close session\x1b[0m		'6'(-1), '7'(all)\n"sv;
	buf_output << "   \x1b[90m- disconnect session\x1b[0m		'8'(-1), '9'(all)\n"sv;
	buf_output << "   \x1b[90m- single send\x1b[0m		'u'(8byte), 'i'(1kbyte), 'o'(64kbyte)\n"sv;
	buf_output << "\n"sv;
	buf_output << "   multi echo test\n"sv;
	buf_output << "   \x1b[90m- echo on/off\x1b[0m		'a'\n"sv;
	buf_output << "\n"sv;
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	std::cout << buf_output.str();
}

void print_statistics_info(const statistics::unit_connective& _statistics_connective, bool _update_now)
{
	// 1) 현재 Tick과 Tick Gap을 구한다.
	static auto tick_last = chrono::tick::time_point(chrono::tick::duration::zero());
	auto tick_now = chrono::tick::now();

	// 2) get tick differ
	auto tick_differ = std::chrono::duration_cast<chrono::tick::milliseconds>(tick_now - tick_last);

	// check) tickdiffer가 1s이하면 그냥 끝낸다.
	RETURN_IF(_update_now == false && tick_differ < 1s);

	// 3) 최종 시간을 Update한다.
	tick_last = tick_now;

	// 4) alloc buffer
	auto buf_output = alloc_shared_buffer(8192);

	// 5) connection info
	{
		// declare) 
		static uint64_t	last_count_try = 0;
		static uint64_t	last_count_success = 0;
		static uint64_t	last_count_disconnected = 0;

		// - 이전과 현재의 차이를 구한다. (Overflow가 났을 경우를 대비하여 계산해야 한다.)
		auto now_count_keep = _statistics_connective.count_keep.load();
		auto now_count_try = _statistics_connective.count_try.load();
		auto now_count_success = _statistics_connective.count_success_connect.load();
		auto now_count_disconnected = _statistics_connective.count_disconnect.load();

		// - 초당 전송률을 구한다.
		auto total_try_per_sec = ((float)(now_count_try - last_count_try)) * 1000.0f / tick_differ.count();
		auto total_success_per_sec = ((float)(now_count_success - last_count_success)) * 1000.0f / tick_differ.count();
		auto total_disconnected_per_sec = ((float)(now_count_disconnected - last_count_disconnected)) * 1000.0f / tick_differ.count();

		// - 이전 값을 현재 값으로 Update한다.(다음 Frame에서의 계산을 위해)
		last_count_try = now_count_try;
		last_count_success = now_count_success;
		last_count_disconnected = now_count_disconnected;

		// - sended
		buf_output.append_text(" [connection]"sv);
		buf_output.append_text("\x1b[1m now \x1b[0m"sv); buf_output.append_text(now_count_keep);
		buf_output.append_text("\x1b[1m   try \x1b[0m"sv); buf_output.append_text(now_count_try);
		buf_output.append_text("\x1b[1m   try/s \x1b[0m"sv); buf_output.append_text(total_try_per_sec);
		buf_output.append_text("\x1b[1m   success/s \x1b[0m"sv); buf_output.append_text(total_success_per_sec);
		buf_output.append_text("\x1b[1m   dis/s \x1b[0m"sv); buf_output.append_text(total_disconnected_per_sec); buf_output.append_text("\x1b[K\n\n"sv);
	}


	// 5) traffic info
	{
		// - get traffic info
		auto& statistics = net::io::statistics::Nsocket::statistics_get_traffic_info_total();

		// declare) 
		static uint64_t	last_count_sended = 0;
		static uint64_t	last_count_received = 0;
		static uint64_t	last_count_sendedByte = 0;
		static uint64_t	last_count_received_byte = 0;

		// - 이전과 현재의 차이를 구한다. (Overflow가 났을 경우를 대비하여 계산해야 한다.)
		auto now_count_sended = statistics.count_sended_message.load();
		auto now_count_sendedByte = statistics.count_sended_bytes.load();
		auto now_count_send_failed = statistics.count_error_on_send.load();
		auto now_count_received = statistics.count_received_message.load();
		auto now_count_received_byte = statistics.count_received_bytes.load();

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
		buf_output.append_text(" [send]    "sv);
		buf_output.append_text("\x1b[90m   messages \x1b[0m"sv); buf_output.append_text("{:12d}"sv, now_count_sended);
		__sprintf(temp_string, "%.2f"sv, total_sended_message_per_sec);
		buf_output.append_text("\x1b[90m   messages/s \x1b[0m"sv); buf_output.append_text(temp_string);
		buf_output.append_text("\x1b[90m   bytes/s \x1b[0m"sv); buf_output.append_text(to_string_scaled_byte(temp_string, 256, total_sended_byte_per_sec));
		buf_output.append_text("\x1b[90m   failed \x1b[0m"sv); buf_output.append_text(now_count_send_failed); buf_output.append_text("\x1b[K\n"sv);

		// - received
		buf_output.append_text(" [receive] "sv);
		buf_output.append_text("\x1b[90m   messages \x1b[0m"sv); buf_output.append_text("{:12d}"sv, now_count_received);
		__sprintf(temp_string, "%.2f", total_receive_message_per_sec);
		buf_output.append_text("\x1b[90m   messages/s \x1b[0m"sv); buf_output.append_text(temp_string);
		buf_output.append_text("\x1b[90m   bytes/s \x1b[0m"sv); buf_output.append_text(to_string_scaled_byte(temp_string, 256, total_receive_byte_per_sec)); buf_output.append_text("\x1b[K\n"sv);
		buf_output.append_text("\n"sv);
	}

	// 3) move cursor
	buf_output.append_text("\x1b[5A"sv);

	// 4) setting info
	_print_setting_info(buf_output);

	// 6) output
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}
