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
// doss::CRepositoryDBSQL
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TENTITY = doss::Ientity, class TCREATE = TENTITY>
class doss::repository::rdb :
	public						Nrepository<TENTITY>,
	public						Nmessage_transmitter,
	public                      object::Ninitializable_startable,
	public						object::Nnameable,
	public						schedulable::Nexecutable
{
public:
			rdb();
			rdb(const std::string_view _name);
	virtual	~rdb() noexcept;

protected:
	virtual	void				on_initializing	(context& _msg) override;
	virtual	void				on_initialize (context& _msg) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;
	virtual	void				on_starting (context& _msg) override;
	virtual	void				on_start (context& _msg) override;
	virtual	void				on_stop_request () override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;
	virtual	void				on_execute () override;

protected:
	[[nodiscard]] virtual object_ptr<TENTITY> process_alloc_entity(sENTITY_ID _entity_id) override;
};


}

#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.rdb.inl"
