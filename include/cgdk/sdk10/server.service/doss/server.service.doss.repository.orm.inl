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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
namespace CGDK
{

template <class TENTITY, class TCREATE>
doss::repository::orm<TENTITY, TCREATE>::orm()
{
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_ORM);
}

template <class TENTITY, class TCREATE>
doss::repository::orm<TENTITY, TCREATE>::orm(const std::string_view _name) : rdb<TENTITY, TCREATE>(_name)
{
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_ORM);
}

template <class TENTITY, class TCREATE>
doss::repository::orm<TENTITY, TCREATE>::~orm() noexcept
{
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_initializing(context& _msg)
{
	rdb<TENTITY, TCREATE>::on_initializing(_msg);
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_initialize(context& _msg)
{
	rdb<TENTITY, TCREATE>::on_initialize(_msg);
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_destroying()
{
	rdb<TENTITY, TCREATE>::on_destroying();
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_destroy()
{
	rdb<TENTITY, TCREATE>::on_destroy();
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_starting(context& _msg)
{
	rdb<TENTITY, TCREATE>::on_starting(_msg);
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_start(context& _msg)
{
	rdb<TENTITY, TCREATE>::on_start(_msg);
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_stop_request()
{
	rdb<TENTITY, TCREATE>::on_stop_request();
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_stopping()
{
	rdb<TENTITY, TCREATE>::on_stopping();
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_stop()
{
	rdb<TENTITY, TCREATE>::on_stop();
}

template <class TENTITY, class TCREATE>
void doss::repository::orm<TENTITY, TCREATE>::on_execute()
{

}


}