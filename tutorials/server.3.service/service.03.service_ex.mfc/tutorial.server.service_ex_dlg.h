
// tutorial.server.service_ex_dlg.h: 헤더 파일
//

#pragma once


// Ctutorial_server_service_ex_dlg 대화 상자
class Ctutorial_server_service_ex_dlg : 
	public						CDialogEx,
	virtual public				Imessageable
{
// constructor/destructor)
public:
	Ctutorial_server_service_ex_dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// MFC virtual function
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL				OnInitDialog();

// MFC message)
public:
	DECLARE_MESSAGE_MAP()

	// 1) system Message
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();

	// 2) control events
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonPoolStatus();
	afx_msg void				OnBnClickedButtonThreadInfo();
	afx_msg void				OnBnClickedButtonLicenseInfo();

	// 3) menu events
	afx_msg void				OnSystemStart();
	afx_msg void				OnSystemCancel();
	afx_msg void				OnSystemStop();
	afx_msg void				OnSystemExit();

	// 4) CGDK.message
	afx_msg LRESULT				OnNotifymessage_Update(WPARAM _wParam, LPARAM _lParam);

//  CGMessage) 
private:
	// 1) Message를 받았을 때 불려지는 함수.
	virtual result_code			process_message(sMESSAGE& _msg) override;

	// 2) Message
			void				OnServiceInitializingPending();
			void				OnServicedestroyingPending();
			void				OnServiceRunning();
			void				OnServiceStartPending();
			void				OnServiceStopPending();
			void				OnServiceStopped();
			void				OnServiceUpdate();

			void				OnSocketConnect(socket_tcp_user* _psocket);
			void				OnSocketDisconnect(socket_tcp_user* _psocket);
			void				OnSocketUpdate(socket_tcp_user* _psocket);

// implementation) 
protected:
			HICON m_hIcon;
			
			CChild_connector_control		m_child_socket;
			CChild_acceptor_control			m_child_acceptor_user;

			CChild_traffic_info				m_child_traffic_info;

			CChild_logger_view				m_child_logger_view;

			CDialog_object_factory_status	m_dlg_factory_status;
			CDialog_thread_status			m_dlg_thread_status;

			void				request_service_initialize();
			void				request_service_start();
			void				request_service_stop();
			void				request_service_destroy();
			void				request_service_cancel();
			void				enable_server_controls(BOOL _bEnable);
};
