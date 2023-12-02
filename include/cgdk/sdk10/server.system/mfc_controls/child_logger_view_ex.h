//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server MFC Controls                            *
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
// CChild_logger_view_ex
//
// 1. CChild_logger_view_ex란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERMFCCONTROL_EXT_CLASS CChild_logger_view_ex : 
	public						CChildDialog,
	public						Ilogger
{
	DECLARE_DYNAMIC(CChild_logger_view_ex)

public:
			CChild_logger_view_ex(CWnd* _pparent = nullptr);
	virtual ~CChild_logger_view_ex();

	struct LOGLIST_INFO
	{
	public:
		std::array<TCHAR, MAX_NAME_LENGTH>	stName;
		CListBox_log*					plist_log;
		object_ptr<Ilog_filter>			plog_filter;

		int								iCount;

		circular_list<sMESSAGE_LOG>		queue_string_0;
		circular_list<sMESSAGE_LOG>		queue_string_1;
		circular_list<sMESSAGE_LOG>*	pqueue_string_stack;
		circular_list<sMESSAGE_LOG>*	pqueue_string_process;
	public:
		LOGLIST_INFO() noexcept : stName{0}, plist_log(nullptr), plog_filter(), iCount(0), queue_string_0{}, queue_string_1{}, pqueue_string_stack(&queue_string_0), pqueue_string_process(&queue_string_1)	{}
	};

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

private:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void				OnEnable(BOOL _is_enable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnLbnSelchangeListLog();
	afx_msg void				OnLbnDblclkListLog();
	afx_msg void				OnLbnErrspaceListLog();
	afx_msg void				OnLbnSelcancelListLog();
	afx_msg void				OnNMThemeChangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);
	afx_msg	LRESULT				OnAddString(WPARAM _wParam, LPARAM _lParam);
	afx_msg void				OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnTcnSelchangingTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnBnClickedNewLog();
	afx_msg void				OnBnClickedEditFilter();
	afx_msg void				OnBnClickedLogClose();
	afx_msg void				OnBnClickedLogSave();
	afx_msg void				OnBnClickedLogSaveSelected();

public:
	virtual	result_code			process_message(sMESSAGE& _msg);
			result_code			on_message_Log(sMESSAGE_LOG& _msg);

public:
			BOOL				CreateChild(const void* _pInfo=nullptr, CWnd* _pwnd=nullptr);

			void				AddString(CListBox_log* _lParam, CListBox_log::ITEM_LOG* _pitem);

			void				AddLogList(const TCHAR* _name, Ilog_filter* _plog_filter, bool _bFocus=false);
			void				RemoveLogList(const TCHAR* _name);
			void				RemoveLogList(int _iTab);
			void				set_log_filter(const TCHAR* _name, Ilog_filter* _plog_filter);
			void				set_log_filter(int iTab, Ilog_filter* _plog_filter);
			void				reset_log_filter(const TCHAR* _name);
			void				reset_log_filter(int iTab);
			void				Clear();

			void				SetTextColor(log_type_t _log_type, COLORREF _ref_color, bool _bold = false) { m_rgb_text[(int)_log_type] = _ref_color; m_is_bold[(int)_log_type] = _bold;}
			COLORREF			GetTextColor(log_type_t _log_type) { return m_rgb_text[(int)_log_type];}
			COLORREF			GetTextBold(log_type_t _log_type) { return m_is_bold[(int)_log_type];}
																		  
			size_t				capacity() const noexcept { return m_capacity; }
			void				capacity(size_t _capacity) noexcept	{ m_capacity = _capacity; }
																		  
			void				SetHorizontalExtent(int _cx);

	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

protected:
			CTabCtrl			m_tabLog;
			CListBox_log		m_list_log;

			struct ITEM_LOG
			{
			public:
				object_ptr<LOG_RECORD> plog_record;
				object_ptr<CListBox_log::ITEM_LOG> pitem;

			public:
				ITEM_LOG(LOG_RECORD* _plog_record, CListBox_log::ITEM_LOG* _pitem) : plog_record(_plog_record), pitem(_pitem)	{}
			};

			lockable<>			m_lockable_queue_string;
			circular_list<object_ptr<LOG_RECORD>> m_pqueue_log_record_queuing;
			circular_list<object_ptr<LOG_RECORD>> m_pqueue_log_record_process;
			size_t				m_capacity;

			lockable<>			m_lockable_log_info;
			std::vector<LOGLIST_INFO> m_vector_log_list;

			int					m_count_log[static_cast<int>(log_type_t::max_)];
			COLORREF			m_rgb_text[static_cast<int>(log_type_t::max_)];
			bool				m_is_bold[static_cast<int>(log_type_t::max_)];
			
protected:
			void				ShowList(int _iTab, int p_iCmdShow);
			void				ProcessAddString(LOG_RECORD* _plog_record, int(&_count_added)[static_cast<size_t>(log_type_t::max_)]);
			void				ProcessAddString(ITEM_LOG&& _item_log);

	virtual void				process_dispose() noexcept override	{}
};


}