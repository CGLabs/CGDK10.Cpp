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
// CDialog_reference_status
//
// 1. CDialog_reference_status란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CDialog_reference_status : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_reference_status)

// constructor/destructor)
public:
			CDialog_reference_status(Ireferenceable* _prefernece=nullptr, CWnd* _pnode_parent = nullptr);   // standard constructor
	virtual ~CDialog_reference_status();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// public) 
public:
			BOOL				CreateModaless(Ireferenceable* _prefernece=nullptr, CWnd* _pparent=nullptr);
			void				EnableControl(BOOL _enable=TRUE);

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pwnd_other, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// implementation) 
protected:
			CComboBox			m_combo_update_interval;
	static int					m_update_inverval;
			CChild_reference_list m_child_refernece_list;
			lockable<object_ptr<Ireferenceable>> m_pobject;

			void				set_object(Ireferenceable* _prefernece);
			void				reset_object();
			void				SetUpdateInterval(int _Interval);
			void				UpdateThreadStatus();
			void				SetViewStatus(bool _enable_sustain);
};


}