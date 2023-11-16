#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"

class CupdateserviceservermfcApp : public CWinApp
{
public:
	CupdateserviceservermfcApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CupdateserviceservermfcApp theApp;
