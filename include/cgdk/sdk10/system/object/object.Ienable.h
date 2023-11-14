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

//-----------------------------------------------------------------------------
/**

 @class		object::Ienable

*/
//-----------------------------------------------------------------------------
class CGDK::object::Ienable : virtual public Ireferenceable
{
public:
	virtual ~Ienable() noexcept {}

public:
			bool				enable(bool _is_state = true) { return this->process_set_enable(_is_state);}
			bool				disable() { return this->process_set_enable(false);}
																  
	[[nodiscard]] bool			is_enable() const noexcept { return this->process_get_enable();}
	[[nodiscard]] bool			is_disable() const noexcept { return !this->process_get_enable();}

protected:
	virtual	bool				process_set_enable(bool _is_state) PURE;
	virtual	bool				process_get_enable() const PURE;
};
