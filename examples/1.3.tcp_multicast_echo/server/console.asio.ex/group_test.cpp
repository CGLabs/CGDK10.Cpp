#include "pch.h"


void group_test::send(shared_buffer& _msg)
{
	// declare)
	std::vector<std::shared_ptr<socket_tcp>> vector_socket;

	// 1) get member list
	{
		// lock) 
		std::scoped_lock cs(this->m_cs_vector_socket);

		vector_socket = m_vector_socket;
	}

	// 2) send to all
	for (const auto& iter : m_vector_socket)
	{
		iter->send(_msg);
	}
}

void group_test::add_member(const std::shared_ptr<asio::Isocket_tcp>& _member)
{
	std::scoped_lock cs(this->m_cs_vector_socket);

	auto pmember = std::dynamic_pointer_cast<socket_tcp>(_member);

	this->m_vector_socket.push_back(std::move(pmember));

}

void group_test::remove_member(const std::shared_ptr<asio::Isocket_tcp>& _member) noexcept
{
	// lock) 
	std::scoped_lock cs(this->m_cs_vector_socket);

	auto pmember = std::dynamic_pointer_cast<socket_tcp>(_member);

	// 1) find member
	auto iter_find = std::find_if(this->m_vector_socket.begin(), this->m_vector_socket.end(), [=](const std::shared_ptr<socket_tcp>& _iter) noexcept { return _iter == pmember; });

	// check)
	if (iter_find == this->m_vector_socket.end())
		return;

	// 2) remove
	this->m_vector_socket.erase(iter_find);
}
