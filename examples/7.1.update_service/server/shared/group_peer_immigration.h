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

class group_socket_immigration :
	public						group::list_sender<socket_peer>,
	public                      object::Ninitializable_startable,
	public						net::io::messageable::Nbase,
	public						schedulable::Nexecutable
{
private:
	virtual	void				on_start(context& _msg) override;
	virtual	void				on_stopping() override;
	virtual	result_code			on_member_entering(socket_peer* _pmember, sMESSAGE& _msg) override;
	virtual	uintptr_t			on_member_leaving(socket_peer* _pmember, uintptr_t _param) override;
	virtual	void				on_execute() override;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_NETWORK_CERTIFY_REQUEST(sMESSAGE_NETWORK& _msg);
};
