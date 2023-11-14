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

@class		Nobject_enable


*/
//-----------------------------------------------------------------------------
class CGDK::object::Nenable : virtual public object::Ienable
{
public:
			Nenable() noexcept : m_is_state(false) {}
			Nenable(bool _is_state) noexcept : m_is_state(_is_state) {}
	virtual	~Nenable() noexcept {}

protected:
	virtual	void				on_enable(bool /*_is_state*/) {}

protected:
	virtual	bool				process_set_enable(bool _is_state) { auto old = this->m_is_state.exchange(_is_state); if(old != _is_state) this->on_enable(_is_state); return old;}
	[[nodiscard]] virtual bool	process_get_enable() const noexcept{ return this->m_is_state;}

private:
			std::atomic<bool>	m_is_state;
};
