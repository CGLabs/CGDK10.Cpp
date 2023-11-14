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
// net::io::binder::manager
//
// 1. net::io::binder::manager는~
//    모든 bind되는 socket을 관리하는 manager이다.
//    net::io::Ibinder를 상속받아 bind한 객체는 이 manager에 등록되어 관린된다.
//    일반적으로 net::io::Ibinder를 상속받는 객체는 접속이 필요한 Client TCP socket,
//    혹은 UDP socket들이다.
//
//-----------------------------------------------------------------------------
class net::io::binder::manager :
// inherited classes)
	public						object::Nnameable,
	virtual public				object::Idestroyable,
	virtual public				Nmessage_transmitter
{
// definitions) 
public:
			using ITERATOR = circular_list<net::io::Ibinder*>::const_iterator;

// constructor/destructor)
protected:
			manager();
	virtual	~manager() noexcept;

// publics) 
public:
	// 1) Iterator용.
	[[nodiscard]] std::size_t	size() const noexcept { return this->m_list_binder.size();}
	[[nodiscard]] auto			begin() noexcept { return this->m_list_binder.begin();}
	[[nodiscard]] auto			begin() const noexcept { return this->m_list_binder.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_list_binder.end();}
	[[nodiscard]] auto			end() const noexcept { return this->m_list_binder.end();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_lockable_list_binder;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_lockable_list_binder;}
	[[nodiscard]] 				operator std::shared_mutex&() noexcept	{ return this->m_lockable_list_binder;}
	[[nodiscard]] 				operator const std::shared_mutex& () const noexcept { return this->m_lockable_list_binder;}

	// 2) Init Instance/run_executor									  
	static 	auto				instance() { if (m_pinstance.empty()) { initialize_instance(); } return object_ptr<manager>(m_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_pinstance.detach(); }

// implementations) 
private:
	// 1) Pool List.
			std::shared_mutex	m_lockable_list_binder;
			std::set<net::io::Ibinder*> m_list_binder;

	// 2) join/leave
			void				join(net::io::Ibinder* _pbinder, net::io::statistics::Nsocket* _pstatistics_socket);
			void				leave(net::io::Ibinder* _pbinder) noexcept;

	// 3) Instance
	static own_ptr<manager>		m_pinstance;
	static std::mutex			m_lockable_create;

public:
	// 4) destroy
	virtual	result_code			destroy() noexcept override;

	// Friend)
	friend	class net::io::Ibinder;
};


}