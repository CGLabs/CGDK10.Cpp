#include "pch.h"

own_ptr<service> g_pservice;

service::service() :
	server_system::service_ex("update server"sv, LOG_FILE, CONFIGURE_FILE)
{
	// 1) set server type
	//server_setting_info().rank.role = SERVER_ROLE_ADMIN;

	// 2) resource manager
	m_presource_manager = make_own<update::resource_manager>();
	m_presource_manager->set_name("update_resource_mamanger"sv);
	attach_child_object(m_presource_manager);

	// 3) groups
	m_pgroup_socket = make_own<group_socket>();
	attach_child_object(m_pgroup_socket);

	m_pgroup_socket_immigration = make_own<group_socket_immigration>();
	attach_child_object(m_pgroup_socket_immigration);

	// 4) acceptor
	m_pacceptor_tcp = make_own<net::acceptor<socket_tcp>>();
	m_pacceptor_tcp->set_name("acceptor_user"sv);
	attach_child_object(m_pacceptor_tcp);
}
