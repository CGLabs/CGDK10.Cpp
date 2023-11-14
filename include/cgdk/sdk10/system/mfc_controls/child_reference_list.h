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
// CCGChildFactoryList
//
// 1. CCGChildFactoryList란!
//    1) Factory의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CChild_reference_list : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_reference_list)

// constructor/destructor)
public:
			CChild_reference_list(Ireferenceable* _prefernece=nullptr, CWnd* pnode_parent = nullptr);   // standard constructor
	virtual ~CChild_reference_list();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL				OnInitDialog();


// MFC) Windows Message
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pwnd_other, BOOL bMinimized);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg void				OnLvnItemchangedListReference(NMHDR *pNMHDR, LRESULT *presult);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateChild(Ireferenceable* _object=nullptr, CWnd* _pwnd=nullptr);
			void				set_object(Ireferenceable* _object);
			void				UpdateReferenceList();
			void				ClearReferenceList();
			void				UpdateReference(int _index);
			void				EnableControl(BOOL _enable=TRUE);

// implementation) 
protected:
			object_ptr<Ireferenceable> m_pobject;
			lockable<>			m_lockable_object;
			CListCtrl			m_listctrl_reference;
			BOOL				m_is_enable_control;
};


}