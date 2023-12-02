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
//-----------------------------------------------------------------------------
//
//  protocols
//
//-----------------------------------------------------------------------------
namespace CGDK
{
namespace eMESSAGE
{
	const uint32_t	REQUEST_CERTIFICATION = eMESSAGE::NETWORK::USER::BASE + 100;
	const uint32_t	ACCEPT_CERTIFICATION = eMESSAGE::NETWORK::USER::BASE + 101;
	const uint32_t	SEND_LOBBYSERVER_STATUS = eMESSAGE::NETWORK::USER::BASE + 102;

	const uint32_t	REQUEST_USER_CHECKIN = eMESSAGE::NETWORK::USER::BASE + 103;
	const uint32_t	RESPONSE_USER_CHECKIN = eMESSAGE::NETWORK::USER::BASE + 104;
	const uint32_t	SEND_CHATTING_MESSAGE = eMESSAGE::NETWORK::USER::BASE + 105;

	const uint32_t	REQUEST_ENTER_CHANNEL = eMESSAGE::NETWORK::USER::BASE + 106;
	const uint32_t	RESPONSE_ENTER_CHANNEL = eMESSAGE::NETWORK::USER::BASE + 107;	// Fail to Enter
	const uint32_t	NOTIFY_ENTER_CHANNEL = eMESSAGE::NETWORK::USER::BASE + 108;	// Success on Enter Channel
	const uint32_t	NOTIFY_LEAVE_CHANNEL = eMESSAGE::NETWORK::USER::BASE + 109;	// 
}
}

inline shared_buffer message_REQUEST_ENTER_CHANNEL(CHANNEL_ID _cid, eCHANNEL_OPTION _option = eCHANNEL_OPTION::ENTER_ALWAYS)
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(64);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::REQUEST_ENTER_CHANNEL);
	buf_temp.append<CHANNEL_ID>(_cid);
	buf_temp.append<eCHANNEL_OPTION>(_option);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

inline shared_buffer message_REQUEST_USER_CHECKIN(ACCOUNT_ID _aid, std::string_view _nickname)
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(1024);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::REQUEST_USER_CHECKIN);
	buf_temp.append<ACCOUNT_ID>(_aid);
	buf_temp.append<std::string_view>(_nickname);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

inline shared_buffer message_RESPONSE_USER_CHECKIN(eRESULT _result)
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(64);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::RESPONSE_USER_CHECKIN);
	buf_temp.append<eRESULT>(_result);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

inline shared_buffer message_NOTIFY_ENTER_CHANNEL(CHANNEL_ID _id_channel, eRESULT _result = eRESULT::SUCCESS, std::string_view _strName="")
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(256);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::NOTIFY_ENTER_CHANNEL);
	buf_temp.append<CHANNEL_ID>(_id_channel);
	buf_temp.append<eRESULT>(_result);
	buf_temp.append<std::string_view>(_strName);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

inline shared_buffer message_NOTIFY_LEAVE_CHANNEL(CHANNEL_ID _id_channel)
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(256);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::NOTIFY_LEAVE_CHANNEL);
	buf_temp.append<CHANNEL_ID>(_id_channel);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}

inline shared_buffer message_SEND_CHATTING_MESSAGE(std::string_view _chatting, std::string_view _nickname)
{
	// 1) alloc memory buffer
	auto buf_temp = alloc_shared_buffer(1024);

	// 2) write message context
	buf_temp.append<uint32_t>();
	buf_temp.append<uint32_t>(eMESSAGE::SEND_CHATTING_MESSAGE);
	buf_temp.append<std::string_view>(_chatting);
	buf_temp.append<std::string_view>(_nickname);

	// 3) set message length
	buf_temp.front<uint32_t>() = buf_temp.size<uint32_t>();

	// return) 
	return buf_temp;
}
