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
// api functions
//
//
//-----------------------------------------------------------------------------
namespace api
{

// 1) Install/UnInstall
	bool service_install(
		std::string_view		_pszSvcDispName	 = std::string_view(),
		std::string_view		_pszSvcDesc		 = std::string_view(),
		uint32_t				_desired_access	 = SERVICE_ALL_ACCESS,
		uint32_t				_service_type	 = SERVICE_WIN32_OWN_PROCESS,
		uint32_t				_start_type		 = SERVICE_AUTO_START,
		uint32_t				_error_control	 = SERVICE_ERROR_NORMAL) noexcept;
	bool service_install(
		std::wstring_view		_pszSvcDispName,
		std::wstring_view		_pszSvcDesc		 = std::wstring_view(),
		uint32_t				_desired_access	 = SERVICE_ALL_ACCESS,
		uint32_t				_service_type	 = SERVICE_WIN32_OWN_PROCESS,
		uint32_t				_start_type		 = SERVICE_AUTO_START,
		uint32_t				_error_control	 = SERVICE_ERROR_NORMAL) noexcept;
	bool service_uninstall() noexcept;

// 2) start/stop/pause/Contiune
bool service_start (std::string_view _str_service_name, uint32_t _dwNumServiceArgs, const char** _lpServiceArgVectors) noexcept;
bool service_start (std::wstring_view _str_service_name, uint32_t _dwNumServiceArgs, const wchar_t** _lpServiceArgVectors) noexcept;
bool service_stop (std::string_view  _str_service_name) noexcept;
bool service_stop (std::wstring_view _str_service_name) noexcept;
bool service_pause (std::string_view  _str_service_name) noexcept;
bool service_pause (std::wstring_view _str_service_name) noexcept;
bool service_continue (std::string_view  _str_service_name) noexcept;
bool service_continue (std::wstring_view _str_service_name) noexcept;

// 3) Status
uint32_t service_status(std::string_view  _str_service_name) noexcept;
uint32_t service_status(std::wstring_view _str_service_name) noexcept;

// 4) Util..
uint32_t get_service_path_name(char* _str_service_name, char* _str_binary_path_name = nullptr) noexcept;
uint32_t get_service_path_name(wchar_t* _str_service_name, wchar_t* _str_binary_path_name = nullptr) noexcept;

}


}