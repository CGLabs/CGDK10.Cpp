#pragma once

class Cupdate_service_server_mfc_dlg : 
	public						CDialogEx,
	virtual public				Imessageable
{
public:
	Cupdate_service_server_mfc_dlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_SERVICESERVERMFC_DIALOG };
#endif

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);
	virtual BOOL				OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()

	// 1) system message
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	// 2) control events
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonPoolStatus();
	afx_msg void				OnBnClickedButtonThreadInfo();

	// 3) menu
	afx_msg void				OnSystemServiceStart();
	afx_msg void				OnSystemServiceCancel();
	afx_msg void				OnSystemServiceStop();
	afx_msg void				OnSystemExit();
	afx_msg void				OnSettingConfigures();
	afx_msg void				OnSettingEnginetunning();
	afx_msg void				OnAboutSystemInfo();

	// 4) CGDK.message
	afx_msg LRESULT				on_notify_message_update(WPARAM _wParam, LPARAM _lParam);

	// 5) ...
	afx_msg void				OnLvnItemchangedListSocket(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void				OnLvnItemchangedListUpdatableResource(NMHDR* pNMHDR, LRESULT* pResult);

private:
	// 1) message를 받았을 때 불려지는 함수.
	virtual result_code			process_message(sMESSAGE& _msg) override;

	// 2) message
			void				on_service_initializing_pending();
			void				on_service_destroying_pending();
			void				on_service_running();
			void				on_service_start_pending();
			void				on_service_stop_pending();
			void				on_service_stopped();
			void				on_service_update();

protected:
	// 1) MFC resource & controls
			HICON				m_hIcon;

	// 2) logger view
			CChild_logger_view	m_child_logger_view;

	// 3) factory & thread status
			CDialog_object_factory_status m_dlg_factory_status;
			CDialog_thread_status m_dlg_thread_status;

	// 4) other mfc controls
			CChild_acceptor_control m_child_acceptor_socket_peer;

	// 5) service
			void				request_service_initialize();
			void				request_service_start();
			void				request_service_cancel();
			void				request_service_stop();
			void				request_service_destroy();
			void				enable_server_controls(BOOL _bEnable);

public:
			struct EVENT_SOCKET_USER_NOTIFY
			{
			public:
				uint32_t					message;
				object_ptr<socket_peer>		psource;
			};
			lockable<CListCtrl>	m_listctrl_socket_peer;
			lockable<>			m_cs_vector_event_socket_peer;
			std::vector<EVENT_SOCKET_USER_NOTIFY> m_vector_event_socket_peer_queuing;
			std::vector<EVENT_SOCKET_USER_NOTIFY> m_vector_event_socket_peer_processing;
			int					list_add_socket_peer(socket_peer* _psocket_peer);
			void				list_remove_socket_peer(socket_peer* _psocket_peer);
			void				list_update_socket_peer(socket_peer* _psocket_peer);
			void				list_update_socket_peer(int _index);
			void				list_update_event_socket_peer();

			struct EVENT_UPDATABLE_RESOURCE_NOTIFY
			{
			public:
				uint32_t					message;
				object_ptr<socket_peer>		psource;
			};
			lockable<CListCtrl>	m_listctrl_updatable_resource;
			lockable<>			m_cs_vector_event_updatable_resource;
			std::vector<EVENT_UPDATABLE_RESOURCE_NOTIFY> m_vector_event_updatable_resource_queuing;
			std::vector<EVENT_UPDATABLE_RESOURCE_NOTIFY> m_vector_event_updatable_resource_processing;
			int					list_add_updatable_resource(socket_peer* _psocket_peer);
			void				list_remove_updatable_resource(socket_peer* _psocket_peer);
			void				list_update_updatable_resource(socket_peer* _psocket_peer);
			void				list_update_updatable_resource(int _index);
			void				list_update_event_updatable_resource();


};
