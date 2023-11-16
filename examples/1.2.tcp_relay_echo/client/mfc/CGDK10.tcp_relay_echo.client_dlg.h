
// tcp_echo_dlg.h: 헤더 파일
//

#pragma once


// Ctcp_relay_echo_client_dlg 대화 상자
class Ctcp_relay_echo_client_dlg : public CDialogEx
{
// 생성입니다.
public:
	Ctcp_relay_echo_client_dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCP_ECHOWINDOWSMFC_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual BOOL				OnInitDialog();
	virtual void				DoDataExchange(CDataExchange* pDX);
	virtual BOOL				PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	afx_msg void				OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnPaint();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnSystemExit();
	afx_msg void				OnAboutCGDKinfo();
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonConnect();
	afx_msg void				OnBnClickedButtonConnect1();
	afx_msg void				OnBnClickedButtonConnect10();
	afx_msg void				OnBnClickedButtonConnect100();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonDisconnect();
	afx_msg void				OnCbnSelchangeComboMessageSize();
	afx_msg void				OnBnClickedButtonSingleSend();
	afx_msg void				OnBnClickedButtonPool();
	afx_msg void				OnBnClickedButtonThread();
	afx_msg void				OnBnClickedButtonClosesocketSingle();
	afx_msg void				OnBnClickedButtonClosesocketAll();

private:
			CComboBox			m_comboMessageSize;
			CToolTipCtrl		m_ctrl_tooltip;

public:
	// 1) Contorls
			CChild_connective_info		m_child_connective_info;
			CChild_traffic_info			m_child_traffic_info;
			CDialog_object_factory_status m_dlg_object_factory_status;
			CDialog_thread_status		m_dlg_thread_status;
			
public:
	// 5) 조작함수.
			void				ReadServerAddress();
};
