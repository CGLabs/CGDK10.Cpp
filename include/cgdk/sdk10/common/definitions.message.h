//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
	using message_t = uint32_t;

//----------------------------------------------------------------------------
//  CODE
//
// 
//
//
//
//----------------------------------------------------------------------------
namespace CODE_TYPE
{
	//-----------------------------------------------------------------------------
	// code components
	//-----------------------------------------------------------------------------
	constexpr static message_t		HEAD_0		 = 0x00000000;		// Reserved for System
	constexpr static message_t		HEAD_1		 = 0x00100000;		// Reserved for Application
	constexpr static message_t		HEAD_2		 = 0x00200000;		// Reserved for Script
	constexpr static message_t		HEAD_3		 = 0x00300000;		// Free

	constexpr static message_t		SUB_0		 = 0x00000000;
	constexpr static message_t		SUB_1		 = 0x00010000;
	constexpr static message_t		SUB_2		 = 0x00020000;
	constexpr static message_t		SUB_3		 = 0x00030000;
	constexpr static message_t		SUB_4		 = 0x00040000;
	constexpr static message_t		SUB_5		 = 0x00050000;
	constexpr static message_t		SUB_6		 = 0x00060000;
	constexpr static message_t		SUB_7		 = 0x00070000;
	constexpr static message_t		SUB_8		 = 0x00080000;
	constexpr static message_t		SUB_9		 = 0x00090000;
	constexpr static message_t		SUB_10		 = 0x000a0000;
	constexpr static message_t		SUB_A		 = SUB_10;
	constexpr static message_t		SUB_11		 = 0x000b0000;
	constexpr static message_t		SUB_B		 = SUB_11;
	constexpr static message_t		SUB_12		 = 0x000c0000;
	constexpr static message_t		SUB_C		 = SUB_12;
	constexpr static message_t		SUB_13		 = 0x000d0000;
	constexpr static message_t		SUB_D		 = SUB_13;
	constexpr static message_t		SUB_14		 = 0x000e0000;
	constexpr static message_t		SUB_E		 = SUB_14;
	constexpr static message_t		SUB_15		 = 0x000f0000;
	constexpr static message_t		SUB_F		 = SUB_15;

	constexpr static message_t		TAIL_0		 = 0x00000000;
	constexpr static message_t		TAIL_1		 = 0x00001000;
	constexpr static message_t		TAIL_2		 = 0x00002000;
	constexpr static message_t		TAIL_3		 = 0x00003000;
	constexpr static message_t		TAIL_4		 = 0x00004000;
	constexpr static message_t		TAIL_5		 = 0x00005000;
	constexpr static message_t		TAIL_6		 = 0x00006000;
	constexpr static message_t		TAIL_7		 = 0x00007000;
	constexpr static message_t		TAIL_8		 = 0x00008000;
	constexpr static message_t		TAIL_9		 = 0x00009000;
	constexpr static message_t		TAIL_10		 = 0x0000a000;
	constexpr static message_t		TAIL_A		 = TAIL_10;
	constexpr static message_t		TAIL_11		 = 0x0000b000;
	constexpr static message_t		TAIL_B		 = TAIL_11;
	constexpr static message_t		TAIL_12		 = 0x0000c000;
	constexpr static message_t		TAIL_C		 = TAIL_12;
	constexpr static message_t		TAIL_13		 = 0x0000d000;
	constexpr static message_t		TAIL_D		 = TAIL_13;
	constexpr static message_t		TAIL_14		 = 0x0000e000;
	constexpr static message_t		TAIL_E		 = TAIL_14;
	constexpr static message_t		TAIL_15		 = 0x0000f000;
	constexpr static message_t		TAIL_F		 = TAIL_15;

