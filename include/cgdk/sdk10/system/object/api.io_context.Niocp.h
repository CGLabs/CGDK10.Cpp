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

	api::io_context_Niocp
 

*///-----------------------------------------------------------------------------
class api::io_context_Niocp :
	virtual public				object::Idestroyable
{
// constructor/destructor)
public:
			io_context_Niocp() noexcept;
	virtual	~io_context_Niocp() noexcept;

// public)
public:
	struct RESULT
	{
	public:
		uintptr_t				per_handle_key {};
		EXECUTABLE_NODE*		pexecutable {nullptr};
		intptr_t				result_ {};
		uint32_t				bytes_transfered {};

	public:
		[[nodiscard]] bool		is_valid() const noexcept { return pexecutable != nullptr;}
		[[nodiscard]] intptr_t	result() const noexcept { return result_; }
		Iexecutable*			executable() const noexcept { return static_cast<Iexecutable*>(pexecutable);}
		[[nodiscard]] size_t	param() const noexcept { return static_cast<size_t>(bytes_transfered); }
	};

public:
			[[nodiscard]] size_t	attached_count() const noexcept { return m_count_attached;}
			[[nodiscard]] CGHANDLE	handle() const noexcept { return m_handle_iocp;}

			bool				create() noexcept;
	virtual	CGHANDLE			dispose() noexcept;
	virtual	result_code			destroy() noexcept override;

			bool				cancel_io() noexcept;
	static	bool				cancel_io(CGHANDLE _handle) noexcept;

			bool				attach(CGHANDLE _handle) noexcept;
			bool				detach(CGHANDLE _handle) noexcept;

// implementation)
protected:
			std::atomic<CGHANDLE>	m_handle_iocp;
			std::atomic<CGHANDLE>	m_handle_iocp_created;
			std::atomic<size_t>		m_count_attached;
};


}
#endif
