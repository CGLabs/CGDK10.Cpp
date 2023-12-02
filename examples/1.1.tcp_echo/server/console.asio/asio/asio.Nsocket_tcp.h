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

class asio::Nsocket_tcp : public Isocket_tcp
{
public:
			Nsocket_tcp();
	virtual ~Nsocket_tcp() noexcept;

protected:
	virtual void on_connect() {}
	virtual void on_disconnect() noexcept {}
	virtual int on_message(const const_buffer& /*_msg*/) { return 0; }

	virtual void process_connect_complate() override;
	virtual bool process_closesocket() noexcept override;
	virtual bool process_send(const SEND_NODE& _send_node) override;
			bool process_send_sync(const SEND_NODE& _send_node);
			void process_receive_async();
			friend class Nconnector;

			mutable_buffer m_received_msg;
			mutable_buffer m_receiving_msg;
};
