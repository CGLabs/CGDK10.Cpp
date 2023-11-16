#include "pch.h"
#include "echo_client.h"

extern own_ptr<test_tcp_echo_client> g_ptest_tcp_echo_client;
void print_title();
void print_endpoint(test_tcp_echo_client* _ptest_tcp_echo_client);
void print_statistics_info(test_tcp_echo_client* _ptest_tcp_echo_client, bool _update_now = false);
void print_setting_info(test_tcp_echo_client* _ptest_tcp_echo_client);

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

std::string get_cin_line()
{
	std::string str_input;
	int ch;

	while ((ch = _getch()) != ASCII_CODE_ENTER && str_input.size() < 256)
	{
		if (ch == ASCII_CODE_ESCAPE)
		{
			str_input.clear();
			break;
		}

		if (ch == ASCII_CODE_BACKSPACE)
		{
			if (str_input.empty())
				continue;

			str_input.pop_back();
			std::cout << "\b \b" << std::flush;

			continue;
		}

		if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'A') || (ch >= '0' && ch <= '9') || ch == '.'))
		{
			continue;
		}

		str_input += static_cast<char>(ch);
		std::putchar(ch);
		std::cout << std::flush;
	}
	std::cout << std::endl;
	std::cout << std::flush;

	return str_input;
}

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	// 1) print title
	print_title();

	// 2) create tcp echo client
	g_ptest_tcp_echo_client = make_own<test_tcp_echo_client>();

	// 3) start
	g_ptest_tcp_echo_client->start();

	// 4) ...
	print_endpoint(g_ptest_tcp_echo_client);

	// 5) loop
	for (;;)
	{
		// - output traffic info
		print_statistics_info(g_ptest_tcp_echo_client);

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
			// connect
			case	'1':
					g_ptest_tcp_echo_client->request_connect(1);
					break;
			case	'2':
					g_ptest_tcp_echo_client->request_connect(10);
					break;
			case	'3':
					g_ptest_tcp_echo_client->request_connect(100);
					break;
			case	'4':
					g_ptest_tcp_echo_client->request_connect(1000);
					break;
			case	'5':
					g_ptest_tcp_echo_client->request_connect(10000);
					break;

			// closesocket
			case	'6':
					g_ptest_tcp_echo_client->request_closesocket(1);
					break;
			case	'7':
					g_ptest_tcp_echo_client->request_closesocket_all();
					break;

			// disconnect
			case	'8':
					g_ptest_tcp_echo_client->request_disconnect_socket(1);
					break;
			case	'9':
					g_ptest_tcp_echo_client->request_disconnect_socket_all();
					break;

			// connection test
			case	'Q':
			case	'q':
					g_ptest_tcp_echo_client->toggle_connect_test();
					break;

			case	'W':
			case	'w':
					g_ptest_tcp_echo_client->add_connect_test_min(100);
					break;

			case	'E':
			case	'e':
					g_ptest_tcp_echo_client->sub_connect_test_min(100);
					break;

			case	'R':
			case	'r':
					g_ptest_tcp_echo_client->add_connect_test_max(100);
					break;

			case	'T':
			case	't':
					g_ptest_tcp_echo_client->sub_connect_test_max(100);
					break;

			// traffic test
			case	' ':
					g_ptest_tcp_echo_client->toggle_traffic_test();
					break;

			case	'A':
			case	'a':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(1);
					break;

			case	'Z':
			case	'z':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(1);
					break;

			case	'S':
			case	's':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(10);
					break;

			case	'X':
			case	'x':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(10);
					break;

			case	'D':
			case	'd':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(100);
					break;

			case	'C':
			case	'c':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(100);
					break;

			case	'F':
			case	'f':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(1000);
					break;

			case	'V':
			case	'v':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(1000);
					break;

			case	'G':
			case	'g':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(10000);
					break;

			case	'B':
			case	'b':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(10000);
					break;

			case	'H':
			case	'h':
					g_ptest_tcp_echo_client->add_traffic_test_count_per_single(100000);
					break;

			case	'N':
			case	'n':
					g_ptest_tcp_echo_client->sub_traffic_test_count_per_single(100000);
					break;

			case	'j':
					g_ptest_tcp_echo_client->increase_traffic_test_message_size();
					break;

			case	'm':
					g_ptest_tcp_echo_client->decrease_traffic_test_message_size();
					break;

			case	'U':
			case	'u':
					g_ptest_tcp_echo_client->request_send_immidiately(1);
					break;

			case	'I':
			case	'i':
					g_ptest_tcp_echo_client->request_send_immidiately(10);
					break;

			case	'O':
			case	'o':
					g_ptest_tcp_echo_client->request_send_immidiately(100);
					break;

			case	'P':
			case	'p':
					g_ptest_tcp_echo_client->request_send_immidiately(1000);
					break;

			case	'[':
					g_ptest_tcp_echo_client->request_send_immidiately(100000);
					break;

			case	']':
					g_ptest_tcp_echo_client->request_send_immidiately(1000000);
					break;

		#if defined(_WIN32)
			case	0xe0:
					{
						// - extended key (for windows)
						/*auto key = */_getch();
					}
					break;
		#endif

			case	ASCII_CODE_ENTER:
					{
						// - get address
						std::cout << "\x1b[3A";
						std::cout << "\x1b[2K";
						std::cout << "\x1b[90m address : \x1b[0m" << std::flush;
						auto str_address = get_cin_line();

						// - get port
						std::cout << "\x1b[2K";
						std::cout << "\x1b[90m port    : \x1b[0m" << std::flush;
						auto str_port = get_cin_line();

						// - set endpoint
						g_ptest_tcp_echo_client->set_endpoint(str_address, str_port);

						std::cout << "\x1b[3A";
						print_endpoint(g_ptest_tcp_echo_client);
					}
					break;

			case	'=':
					{

						factory::manager::print_statistics(true);
						std::cout << "\n";
						print_endpoint(g_ptest_tcp_echo_client);
						print_statistics_info(g_ptest_tcp_echo_client, true);
					}
					break;

			case	'+':
					{
						factory::manager::print_statistics();
						std::cout << "\n";
						print_statistics_info(g_ptest_tcp_echo_client, true);
					}
					break;

			case	'-':
					{

						executor::manager::print_statistics(true);
						std::cout << "\n";
						print_endpoint(g_ptest_tcp_echo_client);
						print_statistics_info(g_ptest_tcp_echo_client, true);
					}
					break;

			case	'_':
					{
						executor::manager::print_statistics();
						std::cout << "\n";
						print_endpoint(g_ptest_tcp_echo_client);
						print_statistics_info(g_ptest_tcp_echo_client, true);
					}
					break;

			case	ASCII_CODE_BACKSPACE:
					{
						std::cout << "\033c";
						print_title();
						print_endpoint(g_ptest_tcp_echo_client);
						print_statistics_info(g_ptest_tcp_echo_client, true);
					}
					break;
			}

			// output setting info
			print_setting_info(g_ptest_tcp_echo_client);
		}

		// - sleep
		std::this_thread::sleep_for(100ms);
	}

	// 6) destroy
	g_ptest_tcp_echo_client.reset();

	// 7) 
	std::cout << "\x1b[7B\n tcp echo client closed... \n";

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;
}

