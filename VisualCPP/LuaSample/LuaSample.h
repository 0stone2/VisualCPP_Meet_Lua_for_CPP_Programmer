
// LuaSample.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLuaSampleApp:
// �� Ŭ������ ������ ���ؼ��� LuaSample.cpp�� �����Ͻʽÿ�.
//

class CLuaSampleApp : public CWinApp
{
public:
	CLuaSampleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CLuaSampleApp theApp;