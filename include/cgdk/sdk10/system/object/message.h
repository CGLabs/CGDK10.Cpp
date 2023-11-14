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

namespace CGDK
{
//-----------------------------------------------------------------------------
/**
*  message struct
*/
//-----------------------------------------------------------------------------
struct sMESSAGE
{
public:
			constexpr sMESSAGE() noexcept : message(0), source() {}
			constexpr sMESSAGE(message_t _message) noexcept : message(_message), source() {}
			template <class TSOURCE, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>>>
			constexpr sMESSAGE(message_t _message, TSOURCE* _source) noexcept : message(_message), source(_source) {}
			template <class TSOURCE, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>>>
			constexpr sMESSAGE(message_t _message, const object_ptr<TSOURCE>& _source) noexcept : message(_message), source(_source) {}
			template <class TSOURCE, class = std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>>>
			constexpr sMESSAGE(message_t _message, object_ptr<TSOURCE>&& _source) noexcept : message(_message), source(std::move(_source)) {}

public:
	[[nodiscard]] constexpr any_ptr&	get_source() noexcept { return this->source; }
			template <class TSOURCE>
	[[nodiscard]] constexpr std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>, TSOURCE*>
								get_source() const { RETURN_IF(this->source.has_value() == false, nullptr); return this->source.get_ptr<TSOURCE>();	}
			void				swap_source(any_ptr& _source) noexcept { this->source.swap(_source); }
	[[nodiscard]] bool			has_source() const noexcept { return this->source.has_value(); }
			void				set_source(const any_ptr& _source) noexcept { this->source = _source; }
			void				set_source(any_ptr&& _source) noexcept { this->source = std::move(_source); }
			template <class TSOURCE>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>, void>
								set_source(TSOURCE* _source) noexcept { this->source = _source;}
			template <class TSOURCE>
			std::enable_if_t<std::is_base_of_v<Ireferenceable, TSOURCE>, void>
								set_source(object_ptr<TSOURCE>&& _source) noexcept { this->source = std::move(_source); }
			any_ptr				set_and_get_source(any_ptr _source) noexcept { _source.swap(this->source); return _source; }
public:
			message_t			message;

protected:
			any_ptr				source;
};


//-----------------------------------------------------------------------------
// 2. sMESSAGE- for window message
//-----------------------------------------------------------------------------
struct sMESSAGE_WINDOW : public sMESSAGE
{
public:
			sMESSAGE_WINDOW() noexcept : sMESSAGE(), wParam(), lParam() {}
			sMESSAGE_WINDOW(message_t _message, Ireferenceable* _psource, uint64_t _wParam = 0, uint64_t _lParam = 0) noexcept : sMESSAGE(_message, _psource), wParam(_wParam), lParam(_lParam) {}
public:
			uint64_t				wParam;
			uint64_t				lParam;
};


//-----------------------------------------------------------------------------
// 4. sMESSAGE - for command
//-----------------------------------------------------------------------------
class sMESSAGE_COMMAND : public sMESSAGE
{
public:
			sMESSAGE_COMMAND() noexcept :command() {}
			sMESSAGE_COMMAND(message_t _message, uint32_t _command) noexcept : sMESSAGE(_message), command(_command) {}

public:
			uint32_t			command;
};

struct sMESSAGE_NOTIFY : public sMESSAGE_COMMAND
{
public:
			sMESSAGE_NOTIFY() noexcept : sMESSAGE_COMMAND(), wParam(), lParam() {}
			sMESSAGE_NOTIFY(message_t _message, uint32_t _command, uintptr_t _wParam = 0, uintptr_t _lPara = 0) noexcept : sMESSAGE_COMMAND(_message, _command), wParam(_wParam), lParam(_lPara) {}
public:
			uintptr_t			wParam;
			uintptr_t			lParam;
};


//-----------------------------------------------------------------------------
// 5. sMESSAGE- with DATA
//-----------------------------------------------------------------------------
template <class TDATA>
struct sMESSAGE_DATA : public sMESSAGE
{
public:
			sMESSAGE_DATA() noexcept : data() {}
			sMESSAGE_DATA(message_t _message, const TDATA& _data) noexcept : sMESSAGE(_message), data(_data) {}
public:
			TDATA				data;
};


}