void _print_setting_info(shared_buffer& _buffer_output, test_tcp_echo_client* _ptest_tcp_echo_client)
{
	// 1) move cursor
	_buffer_output.append_text("\x1b[5B");

	// definitions)
	static const char* str_index_to_string[] = { "8 byte", "64 byte", "256 byte", "1K byte", "4K byte", "16K byte", "64K byte", "512K byte", "4M byte", "32M byte", "256M byte" };

	// 2) ...
	_buffer_output.append_text("\x1b[37m [con test]   \x1b[0m");
	_buffer_output.append_text<char>((_ptest_tcp_echo_client->m_enable_connect_test) ? "\x1b[47m\x1b[30m on \x1b[0m " : "\x1b[90m off\x1b[0m ");
	_buffer_output.append_text("\x1b[90mrange min \x1b[0m"); _buffer_output.append_text(_ptest_tcp_echo_client->m_connect_test_min);
	_buffer_output.append_text("\x1b[90m ~ max \x1b[0m"); _buffer_output.append_text(_ptest_tcp_echo_client->m_connect_test_max); _buffer_output.append_text(", ");
	_buffer_output.append_text("\x1b[90minterval \x1b[0m"); _buffer_output.append_text<char>((int)0); _buffer_output.append_text("\x1b[K\n");

	_buffer_output.append_text("\x1b[37m [echo test]  \x1b[0m");
	_buffer_output.append_text<char>((_ptest_tcp_echo_client->m_enable_traffic_test) ? "\x1b[47m\x1b[30m on \x1b[0m " : "\x1b[90m off\x1b[0m ");
	_buffer_output.append_text("\x1b[90mmessage size \x1b[0m"); _buffer_output.append_text<char>(str_index_to_string[_ptest_tcp_echo_client->m_traffic_test_selected]); _buffer_output.append_text(",  ");
	_buffer_output.append_text("\x1b[90mtimes \x1b[0m"); _buffer_output.append_text(_ptest_tcp_echo_client->m_traffic_test_count_per_single); _buffer_output.append_text("\x1b[K\n");

	_buffer_output.append_text("\x1b[37m [relay echo] \x1b[0m");
	_buffer_output.append_text<char>("\x1b[90m off\x1b[0m "); _buffer_output.append_text("\x1b[K");
	_buffer_output.append_text("              \x1b[37m [dis on res] \x1b[0m");
	_buffer_output.append_text<char>("\x1b[90m off\x1b[0m "); _buffer_output.append_text("\x1b[K\n");

	// 3) move cursor
	_buffer_output.append_text("\x1b[8A");
}

