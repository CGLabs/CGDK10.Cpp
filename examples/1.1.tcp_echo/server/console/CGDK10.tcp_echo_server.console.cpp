#include "cgdk/sdk10/net.socket.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;
using namespace std::literals;
bool g_disable_echo = false;

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

class socket_tcp_buffered :	public net::socket::tcp_buffered<>
{
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// check)
		RETURN_IF(g_disable_echo, eRESULT::BYPASS);

		// 1) echo send
		this->send(_msg.buf_message);

		// return) 
		return eRESULT::DONE;
	}
};

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	// 1) print title
	print_title();

	// 2) create CGCI acceptor
	auto pacceptor = make_own<net::acceptor<socket_tcp_buffered>>();

	// 2) create boost asio acceptor - listen on 'localhost:20000'
	pacceptor->start({{ net::ip::tcp::v6(), 20000 }});

	// 4) loop - wait press any key 
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
							(*pacceptor->begin())->closesocket();
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
							(*pacceptor->begin())->disconnect();
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

			// redraw
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

			// CGCII statistics
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
			}

			// output setting info
			print_setting_info();
		}

		// - sleep
		std::this_thread::sleep_for(100ms);
	}

	// 5) close asio 
	pacceptor.reset();

	// 6) exit
	std::cout << "\x1b[4B\n tcp echo server closed...\n"sv;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;
}

