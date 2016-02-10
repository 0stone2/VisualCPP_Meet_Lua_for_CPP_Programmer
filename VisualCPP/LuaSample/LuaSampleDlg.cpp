
// LuaSampleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "LuaSample.h"
#include "LuaSampleDlg.h"
#include "afxdialogex.h"


#define __LUA_532__
//#define __LUA_515__

#if defined(__LUA_532__)
	#include "C:/Script/Lua/5.3.2/Library/include/lua.hpp"
	#include "C:/Script/Lua/5.3.2/Library/include/luaconf.h"

	#if defined(_WIN64)
		#pragma comment(lib,"C:/Script/Lua/5.3.2/Library/x64/lua53.lib")
	#else
		#pragma comment(lib,"C:/Script/Lua/5.3.2/Library/x86/lua53.lib")
	#endif
#elif defined(__LUA_515__)
	#include "C:/Script/Lua/5.1.5/Library/include/lua.hpp"
	#include "C:/Script/Lua/5.1.5/Library/include/luaconf.h"

	#if defined(_WIN64)
		#pragma comment(lib,"C:/Script/Lua/5.1.5/Library/x64/lua51.lib")
	#else
		#pragma comment(lib,"C:/Script/Lua/5.1.5/Library/x86/lua51.lib")
	#endif
#endif

void DumpLuaStack(lua_State *pLuaState);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLuaSampleDlg 대화 상자



CLuaSampleDlg::CLuaSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LUASAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLuaSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLuaSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXAMPLE01_BUTTON, &CLuaSampleDlg::OnBnClickedExample01Button)
	ON_BN_CLICKED(IDC_EXAMPLE02_BUTTON, &CLuaSampleDlg::OnBnClickedExample02Button)
	ON_BN_CLICKED(IDC_EXAMPLE03_BUTTON, &CLuaSampleDlg::OnBnClickedExample03Button)
	ON_BN_CLICKED(IDC_EXAMPLE04_BUTTON, &CLuaSampleDlg::OnBnClickedExample04Button)
	ON_BN_CLICKED(IDC_EXAMPLE05_BUTTON, &CLuaSampleDlg::OnBnClickedExample05Button)
	ON_BN_CLICKED(IDC_EXAMPLE06_BUTTON, &CLuaSampleDlg::OnBnClickedExample06Button)
	ON_BN_CLICKED(IDC_EXAMPLE07_BUTTON, &CLuaSampleDlg::OnBnClickedExample07Button)
END_MESSAGE_MAP()


// CLuaSampleDlg 메시지 처리기

