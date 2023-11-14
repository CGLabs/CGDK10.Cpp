//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                        Server System MFC Controls                         *
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
namespace CGDK
{

template <class TENTITY>
doss::repository::Nhub<TENTITY>::Nhub()
{
	// 1) object Type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_HUB);

	// 2) register repository
	doss::manager_repository::get_instance()->register_repository(this);
}

template <class TENTITY>
doss::repository::Nhub<TENTITY>::Nhub(const std::string_view _name) : Nnameable(_name)
{
	// 1) Object Type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_HUB);

	// 2) Register Repository
	doss::manager_repository::get_instance()->register_repository(this);
}

template <class TENTITY>
doss::repository::Nhub<TENTITY>::~Nhub() noexcept
{
	// 1) Unregister Repository
	doss::manager_repository::get_instance()->unregister_repository(this);
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_initializing(context& /*_msg*/)
{
	// 1) sREPOSITORY_ID를 새로 할당받는다.
	m_object_id	 = sOBJECT_ID::generate();
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_initialize(context& _msg)
{
	// 1) 모두 초기화한다.
	scoped_lock(m_list_repository)
	{
		for(auto& iter:m_list_repository)
		{
			iter->Initialize(_msg);
		}
	}
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_destroying()
{
	// 1) 모두 Destroying한다.
	scoped_lock(m_list_repository)
	{
		for(auto& iter:m_list_repository)
		{
			iter->destroy();
		}
	}
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_destroy()
{
	// 1) sREPOSITORY_ID를 Reset한다.
	m_object_id.reset();
}

// 2) start/Stop
template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_starting(context& _msg)
{
	// 1) 모두 start한다.
	scoped_lock(m_list_repository)
	{
		for(auto& iter:m_list_repository)
		{
			iter->start(_msg);
		}
	}
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_start(context& /*_msg*/)
{
	// 1) state ...
	set_object_state(eOBJECT_STATE::ESTABLISHED);

	// 2) notify one 
	this->m_cv_complete.notify_one();
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_stop_request()
{
	// - set eOBJECT_STATE::RUNNING if state is 'eOBJECT_STATE::ESTABLISHED'
	set_object_state_if(eOBJECT_STATE::ESTABLISHED, eOBJECT_STATE::RUNNING);
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_stopping()
{
	// 1) 모두 Stop한다.
	scoped_lock(m_list_repository)
	{
		for(auto& iter:m_list_repository)
		{
			iter->Stop();
		}
	}
}

template <class TENTITY>
void doss::repository::Nhub<TENTITY>::on_stop()
{
}

template <class TENTITY>
result_code doss::repository::Nhub<TENTITY>::process_request_transaction(Itransactable* _ptransactable)
{
	// 1) get repository
	auto prepository = process_find_repository(_ptransactable);

	// check) 
	RETURN_IF(prepository.empty(), eRESULT::NOT_READY);

	// 2) ...
	return	prepository->process_request_transaction(_ptransactable);
}


}