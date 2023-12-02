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
//-----------------------------------------------------------------
// message definitions
//-----------------------------------------------------------------
namespace eMESSAGE
{
	namespace SERVER
	{
		constexpr static message_t	CERTIFY_REQUEST						= COMMON + 10;
		constexpr static message_t	CERTIFY_RESPONSE					= COMMON + 11;

		namespace ADMIN
		{
			constexpr static message_t	CERTIFY_REQUEST					 = BASE +  1;	//	213050	0x00034039
			constexpr static message_t	CERTIFY_RESPONSE				 = BASE +  2;	//  213051	0x0003403A
			constexpr static message_t	CERTIFIED						 = BASE	+  3;	//	213124	0x00034084

			constexpr static message_t	INSTANCE_CERTIFY_REQUEST		 = BASE	+  5;	//	213124	0x00034084
			constexpr static message_t	INSTANCE_CERTIFY_RESPONSE		 = BASE	+  6;	//	213124	0x00034084

			constexpr static message_t	INSTANCE_ENTER					 = BASE + 14;	//	213045	0x00034034
			constexpr static message_t	INSTANCE_LEAVE					 = BASE + 15;	//	213047	0x00034036

			constexpr static message_t	INSTANCE_REGISTER				 = BASE + 17;	//	213004	0x0003400C
			constexpr static message_t	INSTANCE_UNREGISTER				 = BASE + 18;	//	213005	0x0003400D
			constexpr static message_t	INSTANCE_UPDATE					 = BASE + 19;	//	213006	0x0003400E
			constexpr static message_t	INSTANCE_UPDATE_SETTING			 = BASE + 20;	//	213049	0x00034038
			constexpr static message_t	INSTANCE_UPDATE_INFO			 = BASE + 21;	//	213049	0x00034038
			constexpr static message_t	INSTANCE_UPDATE_STATUS 			 = BASE + 22;	//	213049	0x00034038
			constexpr static message_t	INSTANCE_UPDATE_STATE 			 = BASE + 23;	//	213049	0x00034038
			constexpr static message_t	INSTANCE_UPDATE_PID 			 = BASE + 24;	//	213049	0x00034038

			constexpr static message_t	REQUEST_VERSION_UPDATE			 = BASE + 62;	//	213033	0x00034022
			constexpr static message_t	REQUEST_UPDATE_SETTING			 = BASE + 63;	//	213033	0x00034022
			constexpr static message_t	REQUEST_INIT_SERVICE			 = BASE + 64;	//	213054	0x0003403E
			constexpr static message_t	REQUEST_DESTROY_SERVICE			 = BASE + 65;	//	213055	0x0003403F
			constexpr static message_t	REQUEST_KILL_SERVICE			 = BASE + 66;	//	213056	0x00034040
			constexpr static message_t	REQUEST_START_SERVICE			 = BASE + 67;	//	213057	0x00034041
			constexpr static message_t	REQUEST_STOP_SERVICE			 = BASE + 68;	//	213058	0x00034042
			constexpr static message_t	REQUEST_PAUSE_SERVICE			 = BASE + 69;	//	213059	0x00034043
			constexpr static message_t	REQUEST_CONTINUE_SERVICE		 = BASE + 70;	//	213060	0x00034044

			constexpr static message_t	SERVER_STATUS_UPDATE			 = BASE + 71;	//	213063	0x00034047
			constexpr static message_t	SERVER_PID_UPDATE				 = BASE + 151;	//	213143	0x00034092

			constexpr static message_t	DUMP_INFO_LIST					 = BASE + 181;	//	213173	0x000340B5
			constexpr static message_t	DUMP_INFO						 = BASE + 182;	//	213173	0x000340B5

			constexpr static message_t	UPDATE_SERVICE_STATUS			 = BASE + 191;	//	213183	0x000340BF

			constexpr static message_t	REQUEST_LOG						 = BASE	+ 211;	//	213203	0x000340D3
			constexpr static message_t	LOG_ADD							 = BASE	+ 212;	//	213203	0x000340D3

			constexpr static message_t	SUCCESS							 = BASE	+ 221;	//	213213	0x000340DC
			constexpr static message_t	ERROR_							 = BASE	+ 231;	//	213214	0x000340DE
		}
	}
}

shared_buffer message_SERVER_ADMIN_REQUEST_INIT_SERVICE();
shared_buffer message_SERVER_ADMIN_REQUEST_DESTROY_SERVICE();
shared_buffer message_SERVER_ADMIN_REQUEST_START_SERVICE();
shared_buffer message_SERVER_ADMIN_REQUEST_STOP_SERVICE();
shared_buffer message_SERVER_ADMIN_REQUEST_PAUSE_SERVICE();
shared_buffer message_SERVER_ADMIN_REQUEST_CONTINUE_SERVICE();

}