	constexpr static message_t		TAIL_SUB_0	 = 0x00000000;
	constexpr static message_t		TAIL_SUB_1	 = 0x00000100;
	constexpr static message_t		TAIL_SUB_2	 = 0x00000200;
	constexpr static message_t		TAIL_SUB_3	 = 0x00000300;
	constexpr static message_t		TAIL_SUB_4	 = 0x00000400;
	constexpr static message_t		TAIL_SUB_5	 = 0x00000500;
	constexpr static message_t		TAIL_SUB_6	 = 0x00000600;
	constexpr static message_t		TAIL_SUB_7	 = 0x00000700;
	constexpr static message_t		TAIL_SUB_8	 = 0x00000800;
	constexpr static message_t		TAIL_SUB_9	 = 0x00000900;
	constexpr static message_t		TAIL_SUB_10	 = 0x00000a00;
	constexpr static message_t		TAIL_SUB_A	 = 0x00000a00;
	constexpr static message_t		TAIL_SUB_11	 = 0x00000b00;
	constexpr static message_t		TAIL_SUB_B	 = TAIL_SUB_11;
	constexpr static message_t		TAIL_SUB_12	 = 0x00000c00;
	constexpr static message_t		TAIL_SUB_C	 = TAIL_SUB_12;
	constexpr static message_t		TAIL_SUB_13	 = 0x00000d00;
	constexpr static message_t		TAIL_SUB_D	 = TAIL_SUB_13;
	constexpr static message_t		TAIL_SUB_14	 = 0x00000e00;
	constexpr static message_t		TAIL_SUB_E	 = TAIL_SUB_14;
	constexpr static message_t		TAIL_SUB_15	 = 0x00000f00;
	constexpr static message_t		TAIL_SUB_F	 = TAIL_SUB_15;


	//-----------------------------------------------------------------------------
	// Reserved List)
	//-----------------------------------------------------------------------------
	constexpr static message_t		WINDOWS		 = (HEAD_0 | SUB_0);
	constexpr static message_t		SYSTEM		 = (HEAD_0 | SUB_1);
	constexpr static message_t		NETWORK		 = (HEAD_0 | SUB_2);
	constexpr static message_t		SERVER		 = (HEAD_0 | SUB_3);
	constexpr static message_t		SCRIPT		 = (HEAD_0 | SUB_4);
	constexpr static message_t		RENDER		 = (HEAD_0 | SUB_5);
	constexpr static message_t		UPDATE		 = (HEAD_0 | SUB_6);
	constexpr static message_t		UI			 = (HEAD_0 | SUB_7);
	constexpr static message_t		INIT		 = (HEAD_0 | SUB_8);
	constexpr static message_t		INPUT		 = (HEAD_0 | SUB_9);   // Input용 메세지   [11/10/2016 BSH]
	constexpr static message_t		USER		 = (HEAD_1 | SUB_A);
}


namespace eMESSAGE
{
	//-----------------------------------------------------------------------------
	//
	// 1. windows message
	//
	//-----------------------------------------------------------------------------
	namespace WINDOWS
	{
		// 1) user messages
		constexpr static message_t	USER_RESERVED			 = (CODE_TYPE::WINDOWS | CODE_TYPE::TAIL_0 | CODE_TYPE::TAIL_SUB_4); // windows user message

		// message definitions)
		constexpr static message_t	NOTIFY					 = (USER_RESERVED+0);
		constexpr static message_t	NOTIFY_UPDATE			 = (USER_RESERVED+1);

		// 2) user messages
		constexpr static message_t	USER					 = (CODE_TYPE::WINDOWS | CODE_TYPE::TAIL_0 | CODE_TYPE::TAIL_SUB_5); // windows user message
	}


	//-----------------------------------------------------------------------------
	//
	// 2. common
	//
	//-----------------------------------------------------------------------------
	namespace SYSTEM
	{
		// 1) message
		constexpr static message_t	FLAG_RELIABLE			 = 0x80000000;
		constexpr static message_t	MASK					 = 0x0fffffff;

