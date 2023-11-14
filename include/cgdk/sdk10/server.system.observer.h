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
	template <class> class Iserver_container;

	namespace observable
	{
		template <class> struct OBSERVER_SET;
		template <class, class> struct OBSERVER_SET_DATA;

		template <class, class, class> class list;
		template <class, class, class> class list_sender;

		template <class, class, class> class set;
		template <class, class, class> class set_sender;

		template <class, class, class, class> class map;
		template <class, class, class, class> class map_sender;
	}
	using observer_channel_id = int64_t;
}

// ----------------------------------------------------------------------------
// group_system.observable
// ----------------------------------------------------------------------------
// 1) observerd ata
#include "cgdk/sdk10/server.system/group/server.observer_data.h"

// 2) observerable
#include "cgdk/sdk10/server.system/group/server.Iobservable.h"

// 3) observers
#include "cgdk/sdk10/server.system/group/server.Iobserver.h"
#include "cgdk/sdk10/server.system/group/server.observable.list.h"
#include "cgdk/sdk10/server.system/group/server.observable.list_sender.h"
#include "cgdk/sdk10/server.system/group/server.observable.set.h"
#include "cgdk/sdk10/server.system/group/server.observable.set_sender.h"
#include "cgdk/sdk10/server.system/group/server.observable.map.h"
#include "cgdk/sdk10/server.system/group/server.observable.map_sender.h"
