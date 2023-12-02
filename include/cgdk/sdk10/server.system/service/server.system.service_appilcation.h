//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// template<class TCLASS>
// service_application
//
//-----------------------------------------------------------------------------
template<class TCLASS>
class server_system::service_application :
	public						Nservice_application
{
public:
	static	object_ptr<TCLASS>	instance() { if(m_pinstance_create.empty()) { initialize_instance();} return m_pinstance_create;}
	[[nodiscard]] static object_ptr<TCLASS>	peek_instance() { return m_pinstance_create; }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<TCLASS>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;

	static	int					run(int _argc, char** _ppargv);

protected:
	// 2) Instance
	static	object_ptr<TCLASS>	m_pinstance_create;
};

template<class TCLASS>
object_ptr<TCLASS> server_system::service_application<TCLASS>::m_pinstance_create;


template<class TCLASS>
void server_system::service_application<TCLASS>::initialize_instance()
{
	scoped_lock(m_lockable_create)
	{
		// check) 
		RETURN_IF(m_pinstance_create.exist());
		
		// 1) create
		auto pinstance = make_own<TCLASS>();

		// 2) set instance
		m_pinstance_create = pinstance;
		m_pinstance = std::move(pinstance);
	}
}

template<class TCLASS>
void server_system::service_application<TCLASS>::set_instance(own_ptr<TCLASS>&& _pinstance) noexcept
{
	// declare) 
	own_ptr<Nservice_application> pinstance_old;

	scoped_lock(m_lockable_create)
	{ 
		// 1) store old instance
		pinstance_old = std::move(m_pinstance);

		// 2) set instance
		m_pinstance_create = _pinstance;
		m_pinstance = std::move(_pinstance);
	}

	// 3) reset instance
	pinstance_old.reset();
}

template<class TCLASS>
void server_system::service_application<TCLASS>::reset_instance() noexcept
{
	// declare) 
	own_ptr<Nservice_application> pinstance_old;

	scoped_lock(m_lockable_create)
	{
		// 1) move instance
		pinstance_old = std::move(m_pinstance);

		// 2) reset create_instance
		m_pinstance_create.reset();
	}

	// 3) reset old instance
	pinstance_old.reset();
}

template<class TCLASS>
int server_system::service_application<TCLASS>::run(int _argc, char** _ppargv)
{
	// 1) service process
#if defined(_WIN32)
	auto result = Nservice_application::process_service_parpare(_argc, _ppargv, instance());
#elif defined(__linux__)
	auto result = Nservice_application::process_service_parpare(_argc, _ppargv);
#else
#endif
	// check) 
	RETURN_IF(result, 0);

	//  2) start~
	return instance()->process_run(_argc, _ppargv);
}


}