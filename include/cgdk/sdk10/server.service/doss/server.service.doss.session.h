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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::CAccount
//
//  State of Account
//
//   
//
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TENTITY = doss::Ientity>
class doss::session :
// inherited classes)
	virtual public				doss::Isession
{
public:
			session() {}
	virtual ~session() noexcept {}

public:
			result_code			checkin(const sENTITY_ID& _id_entity);
			result_code			checkin(const sENTITY_ID& _id_entity, Irepository* _prepository);
			result_code			checkout() noexcept;
			result_code			checkout(TRESPONSE&& _f_completion) noexcept;
			result_code			request(Itransactable* _ptransactable);
			void				cancel() noexcept;
	virtual	result_code			destroy() noexcept override;

	[[nodiscard]] auto			get_entity() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(m_lockable_entity)); return m_pentity; }
	[[nodiscard]] auto&			get_checkin_id() const noexcept { return m_cid; }
	[[nodiscard]] auto			get_session_id() const noexcept { return m_id_session; }

protected:
	virtual	void				on_entity_request_checkin (Itransactable* _ptransactable);
	virtual	void				on_entity_request_checkout (Itransactable* _ptransactable);
	virtual	void				on_entity_request_command (Itransactable* _ptransactable);
	virtual	void				on_entity_request_create (Itransactable* _ptransactable);
	virtual	void				on_entity_request_remove (Itransactable* _ptransactable);

	virtual	void				on_entity_checkin (Itransactable* _ptransactable);
	virtual	void				on_entity_fail_checkin (Itransactable* _ptransactable);
	virtual	void				on_entity_checkout (Itransactable* _ptransactable);
	virtual	void				on_entity_command (Itransactable* _ptransactable);
	virtual	void				on_entity_create (Itransactable* _ptransactable);
	virtual	void				on_entity_remove (Itransactable* _ptransactable);
	virtual	void				on_entity_update (Itransactable* _ptransactable);

protected:
			result_code			process_request_checkin (sCHECKIN_ID _cid, Irepository* _prepository);
	virtual	void				process_entity_transaction_request (Itransactable* _ptransactable) noexcept override;
	virtual	void				process_entity_transaction_complete	(Itransactable* _ptransactable) noexcept override;
	virtual void				process_entity_set (Itransactable* _ptransactable) override;
	virtual	bool				process_entity_reset (Ientity* _pentity, const sCHECKIN_ID& _cid, bool _is_force) noexcept override;

protected:
	// * entity objet
	//    - checkin 대상 entity object이다.
	//    - checin()함수로 요청하는 순간 설정되며 checkout()을 요청하는 순간 설정해제된다.
	//    - 따라서 m_pentity값이 존재한다고 해서 checkin된 상태라고 할 수 없다.
	//      checkin 여분는 m_cid의 값으로 확인할 수 있다.
			lockable<>			m_lockable_entity;
			object_ptr<TENTITY>	m_pentity;

	// * session id
	//    - session 고유의 id로 session이 생성될때 자동 부여된다.()
	//    - 같은 host에서만 고유하며 다른 host간에는 중복될수 있다.
	//    - 생성후 파괴될 때까지 변화지 않는다.
			sSESSION_ID			m_id_session = sSESSION_ID::generate();

	// * checin id
	//    - checkin시 할당되는 고유번호로 checin이 때마다 바뀔수 있다.
	//    - checin_id는 entity_id와 session_id를 포함하고 있다.
	//    - 따라서	repository_id -> checkin을 요청하는 repository에서 부여한다.
	//				entity_id -> checkin시 필수로 입력해 주어야 하는 id이다.
	//				session_id -> checkin시 session에서 해당 session_id를 설정한다.
	//				key_checkin -> checkin이 성공 시 repository에서 부여된다.
	//    - checkin_id는 checkin시 설정되며 checkout시 제거된다.
			sCHECKIN_ID			m_cid;
			lockable<>			m_lockable_request;

	// * time 
	//	  - m_time_checkin		마지막 checin 성공한 시간
	//    - m_time_checkout		마지막 checkout을 성공한 시간
			chrono::time::utc::time_point m_time_checkin;
			chrono::time::utc::time_point m_time_checkout;
};

template <class TENTITY>
result_code doss::session<TENTITY>::checkin(const sENTITY_ID& _id_entity)
{
	// 1) get repository
	auto prepository = doss::manager_repository::get_instance()->find(_id_entity.repository_id());
	
	// check) 
	RETURN_IF(prepository.empty(), eRESULT::NOT_EXIST); 
	
	// 2) checkin
	return process_request_checkin(sCHECKIN_ID{ _id_entity, get_session_id() }, prepository);
}

