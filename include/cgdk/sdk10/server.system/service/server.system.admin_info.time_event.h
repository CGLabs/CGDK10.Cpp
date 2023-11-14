//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
namespace server_system
{
// ----------------------------------------------------------------------------
//
// admin_info::time_event
//
// ----------------------------------------------------------------------------
class admin_info::time_event
{
// constructor/destructor)
public:
			time_event();
	virtual ~time_event();

// implementation)
public:
			CGDK::time_event::sENTITY_SETTING	m_event_entity_setting;
			CGDK::time_event::sENTITY_STATUS	m_event_entity_status;
};


}
}