		// 2) message for system(5~B(11))
		constexpr static message_t	OBJECT					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_0); // (reserved for object classes)
		constexpr static message_t	FACTORY					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_1); // (reserved for factory classes)
		constexpr static message_t	EXECUTE					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_2); // (reserved for execute classes)
		constexpr static message_t	LOG_					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_3); // (reserved for log)
		constexpr static message_t	BUFFER					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_4); // (reserved for buffers)

		// 3) message for object state
		constexpr static message_t	REQUEST_INITIALIZE		 = OBJECT | 1;
		constexpr static message_t	REQUEST_DESTROY			 = OBJECT | 2;
		constexpr static message_t	REQUEST_START			 = OBJECT | 3;
		constexpr static message_t	REQUEST_STOP			 = OBJECT | 4;

		// 4) state
		constexpr static message_t	UPDATE_STATE			 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_4 | 1);// state change

		// 5) contexts
		constexpr static message_t	CONTEXT					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_5);

		// 6) message for network message
		constexpr static message_t	NETWORK					 = BUFFER | 0x02000000;	// 0x02015000
		constexpr static message_t	NETWORK_MASK			 = 0x0ffff000;
		constexpr static message_t	NETWORK_USER_MIN		 = NETWORK + 1;
		constexpr static message_t	NETWORK_USER_MAX		 = NETWORK | 0x00000fff;
		constexpr static message_t	NETWORK_USER			 = NETWORK_USER_MIN;
		constexpr static message_t	NETWORK_RESP			 = NETWORK | 96;
	}


	//-----------------------------------------------------------------------------
	//
	// 3. base
	//
	//-----------------------------------------------------------------------------
	namespace NETWORK
	{
		constexpr static message_t	COMMON = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_0);

		namespace SOCKET	{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_1);}
		namespace P2P		{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_2);}
		namespace UPDATE	{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_3);}
		namespace SECURITY	{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_4);}
		namespace ROOM		{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_6);}
		namespace USER		{ constexpr static message_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_7);}

		constexpr static message_t	CLIENT_INFO_REQUEST		 = COMMON + 0;
		constexpr static message_t	CLIENT_INFO_SEND		 = COMMON + 1;
		constexpr static message_t	SERVER_INFO_REQUEST		 = COMMON + 2;
		constexpr static message_t	SERVER_INFO_SEND		 = COMMON + 3;

		constexpr static message_t	ACK						 = COMMON + 8;
		constexpr static message_t	REQUEST_ACK				 = COMMON + 9;
		constexpr static message_t	PING_REQ				 = COMMON + 10;
		constexpr static message_t	PING_ACK				 = COMMON + 11;
		constexpr static message_t	LOGIN_REQUEST			 = COMMON + 12;
		constexpr static message_t	LOGIN_RESPONSE			 = COMMON + 14;
		constexpr static message_t	CERTIFY_REQUEST			 = COMMON + 15;
		constexpr static message_t	CERTIFY_RESPONSE		 = COMMON + 16;

		namespace ROOM
		{
			constexpr message_t	COMMON = (ROOM::BASE | CODE_TYPE::TAIL_SUB_0);

			namespace CHANNEL { constexpr static message_t	BASE = (ROOM::BASE | CODE_TYPE::TAIL_SUB_1); }
		}
	}

	namespace SERVER
	{
		constexpr static message_t	COMMON = (CODE_TYPE::SERVER | CODE_TYPE::TAIL_0);

		namespace TIME_EVENT { constexpr static message_t	BASE = (CODE_TYPE::SERVER | CODE_TYPE::TAIL_1);}
		namespace QUERY		 { constexpr static message_t	BASE = (CODE_TYPE::SERVER | CODE_TYPE::TAIL_2);}
		namespace DOSS		 { constexpr static message_t	BASE = (CODE_TYPE::SERVER | CODE_TYPE::TAIL_3);}
		namespace ADMIN		 { constexpr static message_t	BASE = (CODE_TYPE::SERVER | CODE_TYPE::TAIL_4);}
	}


	//-----------------------------------------------------------------------------
	//
	// 4. attributes
	//
	//-----------------------------------------------------------------------------
	namespace ATTRIBUTE
	{
		// 1) Base
		constexpr static message_t	BASE					 = (CODE_TYPE::SCRIPT | CODE_TYPE::TAIL_0);

		// 2) Attributes
		constexpr static message_t	NAME					 = (BASE | CODE_TYPE::TAIL_SUB_0 |   1);
		constexpr static message_t	GET_ALL_ATTRIBUTE_INFO	 = (BASE | CODE_TYPE::TAIL_SUB_0 |   2);
		constexpr static message_t	GET_ALL_ATTRIBUTES		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   3);
		constexpr static message_t	GET_ATTRIBUTE_COUNT		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   4);
		constexpr static message_t	GET_ALL_METHOD_INFO		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   5);
		constexpr static message_t	GET_ALL_METHODES		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   6);
		constexpr static message_t	GET_METHOD_COUNT		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   7);
		constexpr static message_t	GET_TYPE_NAME			 = (BASE | CODE_TYPE::TAIL_SUB_0 |   8);
		constexpr static message_t	GET_TYPE_ID				 = (BASE | CODE_TYPE::TAIL_SUB_0 |   9);
		constexpr static message_t	GET_ENTITY_NAME			 = (BASE | CODE_TYPE::TAIL_SUB_0 |  10);
		constexpr static message_t	GET_ENTITY_ID			 = (BASE | CODE_TYPE::TAIL_SUB_0 |  11);
	}


	//-----------------------------------------------------------------------------
	//
	// 5. automation
	//
	//-----------------------------------------------------------------------------
	namespace AUTOMATION
	{
		// 1) ...
		constexpr static message_t	BASE					 = (CODE_TYPE::SCRIPT | CODE_TYPE::TAIL_1);

		// 2) 
		constexpr static message_t	MEMBER_FUNCTION			 = (BASE | CODE_TYPE::TAIL_SUB_0 | 1);
		constexpr static message_t	MEMBER_SET				 = (BASE | CODE_TYPE::TAIL_SUB_0 | 2);
		constexpr static message_t	MEMBER_RESET			 = (BASE | CODE_TYPE::TAIL_SUB_0 | 3);
		constexpr static message_t	MEMBER_GET				 = (BASE | CODE_TYPE::TAIL_SUB_0 | 4);
	}												   

	//-----------------------------------------------------------------------------
	//
	// 6. ...
	//
	//-----------------------------------------------------------------------------
	// 1) message for render(8~12)
	namespace RENDER
	{
		constexpr static message_t	BASE					 = (CODE_TYPE::RENDER | CODE_TYPE::TAIL_0);
		constexpr static message_t	RENDER					 = (CODE_TYPE::RENDER | CODE_TYPE::TAIL_0) | 1;
		constexpr static message_t	PROCESS_RENDER			 = (CODE_TYPE::RENDER | CODE_TYPE::TAIL_0) | 2;
	}
											
	// 2) message for update(8~12)
	namespace UPDATE
	{
		constexpr static message_t	BASE				 	 = (CODE_TYPE::RENDER | CODE_TYPE::TAIL_9);
		constexpr static message_t	FRAME				 	 = (CODE_TYPE::RENDER | CODE_TYPE::TAIL_9) | 0;
	}

	//-----------------------------------------------------------------------------
	//
	// 7. user interface
	//
	//-----------------------------------------------------------------------------
	// 1) message for game application(8~12)
	namespace UI
	{
		constexpr static message_t	NOTIFY					 = (CODE_TYPE::UI | CODE_TYPE::TAIL_0);
	}

	// 2) input message [11/10/2016 BSH]
	namespace INPUT
	{
		constexpr static message_t	BASE					= CODE_TYPE::INPUT;
		constexpr static message_t MOTION					= (CODE_TYPE::INPUT | CODE_TYPE::TAIL_0);
		constexpr static message_t	KEYBOARD				= (CODE_TYPE::INPUT | CODE_TYPE::TAIL_1);
	}

	//-----------------------------------------------------------------------------
	//
	// 9. users
	//
	//-----------------------------------------------------------------------------
	constexpr static message_t	USER						 = (CODE_TYPE::USER | CODE_TYPE::TAIL_0);

} // end of namespace eMESSAGE

// Convertability) 
constexpr static uint32_t	CGNETMESSAGE					 = eMESSAGE::SYSTEM::NETWORK;

//-----------------------------------------------------------------------------
// definitions)
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4239)
#endif
																 
constexpr static int	RETURN_VALUE_FAIL			 = 0;
constexpr static int	RETURN_VALUE_SUCCESS		 = 0;
constexpr static int	RETURN_VALUE_STOP			 = 1;
constexpr static int	RETURN_VALUE_CONTINUE		 = -1;

}