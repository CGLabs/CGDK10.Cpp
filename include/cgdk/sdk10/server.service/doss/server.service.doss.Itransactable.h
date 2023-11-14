//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
struct _COMMAND
{
	eTRANSACTION_TYPE		command;
	sREQUEST_ID				rid_source;
	sREQUEST_ID				rid;
	result_code				result;
	sCHECKIN_ID				cid;
};


typedef	std::function<result_code(doss::Itransactable* _ptransactable)>	TREQUEST;
typedef	std::function<result_code(doss::Itransactable* _ptransactable)>	TRESPONSE;


//-----------------------------------------------------------------------------
// Itransactable
//-----------------------------------------------------------------------------
class doss::Itransactable : 
	virtual public				Iexecutable
{
public:
			Itransactable() noexcept {}
	virtual ~Itransactable() noexcept {}

public:
			void				reset() noexcept;
			bool				cancel() noexcept;

			void				set_result(result_code _result, const shared_buffer& _buffer);
			void				set_result(result_code _result);
			void				complete_transaction() noexcept;
			void				complete_transaction(result_code _result) noexcept;
			void				complete_transaction(result_code _result, const shared_buffer& _buffer) noexcept;

public:
			eTRANSACTION_TYPE	m_type = eTRANSACTION_TYPE::NONE;
			uint64_t			m_option = 0;
			lockable<>			m_lockable_state;

			sREQUEST_ID			m_rid_source;
			sREQUEST_ID			m_rid;
			shared_buffer		m_buf_request;
			TREQUEST			m_f_request = nullptr;

			result_code			m_result = eRESULT::NOT_DEFINED;
			shared_buffer		m_buf_result;
			TRESPONSE			m_f_completion = nullptr;

			object_ptr<Irepository> m_prepository;
			object_ptr<Isession> m_psession;
			object_ptr<Ientity>	m_pentity;
			sCHECKIN_ID			m_cid;

protected:
			virtual intptr_t	process_execute(intptr_t _return, size_t _param) override;

			CGDK::flexible<sizeof(circular_list<int>::iterator)> m_iter_pending;
			friend class Ientity;
};

namespace doss
{
	inline object_ptr< doss::Itransactable> make_command(eTRANSACTION_TYPE _type)
	{
		// 1) alloc transaction
		auto ptransactable = make_object<doss::Itransactable>();

		// 2) set command
		ptransactable->m_type = _type;

		// return)
		return ptransactable;
	}
}


}