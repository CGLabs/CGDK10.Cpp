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
// api::service_handle
//
//
//-----------------------------------------------------------------------------
class api::service_handle :
// inherited classes)
	virtual public				Ireferenceable
{
// constructor/destructor)
public:
			service_handle() noexcept;
	virtual ~service_handle() noexcept;

// publics)
public:
#if defined (_WIN32)
	// 1) open / close
			void					open_SC_manager(uint32_t _desired_access=SC_MANAGER_ALL_ACCESS);
			void					open_SC_manager(std::string_view _lpMachineName,  std::string_view _lpDatabaseName = std::string_view(),   uint32_t _desired_access = SC_MANAGER_ALL_ACCESS);
			void					open_SC_manager(std::wstring_view _lpMachineName, std::wstring_view _lpDatabaseName = std::wstring_view(), uint32_t _desired_access = SC_MANAGER_ALL_ACCESS);
			void					open(SC_HANDLE _hSCManager, std::string_view _lpServiceName, uint32_t _desired_access = SERVICE_ALL_ACCESS);
			void					open(SC_HANDLE _hSCManager, std::wstring_view _lpServiceName, uint32_t _desired_access = SERVICE_ALL_ACCESS);

			void					create(
										SC_HANDLE			_hSCManager,
										std::string_view	_lpServiceName,
										std::string_view	_lpDisplayName,
										uint32_t			_desired_access,
										uint32_t			_service_type,
										uint32_t			_start_type,
										uint32_t			_error_control,
										std::string_view	_lpBinaryPathName,
										std::string_view	_lpLoadOrderGroup	= std::string_view(),
										uint32_t*			_lpdwTagId			= nullptr,
										std::string_view	_lpDependencies		= std::string_view(),
										std::string_view	_lpServiceStartName	= std::string_view(),
										std::string_view	_lpPassword			= std::string_view());

			void					create(
										SC_HANDLE			_hSCManager,
										std::wstring_view	_lpServiceName,
										std::wstring_view	_lpDisplayName,
										uint32_t			_desired_access,
										uint32_t			_service_type,
										uint32_t			_start_type,
										uint32_t			_error_control,
										std::wstring_view	_lpBinaryPathName,
										std::wstring_view	_lpLoadOrderGroup	= std::wstring_view(),
										uint32_t*			_lpdwTagId			= nullptr,
										std::wstring_view	_lpDependencies		= std::wstring_view(),
										std::wstring_view	_lpServiceStartName	= std::wstring_view(),
										std::wstring_view	_lpPassword			= std::wstring_view());

			bool					destroy() noexcept;
			bool					close() noexcept;
		
	// 2) Service configure
			bool					set_config(uint32_t _dwInfoLevel, void* _lpInfo) noexcept;
		
			bool					set_description(std::string_view _str_service_description) noexcept;
			bool					set_description(std::wstring_view _str_service_description) noexcept;
		
	// 3) Service control
			bool					start(uint32_t _dwNumServiceArgs=0, const char** _lpServiceArgVectors=nullptr) noexcept;
			bool					start(uint32_t _dwNumServiceArgs=0, const wchar_t** _lpServiceArgVectors=nullptr) noexcept;
			bool					control(uint32_t _dwControl, LPSERVICE_STATUS _lpServiceStatus) noexcept;
			bool					stop() noexcept;
			bool					pause() noexcept;
			bool					resume() noexcept;
			bool					get_status(LPSERVICE_STATUS _lpServiceStatus) noexcept;
	[[nodiscard]] uint32_t			get_status() noexcept;
			bool					query_status(LPSERVICE_STATUS _lpServiceStatus) noexcept;
		
	// 4) Status
	[[nodiscard]] bool				is_ready() const noexcept { return m_hService != 0;}

	// 5) Operator
	[[nodiscard]] operator SC_HANDLE() const noexcept { return m_hService;}

// implementation)
protected:
			SC_HANDLE			m_hService;
			PDH_HCOUNTER		m_hCounter;
			object_ptr<manager_perfornamce_query>	m_pmanager;
#elif defined(__linux__)
#else
#endif
};


}