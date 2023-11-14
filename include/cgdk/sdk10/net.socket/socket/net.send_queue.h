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
/**

 @class		net::concurrent_send_queue
 @brief		전송 순서를 보장하기 위한 queue이다.
 @todo		qeueu_send()로 전송할 내용을 먼저 queue에 넣은 후 
            send()함수를 호출해 queuing된 것들을 모두 전송한다.
			전송마다 sender를 각각 지정할 수 있다.
 @ref		
 @details	\n

 다중쓰레드에서 각각 전송할 경우 전송의 순서를 보장하기 힘든 경우 사용한다.
 다른 쓰레드에서 전송하더라도 queue에 저장된 순서로 전송되는 것이 보장된다.
 또 sender를 각 전송마다 설정하므로 다른 sender에 전송도 순서를 보장할 수 있다.
 */
//-----------------------------------------------------------------------------
class net::concurrent_send_queue :
	virtual public				Ireferenceable
{
public:
	struct SENDING
	{
		object_ptr<net::io::Isender> psender;
		shared_buffer	buffer;
	};

public:
			concurrent_send_queue();
	virtual	~concurrent_send_queue() noexcept;

			void				enqueue(const SENDING& _sending);
			void				enqueue(SENDING&& _sending);

			void				send() noexcept;

protected:
			lockable<>			m_cs_vector_send_queued;
			std::vector<SENDING> m_vector_send_queued;

			lockable<>			m_cs_vector_send_sending;
			std::vector<SENDING> m_vector_send_sending;
};

class net::local_send_queue
{
public:
	struct SENDING
	{
		object_ptr<net::io::Isender> psender;
		shared_buffer	buffer;
	};

	void				enqueue(SENDING&& _sending);
	void				send() noexcept;

private:
			std::vector<SENDING> m_vector_send_queued;
};


}