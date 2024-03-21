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
#include "afxcmn.h"

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CDialog_reference_status
//
// 1. CDialog_reference_status란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CDialog_CGDK_component_info : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_CGDK_component_info)
public:
			CDialog_CGDK_component_info(CWnd* pnode_parent = nullptr);
			CDialog_CGDK_component_info(const std::vector<CGDK::sCOMPONENT_INFO>& _vector_components, CWnd* pnode_parent = nullptr);
	virtual ~CDialog_CGDK_component_info();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CGDK_VERSION_INFO };
#endif

			BOOL				CreateModaless(const std::vector<CGDK::sCOMPONENT_INFO>& _vector_components, CWnd* _pparent=nullptr);
			void				EnableControl(BOOL _enable=TRUE);
			void				SetComponentInfo(const std::vector<CGDK::sCOMPONENT_INFO>& _vector_components) noexcept { m_pvector_components = &_vector_components; }


protected:
	DECLARE_MESSAGE_MAP()
	virtual void				DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL				OnInitDialog() override;

			const std::vector<CGDK::sCOMPONENT_INFO>* m_pvector_components;

			CListCtrl			m_listctrl_components;
			BOOL				m_is_enable_control;

			CRichEditCtrl		m_rich_explanation_1;
			CRichEditCtrl		m_rich_explanation_2;
			CRichEditCtrl		m_rich_explanation_3;
};


}