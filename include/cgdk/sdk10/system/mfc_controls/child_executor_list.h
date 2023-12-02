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
// CChild_executor_list
//
// 1. CChild_executor_list란!
//    1) Thread List를 출력하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CChild_executor_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_executor_list)

// constructor/destructor)
public:
			CChild_executor_list(executor::manager* _pexecutor=nullptr, CWnd* pnode_parent=nullptr);   // standard constructor
	virtual ~CChild_executor_list();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnLvnItemchangedListExecutor(NMHDR* _pNMHDR, LRESULT* _presult);
	afx_msg void				OnNMDblclkListExecutor(NMHDR* _pNMHDR, LRESULT* _presult);
	afx_msg void				OnEnable(BOOL _is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT _nState, CWnd* _pwnd_other, BOOL _bMinimized);
	//afx_msg	void				OnBnClickedForceException();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateChild(executor::manager* _pexecutor_manager = nullptr, CWnd* _pwnd = nullptr);
			void				SetExecutorManager(executor::manager* _pexecutor_manager);
			void				UpdateExecutorList();
			void				UpdateExecutorList(int _index, chrono::tick::time_point _tick_now);
			void				ClearExecutorList();
			void				EnableControl(BOOL _enable = TRUE);

// implementation) 
protected:
			CListCtrl			m_listctrl_executor;
			object_ptr<executor::manager> m_pmanager_executor;
			lockable<>			m_lockable_manager_executor;
			BOOL				m_is_enable_control;
};


}