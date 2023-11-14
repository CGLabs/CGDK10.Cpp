//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server MFC Controls                            *
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
// CChild_event_list
//
// 1. CChild_event_list란!
//    1) Event Manager를  설정하여 Event List를 관리하는 관리자.
//    2) 
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERMFCCONTROL_EXT_CLASS CChild_event_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_event_list)

// constructor/destructor)
public:
			CChild_event_list(time_event::entity_manager* _pentity_manager = nullptr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CChild_event_list();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedButtonDeleteEvent();
	afx_msg void				OnBnClickedButtonNewEvent();
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnBnClickedCheckDeleteDoneEvent();
	afx_msg void				OnBnClickedButtonSuspendEvent();
	afx_msg void				OnBnClickedButtonResumeEvent();
	afx_msg	void				OnNMDblclkListEvent(NMHDR* pNMHDR, LRESULT *pResult);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateChild(time_event::entity_manager* _pentity_manager=nullptr, CWnd* _pwnd=nullptr);
			void				SetEventManager(time_event::entity_manager* _pentity_manager);
			object_ptr<time_event::entity_manager>	GetEventManager() const { return m_pentity_manager;}
			void				UpdateEventManager();
			void				EnableControl(BOOL _enable=TRUE);

// implementation) 
protected:
			CListCtrl			m_listctrlEvent;
			object_ptr<time_event::entity_manager>	m_pentity_manager;
			lockable<>			m_cs_event_manager;
			BOOL				m_bEnableControl;

protected:
			void				UpdateEvent(int p_iIndex);
};


}