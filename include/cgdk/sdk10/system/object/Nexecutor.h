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

 @class		Iexecutor
 

*///-----------------------------------------------------------------------------
class Nexecutor : virtual public Iexecutor
{
public:
			Nexecutor() noexcept {}
			Nexecutor(std::string_view _name) noexcept { this->process_set_name(_name); }
	virtual ~Nexecutor() noexcept {}

protected:
	[[nodiscard]] virtual bool	process_is_this(std::string_view _compare) const noexcept override { return this->Iexecutor::m_statistics.name == _compare; }
	[[nodiscard]] virtual std::string_view process_get_name() const noexcept override { return this->Iexecutor::m_statistics.name; }
	virtual	void				process_set_name(std::string_view _name) override { this->Iexecutor::m_statistics.name = _name; }
};


}