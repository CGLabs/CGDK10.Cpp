//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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
// Query Performance
//
//-----------------------------------------------------------------------------
class query_performance
{
#ifdef _WIN32
// constructor/destructor) 
public:
			query_performance() noexcept : m_tick_frequency(), m_time_pre(), m_time_now(), m_gap_time()	{ QueryPerformanceFrequency(&m_tick_frequency); ;}
			~query_performance() noexcept {}

// public)
public:
	[[nodiscard]] float		get_gaptime() const noexcept { return m_gap_time;}
			void			check_time_start() noexcept { QueryPerformanceCounter(&m_time_pre);}
			void			check_time_end() noexcept { QueryPerformanceCounter(&m_time_now); m_gap_time=(float(m_time_now.QuadPart)-float(m_time_pre.QuadPart))/float(m_tick_frequency.QuadPart)*1000.f;}

// implementation) 
protected:
			LARGE_INTEGER	m_tick_frequency;

			LARGE_INTEGER	m_time_pre;
			LARGE_INTEGER	m_time_now;

			float			m_gap_time;
#endif
};















}