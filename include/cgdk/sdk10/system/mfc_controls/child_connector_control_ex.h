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
// CChild_connector_control_ex
//
// 1. CChild_connector_control_ex란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connector_control_ex : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connector_control_ex)

// constructor/destructor)
public:
			CChild_connector_control_ex(net::io::Iconnect_requestable* _pConnector=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connector_control_ex();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
private:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnBnClickedCheckConnect();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::Iconnect_requestable* _pConnector=nullptr, uint16_t _port=10000, CWnd* _pwnd=nullptr);
			void				SetConnector(net::io::Iconnect_requestable* _pConnector);

			void				UpdateConnectorStatus();

// implementation) 
protected:
			object_ptr<net::io::Iconnect_requestable> m_pconnector;
			lockable<>			m_csConnector;

			CComboBox			m_comboBindAddress;
			uint16_t			m_port_default = 0;
			uint16_t			m_port_bind = 0;

			eSOCKET_STATE		m_state_pre = eSOCKET_STATE::CLOSED;
};


}