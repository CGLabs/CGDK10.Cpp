// ----------------------------------------------------------------------------
//
// message definitions
//
// ----------------------------------------------------------------------------
#pragma once

enum eMESSAGE_TYPE : uint32_t
{
	CONNECT_SUCCESS		 = 0x00000001,
	CONNECT_CLOSE		 = 0x00000002,
	SEND_CHAT			 = 0x00000003,
	REQUEST_LOGIN		 = 0x00000004,
	RESPONSE_LOGIN		 = 0x00000005,
	REQUEST_DISCONNECT	 = 0x00000006,
	ENTER				 = 0x00000007,
	LEAVE				 = 0x00000008,
	ENTER_MEMBER		 = 0x00000009,
	LEAVE_MEMBER		 = 0x0000000a,
	REQUEST_CREATEROOM	 = 0x0000000b,
	REQUEST_ENTERROOM	 = 0x0000000c,
	REQUEST_LEAVEROOM	 = 0x0000000d,
	ADD_ROOM			 = 0x0000000e,
	REMOVE_ROOM			 = 0x0000000f,
	ROOM_LIST			 = 0x00000010,
	MEMBER_LIST			 = 0x00000011,
	SET_STATE			 = 0x00000012,
	PRE_STATE			 = 0x00000013,
	NEXT_STATE			 = 0x00000014,
	REQUEST_LEAVE_ALL	 = 0x00000015,

	SEND_A				 = 0x00000020,
	SEND_B				 = 0x00000021,
	SEND_C				 = 0x00000022,
	SEND_D				 = 0x00000023,
	SEND_E				 = 0x00000024,
	SEND_F				 = 0x00000025,
	SEND_G				 = 0x00000026,
	SEND_H				 = 0x00000027,
	SEND_I				 = 0x00000028,
};

struct sMESSAGE_HEAD
{
	uint32_t			message_size;
	eMESSAGE_TYPE		message_type;
};

struct sMESSAGE_A : 
	public	sMESSAGE_HEAD
{
public:
	int					x;
	char				y;
	float				z;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_B : 
	public	sMESSAGE_HEAD
{
public:
	int							a;
	std::string					b;
	std::vector<int>			c;
	std::map<int, std::string>	d;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_REQUEST_LOGIN : 
	public	sMESSAGE_HEAD
{
public:
	std::string_view			nickname;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_RESPONSE_LOGIN :
	public	sMESSAGE_HEAD
{
public:
	CGDK::result_code			result;
	std::string_view			result_message;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_REQUEST_ENTER :
	public	sMESSAGE_HEAD
{
public:
	uint64_t					channel_id;

	ENABLE_STRUCT_SERIALIZABLE
};

struct sMESSAGE_SEND_CHAT :
	public	sMESSAGE_HEAD
{
public:
	std::string_view			message;

	ENABLE_STRUCT_SERIALIZABLE
};
