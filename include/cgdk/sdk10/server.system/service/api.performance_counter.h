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
// api::performance_counter
//
//
//-----------------------------------------------------------------------------
class api::performance_counter :
// inherited classes)
	virtual public				Ireferenceable,
	public						factory::_traits_system
{
// constructor/destructor)
public:
			performance_counter();
			performance_counter(std::string_view  _query);
			performance_counter(std::wstring_view _query);
	virtual ~performance_counter() noexcept;

// publics)
public:
	// 1) create/destroy
			bool				create(std::string_view _query);
			bool				create(std::wstring_view _query);
			void				destroy() noexcept;

	// 2) GetValue
	[[nodiscard]] long			get_value_long(uint32_t _flag=PDH_FMT_1000);
	[[nodiscard]] double		get_value_double();

// implementation)
protected:
#if defined (_WIN32)
			PDH_HCOUNTER		m_hCounter;
			object_ptr<manager_perfornamce_query>	m_pmanager;
#elif defined(__linux__)

#else

#endif

	friend	class manager_perfornamce_query;
};


}