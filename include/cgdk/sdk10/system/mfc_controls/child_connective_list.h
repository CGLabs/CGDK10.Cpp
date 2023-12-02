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
// CChild_connective_list
//
// 1. CChild_connective_list란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connective_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connective_list)

// constructor/destructor)
public:
			CChild_connective_list(net::io::connective::manager* _pconnective_manager=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connective_list();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnLvnItemchangedListConnective(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListConnective(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::connective::manager* _pconnective_manager=nullptr, CWnd* _pwnd=nullptr);

			void				SetConnectiveManager(net::io::connective::manager* _pconnective_manager);

			void				UpdateConnectiveList();
			void				UpdateConnective(int _index);

// implementation) 
protected:
			CListCtrl			m_list_connective;

			object_ptr<net::io::connective::manager>	m_pmanager_connective;
			std::recursive_mutex m_lockable_manager_connective;

			void				SetConnectiveStatus();
			bool				ListenAcceptor();

			object_ptr<net::io::Iconnective>	VarifyConnective(net::io::Iconnective* _pconnective);
};


}