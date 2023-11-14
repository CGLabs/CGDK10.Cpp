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

 @class		Nmessage_transmitter_static
 @brief		
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class CGDK::Nmessage_transmitter_static : virtual public Imessage_transmitter
{
public:
	[[nodiscard]] static object_ptr<Imessageable> get_messageable() noexcept { return get_messageable_static();}

	static	object_ptr<Imessageable> reset_dispatchable_static() noexcept;
	static	bool				register_messageable_static(const object_ptr<Imessageable>& _pmessageable) { return register_messageable_static(object_ptr<Imessageable>(_pmessageable));}
	static	bool				register_messageable_static(object_ptr<Imessageable>&& _pmessageable);
	static	int					unregister_messageable_static(Imessageable* _pmessageable=nullptr) noexcept;

private:
	[[nodiscard]] static lockable<object_ptr<Imessageable>>& get_messageable_static() noexcept { static lockable<object_ptr<Imessageable>> pmessageable; return pmessageable;}

protected:
	virtual	result_code			process_transmit_message(sMESSAGE& _msg) override;
	virtual	bool				process_attach(object_ptr<Imessageable>&& _pmessageable) override;
	virtual	bool				process_detach(Imessageable* _pmessageable=nullptr) noexcept override;
	virtual	int					process_reset_message_transmitter() noexcept override;
};
