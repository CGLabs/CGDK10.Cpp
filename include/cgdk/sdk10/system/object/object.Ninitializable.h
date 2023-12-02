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

 @class		object::Ninitializable


*/
//-----------------------------------------------------------------------------
class CGDK::object::Ninitializable : virtual	public object::Istate, virtual public object::Iinitializable
{
public:
			result_code			initialize() { context _context; return this->initialize(_context); }
			template<class TPARAMETER>
			result_code			initialize(const TPARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(TPARAMETER)) }; return this->initialize(temp); }
	virtual	result_code			initialize(context& _context) override;
	virtual	result_code			destroy() noexcept override;

protected:
	virtual	void				on_initialize_request(context& /*_context*/) {}
	virtual	void				on_initializing(context& /*_context*/) {}
	virtual	void				on_initialize(context& /*_context*/) {}

	virtual	void				on_destroy_request() {}
	virtual	void				on_destroying() {}
	virtual	void				on_destroy() {}

public:
	virtual	result_code			process_initialize(context& _context);
	virtual	result_code			process_destroy() noexcept;

	virtual void				_process_initialize_request(context& _context) { this->on_initialize_request(_context); }
	virtual result_code			_process_initializing(context& _context) { this->on_initializing(_context); return result_code(eRESULT::SUCCESS);}
	virtual result_code			_process_initialize(context& _context) { this->on_initialize(_context); return result_code(eRESULT::SUCCESS); }
	virtual void				_process_destroy_request() noexcept { try { this->on_destroy_request(); } catch (...) { CGASSERT_ERROR(false); }}
	virtual result_code			_process_destroying() noexcept { try { this->on_destroying(); } catch (...) { CGASSERT_ERROR(false); } return result_code(eRESULT::SUCCESS); }
	virtual result_code			_process_destroy() noexcept { try { this->on_destroy(); } catch (...) { CGASSERT_ERROR(false); } return result_code(eRESULT::SUCCESS); }

protected:
			result_code			_process_initializing_child(context& _context);
			result_code			_process_initializing_child_complete(context& _context);
			void				_process_initialize_complete(context& _context);

			result_code			_process_destroying_child() noexcept;
			result_code			_process_destroying_child_complete() noexcept;
			void				_process_destroy_complete() noexcept;

			lockable<>			m_cs_map_applied_initialization_param;
			std::map<std::string, std::string> m_map_applied_initialization_param;
			void				_process_add_applied_initialization_param(const std::string& _key, const std::string_view _value);
			void				_process_reset_applied_initialization_param() noexcept;
};