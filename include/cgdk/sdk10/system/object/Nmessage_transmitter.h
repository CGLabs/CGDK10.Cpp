//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

//-----------------------------------------------------------------------------
/**

 @class		Nmessage_transmitter


*/
//-----------------------------------------------------------------------------
class CGDK::Nmessage_transmitter : virtual public Imessage_transmitter
{
protected:
	virtual result_code			process_transmit_message(sMESSAGE& _msg) override;

	virtual bool				process_attach(object_ptr<Imessageable>&& _pmessageable) override { return this->process_attach_messageable_back(std::move(_pmessageable));}
	virtual bool				process_detach(Imessageable* _pmessageable) noexcept override;
	virtual int					process_reset_message_transmitter() noexcept override;

			bool				process_attach_messageable_front(object_ptr<Imessageable>&& _pmessageable);
			bool				process_attach_messageable_back(object_ptr<Imessageable>&& _pmessageable);
private:
			std::shared_mutex	m_lockable_array_messageable;
			static_vector<object_ptr<Imessageable>, MAX_MEDIATOR> m_array_messageable;
};
