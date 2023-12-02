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
// CChild_connective_connector_control
//
// 1. CChild_connective_connector_control란!
//    1) Connective Connector의 기본 조작용 콘트롤
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connective_connector_control : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connective_connector_control)

public:
			CChild_connective_connector_control(net::io::connective::connector::Ntcp* _pconnective_connector=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connective_connector_control();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnBnClickedButtonConnect1();
	afx_msg void				OnBnClickedButtonConnect10();
	afx_msg void				OnBnClickedButtonConnect100();
	afx_msg void				OnBnClickedButtonConnectMassive();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonDisconnect();

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(net::io::connective::connector::Ntcp* _pconnective_connector=nullptr, CWnd* _pwnd=nullptr);

			void				ConnectN(int p_n);
			void				disconnect(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept;
			void				DisconnectAll();
			void				SetConnectiveConnector(net::io::connective::connector::Ntcp* _pconnective_connector);

			void				SetAddress(const std::string_view _address, int _port);
			void				SetAddress(const std::wstring_view _address, int _port);

// implementation) 
protected:
			lockable<object_ptr<net::io::connective::connector::Ntcp>>	m_pconnectiveConnector;
		#ifdef _UNICODE
			std::wstring		m_str_address;
		#else
			std::string			m_str_address;
		#endif
			int					m_port;
};


}