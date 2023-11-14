//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Server DB MFC Controls                           *
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
// CCGChildEventList
//
// 1. CCGChildEventList란!
//    1) Event Manager를  설정하여 Event List를 관리하는 관리자.
//    2) 
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERQUERYMFCCONTROL_EXT_CLASS CChild_querier_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_querier_list)

// constructor/destructor)
public:
			CChild_querier_list(query::manager_querier* _pquerier_manager=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_querier_list();

// public) 
public:
			BOOL				CreateChild(query::manager_querier* _pquerier_manager=nullptr, CWnd* p_pWnd=nullptr);

			void				SetDBQuerierManager(query::manager_querier* _pquerier_manager);
			object_ptr<query::manager_querier>	GetDBQuerierManager() const		{	return m_pquerier_manager;}

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);
	afx_msg void				OnBnClickedOpen();
	afx_msg void				OnBnClickedOpenWithParam();
	afx_msg void				OnBnClickedClose();

// implementation) 
protected:
			CListCtrl			m_list_querier;

			std::recursive_mutex m_lockable_querier_manager;
			object_ptr<query::manager_querier>	m_pquerier_manager;

protected:
			void				UpdateQuerierManager();
			void				UpdateQuerier(int p_iIndex);
public:
};


}