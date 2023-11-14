//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// net::io::messageable::Nproxy<T>
//
//-----------------------------------------------------------------------------
template <class TPROXY>
class net::io::messageable::Nproxy : 
// inherited classes)
	virtual public				Imessageable
{
// constructor/destructor)
protected:
			Nproxy() {}
	virtual	~Nproxy() noexcept {}

// public)
public:
			void				set_proxy( TPROXY* _pProxy) noexcept{ std::lock_guard<lockable<>> cs(this->m_pproxy); this->m_pproxy=_pProxy; }
			[[nodiscard]] object_ptr<TPROXY> get_proxy() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<object_ptr<TPROXY>>&>(this->m_pproxy)); return this->m_pproxy; }
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_pproxy;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_pproxy;}

// implementation)
public:
	virtual	result_code			process_message(sMESSAGE& _msg) override;

private:
			lockable<object_ptr<TPROXY>> m_pproxy;
};

template <class TPROXY>
result_code net::io::messageable::Nproxy<TPROXY>::process_message(sMESSAGE& _msg)
{
	// 1) get proxy object
	auto pproxy = get_proxy();

	// check) m_pMessageable가 nullptr이면 끝낸다.
	RETURN_IF(pproxy.empty(), 0);

	// 1) process_message()함수를 호출한다.
	return pproxy->process_message(_msg);
}


}
