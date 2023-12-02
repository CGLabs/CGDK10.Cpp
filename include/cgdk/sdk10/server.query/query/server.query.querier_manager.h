//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// query::manager_querier
//
//
//-----------------------------------------------------------------------------
class query::manager_querier :
// inherited classes)
	public						object::Nnameable,
	virtual public				object::Idestroyable,
	virtual public				Nmessage_transmitter,
	virtual public				Imessageable
{
// definitions)
public:
			typedef	circular_list<Iquerier*>::const_iterator ITERATOR;

// constructor/destructor) 
public:
			manager_querier();
	virtual ~manager_querier();

// public) 
public:
	// 1) iterator
			ITERATOR			begin() { return m_list_querier.begin();}
			ITERATOR			end() { return m_list_querier.end();}
			int					count() { return (int)m_list_querier.size();}
															
			std::recursive_mutex& get_lockable() noexcept { return m_lockable_list_querier; }
			const std::recursive_mutex& get_lockable() const noexcept { return m_lockable_list_querier; }
								operator std::recursive_mutex&() noexcept { return m_lockable_list_querier;}
								operator const std::recursive_mutex& () const noexcept { return m_lockable_list_querier; }

	// 2) init instance/run_executor
	static	auto				instance() { if(m_pinstance.empty()){ initialize_instance();} return object_ptr<manager_querier>(m_pinstance);}
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<manager_querier>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_pinstance.detach(); }

// implementation) 
private:
	// 1) querier list
			std::recursive_mutex m_lockable_list_querier;
			circular_list<Iquerier*> m_list_querier;
			int					m_db_querier_serial;
	// 2) register/unregister
			void				register_querier(Iquerier* _pquerier);
			void				unregister_querier(Iquerier* _pquerier) noexcept;

	// 3) instance
	static	lockable<>			m_lockable_create;
	static	own_ptr<manager_querier> m_pinstance;

public:
	// 4) destroy
	virtual	result_code			destroy() noexcept override;

	// 5) process message
	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// friends)
	friend	Iquerier;
};


}