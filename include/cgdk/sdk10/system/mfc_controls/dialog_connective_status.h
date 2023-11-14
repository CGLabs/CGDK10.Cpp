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
// CDialogAcceptorStatus
//
// 1. CDialogAcceptorStatus란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CDialog_connective_status : public CDialog
{
	DECLARE_DYNAMIC(CDialog_connective_status)

// constructor/destructor)
public:
			CDialog_connective_status(net::io::connective::manager* p_pmangerAcceptor=nullptr, CWnd* pParent=nullptr);	// standard constructor
			CDialog_connective_status(net::io::Iconnective* _pconnective, CWnd* pParent=nullptr);
	virtual ~CDialog_connective_status();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

public:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeConnective();
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// implementation) 
protected:
			CComboBox			m_comboUpdateInterval;
			CComboBox			m_comboConnective;
	static int					m_iUpdateInverval;
			CChild_connectable_manager	m_ChildConnectableManager;

			object_ptr<net::io::connective::manager> m_pmangerConnective;
			object_ptr<net::io::Iconnective> m_pconnective;
			lockable<>			m_csConnective;
		

			void				SetConnective(net::io::Iconnective* _pconnective);
			void				ResetConnectiveList();
			void				SetUpdateInterval(int p_iInterval);
			void				UpdateConnectiveStatus();

			void				SetViewStatus(bool p_bStatus);

public:
			BOOL				CreateModaless(net::io::connective::manager* p_pmangerAcceptor=nullptr, CWnd* p_pParent=nullptr);
			BOOL				CreateModaless(net::io::Iconnective* _pconnective=nullptr, CWnd* p_pParent=nullptr);
};


}