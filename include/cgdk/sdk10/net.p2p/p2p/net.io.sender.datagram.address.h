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
// net::io::sender::NStreamAddress
//
// 1. net::io::sender::CProxyStream��~
//    - sender�� Pointer�� ������ �ִ� sender�� send�� �� ��� Pointer�� ������
//      send�� ���� send�� �����Ѵ�. 
//
//
//-----------------------------------------------------------------------------
class net::io::sender::Ndatagram_address : 
// inherited classes)
	virtual public				net::io::Iaddress,
	virtual public				net::io::Isend_request,
	virtual public				net::io::Isender,
	virtual public				net::io::statistics::Nsocket
{
protected:
	// 1) process send
	virtual	bool				process_send( const shared_buffer& _buffer, uint64_t _option) override;
};

inline bool net::io::sender::Ndatagram_address::process_send( const shared_buffer& _buffer, uint64_t /*_option*/)
{
	// check) _buffer->data_�� nullptr�� �ƴѰ�?
	RETURN_IF(_buffer.data() == nullptr, false)

	// check) _buffer->size_�� 0�� �ƴѰ�?
	RETURN_IF(_buffer.size() == 0, false)

	// check) ���۰� Overflow�Ǿ��°�?
	CGASSERT_ERROR(_buffer._is_buffer_overflow() == false);

	// 1) peer Address�� ��´�.
	auto address_peer = remote_endpoint();

	// 2) �����Ѵ�.
	return request_send(&_buffer, 1, _buffer.get_source(), 1, address_peer);
}


}