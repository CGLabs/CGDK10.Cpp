#include "cgdk/sdk10/net.socket.h"
#include <iostream>
#include <sstream>

using namespace CGDK;
using namespace std::literals;
extern bool g_disable_echo;

void print_title()
{
	std::ostringstream buf_output;
	buf_output.str().reserve(8192);
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	buf_output << "    CGCII tcp echo server\n"sv;
	buf_output << "\n"sv;
	buf_output << "\n"sv;
	buf_output << "  [command]\n"sv;
	buf_output << "\n"sv;
	buf_output << "   \x1b[90m- close session\x1b[0m		'6'(-1), '7'(all)\n"sv;
	buf_output << "   \x1b[90m- disconnect session\x1b[0m		'8'(-1), '9'(all)\n"sv;
	buf_output << "   \x1b[90m- single send\x1b[0m		'u'(8byte), 'i'(1kbyte), 'o'(64kbyte)\n"sv;
	buf_output << "\n"sv;
	buf_output << "   echo test\n"sv;
	buf_output << "   \x1b[90m- echo on/off\x1b[0m		'a'\n"sv;
	buf_output << "\n"sv;
	buf_output << " ---------------------------------------------------\n"sv;
	buf_output << "\n"sv;
	std::cout << buf_output.str();
}

void _print_setting_info(shared_buffer& _buffer_output)
{
	// 1) move cursor
	_buffer_output.append_text("\x1b[5B");

	// 2) ...
	_buffer_output.append_text("\x1b[37m [echo test]   \x1b[0m"sv);
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

void print_statistics_info(const statistics::unit_connective& _statistics_connective, bool _update_now)
{
	// 1) 현재 Tick과 Tick Gap을 구한다.
	static auto tick_last = chrono::tick::time_point(chrono::tick::duration::zero());
	auto tick_now = chrono::tick::now();
	auto tick_differ = std::chrono::duration_cast<chrono::tick::milliseconds>(tick_now - tick_last);

	// check) tickdiffer가 1s이하면 그냥 끝낸다.
	RETURN_IF(_update_now == false && tick_differ < 1s);

	// 2) 최종 시간을 Update한다.
	tick_last = tick_now;

	// 3) alloc buffer
	auto buf_output = alloc_shared_buffer(8192);

	// 4) connection info
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

	// 6) move cursor
	buf_output.append_text("\x1b[5A"sv);

	// 7) setting info
	_print_setting_info(buf_output);

	// 8) output
	fwrite(buf_output.data(), 1, buf_output.size<int>(), stdout);
	fflush(stdout);
}
