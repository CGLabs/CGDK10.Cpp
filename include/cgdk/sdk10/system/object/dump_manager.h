//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
/**

 @class		Manager
 @brief		예외 관리자이다.
 @todo		
 @ref		
 @details	\n
 Access Violation과 같은 SEH에 의해 발생하는 Exception을 관리하는 매니저이다.
 일반적으로 예외가 발생했을 때 덤프를 남기는 역할을 수행한다.
 내부적으로 같은 주소에서 발생하는 예외에 대해서는 중복적으로 Dump를 남기지 않는다.
 set_dump_count_limit()를 사용해 남기는 최대의 Dump수를 설정할 수 있다.
 (기본값은 DEFAULT_MAX_DUMP_LIMIT:4096개)
 set_dump_type()를 사용하여 남기는 Dump의 내용을 설정할 수 있다.
 (기본값은 DEFAULT_MINIDUMP_TYPE:MINIDUMP_TYPE_MINI)

*///-----------------------------------------------------------------------------
#ifndef _WIN32
	struct EXCEPTION_POINTERS
	{
	};

	using LPEXCEPTION_POINTERS = EXCEPTION_POINTERS*;

#endif

class dump_manager :
// inherited classes)
	public						object::Nnameable,
	public						Nmessage_transmitter,
	virtual public				object::Idestroyable
{
// definitions)
public:
		using ITERATOR = std::map<void*, DUMP_INFO>::const_iterator;

// constructor/destructor) 
protected:
			dump_manager(eDUMP_CONTEXT _type_dump=eDUMP_CONTEXT::DEFAULT, size_t _max_dump_count=DEFAULT_MAX_DUMP_LIMIT) noexcept;
	virtual ~dump_manager() noexcept;

// public)
public:
	// 1) SEH enable/Disable
	//! @brief SEH 가능 여부를 설정한다. @param _enable SEH 가능 여부
			void				enable_seh(bool _enable=true) noexcept;
			void				disable_seh() noexcept;
			bool				seh_enabled() const noexcept;
			void				set_seh_to_thread() noexcept;
			void				set_invalid_parameter_handle() noexcept;

	// 2) dump
	//! @brief 미니 덤프 형태를 설정한다. @param _type_dump 미니 덤프 형태
			void				set_dump_type(eDUMP_CONTEXT _type_dump) noexcept { m_type_dump=_type_dump;}
			eDUMP_CONTEXT		get_dump_type() const noexcept { return m_type_dump;}
			void				set_dump_count_limit(size_t _limit) noexcept { m_count_dump_limit=_limit;}
			size_t				get_dump_count_limit() const noexcept { return m_count_dump_limit;}
			void				set_dump_path(std::string_view _path) noexcept { m_str_dump_path = _path; }
	[[nodiscard]] std::string_view get_dump_path() const noexcept { return m_str_dump_path; }
	[[nodiscard]] size_t		dump_count() const noexcept { return m_count_dump_now;}
																						  
	// 5) Iterator용.																	 
	//! @brief 락 객체를 얻는다.								
	[[nodiscard]] std::shared_mutex& get_lockable() noexcept { return m_lockable_map_dump; }
	[[nodiscard]] const std::shared_mutex& get_lockable() const noexcept { return m_lockable_map_dump; }
	[[nodiscard]] 				operator std::shared_mutex&() noexcept { return m_lockable_map_dump;}
	[[nodiscard]] 				operator const std::shared_mutex&() const noexcept { return m_lockable_map_dump;}
	[[nodiscard]] ITERATOR		begin() const noexcept { return m_map_dump.begin();}
	[[nodiscard]] ITERATOR		end() const noexcept { return m_map_dump.end();}
	[[nodiscard]] std::vector<DUMP_INFO> status_snap() const noexcept;
																						  
																						  
	// 6) initialize Instance/run_executor												  
	static 	auto				instance() { if(m_s_pinstance.empty()) { initialize_instance(); } return object_ptr<dump_manager>(m_s_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<dump_manager>&& _instance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_s_pinstance.detach(); }

	//! @extra
	static	void				print_statistics() noexcept;

	// 7) dispatch_exception_message_all
			void				dispatch_exception_message_all();

// framework) 
public:
	//! @brief 예외가 발생되었을 때 처리 내용을 정의한 함수
	virtual	void				process_exception(LPEXCEPTION_POINTERS _pexception);

	//! @brief 잘못된 인자가 발생했을 때 처리 내용을 정의한 함수
	virtual	void				process_invalid_parameter(std::wstring_view _expression, std::wstring_view _function, std::wstring_view _file, unsigned int _line, uintptr_t _reserved);

// implementation) 
protected:
	// 1) enable_seh
			bool				m_is_enable_seh;

	// 2) Dump 관련
			size_t				m_count_dump_limit;
			size_t				m_count_dump_now;
			eDUMP_CONTEXT		m_type_dump;
			std::shared_mutex	m_lockable_map_dump;
			std::map<void*, DUMP_INFO> m_map_dump;
			circular_list<void*> m_list_exception_event;
			std::string			m_str_dump_path;

	// 3) Instance
	static std::mutex			m_s_lockable_create;
	static own_ptr<dump_manager> m_s_pinstance;

private:
	// 4) destroy
	virtual	result_code			destroy() noexcept override;

protected:
	//! @brief 덤프를 생성한다. @param _str_dump_file 덤프 파일 이름 @param _pexception 예외 정보
			bool				create_dump(const std::string_view _str_dump_file, LPEXCEPTION_POINTERS _pexception);

	static	void				translator_function(uint32_t, LPEXCEPTION_POINTERS _pexception);
	static	void				invalid_parameter_handler(wchar_t const* _expression, wchar_t const* _function, wchar_t const* _file, unsigned int _line, uintptr_t _reserved);
};


// ----------------------------------------------------------------------------
//
//  Functions
//
// ----------------------------------------------------------------------------
void enable_seh(bool _is_enable=true);
void disable_seh();
bool seh_enabled();
void set_seh_to_thread() noexcept;
bool snap_dump(const std::string_view _str_dump_file = std::string_view(), eDUMP_CONTEXT _type_dump = eDUMP_CONTEXT::DEFAULT);
bool snap_dump(const std::wstring_view _str_dump_file, eDUMP_CONTEXT _type_dump = eDUMP_CONTEXT::DEFAULT);

}