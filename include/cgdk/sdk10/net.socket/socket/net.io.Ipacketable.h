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
/*!
* @class Ipacketable
*
* @ingroup net::io::packetable
*
* @brief 데이터를 메시지로 잘라주는 역할을 하는 클래스
*
*  process_packet으로 넘겨져온 데이터를 메시지로 구분해 전달해주는 역할을 하는 클래스의
*  인터페이스(Interface) 객체이다.
*
*/
//-----------------------------------------------------------------------------
class net::io::Ipacketable :
	virtual public				Ireferenceable
{
public:
			void				enable_message_histroy (bool _enable=true) noexcept { this->m_enable_history=_enable;}
			void				disable_message_histroy () noexcept { this->enable_message_histroy (false);}
	[[nodiscard]] bool			Is_enable_message_histroy () const noexcept { return this->m_enable_history;}

public:
	// 1) 데이터를 처리하는 함수.
	virtual	std::size_t			process_packet(shared_buffer& _buffer, const net::sockaddr& _address) PURE;

	// 2) Ipacketable을 reset하는 함수.
	virtual	void				process_reset_packetable() noexcept PURE;

protected:
	// debug) ...
			void				push_message_to_history(shared_buffer& _message)
			{
				// check)
				RETURN_IF(this->m_enable_history == false);

				scoped_lock(this->m_queue_history)
				{
					// check) 최대 History 갯수를 넘길 경우 제일 앞에 것을 빼낸다.
					if (this->m_queue_history.size() > 16)
					{
						this->m_queue_history.pop_front();
					}

					// 1) history에 추가한다.
					this->m_queue_history.push_back(_message);
				}
			}
			void				reset_message_history() noexcept
			{
				scoped_lock(this->m_queue_history)
				{
					this->m_queue_history.clear();
				}
			}

	// debug) History of messages
			bool				m_enable_history = false;
			lockable<circular_list<shared_buffer>> m_queue_history;
};


}