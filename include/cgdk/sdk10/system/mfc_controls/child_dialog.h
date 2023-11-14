//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               MFC Controls                                *
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
// CChildDialog
//
// 1. CChildDialog¶õ!
//    1) 
//    2) 
// 
// 
//-----------------------------------------------------------------------------
#define	ORIGIN_CENTER_X	0x01
#define	ORIGIN_LEFT		0x02
#define	ORIGIN_RIGHT	0x03
#define	ORIGIN_FRONT	0x04
#define	ORIGIN_REAR		0x05

#define	ORIGIN_CENTER_Y	0x10
#define	ORIGIN_TOP		0x20
#define	ORIGIN_BOTTOM	0x30
#define	ORIGIN_UPON		0x40
#define	ORIGIN_BELOW	0x50

class CGMFCCONTROL_EXT_CLASS CChildDialog : public CGDIALOG
{
	DECLARE_DYNAMIC(CChildDialog)

// constructor/destructor)
public:
			CChildDialog(UINT nIDTemplate, CWnd* pnode_parent = nullptr);
	virtual ~CChildDialog();

// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();

// public) 
public:
			void				MoveToCenter(CWnd* _pwnd, int _off_x = 0, int _off_y = 0);
			void				Move(int _off_x, int _off_y);
			void				Move(int _off_x, int _off_y, int _origin, CWnd* _pwnd);
			void				Resize(int _off_x, int _off_y);
			void				AddTargetWnd(CWnd* _pwnd);
			void				RemoveTargetWnd(CWnd* _pwnd);
			void				SetUpdateInterval(int _Interval);

// implementation) 
protected:
			circular_list<CWnd*> m_list_wnd_target;
			void				SendMessageToTarget(WPARAM _message, LPARAM _lParam);



};


}