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

 @class		CGDK::object::Istartable

*/
//-----------------------------------------------------------------------------
class CGDK::object::Istartable : virtual public Ireferenceable
{
public:
	virtual ~Istartable() noexcept {}

public:
			result_code			start() { context _context; return this->start(_context);}
			template<class TPARAMETER>
			result_code			start(const TPARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(TPARAMETER)) }; return this->start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) PURE;
	virtual	result_code			stop() noexcept PURE;

public:
			void				enable_ignore_exception_on_start(bool _flag_enable = true) noexcept { this->m_ignore_exception_on_start = _flag_enable; }
			void				disable_ignore_exception_on_start() noexcept { this->m_ignore_exception_on_start = false; }
	[[nodiscard]] bool			ignore_exception_on_start() const noexcept { return this->m_ignore_exception_on_start; }

			void				enable_ignore_exception_in_child_on_start(bool _flag_enable = true) noexcept { this->m_ignore_exception_in_child_on_start = _flag_enable; }
			void				disable_ignore_exception_in_child_on_start() noexcept { this->m_ignore_exception_in_child_on_start = false; }
	[[nodiscard]] bool			ignore_exception_in_child_on_start() const noexcept { return this->m_ignore_exception_in_child_on_start; }
private:
			bool				m_ignore_exception_on_start = false;
			bool				m_ignore_exception_in_child_on_start = false;
};