template <class TENTITY>
result_code doss::session<TENTITY>::checkin(const sENTITY_ID& _id_entity, Irepository* _prepository)
{
	return process_request_checkin(sCHECKIN_ID{ _id_entity, get_session_id(), sOBJECT_ID(), 0 }, _prepository);
}

template <class TENTITY>
result_code doss::session<TENTITY>::checkout() noexcept
{
	return checkout(nullptr);
}

template <class TENTITY>
result_code doss::session<TENTITY>::checkout(TRESPONSE&& _f_completion) noexcept
{
	// 1) alloc transactable object
	auto ptransactable = make_object<Itransactable>();

	// 2) set transaction info
	ptransactable->m_type = eTRANSACTION_TYPE::CHECKOUT;
	ptransactable->m_f_request = nullptr;
	ptransactable->m_result = eRESULT::NOT_DEFINED;
	ptransactable->m_f_completion = std::move(_f_completion);
	ptransactable->m_psession = this;
	ptransactable->m_cid.reset();

	// locked) 
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs_request(m_lockable_request);

		{
			// scoped_lock) 
			std::lock_guard<lockable<>> cs_entity(m_lockable_entity);

			// check) return if pentity is empty
			RETURN_IF(m_pentity.empty(), eRESULT::NOT_READY);

			// 3) set entity
			ptransactable->m_pentity = std::move(m_pentity);
		}

		// 4) call 'request_transaction' and return
		return ptransactable->m_pentity->request_transaction(ptransactable);
	}
}

template <class TENTITY>
result_code doss::session<TENTITY>::request(Itransactable* _ptransactable)
{
	// 1) alloc transaction object
	_ptransactable->m_type = eTRANSACTION_TYPE::COMMAND;
	_ptransactable->m_result = eRESULT::NOT_DEFINED;
	_ptransactable->m_psession = this;
	_ptransactable->m_cid.reset();

	// locked) 
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs_request(m_lockable_request);

		// 2) set transaction info - 2 (with lock)
		{
			// scoped_lock) 
			std::lock_guard<lockable<>> cs_entity(m_lockable_entity);

			// check) 
			RETURN_IF(m_pentity.empty(), eRESULT::NOT_READY);

			// - ...
			_ptransactable->m_pentity = m_pentity;
		}

		// 3) call 'request_transaction' and return
		return _ptransactable->m_pentity->request_transaction(_ptransactable);
	}
}

template <class TENTITY>
void doss::session<TENTITY>::cancel() noexcept
{
	// locked)
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs(m_lockable_entity);

		// check) 
		RETURN_IF(m_pentity.empty());

		// 1) cancel한다.
		m_pentity->cancel(m_cid);
	}
}

template <class TENTITY>
result_code doss::session<TENTITY>::destroy() noexcept
{
	// 1) checkout
	checkout(nullptr);

	// return)
	return eRESULT::SUCCESS;
}

