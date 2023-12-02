#include "asio.h"


asio::Nsocket_tcp::Nsocket_tcp() :
	Isocket_tcp(asio::system::get_io_service().get_executor())
{
}

asio::Nsocket_tcp::~Nsocket_tcp() noexcept
{
	// 1) close socket
	this->process_closesocket();

	// 2) free buffer
	if (this->m_received_msg.data() != nullptr)
	{
		::free(this->m_received_msg.data());
	}
}

void asio::Nsocket_tcp::process_connect_complate()
 {
	// 1) set socket state ESOCKET_STATUE::ESTABLISHED
	{
		// - desiged state
		 ESOCKET_STATUE socket_state_old = ESOCKET_STATUE::SYN;

		// - change state
		auto changed = m_socket_state.compare_exchange_weak(socket_state_old, ESOCKET_STATUE::ESTABLISHED);

		// check)
		assert(changed == true);

		// return) 
		if (changed == false)
			return;
	}

	// 2) on connect
	this->on_connect();

	// 3) 기존의 buffer가 있으면 지운다.
	if (this->m_received_msg.data())
	{
		::free(this->m_received_msg.data());
	}

	// 4) alloc buffer
	auto buffer_receive = (char*)::malloc(RECEIVE_BUFFER_SIZE);

	// 5) reset buffer
	this->m_received_msg = mutable_buffer{ buffer_receive, 0 };
	this->m_receiving_msg = mutable_buffer{ buffer_receive, RECEIVE_BUFFER_SIZE };

	// 6) read async
	this->process_receive_async();
}

bool asio::Nsocket_tcp::process_closesocket() noexcept
{
	// 1) close socket
	this->process_close_native_handle();

	// 2) set socket state ESOCKET_STATUE::CLOSING
	{
		// - desiged state
		ESOCKET_STATUE socket_state_old = ESOCKET_STATUE::ESTABLISHED;

		// - change state
		auto changed = this->m_socket_state.compare_exchange_weak(socket_state_old, ESOCKET_STATUE::CLOSING);

		// return) 
		if (changed == false)
			return false;
	}

	// statistics)
	++Nstatistics::statistics_connect_disconnect;
	--Nstatistics::statistics_connect_keep;

	// 3) call 'on disconnect'
	this->on_disconnect();

	// 4) remove form acceptor
	this->process_connective_closesocket();

	// 5) set socket state ESOCKET_STATUE::NONE
	{
		// - ...
		auto old_socket_state = this->m_socket_state.exchange(ESOCKET_STATUE::NONE);

		// check)
		assert(old_socket_state == ESOCKET_STATUE::CLOSING);

		// check)
		if (old_socket_state != ESOCKET_STATUE::CLOSING)
			return false;
	}

	// return)
	return true;
}

bool asio::Nsocket_tcp::process_send(const SEND_NODE& _send_node)
{
	return this->process_send_sync(_send_node);
}

bool asio::Nsocket_tcp::process_send_sync(const SEND_NODE& _send_node)
{
	// check) 
	if (this->m_socket_state < ESOCKET_STATUE::CLOSING)
		return false;

	// 1) 
	const_buffer buffer_transfer = _send_node.buffer;

	while (buffer_transfer.size() != 0)
	{
		// declare)
		boost::system::error_code ec;

		// - send
		auto size_transfered = this->m_socket.write_some(buffer_transfer, ec);

		// check) 
		if (ec)
			return false;

		// - proceed
		buffer_transfer += size_transfered;
	}

	// statistics)
	Nstatistics::statistics_send_messages += _send_node.message_count;
	Nstatistics::statistics_send_bytes += _send_node.buffer.size();

	// return)
	return true;
}

void asio::Nsocket_tcp::process_receive_async()
{
    auto self(shared_from_this());

	this->m_socket.async_read_some(m_receiving_msg,
		[this, self](boost::system::error_code _error_code, std::size_t _length)
		{
			// - disconnected?
			if (_error_code.failed())
			{
				// - closesocket
				this->process_closesocket();
					
				// return) 
				return;
			}

			// - get received buffer
			auto pdata = reinterpret_cast<char*>(m_received_msg.data());
			auto length = m_received_msg.size() + _length;
			size_t message_size;

			if (pdata == nullptr)
				return;

			// statistics) 
			Nstatistics::statistics_receive_bytes += _length;

			try
			{
				while (length >= 4)
				{
					// - get message size
					message_size = *reinterpret_cast<uint32_t*>(pdata);

					// check) 
					if (message_size == 0)
						throw std::length_error("message length is zero");

					// check) 
					if (message_size > length)
						break;

					// - make message
					const_buffer temp_buffer{ pdata, message_size };

					// - on message
					this->on_message(temp_buffer);

					// statistics)
					++Nstatistics::statistics_receive_messages;

					// - 
					pdata += message_size;
					length -= message_size;
				}

				// - copy 
				if (length != 0)
				{
					memcpy(this->m_received_msg.data(), reinterpret_cast<void*>(pdata), length);
				}

				// - update receive buffer 
				this->m_received_msg = mutable_buffer{ this->m_received_msg.data(), length };
				this->m_receiving_msg = mutable_buffer{ reinterpret_cast<char*>(this->m_received_msg.data()) + length, RECEIVE_BUFFER_SIZE - length };

				// - read 
				this->process_receive_async();
			}
			catch (...)
			{
				// - closesocket
				this->process_closesocket();

				// return) 
				return;
			}
		});
}
