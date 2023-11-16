#pragma once

class group_test :
	public group::list_sender<socket_tcp>,
	public schedulable::Nexecutable
{
public:
	group_test();

			void	queuing_message(buffer_view _buf);

public:
	virtual	void	on_execute() override;

			lockable<>		m_cs_buf_send;
			shared_buffer	m_buf_send;
			std::atomic<uint64_t> m_queued_messages{0};
			void	_alloc_buf_queue();

};
