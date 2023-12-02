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
// net::io::connective::manager
//
//-----------------------------------------------------------------------------
class net::io::connective::manager : 
// inherited classes) 
	public						object::Nnameable,
	virtual public				object::Idestroyable,
	virtual public				Nmessage_transmitter,
	public						factory::_traits_system
{
// definitions) 
public:
			using iterator_t = circular_list<net::io::Iconnective*>::const_iterator;

// constructor/destructor) 
protected:
			manager();
	virtual	~manager() noexcept;

// publics) 
public:
	// 1) iterator 
	[[nodiscard]] std::size_t	size() const noexcept { return this->m_list_connective.size();}
	[[nodiscard]] auto			begin() noexcept { return this->m_list_connective.begin();}
	[[nodiscard]] auto			begin() const noexcept { return this->m_list_connective.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_list_connective.end();}
	[[nodiscard]] auto			end() const noexcept { return this->m_list_connective.end();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_lockable_list_connective;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_lockable_list_connective;}
	[[nodiscard]] 				operator std::shared_mutex&() noexcept { return this->get_lockable();}
	[[nodiscard]] 				operator const std::shared_mutex& () const noexcept { return this->get_lockable();}

	// 2) singleton
	static 	auto				instance() { if (m_pinstance.empty()) { initialize_instance(); } return object_ptr<manager>(m_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_pinstance.detach(); }

// implementations) 
private:
	// 1) ...
			std::shared_mutex	m_lockable_list_connective;
			circular_list<net::io::Iconnective*> m_list_connective;
			std::size_t			m_connective_serial;

			void				join( net::io::Iconnective* _pconnective);
			void				leave( net::io::Iconnective* _pconnective) noexcept;

	// 2) instance
	static own_ptr<manager>		m_pinstance;
	static std::mutex			m_lockable_create;

public:
	// 3) destroy
	virtual	result_code			destroy() noexcept override;

	// Friend) 
	friend	net::io::Iconnective;
};


}