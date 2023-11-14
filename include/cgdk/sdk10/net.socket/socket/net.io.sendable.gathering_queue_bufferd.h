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
#if defined(_WINSOCK2API_)

namespace CGDK
{
	//-----------------------------------------------------------------------------
	//
	// net::io::sendable::executable_send_buffer
	//
	//-----------------------------------------------------------------------------
	struct net::io::sendable::QUEUE_SEND_bufferd
	{
		struct NODE
		{
			object_ptr<Ireferenceable> powner;
		};

		std::vector<WSABUF> array_buffer;
		std::vector<NODE> array_node;

		std::size_t		bytes_data = 0;
		std::size_t		count_message = 0;
		std::size_t		bytes_remained = 0;

		void clear() noexcept;
		void reset_and_swap(QUEUE_SEND_bufferd&& _move) noexcept;
		void push_back(const buffer_view _buffer, object_ptr<Ireferenceable>&& _owner, std::size_t _count_messages);
	};
}
#endif