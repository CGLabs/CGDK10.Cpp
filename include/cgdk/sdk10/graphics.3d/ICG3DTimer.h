//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. ICG3DTimer´Â...
//    1) 
//    2) 
//    3) 
//
//-----------------------------------------------------------------------------
class ICG3DTimer : 
// ****************************************************************************
// Inheritied from) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneComponent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICG3DTimer()		{}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	// 1) Time Add/Set/Reset
	virtual	float				GetTime() const PURE;
	virtual	void				AddTime(float p_fTime=1.0f) PURE;
	virtual	void				SetTime(float p_fTime=0.0f) PURE;
	virtual	void				ResetTime() PURE;

	// 2) Blend Factor
	virtual float				GetBlendFactor() const PURE;
	virtual	void				SetBlendFactor(float p_fSub) PURE;
};
