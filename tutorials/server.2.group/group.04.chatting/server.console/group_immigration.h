#pragma once

class group_immigration : 
	public CGDK::group::list_sender<socket_user>,
	public CGDK::net::io::messageable::Nbase
{
protected:
	virtual	void				on_member_entered(socket_user* _pmember, CGDK::sMESSAGE& param) /*override*/;
	virtual	uintptr_t			on_member_leaving(socket_user* _pmember, uintptr_t _param) /*override*/;

	virtual CGDK::result_code	on_message(CGDK::sMESSAGE_NETWORK& _msg) override;
			CGDK::result_code	on_message_REQUEST_LOGIN(CGDK::sMESSAGE_NETWORK& _msg);
};
