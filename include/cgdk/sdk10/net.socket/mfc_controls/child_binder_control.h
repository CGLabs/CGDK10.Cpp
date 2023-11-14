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
// CChild_binder_control dialog
//
// 1. CChild_binder_control란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_binder_control : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_binder_control)

// constructor/destructor)
public:
			CChild_binder_control(CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_binder_control();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedCheckBind();
	afx_msg void				OnBnClickedButtonBinderStatus();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::Ibinder* _pbinder=nullptr, CWnd* _pwnd=nullptr);
			void				SetDefaultPort(uint16_t _port);
			void				SetBinder(net::io::Ibinder* _pbinder);
			void				UpdateBinderStatus();

// implementation) 
protected:
			CComboBox			m_comboBindAddress;
			uint16_t			m_port_default;

			CButton				m_checkBind;
			CButton				m_buttonStatus;

			object_ptr<net::io::Ibinder>	m_pBinder;
			lockable<>			m_csBinder;

			bool				Bind();
};


}