void print_title()
{
	// 1) initialization
	auto buf_output = alloc_shared_buffer(8192);

	buf_output.append_text(" ---------------------------------------------------\n");
	buf_output.append_text("\n");
	buf_output.append_text("\x1b[97m    CGCII tcp echo client \x1b[0m\n");
	buf_output.append_text("\n");
	buf_output.append_text("\n");
	buf_output.append_text("  [command]\n");
	buf_output.append_text("\n");
	buf_output.append_text("   \x1b[90m- change remote endpoint\x1b[0m	'ENTER' key\n");
	buf_output.append_text("   \x1b[90m- connect session\x1b[0m		'1'(+1), '2'(+10), '3'(+100), '4'(+1000), '5'(+10000)\n");
	buf_output.append_text("   \x1b[90m- close session\x1b[0m		'6'(-1), '7'(all)\n");
	buf_output.append_text("   \x1b[90m- disconnect session\x1b[0m		'8'(-1), '9'(all)\n");
	buf_output.append_text("\n");
	buf_output.append_text("   connection test\n");
	buf_output.append_text("   \x1b[90m- start/stop\x1b[0m			'q'\n");
	buf_output.append_text("   \x1b[90m- increase min range\x1b[0m		'w'\n");
	buf_output.append_text("   \x1b[90m- decrease min range\x1b[0m		'e'\n");
	buf_output.append_text("   \x1b[90m- increase max range\x1b[0m		'r'\n");
	buf_output.append_text("   \x1b[90m- decrease max range\x1b[0m		't'\n");
	buf_output.append_text("\n");
	buf_output.append_text("   traffic test\n");
	buf_output.append_text("   \x1b[90m- start/stop\x1b[0m			space key\n");
	buf_output.append_text("   \x1b[90m- relay echo on/off\x1b[0m		'/'\n");
	buf_output.append_text("   \x1b[90m- disconnect on response\x1b[0m	';'\n");
	buf_output.append_text("   \x1b[90m- increase traffic\x1b[0m		'a'(+1), 's'(+10), 'd'(+100), 'f'(+1000), 'g'(+10000), 'h'(+100000)\n");
	buf_output.append_text("   \x1b[90m- decrease traffic\x1b[0m		'z'(-1), 'x'(-10), 'c'(-100), 'v'(-1000), 'b'(-10000), 'n'(-100000)\n");
	buf_output.append_text("   \x1b[90m- change message size\x1b[0m	'm'(-), 'j'(+)\n");
	buf_output.append_text("   \x1b[90m- single send\x1b[0m		'u'(1), 'i'(10), 'o'(100), 'p'(1000), '['(100000), ']'(1000000)\n");
	buf_output.append_text("\n");
	buf_output.append_text(" ---------------------------------------------------\n");
	buf_output.append_text("\n");
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}

void print_setting_info(test_tcp_echo_client* _ptest_tcp_echo_client)
{
	// 1) alloc buffer
	auto buf_output = alloc_shared_buffer(8192);

	// 2) text
	_print_setting_info(buf_output, _ptest_tcp_echo_client);

	// 3) write
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}

void print_endpoint(test_tcp_echo_client* _ptest_tcp_echo_client)
{
	const auto& end_point = _ptest_tcp_echo_client->get_endpoint();

	std::cout << " [remote endpoint]\n";
	std::cout << "\x1b[90m address : \x1b[0m" << to_string<char>(end_point.address()) << "\x1b[K\n";
	std::cout << "\x1b[90m port    : \x1b[0m" << end_point.port() << "\x1b[K\n\n";
}

