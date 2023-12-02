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
// CDialog_connectable_status
//
// 1. CDialog_connectable_status란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CDialog_connectable_status : public CDialog
{
	DECLARE_DYNAMIC(CDialog_connectable_status)

// constructor/destructor)
public:
			CDialog_connectable_status(net::io::Iconnectable* _pconnectable=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CDialog_connectable_status();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonDisconnect();
	afx_msg void				OnBnClickedButtonClose();
	afx_msg void				OnBnClickedButtonReferenceList();
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg	void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pscroll_bar);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedCheckMessageSend();
	afx_msg void				OnBnClickedCheckMessageReceived();
	afx_msg void				OnBnClickedCheckBytesSend();
	afx_msg void				OnBnClickedCheckBytesReceive();
	afx_msg void				OnBnClickedCheckIOSend();
	afx_msg void				OnBnClickedCheckIOReceive();
	afx_msg void				OnBnClickedCheckIOSendEff();
	afx_msg void				OnBnClickedCheckIOReceiveEff();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// implementation) 
private:
			chrono::tick::time_point m_tick_last;

			LONGLONG			m_countMessageSended;
			LONGLONG			m_countMessageReceived;
			LONGLONG			m_countMessageSendedByte;
			LONGLONG			m_countMessageReceivedByte;
			LONGLONG			m_countIOSended;
			LONGLONG			m_countIOReceived;

			CStatic_graph		m_graphMessage_Traffic;
			CSliderCtrl			m_sliderScaleMessage_Traffic;
			CStatic_graph		m_graphBytes_Traffic;
			CSliderCtrl			m_sliderScaleBytes_Traffic;
			CStatic_graph		m_graphIO;
			CSliderCtrl			m_sliderScaleIO;
			CStatic_graph		m_graphIO_Eff;
			CSliderCtrl			m_sliderScaleIO_Eff;

			object_ptr<net::io::Iconnectable>	m_pConnectable;
			lockable<>			m_csConnectable;

			CComboBox			m_comboUpdateInterval;
	static	int					m_s_iUpdateInverval;

			void				set_connectable(net::io::Iconnectable* _pconnectable);
			void				SetUpdateInterval(int p_iInterval);
			void				UpdateConnectableStatus();

public:
			BOOL				CreateModaless(net::io::Iconnectable* _pconnectable, CWnd* p_pParent);
};


}