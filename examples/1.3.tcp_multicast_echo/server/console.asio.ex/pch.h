﻿#pragma once

#include "asio.ex/asio.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>
#include <boost/thread.hpp>
#if defined(_WIN32)
	#include <conio.h>
#elif defined(__linux__)
	int _kbhit();
	int _getch();
#endif

using namespace std::literals::string_view_literals;
using namespace std::chrono;


#include "socket_test.h"
#include "group_test.h"

extern std::unique_ptr<group_test> g_pgroup;
extern bool g_disable_echo;
