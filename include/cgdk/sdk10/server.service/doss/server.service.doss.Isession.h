//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
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
// doss::CAccount
//
//  State of Account
//
//   
//
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Isession :
// inherited classes)
	virtual public				object::Idestroyable
{
public:
	virtual	void				process_entity_transaction_request	(Itransactable* _ptransactable) noexcept PURE;
	virtual	void				process_entity_transaction_complete	(Itransactable* _ptransactable) noexcept PURE;
	virtual void				process_entity_set					(Itransactable* _ptransactable) PURE;
	virtual	bool				process_entity_reset				(Ientity* _pentity, const sCHECKIN_ID& _cid, bool _is_force) noexcept PURE;

};


}