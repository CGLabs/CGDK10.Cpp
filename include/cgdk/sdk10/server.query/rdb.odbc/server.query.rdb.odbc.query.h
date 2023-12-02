//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Query odbc Classes                         *
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
// query::rdb::odbc::Cquery
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR>
class query::rdb::odbc::Cquery : 
	public					Nquery
{
public:
			typedef	Cquery<TACCESSOR> TSELF;
			typedef typename Cquery<TACCESSOR>::template ITERATOR<TSELF> TITERATOR;

	[[nodiscard]] auto				result() noexcept { return _ITEM<Cquery>{this}; }
	[[nodiscard]] ITERATOR<Cquery>	begin() { return TITERATOR(this, (this->m_handle_stmt != 0) ? this->move_first() : result_code(eRESULT::FAIL)); }
	[[nodiscard]] ITERATOR<Cquery>	end() { return TITERATOR(nullptr, eRESULT::SUCCESS); }
};


}