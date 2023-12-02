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
// net::io::connective::Iacceptor
//
//-----------------------------------------------------------------------------
class net::io::connective::Iacceptor : 
// inherited classes)
	virtual public				net::io::Isocket,
	virtual	public				net::io::Iconnective
{
// defintions)
public:
			using end_point_type = net::ip::tcp::endpoint;
			using START_PARAMETER = sSOCKET_ACCEPT_PARAMETER;

// publics)
public:
	// 1) socket status
	[[nodiscard]] virtual std::size_t prepared_socket_count() const noexcept PURE;
	[[nodiscard]] virtual std::size_t must_prepare_socket_count() const noexcept PURE;

	// 2) address
	[[nodiscard]] virtual end_point_type get_accept_endpoint() const noexcept PURE;
	virtual void				set_accept_endpoint(const end_point_type& _accept_endpoint) noexcept PURE;
	virtual void				reset_accept_endpoint() noexcept PURE;
};


}