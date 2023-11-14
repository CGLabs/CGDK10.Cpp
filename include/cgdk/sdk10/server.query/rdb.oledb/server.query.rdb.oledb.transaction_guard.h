//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query oledb Classes                         *
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
// query::rdb::oledb::transaction_guard
//
//
// 
//-----------------------------------------------------------------------------
class query::rdb::oledb::transaction_guard
{
public:
	transaction_guard(session* _psession);
	~transaction_guard() noexcept;
																						 
public:																						 
	void			_commit();
	void			_abort() noexcept;

protected:
	object_ptr<session>	m_psession;
};

#define	scoped_transaction(pquery)	if(typename CGDK::query::rdb::oledb::transaction_guard _x__temp_transaction(pquery); true)
#define commit						_x__temp_transaction._commit();
#define rollback					_x__temp_transaction._abort();

}