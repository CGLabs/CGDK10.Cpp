
// chatting_client_dlg.h: 헤더 파일
//

#pragma once


// Cchatting_client_mfc_dlg 대화 상자
class Cchatting_client_mfc_dlg : public CDialogEx
{
// 생성입니다.
public:
	Cchatting_client_mfc_dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTING_CLIENTMFC_DIALOG };
#endif

// 구현입니다.
protected:
			HICON				m_hIcon;

// 3) MFC Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL				OnInitDialog();
	virtual BOOL				PreTranslateMessage(MSG* pMsg);

// 4) MFC Message map
	DECLARE_MESSAGE_MAP()

private:
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnPaint();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonConnect();
	afx_msg void				OnBnClickedButtonChattingSend();
	afx_msg void				OnEnChangeEditAccountId();
	afx_msg void				OnBnClickedButtonClose();
	afx_msg void				OnBnClickedButtonEnterChannel();

// 5) MFC Controls
private:

// 6) CGCII 
public:
	// - Contorls
			CToolTipCtrl		m_Tooltip;
			CListBox			m_listctrlChatting;
			own_ptr<socket_chatting> m_psocket_chatting;
		
public:
	// - On Functions.
			void				on_request_connect	(socket_chatting* _psocket);
			void				OnConnect			(socket_chatting* _psocket);
			void				on_fail_connect		(socket_chatting* _psocket);
			void				on_disconnect		(socket_chatting* _psocket);
			void				on_notify_enter_channel(socket_chatting* _psocket, CHANNEL_ID _cid, eCHANNEL_OPTION _option, std::string_view _channel_name);
			void				on_send_chatting_message(socket_chatting* _psocket, std::string_view _chatting, std::string_view _nickname);

			void				ShowWindow_Login(BOOL _bEnable);
			void				ShowWindow_Lobby(BOOL _bEnable);
			void				ShowWindow_Chatting(BOOL _bEnable);
};