template <class TENTITY>
void doss::session<TENTITY>::on_entity_request_checkin(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_request_checkout(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_request_command(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_request_create(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_request_remove(Itransactable* /*_ptransactable*/)
{
}

template <class TENTITY>
void doss::session<TENTITY>::on_entity_checkin(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_fail_checkin(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_checkout(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_command(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_create(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_remove(Itransactable* /*_ptransactable*/)
{
}
template <class TENTITY>
void doss::session<TENTITY>::on_entity_update(Itransactable* /*_ptransactable*/)
{
}

template <class TENTITY>
result_code doss::session<TENTITY>::process_request_checkin(sCHECKIN_ID _cid, Irepository* _prepository)
{
	// check) _prepository must not be nullptr
	CGASSERT_ERROR(_prepository != nullptr);

	// check) return if _prepository is nullptr
	RETURN_IF(_prepository == nullptr, eRESULT::INVALID_ARGUMENT);

	// check) _cid must not empty
	CGASSERT_ERROR(_cid.entity_id().exist());

	// check) id_entity must not empty (id_entity는 entity는 고유번호다.)
	RETURN_IF(_cid.entity_id().empty(), eRESULT::INVALID_ARGUMENT);

	// check) _cid must not empty
	CGASSERT_ERROR(_cid.session_id().exist());

	// check) id_entity must not empty (id_entity는 entity는 고유번호다.)
	RETURN_IF(_cid.session_id().empty(), eRESULT::INVALID_ARGUMENT);

	// check) _cid must not empty
	CGASSERT_ERROR(_cid.session_id() == get_session_id());

	// check) id_entity must not empty (id_entity는 entity는 고유번호다.)
	RETURN_IF(_cid.session_id() != get_session_id(), eRESULT::INVALID_ARGUMENT);

	// 1) get entity
	auto pentity = _prepository->get_entity(_cid.entity_id());

	// check) pentity must not be nullptr (이럴 확률은  사실상 0이다.)
	THROW_IF(pentity.empty(), throwable::failure(eRESULT::BAD_ALLOC));

	// 2) alloc transactable
	auto ptransactable = make_object<Itransactable>();

	// 3) set parameters
	ptransactable->m_type = eTRANSACTION_TYPE::CHECKIN;
	ptransactable->m_rid = m_id_session;
	ptransactable->m_result = eRESULT::NOT_DEFINED;
	ptransactable->m_prepository = _prepository;
	ptransactable->m_psession = this;
	ptransactable->m_pentity = pentity;
	ptransactable->m_cid = _cid;

	// lock) 
	{
		// scoped_lock)
		std::lock_guard<lockable<>> cs(m_lockable_request);

		// declare)
		object_ptr<Ientity>	pentity_old;

		// declare) 
		scoped_lock(m_lockable_entity)
		{
			// check) return if pentity is empty
			RETURN_IF(m_pentity.exist(), eRESULT::ALEADY_EXIST);

			// - checkout old entity
			if (m_pentity != pentity)
			{
				pentity_old = std::move(m_pentity);
			}

			// - set pentity
			m_pentity = pentity;
		}

		// check)
		CGASSERT_ERROR(m_pentity.exist());

		// 4) set entity object (내부적으로 이미 checkin한 entity가 존재하면 checkinout 요청을 한다.)
		if (pentity_old.exist())
		{
			// - alloc transaction object for checkout
			auto ptransactable_checkout = make_object<Itransactable>();

			// - set transaction parameters
			ptransactable_checkout->m_type = eTRANSACTION_TYPE::CHECKOUT;
			ptransactable_checkout->m_rid = m_id_session;
			ptransactable_checkout->m_result = eRESULT::NOT_DEFINED;
			ptransactable_checkout->m_prepository = pentity_old->m_prepository;
			ptransactable_checkout->m_psession = this;
			ptransactable_checkout->m_pentity = std::move(pentity_old);
			ptransactable_checkout->m_cid.reset();

			// - request checkout
			ptransactable_checkout->m_pentity->request_transaction(ptransactable_checkout);
		}

		// 5) request checkin
		auto result = ptransactable->m_pentity->request_transaction(ptransactable);

		// check) rollback if failed (기존에 checkin한 entity의 rollbak은 되지 않는다!
		if (result > eRESULT::PENDED&& result != eRESULT::ALEADY_DONE)
		{
			scoped_lock(m_lockable_entity)
			{
				if (m_pentity == pentity)
					m_pentity.reset();
			}
		}

		// return) 
		return result;
	}
}

template <class TENTITY>
void doss::session<TENTITY>::process_entity_transaction_request(Itransactable* _ptransactable) noexcept
{
	switch(_ptransactable->m_type)
	{
	case	eTRANSACTION_TYPE::CHECKIN:
			{
				// - checkin에서는 이미 동일한 cid로 checkin을 시도할 경우 취소처리를 하기 위해 m_cid를 empty로 만단다.
				if(_ptransactable->m_cid.id_entity == m_cid.id_entity)
				{
					_ptransactable->m_cid.reset();
				}

				// check) 
				CGASSERT_ERROR(_ptransactable->m_cid.empty() || _ptransactable->m_cid.id_entity == _ptransactable->m_pentity->m_eid);

				// - call 'on_entity_request_checkout'
				on_entity_request_checkin(_ptransactable);
			}
			break;

	case	eTRANSACTION_TYPE::COMMAND:
			{
				if(_ptransactable->m_pentity->m_eid == m_cid.id_entity)
				{
					// - set cid
					_ptransactable->m_cid = m_cid;

					// check) 
					RETURN_IF(m_cid.empty());

					// - call 'on_entity_request_checkout'
					on_entity_request_command(_ptransactable);
				}
				// 2) checkout을 요청한 entity와 다를 경우 취소한다.
				else
				{
					_ptransactable->m_cid.reset();
				}
			}
			break;

	case	eTRANSACTION_TYPE::UPDATE:
			{
			}
			break;

	case	eTRANSACTION_TYPE::CHECKOUT:
			{
				// 1) checkout을 요청한 entity와 동일해야 checkout을 요청한다.
				if(_ptransactable->m_pentity->m_eid == m_cid.id_entity)
				{
					// - set checkout
					_ptransactable->m_cid = m_cid;

					// check) 
					RETURN_IF(m_cid.empty());

					// debug)
					CGASSERT_ERROR(_ptransactable->m_cid.id_entity == _ptransactable->m_pentity->m_eid);

					// - call 'on_entity_request_checkout'
					on_entity_request_checkout(_ptransactable);
				}
				// 2) checkout을 요청한 entity와 다를 경우 취소한다.
				else
				{
					_ptransactable->m_cid.reset();
				}
			}
			break;

	case	eTRANSACTION_TYPE::CREATE:
			{
				//m_cid = _ptransactable->m_cid;

				// - call 'on_entity_request_create'
				on_entity_request_create(_ptransactable);
			}
			break;

	case	eTRANSACTION_TYPE::REMOVE:
			{
				// - call 'on_entity_request_remove'
				on_entity_request_remove(_ptransactable);

				_ptransactable->m_cid = m_cid;
				m_cid.reset();
			}
			break;

	default:
			break;
	}
}

template <class TENTITY>
void doss::session<TENTITY>::process_entity_transaction_complete(Itransactable* _ptransactable) noexcept
{
	try
	{
		switch(_ptransactable->m_type)
		{
		case	eTRANSACTION_TYPE::CHECKIN:
				{
					// !주의) on_entity_checkin은 doss::session<TENTITY>::process_entity_set에서 호출된다.

					// - call 'on_entity_fail_checkin'
					if(_ptransactable->m_result != eRESULT::SUCCESS)
					{
						on_entity_fail_checkin(_ptransactable);
					}
				}
				break;

		case	eTRANSACTION_TYPE::COMMAND:
				{
					on_entity_command(_ptransactable);
				}
				break;

		case	eTRANSACTION_TYPE::UPDATE:
				{
					on_entity_update(_ptransactable);
				}
				break;

		case	eTRANSACTION_TYPE::CHECKOUT:
				{
					// !주의) on_entity_checkout은 doss::session<TENTITY>::process_entity_reset에서 호출된다.
				}
				break;

		case	eTRANSACTION_TYPE::CREATE:
				{
					on_entity_create(_ptransactable);
				}
				break;

		case	eTRANSACTION_TYPE::REMOVE:
				{
					on_entity_remove(_ptransactable);
				}
				break;

		default:
				break;
		}
	}
	catch (...)
	{
	}
}

template <class TENTITY>
void doss::session<TENTITY>::process_entity_set(Itransactable* _ptransactable) // const sCHECKIN_ID& _cid, Ientity* _pentity)
{
	// check) 기존 m_cid가 존재한다면
	CGASSERT_ERROR(_ptransactable != nullptr)

	scoped_lock(m_lockable_entity)
	{
		// check) 같을 경우 앗사리 _cid는 empty로 전달되어와야 한다.
		CGASSERT_ERROR(m_cid.id_entity != _ptransactable->m_cid.id_entity);

		// check) m_pentity와 다르면 eRESULT::CANCEL exception을 던진다.
		THROW_IF(m_pentity != _ptransactable->m_pentity, throwable::failure(eRESULT::CANCEL));

		// 1) set checkin time
		m_time_checkin = chrono::time::utc::now();

		// check) 
		//CGASSERT_ERROR(m_cid.empty());

		// 2) set checkin_id
		m_cid = _ptransactable->m_cid;
	}

	// 3) call 'on_entity_checkin;
	on_entity_checkin(_ptransactable);
}

template <class TENTITY>
bool doss::session<TENTITY>::process_entity_reset(Ientity* /*_pentity*/, const sCHECKIN_ID& _cid, bool /*_is_force*/) noexcept
{
	// 1) reset value
	scoped_lock(m_lockable_entity)
	{
		// check) 
		if (m_cid != _cid)
		{
			return false;
		}

		// check)
		CGASSERT_ERROR(m_cid.exist());

		// - reset cid
		m_cid.reset();
	}

	// 2) set checkin time
	m_time_checkout = chrono::time::utc::now();

	// 3) Force Close한다.
	on_entity_checkout(nullptr);

	// return)
	return true;
}


}