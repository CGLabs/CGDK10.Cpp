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

 @class		object::Nstate

*/
//-----------------------------------------------------------------------------
class object::Nstate :virtual public object::Istate, virtual public Ireferenceable
{
public:
			Nstate() noexcept : m_state_object(eOBJECT_STATE::NONE) {}
			Nstate(eOBJECT_STATE _init_state) noexcept : m_state_object(_init_state) {}
	virtual	~Nstate() noexcept { CGASSERT_ERROR(this->m_state_object == eOBJECT_STATE::NONE); }

public:
	[[nodiscard]] virtual eOBJECT_STATE get_object_state() const noexcept override { return this->m_state_object;}
	virtual	eOBJECT_STATE		set_object_state(eOBJECT_STATE _state) noexcept  override { eOBJECT_STATE state_old = this->m_state_object.exchange(_state); if(state_old != _state) this->process_state_changed(_state, state_old); return state_old; }
	virtual	bool				set_object_state_if(eOBJECT_STATE _state_compare, eOBJECT_STATE _state) noexcept override { bool is_changed = this->m_state_object.compare_exchange_weak(_state_compare, _state); if(is_changed) this->process_state_changed(_state, _state_compare); return is_changed; }

protected:
	virtual	void				process_state_changed(eOBJECT_STATE /*_state_new*/, eOBJECT_STATE /*_state_old*/) {}

	virtual	void				on_final_release() noexcept override
	{
		auto pstartable = dynamic_cast<object::Istartable*>(this);
		if (pstartable != nullptr)
			pstartable->stop();

		auto pdestroyable = dynamic_cast<object::Idestroyable*>(this);
		if (pdestroyable != nullptr)
			pdestroyable->destroy();
	}

protected:
			std::atomic<eOBJECT_STATE>	m_state_object;
};


}