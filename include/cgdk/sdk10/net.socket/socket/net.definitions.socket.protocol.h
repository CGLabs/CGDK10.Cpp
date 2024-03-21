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
// ----------------------------------------------------------------------------
//
// message definitions
//
// ----------------------------------------------------------------------------
namespace eMESSAGE
{
	namespace NETWORK
	{
		namespace SOCKET
		{
			const message_t	CONNECTIVE_LIST				 = BASE +  12;
			const message_t	CONNECTIVE_LIST_UPDATE		 = BASE +  13;
			const message_t	CONNECTIVE_REGISTER			 = BASE +  14;
			const message_t	CONNECTIVE_UNREGISTER		 = BASE +  15;
			const message_t	CONNECTIVE_UPDATE			 = BASE +  16;
			const message_t	CONNECTIVE_ENABLE			 = BASE +  17;
			const message_t	CONNECTIVE_DISABLE			 = BASE +  18;

			const message_t	BINDER_LIST					 = BASE +  19;
			const message_t	BINDER_LIST_UPDATE			 = BASE +  20;
			const message_t	BINDER_REGISTER				 = BASE +  21;
			const message_t	BINDER_UNREGISTER			 = BASE +  22;
			const message_t	BINDER_UPDATE				 = BASE +  23;

			const message_t	REMOTE_REQUEST				 = BASE +  24;
			const message_t	REMOTE_RESPONSE				 = BASE +  25;

			const message_t	ON_CONNECT					 = BASE +  32;
			const message_t	ON_FAILCONNECT				 = BASE +  33;
			const message_t	ON_DISCONNECT				 = BASE +  34;

			const message_t	RESTORE						 = BASE +  64;
			const message_t	REQUEST_IO_RESTORE			 = BASE +  65;
			const message_t	RESPONSE_IO_RESTORE			 = BASE +  66;
			const message_t	COMPLETE_IO_RESTORE			 = BASE +  67;
			const message_t	REQUEST_RESET_IO_RESTORE	 = BASE +  68;
			const message_t	SEND_MESSAGE_ACK_REQUIRED	 = BASE +  69;
		}

		namespace SECURITY
		{
			const message_t	REQUEST_CERTIFICATION		 = BASE |   1;
			const message_t	ACCEPT_CERTIFICATION		 = BASE |   2;
			const message_t	REJECT_CERTIFICATION		 = BASE |   3;
			const message_t	SEND_DECODER_INFO			 = BASE |   4;
		}
	}
}

#define	CGACCEPTOR_SET_CONNECTIVE			11
#define	CGACCEPTOR_OPEN_CONNECTIVE			12
#define	CGACCEPTOR_SET_CONNECTABLE			13
#define	CGACCEPTOR_OPEN_CONNECTABLE			14
#define	CGACCEPTOR_READY					15
#define	CGACCEPTOR_CLOSE					16
#define	CGACCEPTOR_START					17
#define	CGACCEPTOR_STOP						18
#define	CGBINDER_SET						19
#define	CGBINDER_OPEN						20

#define AF_INET_PREFER	(AF_MAX+2)
#define AF_INET6_PREFER	(AF_MAX+3)


//-----------------------------------------------------------------------------
//
// definition_message_header
//
//
//-----------------------------------------------------------------------------
struct sMESSAGE_BUNDLE
{
	shared_buffer buf_message;
	std::size_t count_message = 1;
};


//-----------------------------------------------------------------------------
//
// definition_message_header
//
//
//-----------------------------------------------------------------------------
struct message_headerable
{
	static void			_set_message_size(buffer& _buffer) noexcept { _buffer.front<uint32_t>() = _buffer.size<int32_t>(); }
	static std::size_t	_get_message_size(const buffer_view& _buffer) noexcept { return static_cast<std::size_t>(*_buffer.data<int32_t>()); }
	static bool			_validate_message(const std::vector<shared_buffer>& _vector_buffer) noexcept
	{
		// declare)
		int32_t	total_bytes = 0;

		// 1) total_bytes
		for (auto& iter: _vector_buffer)
			total_bytes += iter.size<int32_t>();

		for(auto iter= _vector_buffer.begin(), iter_end = _vector_buffer.end(); iter != iter_end;)
		{
			// 2) Buffer를 설정한다.
			buffer_view	buf_temp = *iter;

			while (total_bytes != 0)
			{
				// Check) Message의 크기가 실제 버퍼의 크기보다 작으면 안됀다.
				CGASSERT_ERROR(iter != iter_end)
				if (iter == iter_end) return false;

				// - message_size를 구한다.
				auto message_size = *buf_temp.data<int32_t>();

				// check) message_size가 0byte면 안됀다.
				CGASSERT_ERROR(message_size != 0);
				if (message_size == 0) return false;

				// check) message_size가 실제 버퍼의 크기보다 작으면 안됀다.
				CGASSERT_ERROR(message_size <= total_bytes);
				if (message_size > total_bytes) return false;

				// - next message
				total_bytes -= message_size;

				// Check) total_bytes보다 더 긴 메시지를 요구할 경우 바로 false를 리턴한다.
				CGASSERT_ERROR(total_bytes >= 0);
				if (total_bytes < 0) return false;

				while (message_size >= buf_temp.size<int32_t>())
				{
					message_size -= buf_temp.size<int32_t>();

					++iter;

					if(message_size == 0) break;

					if (iter == iter_end)
						return false;

					buf_temp = *iter;
				}

				buf_temp.add_data(message_size);
				buf_temp.sub_size(message_size);
			}
		}

		return	true;
	}
	static bool			_validate_message(const buffer_view& _buffer) noexcept
	{
		// 1) message 크기를 확인한다.
		const char* data_ = _buffer.data();
		std::size_t size_ = _buffer.size();

		while(size_ != 0)
		{
			// check) message의 크기가 0Byte면 안됀다.
			CGDK_ASSERT(size_ >= sizeof(uint32_t));
			if (size_ < sizeof(uint32_t)) return false;

			auto message_size = *reinterpret_cast<const uint32_t*>(data_);

			// check) message의 크기가 0Byte면 안됀다.
			CGDK_ASSERT(message_size != 0);
			if(message_size == 0) return false;

			// check) message의 크기가 실제 버퍼의 크기보다 작으면 안됀다.
			CGDK_ASSERT(message_size <= size_);
			if(message_size > size_) return false;

			// - 다음 message
			data_ += message_size;
			size_ -= message_size;
		}

		// return) 성공~
		return true;
	}
};

