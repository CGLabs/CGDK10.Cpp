﻿#include "asio/asio.h"
#include <iostream>
#include <sstream>
#include <boost/thread.hpp>
#if defined(_WIN32)
	#include <conio.h>
#elif defined(__linux__)
	int _kbhit();
	int _getch();
#endif

using namespace std::literals;
bool g_disable_echo = false;

void print_title();
void print_statistics_info();
void print_setting_info();
mutable_buffer make_message(size_t _size);

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

class socket_tcp : public asio::Nsocket_tcp
{
public:
	virtual void on_connect() override
	{
	}
	virtual void on_disconnect() noexcept override
	{
	}
	virtual int on_message(const const_buffer& _msg) override
	{
		if (g_disable_echo)
			return 0;

		send(_msg);
		return 1;
	}
};

int main()
{
	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

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
							(*pacceptor->begin())->disconnect();
						}
					}
					break;

			case	'7':
					{
						pacceptor->close_connectable_all();
					}
					break;

			// closesocket
			case	'8':
					{
						std::unique_lock cs(pacceptor->get_lockable());

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
						::free(buf_send.data());
					}
					break;

			case	'I':
			case	'i':
					{
						auto buf_send = make_message(1024);
						pacceptor->send(buf_send);
						::free(buf_send.data());
					}
					break;

			case	'O':
			case	'o':
					{
						auto buf_send = make_message(65536);
						pacceptor->send(buf_send);
						::free(buf_send.data());
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
						print_statistics_info();
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

	// 4) close asio 
	pacceptor.reset();

	// 5) exit
	std::cout << "\x1b[4B\n tcp echo server closed...\n"sv;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;
}