//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Socket template Classes                           *
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

 @class		preset
 @brief		CGDK::group
 @todo		
 @ref		
 @details	\n
 List형 Observer Class 객체
 Group과 다른 점은 독점적이지 않다는 것이다.
 여러개의 Observer에도 붙어서 동작할 수 있다.

*///-----------------------------------------------------------------------------
template <class _TMEMBER, class TPARAM = sMESSAGE, template <class... _A> class _GROUP = group::list_sender>
class group::preset :
	public						_GROUP<_TMEMBER, TPARAM>,
	public                      object::Ninitializable_startable,
    public						object::Nnameable,
    virtual public              net::io::Isender,
    public						net::io::messageable::Nbase
{
public:
	using group_base_t = _GROUP<_TMEMBER, TPARAM>;
	using param_t = typename _GROUP<_TMEMBER, TPARAM>::param_t;

public:
            preset() {}
            preset(const std::string_view _name) : Nnameable{_name} {}
    virtual ~preset() noexcept {}

private:
	virtual	void				on_start (context& /*_context*/) override { this->enable_member_enter(true);}
	virtual	void				on_stopping () override { this->disable_member_enter(); this->for_each_member([=](_TMEMBER* _pmember)->bool { _pmember->closesocket(); return true; }); }

	virtual	void				on_member_entered (_TMEMBER* _pmember, param_t& /*_param*/) override { _pmember->register_messageable(this); }
	virtual	void				on_member_leaved (_TMEMBER* _pmember, uintptr_t /*_result*/) override { _pmember->unregister_messageable(this); }
public:
			uint32_t			m_idx_list = 0xffffffff;
};



}