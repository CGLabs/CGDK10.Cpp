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
// net::io::sender::Nstream_header
// 
//-----------------------------------------------------------------------------
template <class HEADER_T = uint32_t>
class net::io::sender::Nstream_header : 
	public						net::io::sender::Nstream,
	virtual public				net::io::Isender
{
#if defined(_VALIDATE_SEND_MESSAGE)
public:
			void				enable_validate_send_message(bool _enable = true) noexcept { this->m_check_validate_send_message = _enable;}
			void				disable_validate_send_message() noexcept { this->enable_validate_send_message(false); }
	[[nodiscard]] bool			is_validate_send_message() const noexcept { return this->m_check_validate_send_message; }
private:
			bool				m_check_validate_send_message = true;

	virtual void				__is_message_valid(const shared_buffer& _buffer) override { RETURN_IF(is_validate_send_message() == false); definition_message_header<HEADER_T>::_validate_message(_buffer); }
	virtual void				__is_message_valid(const std::vector<shared_buffer>& _vector_buffer) override { RETURN_IF(is_validate_send_message() == false); definition_message_header<HEADER_T>::_validate_message(_vector_buffer); }
#else
			constexpr void		enable_validate_send_message(bool /*_enable*/ = true) noexcept {}
			constexpr void		disable_validate_send_message() noexcept {}
	[[nodiscard]] constexpr bool is_validate_send_message() const noexcept { return false; }
#endif







};

}