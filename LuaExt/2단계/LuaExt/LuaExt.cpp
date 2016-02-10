// LuaExt.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "LuaExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CLuaExtApp

BEGIN_MESSAGE_MAP(CLuaExtApp, CWinApp)
END_MESSAGE_MAP()


// CLuaExtApp 생성

CLuaExtApp::CLuaExtApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CLuaExtApp 개체입니다.

CLuaExtApp theApp;


// CLuaExtApp 초기화

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