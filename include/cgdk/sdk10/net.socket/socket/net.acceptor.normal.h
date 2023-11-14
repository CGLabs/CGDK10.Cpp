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
// net::acceptor<T> - 
//
//-----------------------------------------------------------------------------
template <typename TSOCKET>
class net::acceptor<TSOCKET, typename std::enable_if<!std::is_base_of<net::io::Nhttp_server, TSOCKET>::value && !std::is_base_of<net::io::Nsocket_secure, TSOCKET>::value>::type> :
	public						net::io::connective::acceptor::Ntcp,
	public						Nmessage_transmitter,
	public						net::io::connectable_manager::list<TSOCKET>
{
public:
			acceptor()
			{
				// - 기본 acceptor의 Name을 기본 이름으로 설정한다.
				this->set_name(NFMT::format("acceptor<{}>", typeid(TSOCKET).name()));
			}
			acceptor(std::string_view _name) : net::io::connective::acceptor::Ntcp{ _name }
			{
				// - Name이 없을 경우 acceptor의 Name을 설정한다.
				if (_name.empty())
				{
					this->set_name(NFMT::format("acceptor<{}>", typeid(TSOCKET).name()));
				}
			}
	virtual	~acceptor() noexcept {}

protected:
	virtual	object_ptr<net::io::Iconnectable> process_alloc_connectable() override { return alloc_object<TSOCKET>(); }
	virtual result_code			_process_destroy() noexcept override { auto result = this->net::io::connective::acceptor::Ntcp::_process_destroy(); this->reset_message_transmitter(); return result; }
};


}