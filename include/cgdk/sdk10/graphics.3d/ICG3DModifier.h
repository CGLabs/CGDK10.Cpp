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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. ICG3DModifier는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//
// 2. 주의 사항
//
//-----------------------------------------------------------------------------
class ICG3DModifier : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneComponent,
	public						CGNameable::NString
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DModifier() : m_bEnableModify(true)						{}
	virtual	~ICG3DModifier()											{}

	
// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	// 1) ProcessRender 
			int					Modify(CGMSG_PROCESS_RENDER& _Msg)	{	RETURN_IF(IsModifyDisable(), 0); return ProcessRender(_Msg);}

	// 2) Enable/Disable Flags
			void				SetModifyStatus(bool p_bStatus)			{	m_bEnableModify=p_bStatus;}
			void				EnableModify()							{	m_bEnableModify=true;}
			void				DisableModify()							{	m_bEnableModify=false;}
			void				ToggleModify()							{	m_bEnableModify=!m_bEnableModify;}

			bool				IsModifyEnable() const					{	return	m_bEnableModify;}
			bool				IsModifyDisable() const					{	return	m_bEnableModify==false;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			bool				m_bEnableModify;
};
