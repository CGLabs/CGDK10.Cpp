//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials update - update service                      *
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

class socket_tcp :
	public						net::socket::tcp<>,
	public						Nmessage_transmitter,
	public						Igroupable<socket_tcp>
{
public:
			void				set_update_sender(own_ptr<update::sender>&& _update_sender);
			void				reset_update_sender() noexcept;

private:
	virtual void				on_connect() override;
	virtual void				on_disconnect(uint64_t) override;
	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;

public:
			own_ptr<update::sender> m_pupdate_sender;
};
