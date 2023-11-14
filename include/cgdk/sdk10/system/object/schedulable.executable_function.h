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

 @class		schedulable::executable_function<T>
 @brief		독립 객체화 가능한 schedulable::Nexecutable_function<T>
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TEXECUTE = std::function<void()>>
class schedulable::executable_function :
	public						schedulable::Nexecutable_function<TEXECUTE>,
	public                      schedulable::Ninitializable_startable
{
			struct START_PARAMETER
			{
				TEXECUTE		function;
				chrono::tick::duration tick;
			};

public:
	explicit executable_function() { this->set_object_type(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	explicit executable_function(std::string_view _name) : schedulable::Ninitializable_startable(_name) { this->set_object_type(eOBJECT_TYPE::SCHEDULABLE_FUNCTION); }
	virtual ~executable_function() noexcept	{}

public:
			result_code			start() { return this->object::Nstartable::start();}
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }; return this->start(temp); }
	virtual	result_code			start(context& _context) override { return this->object::Nstartable::start(_context);}

protected:
			void				_procss_get_parameter_execute_function(const context& _context);
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
};

void get_parameter_execute_interval(schedulable::Iexecutable* _pschedulable, const context& _context);

template <class TEXECUTE>
result_code schedulable::executable_function<TEXECUTE>::_process_initialize(context& _context)
{
	// declare) 
	START_PARAMETER parameter;

	// 1A) 
	if (_context.type() == eCONTEXT_VALUE_TYPE::BUFFER_)
	{
		// - get parameter
		parameter = _context.v.value_buffer.front<START_PARAMETER>();

		// - get function
		if (parameter.function != nullptr)
		{
			this->set_function(parameter.function);
		}

		// - set interval
		if (parameter.tick != chrono::tick::duration::zero())
		{
			this->execute_interval(parameter.tick);
		}
	}
	// 1B)
	else
	{
		get_parameter_execute_interval(this, _context);
	}

	// 2) ...
	return this->schedulable::Ninitializable_startable::_process_initialize(_context);
}

template <class TEXECUTE>
result_code schedulable::executable_function<TEXECUTE>::_process_start(context& _context)
{
	// declare) 
	START_PARAMETER parameter;

	// 1A)
	if (_context.type() == eCONTEXT_VALUE_TYPE::BUFFER_)
	{
		// - get parameter
		parameter = _context.v.value_buffer.front<START_PARAMETER>();

		// - get function
		if (parameter.function != nullptr)
		{
			this->set_function(parameter.function);
		}

		// - set interval
		if (parameter.tick != chrono::tick::duration::zero())
		{
			this->execute_interval(parameter.tick);
		}
	}
	// 1B)
	else
	{
		get_parameter_execute_interval(this, _context);
	}

	// 2) ...
	return this->schedulable::Ninitializable_startable::_process_start(_context);
}


}