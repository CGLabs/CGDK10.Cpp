//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Network Base Classes                            *
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
//----------------------------------------------------------------------------
//  Disable Warnning
//
// 1) Warnning C4250 Disable
//    - C4250은 다중 상속의 virtual 상속된 interface에 대해서 어떤 것을 선택
//      했는지에 대해서 표시해주는 Warnning이다. 이 부분에 대한 표시가
//      필요 없으므로 이 부분은 Disable한다.
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 1. sMESSAGE- Network용
//-----------------------------------------------------------------------------
struct sMESSAGE_NETWORK : public sMESSAGE_BUFFER
{
public:
	sMESSAGE_NETWORK() noexcept : sMESSAGE_BUFFER(eMESSAGE::SYSTEM::NETWORK), address() {}
	template<class TSOURCE>
	sMESSAGE_NETWORK(uint32_t _message, TSOURCE _psource = nullptr) noexcept : sMESSAGE_BUFFER(_message, _psource), address() {}
	template<class TSOURCE>
	sMESSAGE_NETWORK(uint32_t _message, TSOURCE _psource, const net::sockaddr& _address) noexcept : sMESSAGE_BUFFER(_message, _psource), address(_address) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK(uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer) noexcept : sMESSAGE_BUFFER(_message, _psource, _buffer), address() {}
	template<class TSOURCE>
	sMESSAGE_NETWORK(uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_BUFFER(_message, _psource, _buffer), address(_address)	{}
	sMESSAGE_NETWORK(uint32_t _message, const shared_buffer& _buffer) noexcept : sMESSAGE_BUFFER(_message, _buffer), address() {}
	sMESSAGE_NETWORK(uint32_t _message, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_BUFFER(_message, _buffer), address(_address)	{}
	sMESSAGE_NETWORK(const sMESSAGE_BUFFER& _msg) noexcept : sMESSAGE_BUFFER(_msg), address()	{}
	sMESSAGE_NETWORK(const sMESSAGE_BUFFER& _msg, const net::sockaddr& _address) noexcept : sMESSAGE_BUFFER(_msg), address(_address) {}
	sMESSAGE_NETWORK(const shared_buffer& _buffer) noexcept : sMESSAGE_BUFFER(eMESSAGE::SYSTEM::NETWORK, _buffer), address() {}
	sMESSAGE_NETWORK(const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_BUFFER(eMESSAGE::SYSTEM::NETWORK, _buffer), address(_address)	{}

public:
	net::sockaddr	address;
};

inline bool is_network_message(uint32_t _message_type) noexcept
{
	return (_message_type & eMESSAGE::SYSTEM::NETWORK_MASK) == eMESSAGE::SYSTEM::NETWORK;
}


struct sMESSAGE_NETWORK_RESULT : public sMESSAGE_NETWORK
{
public:
	sMESSAGE_NETWORK_RESULT() noexcept : sMESSAGE_NETWORK(), result(eRESULT::NOT_DEFINED)	{}
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message) noexcept : sMESSAGE_NETWORK(_message), result(_result)	{}
	template<class TSOURCE>
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, TSOURCE _psource) noexcept : sMESSAGE_NETWORK(_message, _psource), result(_result)	{}
	template<class TSOURCE>
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, TSOURCE _psource, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _psource, _address), result(_result) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(_message, _psource, _buffer), result(_result) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _psource, _buffer, _address), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(_message, _buffer), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, uint32_t _message, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _buffer, _address), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, const sMESSAGE_BUFFER& _msg) noexcept : sMESSAGE_NETWORK(_msg), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, const sMESSAGE_BUFFER& _msg, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_msg, _address), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(eMESSAGE::SYSTEM::NETWORK, _buffer), result(_result) {}
	sMESSAGE_NETWORK_RESULT(result_code _result, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(eMESSAGE::SYSTEM::NETWORK, _buffer, _address), result(_result) {}

public:
		result_code	result;
};


#define	CGMESSAGE_TYPE_SUB_BUFFER_NETWORK				CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, static_cast<sMESSAGE_BUFFER&>(_msg).buf_message.front<uint32_t>(4) & eMESSAGE::SYSTEM::MASK)
#define	CGMESSAGE_TYPE_SUB_BUFFER_NETWORK_TYPE(type)	CGMESSAGE_TYPE_SUB(eMESSAGE::SYSTEM::NETWORK, static_cast<type>(static_cast<uint32_t>(((sMESSAGE_BUFFER&)_msg).buf_message.front<type>(4)) & eMESSAGE::SYSTEM::MASK))


//-----------------------------------------------------------------------------
// 2. sMESSAGE- JSON용
//-----------------------------------------------------------------------------
struct sMESSAGE_NETWORK_JSON : public sMESSAGE_NETWORK
{
public:
	sMESSAGE_NETWORK_JSON() noexcept : sMESSAGE_NETWORK() {}
	sMESSAGE_NETWORK_JSON(uint32_t _message) noexcept : sMESSAGE_NETWORK(_message) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_JSON(uint32_t _message, TSOURCE _psource) noexcept : sMESSAGE_NETWORK(_message, _psource) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_JSON(uint32_t _message, TSOURCE _psource, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _psource, _address) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_JSON(uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(_message, _psource, _buffer) {}
	template<class TSOURCE>
	sMESSAGE_NETWORK_JSON(uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _psource, _buffer, _address) {}
	sMESSAGE_NETWORK_JSON(uint32_t _message, const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(_message, _buffer) {}
	sMESSAGE_NETWORK_JSON(uint32_t _message, const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_message, _buffer, _address) {}
	sMESSAGE_NETWORK_JSON(const sMESSAGE_BUFFER& _msg) noexcept : sMESSAGE_NETWORK(_msg) {}
	sMESSAGE_NETWORK_JSON(const sMESSAGE_BUFFER& _msg, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(_msg, _address) {}
	sMESSAGE_NETWORK_JSON(const shared_buffer& _buffer) noexcept : sMESSAGE_NETWORK(eMESSAGE::SYSTEM::NETWORK, _buffer) {}
	sMESSAGE_NETWORK_JSON(const shared_buffer& _buffer, const net::sockaddr& _address) noexcept : sMESSAGE_NETWORK(eMESSAGE::SYSTEM::NETWORK, _buffer, _address) {}
};


//-----------------------------------------------------------------------------
// 3. etc
//-----------------------------------------------------------------------------
// message) 
struct sMESSAGE_RESPONSE : public sMESSAGE_NETWORK
{
public:
	sMESSAGE_RESPONSE( net::io::Isender* _psender, const shared_buffer& _buffer);

public:
			bool		response_message( const shared_buffer& _buffer);
protected:
	// 1) sender
			object_ptr<net::io::Isender>	psender;

	// 2) RequestID/ RequestSerial
			int					request_id;
			uint32_t			request_serial;
};

#define TRANSLATE_REQUEST_MESSAGE(msg, source)		if((msg.message==eMESSAGE::SYSTEM::eMESSAGE) && ((sMESSAGE_NETWORK&)msg).buf_message.front<uint32_t>(4)==eMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST) { msg=sMESSAGE_RESPONSE(source, msg);}


}