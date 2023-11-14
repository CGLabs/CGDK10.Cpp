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
// net::io::sender::Ndatagram_proxy
//
// 1. net::io::sender::CDatagramProxy은~
//    - sender의 Pointer를 가지고 있는 sender로 send를 할 경우 Pointer로 지정된
//      send를 통해 send를 수행한다. 
//
//
//-----------------------------------------------------------------------------
class net::io::sender::Ndatagram_proxy : 
// inherited classes)
	virtual public				net::io::Isender_datagram,
	virtual public				net::io::statistics::Nsocket
{
// constructor/destructor)
protected:
			Ndatagram_proxy( Isender_datagram* _psender = nullptr) noexcept : m_psender(_psender) {}
	virtual	~Ndatagram_proxy() noexcept {}

// publics)
public:
	// 1) 
			void				set_sender( Isender_datagram* _psender) noexcept { m_psender = _psender; }
			auto				get_sender() const noexcept { return m_psender;}

// implementation)
private:
			object_ptr<Isender_datagram> m_psender;

// framework)
protected:
	// 1) send할 때 부르는 함수.
	virtual	bool				process_send(const shared_buffer& _buffer, const net::sockaddr& _address, uint64_t _option = 0) override;
};

inline bool net::io::sender::Ndatagram_proxy::process_send(const shared_buffer& _buffer, const net::sockaddr& _address, uint64_t _option)
{
	// check) _array_buffer->data_가 nullptr이 아닌가?
	CGASSERT(_buffer.data() != nullptr, false)

	// check) _array_buffer->size_이 0이 아닌가?
	CGASSERT(_buffer.size() != 0, false)

	// check) sender가 nullptr이면 안됀다.
	CGASSERT(m_psender.exist(), false);

	// 1) send to
	return m_psender->send_to(_buffer, _address, _option);
}


}