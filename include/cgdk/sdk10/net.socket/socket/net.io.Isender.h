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
// net::io::Isender
//
//-----------------------------------------------------------------------------
class net::io::Isender : virtual public Ireferenceable
{
public:
			bool				send( const shared_buffer& _buffer, uint64_t _option = 0)
			{
			#if defined(_VALIDATE_SEND_MESSAGE)
				this->__is_message_valid(_buffer);
			#endif
				return process_send(shared_buffer(_buffer), 1, _option);
			}
			bool				send( shared_buffer&& _buffer, uint64_t _option = 0)
			{
			#if defined(_VALIDATE_SEND_MESSAGE)
				this->__is_message_valid(_buffer);
			#endif
				return process_send(std::move(_buffer), 1, _option);
			}

	template <std::size_t ICOUNT>
			bool				send( const shared_buffer (&_array_buffer)[ICOUNT], uint64_t _option = 0);
	template <std::size_t ICOUNT>
			bool				send( shared_buffer (&&_array_buffer)[ICOUNT], uint64_t _option = 0);
	template <class T>
	typename std::enable_if<is_send_container_buffer<T>::value, bool>::type
								send( const T& _list, uint64_t _option = 0);

			bool				send(const sMESSAGE_BUNDLE& _message_bundle, uint64_t _option = 0) { return process_send(shared_buffer(_message_bundle.buf_message), _message_bundle.count_message, _option); }
			bool				send(sMESSAGE_BUNDLE&& _message_bundle, uint64_t _option = 0) { return process_send(std::move(_message_bundle.buf_message), _message_bundle.count_message, _option); }
	template <class T>
			Isender&			operator<<(const T& _rhs) { send(_rhs); return *this;}

public:
	virtual	bool				process_send( shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) PURE;

#if defined(_VALIDATE_SEND_MESSAGE)
	virtual void				__is_message_valid(const shared_buffer& /*_buffer*/) {}
	virtual void				__is_message_valid(const std::vector<shared_buffer>& /*_vector_buffer*/) {}
#endif
};

template <std::size_t ICOUNT>
bool net::io::Isender::send( const shared_buffer(&_array_buffer)[ICOUNT], uint64_t _option)
{
#if defined(_VALIDATE_SEND_MESSAGE)
	{
		std::vector<shared_buffer> vector_temp;
		vector_temp.reserve(ICOUNT);
		const shared_buffer* iter = _array_buffer;
		const shared_buffer* iter_end = _array_buffer + ICOUNT;
		for (; iter != iter_end; ++iter) vector_temp.push_back(*iter);
		this->__is_message_valid(vector_temp);
	}
#endif

	for (std::size_t i = 0; i < ICOUNT; ++i)
	{
		send(_array_buffer[i], _option);
	}

	return true;
}

template <std::size_t ICOUNT>
bool net::io::Isender::send(shared_buffer(&&_array_buffer)[ICOUNT], uint64_t _option)
{
#if defined(_VALIDATE_SEND_MESSAGE)
	{
		std::vector<shared_buffer> vector_temp;
		vector_temp.reserve(ICOUNT);
		const shared_buffer* iter = _array_buffer;
		const shared_buffer* iter_end = _array_buffer + ICOUNT;
		for (; iter != iter_end; ++iter) vector_temp.push_back(*iter);
		this->__is_message_valid(vector_temp);
}
#endif

	for (std::size_t i = 0; i < ICOUNT; ++i)
	{
		send(std::move(_array_buffer[i]), _option);
	}

	return true;
}

template <class T>
typename std::enable_if<is_send_container_buffer<T>::value, bool>::type
net::io::Isender::send( const T& _list, uint64_t _option)
{
#if defined(_VALIDATE_SEND_MESSAGE)
	{
		std::vector<shared_buffer> vector_temp;
		vector_temp.reserve(_list.size());
		for (const shared_buffer& iter : _list) vector_temp.push_back(iter);
		this->__is_message_valid(vector_temp);
	}
#endif

	for (const auto& iter : _list)
	{
		std::vector<shared_buffer> vector_temp;
		send(iter, _option);
	}

	return true;
}

