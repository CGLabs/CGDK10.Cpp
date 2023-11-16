#include "pch.h"


group_test::group_test()
{
	scoped_lock(m_cs_buf_send)
	{
		this->_alloc_buf_queue();
	}
}

void group_test::queuing_message(buffer_view _buf)
{
	scoped_lock(this->m_cs_buf_send)
	{
		this->m_buf_send.append(_buf.size(), _buf.data());
		++this->m_queued_messages;
	}
}

void group_test::on_execute()
{
	// declare0 
	shared_buffer buf_send;
	uint64_t count_message;

	// 1) get stored message and reallocate buffer
	scoped_lock(this->m_cs_buf_send)
	{
		// check)
		RETURN_IF(this->m_buf_send.size() == 0);

		// - alloc new buffer
		buf_send = std::move(this->m_buf_send);
		count_message = m_queued_messages;

		this->_alloc_buf_queue();
	}

	// 2) send messages
	this->send({ buf_send, count_message });
}

void group_test::_alloc_buf_queue()
{
	static const size_t MESSAGE_SIZE = 1024; // 1K
	static const size_t MESSAGE_COUNT = 100 * 500; // 50M

	this->m_buf_send = alloc_shared_buffer(MESSAGE_SIZE * MESSAGE_COUNT);
	this->m_queued_messages = 0;
}
