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
// CCGDialogConnectableStatus
//
// 1. CCGDialogConnectableStatus란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CDialog_thread_status : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_thread_status)

// constructor/destructor)
public:
			CDialog_thread_status(api::manager_thread* _pthread_manager=nullptr, executor::manager* _pexecutor_manager=nullptr, system_executor* _pDefaultExecutor=nullptr, CWnd* _pparent = nullptr);   // standard constructor
	virtual ~CDialog_thread_status();


// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// public) 
public:
			BOOL				CreateModaless(api::manager_thread* _pthread_manager=nullptr, executor::manager* _pexecutor_manager=nullptr, system_executor* _pDefaultExecutor=nullptr, CWnd* _pparent=nullptr);
			void				EnableControl(BOOL _enable=TRUE);

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT _nState, CWnd* _pWndOther, BOOL _bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR _nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);
	afx_msg void				OnTcnSelchangeTabMenu(NMHDR* _pNMHDR, LRESULT *presult);
	afx_msg void				OnTcnSelchangingTabMenu(NMHDR* _pNMHDR, LRESULT *presult);

// implementation) 
protected:
			CComboBox			m_combo_update_interval;
	static int					m_update_inverval;

			CTabCtrl			m_tabMenu;

			CChild_thread_list	m_child_thread_list;
			CChild_executor_list m_child_executor_list;
			CChild_schedulable_list m_child_schedulable_list;
			lockable<object_ptr<api::manager_thread>>	m_pmanager_thead;
			object_ptr<executor::manager>				m_pmanager_executor;
			system_executor*							m_pdefault_executor;

			void				SetManager(api::manager_thread* _pthread_manager, executor::manager* _pexecutor_manager, system_executor* _pDefaultExecutor);
			void				resetThreadList();
			void				SetUpdateInterval(int _Interval);
			void				UpdateThreadStatus();
						void				SetViewStatus(bool _enable_sustain);
};


}