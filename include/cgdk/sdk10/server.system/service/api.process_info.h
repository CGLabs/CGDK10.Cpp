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


#if defined(_WIN32)
#include <Pdh.h>

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// api::process_info
//
//
//-----------------------------------------------------------------------------
class api::process_info
{
// constructor/destructor)
public:
			process_info();
	virtual	~process_info();

// publics)
public:
			BOOL				init_process_info(std::string_view _process);
			BOOL				init_process_info(std::wstring_view _process);
			void				close_process_info() noexcept;

	[[nodiscard]] static PDH_STATUS get_counter(std::string_view _path, size_t _length_max);
	[[nodiscard]] static PDH_STATUS get_counter(std::wstring_view _path, size_t _length_max);

			void				update_counter();

public:
			int					m_process_time;

// implementation)
private:
			HQUERY				m_hquery;

			HCOUNTER			m_hCounter_ProcessTime;
};

}

//----------------------------------------------------------------------------
// Libraries Link
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)
	#pragma comment(lib, "Pdh.Lib")
#endif

#elif defined(__linux__)

#endif
