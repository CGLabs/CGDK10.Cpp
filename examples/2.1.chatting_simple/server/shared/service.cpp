#include "pch.h"

own_ptr<service> g_pservice;


service::service() : server_system::service_ex("service", "chatting_server_setting.log", "chatting_server_setting.json")
{
	// 1) manager
	this->m_pmanager_user = make_own<user::manager>();
	this->m_pmanager_user->set_name("user_manager"sv);
	this->attach_child_object(this->m_pmanager_user);

	this->m_pmanager_channel = make_own<channel::manager>();
	this->m_pmanager_channel->set_name("channel_manager"sv);
	this->attach_child_object(this->m_pmanager_channel);

	// 2) user immigration group
	this->m_pgroup_user_immigration = make_own<user::group_immigration>();
	this->m_pgroup_user_immigration->set_name("group_immigration_user"sv);
	this->attach_child_object(this->m_pgroup_user_immigration);

	// 3) user acceptor
	this->m_pacceptor_user = make_own<net::acceptor<user::socket>>();
	this->m_pacceptor_user->set_name("acceptor_user"sv);
	this->attach_child_object(this->m_pacceptor_user);
}

service::~service() noexcept
{
}
