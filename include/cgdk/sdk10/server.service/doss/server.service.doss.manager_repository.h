//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                              Account Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::manager_repository
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::manager_repository :
// inherited classes)
	public						object::Nnameable,
	virtual public				object::Idestroyable,
	virtual public				Nmessage_transmitter,
	virtual public				Imessageable
{
// definitions)
public:
			typedef	circular_list<Irepository*>::const_iterator	ITERATOR;

// constructor/destructor)
public:
			manager_repository();
	virtual	~manager_repository() noexcept;

// Public) 
public:
//	// 1) Iterator¿ë.
	[[nodiscard]] ITERATOR		begin() noexcept { return m_list_repository.begin();}
	[[nodiscard]] ITERATOR		end() noexcept { return m_list_repository.end();}
	[[nodiscard]] size_t		get_count() noexcept { return m_list_repository.size();}
	[[nodiscard]] object_ptr<Irepository> find(sREPOSITORY_ID _rid) const noexcept;
	[[nodiscard]] object_ptr<Irepository> find(const std::string_view _name) const noexcept;

	// 2) lock
	[[nodiscard]]				operator lockable<>&() noexcept { return m_list_repository;}

	// 3) Init Instance/RunExecutor										  
	static	auto				get_instance() { if(m_pinstance.empty()){ init_instance();} return static_cast<object_ptr<manager_repository>>(m_pinstance);}
	static	void				set_instance(own_ptr<manager_repository>&& _pInstance);
	static	void				reset_instance() noexcept;

			void				register_repository(Irepository* _prepository);
			void				unregister_repository(Irepository* _prepository) noexcept;

// implementation) 
private:
	// 1) Pool List.
			lockable<circular_list<Irepository*>> m_list_repository;
			uint64_t			m_repository_serial = 0;

	// 3) instance
	static	own_ptr<manager_repository> m_pinstance;
	static	void				init_instance();
	static	lockable<>			m_lockable_create;

public:
	// 4) destroy
	virtual	result_code			destroy() noexcept override;

	// 5) process message
	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// Friends)
	friend	class Irepository;
};


}