//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               MFC Controls                                *
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
// CCGChildLogView
//
// 1. CCGChildLogView란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGListBox : public CListBox
{
	DECLARE_DYNAMIC(CCGListBox)

// constructor/destructor)
public:
			CCGListBox() noexcept;
	virtual ~CCGListBox() noexcept;

// public) 
public:
			int					AddString(LPCTSTR lpszItem);
			int					AddString(LPCTSTR lpszItem, COLORREF rgb);
			int					InsertString(int nIndex, LPCTSTR lpszItem);
			int					InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb);
			void				SetItemColor(int nIndex, COLORREF rgb);

// MFC) Virtual Functions
protected:
	virtual BOOL				PreCreateWindow(CREATESTRUCT& cs);
	virtual void				DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void				MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

// MFC) Windows Message
protected:
	DECLARE_MESSAGE_MAP()


};


}