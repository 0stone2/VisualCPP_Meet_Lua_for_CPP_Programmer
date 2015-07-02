
// LuaSampleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "LuaSample.h"
#include "LuaSampleDlg.h"
#include "afxdialogex.h"


#include "C:/Lua/Library/include/lua.hpp"
#include "C:/Lua/Library/include/luaconf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
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
	: CDialogEx(CLuaSampleDlg::IDD, pParent)
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
	ON_BN_CLICKED(IDC_SAMPLE1_BUTTON, &CLuaSampleDlg::OnBnClickedSample1Button)
	ON_BN_CLICKED(IDC_SAMPLE2_BUTTON, &CLuaSampleDlg::OnBnClickedSample2Button)
	ON_BN_CLICKED(IDC_SAMPLE3_BUTTON, &CLuaSampleDlg::OnBnClickedSample3Button)
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

void CLuaSampleDlg::OnBnClickedSample1Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{0, };
	lua_State *		m_pLuaState{ NULL };

	__try {
		m_pLuaState = luaL_newstate();
		if (NULL == m_pLuaState) __leave;

		if (luaL_dofile(m_pLuaState, "Sample01.lua")) {
			const char *pError = lua_tostring(m_pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {

	}
}


void CLuaSampleDlg::OnBnClickedSample2Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char			szDbgString[MAX_PATH]{0, };
	lua_State *		m_pLuaState{ NULL };
	const char *	szWelcomMessage{ NULL };
	const char *	szWhoamI{ NULL };


	__try {
		m_pLuaState = luaL_newstate();
		if (NULL == m_pLuaState) __leave;

		if (luaL_dofile(m_pLuaState, "Sample02.lua")) {
			const char *pError = lua_tostring(m_pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}

		lua_getglobal(m_pLuaState, "szWelcomMessage");
		lua_getglobal(m_pLuaState, "szWhoamI");


		if (!lua_isstring(m_pLuaState, -1)) {
			// error(L, "`height' should be a number\n");
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(m_pLuaState, -1);

		if (!lua_isstring(m_pLuaState, -2)) {
			// error(L, "`height' should be a number\n");
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(m_pLuaState, -2);
		

		/*
		Executing Lua Code

		int lua_dofile   (lua_State *L, const char *filename);
		int lua_dostring (lua_State *L, const char *string);
		int lua_dobuffer (lua_State *L, const char *buff,
		size_t size, const char *name);



		int         lua_isnil       (lua_State *L, int index);
		int         lua_isnumber    (lua_State *L, int index);
		int         lua_isstring    (lua_State *L, int index);
		int         lua_istable     (lua_State *L, int index);
		int         lua_isfunction  (lua_State *L, int index);
		int         lua_iscfunction (lua_State *L, int index);
		int         lua_isuserdata  (lua_State *L, int index);

		int lua_equal    (lua_State *L, int index1, int index2);
		int lua_lessthan (lua_State *L, int index1, int index2);

		int				lua_toboolean (lua_State *L, int index);
		double			lua_tonumber (lua_State *L, int index);
		const char    *	lua_tostring (lua_State *L, int index);
		size_t			lua_strlen (lua_State *L, int index);
		int				lua_tag (lua_State *L, int index);
		int				lua_type(lua_State *L, int index);
		const char    *	lua_typename(lua_State *L, int type)

		double         lua_tonumber    (lua_State *L, int index);
		const char    *lua_tostring    (lua_State *L, int index);
		size_t         lua_strlen      (lua_State *L, int index);
		lua_CFunction  lua_tocfunction (lua_State *L, int index);
		void          *lua_touserdata  (lua_State *L, int index);

		int		lua_stackspace (lua_State *L);
		int		lua_gettop (lua_State *L);
		void	lua_settop (lua_State *L, int index);
		void	lua_pushvalue (lua_State *L, int index);
		void	lua_remove (lua_State *L, int index);
		void	lua_insert (lua_State *L, int index);
		void	lua_replace (lua_State *L, int index);




		-- The Stack and Indices
		int lua_gettop (lua_State *L);
		int lua_stackspace (lua_State *L);




		-- Stack Manipulation
		void lua_settop    (lua_State *L, int index);
		void lua_pushvalue (lua_State *L, int index);
		void lua_remove    (lua_State *L, int index);
		void lua_insert    (lua_State *L, int index);



		-- Querying the Stack
		int         lua_type        (lua_State *L, int index);
		int         lua_tag         (lua_State *L, int index);
		int         lua_isnil       (lua_State *L, int index);
		int         lua_isnumber    (lua_State *L, int index);
		int         lua_isstring    (lua_State *L, int index);
		int         lua_istable     (lua_State *L, int index);
		int         lua_isfunction  (lua_State *L, int index);
		int         lua_iscfunction (lua_State *L, int index);
		int         lua_isuserdata  (lua_State *L, int index);



		-- Pushing values onto the Stack
		void lua_pushnumber    (lua_State *L, double n);
		void lua_pushlstring   (lua_State *L, const char *s, size_t len);
		void lua_pushstring    (lua_State *L, const char *s);
		void lua_pushusertag   (lua_State *L, void *u, int tag);
		void lua_pushnil       (lua_State *L);
		void lua_pushcfunction (lua_State *L, lua_CFunction f);
		*/




		szWelcomMessage = lua_tostring(m_pLuaState, 1);
		szWhoamI = lua_tostring(m_pLuaState, 2);
	}
	__finally {

	}
}


void CLuaSampleDlg::OnBnClickedSample3Button()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