void print_statistics_info(test_tcp_echo_client* _ptest_tcp_echo_client, bool _update_now)
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
		// - get connective info
		const auto& statistics = _ptest_tcp_echo_client->m_pconnector_socket->statistics_get_connective_info_total();

		// declare) 
		static uint64_t	last_count_try = 0;
		static uint64_t	last_count_success = 0;
		static uint64_t	last_count_disconnected = 0;

		// - 이전과 현재의 차이를 구한다. (Overflow가 났을 경우를 대비하여 계산해야 한다.)
		auto now_count_keep = statistics.count_keep.load();
		auto now_count_try = statistics.count_try.load();
		auto now_count_success = statistics.count_success_connect.load();
		auto now_count_fail = statistics.count_fail_connect.load();
		auto now_count_disconnected = statistics.count_disconnect.load();

		// - 초당 전송률을 구한다.
		auto total_try_per_sec = ((float)(now_count_try - last_count_try)) * 1000.0f / tick_differ.count();
		auto total_success_per_sec = ((float)(now_count_success - last_count_success)) * 1000.0f / tick_differ.count();
		auto total_disconnected_per_sec = ((float)(now_count_disconnected - last_count_disconnected)) * 1000.0f / tick_differ.count();

		// - 이전 값을 현재 값으로 Update한다.(다음 Frame에서의 계산을 위해)
		last_count_try = now_count_try;
		last_count_success = now_count_success;
		last_count_disconnected = now_count_disconnected;

		// - sended
		buf_output.append_text(" [connection]");
		buf_output.append_text("\x1b[90m now \x1b[0m"); buf_output.append_text(now_count_keep);
		buf_output.append_text("\x1b[90m   try \x1b[0m"); buf_output.append_text(now_count_try);
		buf_output.append_text("\x1b[90m   success \x1b[0m"); buf_output.append_text(now_count_success);
		buf_output.append_text("\x1b[90m   fail \x1b[0m"); buf_output.append_text(now_count_fail);
		buf_output.append_text("\x1b[90m   dis \x1b[0m"); buf_output.append_text(now_count_disconnected);
		buf_output.append_text("\x1b[90m   try/s \x1b[0m"); buf_output.append_text(total_try_per_sec);
		buf_output.append_text("\x1b[90m   success/s \x1b[0m"); buf_output.append_text(total_success_per_sec);
		buf_output.append_text("\x1b[90m   dis/s \x1b[0m"); buf_output.append_text(total_disconnected_per_sec); buf_output.append_text("\x1b[K\n\n");
	}

	// 6) traffic info
	{
		// - get traffic info
		const auto& statistics = net::io::statistics::Nsocket::statistics_get_traffic_info_total();

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
		buf_output.append_text(" [send]    ");
		buf_output.append_text("\x1b[90m   messages \x1b[0m"); buf_output.append_text("{:12d}", now_count_sended);
		__sprintf(temp_string, "%.2f", total_sended_message_per_sec);
		buf_output.append_text("\x1b[90m   messages/s \x1b[0m"); buf_output.append_text(temp_string);
		buf_output.append_text("\x1b[90m   bytes/s \x1b[0m"); buf_output.append_text(to_string_scaled_byte(temp_string, 256, total_sended_byte_per_sec));
		buf_output.append_text("\x1b[90m   failed \x1b[0m"); buf_output.append_text<char>(now_count_send_failed); buf_output.append_text("\x1b[K\n");

		// - received
		buf_output.append_text(" [receive] ");
		buf_output.append_text("\x1b[90m   messages \x1b[0m"); buf_output.append_text("{:12d}", now_count_received);
		__sprintf(temp_string, "%.2f", total_receive_message_per_sec);
		buf_output.append_text("\x1b[90m   messages/s \x1b[0m"); buf_output.append_text(temp_string);
		buf_output.append_text("\x1b[90m   bytes/s \x1b[0m"); buf_output.append_text(to_string_scaled_byte(temp_string, 256, total_receive_byte_per_sec)); buf_output.append_text("\x1b[K\n");
		buf_output.append_text("\n");
	}

	// 7) move cursor
	buf_output.append_text("\x1b[5A");

	// 8) setting info
	_print_setting_info(buf_output, _ptest_tcp_echo_client);

	// 9) output
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}

