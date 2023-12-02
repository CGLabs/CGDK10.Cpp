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
// 1. message_remote_request��!
//    1) �������� ���ӵǾ� �ִ�(�Ϲ������� TCP) ��뿡�� ���� �޽����� ���� ȸ�� 
//       �޽����� ���� �� �ֵ��� �ϴ� �ý����̴�.
//    2) ������ �� ������ Lambda�Լ��� ������ �ָ� �ش� �޽����� ���� �亯 �޽�����
//       �����Ͽ��� �� �� Lambda �Լ��� ȣ���� �ش�.
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
	// 1) Request Object�� ��´�.
	object_ptr<CRequest> prequest = make_object<CRequest>();

	// 2) Response Function�� ������ ���´�.
	prequest->m_f_response = _functor_response;
	prequest->m_psource = _psource;

	// 3) message�� �����.
	auto temp_buffer = alloc_shared_buffer(16+_buffer.size_);

	temp_buffer.append<uint32_t>();
	temp_buffer.append<uint32_t>(eMESSAGE::NETWORK::SOCKET::REMOTE_REQUEST);
	temp_buffer.append<int>(m_request_id);
	temp_buffer.append<uint32_t>();
	temp_buffer.append(_buffer.size_, _buffer.data_);
	temp_buffer.front<uint32_t>() = temp_buffer.size_;

	// 4) �߰��Ѵ�.
	scoped_lock(this->m_map_request)
	{
		// -Request Serial�� ��´�.
		uint32_t request_serial = this->m_request_serial++;

		// - Request Serial�� ���� �ִ´�.
		temp_buffer.front<uint32_t>(8) = request_serial;

		// - �߰��Ѵ�.
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

	// 1) message�� Casting�Ѵ�.
	sMESSAGE_NETWORK& msg_network = (sMESSAGE_NETWORK&)_msg;

	// check) Response�� ���� message�� ó���Ѵ�.
	if(msg_network.buf_message.front<uint32_t>(4)==eMESSAGE::NETWORK::SOCKET::REMOTE_RESPONSE)
	{
		// 2) Resquestor�� ID�� Ȯ���Ѵ�.
		int request_id = msg_network.buf_message.front<int>(8);

		// check)
		CGASSERT_ERROR(request_id != 0)

		// check) Request ID�� �ٸ��� ������.
		RETURN_IF(request_id != m_request_id, eRESULT::BYPASS);

		// 3) Request ID�� ��´�.
		uint32_t request_serial = msg_network.buf_message.front<uint32_t>(12);

		// declare) 
		object_ptr<CRequest> prequest;

		scoped_lock(this->m_map_request)
		{
			// - Request�� ã�´�.
			auto iter = this->m_map_request.find(request_serial);

			// check) �ش� Request ��ü�� ã�� �������� ������.
			RETURN_IF(iter == this->m_map_request.end(), false);

			// check) Request�� ã�� �������� ������.
			RETURN_IF(iter->second.empty(), false);

			// - ���� �����Ѵ�.
			prequest = iter->second;
		}

		// 4) ������ ���� message head �κ��� 12Byte�� Extract�Ѵ�.
		msg_network.buf_message.extract<16>();

		// 5) �����Ѵ�.
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