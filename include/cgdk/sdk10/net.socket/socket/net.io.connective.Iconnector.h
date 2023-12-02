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
// net::io::connective::Iconnector
//
//-----------------------------------------------------------------------------
class net::io::connective::Iconnector :
// inherited classes)
	virtual	public				net::io::Iconnective
{
// defintions)
public:
			using end_point_type = net::ip::tcp::endpoint;

// publics)
protected:
			Iconnector() { net::io::Iconnective::register_connective(); }
	virtual	~Iconnector() { net::io::Iconnective::unregister_connective(); }

// public)
public:
	// 1) request_connect
			object_ptr<Iconnectable> request_connect(end_point_type _endpoint_remote, end_point_type _endpoint_bind = end_point_type());
			object_ptr<Iconnectable> request_connect(context& _context_connect) { return process_request_connect(_context_connect); }

	// 2) request_connect
			bool				request_connect(Iconnectable* _pconnectable, end_point_type _endpoint_remote, end_point_type _endpoint_bind = end_point_type());
			bool				request_connect(Iconnectable* _pconnectable, context& _context_connect) { return process_connecting(_pconnectable, _context_connect); }

	// 3) 
	[[nodiscard]] virtual end_point_type get_default_endpoint() const noexcept PURE;
	virtual void				set_default_endpoint(const end_point_type& _sockaddr_default)  PURE;

	// 4) allocate connectable
	[[nodiscard]] virtual object_ptr<Iconnectable> alloc_connectable() PURE;

	// 5) executor
	virtual void				io_context(executor::Iio_context* _pio_context) noexcept PURE;
	[[nodiscard]] virtual object_ptr<executor::Iio_context> io_context() const noexcept PURE;

	// 6) 
	virtual	object_ptr<Iconnectable> process_request_connect(context& _context_connect) PURE;
	virtual	bool				process_connecting( Iconnectable* _pconnectable, context& _context_connect) PURE;
};


}