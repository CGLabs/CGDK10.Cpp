//*****************************************************************************
//*                                                                           *
//*                            CGCII update server                            *
//*                                 ver.10.0                                  *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
//*                          http://www.CGCIII.co.kr                          *
//*                                                                           *
//*****************************************************************************
#pragma once

// 1) SDKDDKVer
#if defined(_WIN32)
	#include <SDKDDKVer.h>
#endif

// 2) includes
#include <stdio.h>
#if defined(_WIN32)
	#include <conio.h>
#endif
#include <iostream>

// 3) CGDK
#include "cgdk/sdk10/net.update.h"
#include "cgdk/sdk10/server.group.list.h"
#include "cgdk/sdk10/server.service.h"

// definitions) 
using namespace CGDK;

// definition) 
#define	LOG_FILE		"log/update_server_{}{}[}-{}{}[}.log"sv
#define	CONFIGURE_FILE	"configure/update_server_setting.json"sv

// 4) ...
#include "../define_message.h"
#include "socket_tcp.h"
#include "group_socket.h"
#include "group_socket_immigration.h"
#include "service.h"

// 5) service object
extern own_ptr<service> g_pservice;
