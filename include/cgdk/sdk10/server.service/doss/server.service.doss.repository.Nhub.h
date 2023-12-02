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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::CAccount
//-----------------------------------------------------------------------------
namespace CGDK
{

template<class TENTITY = doss::Ientity>
class doss::repository::Nhub :
// inherited classes)
	virtual public				Irepository,
	public						object::Nnameable,
	public                      object::Ninitializable_startable
{
// constructor/destructor)
public:
			Nhub();
			Nhub(const std::string_view _name);
	virtual ~Nhub() noexcept;

// frameworks)
protected:
	// 1) initialize/destroy
	virtual	void				on_initializing	(context& _msg) override;
	virtual	void				on_initialize (context& _msg) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;

	// 2) start/stop
	virtual	void				on_starting (context& _msg) override;
	virtual	void				on_start (context& _msg) override;
	virtual	void				on_stop_request () override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

// implementations)
protected:
	//! @brief 
	virtual result_code			process_request_transaction	(Itransactable* _ptransactable) override;

	//! @brief 계정의 '_auth에 맞는 'Repository'를 되돌린다. @param _auth 인증정보 @return 'Repository'
	[[nodiscard]] virtual object_ptr<doss::Nrepository<TENTITY>> process_find_repository(const shared_buffer& _buffer) PURE;

	// 1) repository
			lockable<circular_list<object_ptr<doss::Nrepository<TENTITY>>>> m_list_repository;
};


}

#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.Nhub.inl"
