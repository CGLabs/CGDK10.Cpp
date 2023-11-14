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
// CCGChildAcceptorList
//
// 1. CCGChildAcceptorList란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_acceptor_control : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_acceptor_control)

// constructor/destructor)
public:
			CChild_acceptor_control(net::io::connective::Iacceptor* p_pAcceptor=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_acceptor_control();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedCheckAcceptorStartStop();
	afx_msg void				OnBnClickedButtonAcceptorStatus();
	afx_msg void				OnBnClickedButtonAcceptorDisconnectAll();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::connective::Iacceptor* p_pAcceptor=nullptr, CWnd* _pwnd=nullptr);

			void				SetDefaultPort(uint16_t _port);
			void				SetConnective(net::io::Iconnective* _pconnective);
			void				SetAcceptor(net::io::connective::Iacceptor* p_pAcceptor);
			void				UpdateAcceptorStatus();

			void				EnableControl(BOOL _enable=TRUE);

			object_ptr<net::io::connective::Iacceptor>	GetAcceptor();

// implementation) 
protected:
			CComboBox			m_comboBindAddress;
			uint16_t			m_port_default;

			CEdit				m_editBindPort;
			CButton				m_checkReady;
			CButton				m_buttonStatus;
			CButton				m_buttonDisconnectAll;

			object_ptr<net::io::connective::Iacceptor>	m_pAcceptor;
			lockable<>			m_csAcceptor;
			eSOCKET_STATE		m_statusPre;

			BOOL				m_bEnableControl;

			bool				ListenAcceptor();
			
			CDialog_connective_status	m_dlgConnectiveStatus;
};


}