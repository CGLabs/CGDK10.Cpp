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
// CGDK::update::receiver
//
//
// ----------------------------------------------------------------------------
namespace CGDK
{
namespace update
{

class receiver_lambda : public receiver
{
public:
	typedef	std::function<void(receiver_lambda*, const sUPDATE_REQUEST_INFO&)> TFUNCTION_UPDATE_BEGIN;
	typedef	std::function<void(receiver_lambda*, eRESULT)> TFUNCTION_UPDATE_END;

	typedef	std::function<void(receiver_lambda*, Ireceivable* _preceivable)> TFUNCTION_UPDATABLEE_PREPARE;
	typedef	std::function<void(receiver_lambda*, Ireceivable* _preceivable, uint64_t)> TFUNCTION_UPDATABLEE_BEGIN;
	typedef	std::function<void(receiver_lambda*, Ireceivable* _preceivable, const resource::sMETA_FILE_BLOCK&)> TFUNCTION_UPDATABLEE_PROCESS;
	typedef	std::function<void(receiver_lambda*, Ireceivable* _preceivable, eRESULT)> TFUNCTION_UPDATABLEE_END;

public:
			void				set_function_update_begin(const TFUNCTION_UPDATE_BEGIN& _function) { this->m_function_update_begin = _function; }
			void				set_function_update_begin(TFUNCTION_UPDATE_BEGIN&& _function) { this->m_function_update_begin = std::move(_function); }
			void				reset_function_update_begin() noexcept { this->m_function_update_begin = std::move(TFUNCTION_UPDATE_BEGIN()); }

			void				set_function_update_end(const TFUNCTION_UPDATE_END& _function) { this->m_function_update_end = _function; }
			void				set_function_update_end(TFUNCTION_UPDATE_END&& _function) { this->m_function_update_end = std::move(_function); }
			void				reset_function_update_end() noexcept { this->m_function_update_end = std::move(TFUNCTION_UPDATE_END()); }

			void				set_function_updatable_prepare(const TFUNCTION_UPDATABLEE_PREPARE& _function) { this->m_function_updatable_prepare = _function; }
			void				set_function_updatable_prepare(TFUNCTION_UPDATABLEE_PREPARE&& _function) { this->m_function_updatable_prepare = std::move(_function); }
			void				reset_function_updatable_prepare() noexcept { this->m_function_updatable_prepare = std::move(TFUNCTION_UPDATABLEE_PREPARE()); }

			void				set_function_updatable_begin(const TFUNCTION_UPDATABLEE_BEGIN& _function) { this->m_function_updatable_begin = _function; }
			void				set_function_updatable_begin(TFUNCTION_UPDATABLEE_BEGIN&& _function) { this->m_function_updatable_begin = std::move(_function); }
			void				reset_function_updatable_begin() noexcept { this->m_function_updatable_begin = std::move(TFUNCTION_UPDATABLEE_BEGIN()); }

			void				set_function_updatable_process(const TFUNCTION_UPDATABLEE_PROCESS& _function) { this->m_function_updatable_process = _function; }
			void				set_function_updatable_process(TFUNCTION_UPDATABLEE_PROCESS&& _function) { this->m_function_updatable_process = std::move(_function); }
			void				reset_function_updatable_process() noexcept { this->m_function_updatable_process = std::move(TFUNCTION_UPDATABLEE_PROCESS()); }

			void				set_function_updatable_end(const TFUNCTION_UPDATABLEE_END& _function) { this->m_function_updatable_end = _function; }
			void				set_function_updatable_end(TFUNCTION_UPDATABLEE_END&& _function) { this->m_function_updatable_end = std::move(_function); }
			void				reset_function_updatable_end() noexcept { this->m_function_updatable_end = std::move(TFUNCTION_UPDATABLEE_END()); }

			//------------------------------------------------------------
			//
			// template source for setting lambda function
			//
			// 
			//				set_function_update_begin([=](update::receiver_lambda* /*_preceiver*/, const update::sUPDATE_REQUEST_INFO& /*_update_request_info*/) {
			//					});
			//
			//				set_function_update_end([=](update::receiver_lambda* /*_preceiver*/, eRESULT /*_result*/) {
			//					});
			//
			//				set_function_updatable_begin([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* /*_preceivable*/, const resource::sUPDATABLE_FILE_META_INFO& /*_updatable_info*/) {
			//					});
			//
			//				set_function_updatable_process([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* /*_preceivable*/, const resource::sMETA_FILE_BLOCK& /*_block_info*/) {
			//					});
			//
			//				set_function_updatable_end([=](update::receiver_lambda* /*_preceiver*/, update::Ireceivable* /*_preceivable*/, eRESULT /*_result*/) {
			//					});
			// 
			//------------------------------------------------------------
protected:
	virtual	void				on_update_begin(const sUPDATE_REQUEST_INFO& _info) override { if (this->m_function_update_begin) this->m_function_update_begin(this, _info); }
	virtual	void				on_update_end(eRESULT _result) override { if (this->m_function_update_end) this->m_function_update_end(this, _result); }

	virtual	void				on_updatable_requested(Ireceivable* _preceivable) override { if (this->m_function_updatable_prepare) this->m_function_updatable_prepare(this, _preceivable); }
	virtual	void				on_updatable_begin(Ireceivable* _preceivable, uint64_t _pos_begin) override { if (this->m_function_updatable_begin) this->m_function_updatable_begin(this, _preceivable, _pos_begin); }
	virtual	void				on_updatable_process(Ireceivable* _preceivable, const resource::sMETA_FILE_BLOCK& _block_info) override { if (this->m_function_updatable_process) this->m_function_updatable_process(this, _preceivable, _block_info); }
	virtual	void				on_updatable_end(Ireceivable* _preceivable, eRESULT _result) override { if (this->m_function_updatable_end) this->m_function_updatable_end(this, _preceivable, _result); }

protected:
			TFUNCTION_UPDATE_BEGIN		m_function_update_begin;
			TFUNCTION_UPDATE_END		m_function_update_end;

			TFUNCTION_UPDATABLEE_PREPARE m_function_updatable_prepare;
			TFUNCTION_UPDATABLEE_BEGIN	m_function_updatable_begin;
			TFUNCTION_UPDATABLEE_PROCESS m_function_updatable_process;
			TFUNCTION_UPDATABLEE_END	m_function_updatable_end;

};

}
}
