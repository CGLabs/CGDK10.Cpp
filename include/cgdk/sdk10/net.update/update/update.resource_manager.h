//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
// ----------------------------------------------------------------------------
//
// resource::updatable::folder
//
//
// ----------------------------------------------------------------------------
class CGDK::update::resource_manager :
	public                      object::Ninitializable_startable,
	public						object::Nnameable
{
public:
			object_ptr<resource::Iupdatable> get_resource(UPDATE_RESOURCE_ID _update_resource_id) const;

protected:
			lockable<>			m_cs_map_resource;
			std::map<UPDATE_RESOURCE_ID, object_ptr<resource::Iupdatable>> m_map_resource;

	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;
};
