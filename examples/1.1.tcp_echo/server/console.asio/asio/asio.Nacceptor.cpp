#include "asio.h"


asio::Nacceptor::Nacceptor()
{
}

asio::Nacceptor::~Nacceptor() noexcept
{
	this->close();
}

void asio::Nacceptor::start(tcp::endpoint _endpoint)
{
	// 1) initialize asio
	this->m_pacceptor = std::make_unique<tcp::acceptor>(asio::system::get_io_service().get_executor(), _endpoint);

	// 2) start accept
	try 
	{
		this->process_accept();
	}
	catch (...)
	{
		// - reset...
		this->m_pacceptor.reset();

		// reraise) 
		throw;
	}
}

void asio::Nacceptor::close() noexcept
{
	// 1) destroy all connectalbe
	this->destroy_connectable_all();

	// 2) close
	this->m_pacceptor.reset();
}

void asio::Nacceptor::process_accept()
{
	// check)
	if (this->m_pacceptor == nullptr)
		throw std::bad_alloc();

	// 1) accept noew connection and start
	auto psocket_new = this->process_create_socket();

	// 2) set socket state ESOCKET_STATUE::SYN
	{
		// - desiged state
		ESOCKET_STATUE socket_state_old = ESOCKET_STATUE::NONE;

		// - change state
		auto changed = psocket_new->m_socket_state.compare_exchange_weak(socket_state_old, ESOCKET_STATUE::SYN);

		// check)
		assert(changed == true);

		// return) 
		if (changed == false)
			throw std::runtime_error("socket aleady connected or tring connectiong");
	}

	// 3) accept
	this->m_pacceptor->async_accept(psocket_new->native_handle(),
		[=,this](boost::system::error_code ec)
		{
			// check) 
			if (ec)
			{
				// - set socket state
				psocket_new->m_socket_state.exchange(ESOCKET_STATUE::NONE);

				// return) 
				return;
			}

			// 2) register socket
			this->process_register_socket(psocket_new);
			
			try
			{
				// 2) connect
				psocket_new->process_connect_complate();

				// statistics) 
				++Nstatistics::statistics_connect_success;
				++Nstatistics::statistics_connect_keep;
			}
			catch (...)
			{
				this->process_unregister_socket(psocket_new);

				// - rollback (set socket state ESOCKET_STATUE::NONE)
				psocket_new->m_socket_state.exchange(ESOCKET_STATUE::NONE);
			}

			// 2) request asyc-accept
			this->process_accept();
		});
}
