#ifndef PCH_H
#define PCH_H

// 1) CGCII header files
#include "cgdk/sdk10/net.socket.h"

// 2) C++ standard header files
#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

// 3) using
using namespace CGDK;

#endif //PCH_H
