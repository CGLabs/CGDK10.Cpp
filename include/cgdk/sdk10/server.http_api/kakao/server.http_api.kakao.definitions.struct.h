//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           server.http_api.kakao                           *
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

namespace CGDK::http_api::kakao
{
	
//-----------------------------------------------------------------------------
//
// Login(로그인)
//
//  기본적으로 OAuth 2.0의 기준을 따른다.
//  따라서 로그인처리는 'Authorize'를 통해 'authorize_code(인증 코드)'를 받은 후
//  'token'을 통해 'access_token'을 받아 이 'access_token'으로 각종 조작을 수행한다.

//
//   1) Authorize (코드 받기)
//   2) Token (사용자 토큰 갱신)
//   3) Logout (로그 아웃)
//   4) Signup (앱 연결)
//   5) Unlink (앱 연결 해제)
//   6) Me (사용자 정보 요청)
//   7) UPDATE_PROFILE (사용자 정보 저장)
//   8) IDS (사용자 리스트 요청)
//   9) ACCESS_TOKEN_INFO (사용자 토큰 유효성 검사 및 정보 얻기)
//  10) memo/default/send (동적 동의)
//
// ----------------------------------------------------------------------------
// 1) Authorize (코드받기)
struct REQUEST_AUTHORIZE : public query::REQUEST
{
public:
	static_string<64>			client_id;
	static_string<64>			redirect_uri;
	static_string<64>			state;
	bool						encode_state = false;

public:
	REQUEST_AUTHORIZE() noexcept : REQUEST{ "kauth.kakao.com" } {}
};

struct RESPONSE_AUTHORIZE : public query::RESPONSE
{
public:
	static_string<64>			code;
};


// 2) Token (사용자 토큰 갱신)
struct REQUEST_TOKEN : public query::REQUEST
{
public:												// grant_type은 refresh_token으로 고정
	static_string<64>			client_id;			// 앱 생성시 발급 받은 REST_API 키
	static_string<64>			redirect_uri;		// 코드가 리다이렉트 된 URI, 설정>일반>웹>도매이니사이트에서 설정한 각각의 도메인에 설정>일반>웹>Redirect Path를 붙인 URI
	static_string<64>			code;				// 위 코드받기(AUTHORIZE)에서 발급 받은 인증된 코드('authorize_code')
	static_string<64>			client_secret;		// Option) 

public:
	REQUEST_TOKEN() noexcept : REQUEST{ "kauth.kakao.com" } {}
};

struct RESPONSE_TOKEN : public query::RESPONSE
{
public:												
	static_string<64>			access_token;		// access_token은 발급 받은 후 12시간 24시간(정책에 따라 변동 가능) 동안 유효합니다. refresh_token은 한달간 유효하며, refresh_token 만료가 1주일 이내로 남은 시점에서 사용자 토큰 갱신 요청을 하면 갱신된 access_token과 갱신된 refresh_token이 함께 반환됩니다.
	static_string<64>			token_type;			// 'bearer'
	static_string<64>			refresh_token;		// 토큰이 만료되면 토큰 요청 응답으로 받은 또는 토큰 갱신 요청 응답으로 받은 refresh_token을 이용하여 토큰을 갱신합니다.
	static_string<64>			expires_in;			// 만료시간(초 단위)
	static_string<64>			scope;				// 'Basic_Profile'
};


// 3) LOGOUT (카카오 계정과 연결 해제하는 기능)
struct REQUEST_LOGOUT : public query::REQUEST
{
public:
	static_string<64>			access_token;		// 사용자 토큰을 헤더에 담아 POST로 요청합니다.

public:
	REQUEST_LOGOUT() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_LOGOUT : public query::RESPONSE
{
public:
	static_string<64>			id;
};


// 4) SIGNUP (앱연결)
struct REQUEST_SIGNUP : public query::REQUEST
{
public:
	static_string<64>			access_token;		// 
	static_string<64>			properties;

public:
	REQUEST_SIGNUP() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_SIGNUP : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 5) UNLINK
struct REQUEST_UNLINK : public query::REQUEST
{
public:
	static_string<64>			access_token;
	static_string<64>			admin_key;

public:
	REQUEST_UNLINK() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_UNLINK : public query::RESPONSE
{
public:
	static_string<64>			id;
};


// 6) ME
struct REQUEST_ME : public query::REQUEST
{
public:
	static_string<64>			target_id_type;
	static_string<64>			target_id;
	static_string<64>			property_keys;
	static_string<64>			secure_resource;

public:
	REQUEST_ME() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_ME : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 7) UPDATE_PROFILE
struct REQUEST_UPDATE_PROFILE : public query::REQUEST
{
public:
	static_string<64>			access_token;
	static_string<64>			property;

public:
	REQUEST_UPDATE_PROFILE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_UPDATE_PROFILE : public query::RESPONSE
{
public:
	static_string<64>			id;
};


// 8) IDS
struct REQUEST_IDS : public query::REQUEST
{
public:
	static_string<64>			admin_key;
	static_string<64>			limit;
	static_string<64>			from_id;
	static_string<64>			order;

public:
	REQUEST_IDS() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_IDS : public query::RESPONSE
{
public:
	static_string<64>			elements;
	static_string<64>			total_count;
	static_string<64>			before_url;
	static_string<64>			after_url;
};


// 9) ACCESS_TOKEN_INFO
struct REQUEST_ACCESS_TOKEN_INFO : public query::REQUEST
{
public:
	static_string<64>		admin_key;

public:
	REQUEST_ACCESS_TOKEN_INFO() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_ACCESS_TOKEN_INFO : public query::RESPONSE
{
public:
	static_string<64>			id;
	static_string<64>			expiresInMillis;
	static_string<64>			appId;
};


//-----------------------------------------------------------------------------
//
// KAKAO Talk
//
//RESPONSE_TAKL_PROFILE					request(const REQUEST_TALK_PROFILE&			_request);
//RESPONSE_TAKL_SEND					request(const REQUEST_TALK_SEND&				_request);
// ----------------------------------------------------------------------------
// 1) TALK_PROFILE
struct REQUEST_TALK_PROFILE : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_TALK_PROFILE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_TAKL_PROFILE : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 2) TALK_SEND
struct REQUEST_TALK_SEND : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_TALK_SEND() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_TAKL_SEND : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


//-----------------------------------------------------------------------------
//
// KAKAO Pay
//
// RESPONSE_PAY_READY					request(const REQUEST_PAY_READY&				_request);
// RESPONSE_PAY_APPROVE				request(const REQUEST_PAY_APPROVE&			_request);
// RESPONSE_PAY_SUBSCRIPTION			request(const REQUEST_PAY_SUBSCRIPTION&		_request);
// RESPONSE_PAY_CANCEL				request(const REQUEST_PAY_CANCEL&				_request);
// RESPONSE_PAY_ORDER					request(const REQUEST_PAY_ORDER&				_request);
// RESPONSE_PAY_ORDERS				request(const REQUEST_PAY_ORDERS&				_request);
// RESPONSE_PAY_STATUS				request(const REQUEST_PAY_STATUS&				_request);
// RESPONSE_PAY_INACTIVE				request(const REQUEST_PAY_INACTIVE&			_request);
// ----------------------------------------------------------------------------
// 1) READY
struct REQUEST_PAY_READY : public query::REQUEST
{
public:
	static_string<64>		temp;

public:
	REQUEST_PAY_READY() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_READY : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 2) KAKAO_PAY_APPROVE
struct REQUEST_PAY_APPROVE : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_APPROVE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_APPROVE : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 3) PAY_SUBSCRIPTION
struct REQUEST_PAY_SUBSCRIPTION : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_SUBSCRIPTION() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_SUBSCRIPTION : public query::RESPONSE
{
public:
	static_string<64>			temp;
};



// 4) KAKAO_PAY_CANCEL
struct REQUEST_PAY_CANCEL : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_CANCEL() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_CANCEL : public query::RESPONSE
{
public:
	static_string<64>			temp;
};



// 5) KAKAO_PAY_ORDER
struct REQUEST_PAY_ORDER : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_ORDER() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_ORDER : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 6) KAKAO_PAY_ORDERS
struct REQUEST_PAY_ORDERS : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_ORDERS() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_ORDERS : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 7) KAKAO_PAY_ORDERS
struct REQUEST_PAY_STATUS : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_STATUS() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_STATUS : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 8) KAKAO_PAY_INACTIVE
struct REQUEST_PAY_INACTIVE : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PAY_INACTIVE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PAY_INACTIVE : public query::RESPONSE
{
public:
	static_string<64>			temp;
};



//-----------------------------------------------------------------------------
//
// KAKAO Story
//
// RESPONSE_STORY_ISSTORYUSER			request(const REQUEST_STORY_ISSTORYUSER&		_request);
// RESPONSE_STORY_PROFILE				request(const REQUEST_STORY_PROFILE&			_request);
// RESPONSE_STORY_NOTE				request(const REQUEST_STORY_NOTE&				_request);
// RESPONSE_STORY_UPLOAD				request(const REQUEST_STORY_UPLOAD&			_request);
// RESPONSE_STORY_PHOTO				request(const REQUEST_STORY_PHOTO&			_request);
// RESPONSE_STORY_LINKINFO			request(const REQUEST_STORY_LINKINFO&			_request);
// RESPONSE_STORY_LINK				request(const REQUEST_STORY_LINK&				_request);
// RESPONSE_STORY_MYSTORY				request(const REQUEST_STORY_MYSTORY&			_request);
// RESPONSE_STORY_MYSTORIES			request(const REQUEST_STORY_MYSTORIES&		_request);
// RESPONSE_STORY_DELETE_MYSTROY		request(const REQUEST_STORY_DELETE_MYSTROY&	_request);
//
// ----------------------------------------------------------------------------
// 1) ISSTORYUSER
struct REQUEST_STORY_ISSTORYUSER : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_ISSTORYUSER() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_ISSTORYUSER : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 2) PROFILE
struct REQUEST_STORY_PROFILE : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_PROFILE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_PROFILE : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 3) NOTE
struct REQUEST_STORY_NOTE : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_NOTE() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_NOTE : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 4) UPLOAD
struct REQUEST_STORY_UPLOAD : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_UPLOAD() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_UPLOAD : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 5) REQUEST_STORY_PHOTO
struct REQUEST_STORY_PHOTO : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_PHOTO() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_PHOTO : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 6) LINKINFO
struct REQUEST_STORY_LINKINFO : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_LINKINFO() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_LINKINFO : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 7)STORY_LINK
struct REQUEST_STORY_LINK : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_LINK() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_LINK : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 8) MYSTORY
struct REQUEST_STORY_MYSTORY : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_MYSTORY() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_MYSTORY : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 9) MYSTORIES
struct REQUEST_STORY_MYSTORIES : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_MYSTORIES() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_MYSTORIES : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 10) MYSTORIES
struct REQUEST_STORY_DELETE_MYSTROY : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_STORY_DELETE_MYSTROY() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_STORY_DELETE_MYSTROY : public query::RESPONSE
{
public:
	static_string<64>			temp;
};



