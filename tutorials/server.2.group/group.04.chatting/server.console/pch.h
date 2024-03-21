#pragma once

#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.group.list.h"
#include "../define_message_chatting.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

#include "socket_user.h"
#include "group_immigration.h"
#include "group_channel.h"
#include "manager_channel.h"
#include "manager_user.h"

extern CGDK::own_ptr<group_immigration> g_pgroup_immigration;
extern CGDK::own_ptr<manager_user> g_pmanager_user;
extern CGDK::own_ptr<manager_channel> g_pmanager_channel;
extern CGDK::own_ptr<CGDK::net::acceptor<socket_user>> g_pacceptor;
