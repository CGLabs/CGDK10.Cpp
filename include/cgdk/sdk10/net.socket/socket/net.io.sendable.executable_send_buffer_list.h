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
// net::io::sendable::executable_send_buffer_list
//
//-----------------------------------------------------------------------------
class net::io::sendable::executable_send_buffer_list :
	virtual public				Iexecutable,
	public						Npoolable<executable_send_buffer_list>,
	public						factory::_traits_system
{
public:
	virtual	~executable_send_buffer_list() noexcept;

public:
			void				reset() noexcept;
	virtual	void				on_final_release() noexcept override { this->reset(); }

	// define pool name)
	DEFAULT_FACTORY_NAME(net::io::sendable::executable_send_buffer_list)

private:
	virtual	intptr_t			process_execute( intptr_t _result, std::size_t _param) override;

public:
			object_ptr<net::io::Isendable> m_psendable;
			WSABUF				m_wsabuf{ 0, nullptr };
};


}
#endif