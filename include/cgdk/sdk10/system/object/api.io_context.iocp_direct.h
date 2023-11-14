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

#if defined(_IO_APISET_H_)

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 api::io_context_iocp_direct

 iocp를 단순히 i/o의 completion 정보 뿐만 아니라 전체 시스템을 동작시키는
 thread pool로 사용한다. 
 따라서 i/o가 아닌 일반적인 post 역시 iocp에 post 함수를 사용해 실생을 건다.
 자체적인 thread pool보다는 일반적인 처리의 성능은 약간 떨어질수 있으나 i/o
 처리가 최소한의 지연으로 처리할수 있는 장점이 있다.

*///-----------------------------------------------------------------------------
class api::io_context_iocp_direct : public io_context_Niocp
{
// constructor/destructor)
public:
			io_context_iocp_direct() noexcept;
	virtual	~io_context_iocp_direct() noexcept;

public:
			bool				create() noexcept;
	virtual	CGHANDLE			dispose() noexcept override;
	virtual	result_code			destroy() noexcept override;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, Iexecutable* _pexecutable) noexcept;
			void				pop_executable(RESULT& _result, chrono::tick::duration _ticks_wait) noexcept;
			[[nodiscard]] size_t queued_count() const noexcept { return 0; }
};


}
#endif
