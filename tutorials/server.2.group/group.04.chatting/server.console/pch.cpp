#include "pch.h"


// 1) global variable
CGDK::own_ptr<group_immigration> g_pgroup_immigration;
CGDK::own_ptr<manager_user> g_pmanager_user;
CGDK::own_ptr<manager_channel> g_pmanager_channel;
CGDK::own_ptr<CGDK::net::acceptor<socket_user>> g_pacceptor;

