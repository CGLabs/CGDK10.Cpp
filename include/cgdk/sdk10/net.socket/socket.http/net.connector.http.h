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
// net::connector<TSOCKET> - for http socket
//
// ----------------------------------------------------------------------------
// definitioins)
	template <class TSOCKET> class CONNECTABLE_SOCKET_HTTP : public TSOCKET, public net::io::connect_requestable::Nhttp { public: virtual ~CONNECTABLE_SOCKET_HTTP() noexcept {} };
namespace factory { template<class T> class _factory_name<CONNECTABLE_SOCKET_HTTP<T>> { public: static std::string_view get_default_name() noexcept { return std::string_view(typeid(T).name()); } };}

template <class TSOCKET>
class net::connector<TSOCKET, typename std::enable_if<std::is_base_of<net::io::Nhttp_client, TSOCKET>::value>::type> :
// inherited classes) 
	public						net::io::connective::connector::Ntcp,
	public						net::io::connectable_manager::list<TSOCKET>
{
// constructor/destructor) 
public:
			connector()
			{
				// declare) 
				char temp[MAX_NAME_LENGTH];

				// - 기본 acceptor의 Name을 설정한다.
				__sprintf(temp, "connector<%s>", typeid(TSOCKET).name());

				// - 기본 이름을 설정한다.
				set_name(temp);
			}
			connector(std::string_view _name) : net::io::connective::connector::Ntcp(_name)
			{
				// 1) Name이 없을 경우 connector의 Name을 설정한다.
				if (_name.empty())
				{
					// declare) 
					char temp[MAX_NAME_LENGTH];

					// - 기본 acceptor의 Name을 설정한다.
					__sprintf(temp, "connector<%s>", typeid(TSOCKET).name());

					// - 기본 이름을 설정한다.
					set_name(temp);
				}
			}
	virtual	~connector() noexcept
			{
			}

public:
			bool				request(Ihttp_request* _prequest)
								{
									// check) _prequest이 nullptr이면 안됀다.
									CGASSERT_ERROR(_prequest != nullptr);

									// check) _prequest가 nullptr이면 그냥 끝낸다.
									RETURN_IF(_prequest == nullptr, false);

									// 1) socket을 DynamicCast
									auto pconnectable_http = dynamic_pointer_cast<net::io::connect_requestable::Nhttp>(this->alloc_connectable());

									// check) psocket이 nullptr일리는 절대 없어야 한다.
									CGASSERT_ERROR(pconnectable_http.exist());

									// declare) 
									bool result = false;

									try
									{
										// check) 
										THROW_IF(pconnectable_http.empty(), throwable::failure(eRESULT::NOT_READY));

										// 2) prepare
										pconnectable_http->prepare_socket(_prequest->m_address_host.data().family());

										// check) _pconnectable의 reference count를 1여야지만 한다.
										CGASSERT_ERROR(pconnectable_http->reference_count() == 1);

										// 2) HTTP Request 객체를 Set한다.
										pconnectable_http->set_request(_prequest);

										// 3) connect를 요청한다.
										result = pconnectable_http->net::io::Iconnect_requestable::process_request_connecting(_prequest->m_address_host);

										// check) connect 요청에 실패했을 경우 Exception을 던진다.
										THROW_IF(result == false, throwable::failure(eRESULT::FAIL_TO_CONNECT))
									}
									catch(...)
									{
										// - HTTP Request 객체를 Set한다.
										pconnectable_http->reset_request();
									}

									// return)
									return result;
								}

// implementations) 
protected:
	// Process Functions)
	virtual	object_ptr<net::io::Iconnectable> process_alloc_connectable() override
	{
		return _process_alloc_connectable<TSOCKET>();
	}
	
	// - Process
	template <class NSOCKET>
	static	typename std::enable_if<std::is_base_of<net::io::Iconnect_requestable, NSOCKET>::value, object_ptr<NSOCKET>>::type
	_process_alloc_connectable()
	{
		return alloc_object<NSOCKET>();
	}

	template <class NSOCKET>
	static	typename std::enable_if<!std::is_base_of<net::io::Iconnect_requestable, NSOCKET>::value, object_ptr<NSOCKET>>::type
	_process_alloc_connectable()
	{
		return alloc_object<CONNECTABLE_SOCKET_HTTP<NSOCKET>>();
	}
};


}