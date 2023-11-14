//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
/**

 @class		executor::manager
 @brief		executor °ü¸®ÀÚ.
 @todo		
 @ref		
 @details	\n
 
*///-----------------------------------------------------------------------------
class executor::manager :
	public						object::Nnameable,
	public						Nmessage_transmitter,
	virtual public				object::Idestroyable,
	public						factory::_traits_system
{
public:
		using ITERATOR = circular_list<Iexecutor*>::iterator;

protected:
			manager() noexcept;
	virtual ~manager() noexcept;

public:
	[[nodiscard]] size_t		size() noexcept { return this->m_list_executor.size();}
	[[nodiscard]] bool			empty() const noexcept { return this->m_list_executor.empty();}
	[[nodiscard]] bool			exist() const noexcept { return !this->empty();}
	[[nodiscard]] auto			begin() noexcept { return this->m_list_executor.begin();}
	[[nodiscard]] auto			begin() const noexcept { return this->m_list_executor.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_list_executor.end();}
	[[nodiscard]] auto			end() const noexcept { return this->m_list_executor.end();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_lockable_list_executor;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_lockable_list_executor;}
	[[nodiscard]] 				operator std::shared_mutex&() noexcept{ return this->m_lockable_list_executor;}
	[[nodiscard]] 				operator const std::shared_mutex&() const noexcept{ return this->m_lockable_list_executor;}

	static 	auto				instance() { if(m_s_pinstance.empty()) { initialize_instance(); } return object_ptr<manager>(m_s_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_s_pinstance.detach(); }

	static	void				print_statistics(bool _using_only = false) noexcept;

private:
			bool				process_register_executor(Iexecutor* _pexecutor);
			bool				process_unregister_executor(Iexecutor* _pexecutor) noexcept;
	virtual	void				process_on_register() {}
	virtual	void				process_on_unregister() {}

			std::shared_mutex	m_lockable_list_executor;
			circular_list<Iexecutor*> m_list_executor;
			int					m_executor_serial;

	static std::mutex			m_s_lockable_create;
	static own_ptr<manager>		m_s_pinstance;

	friend	class CGDK::Iexecutor;

private:
	virtual	result_code			destroy() noexcept override;
};

object_ptr<Iexecutor>			get_current_executor() noexcept;


}