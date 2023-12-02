//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           asio network classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
#pragma once

enum class ESOCKET_STATUE : int
{
	NONE = 0,
	SYN = 1,
	CLOSING = 2,
	ESTABLISHED = 3,
};

class asio::Isocket_tcp : public std::enable_shared_from_this<asio::Isocket_tcp>
{
public:
	struct SEND_NODE { const_buffer buffer{ nullptr, 0 }; size_t message_count{ 0 }; };

public:
			Isocket_tcp(const boost::asio::any_io_executor& _executor);
	virtual ~Isocket_tcp() noexcept;

public:
	virtual bool send(const const_buffer& _buffer) { return this->process_send({ _buffer, 1 }); }
	virtual bool send(const SEND_NODE& _send) { return this->process_send(_send); }
	virtual bool closesocket() noexcept;
	virtual bool disconnect() noexcept;
			tcp::socket& native_handle() noexcept { return m_socket; }

public:
	virtual void process_connect_complate() = 0;
	virtual bool process_send(const SEND_NODE& _send_node) = 0;
	virtual bool process_closesocket() noexcept = 0;

			void process_connective_closesocket() noexcept;
			bool process_close_native_handle() noexcept;

protected:
			tcp::socket	m_socket;
			std::mutex m_lock_socket;
			std::shared_ptr<Nconnective> m_pconnective;
			std::atomic<ESOCKET_STATUE> m_socket_state;
			friend class Nconnective;
			friend class Nconnector;
			friend class Nacceptor;
};
