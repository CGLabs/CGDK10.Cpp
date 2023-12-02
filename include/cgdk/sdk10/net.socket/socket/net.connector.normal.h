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
// net::connector<TSOCKET> - for general socket
//
//-----------------------------------------------------------------------------
template <class TSOCKET>
class net::connector<TSOCKET, typename std::enable_if<!std::is_base_of<net::io::Nhttp_client, TSOCKET>::value>::type> :
	public						net::io::connective::connector::Ntcp,
	public						net::io::connectable_manager::list<TSOCKET>
{
public:
			connector()
			{
				// - 기본 이름을 설정한다.
				this->set_name(NFMT::format("connector<{}>", typeid(TSOCKET).name()));
			}
			connector(std::string_view _name) : net::io::connective::connector::Ntcp{ _name }
			{
				// - Name이 없을 경우 connector의 Name을 설정한다.
				if (_name.empty())
				{
					this->set_name(NFMT::format("connector<{}>", typeid(TSOCKET).name()));
				}
			}
	virtual	~connector() noexcept
			{
			}

protected:
	[[nodiscard]] virtual object_ptr<net::io::Iconnectable> process_alloc_connectable() override
	{
		return this->_process_alloc_connectable<TSOCKET>();
	}

	template <class NSOCKET>
	[[nodiscard]] static std::enable_if_t<std::is_base_of<net::io::Iconnect_requestable, NSOCKET>::value, object_ptr<TSOCKET>>
	_process_alloc_connectable()
	{
		return alloc_object<NSOCKET>();
	}

	template <class NSOCKET>
	[[nodiscard]] static std::enable_if_t<!std::is_base_of<net::io::Iconnect_requestable, NSOCKET>::value, object_ptr<TSOCKET>>
	_process_alloc_connectable()
	{
		return alloc_object<CONNECTABLE_SOCKET_TCP<NSOCKET>>();
	}
};


}