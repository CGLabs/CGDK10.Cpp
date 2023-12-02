//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::acceptor<TSOCKET>
//
//  1) acceptor for general secure(ssl) tcp socket
//
//-----------------------------------------------------------------------------
template <class TSOCKET>
class net::acceptor<TSOCKET, typename std::enable_if<!std::is_base_of<net::io::Nhttp_server, TSOCKET>::value && std::is_base_of<net::io::Nsocket_secure, TSOCKET>::value>::type> :
// inherited classes) 
	public						net::io::connective::acceptor::Ntcp_secure,
	public						Nmessage_transmitter,
	public						net::io::connectable_manager::list<TSOCKET>
{
// definitions)
	using	TBASE_ACCEPTOR = net::io::connective::acceptor::Ntcp_secure;

// constructor/destructor) 
public:
			acceptor()
			{
				// check) 
				static_assert(std::is_base_of_v<Icryptable, TSOCKET>, "secured socket must have 'Icryptable' interface (dereive 'net::io::connect_requestable::Ntcp_secure' or 'net::io::Nsocket_secure')");
			}
			acceptor(std::string_view _name) : net::io::connective::acceptor::Ntcp_secure{ _name }
			{
				// check) 
				static_assert(std::is_base_of_v<Icryptable, TSOCKET>, "secured socket must have 'Icryptable' interface (dereive 'net::io::connect_requestable::Ntcp_secure' or 'net::io::Nsocket_secure')");

				// 1) Name이 없을 경우 acceptor의 Name을 설정한다.
				if (_name.empty())
				{
					// declare) 
					char temp[MAX_NAME_LENGTH];

					// - 기본 acceptor의 Name을 설정한다.
					__sprintf(temp, "acceptor.http<%s>", typeid(TSOCKET).name());

					// - 기본 이름을 설정한다.
					set_name(temp);
				}
			}
	virtual	~acceptor() noexcept {}

// public) 
protected:
	virtual	object_ptr<net::io::Iconnectable> process_alloc_connectable() override { return alloc_object<TSOCKET>(); }
	virtual bool				_process_destroy() noexcept override { auto result = net::io::connective::acceptor::Ntcp_secure::_process_destroy(); reset_message_transmitter(); return result; }

protected:
	// 1) set default port
	virtual	uint16_t			process_get_default_port() noexcept override { return 0;}
};


}
