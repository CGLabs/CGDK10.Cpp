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
// CGDK::update::Nsender_stream
//
//
// ----------------------------------------------------------------------------
class CGDK::update::md5_caching :
	public                      object::Ninitializable_startable
{
protected:
			struct sPREPARE_INFO
			{
				sUPDATABLE_PREPARE_INFO prepare_info;
				std::filesystem::file_time_type time_write;
			};
public:
			md5_caching();
	virtual ~md5_caching() noexcept;

public:
			result_code			start();
	virtual	result_code			start(context& _context);
			result_code			start(std::string_view _filename, int _file_confirm_level=1, bool _auto_save = true);

			sUPDATABLE_PREPARE_INFO get_prepare_info(const std::string& _full_file_path) const noexcept;
			void				put_prepare_info(const std::string& _full_file_path, const sUPDATABLE_PREPARE_INFO& _prepare_info);
			void				pop_prepare_info(const std::string& _fullpath) noexcept;

			void				save();
			void				save_as(std::string_view _filename = std::string_view());
			void				load();
			void				load_from(std::string_view _filename = std::string_view());
			void				set_filename(const std::string& _filename);
			void				set_filename(std::string&& _filename);			
			std::filesystem::path get_filename() const noexcept;

protected:
	virtual	void				on_caching_file_saved() {}
	virtual	void				on_caching_file_loaded() {}

protected:
	virtual	result_code			_process_starting(context& _context) override;
	virtual	result_code			_process_stopping() noexcept override;
			bool				_process_confirm_files(std::map<std::string, sPREPARE_INFO>& _map_cached_file);
			void				process_save_caching_file(std::string_view _filename);
			void				process_load_caching_file(std::string_view _filename);


			std::string			m_filename;
			int					m_file_confirm_level = 1;
			bool				m_is_auto_save = true;
			bool				m_is_changed = true;

			lockable<>			m_cs_map_prepare_info;
			std::map<std::string, sPREPARE_INFO> m_map_prepare_info;
};