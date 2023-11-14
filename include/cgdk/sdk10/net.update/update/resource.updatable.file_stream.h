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
class CGDK::resource::updatable::file_stream :
	public                      object::Ninitializable,
	public                      object::Nnameable,
	public                      object::Nstate,
	virtual public				Iupdatable
{
public:
	virtual	const sUPDATABLE_FILE_COMPLETION_INFO& get_meta_completion() override;

protected:
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	virtual	result_code			process_message(sMESSAGE& _msg) override;
	virtual shared_buffer		get_block(uint64_t _pos) override;

			void				process_resource_prepare(std::string_view _path_base, std::string_view _path, std::string_view _filename, resource::eOPTION _flag = eOPTION::NONE, uint64_t _block_size = update::_FILE_BLOCK_SIZE);
			void				process_resource_load();
			void				process_resource_clear() noexcept;

			void				_process_md5_prepare(FILE_HANDLE _file_handle, uint64_t _pos);
			void				_process_md5_append_md5(const char* _data, size_t _size);

			std::filesystem::path m_full_path;
			std::filesystem::path m_path;
			std::string			m_filename;
			resource::eOPTION	m_flag = resource::eOPTION::NONE;
			uint64_t			m_md5_pos = 0;
			edc::md5			m_md5_file;
			std::vector<shared_buffer> m_vector_buffer;
};