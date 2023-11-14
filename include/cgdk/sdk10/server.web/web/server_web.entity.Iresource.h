//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
//*                                                                           *
//*                             Web Server Classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 (c) 2016 Cho Sanghyun All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CGDK::server::web::entity::Iresource
//
//
// ----------------------------------------------------------------------------
class server::web::entity::Iresource :
// inherited classes) 
	virtual public				server::web::Ientity
{
// constructor/destructor)
protected:
	virtual	~Iresource() noexcept {}

// implementation)
protected:
			std::filesystem::path m_path_source;
};


}