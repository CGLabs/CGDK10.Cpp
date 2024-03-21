#include "cgdk/sdk10/server.log.h"
#include "cgdk/sdk10/server.service.h"
#include "cgdk/sdk10/net.socket.h"

#include <iostream>
#if defined(_WIN32)
#include <conio.h>
#endif

using namespace CGDK;

#include "socket_tcp_user.h"
#include "socket_tcp_server.h"
#include "service.h"

extern own_ptr<service> g_pservice;
