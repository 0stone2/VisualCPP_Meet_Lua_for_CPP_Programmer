// LuaExt.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "LuaExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CLuaExtApp

BEGIN_MESSAGE_MAP(CLuaExtApp, CWinApp)
END_MESSAGE_MAP()


// CLuaExtApp ����

CLuaExtApp::CLuaExtApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CLuaExtApp ��ü�Դϴ�.

CLuaExtApp theApp;


// CLuaExtApp �ʱ�ȭ

BOOL CLuaExtApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

int luaopen_LuaExt(lua_State *pLuaState)
{
	BOOL bSuccess{ FALSE };

	__try {
		if (NULL == pLuaState) __leave;

		lua_register(pLuaState, "DbgString", DbgString);
		lua_register(pLuaState, "SumAndAverage", SumAndAverage);

		bSuccess = TRUE;
	}
	__finally {

	}

	lua_pushnumber(pLuaState, pLuaState);
	return 1;
}

int DbgString(lua_State *pLuaState)
{
	/* get number of arguments */
	int nTop{ 0 };
	const char *szDbgString{ NULL };
	wchar_t		wszDbgString[MAX_PATH]{ 0, };

	__try {
		nTop = lua_gettop(pLuaState);
		if (1 != nTop) __leave;
		if (!lua_isstring(pLuaState, nTop)) __leave;

		szDbgString = lua_tostring(pLuaState, nTop);

		int nLen = MultiByteToWideChar(CP_UTF8, 0, szDbgString, strlen(szDbgString), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, szDbgString, strlen(szDbgString), wszDbgString, nLen);

		OutputDebugStringW(wszDbgString);
	}
	__finally {

	}

	return 0;
}

int SumAndAverage(lua_State *pLuaState)
{
	/* get number of arguments */
	int nTop{ 0 };
	const char *szDbgString{ NULL };
	int nStartVar{ 0 };
	int nStopVar{ 0 };
	int nSum{ 0 };
	int nAverage{ 0 };
	int nNumberOfReternValues{ 0 };

	__try {
		nTop = lua_gettop(pLuaState);
		if (2 != nTop) __leave;
		if (!lua_isnumber(pLuaState, nTop)) __leave;
		if (!lua_isnumber(pLuaState, nTop - 1)) __leave;

		nStopVar = lua_tonumber(pLuaState, nTop);
		nStartVar = lua_tonumber(pLuaState, nTop - 1);

		for (int nIndex = nStartVar; nIndex <= nStopVar; nIndex++)
		{
			nSum += nIndex;
		}

		nAverage = nSum / (nStopVar - nStartVar + 1);
		lua_pushnumber(pLuaState, nSum);
		lua_pushnumber(pLuaState, nAverage);
		nNumberOfReternValues = 2;
	}
	__finally {

	}

	return nNumberOfReternValues;
}