template <class T = int32_t, std::size_t N = 0>
struct message_headable_primitive : public message_headerable
{
	static void			_set_message_size(buffer& _buffer) noexcept { _buffer.front<T>(N) = _buffer.size<T>(); }
	static std::size_t	_get_message_size(const buffer_view& _buffer) noexcept { return static_cast<std::size_t>(*_buffer.data<T>(N)); }
	static bool			_validate_message(const std::vector<shared_buffer>& _vector_buffer) noexcept
	{
		// declare)
		int32_t total_bytes = 0;

		// 1) total_bytes
		for (auto& iter: _vector_buffer)
			total_bytes += (int32_t)iter.size<T>();

		for(auto iter= _vector_buffer.begin(), iter_end = _vector_buffer.end(); iter != iter_end;)
		{
			// 2) Buffer를 설정한다.
			buffer_view	buf_temp = *iter;

			while (total_bytes != 0)
			{
				// Check) Message의 크기가 실제 버퍼의 크기보다 작으면 안됀다.
				CGASSERT_ERROR(iter != iter_end)
				if (iter == iter_end) return false;

				// - message_size를 구한다.
				int32_t message_size = (int32_t)*buf_temp.data<T>(N);
					
				// check) message_size가 0byte면 안됀다.
				CGASSERT_ERROR(message_size != 0);
				if (message_size == 0) return false;

				// check) message_size가 실제 버퍼의 크기보다 작으면 안됀다.
				CGASSERT_ERROR(message_size <= total_bytes);
				if (message_size > total_bytes) return false;

				// - next message
				total_bytes -= message_size;

				// Check) total_bytes보다 더 긴 메시지를 요구할 경우 바로 false를 리턴한다.
				CGASSERT_ERROR(total_bytes >= 0);
				if (total_bytes < 0) return false;

				while (message_size >= (int32_t)buf_temp.size<T>())
				{
					message_size -= buf_temp.size<int32_t>();

					++iter;

					if(message_size == 0) break;

					if (iter == iter_end)
						return false;

					buf_temp = *iter;
				}

				buf_temp.add_data(message_size);
				buf_temp.sub_size(message_size);
			}
		}

		return	true;
	}
	static bool			_validate_message(const buffer_view& _buffer) noexcept
	{
		// 1) message 크기를 확인한다.
		const char* data_ = _buffer.data();
		int64_t size_ = _buffer.size<int64_t>();

		while(size_ != 0)
		{
			// check) message의 크기가 0Byte면 안됀다.
			CGDK_ASSERT(size_ >= static_cast<int64_t>(sizeof(T) + N));
			if (size_ < static_cast<int64_t>(sizeof(T) + N)) return false;

			int64_t message_size = *reinterpret_cast<const T*>(data_ + N);

			// check) message의 크기가 0Byte면 안됀다.
			CGDK_ASSERT(message_size !=0);
			if(message_size ==0) return false;

			// check) message의 크기가 실제 버퍼의 크기보다 작으면 안됀다.
			CGDK_ASSERT(message_size <= size_);
			if(message_size > size_) return false;

			// - 다음 message
			data_ += message_size;
			size_ -= message_size;
		}

		// return) 성공~
		return true;
	}
};

template<class T = uint32_t, std::size_t N = 0, class E = void>
struct definition_message_header : public message_headable_primitive<T, N>
{
};

template<class T, std::size_t N>
struct definition_message_header<T, N, std::enable_if_t<std::is_base_of_v<message_headerable, T>>>
{
	static void			_set_message_size(buffer& _buffer) noexcept { T::_set_message_size(_buffer); }
	static std::size_t	_get_message_size(const buffer_view& _buffer) noexcept { return T::_get_message_size(_buffer); }
	static bool			_validate_message(const buffer_view& _buffer) noexcept { return T::_validate_message(_buffer); }
	static bool			_validate_message(const std::vector<shared_buffer>& _vector_buffer) noexcept { return T::_validate_message(_vector_buffer); }
};

template <class T, std::enable_if_t<std::is_base_of_v<message_headerable, T>>>
constexpr void _do_post_make_shared_buffer(CGDK::_shared_buffer<buffer>& _source)
{
	T::_set_message_size(_source);
}


}