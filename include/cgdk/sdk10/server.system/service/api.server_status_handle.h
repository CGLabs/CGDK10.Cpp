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
//-----------------------------------------------------------------------------
//
// api::server_status_handle
//
//
//-----------------------------------------------------------------------------
class api::server_status_handle :
// inherited classes)
	virtual public				Ireferenceable
{
// constructor/destructor)
public:
			server_status_handle();
	virtual	~server_status_handle() noexcept;

// publics)
public:
	// 1) Register
			uint32_t			register_service_ctrl_handle(std::string_view  _lpServiceName, __callback LPHANDLER_FUNCTION_EX _lp_handler_proc, void* _pcontext = nullptr);
			uint32_t			register_service_ctrl_handle(std::wstring_view _lpServiceName, __callback LPHANDLER_FUNCTION_EX _lp_handler_proc, void* _pcontext = nullptr);

	// 2) Status
			bool				set_service_status(LPSERVICE_STATUS _lpServiceStatus);
			eOBJECT_STATE		set_service_status(eOBJECT_STATE _stateService, eOBJECT_STATE _ControlAccept = eOBJECT_STATE::DEFAULT);

	[[nodiscard]] bool			is_ready() const noexcept { return	m_hservice_status!= SERVICE_STATUS_HANDLE(0);}

// implementation)
protected:
			SERVICE_STATUS_HANDLE	m_hservice_status;
};


}