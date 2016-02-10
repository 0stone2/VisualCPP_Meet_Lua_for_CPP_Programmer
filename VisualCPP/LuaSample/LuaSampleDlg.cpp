
// LuaSampleDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CLuaSampleDlg ��ȭ ����



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


// CLuaSampleDlg �޽��� ó����

BOOL CLuaSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLuaSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLuaSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 1 �� - C���� Lua ȣ���ϱ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 1 - ��� ��ũ��Ʈ ���� �����ϱ�
//
void CLuaSampleDlg::OnBnClickedExample01Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// ���� 2 - ��� ���� ���� �����ϱ�
//
void CLuaSampleDlg::OnBnClickedExample02Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

		// Lua�� ���� ���� �о� ����
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

		OutputDebugStringA("\n\n**** Lua ���� ���� ���� ��****\n");
		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
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

		OutputDebugStringA("****Lua ���� ���� ���� ��****\n");
		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);

		szWelcomMessage = lua_tostring(pLuaState, 1);
		szWhoamI = lua_tostring(pLuaState, 2);
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 3 - ��� �Լ� ȣ���ϱ�
//
void CLuaSampleDlg::OnBnClickedExample03Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		// ���ڿ� ���ϰ��� ���� �Լ� ȣ���ϱ�
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

		OutputDebugStringA("\n****Lua �Լ� func_1 ȣ�� ��****\n");
		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// ���ڴ� ������ ���ϰ��� �ϳ��� �Լ� ȣ���ϱ�
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

		OutputDebugStringA("\n****Lua �Լ� func_3 ȣ�� ��****\n");
		sprintf_s(szDbgString, "Lua�� �Լ� func_3�� ���ϰ��� ? %s\n", szReturn1);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// ���ڴ� ������ ���ϰ��� �������� �Լ� ȣ���ϱ�
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

		OutputDebugStringA("\n****Lua �Լ� func_3 ȣ�� ��****\n");
		sprintf_s(szDbgString, "Lua�� �Լ� func_3�� ���ϰ��� ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// ���ڴ� �ϳ� ���ϰ��� �������� �Լ� ȣ���ϱ�
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

		OutputDebugStringA("\n****Lua �Լ� func_4 ȣ�� ��****\n");
		sprintf_s(szDbgString, "Lua�� �Լ� func_4�� ���ϰ��� ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);



		////////////////////////////////////////////////////////////////////////////////////////////
		//
		// ���ڿ� ���ϰ��� �������� �Լ� ȣ���ϱ�
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

		OutputDebugStringA("\n****Lua �Լ� func_5 ȣ�� ��****\n");
		sprintf_s(szDbgString, "Lua�� �Լ� func_5�� ���ϰ��� ? %s, %d\n", szReturn1, bReturn2);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWhoamI�� ���� ? %s\n", szWhoamI);
		OutputDebugStringA(szDbgString);

		sprintf_s(szDbgString, "Lua�� ���� ���� szWelcomMessage�� ���� ? %s\n", szWelcomMessage);
		OutputDebugStringA(szDbgString);
	}
	__finally {
		if (NULL != pLuaState) lua_close(pLuaState);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// 2 �� - Lua���� C ȣ���ϱ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////

static int MyDbgString1(lua_State *pLuaState)
{
	OutputDebugStringA("MyDbgString ȣ��� \n");

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
// 2 �� - Lua���� C ȣ���ϱ�
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 4 - ��ƿ��� ȣ�� ������ C�Լ� ����� 1
//
void CLuaSampleDlg::OnBnClickedExample04Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// ���� 5 - ��ƿ��� ȣ�� ������ C�Լ� ����� 2(���� �����ϱ�)
//
void CLuaSampleDlg::OnBnClickedExample05Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// ���� 6 - ��ƿ��� ȣ�� ������ C�Լ� ����� 3(���ϰ� ���� �ޱ�)
//
void CLuaSampleDlg::OnBnClickedExample06Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// 3 �� - Lua Ȯ�� ���(DLL) �����
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////


int(*pNewSumAndAverage)(lua_State *pLuaState);
int(*pNewDbgString)(lua_State *pLuaState);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� 7 - MyDbgString�� DLL�� �����ϱ�
//
void CLuaSampleDlg::OnBnClickedExample07Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
