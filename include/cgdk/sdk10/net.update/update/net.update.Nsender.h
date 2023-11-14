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
// CGDK::update::Nsender
//
//
// ----------------------------------------------------------------------------
class CGDK::update::Nsender :
	public                      object::Ninitializable_startable,
	public						net::io::messageable::Nbase,
	virtual public				net::io::Isender
{
public:
			Nsender();
	virtual ~Nsender() noexcept;

public:
			RECEIVER_ID			get_receiver_id() const noexcept { return m_receiver_id; }
			void				set_receiver_id(RECEIVER_ID _receiver_id) noexcept { m_receiver_id = _receiver_id; }

			SENDER_ID			get_sender_id() const noexcept { return m_sender_id; }
			void				set_sender_id(SENDER_ID _sender_id) noexcept { m_sender_id = _sender_id; }
			void				generate_and_set_sender_id() noexcept;

			bool				add(const object_ptr<resource::Iupdatable>& _request);
			bool				add(object_ptr<resource::Iupdatable>&& _request);
			template <class TUPDATABLE>
			void				add(std::vector<object_ptr<TUPDATABLE>>&& _request)
			{
				for (auto& iter : _request)
					this->add(std::move(iter));
			}
			template <class TUPDATABLE>
			void				add(const std::vector<object_ptr<TUPDATABLE>>& _request)
			{
				for (auto& iter : _request)
					this->add(iter);
			}

			bool				empty() const noexcept { bool result; scoped_lock(this->m_cs_vector_updatable) { result = this->m_list_updatable_process.empty(); } return result; }
			bool				exist() const noexcept { return !empty(); }
			void				clear() noexcept;

			uint64_t			get_total_required_bytes() const noexcept { return this->m_total_required_bytes; }
			uint64_t			get_total_required_files() const noexcept { return this->m_total_required_files; }
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

	virtual	void				on_updatable_begin(resource::Iupdatable* /*_resource_updatable*/, const resource::sUPDATABLE_FILE_META_INFO& /*_info*/) {}
	virtual	void				on_updatable_process(resource::Iupdatable* /*_resource_updatable*/, const resource::sMETA_FILE_BLOCK& /*_info*/) {}
	virtual	void				on_updatable_end(resource::Iupdatable* /*_resource_updatable*/, eRESULT /*_result*/) {}

protected:
	virtual	result_code			_process_starting(context& _context) override;
	virtual	result_code			_process_stopping() noexcept override;

			void				process_add_updatable(object_ptr<resource::Iupdatable>&& _updatable);
			void				process_updatable_prepare();
			void				process_updatable_begin(resource::Iupdatable* _pupdatable, UPDATABLE_ID _updatable_id, uint64_t _pos_begin);
			void				process_updatable_next(resource::Iupdatable* _pupdatable);
			void				process_updatable_end(resource::Iupdatable* _pupdatable, UPDATABLE_ID _updatable_id, eRESULT _result);

			void				process_update_end(eRESULT _result) noexcept;
			void				process_cancel_all_updatable() noexcept;
			object_ptr<resource::Iupdatable> _process_get_first_updatable(UPDATABLE_ID _updatable_id) const;

	virtual result_code			on_message(sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_UPDATE_BEGIN_RESPONSE(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_RESPONSE(sMESSAGE_NETWORK& _msg);
			result_code			on_message_UPDATE_UPDATABLE_END(sMESSAGE_NETWORK& _msg);
protected:
			lockable<> m_cs_vector_updatable;
			std::list<object_ptr<resource::Iupdatable>> m_list_updatable_process;

			RECEIVER_ID			m_receiver_id;
			SENDER_ID			m_sender_id;

			int					m_count_try;
			size_t				m_bytes_now;

			// statistics)
			std::atomic<uint64_t> m_total_required_bytes;
			std::atomic<uint64_t> m_total_required_files;
			std::atomic<uint64_t> m_total_processed_bytes;
			std::atomic<uint64_t> m_total_processed_files;
			std::atomic<uint64_t> m_total_transfered_bytes;
			std::atomic<uint64_t> m_total_transfered_files;
			chrono::time::utc::time_point m_total_tick_begin;
			chrono::time::utc::time_point m_total_tick_end;

			std::atomic<uint64_t> m_period_transfered_bytes;
			float				 m_period_transfered_bytes_per_sec;
			chrono::time::utc::time_point m_period_tick_last;

			class Nreferenceable_send_completor : virtual public Imemory
			{
			public:
				object_ptr<Imemory> buf_original;
				object_ptr<Nsender> psender;
				object_ptr<resource::Iupdatable> pupdatable;
			private:
				virtual void process_dispose() noexcept override
				{
					// check)
					CGASSERT_ERROR(buf_original.exist());

					// check)
					CGASSERT_ERROR(pupdatable.exist());

					// 1) reset buf
					buf_original.reset();

					// 2) get sender
					object_ptr<Nsender> p = psender;

					// 3) call 'process_updatable_next'
					if (p.exist())
					{
						system_executor::post(make_executable([=,this] {p->process_updatable_next( this->pupdatable); }));
					}
				}
			};
			Nreferenceable_send_completor m_referenceable_send_completor;
};
