#pragma once

class socket_user :
	public CGDK::net::socket::tcp<sMESSAGE_HEAD>,
	public CGDK::Igroupable<socket_user>,
	public CGDK::Nmessage_transmitter
{
private:
	virtual void				on_connect() /*override*/;
	virtual void				on_disconnect(uint64_t) /*override*/;
	virtual CGDK::result_code	on_message(CGDK::sMESSAGE_NETWORK& _msg) /*override*/;

public:
			int					m_user_id = 0;
};
