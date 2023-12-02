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
// Login(�α���)
//
//  �⺻������ OAuth 2.0�� ������ ������.
//  ���� �α���ó���� 'Authorize'�� ���� 'authorize_code(���� �ڵ�)'�� ���� ��
//  'token'�� ���� 'access_token'�� �޾� �� 'access_token'���� ���� ������ �����Ѵ�.

//
//   1) Authorize (�ڵ� �ޱ�)
//   2) Token (����� ��ū ����)
//   3) Logout (�α� �ƿ�)
//   4) Signup (�� ����)
//   5) Unlink (�� ���� ����)
//   6) Me (����� ���� ��û)
//   7) UPDATE_PROFILE (����� ���� ����)
//   8) IDS (����� ����Ʈ ��û)
//   9) ACCESS_TOKEN_INFO (����� ��ū ��ȿ�� �˻� �� ���� ���)
//  10) memo/default/send (���� ����)
//
// ----------------------------------------------------------------------------
// 1) Authorize (�ڵ�ޱ�)
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


// 2) Token (����� ��ū ����)
struct REQUEST_TOKEN : public query::REQUEST
{
public:												// grant_type�� refresh_token���� ����
	static_string<64>			client_id;			// �� ������ �߱� ���� REST_API Ű
	static_string<64>			redirect_uri;		// �ڵ尡 �����̷�Ʈ �� URI, ����>�Ϲ�>��>�����̴ϻ���Ʈ���� ������ ������ �����ο� ����>�Ϲ�>��>Redirect Path�� ���� URI
	static_string<64>			code;				// �� �ڵ�ޱ�(AUTHORIZE)���� �߱� ���� ������ �ڵ�('authorize_code')
	static_string<64>			client_secret;		// Option) 

public:
	REQUEST_TOKEN() noexcept : REQUEST{ "kauth.kakao.com" } {}
};

struct RESPONSE_TOKEN : public query::RESPONSE
{
public:												
	static_string<64>			access_token;		// access_token�� �߱� ���� �� 12�ð� 24�ð�(��å�� ���� ���� ����) ���� ��ȿ�մϴ�. refresh_token�� �Ѵް� ��ȿ�ϸ�, refresh_token ���ᰡ 1���� �̳��� ���� �������� ����� ��ū ���� ��û�� �ϸ� ���ŵ� access_token�� ���ŵ� refresh_token�� �Բ� ��ȯ�˴ϴ�.
	static_string<64>			token_type;			// 'bearer'
	static_string<64>			refresh_token;		// ��ū�� ����Ǹ� ��ū ��û �������� ���� �Ǵ� ��ū ���� ��û �������� ���� refresh_token�� �̿��Ͽ� ��ū�� �����մϴ�.
	static_string<64>			expires_in;			// ����ð�(�� ����)
	static_string<64>			scope;				// 'Basic_Profile'
};


// 3) LOGOUT (īī�� ������ ���� �����ϴ� ���)
struct REQUEST_LOGOUT : public query::REQUEST
{
public:
	static_string<64>			access_token;		// ����� ��ū�� ����� ��� POST�� ��û�մϴ�.

public:
	REQUEST_LOGOUT() noexcept : REQUEST{ "kapi.kakao.com" } {}
};

struct RESPONSE_LOGOUT : public query::RESPONSE
{
public:
	static_string<64>			id;
};


// 4) SIGNUP (�ۿ���)
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
