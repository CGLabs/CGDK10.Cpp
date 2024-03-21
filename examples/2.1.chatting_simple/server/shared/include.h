//*****************************************************************************
//*                                                                           *
//*                     CGCII simple chatting system (1)                      *
//*                                                                           *
//*                             chatting Server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------
// 1. header files - CGCII header files
//-----------------------------------------------------------------
// 1) CGCII 
#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.time_event.h"
#include "cgdk/sdk10/server.log.h"
#include "cgdk/sdk10/server.service.h"
#include "cgdk/sdk10/server.group.h"

using namespace CGDK;


//-----------------------------------------------------------------
// 2. 
//-----------------------------------------------------------------
namespace channel
{
	class manager;

	class Igroup;
	class group_chatting;
	class group_waiting;
}

namespace user
{
	class manager;

	class group_immigration;
	class socket;
}


//-----------------------------------------------------------------
// 3. definitionss
//-----------------------------------------------------------------
const uint32_t	CGNOTIFY_SERVER_UPDATE	 = (eMESSAGE::USER | 1);

const uint32_t	CGNOTIFY_CHANNEL_ADD	 = (eMESSAGE::USER | 2);
const uint32_t	CGNOTIFY_CHANNEL_REMOVE	 = (eMESSAGE::USER | 3);
const uint32_t	CGNOTIFY_CHANNEL_UPDATE	 = (eMESSAGE::USER | 4);


//-----------------------------------------------------------------
// 5. 
//-----------------------------------------------------------------
// 1) definitions
#include "../../common/definitions.h"
#include "../../common/definition_message.h"

// 2) user
#include "user_socket.h"
#include "user_group_immigration.h"
#include "user_manager.h"

// 3) channels
#include "channel_Igroup.h"
#include "channel_group_waiting.h"
#include "channel_group_chatting.h"
#include "channel_manager.h"

// 4) service
#include "service.h"

// 5) service object
extern own_ptr<service> g_pservice;
