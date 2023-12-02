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

//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------
class CGDK::net::io::executable_connect_requestable :
// inherited classes) 
	virtual public				Iexecutable,
	public						Npoolable<executable_connect_requestable>,
	public						factory::_traits_system
{
public:
			executable_connect_requestable() {}
	virtual ~executable_connect_requestable() {}

// framework)
public:
	virtual	intptr_t			process_execute(intptr_t _result, size_t) override;
			void				set_connectable( net::io::connect_requestable::Ntcp* _pConnector) { this->m_pconnect_requestable = _pConnector; }
	virtual void				on_final_release() noexcept override { this->m_pconnect_requestable.reset(); }

// implementation) 
public:
			object_ptr<net::io::connect_requestable::Ntcp>	m_pconnect_requestable;
};

inline intptr_t CGDK::net::io::executable_connect_requestable::process_execute(intptr_t _result, size_t)
{
#if defined(_SYS_EPOLL_H)
	// 1) move connect_requestable
	object_ptr<net::io::connect_requestable::Ntcp> pconnect_requestable = std::move(this->m_pconnect_requestable);

	// check) 
	RETURN_IF(pconnect_requestable.empty(), 0);

	// 2) call 'process_complete_connection'
	pconnect_requestable->process_complete_connecting(_result); 
#else
	// 1) move connect_requestable
	object_ptr<net::io::connect_requestable::Ntcp> pconnect_requestable = std::move(this->m_pconnect_requestable);

	// check) 
	CGASSERT_ERROR(pconnect_requestable.exist());

	// 2) call 'process_complete_connection'
	pconnect_requestable->process_complete_connecting(_result);
#endif

	// return) 
	return intptr_t(0);
}
