// ----------------------------------------------------------------------------
//
// message definitions
//
// ----------------------------------------------------------------------------
#pragma once


enum eMESSAGE_TYPE : uint32_t
{
	NONE   = 0,
	SEND_A = 0x00000020,
	SEND_B = 0x00000021,
	SEND_C = 0x00000022,
	SEND_D = 0x00000023,
};

// message header
struct sMESSAGE_HEADER
{
	uint32_t			size = 0;
	eMESSAGE_TYPE		type;

	ENABLE_STRUCT_SERIALIZABLE
};

// message A
struct sMESSAGE_A : public sMESSAGE_HEADER
{
	int					x = 0;
	char				y = 0;
	float				z = 0.0f;
};

// message B
struct sMESSAGE_B : public sMESSAGE_HEADER
{
	int							a = 0;
	std::string					b;
	std::vector<int>			c;
	std::map<int, std::string>	d;
};
