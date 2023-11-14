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

 @class		schedulable::system::exception_observer


*///-----------------------------------------------------------------------------
class schedulable::system::exception_observer:
	public						Nschedulable,
	public						factory::_traits_system
{
protected:
			exception_observer() noexcept;
	virtual ~exception_observer() noexcept;

private:
	virtual	bool				process_on_register() override;
	virtual	void				process_on_unregister() override;
	virtual	bool				process_schedule() override;

			lockable<object_ptr<dump_manager>>	m_pmanager_dump;
};


}