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

 @class		Nschedulable
 @brief		
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class Nschedulable :
		virtual public			Ischedulable
{
public:
	virtual	~Nschedulable() noexcept {}

// public)
public:
	[[nodiscard]] auto			execute_interval() const noexcept { return this->m_tick_diff_execute; }
			void				execute_interval(chrono::tick::duration _tick_interval)	{ this->m_tick_diff_execute=_tick_interval; this->m_tick_next = chrono::tick::now()+m_tick_diff_execute;}

// framework)
protected:
			chrono::tick::duration	m_tick_diff_execute = 1s;
};


}