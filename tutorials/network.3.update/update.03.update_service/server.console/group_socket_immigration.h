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

class group_socket_immigration :
	public						group::list_sender<socket_tcp>,
	public                      object::Ninitializable_startable,
	public						net::io::messageable::Nbase,
	public						schedulable::Nexecutable
{
private:
	virtual	void				on_start(context& _msg) override;
	virtual	void				on_stopping() override;
	virtual	result_code			on_member_entering(socket_tcp* _pmember, sMESSAGE& _msg) override;
	virtual	uintptr_t			on_member_leaving(socket_tcp* _pmember, uintptr_t _param) override;
	virtual	void				on_execute() override;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_NETWORK_CERTIFY_REQUEST(sMESSAGE_NETWORK& _msg);
};
