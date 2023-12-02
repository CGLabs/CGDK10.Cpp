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

 @class		executable::iterative
 

*///-----------------------------------------------------------------------------
class executable::Iiterative : virtual public executable::Ischedulable
{
public:
	virtual ~Iiterative() noexcept {}

public:
			auto				interval() const noexcept { return this->m_duration_interval; }
			void				interval(chrono::tick::duration _duration_interval) noexcept { this->m_duration_interval = _duration_interval; }

protected:
	virtual	void				on_execute() PURE;

protected:
	virtual	intptr_t			process_execute(intptr_t _result, size_t _param) override;
			chrono::tick::duration m_duration_interval = chrono::tick::duration::zero();
};


}
