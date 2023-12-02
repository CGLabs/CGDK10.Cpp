//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           server.http_api.line                            *
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

namespace CGDK::http_api::line
{
	
//-----------------------------------------------------------------------------
//
// LINE OAuth
//
// ----------------------------------------------------------------------------
// 1) Access Token (Issue channel access token)
struct REQUEST_LINE_ACCESS_TOKEN : public query::REQUEST
{
public:
	static_string<64>			client_id;		// Channel ID. Found on the console.
	static_string<64>			client_secret;	// Channel secret. Found on the console.

public:
	REQUEST_LINE_ACCESS_TOKEN() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_ACCESS_TOKEN : public query::RESPONSE
{
public:
	static_string<256>			access_token;	// Short-lived channel access token. Valid for 30 days. Note: Channel access tokens cannet be refreshed.
	uint64_t					expire_in;		// Time until channel access token expires in seconds from time the token is issued.
	static_string<64>			token_type;
};


// 2) Revoke (Revoke channel access token)
struct REQUEST_LINE_REVOKE : public query::REQUEST
{
public:
	static_string<256>			access_token;	// Channel access token

public:
	REQUEST_LINE_REVOKE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_REVOKE : public query::RESPONSE
{
	// Empty
};


//-----------------------------------------------------------------------------
//
// LINE Message
//
// ----------------------------------------------------------------------------
// 1) send reply message
struct REQUEST_LINE_MESSAGE_REPLY : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<256>			replyToken;				// Reply token received via webhook
	std::vector<std::string>	messages;				// Messages Max: 5

public:
	REQUEST_LINE_MESSAGE_REPLY() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_MESSAGE_REPLY : public query::RESPONSE
{
	// Empty
};


// 2) send push message
struct REQUEST_LINE_MESSAGE_PUSH : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<256>			to;						// ID of the target recipient. Use a userId, groupId or roomId value returned in a webhook event object. Do not use the LINE ID found on the LINE app.
	shared_buffer				messages;

public:
	REQUEST_LINE_MESSAGE_PUSH() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_MESSAGE_PUSH : public query::RESPONSE
{
	// Empty
};


// 3) send multicast messages
struct REQUEST_LINE_MESSAGE_MULTICAST : public query::REQUEST
{
public:
	static_string<256>			channel_access_token;
	std::vector<std::string>	to;
	std::vector<std::string>	messages;

public:
	REQUEST_LINE_MESSAGE_MULTICAST() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_MESSAGE_MULTICAST : public query::RESPONSE
{
	// Empty
};


// 4) ME
struct REQUEST_LINE_GET_CONTENTS : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			messageid;		// Message ID

public:
	REQUEST_LINE_GET_CONTENTS() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_GET_CONTENTS : public query::RESPONSE
{
	// Empty
};


//-----------------------------------------------------------------------------
//
// LINE Profile
//
// ----------------------------------------------------------------------------
// 1) Get profile
struct REQUEST_LINE_PROFILE : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			userId;				// User ID that is returned in a webhook event object. Do not use the LINE ID found on the LINE app.

public:
	REQUEST_LINE_PROFILE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_PROFILE : public query::RESPONSE
{
public:
	static_string<64>			displayName;		// Display name
	static_string<64>			userId;				// User ID
	static_string<64>			pictureUrl;			// Image URL
	static_string<64>			statusMessage;		// Status message
};


//-----------------------------------------------------------------------------
//
// Group
//
// ----------------------------------------------------------------------------
// 1) Get group member profile
struct REQUEST_LINE_GROUP_MEMBER : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			groupId;			// Found in the source object of webhook event objects
	static_string<64>			userId;				// User ID that is returned in a webhook event object. Do not use the LINE ID found on the LINE app.

public:
	REQUEST_LINE_GROUP_MEMBER() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_GROUP_MEMBER : public query::RESPONSE
{
public:
	static_string<64>			displayName;		// Display name
	static_string<64>			userId;				// User ID
	static_string<64>			pictureUrl;			// Image URL
};

// 2) Get group member user IDs
struct REQUEST_LINE_GROUP_MEMBER_IDS : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			groupId;			// Found in the source object of webhook event objects
	static_string<64>			start;				// (Optinal) Value of the continuation token found in the next property of the JSON object returned in the response. Include this parameter to get the next array of user IDs for the members of the group.

public:
	REQUEST_LINE_GROUP_MEMBER_IDS() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_GROUP_MEMBER_IDS : public query::RESPONSE
{
public:
	std::vector<std::string>	memberse;			// List of user IDs of the members in the group. The number of user IDs returned in memberIds is not fixed. Users who have not agreed to the Official Accounts Terms of Use ar net included in memberIds. Max:100 user IDs
	static_string<64>		next;				// A continuation token to get the next array of use IDs of the members in the group. Returned only when there are remaining user IDs that were not returned in memberIds in the original request.
};


// 3) Leave group
struct REQUEST_LINE_GROUP_LEAVE : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			groupId;			// Found in the source object of webhook event objects

public:
	REQUEST_LINE_GROUP_LEAVE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_GROUP_LEAVE : public query::RESPONSE
{
	// Empty
};


//-----------------------------------------------------------------------------
//
// Room
//
// ----------------------------------------------------------------------------
// 1) Get room member profile
struct REQUEST_LINE_ROOM_MEMBER : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			roomId;				// Found in the source object of webhook event objects
	static_string<64>			userId;				// User ID that is returned in a webhook event object. Do not use the LINE ID found on the LINE app.

public:
	REQUEST_LINE_ROOM_MEMBER() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_ROOM_MEMBER : public query::RESPONSE
{
public:
	static_string<64>			displayName;		// Display name
	static_string<64>			userId;				// User ID
	static_string<64>			pictureUrl;			// Image URL
};


// 2) Get room member user IDs
struct REQUEST_LINE_ROOM_MEMBER_IDS : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			roomId;				// Found in the source object of webhook event objects
	static_string<64>			start;				// (Optinal) Value of the continuation token found in the next property of the JSON object returned in the response. Include this parameter to get the next array of user IDs for the members of the group.

public:
	REQUEST_LINE_ROOM_MEMBER_IDS() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_ROOM_MEMBER_IDS : public query::RESPONSE
{
public:
	std::vector<std::string>	memberse;			// List of user IDs of the members in the group. The number of user IDs returned in memberIds is not fixed. Users who have not agreed to the Official Accounts Terms of Use ar net included in memberIds. Max:100 user IDs
	static_string<64>			next;				// A continuation token to get the next array of use IDs of the members in the group. Returned only when there are remaining user IDs that were not returned in memberIds in the original request.
};


// 3) Leave room
struct REQUEST_LINE_ROOM_LEAVE : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			roomId;				// Found in the source object of webhook event objects

public:
	REQUEST_LINE_ROOM_LEAVE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_ROOM_LEAVE : public query::RESPONSE
{
	// Empty
};


//-----------------------------------------------------------------------------
//
// Rich menu
//
// ----------------------------------------------------------------------------
// 1) Get rich menu
struct REQUEST_LINE_RICHMENU_GET : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			richMenuId;			// 	ID of an uploaded rich menu

public:
	REQUEST_LINE_RICHMENU_GET() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_GET : public query::RESPONSE
{
	// JSON Object
};


// 2) create rich menu
struct REQUEST_LINE_RICHMENU_CREATE : public query::REQUEST
{
public:
	static_string<256>			access_token;
	shared_buffer				contents;

public:
	REQUEST_LINE_RICHMENU_CREATE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_CREATE : public query::RESPONSE
{
	// JSON Object
};


// 3) Delete rich menu
struct REQUEST_LINE_RICHMENU_DELETE : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			richMenuId;			// 	ID of an uploaded rich menu

public:
	REQUEST_LINE_RICHMENU_DELETE() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_DELETE : public query::RESPONSE
{
	// JSON Object
};


// 4) Get rich numu ID of user
struct REQUEST_LINE_RICHMENU_USER : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			userId;				// User ID

public:
	REQUEST_LINE_RICHMENU_USER() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_USER : public query::RESPONSE
{
	// JSON Object
};


// 5) Link rich numu ID of user
struct REQUEST_LINE_RICHMENU_USER_LINK : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			richMenuId;			// 	ID of an uploaded rich menu
	static_string<64>			userId;				// User ID

public:
	REQUEST_LINE_RICHMENU_USER_LINK() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_USER_LINK : public query::RESPONSE
{
	// JSON Object
};


// 6) Unlink rich numu ID of user
struct REQUEST_LINE_RICHMENU_USER_UNLINK : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			userId;				// User ID

public:
	REQUEST_LINE_RICHMENU_USER_UNLINK() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_USER_UNLINK : public query::RESPONSE
{
	// JSON Object
};


// 7) Download rich menu image
struct REQUEST_LINE_RICHMENU_CONTENT_DOWNLOAD : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			richMenuId;			// 	ID of an uploaded rich menu

public:
	REQUEST_LINE_RICHMENU_CONTENT_DOWNLOAD() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_CONTENT_DOWNLOAD : public query::RESPONSE
{
	// JSON Object
};


// 8) Upload rich menu image
struct REQUEST_LINE_RICHMENU_CONTENT_UPLOAD : public query::REQUEST
{
public:
	static_string<256>			access_token;
	static_string<64>			richMenuId;			// 	ID of an uploaded rich menu

public:
	REQUEST_LINE_RICHMENU_CONTENT_UPLOAD() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_CONTENT_UPLOAD : public query::RESPONSE
{
	// JSON Object
};


// 9) Get rich menu list
struct REQUEST_LINE_RICHMENU_LIST : public query::REQUEST
{
public:
	static_string<256>			access_token;
	std::vector<std::string>	richmenus;			// Array of rich menu response objects

public:
	REQUEST_LINE_RICHMENU_LIST() noexcept : REQUEST{ "api.line.me" } {}
};

struct RESPONSE_LINE_RICHMENU_LIST : public query::RESPONSE
{
	// JSON Object
};


}