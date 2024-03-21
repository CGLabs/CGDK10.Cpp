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
// CChild_traffic_info
//
// 1. CChild_traffic_info란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_traffic_info : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_traffic_info)

// constructor/destructor)
public:
		CChild_traffic_info(const statistics::unit_traffic* _pinfo=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_traffic_info();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void				OnBnClickedCheckSend();
	afx_msg void				OnBnClickedCheckReceive();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pscroll_bar);
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(const statistics::unit_traffic* _pinfo=nullptr, CWnd* _pwnd=nullptr);
			void				UpdateTrafficInfo();

// implementation) 
protected:
			chrono::tick::time_point m_tick_last;

			uint64_t			m_count_sended;
			uint64_t			m_count_received;
			uint64_t			m_count_sendedByte;
			uint64_t			m_count_receivedByte;
			uint64_t			m_count_send_io_call;
			uint64_t			m_count_receive_io_call;

			CStatic_graph		m_graph_traffic;
			CSliderCtrl			m_slider_scale_traffic;

			const statistics::unit_traffic* m_pstatistics;
};


}