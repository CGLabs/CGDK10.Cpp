//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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

//-----------------------------------------------------------------------------
// 1. http definitions
//-----------------------------------------------------------------------------
enum class net::email::eSTATE
{
	NONE			 = 0,
	REQUESTED		 = 1,
	SEND_HELLO		 = 2,
	SEND_AUTH		 = 3,
	SEND_NAME		 = 4,
	SEND_PASSWORD	 = 5,
	SEND_MAIL_FROM	 = 6,
	SEND_RCPT_TO	 = 7,
	REQUEST_DATA	 = 8,
	SEND_DATA		 = 9,
	SEND_QUIT		 = 10,
	DONE			 = 11,
};

enum class net::email::eAUTH_TYPE
{
	NONE			 = 0,
	PLAIN_CRAM_MD5	 = 1,
	XOAUTH_XOAUTH2	 = 2,
	GSSAPI_NTLM		 = 3,
	GSSAPI_PLAIN	 = 4,
};

struct net::email::sRESULT;

struct net::email::sAUTH
{
	std::string		name;
	std::string		password;
};

struct net::email::sREQUEST
{
public:
	std::string		from;
	std::string		to;
	std::vector<std::string> cc_list;
	std::string		subject;
	shared_buffer	text;
	sAUTH			auth;

	std::function<void(const sRESULT&)> complete;

public:
	void clear() noexcept
	{
		from.clear();
		to.clear();
		cc_list.clear();
		subject.clear();
		text.clear();
		complete = std::function<void(const sRESULT&)>();
	}
};

struct net::email::sRESULT
{
public:
	net::email::sREQUEST request;

	chrono::time::utc::time_point send_time;
	eRESULT			result = eRESULT::SUCCESS;
	eSTATE			state = eSTATE::NONE;
	eAUTH_TYPE		auth_type = eAUTH_TYPE::NONE;
	std::vector<std::string> vector_result;

public:
	void clear() noexcept
	{
		request.clear();
		result = eRESULT::SUCCESS;
		state = eSTATE::NONE;
		vector_result.clear();
	}
};


}