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

 @class		schedulable::Ninitializable_startable
 

*///-----------------------------------------------------------------------------
class schedulable::Ninitializable_startable :
	virtual public				schedulable::Iexecutable,
    public				        object::Ninitializable_startable,
    public				        object::Nnameable
{
protected:
			Ninitializable_startable() noexcept {}
			Ninitializable_startable(std::string_view _name) noexcept : object::Nnameable(_name) {}
	virtual ~Ninitializable_startable() noexcept {}

protected:
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_destroying() noexcept override;
};


}
