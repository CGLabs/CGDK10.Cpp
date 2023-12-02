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

class asio::Nacceptor : virtual public Nconnective
{
public:
			Nacceptor();
	virtual ~Nacceptor() noexcept;

public:
			void start(tcp::endpoint _endpoint);
			void close() noexcept;

private:
			void process_accept();
	virtual std::shared_ptr<Isocket_tcp> process_create_socket() = 0;

private:
			std::unique_ptr<tcp::acceptor> m_pacceptor;
};