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
// net::io::binder::Nudp
//
// 1. binder은~
//    1) socket의 bind() 기능이 있는 클래스로 기본적으로 UDP의 bind를 위한 것이다.
//
//
//-----------------------------------------------------------------------------
class net::io::binder::Nudp :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ibinder,
	virtual public				net::io::Ireceivable_datagram,
	public						object::Nnameable,
	virtual public				net::io::statistics::Nsocket
{
// constructor/destructor)
protected:
			Nudp() noexcept { register_binder(this); }
			Nudp(std::string_view _name) : object::Nnameable{ _name } {}
	virtual ~Nudp() noexcept { unregister_binder(); }

// publics)
public:
	virtual	bool				process_request_bind(const net::sockaddr& _address) override;
	virtual	void				process_reset_binder() override {}

// framework)
protected:
	virtual	void				on_bind() {}
};


}