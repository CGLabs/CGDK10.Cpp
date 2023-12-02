//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                MFC Controls                               *
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
// CDialogObjectFactoryStatus
//
// 1. CDialogObjectFactoryStatus란!
//    1) Object Factory의 각종 통계정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CDialog_object_factory_status : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_object_factory_status)

// constructor/destructor)
public:
			CDialog_object_factory_status(factory::manager* _pmanager=nullptr, CWnd* pnode_parent=nullptr) noexcept;   // standard constructor
	virtual ~CDialog_object_factory_status() noexcept;

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
private:
	DECLARE_MESSAGE_MAP()

	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pwnd_other, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg void				OnBnClickedButtonPrepare();
	afx_msg void				OnBnClickedButtonShrink();
	afx_msg void				OnBnClickedButtonEnableSustain();
	afx_msg void				OnBnClickedButtonDisableSustain();
	afx_msg void				OnBnClickedCheckEnableSustainManager();
	afx_msg void				OnBnClickedCheckVisibleMemoryBlock();
	afx_msg void				OnBnClickedCheckVisibleSystem();
	afx_msg void				OnBnClickedCheckVisibleUser();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateModaless(factory::manager* _pmanager=nullptr, CWnd* _pparent=nullptr);
			void				SetUpdateInterval(int _Interval);
			void				EnableControl(BOOL _enable=TRUE);

// implementation) 
protected:
			lockable<object_ptr<factory::manager>> m_pmanager;

			std::array<bool, 16> m_bVisiableTypeStatus {};

			CListCtrl			m_listctrl_object_factory;
			CImageList			m_imagelist_object_factory;
			CComboBox			m_combo_update_interval;
	static	int					m_update_inverval;
			CProgressCtrl		m_progressMemoryUsage;


			BOOL				m_is_enable_control;

			void				ClearFactoryList();
			void				UpdateFactoryList();
			void				update_factory_status(int _index);
};


}