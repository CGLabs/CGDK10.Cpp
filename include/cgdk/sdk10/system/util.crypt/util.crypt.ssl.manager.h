//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Web Classes                                *
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
// CGDK::crypt::ssl_manager
//
//
//-----------------------------------------------------------------------------
namespace crypt
{

class ssl_manager :
// Inherited Classes)
	public						object::Nnameable,
	virtual public				object::Idestroyable
{
// constructor/destructor)
public:
			ssl_manager() noexcept;
	virtual ~ssl_manager() noexcept;

// public)
public:
	// 1) initialize Instance/run_executor
	static	auto				instance() { if(m_s_pinstance.empty()){ initialize_instance();} return object_ptr<ssl_manager>(m_s_pinstance);}
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<ssl_manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;

	// 2) SSL Methods
	[[nodiscard]] const SSL_METHOD*	get_ssl_method(int _type) const noexcept;

// implementation)
private:
	// 1) SSL Components
			lockable<std::vector<const SSL_METHOD*>> m_vector_ssl_method;

private:
	// 2) Instance
	static	std::mutex			m_s_lockable_create;
	static	own_ptr<ssl_manager> m_s_pinstance;
	static	void				_set_instance(own_ptr<ssl_manager>&& _instance);

public:
	// 3) destroy
	virtual result_code			initialize();
	virtual	result_code			destroy() noexcept override;
};


}
}