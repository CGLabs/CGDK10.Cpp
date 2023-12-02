//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          server.http_api.naver                            *
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
//-----------------------------------------------------------------------------
//
// http_api::naver
//
//
// ----------------------------------------------------------------------------
namespace CGDK::http_api::naver
{
	// 1) LINE OAuth
	RESPONSE_LINE_ACCESS_TOKEN				request(const REQUEST_LINE_ACCESS_TOKEN&				_request);
	RESPONSE_LINE_REVOKE					request(const REQUEST_LINE_REVOKE&						_request);

	// 2) LINE Message
	RESPONSE_LINE_MESSAGE_REPLY				request(const REQUEST_LINE_MESSAGE_REPLY&				_request);
	RESPONSE_LINE_MESSAGE_PUSH				request(const REQUEST_LINE_MESSAGE_PUSH&				_request);
	RESPONSE_LINE_MESSAGE_MULTICAST			request(const REQUEST_LINE_MESSAGE_MULTICAST&			_request);
	RESPONSE_LINE_GET_CONTENTS				request(const REQUEST_LINE_GET_CONTENTS&				_request);

	// 3) LINE Profile
	RESPONSE_LINE_PROFILE					request(const REQUEST_LINE_PROFILE&						_request);

	// 4) LINE Group
	RESPONSE_LINE_GROUP_MEMBER				request(const REQUEST_LINE_GROUP_MEMBER&				_request);
	RESPONSE_LINE_GROUP_MEMBER_IDS			request(const REQUEST_LINE_GROUP_MEMBER_IDS&			_request);
	RESPONSE_LINE_GROUP_LEAVE				request(const REQUEST_LINE_GROUP_LEAVE&					_request);

	// 5) LINE Room
	RESPONSE_LINE_ROOM_MEMBER				request(const REQUEST_LINE_ROOM_MEMBER&					_request);
	RESPONSE_LINE_ROOM_MEMBER_IDS			request(const REQUEST_LINE_ROOM_MEMBER_IDS&				_request);
	RESPONSE_LINE_ROOM_LEAVE				request(const REQUEST_LINE_ROOM_LEAVE&					_request);

	// 6) LINE Rich menu
	RESPONSE_LINE_RICHMENU_GET				request(const REQUEST_LINE_RICHMENU_GET&				_request);
	RESPONSE_LINE_RICHMENU_CREATE			request(const REQUEST_LINE_RICHMENU_CREATE&				_request);
	RESPONSE_LINE_RICHMENU_DELETE			request(const REQUEST_LINE_RICHMENU_DELETE&				_request);
	RESPONSE_LINE_RICHMENU_USER				request(const REQUEST_LINE_RICHMENU_USER&				_request);
	RESPONSE_LINE_RICHMENU_USER_LINK		request(const REQUEST_LINE_RICHMENU_USER_LINK&			_request);
	RESPONSE_LINE_RICHMENU_USER_UNLINK		request(const REQUEST_LINE_RICHMENU_USER_UNLINK&		_request);
	RESPONSE_LINE_RICHMENU_CONTENT_DOWNLOAD	request(const REQUEST_LINE_RICHMENU_CONTENT_DOWNLOAD&	_request);
	RESPONSE_LINE_RICHMENU_CONTENT_UPLOAD	request(const REQUEST_LINE_RICHMENU_CONTENT_UPLOAD&		_request);
	RESPONSE_LINE_RICHMENU_LIST				request(const REQUEST_LINE_RICHMENU_LIST&				_request);
}
