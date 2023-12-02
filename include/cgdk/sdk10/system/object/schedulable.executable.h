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

 @class		schedulable::executable


*///-----------------------------------------------------------------------------
class schedulable::executable :
	public                      schedulable::Nexecutable,
    public                      schedulable::Ninitializable_startable
{
public:
			struct START_PARAMETER
			{
				chrono::tick::duration tick;
			};

public:
			executable(std::string_view _name) noexcept : schedulable::Ninitializable_startable(_name) { this->set_object_type(eOBJECT_TYPE::SCHEDULABLE_EXECUTABLE);}
	virtual ~executable() noexcept {}

public:
			result_code			start() { return this->Ninitializable_startable::start();}
			result_code			start(const START_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, sizeof(START_PARAMETER))); return this->start(temp); }
			result_code			start(const context& _context) { return this->Ninitializable_startable::start(_context); }
	virtual	result_code			start(context& _context) override { return this->Ninitializable_startable::start(_context);}

protected:
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
};


}
