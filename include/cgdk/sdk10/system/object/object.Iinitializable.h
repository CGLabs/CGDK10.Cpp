//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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

 @class		object::Iinitializable

*/
//-----------------------------------------------------------------------------
class CGDK::object::Iinitializable : virtual public object::Idestroyable
{
public:
	virtual ~Iinitializable() noexcept {}

public:
			result_code			initialize() { context _context; return this->initialize(_context); }
			template<class TPARAMETER>
			result_code			initialize(const TPARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(TPARAMETER)) }; return this->initialize(temp); }
			result_code			initialize(const context& _context) { context context_copy(_context); return this->initialize(context_copy);}
	virtual	result_code			initialize(context& _context) PURE;

public:
			void				enable_ignore_exception_on_initialize(bool _flag_enable = true) noexcept { this->m_ignore_exception_on_initialize = _flag_enable; }
			void				disable_ignore_exception_on_initialize() noexcept { this->m_ignore_exception_on_initialize = false; }
	[[nodiscard]] bool			ignore_exception_on_initialize() const noexcept { return this->m_ignore_exception_on_initialize; }

			void				enable_ignore_exception_in_child_on_initialize(bool _flag_enable = true) noexcept { this->m_ignore_exception_in_child_on_initialize = _flag_enable; }
			void				disable_ignore_exception_in_child_on_initialize() noexcept { this->m_ignore_exception_in_child_on_initialize = false; }
	[[nodiscard]] bool			ignore_exception_in_child_on_initialize() const noexcept { return this->m_ignore_exception_in_child_on_initialize; }
private:
			bool				m_ignore_exception_on_initialize = false;
			bool				m_ignore_exception_in_child_on_initialize = false;
};