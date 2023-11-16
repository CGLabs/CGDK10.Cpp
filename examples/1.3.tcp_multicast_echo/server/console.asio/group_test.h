#pragma once

class group_test
{
public:
	void send(const const_buffer& _msg);

	void add_member(const std::shared_ptr<asio::Isocket_tcp>& _member);
	void remove_member(const std::shared_ptr<asio::Isocket_tcp>& _member) noexcept;

public:
	std::mutex m_cs_vector_socket;
	std::vector<std::shared_ptr<socket_tcp>> m_vector_socket;

};