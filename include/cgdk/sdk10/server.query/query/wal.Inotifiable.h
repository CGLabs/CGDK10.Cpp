//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// Iserver_query
//
// 1. Iserver_query...
//    1) query request and have it's result
//
//-----------------------------------------------------------------------------
template <class T>
struct wal::sCHUNK
{
	uint64_t		size;
	uint64_t		pos_end;
	uint64_t		key_a;
	uint64_t		key_b;
	T				data;
};

template <class T>
struct wal::sQUERY
{
	uint64_t		size;
	uint64_t		pos_end;
	object_ptr<T>	pquery;
};

struct wal::sHEADER
{
	char			init_string[64];
	uint64_t		key[4];
	uint32_t		version_major;
	uint64_t		version_minor;
	uint64_t		value[2];
};

template <class T>
class wal::Inotifiable : virtual public Ireferenceable
{
// public)
public:
	virtual void				process_wal_restore(T* /*_query*/) {}
	virtual void				process_wal_appended(T* /*_query*/) {}
};

template <class T, class Q>
class wal::Inotifiable_file : public wal::Inotifiable<T>
{
// public)
public:
	virtual object_ptr<Q>		process_wal_query(std::vector<sCHUNK<T>>& _vector_query, bool _is_close = false) PURE;
};


}