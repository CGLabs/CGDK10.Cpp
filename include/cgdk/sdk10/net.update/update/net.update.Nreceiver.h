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
// CGDK::update::Nreceiver
//
//
// ----------------------------------------------------------------------------
class CGDK::update::Nreceiver :
	public                      object::Ninitializable_startable,
	public						net::io::messageable::Nbase,
	virtual public				net::io::Isender
{
public:
			Nreceiver();
	virtual ~Nreceiver() noexcept;

public:
			void				set_root_path(std::string_view _root_path);
			void				set_root_path(std::string&& _root_path) noexcept;
			std::string			get_root_path() const noexcept { return m_path_root;}
			bool				have_root_path() const noexcept { return m_path_root.empty() == false; }

			object_ptr<md5_caching> get_md5_caching() const noexcept { return m_pmd5_caching; }
			void				set_md5_caching(md5_caching* _pmd5_caching) noexcept { m_pmd5_caching = _pmd5_caching; }


			uint64_t			get_total_required_bytes() const noexcept { return this->m_update_info.total_bytes; }
			uint64_t			get_total_required_files() const noexcept { return this->m_update_info.total_count; }
			uint64_t			get_total_processed_bytes() const noexcept { return this->m_total_processed_bytes; }
			uint64_t			get_total_processed_files() const noexcept { return this->m_total_processed_files; }
			uint64_t			get_total_transfered_bytes() const noexcept { return this->m_total_transfered_bytes; }
			uint64_t			get_total_transfered_files() const noexcept { return this->m_total_transfered_files; }
			auto				get_begin_time() const noexcept { return this->m_total_tick_begin; }
			auto				get_end_time() const noexcept { return this->m_total_tick_end; }
			float				get_period_bytes_per_second() const noexcept { return this->m_period_transfered_bytes_per_sec; }

protected:
	virtual	void				on_update_begin(const sUPDATE_REQUEST_INFO& /*_info*/) {}
	virtual	void				on_update_end(eRESULT /*_result*/) {}

	virtual	void				on_updatable_requested(update::Ireceivable* /*_pupdatable*/) {}
	virtual	void				on_updatable_begin(update::Ireceivable* /*_pupdatable*/, uint64_t /*_pos_begin*/) {}
	virtual	void				on_updatable_process(update::Ireceivable* /*_pupdatable*/, const resource::sMETA_FILE_BLOCK& /*_info*/) {}
	virtual	void				on_updatable_end(update::Ireceivable* /*_pupdatable*/, eRESULT /*_result*/) {}

private:
	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_UPDATE_BEGIN_REQUEST(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_END(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_REQUEST(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_BEGIN(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_BLOCK(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_END(sMESSAGE_NETWORK& _msg);

protected:
	virtual	result_code			_process_starting(context& _context) override;
	virtual	result_code			_process_stopping() noexcept override;

private:
			std::string			m_path_root;
			RECEIVER_ID			m_receiver_id;

			lockable<>			m_cs_map_updatable;
			sUPDATE_REQUEST_INFO m_update_info;

			// statistics)
			std::atomic<uint64_t> m_total_processed_bytes;
			std::atomic<uint64_t> m_total_processed_files;
			std::atomic<uint64_t> m_total_transfered_bytes;
			std::atomic<uint64_t> m_total_transfered_files;
			chrono::time::utc::time_point m_total_tick_begin;
			chrono::time::utc::time_point m_total_tick_end;

			std::atomic<uint64_t> m_period_transfered_bytes;
			chrono::time::utc::time_point m_period_tick_last;
			float				 m_period_transfered_bytes_per_sec;

			std::map<UPDATABLE_ID, object_ptr<update::Ireceivable>> m_map_updatable_receive;
			object_ptr<md5_caching> m_pmd5_caching;

			object_ptr<update::Ireceivable> find_updatable(UPDATABLE_ID _id);

			void				register_updatable(update::Ireceivable* _pupdatable);
			void				unregister_updatable(UPDATABLE_ID _id) noexcept;
			void				cancel_all_updatable() noexcept;

			void				process_close_updatable(update::Ireceivable* _pupdatable, eRESULT _result) noexcept;

};
