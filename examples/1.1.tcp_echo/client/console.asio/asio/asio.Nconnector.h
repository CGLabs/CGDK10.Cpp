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

class asio::Nconnector : virtual public Nconnective
{
public:
			Nconnector();
	virtual ~Nconnector() noexcept;

public:
	void start();
	void close() noexcept;

	void request_connect(boost::asio::ip::tcp::endpoint _endpoint_connect);
	virtual std::shared_ptr<Isocket_tcp> process_create_socket() = 0;
	void process_connect_request_complete(std::shared_ptr<Isocket_tcp> _socket, const boost::system::error_code& _error);

private:
			boost::asio::any_io_executor m_executor;
};
