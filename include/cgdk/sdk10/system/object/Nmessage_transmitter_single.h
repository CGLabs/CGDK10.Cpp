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

 @class		Nmessage_transmitter_single
 
*/
//-----------------------------------------------------------------------------
class CGDK::Nmessage_transmitter_single : virtual public Imessage_transmitter
{
public:
			object_ptr<Imessageable> get_messageable() const noexcept { return m_pmessageable;}
private:
			lockable<object_ptr<Imessageable>>	m_pmessageable;
public:
	virtual	result_code			process_transmit_message(sMESSAGE& _msg) override;
	virtual	bool				process_attach(object_ptr<Imessageable>&& _pmessageable) override;
	virtual	bool				process_detach(Imessageable* _pmessageable) noexcept override;
	virtual int					process_reset_message_transmitter() noexcept override;
};
