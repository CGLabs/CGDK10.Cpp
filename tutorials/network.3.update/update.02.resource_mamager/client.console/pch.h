#pragma once

// 1) SDKDDKVer
#if defined(_WIN32)
	#include <SDKDDKVer.h>
#endif

// 2) includes
#include <stdio.h>
#if defined(_WIN32)
	#include <conio.h>
#endif
#include <iostream>

// 3) CGDK
#include "cgdk/sdk10/net.update.h"

// definitions) 
using namespace CGDK;

// 4) ...
#include "../define_message.h"
#include "socket_tcp.h"
