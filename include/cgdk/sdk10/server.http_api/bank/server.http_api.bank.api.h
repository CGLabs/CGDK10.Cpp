//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           server.http_api.bank                            *
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
// http_api::bank
//
//
// ----------------------------------------------------------------------------
namespace CGDK::http_api::bank
{
	RESPONSE_AUTHORIZE							request(const REQUEST_AUTHORIZE&					_request);
	RESPONSE_AUTHORIZE2_FIRST					request(const REQUEST_AUTHORIZE2_FIRST&				_request);
	RESPONSE_AUTHORIZE2_REAUTH					request(const REQUEST_AUTHORIZE2_REAUTH&			_request);
	RESPONSE_AUTHORIZE2_AUTH_BYPASS				request(const REQUEST_AUTHORIZE2_AUTH_BYPASS&		_request);
	RESPONSE_TOKEN								request(const REQUEST_TOKEN&						_request);
	RESPONSE_TOKEN2								request(const REQUEST_TOKEN2&						_request);
	RESPONSE_TOKEN_REFRESH						request(const REQUEST_TOKEN_REFRESH&				_request);
	RESPONSE_USER_ME							request(const REQUEST_USER_ME&						_request);
	RESPONSE_UNLINK								request(const REQUEST_UNLINK&						_request);
	RESPONSE_REGISTER_ACCOUNT					request(const REQUEST_REGISTER_ACCOUNT&				_request);
	RESPONSE_UNLINK								request(const REQUEST_UNLINK&						_request);
	RESPONSE_UNLINK								request(const REQUEST_UNLINK&						_request);
	RESPONSE_REGISTER_ACCOUNT					request(const REQUEST_REGISTER_ACCOUNT&				_request);
	RESPONSE_AUTHORIZE_ACCOUNT					request(const REQUEST_AUTHORIZE_ACCOUNT&			_request);
	RESPONSE_AUTHORIZE_ACCOUNT2_FIRST			request(const REQUEST_AUTHORIZE_ACCOUNT2_FIRST&		_request);
	RESPONSE_AUTHORIZE_ACCOUNT2_REAUTH			request(const REQUEST_AUTHORIZE_ACCOUNT2_REAUTH&	_request);
	RESPONSE_AUTHORIZE_ACCOUNT2_BYPASS			request(const REQUEST_AUTHORIZE_ACCOUNT2_BYPASS&	_request);
	RESPONSE_ACCOUNT_LIST						request(const REQUEST_ACCOUNT_LIST&					_request);
	RESPONSE_ACCOUNT_UPDATE_INFO				request(const REQUEST_ACCOUNT_UPDATE_INFO&			_request);
	RESPONSE_ACCOUNT_CANCEL						request(const REQUEST_ACCOUNT_CANCEL&				_request);
	RESPONSE_ACCOUNT_BALANCE					request(const REQUEST_ACCOUNT_BALANCE&				_request);
	RESPONSE_ACCOUNT_TRANSACTION_LIST			request(const REQUEST_ACCOUNT_TRANSACTION_LIST&		_request);
	RESPONSE_TRANSFER_WITHDRAW					request(const REQUEST_TRANSFER_WITHDRAW&			_request);
	RESPONSE_TRANSFER_DEPOSIT					request(const REQUEST_TRANSFER_DEPOSIT&				_request);
	RESPONSE_TRANSFER_DEPOSIT2					request(const REQUEST_TRANSFER_DEPOSIT2&			_request);
	RESPONSE_TRANSFER_RESULT					request(const REQUEST_TRANSFER_RESULT&				_request);
	RESPONSE_TRANSFER_RECHECK					request(const REQUEST_TRANSFER_RECHECK&				_request);
	RESPONSE_INQUIRY_REAL_NAME					request(const REQUEST_INQUIRY_REAL_NAME&			_request);
	RESPONSE_BANK_STATUS						request(const REQUEST_BANK_STATUS&					_request);
}
