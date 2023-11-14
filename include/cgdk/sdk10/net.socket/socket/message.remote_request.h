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
// message_remote_request
//
// 1. message_remote_request란!
//    1) 원격으로 접속되어 있는(일반적으로 TCP) 상대에게 보낸 메시지에 대한 회신 
//       메시지를 받을 수 있도록 하는 시스템이다.
//    2) 전송할 때 실행할 Lambda함수를 정의해 주면 해당 메시지에 대한 답변 메시지가
//       도착하였을 때 그 Lambda 함수를 호출해 준다.
//
//-----------------------------------------------------------------------------
template <class TSOURCE=Imessageable>
class message_remote_request : 
	virtual public				Imessageable
{
// definitions)
public:
			using TRESPONSE_FUNCTION = std::function<bool(TSOURCE * _psource, sMESSAGE & _msg)>;

public:
	virtual	shared_buffer		request_message(const shared_buffer& _buffer, const TRESPONSE_FUNCTION& _functor_response, TSOURCE* _psource);

protected:
	// 1) Process message
	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// definitions)
	class CRequest : public Npoolable<CRequest>
	{
	public:
		TRESPONSE_FUNCTION		m_f_response;
		object_ptr<TSOURCE>		m_psource;
	};

	// 2) Request ID
			int					m_request_id = 0;
			uint32_t			m_request_serial = 0;

	// 3) Request map
			lockable<std::map<uint32_t, object_ptr<CRequest>>>	m_map_request;
};

template <class TSOURCE>
inline shared_buffer message_remote_request<TSOURCE>::request_message(const shared_buffer& _buffer, const TRESPONSE_FUNCTION& _functor_response, TSOURCE* _psource)
{
	// 1) Request Object를 얻는다.
	object_ptr<CRequest> prequest = make_object<CRequest>();

	// 2) Response Function을 저장해 놓는다.
	prequest->m_f_response = _functor_response;
	prequest->m_psource = _psource;

	// 3) message를 만든다.
	auto temp_buffer = alloc_shared_buffer(16+_buffer.size_);

	temp_buffer.append<uint32_t>();
	temp_buffer.append<uint32_t>(eMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST);
	temp_buffer.append<int>(m_request_id);
	temp_buffer.append<uint32_t>();
	temp_buffer.append(_buffer.size_, _buffer.data_);
	temp_buffer.front<uint32_t>() = temp_buffer.size_;

	// 4) 추가한다.
	scoped_lock(this->m_map_request)
	{
		// -Request Serial을 얻는다.
		uint32_t request_serial = this->m_request_serial++;

		// - Request Serial을 적어 넣는다.
		temp_buffer.front<uint32_t>(8) = request_serial;

		// - 추가한다.
		this->m_map_request.emplace(request_serial, prequest);
	}

	// return) 
	return temp_buffer;
}

template <class TSOURCE>
result_code message_remote_request<TSOURCE>::process_message(sMESSAGE& _msg)
{
	// check) 
	RETURN_IF((_msg.message & eMESSAGE::SYSTEM::BUFFER)!=eMESSAGE::SYSTEM::BUFFER, eRESULT::BYPASS);

	// 1) message를 Casting한다.
	sMESSAGE_NETWORK& msg_network = (sMESSAGE_NETWORK&)_msg;

	// check) Response일 때만 message를 처리한다.
	if(msg_network.buf_message.front<uint32_t>(4)==eMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE)
	{
		// 2) Resquestor의 ID를 확인한다.
		int request_id = msg_network.buf_message.front<int>(8);

		// check)
		CGASSERT_ERROR(request_id != 0)

		// check) Request ID가 다르면 끝낸다.
		RETURN_IF(request_id != m_request_id, eRESULT::BYPASS);

		// 3) Request ID를 얻는다.
		uint32_t request_serial = msg_network.buf_message.front<uint32_t>(12);

		// declare) 
		object_ptr<CRequest> prequest;

		scoped_lock(this->m_map_request)
		{
			// - Request를 찾는다.
			auto iter = this->m_map_request.find(request_serial);

			// check) 해당 Request 객체를 찾지 못했으면 끝낸다.
			RETURN_IF(iter == this->m_map_request.end(), false);

			// check) Request를 찾지 못했으면 끝낸다.
			RETURN_IF(iter->second.empty(), false);

			// - 값을 복사한다.
			prequest = iter->second;
		}

		// 4) 전달을 위한 message head 부분의 12Byte를 Extract한다.
		msg_network.buf_message.extract<16>();

		// 5) 실행한다.
		prequest->m_f_response(prequest->m_psource, _msg);

		// return) 
		return eRESULT::DONE;
	}

	// return) 
	return eRESULT::BYPASS;
}

#define	NOTIFY_MESSAGE_REQUEST(request, msg)		\
{													\
	uint32_t result=request->dispatch_message(msg);	\
													\
	if(result!=0)									\
		return result;								\
}

#define	NOTIFY_MESSAGE_REQUEST_SOURCE(request, msg, source)	\
{													\
	msg.psource = source;							\
	uint32_t result=request->dispatch_message(msg);	\
													\
	if(result!=0)									\
		return result;								\
}


}