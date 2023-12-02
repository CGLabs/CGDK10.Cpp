//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// 1. [SEQUENCE_ID]
//
//
//-----------------------------------------------------------------------------
using SEQUENCE_ID = uint64_t;


//-----------------------------------------------------------------------------
//
// 2. [RESTORE_SERVER_ID]
//
//
//-----------------------------------------------------------------------------
struct RESTORE_SERVER_ID
{
public:
	uint64_t	id_key;
	uint64_t	id_certify;

public:
	RESTORE_SERVER_ID() noexcept : id_key(0), id_certify(0) {}

	bool				empty() const noexcept	{ return id_key == 0 || id_certify == 0; }
	bool				exist() const noexcept	{ return id_key != 0 && id_certify != 0; }
	void				reset() noexcept		{ id_key=0; id_certify=0;}

	RESTORE_SERVER_ID&	operator = (const RESTORE_SERVER_ID& _rhs) noexcept { id_key = _rhs.id_key; id_certify = _rhs.id_certify; return *this; }

	bool				operator ==(const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key == _rhs.id_key && id_certify == _rhs.id_certify; }
	bool				operator !=(const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key != _rhs.id_key || id_certify != _rhs.id_certify; }
	bool				operator > (const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key >  _rhs.id_key; }
	bool				operator >=(const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key >= _rhs.id_key; }
	bool				operator < (const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key <  _rhs.id_key; }
	bool				operator <=(const RESTORE_SERVER_ID& _rhs) const noexcept { return id_key <= _rhs.id_key; }
};


//-----------------------------------------------------------------------------
//
// 3. [RESTORE_CLIENT_ID]
//
//
//-----------------------------------------------------------------------------
struct RESTORE_CLIENT_ID
{
public:
	uint64_t	id_key;
	uint64_t	id_certify;

public:
	RESTORE_CLIENT_ID() noexcept : id_key(0), id_certify(0) {}

	bool				empty() const noexcept	{ return id_key == 0 || id_certify == 0; }
	bool				exist() const noexcept	{ return id_key != 0 && id_certify != 0; }
	void				reset() noexcept		{ id_key=0; id_certify=0;}

	RESTORE_CLIENT_ID&	operator = (const RESTORE_CLIENT_ID& _rhs) noexcept { id_key = _rhs.id_key; id_certify = _rhs.id_certify; return *this; }

	bool				operator ==(const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key == _rhs.id_key && id_certify == _rhs.id_certify; }
	bool				operator !=(const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key != _rhs.id_key || id_certify != _rhs.id_certify; }
	bool				operator > (const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key >  _rhs.id_key; }
	bool				operator >=(const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key >= _rhs.id_key; }
	bool				operator < (const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key <  _rhs.id_key; }
	bool				operator <=(const RESTORE_CLIENT_ID& _rhs) const noexcept { return id_key <= _rhs.id_key; }
};


}

