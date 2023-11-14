//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             Server DB Classes                             *
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

// ----------------------------------------------------------------------------
// definitions
// ----------------------------------------------------------------------------
template <class>				class Igroup;
template <class,class>			class Igroupable;
template <class,class>			class Igroup_enterable;
template <class>				class Imember_containerable;

template <class,class,class>	class Iobserver;
template <class>				class Iobservable;

namespace group
{
	template <class>					struct MEMBER_SET;
	template <class,class>				struct MEMBER_SET_ARRAY;
	template <class,class>				struct MEMBER_SET_LIST;
	template <class,class,class, class>	struct MEMBER_SET_MAP;

	template <class,class,class>		class no_manage;
	template <class,class,class>		class no_manage_dispatchable;

	template <class,class,class>		class count;
	template <class,class,class>		class count_dispatchable;

	template <class,class,class,class>	class array;
	template <class,class,class,class>	class array_dispatchable;
	template <class,class,class,class>	class array_seat;
	template <class,class,class,class>	class array_seat_dispatchable;
	template <class,class,class,class>	class array_seat_sender;
	template <class,class,class,class>	class array_seat_sender_dispatchable;
	template <class,class,class,class>	class array_sender;
	template <class,class,class,class>	class array_sender_dispatchable;

	template <class,class,class,class>	class list;
	template <class,class,class,class>	class list_dispatchable;
	template <class,class,class,class>	class list_sender;
	template <class,class,class,class>	class list_sender_dispatchable;

	template <class,class,class,class,class> class Nmap;
	template <class,class,class,class,class> class Nmap_dispatchable;
	template <class,class,class,class,class> class Nmap_sender;
	template <class,class,class,class,class> class Nmap_sender_dispatchable;
	template <class,class,class,class,class> class map;
	template <class,class,template<class...> class> class preset;
}


// ----------------------------------------------------------------------------
// head files                                                              
// ----------------------------------------------------------------------------
// 1) base classes
#include "cgdk/sdk10/net.socket.h"


//----------------------------------------------------------------------------
// definitions for Group
//----------------------------------------------------------------------------
// 1) server (CGOBJECTTYPE_SERVER == 0x210000)
#define CGOBJECTTYPE_SERVER_GROUP		 (0x210000 | 0x0200)

// 2) ...
#define GROUP_LIST	group::list_sender
#define	GROUP_ARRAY	group::array_seat_sender

using group_member_id_t	  = int64_t;

// 3) traits
class group_taits
{
};



}