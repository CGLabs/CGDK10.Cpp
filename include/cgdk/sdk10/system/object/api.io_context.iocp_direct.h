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

 iocp�� �ܼ��� i/o�� completion ���� �Ӹ� �ƴ϶� ��ü �ý����� ���۽�Ű��
 thread pool�� ����Ѵ�. 
 ���� i/o�� �ƴ� �Ϲ����� post ���� iocp�� post �Լ��� ����� �ǻ��� �Ǵ�.
 ��ü���� thread pool���ٴ� �Ϲ����� ó���� ������ �ణ �������� ������ i/o
 ó���� �ּ����� �������� ó���Ҽ� �ִ� ������ �ִ�.

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
