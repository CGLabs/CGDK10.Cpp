//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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

namespace CGDK
{
// ----------------------------------------------------------------------------
//
// time_event::object::service_stop
//
//
// ----------------------------------------------------------------------------
class time_event::object::service_stop :
	public						time_event::Ievent
{
public:
			service_stop(server_system::Iservice* _pservice = nullptr);
	virtual ~service_stop();

public:
			void				set_service(server_system::Iservice* _pservice);
	[[nodiscard]] auto			service() const noexcept { return m_pservice;}

protected:
	virtual	result_code			process_event(const chrono::time::utc::time_point& _time);

private:
			object_ptr<server_system::Iservice> m_pservice;
};


}