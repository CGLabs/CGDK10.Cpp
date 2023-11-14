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
// CChild_schedulable_list
//
// 1. CChild_schedulable_list란!
//    1) Thread List를 출력하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CChild_schedulable_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_schedulable_list)

// constructor/destructor)
public:
			CChild_schedulable_list(schedulable::manager* _pexecutor_schedulable=nullptr, CWnd* pnode_parent=nullptr);   // standard constructor
	virtual ~CChild_schedulable_list();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnLvnItemchangedListSchedulable(NMHDR *pNMHDR, LRESULT *presult);
	afx_msg void				OnNMDblclkListThread(NMHDR *pNMHDR, LRESULT *presult);
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pwnd_other, BOOL bMinimized);
	afx_msg	void				OnBnClickedUnregisterSchedulable();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateChild(schedulable::manager* _pexecutor_schedulable=nullptr, CWnd* _pwnd=nullptr);
			void				SetSchedulableList(schedulable::manager* _pschedulable_manager);
			void				UpdateSchedulableList();
			void				UpdateSchedulableList(int _index, chrono::tick::time_point _tick_now);
			void				ClearSchedulableList();
			void				EnableControl(BOOL _enable = TRUE);

// implementation) 
protected:
			CListCtrl			m_list_schedulable;
			object_ptr<schedulable::manager> m_pexecutor_schedulable;
			lockable<>			m_lockable_manager_thread;
			BOOL				m_is_enable_control;
};


}