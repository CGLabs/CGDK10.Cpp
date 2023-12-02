//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

//-----------------------------------------------------------------------------
/**

 @class		Idisposable
 
*/
//-----------------------------------------------------------------------------
class CGDK::Idisposable
{
public:
			Idisposable() noexcept CGNEW_DEBUG_INFO_COLON CGNEW_DEBUG_INFO_INITIALIZE {}
	virtual	~Idisposable() noexcept {}

public:
			class Nno_act;
			class Ndelete;

protected:
	virtual	void				process_dispose() noexcept PURE;

	// Debug)
	CGNEW_DEBUG_INFO_DECLARE
};

class CGDK::Idisposable::Nno_act : virtual public Idisposable
{
public: 
			Nno_act() noexcept {}
			Nno_act(Nno_act&&) noexcept {}
	explicit Nno_act(const Nno_act&) noexcept {}
	virtual ~Nno_act() noexcept {}

	virtual void process_dispose() noexcept override {}

	Nno_act& operator=(const Nno_act&) noexcept { return *this; }
	Nno_act& operator=(const Nno_act&&) noexcept { return *this; }
};

class CGDK::Idisposable::Ndelete : virtual public Idisposable
{
public:
	virtual ~Ndelete() noexcept {}

	virtual void process_dispose() noexcept override { delete this;}
};
