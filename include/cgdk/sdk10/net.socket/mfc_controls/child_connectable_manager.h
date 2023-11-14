//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                  MFC Controls for Network Socket Classes                  *
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
// CChild_connectable_manager
//
// 1. CChild_connectable_manager란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connectable_manager : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connectable_manager)

// constructor/destructor)
public:
			CChild_connectable_manager(CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connectable_manager();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnBnClickedButtonDisconnect();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonClearGhost();
	afx_msg void				OnLvnItemchangedListConnectable(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListConnectable(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::Iconnectable_manager* p_pConnectableManager=nullptr, CWnd* _pwnd=nullptr);
			void				set_connectable_manager(net::io::Iconnectable_manager* p_pConnectableManager);
			void				UpdateConnectableList();
			void				clear_connectable_list();

// implementation) 
protected:
			CListCtrl			m_list_connectable;

			object_ptr<net::io::Iconnectable_manager>	m_pConnectableManager;
			lockable<>			m_lockable_connectable_manager;

			void				EnableControls(bool p_bStatus);

			void				add_connectable(int _index, net::io::Iconnectable* pconnectable);
			void				UpdateConnectable(int _index);

			object_ptr<net::io::Iconnectable>	VarifyConnectable(net::io::Iconnectable* _pconnectable);
};


}