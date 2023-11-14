//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           CG 3D Object Classes                            *
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
// ClearOption
//
// 1. ClearOption
//
//    - RenderTarget은 Render를 하는 최종 Target이다.
//
//
// 2. ClearOption의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
//
//-----------------------------------------------------------------------------
namespace CG3D
{

class CClearOption : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CClearOption(DWORD p_dwClearOption=D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, COLOR p_ClearColor=0xff000000)	{	m_ClearOption=p_dwClearOption; m_ClearColor=p_ClearColor;}
			~CClearOption()												{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Clear Color
			COLOR				GetClearColor() const 					{	return m_ClearColor;}
			void				SetClearColor(COLOR p_ClearColor)		{	m_ClearColor = p_ClearColor;}

	// 2) Clear Option
			DWORD				GetClearOption() const 					{	return m_ClearOption;}
			void				SetClearOption(DWORD p_ClearOption)		{	m_ClearOption = p_ClearOption;}

	// 3) Clear
			void				Clear() const							{	ClearRect(m_ClearOption, m_ClearColor, NULL, 0);}
			void				Clear(const RECT2D* p_pRect) const		{	ClearRect(m_ClearOption, m_ClearColor, p_pRect, 1);}
			void				Clear(const RECT2D* p_pRect, int p_iRectCount) const		{	ClearRect(m_ClearOption, m_ClearColor, p_pRect, p_iRectCount);}
			void				Clear(DWORD p_dwClearOption, COLOR p_colorClear=0xff000000, const RECT2D* p_Rect=NULL, int p_iRectCount=0) const	{	ClearRect(p_dwClearOption, p_colorClear, p_Rect, p_iRectCount);}

			void				ClearZ() const							{	ClearRect(D3DCLEAR_ZBUFFER, m_ClearColor, NULL, 0);}
			void				ClearZ(const RECT2D* p_pRect) const		{	ClearRect(D3DCLEAR_ZBUFFER, m_ClearColor, p_pRect, 1);}
			void				ClearZ(const RECT2D* p_pRect, int p_iRectCount) const		{	ClearRect(D3DCLEAR_ZBUFFER, m_ClearColor, p_pRect, p_iRectCount);}

			void				ClearTarget() const						{	ClearRect(D3DCLEAR_TARGET, m_ClearColor, NULL, 0);}
			void				ClearTarget(const RECT2D* p_pRect=NULL) const	{	ClearRect(D3DCLEAR_TARGET, m_ClearColor, p_pRect, 1);}
			void				ClearTarget(const RECT2D* p_pRect, int p_iRectCount) const{	ClearRect(D3DCLEAR_TARGET, m_ClearColor, p_pRect, p_iRectCount);}



// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Back관련
			COLOR				m_ClearColor;
			DWORD				m_ClearOption;

			void				ClearRect(DWORD p_dwClearOption, COLOR p_colorClear, const RECT2D* p_Rect, int p_iRectCount) const;
};


}