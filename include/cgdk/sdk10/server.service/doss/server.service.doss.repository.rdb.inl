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

template <class TENTITY, class TCREATE>
doss::repository::rdb<TENTITY, TCREATE>::rdb()
{
	// 1) Object Type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_DB);

	// 2) Register Repository
	doss::manager_repository::get_instance()->register_repository(this);
}

template <class TENTITY, class TCREATE>
doss::repository::rdb<TENTITY, TCREATE>::rdb(const std::string_view _name) :
	Nrepository<TENTITY>(),
	Nnameable(_name)
{
	// 1) Object Type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_DB);

	// 2) Register Repository
	doss::manager_repository::get_instance()->register_repository(this);
}

template <class TENTITY, class TCREATE>
doss::repository::rdb<TENTITY, TCREATE>::~rdb() noexcept
{
	// 1) Unregister Repository
	doss::manager_repository::get_instance()->unregister_repository(this);
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_initializing(context& /*_msg*/)
{
	// 1) sREPOSITORY_ID를 새로 할당받는다.
	Irepository::m_id_repository	 = sREPOSITORY_ID::generate();
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_initialize(context& /*_msg*/)
{
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_destroying()
{
	this->checkout_all();
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_destroy()
{
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_starting(context& /*_msg*/)
{
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_start(context& /*_msg*/)
{
	// 1) state ...
	set_object_state(eOBJECT_STATE::ESTABLISHED);

	// 2) notify one 
	this->m_cv_complete.notify_one();
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_stop_request()
{
	// - set eOBJECT_STATE::RUNNING if state is 'eOBJECT_STATE::ESTABLISHED'
	set_object_state_if(eOBJECT_STATE::ESTABLISHED, eOBJECT_STATE::RUNNING);
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_stopping()
{
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_stop()
{
}

template <class TENTITY, class TCREATE>
void doss::repository::rdb<TENTITY, TCREATE>::on_execute()
{

}

template <class TENTITY, class TCREATE>
object_ptr<TENTITY> doss::repository::rdb<TENTITY, TCREATE>::process_alloc_entity(sENTITY_ID _entity_id)
{
	// 1) alloc entity object
	auto pentity = make_object<TCREATE>();

	// 2) set entity_id 
	pentity->m_eid = _entity_id;

	// return)
	return pentity;
}


}