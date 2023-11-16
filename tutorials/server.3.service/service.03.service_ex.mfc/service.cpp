#include "pch.h"

own_ptr<service> g_pservice;


service::service() : server_system::service_ex("service"sv, "logfile.log"sv, "server_setting.json"sv)
{
	// 1) acceptor를 붙인다.
	attach_child_object(m_pacceptor_user);

	// 2) socket_tcp를 붙인다.
	attach_child_object(m_psocket_tcp);
}