class net::io::Isender_mass : virtual public Ireferenceable
{
public:
	virtual	bool				send_mass( const buffer_view* _buffer, int _count_buffer, Ireferenceable* _powner) PURE;
};

class net::io::Isender_datagram : virtual public Ireferenceable
{
public:
			bool				send_to( const shared_buffer& _buffer, const net::sockaddr& _address, uint64_t _option = 0) { return process_send(shared_buffer(_buffer), 1, _address, _option);}
			bool				send_to( shared_buffer&& _buffer, const net::sockaddr& _address, uint64_t _option = 0) { return process_send(std::move(_buffer), 1, _address, _option); }
			bool				send_to( const shared_buffer& _buffer, net::sockaddr&& _address, uint64_t _option = 0) { return process_send(shared_buffer(_buffer), 1, _address, _option); }
			bool				send_to( shared_buffer&& _buffer, net::sockaddr&& _address, uint64_t _option = 0) { return process_send(std::move(_buffer), 1, _address, _option); }

	template <std::size_t ICOUNT>
			bool				send_to( const shared_buffer (&_array_buffer)[ICOUNT], const net::sockaddr& _address, uint64_t _option = 0);
	template <std::size_t ICOUNT>
			bool				send_to( const shared_buffer (&_array_buffer)[ICOUNT], net::sockaddr&& _address, uint64_t _option = 0) { return send_to(_array_buffer, _address, _option); }
	template <class T, std::size_t ICOUNT>
	typename std::enable_if<!std::is_base_of_v<shared_buffer, T>, bool>::type
								send_to( const T(&_array)[ICOUNT], const net::sockaddr& _address, uint64_t _option = 0);
	template <class T>
	typename std::enable_if<is_send_container_buffer<T>::value, bool>::type
								send_to( const T& _list, const net::sockaddr& _address, uint64_t _option = 0);

public:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, const net::sockaddr& _address, uint64_t _option) PURE;
};

template <std::size_t ICOUNT>
bool net::io::Isender_datagram::send_to( const shared_buffer (&_array_buffer)[ICOUNT], const net::sockaddr& _address, uint64_t _option)
{
	// 1) get size
	auto size_buffer = get_size_of(_array_buffer);

	// check) 
	CGASSERT_ERROR(size_buffer != 0);

	// check) 
	RETURN_IF(size_buffer == 0, false);

	// 2) alloc shared_buffer
	auto buffer_temp = alloc_shared_buffer(size_buffer);

	// 3) append shared_buffer
	for (std::size_t i = 0; i < ICOUNT; ++i)
	{
		// 2) ºÙÀÎ´Ù.
		buffer_temp += _array_buffer[i];
	}

	// 4) send
	return process_send(std::move(buffer_temp), 1, _address, _option);
}

template <class T>
typename std::enable_if<is_send_container_buffer<T>::value, bool>::type
net::io::Isender_datagram::send_to( const T& _list_buffer, const net::sockaddr& _address, uint64_t _option)
{
	// 1) get size
	auto size_buffer = get_size_of(_list_buffer);

	// check) 
	CGASSERT_ERROR(size_buffer != 0);

	// check) 
	RETURN_IF(size_buffer == 0, false);

	// 2) alloc shared_buffer
	auto buffer_temp = alloc_shared_buffer(size_buffer);

	// 3) append shared_buffer
	for (const auto& iter : _list_buffer)
	{
		// 2) append
		buffer_temp += iter;
	}

	// 4) send
	return process_send(std::move(buffer_temp), 1, _address, _option);
}

class net::io::Isender_peer : virtual public Ireferenceable
{
public:
	virtual	bool				send_to(int _peer, const shared_buffer& _buffer, uint64_t _option = 0) PURE;
	virtual	bool				send_to(int _peer, shared_buffer&& _buffer, uint64_t _option = 0) PURE;
};

class net::io::Isender_closser : virtual public Ireferenceable
{
public:
	virtual	void				process_close_sender() PURE;
};


}