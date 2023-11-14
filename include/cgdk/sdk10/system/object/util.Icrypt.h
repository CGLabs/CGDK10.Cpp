//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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
//
// cryptBase
//
// 1. cryptBase란!
//    1) 암복호화에 관련된...
//
//
//-----------------------------------------------------------------------------
enum class eCRYPTION_TYPE : int32_t
{
	NONE,
	PNCODE_BYTE,
	PNCODE_DWORD,
	DES,
	RSA,
	CSP,
};

class Idecoder : 
// inherited classes)
	virtual	public				Ireferenceable
{
// constructor/destructor) 
public:
	virtual	~Idecoder()			{}

// public)
public:
	virtual buffer_view			decode(buffer_view _dest, const_buffer_view _source) PURE;

	virtual	shared_buffer		initialize_decoder() PURE;
	virtual	void				initialize_decoder(buffer_view _seed_info) PURE;
};


class Iencoder : 
// inherited classes)
	virtual	public				Ireferenceable
{
// constructor/destructor) 
public:
	virtual	~Iencoder()		{}

// public)
public:
	virtual buffer_view			encode(buffer_view _dest, const_buffer_view _source) PURE;

	virtual	shared_buffer		initialize_encoder() PURE;
	virtual	void				initialize_encoder(buffer_view _seed_info) PURE;
};


class Icryptable;

class Icrypt : 
// inherited classes)
	virtual	public				Ireferenceable
{
public:
	virtual	void				initialize_handshake_server(Icryptable* _pcryptable) PURE;
	virtual	void				initialize_handshake_client(Icryptable* _pcryptable) PURE;

	virtual bool				encode(buffer_view& _dest, const const_buffer_view* _source, int _count) PURE;
	virtual bool				decode(buffer_view& _dest, const_buffer_view* _source, int _count) PURE;
};


}