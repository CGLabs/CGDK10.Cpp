// ----------------------------------------------------------------------------
//
// message definitions
//
// ----------------------------------------------------------------------------
#pragma once

enum class eMESSAGE_TYPE : uint32_t
{
	REQUEST_LOGIN	 = 0x00000001,
	RESPONSE_LOGIN	 = 0x00000002,
	REQUEST_ENTER	 = 0x00000003,
	ENTER_MEMBER	 = 0x00000004,
	LEAVE_MEMBER	 = 0x00000005,
	SEND_CHAT		 = 0x00000006,
};

struct sMESSAGE_HEAD : 
	public CGDK::message_headable_primitive<uint32_t, 0>	// message size = uint32_t, offset of message_size = 0
{
	uint32_t			message_size;
	eMESSAGE_TYPE		message_type;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_REQUEST_LOGIN : public sMESSAGE_HEAD
{
	std::string_view	nickname;
};

struct sMESSAGE_RESPONSE_LOGIN : public	sMESSAGE_HEAD
{
	CGDK::result_code	result;
	std::string_view	result_message;

	uint64_t			user_id;
};

struct sMESSAGE_REQUEST_ENTER : public	sMESSAGE_HEAD
{
	uint64_t			channel_id;
};

struct sMESSAGE_ENTER : public	sMESSAGE_HEAD
{
	uint64_t			channel_id;
};

struct sMESSAGE_LEAVE : public	sMESSAGE_HEAD
{
	uint64_t			channel_id;
	uint64_t			user_id;
};

struct sMESSAGE_SEND_CHAT : public	sMESSAGE_HEAD
{
	std::string_view	nickname;
	std::string_view	message;
};
