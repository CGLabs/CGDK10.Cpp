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
//
// doss::Nrepository<TENTITY, TCREATE>
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TENTITY = doss::Ientity>
class doss::Nrepository :
// inherited classes)
	virtual public				Irepository
{
// public)
public:
	virtual	void				checkout_all() noexcept;

// framework)
protected:
	//! @brief 개체를 얻는다. @return 생성한 계정 객체의 포인터
	[[nodiscard]] virtual object_ptr<Ientity> process_entity_get (sENTITY_ID _entity_id) override;
	[[nodiscard]] virtual object_ptr<Ientity> process_entity_find (sENTITY_ID _entity_id) const noexcept override;

	//! @brief 계정 객체를 생성한다. @return 생성한 계정 객체의 포인터
	[[nodiscard]] virtual object_ptr<TENTITY>	process_alloc_entity (sENTITY_ID _entity_id);

public:
	// 2) Account Info
			std::map<sENTITY_ID, object_ptr<TENTITY>>  m_map_entity_by_eid;
};

template<class TENTITY>
void doss::Nrepository<TENTITY>::checkout_all() noexcept
{
	scoped_lock(m_lockable_map_entity)
	{
		for (const auto& iter : m_map_entity_by_eid)
		{
			iter.second->checkout_all();
		}
	}
}

template<class TENTITY>
object_ptr<doss::Ientity> doss::Nrepository<TENTITY>::process_entity_get(sENTITY_ID _entity_id)
{
	// declare) 
	object_ptr<TENTITY>	pentity;

	// check) 
	RETURN_IF(get_object_state() < eOBJECT_STATE::STOPPED, pentity);

	// 1) get entity object
	scoped_lock(m_lockable_map_entity)
	{
		// 1) find entity object 
		auto iter_find = m_map_entity_by_eid.find(_entity_id);

		// 2) if find
		if (iter_find != m_map_entity_by_eid.end())
		{
			// check)
			CGASSERT_ERROR(iter_find->second->m_eid == _entity_id);

			// - set pentity
			pentity = iter_find->second;
		}
		else
		{
			// !주의)- checkin id는 여기서 발급되지 않는다. checkin id는 checkin을 시도했을 때 발급된다.

			// - create pentity
			pentity = process_alloc_entity(_entity_id);

			// check)
			CGASSERT_ERROR(pentity.exist());

			// - set value
			pentity->m_prepository = this;

			// - insert entity by eid 
			m_map_entity_by_eid.insert({ _entity_id , pentity });
		}
	}

	// return)
	return pentity;
}

template<class TENTITY>
object_ptr<doss::Ientity> doss::Nrepository<TENTITY>::process_entity_find(sENTITY_ID _entity_id) const noexcept
{
	// declare) 
	object_ptr<TENTITY>	pentity;

	// 1) get entity object
	scoped_lock(m_lockable_map_entity)
	{
		// 1) find entity object 
		auto iter_find = m_map_entity_by_eid.find(_entity_id);

		// 2) if find
		if (iter_find != m_map_entity_by_eid.end())
		{
			// check)
			CGASSERT_ERROR(iter_find->second->m_eid == _entity_id);

			// - set pentity
			pentity = iter_find->second;
		}
	}

	// return)
	return pentity;
}

template<class TENTITY>
object_ptr<TENTITY> doss::Nrepository<TENTITY>::process_alloc_entity(sENTITY_ID _entity_id)
{
	// 1) alloc entity object
	auto pentity = make_object<TENTITY>();

	// 2) set entity_id 
	pentity->m_eid = _entity_id;

	// return)
	return pentity;
}


}
