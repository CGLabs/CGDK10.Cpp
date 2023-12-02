//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
// ----------------------------------------------------------------------------
//
// resource::updatable::folder
//
//
// ----------------------------------------------------------------------------
class CGDK::resource::updatable::file :
	public                      object::Ninitializable,
	public                      object::Nnameable,
	public                      object::Nstate,
	virtual public				Iupdatable
{
public:
			result_code			initialize() { context _context; return this->initialize(_context); }
			result_code			initialize(const INITIALIZE_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(INITIALIZE_PARAMETER)) }; return this->initialize(temp); }
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }

protected:
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

			std::vector<shared_buffer> m_vector_buffer;
			std::filesystem::path m_full_file_path;

	virtual	result_code			process_message(sMESSAGE& _msg) override;
	virtual shared_buffer		get_block(uint64_t _pos) override;

			void				process_resource_load(const INITIALIZE_PARAMETER& _parameter);
			void				process_resource_clear() noexcept;
};