BOOL CLuaSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLuaSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLuaSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLuaSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 1 장 - C에서 Lua 호출하기
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 1 - 루아 스크립트 파일 실행하기
//
void CLuaSampleDlg::OnBnClickedExample01Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };

	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		if (luaL_dofile(pLuaState, "./Script/Sample01.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 2 - 루아 전역 변수 조작하기
//
void CLuaSampleDlg::OnBnClickedExample02Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };
	const char *	szWelcomMessage{ NULL };
	const char *	szWhoamI{ NULL };


	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		if (luaL_dofile(pLuaState, "./Script/Sample02.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}

		// Lua의 전역 변수 읽어 오기
		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n\n**** Lua 전역 변수 변경 전****\n");
		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);


		lua_pushstring(pLuaState, "I am Sample02.lua");
		lua_setglobal(pLuaState, "szWhoamI");

		lua_pushstring(pLuaState, "Hello World^^");
		lua_setglobal(pLuaState, "szWelcomMessage");



		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("****Lua 전역 변수 변경 후****\n");
		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);

		szWelcomMessage = lua_tostring(pLuaState, 1);
		szWhoamI = lua_tostring(pLuaState, 2);
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 3 - 루아 함수 호출하기
//
void CLuaSampleDlg::OnBnClickedExample03Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };
	const char *	szWelcomMessage{ NULL };
	const char *	szWhoamI{ NULL };
	const char *	szReturn1{ NULL };
	int				bReturn2{ FALSE };

	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		if (luaL_dofile(pLuaState, "./Script/Sample03.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}

		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 인자와 리턴값이 없는 함수 호출하기
		//
		lua_getglobal(pLuaState, "myfunc_1");

		DumpLuaStack(pLuaState);

		if (lua_pcall(pLuaState, 0, 0, 0) != 0) {
			sprintf_s(szDbgString, "error running function `f': %s\n", lua_tostring(pLuaState, -1));
			OutputDebugStringA(szDbgString);
			__leave;
		}


		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n****Lua 함수 func_1 호출 후****\n");
		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 인자는 없지만 리턴값이 하나인 함수 호출하기
		//
		lua_getglobal(pLuaState, "myfunc_2");

		if (lua_pcall(pLuaState, 0, 1, 0) != 0) {
			sprintf_s(szDbgString, "error running function `f': %s\n", lua_tostring(pLuaState, -1));
			OutputDebugStringA(szDbgString);
			__leave;
		}

		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("Return Value' should be a string\n");
		}
		szReturn1 = lua_tostring(pLuaState, -1);

		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n****Lua 함수 func_3 호출 후****\n");
		sprintf_s(szDbgString, "Lua의 함수 func_3의 리턴값은 ? %s\n", szReturn1);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 인자는 없지만 리턴값이 여러개인 함수 호출하기
		//
		lua_getglobal(pLuaState, "myfunc_3");

		if (lua_pcall(pLuaState, 0, 2, 0) != 0) {
			sprintf_s(szDbgString, "error running function `f': %s\n", lua_tostring(pLuaState, -1));
			OutputDebugStringA(szDbgString);
			__leave;
		}

		if (!lua_isboolean(pLuaState, -1)) {
			OutputDebugStringA("Return Value' should be a boolean\n");
		}
		bReturn2 = lua_toboolean(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("Return Value' should be a string\n");
		}
		szReturn1 = lua_tostring(pLuaState, -2);




		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n****Lua 함수 func_3 호출 후****\n");
		sprintf_s(szDbgString, "Lua의 함수 func_3의 리턴값은 ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 인자는 하나 리턴값이 여러개인 함수 호출하기
		//
		lua_getglobal(pLuaState, "myfunc_4");
		lua_pushstring(pLuaState, "myfunc_4");
		if (lua_pcall(pLuaState, 1, 2, 0) != 0) {
			sprintf_s(szDbgString, "error running function `f': %s\n", lua_tostring(pLuaState, -1));
			OutputDebugStringA(szDbgString);
			__leave;
		}

		if (!lua_isboolean(pLuaState, -1)) {
			OutputDebugStringA("Return Value' should be a boolean\n");
		}
		bReturn2 = lua_toboolean(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("Return Value' should be a string\n");
		}
		szReturn1 = lua_tostring(pLuaState, -2);




		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n****Lua 함수 func_4 호출 후****\n");
		sprintf_s(szDbgString, "Lua의 함수 func_4의 리턴값은 ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// 인자와 리턴값이 여러개인 함수 호출하기
		//
		
		lua_getglobal(pLuaState, "myfunc_5");
		lua_pushstring(pLuaState, "myfunc_5");
		lua_pushboolean(pLuaState, FALSE);

		DumpLuaStack(pLuaState);
		if (lua_pcall(pLuaState, 2, 2, 0) != 0) {
			sprintf_s(szDbgString, "error running function `f': %s\n", lua_tostring(pLuaState, -1));
			OutputDebugStringA(szDbgString);
			__leave;
		}

		if (!lua_isboolean(pLuaState, -1)) {
			OutputDebugStringA("Return Value' should be a boolean\n");
		}
		bReturn2 = lua_toboolean(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("Return Value' should be a string\n");
		}
		szReturn1 = lua_tostring(pLuaState, -2);




		lua_getglobal(pLuaState, "szWelcomMessage");
		lua_getglobal(pLuaState, "szWhoamI");


		if (!lua_isstring(pLuaState, -1)) {
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(pLuaState, -1);

		if (!lua_isstring(pLuaState, -2)) {
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(pLuaState, -2);

		OutputDebugStringA("\n****Lua 함수 func_5 호출 후****\n");
		sprintf_s(szDbgString, "Lua의 함수 func_5의 리턴값은 ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWhoamI의 값은 ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua의 전역 변수 szWelcomMessage의 값은 ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 2 장 - Lua에서 C 호출하기
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////

static int MyDbgString1(lua_State *pLuaState)
{
	OutputDebugStringA("MyDbgString 호출됨 \n");

	return 0;
}

static int MyDbgString2(lua_State *pLuaState)
{
	/* get number of arguments */
	int nTop{ 0 };
	const char *szDbgString{ NULL };

	__try {
		nTop = lua_gettop(pLuaState);
		if (1 != nTop) __leave;
		if (!lua_isstring(pLuaState, nTop)) __leave;

		szDbgString = lua_tostring(pLuaState, nTop);
		
		OutputDebugStringA(szDbgString);
	}
	__finally {

	}

	return 0;
}

static int MyDbgString3(lua_State *pLuaState)
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

static int MySum(lua_State *pLuaState)
{
	/* get number of arguments */
	int nTop{ 0 };
	const char *szDbgString{ NULL };
	int nStartVar{ 0 };
	int nStopVar{ 0 };
	int nSum{ 0 };

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

		lua_pushnumber(pLuaState, nSum);
	}
	__finally {

	}

	return 1;
}

static int MySumAndAverage(lua_State *pLuaState)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 2 장 - Lua에서 C 호출하기
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 4 - 루아에서 호출 가능한 C함수 만들기 1
//
void CLuaSampleDlg::OnBnClickedExample04Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };

	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		/* register our function */
		lua_register(pLuaState, "DbgString", MyDbgString1);

		if (luaL_dofile(pLuaState, "./Script/Sample04.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 5 - 루아에서 호출 가능한 C함수 만들기 2(인자 전달하기)
//
void CLuaSampleDlg::OnBnClickedExample05Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };

	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		luaL_openlibs(pLuaState);

		/* register our function */
		lua_register(pLuaState, "DbgString", MyDbgString2);
		lua_register(pLuaState, "Sum", MySum);


		if (luaL_dofile(pLuaState, "./Script/Sample05.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 6 - 루아에서 호출 가능한 C함수 만들기 3(리턴값 전달 받기)
//
void CLuaSampleDlg::OnBnClickedExample06Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };

	__try {
		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		luaL_openlibs(pLuaState);

		/* register our function */
		lua_register(pLuaState, "DbgString", MyDbgString3);
		lua_register(pLuaState, "SumAndAverage", MySumAndAverage);

		if (luaL_dofile(pLuaState, "./Script/Sample06.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 3 장 - Lua 확장 모듈(DLL) 만들기
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


int(*pNewSumAndAverage)(lua_State *pLuaState);
int(*pNewDbgString)(lua_State *pLuaState);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// 예제 7 - MyDbgString을 DLL로 구현하기
//
void CLuaSampleDlg::OnBnClickedExample07Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char			szDbgString[MAX_PATH]{ 0, };
	lua_State *		pLuaState{ NULL };
	HMODULE			hLuaExt{ NULL };

	__try {
		hLuaExt = LoadLibrary("LuaExt.dll");
		if (NULL == hLuaExt) __leave;
		pNewDbgString = (int(*)(lua_State *))GetProcAddress(hLuaExt, "DbgString");
		if (NULL == pNewDbgString) __leave;
		pNewSumAndAverage = (int(*)(lua_State *))GetProcAddress(hLuaExt, "SumAndAverage");
		if (NULL == pNewSumAndAverage) __leave;

		pLuaState = luaL_newstate();
		if (NULL == pLuaState) __leave;

		luaL_openlibs(pLuaState);

		/* register our function */
		lua_register(pLuaState, "DbgString", pNewDbgString);
		lua_register(pLuaState, "SumAndAverage", pNewSumAndAverage);

		if (luaL_dofile(pLuaState, "./Script/Sample07.lua")) {
			const char *pError = lua_tostring(pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {
		pNewDbgString = NULL;
		pNewSumAndAverage = NULL;
		if (NULL != hLuaExt) FreeLibrary(hLuaExt);
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}


void EmptyLuaStack(lua_State *pLuaState)
{
	int nTop{ 0 };

	__try {
		nTop = lua_gettop(pLuaState);
		for (int nIndex = nTop; nIndex >= 1; nIndex--)
			lua_remove(pLuaState, nIndex);
	}
	__finally {

	}
}

void DumpLuaStack(lua_State *pLuaState)
{
	int nTop{ 0 };
	char szDbgString[MAX_PATH]{ 0, };

	__try {
		nTop = lua_gettop(pLuaState);
		if (0 == nTop) __leave;
		nTop = -1 * nTop;

		for (int nIndex = -1; nIndex >= nTop; nIndex--)
		{
			switch (lua_type(pLuaState, nIndex))
			{
				case LUA_TNIL:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TNIL]\n", nIndex);
					break;
				case LUA_TNUMBER:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TNUMBER] : %f\n", nIndex, lua_tonumber(pLuaState, nIndex));
					break;
				case LUA_TBOOLEAN:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TBOOLEAN] : %s\n", nIndex, (FALSE == lua_toboolean(pLuaState, nIndex))? "FALSE" : "TRUE");
					break;
				case LUA_TSTRING:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TSTRING] : %s\n", nIndex, lua_tostring(pLuaState, nIndex));
					break;
				case LUA_TTABLE:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TTABLE]\n", nIndex);
					break;
				case LUA_TFUNCTION:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TFUNCTION]\n", nIndex);
					break;
				case LUA_TUSERDATA:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TUSERDATA]\n", nIndex);
					break;
				case LUA_TTHREAD:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TTHREAD]\n", nIndex);
					break;
				case LUA_TLIGHTUSERDATA:
					sprintf_s(szDbgString, MAX_PATH, "[%d][LUA_TLIGHTUSERDATA]\n", nIndex);
					break;
				default :
					sprintf_s(szDbgString, MAX_PATH, "[%d][UnknwonType %d]\n", nIndex, lua_type(pLuaState, nIndex));
			}
			OutputDebugStringA(szDbgString);
		}
	}
	__finally {

	}
}
