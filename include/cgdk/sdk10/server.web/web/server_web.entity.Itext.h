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
// CGDK::server::web::entity::Itext
//
//
// ----------------------------------------------------------------------------
class server::web::entity::Itext :
// inherited classes) 
	virtual public				server::web::Ientity
{
// constructor/destructor)
protected:
	virtual	~Itext() noexcept {}

// public)
public:
	virtual	int					get_encode_type() const noexcept PURE;
	virtual	void				set_encode_type(int _type) PURE;

// implementation)
protected:

};


}