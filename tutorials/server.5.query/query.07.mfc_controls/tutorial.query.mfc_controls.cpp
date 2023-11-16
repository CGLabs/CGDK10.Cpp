
// tutorial.query.mfc_controls.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "tutorial.query.mfc_controls.h"
#include "tutorial.query.mfc_controls.dlg.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CtutorialquerymfccontrolsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtutorialquerymfccontrolsApp 생성

CtutorialquerymfccontrolsApp::CtutorialquerymfccontrolsApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CtutorialquerymfccontrolsApp theApp;

BOOL CtutorialquerymfccontrolsApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));

	CtutorialquerymfccontrolsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}

