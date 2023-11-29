
// chatting_server_dlg.h: 헤더 파일
//

#pragma once


// chatting_server_dlg 대화 상자
class chatting_server_dlg : 
	public						CDialogEx,
	virtual public				Imessageable
{
public:
			chatting_server_dlg(CWnd* pParent = nullptr);

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL				OnInitDialog();

public:
	// Declare) 
	DECLARE_MESSAGE_MAP()

	// 1)  System message
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	// 2) Control events
	afx_msg void				OnBnClickedButtonPoolStatus();
	afx_msg void				OnBnClickedButtonThreadInfo();
	afx_msg void				OnBnClickedButtonChannelNew();
	afx_msg void				OnBnClickedButtonChannelDestroy();
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();

	// 3) Menu events
	afx_msg void				OnSystemServiceStart();
	afx_msg void				OnSystemServiceCancel();
	afx_msg void				OnSystemServiceStop();
	afx_msg void				OnSystemExit();
	afx_msg void				OnSettingConfigures();
	afx_msg void				OnSettingEnginetunning();
	afx_msg void				OnAboutSystemInfo();
	afx_msg void				OnAboutApplicationInfo();

	// 4) CGNetmessage
	afx_msg LRESULT				OnNotifymessage_Update(WPARAM _wparam, LPARAM _lparam);

private:
	// 1) message를 받았을 때 불려지는 함수.
	virtual	result_code			process_message(sMESSAGE& _msg) override;

	// 2) message
			void				OnServiceInitializingPending();
			void				OnServiceDestroyingPending();
			void				OnServiceRunning();
			void				OnServiceStartPending();
			void				OnServiceStopPending();
			void				OnServiceStopped();
			void				OnServiceUpdate();

	// 3) Notified Event
			void				OnChannelAdd		(channel::Igroup* _pchannel);
			void				OnChannelRemove		(channel::Igroup* _pchannel);
			void				OnChannelUpdate		(channel::Igroup* _pchannel);

protected:
	// 1) MFC Resource & Controls
			HICON				m_hIcon;

	// 2) Users & Channels
			CChild_acceptor_control			m_child_acceptor_user;
			lockable<CListCtrl>				m_list_channel;

	// 3) Traffic
			CChild_traffic_info				m_child_traffic_info;

	// 4) Log view
			CChild_logger_view				m_child_log_view;

	// 5) Pool & Thread status
			CDialog_object_factory_status	m_dlg_object_factory_status;
			CDialog_thread_status			m_dlg_thread_status;

	// event)
			struct EVENT_NOTIFY
			{
			public:
				uint32_t					message;
				object_ptr<channel::Igroup>	psource;
			};
			lockable<>						m_lockable_vector_event;
			std::vector<EVENT_NOTIFY>		m_vector_event_queuing;
			std::vector<EVENT_NOTIFY>		m_vector_event_processing;

	// 6) ...
			void				request_service_initialize();
			void				request_service_start();
			void				RequestServiceCancel();
			void				RequestServiceStop();
			void				RequestServiceDestroy();

			void				EnableServerControls(BOOL _bEnable);

public:
			int					List_AddChannel(channel::Igroup* _pchannel);
			void				List_RemoveChannel(channel::Igroup* _pchannel);
			void				List_UpdateChannel(channel::Igroup* _pchannel);
			void				List_UpdateChannel(int _Index);
			void				List_UpdateChannel();

			afx_msg void OnNMRDblclkListChannel(NMHDR *pNMHDR, LRESULT *pResult);
};
