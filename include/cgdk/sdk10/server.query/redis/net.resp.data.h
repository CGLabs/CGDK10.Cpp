//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Redis Classes                              *
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
// 1. RESP data
//-----------------------------------------------------------------------------
class resp_data
{
public:
			resp_data() noexcept : type(eRESP_DATA_TYPE::NONE_), str_value(), buf_store(), vector_child(), pos_processing(0) {}
			resp_data(eRESP_DATA_TYPE _type) noexcept : type(_type), str_value(), buf_store(), vector_child(), pos_processing(0) {}
			resp_data(resp_data&& _data) noexcept : type(_data.type), str_value(std::move(_data.str_value)), buf_store(std::move(_data.buf_store)), vector_child(std::move(_data.vector_child)), pos_processing(_data.pos_processing) { _data.type = eRESP_DATA_TYPE::NONE_; }
	virtual	~resp_data() noexcept {}

public:
	// 1) result Type
			eRESP_DATA_TYPE		type;

	// 2) result Value
			std::string_view	str_value;
			shared_buffer		buf_store;

	// 3) Child result (Array의 경우 Child result를 가진다.)
			std::vector<resp_data> vector_child;

	// 4) Operator overriding
	[[nodiscard]] resp_data&	operator[](int _index) noexcept	{ return vector_child.at(_index);}
	[[nodiscard]] auto			begin() noexcept { return vector_child.begin();}
	[[nodiscard]] auto			begin() const noexcept { return vector_child.begin();}
	[[nodiscard]] auto			end() noexcept { return vector_child.end();}
	[[nodiscard]] auto			end() const noexcept { return vector_child.end();}
			void				reset() noexcept { type = eRESP_DATA_TYPE::NONE_; str_value = std::string_view(); buf_store.clear(); vector_child.clear(); pos_processing = 0;}
	[[nodiscard]] std::size_t	size() const noexcept { return vector_child.size();}
	[[nodiscard]] std::size_t	size_bytes() const noexcept { auto bytes_size = buf_store.size(); for (auto& iter : vector_child) bytes_size += iter.size_bytes(); return bytes_size; }

	[[nodiscard]] bool			is_success() const noexcept { return type != eRESP_DATA_TYPE::ERROR_;}
	[[nodiscard]] bool			is_failed() const noexcept { return type == eRESP_DATA_TYPE::ERROR_;}
	[[nodiscard]] 				operator bool() const noexcept { return is_success();}

			resp_data& operator = (resp_data&& _rhs) noexcept { type = _rhs.type; str_value = std::move(_rhs.str_value); buf_store = std::move(_rhs.buf_store); vector_child = std::move(_rhs.vector_child); pos_processing = _rhs.pos_processing; _rhs.type = eRESP_DATA_TYPE::NONE_; _rhs.pos_processing = 0; return *this; }

	// 5) 진행상황 정보
			int64_t				pos_processing;
};


//-----------------------------------------------------------------------------
// 2. message structure
//-----------------------------------------------------------------------------
struct sMESSAGE_RESP
	: public sMESSAGE
{
public:
	sMESSAGE_RESP() noexcept : sMESSAGE(eMESSAGE::SYSTEM::NETWORK_RESP) {}
	sMESSAGE_RESP(resp_data&& _data) noexcept : sMESSAGE(eMESSAGE::SYSTEM::NETWORK_RESP), data(std::move(_data)) {}

public:
			resp_data			data;
};


}
