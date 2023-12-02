//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Group Template Classes                           *
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
// ----------------------------------------------------------------------------
// definitions
// ----------------------------------------------------------------------------
namespace CGDK
{
	namespace container
	{
		template <class>					struct OBJECT_SET;
		template <class, class>				struct OBJECT_SET_DATA;

		template <class, class, class>		class list;
		template <class, class, class>		class list_sender;

		template <class, class, class>		class set;
		template <class, class, class>		class set_sender;

		template <class, class, class, class>	class map;
		template <class, class, class, class>	class map_sender;
	}
}

// ----------------------------------------------------------------------------
// group_system.container
// ----------------------------------------------------------------------------
// 1) container data
#include "cgdk/sdk10/server.system/group/server.container_data.h"

// 2) container
#include "cgdk/sdk10/server.system/group/server.Icontainer.h"
#include "cgdk/sdk10/server.system/group/server.container.list.h"
#include "cgdk/sdk10/server.system/group/server.container.list_sender.h"
#include "cgdk/sdk10/server.system/group/server.container.set.h"
#include "cgdk/sdk10/server.system/group/server.container.set_sender.h"
#include "cgdk/sdk10/server.system/group/server.container.map.h"
#include "cgdk/sdk10/server.system/group/server.container.map_sender.h"
