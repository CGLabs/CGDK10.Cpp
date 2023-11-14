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
// Iquerier
//
//
//-----------------------------------------------------------------------------
class Iquerier :
// inherited classes)
	virtual public				query::statistics::Nquerier,
	virtual public				object::Iinitializable,
	virtual public				object::Istartable,
	virtual public				object::Istate,
	virtual public				object::Iidentifiable
{
// constructor/destructor)
public:
	virtual ~Iquerier() noexcept {}

// framework)
public:
			void				set_max_retry_on_fail(size_t _max_retry) { CGASSERT_ERROR(_max_retry <= 64); if(_max_retry > 64) return; this->m_max_retry_on_fail = _max_retry; }
	[[nodiscard]] size_t		get_max_retry_on_fail() const noexcept { return this->m_max_retry_on_fail;}

private:
			int					m_id_querier = 0;
			size_t				m_max_retry_on_fail = 8;
			friend class query::manager_querier;

// implementation)
protected:
			void				register_querier() { query::manager_querier::instance()->register_querier(this);}
			void				unregister_querier() noexcept { query::manager_querier::instance()->unregister_querier(this);}
};


}