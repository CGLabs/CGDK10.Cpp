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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
//  definitions
//
//-----------------------------------------------------------------------------
typedef class stServer_Info
{
public:
	net::sockaddr	nServer_Address;

	uint32_t	nServer_Type;
	uint32_t	nServer_No;

	uint64_t	nServer_SessionKey;

	uint32_t	nServer_Player_Count;

public:
	stServer_Info()
	{
		nServer_Address.clear();
		nServer_Type			 = 0;
		nServer_No				 = 0;
		nServer_SessionKey		 = 0;
		nServer_Player_Count	 = 0;
	}
} SERVER_INFO, *LPSERVER_INFO;


struct ACCOUNT_ID
{
public:
	bool		valid() const	{ return u64Account!=0;}
	void		reset()			{ u64Account=0;}

public:
	uint64_t	u64Account;

public:
	ACCOUNT_ID() : u64Account(0) {}
	explicit ACCOUNT_ID(uint64_t _id) : u64Account(_id) {}

	bool				operator==(const ACCOUNT_ID& _rhs) const { return u64Account==_rhs.u64Account; }
	bool				operator!=(const ACCOUNT_ID& _rhs) const { return u64Account!=_rhs.u64Account; }
	bool				operator>=(const ACCOUNT_ID& _rhs) const { return u64Account>=_rhs.u64Account; }
	bool				operator> (const ACCOUNT_ID& _rhs) const { return u64Account> _rhs.u64Account; }
	bool				operator<=(const ACCOUNT_ID& _rhs) const { return u64Account<=_rhs.u64Account; }
	bool				operator< (const ACCOUNT_ID& _rhs) const { return u64Account< _rhs.u64Account; }

						operator uint64_t() const { return u64Account;}
};

namespace std
{
template <>
struct hash<ACCOUNT_ID>
{
	std::size_t operator()(const ACCOUNT_ID& _Key) const
	{
		return	static_cast<size_t>(static_cast<uint64_t>(_Key.u64Account));
	}
};
}


// 1) Channel ID
typedef	uint64_t	CHANNEL_ID;

// 2) Channel Type
enum class eCHANNEL_TYPE : uint32_t
{
	NONE			 = 0,
	WAITING			 = 1,
	CHATTING		 = 2,
	BATTLE			 = 3,

	DEFAULT			 = CHATTING,
	START			 = WAITING,
};

// 3) Channel Option
enum class eCHANNEL_OPTION : uint32_t
{
	NONE					 = 0x00000000,
	ENTER_ALWAYS			 = 0x00000001,	// 해당 방이 없으면 생성해서 입장
	DESTROY_ON_EMPTY		 = 0x00000002,	// 빈방이 되면 소멸
	SYSTEM					 = 0x00000004,	// 시스템적인 채널이다.
	HAS_PASSWORD			 = 0x00000010,	// 비밀번호
	HAS_HIDE				 = 0x00000020,	// 목록에서 숨김
	HAS_MAX_MEMBER			 = 0x00000040,	// 최대 인원 제한이 있는가
	HAS_FUNCTION_MASTER		 = 0x00000100,	// 방장 기능
	HAS_FUNCTION_BAN		 = 0x00000200,	// 밴 기능
	HAS_FUNCTION_INVITE		 = 0x00000400,	// 초청 기능
	HAS_FUNCTION_MUTE		 = 0x00000800,	// 침묵 기능
	ENABLE_CHATTING_FILTER	 = 0x00001000,	// 채팅 필터 (금기어 등 필터처리)

	DEFAULT					 = NONE
};
inline eCHANNEL_OPTION	operator |	(eCHANNEL_OPTION a, eCHANNEL_OPTION b)	{ return eCHANNEL_OPTION(((uint32_t)a) | (uint32_t)b); }
inline eCHANNEL_OPTION&	operator |= (eCHANNEL_OPTION& a, eCHANNEL_OPTION b)	{ return (eCHANNEL_OPTION &)(((uint32_t &)a) |= (uint32_t)b); }
inline eCHANNEL_OPTION	operator &	(eCHANNEL_OPTION a, eCHANNEL_OPTION b)	{ return eCHANNEL_OPTION(((uint32_t)a) & (uint32_t)b); }
inline eCHANNEL_OPTION&	operator &=	(eCHANNEL_OPTION& a, eCHANNEL_OPTION b)	{ return (eCHANNEL_OPTION &)(((uint32_t &)a) &= (uint32_t)b); }
inline eCHANNEL_OPTION	operator ~	(eCHANNEL_OPTION a)						{ return eCHANNEL_OPTION(~((uint32_t)a)); }
inline eCHANNEL_OPTION	operator ^	(eCHANNEL_OPTION a, eCHANNEL_OPTION b)	{ return eCHANNEL_OPTION(((uint32_t)a) ^ (uint32_t)b); }
inline eCHANNEL_OPTION&	operator ^= (eCHANNEL_OPTION& a, eCHANNEL_OPTION b)	{ return (eCHANNEL_OPTION &)(((uint32_t &)a) ^= (uint32_t)b); }
inline eCHANNEL_OPTION	operator |	(eCHANNEL_OPTION a, uint32_t b)			{ return eCHANNEL_OPTION(((uint32_t)a) | (uint32_t)b); }
inline eCHANNEL_OPTION&	operator |= (eCHANNEL_OPTION& a, uint32_t b)		{ return (eCHANNEL_OPTION &)(((uint32_t &)a) |= (uint32_t)b); }
inline eCHANNEL_OPTION	operator &	(eCHANNEL_OPTION a, uint32_t b)			{ return eCHANNEL_OPTION(((uint32_t)a) & (uint32_t)b); }
inline eCHANNEL_OPTION&	operator &=	(eCHANNEL_OPTION& a, uint32_t b)		{ return (eCHANNEL_OPTION &)(((uint32_t &)a) &= (uint32_t)b); }
inline eCHANNEL_OPTION	operator ^	(eCHANNEL_OPTION a, uint32_t b)			{ return eCHANNEL_OPTION(((uint32_t)a) ^ (uint32_t)b); }
inline eCHANNEL_OPTION&	operator ^=	(eCHANNEL_OPTION& a, uint32_t b)		{ return (eCHANNEL_OPTION &)(((uint32_t &)a) ^= (uint32_t)b); }

inline const wchar_t* to_string(eCHANNEL_TYPE _ChannelType)
{
	const wchar_t* str;

	switch (_ChannelType)
	{
	case	eCHANNEL_TYPE::NONE:		str = L"NONE";		break;
	case	eCHANNEL_TYPE::WAITING:		str = L"WAITING";	break;
	case	eCHANNEL_TYPE::CHATTING:	str = L"CHATTING";	break;
	case	eCHANNEL_TYPE::BATTLE:		str = L"BATTLE";	break;
	default:							str = L"(n/a)";		break;
	}

	// Return) 
	return	str;
}

struct CHANNEL_INFO
{
public:
			CHANNEL_ID			idChannel;
			eCHANNEL_TYPE		eType;
			eCHANNEL_OPTION		eOption;
			net::sockaddr		addrServer;

public:
			bool	empty() const noexcept	{ return addrServer.empty(); }
};
