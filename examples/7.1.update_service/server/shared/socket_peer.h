//*****************************************************************************
//*                                                                           *
//*                            CGCII update system                            *
//*                       simple update server ver.10.0                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
//*                          http://www.CGCIII.co.kr                          *
//*                                                                           *
//*****************************************************************************
#pragma once

class socket_peer :
	public						net::socket::tcp<>,
	public						Nmessage_transmitter,
	public						Igroupable<socket_peer>
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
			int					m_idx_list = -1;

			update::sUPDATE_VERSION	m_version_require;
			update::sUPDATE_VERSION	m_version_now;
};
