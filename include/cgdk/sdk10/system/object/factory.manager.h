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

 @class		factory::manager


*/
//-----------------------------------------------------------------------------
class factory::manager :
	public						CGDK::object::Nnameable,
	public						Nmessage_transmitter,
	virtual public				CGDK::object::Idestroyable,
	public						factory::_traits_system
{
protected:
			manager() noexcept;
	virtual	~manager() noexcept;

// public)
public:
			object_ptr<Ifactory> find(int _id_factory) const noexcept;
			object_ptr<Ifactory> find(Ifactory* _pfactory) const noexcept;
			object_ptr<Ifactory> find(const std::string_view _name) const noexcept;

			void				sustain();
			void				sustain(eFACTORY_GC_LEVEL _level);
	[[nodiscard]] bool			is_enable_sustain() const noexcept { return m_flag_sustain;}
			void				enable_sustain(bool _enable_sustain = true) noexcept;
			void				disable_sustain() noexcept { enable_sustain(false);}
			size_t				sustain_threshold(int _index) noexcept { RETURN_IF(_index < 0 || _index >= 4, 0); return *(this->m_size_sustain_threshold + _index); }

	[[nodiscard]] auto			begin() noexcept { return this->m_list_factory.begin();}
	[[nodiscard]] auto			begin() const noexcept { return this->m_list_factory.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_list_factory.end();}
	[[nodiscard]] auto			end() const noexcept { return this->m_list_factory.end();}
	[[nodiscard]] size_t		size() const noexcept { return this->m_list_factory.size(); }
	[[nodiscard]] bool			empty() const noexcept { return this->m_list_factory.empty();}
	[[nodiscard]] bool			exist() const noexcept { return !this->empty();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_lockable_list_factory;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_lockable_list_factory;}
	[[nodiscard]] 				operator std::shared_mutex&() noexcept { return this->get_lockable();}
	[[nodiscard]] 				operator const std::shared_mutex&() const noexcept { return this->get_lockable(); }

	static 	auto				instance() { if (m_s_pinstance.empty()) { initialize_instance(); } return object_ptr<manager>(m_s_pinstance); }
	static	 void				initialize_instance();
	static	 void				set_instance(own_ptr<manager>&& _instance);
	static	 void				reset_instance() noexcept;
	static	 void				detach_instance() noexcept { m_s_pinstance.detach(); }

	static	 void				print_statistics(bool _using_only = false) noexcept;

public:
	static	void				sustain_tls();
	static	size_t				m_s_sustain_serial_now;
	thread_local static size_t	m_s_sustain_serial;

private:
			bool				process_register_factory(Ifactory* _pfactory);
			bool				process_unregister_factory(Ifactory* _pfactory) noexcept;

private:
			std::list<Ifactory*> m_list_registered;
			std::shared_mutex	m_lockable_list_factory;
			std::list<object_ptr<Ifactory>> m_list_factory;
			int					m_factory_serial;
			size_t				m_size_sustain_threshold[4];
			bool				m_flag_sustain;

	static std::mutex			m_s_lockable_create;
	static own_ptr<manager>		m_s_pinstance;

		friend class CGDK::Ifactory;

	virtual	result_code destroy() noexcept override;
};


}