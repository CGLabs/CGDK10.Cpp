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

   executor::Iio_context
 

*///-----------------------------------------------------------------------------
class executor::Iio_context :
	virtual public				executor::Iqueue
{
public:
	virtual	~Iio_context() noexcept	{}

public:
#if defined(_WIN32)
	virtual	bool				attach(CGHANDLE _handle) PURE;
	virtual	bool				detach(CGHANDLE _handle) noexcept PURE;
#elif defined(__ANDROID__) || defined(__linux__)
	virtual	bool				attach(CGHANDLE _handle, Iexecutable* _pexecutable, uint32_t _option = 0) PURE;
	virtual	bool				detach(CGHANDLE _handle) noexcept PURE;
	virtual	bool				set_event(CGHANDLE _handle, uint32_t _flag_event, Iexecutable* _pexecutable = nullptr) noexcept PURE;
#endif
	[[nodiscard]] virtual CGHANDLE handle() const noexcept PURE;
	virtual void				execute_all() PURE;


};


}