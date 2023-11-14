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
 @brief		���� ������ �����ϱ� ���� queue�̴�.
 @todo		qeueu_send()�� ������ ������ ���� queue�� ���� �� 
            send()�Լ��� ȣ���� queuing�� �͵��� ��� �����Ѵ�.
			���۸��� sender�� ���� ������ �� �ִ�.
 @ref		
 @details	\n

 ���߾����忡�� ���� ������ ��� ������ ������ �����ϱ� ���� ��� ����Ѵ�.
 �ٸ� �����忡�� �����ϴ��� queue�� ����� ������ ���۵Ǵ� ���� ����ȴ�.
 �� sender�� �� ���۸��� �����ϹǷ� �ٸ� sender�� ���۵� ������ ������ �� �ִ�.
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