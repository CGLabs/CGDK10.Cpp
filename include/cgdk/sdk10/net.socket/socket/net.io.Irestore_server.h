//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// net::io::Irestore_server
//
//
//-----------------------------------------------------------------------------
class net::io::Irestore_server :
	public						net::io::connectable::tcp::Ndefault,
	virtual public				net::io::messageable::Nbase,
	virtual public				net::io::Isender
{
protected:
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state) override;
	virtual	bool				process_on_suspend (uint64_t _disconnect_reason);

public:
	virtual	object_ptr<Irestorable_server> process_alloc_restorable () PURE;

protected:
	virtual	result_code			process_message (sMESSAGE& _msg) override;

protected:
			object_ptr<Irestorable_server> m_prestorable;
			object_ptr<restore_manager> m_prestore_manager;

			friend class restore_manager;
};

template <class TRESTORABLE>
class net::io::Nrestore_server : net::io::Irestore_server
{
protected:
	virtual	object_ptr<net::io::Irestorable_server>	process_alloc_restorable() { return make_object<TRESTORABLE>(); }
};




}