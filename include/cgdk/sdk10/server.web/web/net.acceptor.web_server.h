//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             CGDK10.server.web                             *
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
// CGDK::net::acceptor_web_server<TSOCKET>
//
//  1) acceptor for general secure(ssl) tcp socket
//
//-----------------------------------------------------------------------------
template <class TSOCKET>
class net::acceptor_web_server :
// inherited classes) 
	public						net::acceptor<TSOCKET>,
	virtual public				server::web::Ientitable
{
// constructor/destructor) 
public:
			acceptor_web_server()
			{
				// check) 
				static_assert(std::is_base_of_v<Icryptable, TSOCKET>, "TSOCKET must inherit 'net::io::Nhttp_server' interface");
			}
			acceptor_web_server(const std::string_view _name) : net::io::connective::acceptor::Ntcp_secure{ _name }
			{
				// check) 
				static_assert(std::is_base_of_v<Icryptable, TSOCKET>, "TSOCKET must inherit 'net::io::Nhttp_server' interface");

				// 1) Name이 없을 경우 acceptor의 Name을 설정한다.
				if (_name.empty())
				{
					// declare) 
					char temp[MAX_NAME_LENGTH];

					// - 기본 acceptor의 Name을 설정한다.
					__sprintf(temp, "acceptor web_server<%s>", typeid(TSOCKET).name());

					// - 기본 이름을 설정한다.
					this->set_name(temp);
				}
			}
	virtual	~acceptor_web_server() noexcept {}
};


}
