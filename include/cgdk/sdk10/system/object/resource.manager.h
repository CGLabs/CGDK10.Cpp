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

 @class		manager
 @brief		'자원 객체'를 관리하는 클래스
 @todo		
 @ref		
 @details	\n
 '자원 객체'를 등록해 관리하는 클래스이다.
 싱클턴으로 구현되어 있다.

*/
//-----------------------------------------------------------------------------
class resource::manager :
// Inherited Classes)
	public						object::Nnameable,
	virtual public				object::Idestroyable
{
// definitions)
public:
	using PATH_STRING = std::string;
	using CONTAINER = std::vector<PATH_STRING>;
	using ITERATOR = CONTAINER::iterator;
	using CONST_ITERATOR = CONTAINER::const_iterator;

// constructor/destructor)
public:
			manager() noexcept;
	virtual ~manager() noexcept;

// public)
public:
	//! @brief '자원 경로'를 등록한다. @param _str_path 등록할 '자원 경로' @return true 신규 등록시 @return false 기존에 등록되어 있었을 경우
				bool			register_resource_path(const std::string& _path);
				bool			unregister_resource_path(const std::string& _path) noexcept;

	//! @brief '자원 객체'를 등록한다. @param _presource 등록할 '자원 객체' @return 등록 성공 시 Exception을 던진다.
				void			register_resource(Iresource* _presource);
				bool			unregister_resource(Iresource* _presource) noexcept;
				bool			unregister_resource(const std::string& _name) noexcept;   // 이름으로 찾아 제거한다.   [12/27/2016 BSH]

	//! @brief '자원 객체'를 찾는다. @param _name 찾을 '객체 이름' @return 찾은 객체
				object_ptr<Iresource> find(const std::string& _name) noexcept;

	//! @brief '정방향 처음 반복자'를 얻는다. @return '정방향 처음 반복자'
	[[nodiscard]] ITERATOR		begin() noexcept { return this->m_vector_path.begin(); }
	[[nodiscard]] CONST_ITERATOR begin() const noexcept { return this->m_vector_path.begin(); }
	[[nodiscard]] ITERATOR		end() noexcept { return this->m_vector_path.end(); }
	[[nodiscard]] CONST_ITERATOR end() const noexcept { return this->m_vector_path.end(); }
																		  
	//! @brief 등록된 '자원 경로' 수를 얻는다. @return 등록된 '자원 경로' 수  
	[[nodiscard]] size_t		registered_path_count() const noexcept	{ return this->m_vector_path.size(); }
	[[nodiscard]] auto&			get_resource_path(size_t _index) const noexcept { return this->m_vector_path.at(_index); }

	//! @brief '자원 패스'를 얻는다. @param _index 인덱스 @return '자원 패스'
#if defined(__ANDROID__)
	[[nodiscard]] auto			get_activity() noexcept { return m_activity; }
				void			set_activity(ANativeActivity* _p) noexcept { m_activity=_p; }
#endif

	// 2) initialize Instance/run_executor
	static	auto				instance() { if(m_s_pinstance.empty()){ initialize_instance();} return object_ptr<manager>(m_s_pinstance); }
	static  void				initialize_instance();
	static	void				set_instance(own_ptr<manager>&& _pinstance);
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_s_pinstance.detach(); }

// implementation)
private:
	// 1) 
#if defined(__ANDROID__)
				ANativeActivity* m_activity;
#endif
	// 2) Path list
				lockable<CONTAINER> m_vector_path;

	// 3) Resources
				lockable<std::map<std::string, Iresource*>>	m_map_resources;

	// 4) Instance
	static	std::mutex			m_s_lockable_create;
	static	own_ptr<manager>	m_s_pinstance;

private:
	// 5) destroy
	virtual	result_code			destroy() noexcept override;
};

char*		get_filename_only(char* _dest, const char* _source);
wchar_t*	get_filename_only(wchar_t* _dest, const wchar_t* _source);
char16_t*	get_filename_only(char16_t* _dest, const char16_t* _source);
char32_t*	get_filename_only(char32_t* _dest, const char32_t* _source);


}