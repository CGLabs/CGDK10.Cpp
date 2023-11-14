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
// api::manager_perfornamce_query
//
//-----------------------------------------------------------------------------
class api::manager_perfornamce_query :
// inherited classes)
	virtual public				Ireferenceable,
	public						factory::_traits_system
{
// constructor/destructor)
protected:
			manager_perfornamce_query();
	virtual ~manager_perfornamce_query() noexcept;

// publics)
public:
			bool				update_query();

	static	object_ptr<manager_perfornamce_query> instance() { if (m_pinstance.empty()) initialize_instance(); return m_pinstance; }

// implementation)
private:
			bool				add_counter(performance_counter* _pcounter, std::string_view _query);
			bool				add_counter(performance_counter* _pcounter, std::wstring_view _query);
			bool				remove_counter(performance_counter* _pcounter) noexcept;

private:
			HQUERY				m_hquery;
			lockable<>			m_lockable_counter;

private:
	static	void				initialize_instance();
	static	lockable<>			m_lockable_create;
	static	own_ptr<manager_perfornamce_query>	m_pinstance;

	friend	class performance_counter;
};


}