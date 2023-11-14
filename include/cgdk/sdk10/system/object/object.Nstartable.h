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

 @class		object::Nstartable

 */
//-----------------------------------------------------------------------------
class CGDK::object::Nstartable :virtual public object::Istartable, virtual	public object::Istate
{
public:
	virtual ~Nstartable() noexcept {}

public:
			result_code			start() { context _context; return this->start(_context);}
			template<class TPARAMETER>
			result_code			start(const TPARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(TPARAMETER)) }; return this->start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;

protected:
	virtual	void				on_start_request(context& /*_context*/) {}
	virtual	void				on_starting(context& /*_context*/) {}
	virtual	void				on_start(context& /*_context*/)	{}

	virtual	void				on_stop_request() {}
	virtual	void				on_stopping() {}
	virtual	void				on_stop() {}

public:
	virtual	result_code			process_start(context& _context);
	virtual	result_code			process_stop() noexcept;

public:
	virtual void				_process_start_request(context& _context) { this->on_start_request(_context);}
	virtual result_code			_process_starting(context& _context) { this->on_starting(_context); return result_code(eRESULT::SUCCESS);}
	virtual result_code			_process_start(context& _context) { this->on_start(_context); return result_code(eRESULT::SUCCESS);}
	virtual void				_process_stop_request() noexcept { try { this->on_stop_request(); } catch (...) { CGASSERT_ERROR(false); } }
	virtual result_code			_process_stopping() noexcept { try { this->on_stopping(); } catch (...) { CGASSERT_ERROR(false); } return result_code(eRESULT::SUCCESS);}
	virtual result_code			_process_stop() noexcept { try { this->on_stop(); } catch (...) { CGASSERT_ERROR(false); } return result_code(eRESULT::SUCCESS);}

protected:
			result_code			_process_starting_child(context& _context);
			result_code			_process_starting_child_complete(context& _context);
			void				_process_start_complete(context& _context);

			result_code			_process_stopping_child() noexcept;
			result_code			_process_stopping_child_complete() noexcept;
			void				_process_stop_complete() noexcept;
};