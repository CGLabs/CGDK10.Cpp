//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
// ----------------------------------------------------------------------------
//
// CGDK::update::receiver
//
//
// ----------------------------------------------------------------------------
class CGDK::update::receiver : public Nreceiver
{
public:
			void				set_transmitter(Ireferenceable* _psource);
			void				reset_transmitter(Ireferenceable* _psource) noexcept;
private:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override { return m_psender->process_send(std::move(_buffer), _count_message, _option); }

			object_ptr<net::io::Isender> m_psender;
			object_ptr<Imessage_transmitter> m_pmessage_transmitter;
};