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

 @class		schedulable::Iexecutable
 

*///-----------------------------------------------------------------------------
class schedulable::Iexecutable :
	public						Nschedulable,
	virtual public				CGDK::Iexecutable
{
protected:
	virtual ~Iexecutable() noexcept {}

protected:
	virtual	bool				process_on_register() override;
	virtual	void				process_on_unregister() override;

	virtual	bool				process_schedule() override;
};


}
