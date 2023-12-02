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

 @class		NString

*/
//-----------------------------------------------------------------------------
class CGDK::object::Nnameable : virtual public object::Inameable
{
public:
			Nnameable() noexcept {}
			Nnameable(std::string_view _name) { set_name(_name);}
	virtual	~Nnameable() noexcept {}

	virtual	void				process_set_name(std::string_view _name) override { this->m_name = _name;}
	[[nodiscard]] virtual bool	process_is_this(std::string_view _str_compare) const noexcept override { return this->m_name == _str_compare;}
	[[nodiscard]] virtual std::string_view process_get_name() const noexcept override{ return this->m_name;}

private:
			static_string<MAX_NAME_LENGTH> m_name;
};