//-----------------------------------------------------------------------------
//
// KAKAO Push
//
//
// RESPONSE_PUSH_REGISTER				request(const REQUEST_PUSH_REGISTER&			_request);
// RESPONSE_PUSH_TOKENS				request(const REQUEST_PUSH_TOKENS&			_request);
// RESPONSE_PUSH_DEREGISTER			request(const REQUEST_PUSH_DEREGISTER&		_request);
// RESPONSE_PUSH_GCM_PUSH_FAIL		request(const REQUEST_PUSH_GCM_PUSH_FAIL&		_request);
// ----------------------------------------------------------------------------
// 1) REGISTER
struct REQUEST_PUSH_REGISTER : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PUSH_REGISTER() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PUSH_REGISTER : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 2) TOKENS
struct REQUEST_PUSH_TOKENS : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PUSH_TOKENS() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PUSH_TOKENS : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 3) DEREGISTER
struct REQUEST_PUSH_DEREGISTER : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PUSH_DEREGISTER() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PUSH_DEREGISTER : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


// 4) GCM_PUSH_FAIL
struct REQUEST_PUSH_GCM_PUSH_FAIL : public query::REQUEST
{
public:
	static_string<64>			temp;

public:
	REQUEST_PUSH_GCM_PUSH_FAIL() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_PUSH_GCM_PUSH_FAIL : public query::RESPONSE
{
public:
	static_string<64>			temp;
};


}
