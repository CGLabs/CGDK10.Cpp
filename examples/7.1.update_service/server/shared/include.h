//*****************************************************************************
//*                                                                           *
//*                            CGCII update system                            *
//*                       simple update server ver.10.0                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
//*                          http://www.CGCIII.co.kr                          *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------
// 1. CGCII header files
//-----------------------------------------------------------------
// 1) CGCII components
#include "cgdk/sdk10/net.update.h"
#include "cgdk/sdk10/server.system.group.list.h"
#include "cgdk/sdk10/server.system.service.h"

// 2) CGDK namespace 
using namespace CGDK;


//-----------------------------------------------------------------
// 2. setting
//----------------------------------------------------------------- 
// definition) 
#define	LOG_FILE		"log/CGDK10.update_server_{}{}[}-{}{}[}.log"sv
#define	CONFIGURE_FILE	"configure/CGDK10.update_server_setting.json"sv

//-----------------------------------------------------------------
// 3. definitions
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// 4. header files - project
//-----------------------------------------------------------------
// 1) commons
#include "CGDK10.update_service.server.definition.h"
#include "../../define_message.h"

// 2) sockets
#include "socket_peer.h"
#include "group_peer.h"
#include "group_peer_immigration.h"

// 3) service
#include "service.h"


//-----------------------------------------------------------------
// 5. Global Variable
//-----------------------------------------------------------------
// 1) ...
extern own_ptr<service> g_pservice;

// debug) 
#ifdef _DEBUG
	#define new DEBUG_NEW
#endif
