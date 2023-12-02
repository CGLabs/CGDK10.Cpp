#pragma once

class Ctcp_echo_server_dlg : public CDialogEx
{
public:
	Ctcp_echo_server_dlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_ECHO_SERVERMFC_DIALOG };
#endif

	protected:
	virtual void				DoDataExchange(CDataExchange* pDX);
	virtual void				OnOK();
	virtual void				OnCancel();

			int					m_socket_type;
			void				set_socket_type(int _socket_type);
			int					get_socket_type() const { return m_socket_type; }
			void				create_acceptor(int _SocketType);

protected:
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
	virtual BOOL				OnInitDialog();
	afx_msg void				OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonSend1();
	afx_msg void				OnBnClickedButtonSend2();
	afx_msg void				OnBnClickedButtonSend3();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonClosesocketSingle();
	afx_msg void				OnBnClickedButtonDisconnectSingle();
	afx_msg void				OnBnClickedButtonObjectpoolStatus();
	afx_msg void				OnBnClickedButtonThreadStatus();
	afx_msg void				OnBnClickedCheckDisableEcho();
	afx_msg void				OnSystemOptions();
	afx_msg void				OnSystemCGDKLicenseInfo();
	afx_msg void				OnSystemExit();

protected:
			CChild_acceptor_control		m_child_acceptor_control;
			CChild_connective_info		m_child_connective_info;
			CChild_traffic_info			m_child_traffic_info;

			CDialog_object_factory_status m_dlg_object_factory_status;
			CDialog_thread_status		m_dlg_thread_status;
};
